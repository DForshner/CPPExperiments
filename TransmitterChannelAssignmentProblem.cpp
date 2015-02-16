// Given a matrix that shows the number of packets to be sent 
// from M transmitters to N receivers determine the maximum number
// of packets that can be transmitted in a single time step.
// Transmitters/receivers can only send/receive a single
// packet each time step.
// The matrix is indexed as m[transmitterId][recieverId].
//
// This is a maximum bipartite matching problem.
// We iterate through each transmitter and attempt to match
// it to either an unoccupied receiver or a receiver that has
// a transmitter we can reassign.
//
// Time Complexity: O(MN^2) (I'm not sure this is correct).
// Space Complexity: O(MN)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TransmitterChannelAssignmentProblem {

  // Perform a Depth First Search that returns true if a matching for the transmitter is possible.
  bool isBipartiteMatchingPossible(const vector<vector<int>>& m, int transmitterId, vector<bool>* visited, vector<int>* transmitterForReceiver) {
    // Try each receiver
    for (int recieverId = 0; recieverId < visited->size(); recieverId++) {

      // If this transmitter has packets for this receiver AND we haven't already visited this receiver.
      if (m[transmitterId][recieverId] > 0
        && !visited->at(recieverId)) {

        visited->at(recieverId) = true; // This receiver has been visited for the sender being matched. 

        // If receiver is not assigned to a sender OR the previously
        // assigned sender for the receiver can be reassigned to an alternate 
        // receiver from the currently unvisited receivers.
        // Think of this like we are going to take this receiver's current transmitter and reassign it 
        // by shuffling it downwards to its next possible receiver that we haven't visited already.
        if (transmitterForReceiver->at(recieverId) < 0
          || isBipartiteMatchingPossible(m, transmitterForReceiver->at(recieverId), visited, transmitterForReceiver)) {
          transmitterForReceiver->at(recieverId) = transmitterId;
          return true;
        }
      }
    }

    return false;
  }

  // Given a matrix with transmitter rows to receiver columns (m[transmitterId][recieverId])
  // return the maximum number of packets that can be assigned in one time slot and the assignment
  // of senders to receivers.
  pair<int, vector<int>> findMaximumNumberOfPacketsForOneTimeSlot(const vector<vector<int>>& m) {
    auto numTransmitters = m.size();
    if (numTransmitters == 0) { return make_pair<int, vector<int>>(0, {}); }

    auto numReceivers = m[0].size();
    vector<int> transmitterForReceiver(numReceivers, numeric_limits<int>::min()); // TransmitterId assigned to receiverId i.

    // Try to assign each transmitter to a receiver
    int numReceiversAssignedToSenders{ 0 };
    for (auto transmitterId = 0; transmitterId < numTransmitters; transmitterId++) {
      vector<bool> visited(numReceivers, false);

      // If sender can be assigned to a receiver
      if (isBipartiteMatchingPossible(m, transmitterId, &visited, &transmitterForReceiver)) {
        numReceiversAssignedToSenders++;
      }
    }

    return make_pair(numReceiversAssignedToSenders, transmitterForReceiver);
  }

  TEST_CLASS(TransmitterChannelAssignmentProblemTests) {
    public:
      TEST_METHOD(WhenLaterTransmittersHaveLimitedReceievers_ExpectEarlierTransmittersReassigned) {
        vector<vector<int>> m{ 
          { 1, 1, 1 },  // Transmitter 0
          { 1, 1, 0 },  // Transmitter 1
          { 1, 0, 0 }   // Transmitter 2 
        };
        auto result = TransmitterChannelAssignmentProblem::findMaximumNumberOfPacketsForOneTimeSlot(m);
        Assert::AreEqual(3, result.first);
        Assert::AreEqual(2, result.second[0]); // R0 -> T2
        Assert::AreEqual(1, result.second[1]); // R1 -> T1
        Assert::AreEqual(0, result.second[2]); // R2 -> T0
      }

      TEST_METHOD(WhenNoPacketsForReceiver_ExpectNoTransmitterAssigned) {
        vector<vector<int>> m{ 
          { 0, 1, 0 },  // Transmitter 0
          { 0, 0, 1 }   // Transmitter 1
        };
        auto result = TransmitterChannelAssignmentProblem::findMaximumNumberOfPacketsForOneTimeSlot(m);
        Assert::AreEqual(2, result.first);
        Assert::AreEqual(numeric_limits<int>::min(), result.second[0]); // R0 -> -ve
        Assert::AreEqual(0, result.second[1]); // R1 -> T0
        Assert::AreEqual(1, result.second[2]); // R2 -> T1
      }

      TEST_METHOD(WhenThreeTrasmittersAndThreeReceievers_ExpectAllAssigned) {
        vector<vector<int>> m{ 
          { 0, 2, 0 },  // Transmitter 0
          { 3, 0, 1 },  // Transmitter 1
          { 2, 4, 0 }   // Transmitter 2
        };
        auto result = TransmitterChannelAssignmentProblem::findMaximumNumberOfPacketsForOneTimeSlot(m);
        Assert::AreEqual(3, result.first);
        Assert::AreEqual(2, result.second[0]); // R0 -> T2
        Assert::AreEqual(0, result.second[1]); // R1 -> T0
        Assert::AreEqual(1, result.second[2]); // R2 -> T1
      }
  };
}