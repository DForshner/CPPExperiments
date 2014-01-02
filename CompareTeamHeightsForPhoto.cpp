// Take the heights of the players in two teams and check if it's possible to take
// a photo such that all members of one team are higher than their counterpart in the
// other team.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct Player {
  bool operator < (const Player& that) const { 
    return height < that.height;
  }
  unsigned height;
};

class Team {
public:
  // Constructor
  explicit Team(const vector<unsigned>& heights) {
    for (const auto &h : heights)
      members.emplace_back(Player{ h });
  }

  // Sort each team's players by height and compare each pair of players.
  bool operator <(const Team& that) const {
    vector<Player> this_sorted(sort_by_height());
    vector<Player> that_sorted(that.sort_by_height());

    // Check that for each pair of players the this is greater than that.
    for (auto i = 0; i < this_sorted.size() && i < that_sorted.size(); ++i) {
      if (!(this_sorted[i] < that_sorted[i]))
        return false;
    }

    return true;
  }

  void display(string title) const {
    cout << endl << title << " ";
    for (const auto &h : members)
      cout << h.height << ",";

    cout << endl;
  }

private:
  vector<Player> sort_by_height() const {
    vector<Player> sorted_members(members);
    sort(sorted_members.begin(), sorted_members.end());
    return sorted_members;
  }

  vector<Player> members;
};

int main() { 
  auto team_a = Team(vector<unsigned> { 1, 2, 3, 4, 5 }); 
  auto team_b = Team(vector<unsigned> { 2, 3, 4, 5, 6 }); 

  team_a.display("Team A");
  team_b.display("Team B");

  cout << endl << "Team A < Team B " << ((team_a < team_b) ? "True" : "False") << endl;

  cout << endl << "Team A > Team B " << ((team_b < team_a) ? "True" : "False") << endl;

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}