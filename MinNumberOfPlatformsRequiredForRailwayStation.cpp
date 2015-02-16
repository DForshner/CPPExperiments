// Given the arrival and departure times of all trains that
// reach a given station, find the minimum number of
// platforms required for the station so that no train waits.
//
// Find the maximum number of trains that are at the station at
// any one time by sorting the events in time and keeping track
// of the net balance of arrivals and departures at a given step.
//
// Time Complexity: O(nlog(n))
// Space Complexity: O(1)
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include <cassert>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MinNumberOfPlatformsRequiredForRailwayStation {

  // O(N^2) Brute force method
  // Compare every interval to all other intervals and track 
  // the max number of overlapping intervals.
  int bruteForce(const vector<int>& arrivals, const vector<int>& departures) {
    assert(arrivals.size() == departures.size());

    auto maxNumberOfTrains = 0;
    for (auto i = 0; i < arrivals.size(); i++) {
      // There will be one train at the station in the current interval
      auto currentNumberOfTrains = 1;
      for (auto j = 0; j < arrivals.size(); j++) {
        if (j == i) { continue; }

        // Does i interval overlap with j interval?
        if (
          // i   a| ----- |d
          // j   ?---|d
          (departures[j] >= arrivals[i] && departures[j] <= departures[i]) 
          // i   a| ----- |d
          // j       a|---?
          || (arrivals[j] >= arrivals[i] && arrivals[j] <= departures[i])) {
          currentNumberOfTrains++;
        }
      }

      // Check if we have achieved a new maximum;
      if (currentNumberOfTrains > maxNumberOfTrains) {
        maxNumberOfTrains = currentNumberOfTrains;
      }
    }
    return maxNumberOfTrains;
  };

  int minNumberOfPlatformsRequired(vector<int>& arrivals, vector<int>& departures) {
    assert(arrivals.size() == departures.size());

    // Sort the events in time
    sort(arrivals.begin(), arrivals.end());
    sort(departures.begin(), departures.end());

    int i{ 1 };
    int j{ 0 };
    int currentNumberOfTrains{ 1 };
    int maxNumberOfTrains{ 0 };
      
    // Use a merge-like process to process the two arrays of 
    // events together in chronological order.
    while (i < arrivals.size() && j < departures.size()) {
      if (arrivals[i] < departures[j]) {
        // An arrival has occurred so increase the number of trains;
        currentNumberOfTrains++;
        i++;

        // Check if we have achieved a new maximum.
        if (currentNumberOfTrains > maxNumberOfTrains) {
          maxNumberOfTrains = currentNumberOfTrains;
        }
      } else {
        // An departure has occurred so decrease the number of trains;
        currentNumberOfTrains--;
        j++;
      }
    }

    return maxNumberOfTrains;
  }

  TEST_CLASS(MinNumberOfPlatformsRequiredForRailwayStationTests) {
    public:
      TEST_METHOD(ExpectMatchesBruteForceResult) {
        vector<int> arrivals{ 900, 940, 950, 1100, 1500, 1800 };
        vector<int> departures{ 910, 1200, 1120, 1130, 1900, 2000 };
        auto bruteForceResult = bruteForce(arrivals, departures);
        auto result = minNumberOfPlatformsRequired(arrivals, departures);
        Assert::AreEqual(bruteForceResult, result);
      }

      TEST_METHOD(WhenNoArrivals_ExpectZeroPlatformsNeeded) {
        vector<int> arrivals{};
        vector<int> departures{};
        auto result = minNumberOfPlatformsRequired(arrivals, departures);
        Assert::AreEqual(0, result);
      }

      TEST_METHOD(WhenThreeIntervalsOverlap_ExpectMinPlatformsIs3) {
        vector<int> arrivals{ 900, 940, 950, 1100, 1500, 1800 };
        vector<int> departures{ 910, 1200, 1120, 1130, 1900, 2000 };
        auto result = minNumberOfPlatformsRequired(arrivals, departures);
        Assert::AreEqual(3, result);
      }
  };
}