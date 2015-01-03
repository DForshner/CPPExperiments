// Attempts to implement a persistent file transaction using a three file scheme.
// Based on https://www.relisoft.com/book/tech/8trans.html
//
// TODO: There is a bug that is crashing this on the first attempt to read from
// the data file.
//
// Compiled with GCC 4.9

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <array>
#include <cassert>
#include <memory>

class SaveTransaction {
  public:
    SaveTransaction(std::string fileName) :
      _fileName(fileName),
      _commit (false) {
        assert(fileName != "");

        // Figure out which file has the most recent updates.
        _switch.open(getSwitchFileName(), std::fstream::in | std::fstream::out);
        if (_switch.good()) {
          std::cout << "Switch file existed" << std::endl;
          unsigned char stuff;
          _switch >> stuff;
          _state = (States)stuff;
        } else {
          std::cout << "Creating switch file" << std::endl;
          // Attempt to Create file
          _switch.open(getSwitchFileName(), std::fstream::in | std::fstream::out | std::fstream::trunc);
          _state = States::DataInA;
          _switch << static_cast<char>(_state);
          _switch.flush();
        }

        if (_state != States::DataInA && _state != States::DataInB) {
          throw "Switch file corrupted";
        }

        std::cout << "Loading data from " << static_cast<char>(_state) << std::endl;

        _data.open(getDataFileName(), std::fstream::in | std::fstream::out);
        if (!_data.good()) {
          // Attempt to create file
          std::cout << "Creating data file" << std::endl;
          _data.open(getDataFileName(), std::fstream::in | std::fstream::out | std::fstream::trunc);
        }

        _backup.open(getBackupFileName(), std::fstream::in | std::fstream::out);
        if (!_backup.good()) {
          // Attempt to create file
          std::cout << "Creating backup file" << std::endl;
          _backup.open(getBackupFileName(), std::fstream::in | std::fstream::out | std::fstream::trunc);
        }
    }

    std::istream* getDataFile() { return &_data; }

    std::ostream* getBackupFile() { return &_backup; }

    ~SaveTransaction() {
      _switch.close();

      // Remove stale data
      std::ofstream toTruncate;
      if (_commit == true) {
         _data.close();
         toTruncate.open(getDataFileName(), std::ofstream::out | std::ofstream::trunc);
      } else {
         _backup.close();
         toTruncate.open(getBackupFileName(), std::ofstream::out | std::ofstream::trunc);
      }
      toTruncate.close();
    }

    void commit() {
      States otherState = (_state == States::DataInA) ? States::DataInB : States::DataInA;

      // Flush the file containing the new updates to disk.
      _backup.flush();

      // Peform what we will hope is an atomic write to the switch file to
      // switch over to the new data.
      std::cout << "Writing data to: " << static_cast<char>(otherState) << std::endl;
      _switch.seekp(0); // Rewind the put pointer to the beginning of file.
      _switch << static_cast<char>(otherState);
      _switch.flush();

      // Once flush succeeds we are going to assume that the data is safely on disk.
      // Note: This isn't true for all file systems.

      _commit = true;
    }

  private:
    enum class States : char { DataInA = 'A', DataInB = 'B' };
    States _state;

    bool _commit;
    std::string _fileName;
    std::fstream _switch;
    std::fstream _data;
    std::fstream _backup;
    
    std::string getSwitchFileName() {
      return _fileName + "_s";
    }

    std::string getBackupFileName() {
      return (_state == States::DataInA) ? _fileName + "_b" : _fileName + "_a";
    }

    std::string getDataFileName() {
      return (_state == States::DataInA) ? _fileName + "_a" : _fileName + "_b";
    }
};

int main() {

  SaveTransaction test("Test.txt");

  std::cout << std::endl << "Start: [" << test.getDataFile()->rdbuf() << "]" << std::endl;

  *(test.getBackupFile()) << "Step A";
  test.commit();
  std::cout << std::endl << "After A: [" << test.getDataFile()->rdbuf() << "]" << std::endl;

  *(test.getBackupFile()) << "Step B";
  test.commit();
  std::cout << std::endl << "After B: [" << test.getDataFile()->rdbuf() << "]" << std::endl;

  return 0;
}
