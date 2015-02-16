// Given a series of weighted jobs to schedule find the
// subset of jobs with the maximum value that do not
// overlap in time. Return both the maximum value and
// the jobs that produced it.
//
// Complier: Visual Studio 2013 (v120)

#include <vector>
#include <algorithm>
#include "CppUnitTest.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JobSchedulingFindMaxValueScheduleForWeightedJobs {

  struct Job {
    int Start;
    int End;
    int Value;

    Job(int start, int end, int value) :
      Start(move(start)), 
      End(move(end)), 
      Value(move(value)) {}
  };

  class Scheduler {
    public:

      Scheduler(vector<Job> jobs) : _jobs(move(jobs)) {
        sort(_jobs.begin(), _jobs.end(), [](const Job& a, const Job& b) { return a.End < b.End; });
      }

      // Returns the maximum value and the jobs that produced it.
      // Time Complexity: O(nlogn)
      // Space Complexity: O(n) to hold the return list of jobs.
      pair<int, vector<Job>> GetMaxValueSchedule() {
        vector<bool> include(_jobs.size(), false);

        // Determine the maximum value.
        vector<int> subProblems(_jobs.size(), 0);
        
        // Start off by including the the first job
        subProblems[0] = _jobs[0].Value;
        include[0] = true;

        for (auto i = 1; i < _jobs.size(); i++) {
          // Including the current job. 
          auto including = _jobs[i].Value;
          auto latestJob = getLatestJobThatDoesNotConflict(i);
          if (latestJob >= 0) {
            including += subProblems[latestJob];
          }

          // Not including the current job.
          auto notIncluding = subProblems[i - 1];

          // Take the maximum value
          if (including > notIncluding) {
            include[i] = true;
            subProblems[i] = including;
          } else {
            subProblems[i] = notIncluding;
          }
        }

        auto includedJobs = getJobsThatProducedMaxValue(include);

        return make_pair(subProblems[_jobs.size() - 1], includedJobs);
      }

    private:
      vector<Job> _jobs;

      // Work backwards to determine which jobs produced the maximum.
      vector<Job> getJobsThatProducedMaxValue(vector<bool> include) {
        vector<Job> includedJobs;
        int currentJob = _jobs.size() - 1;
        while (currentJob >= 0) {

          if (include[currentJob]) {
            includedJobs.emplace_back(_jobs[currentJob]);
          }

          // Get the other job
          currentJob = getLatestJobThatDoesNotConflict(currentJob);
        }

        return move(includedJobs);
      }

      // Use binary search to find the latest job that does not conflict
      // with the current job i.
      // Time Complexity: O(logn), Space Complexity: O(1)
      int getLatestJobThatDoesNotConflict(int i) {
        int target = _jobs[i].Start;
        int left{ 0 };
        int right = _jobs.size() - 1;
        int mid = (left + right) / 2;

        while (mid != left) {
          mid = (left + right) / 2;
          if (_jobs[mid].End <= target) {
            left = mid;
          } else {
            right = mid;
          }
        }

        // We are down to one or two elements so pick the rightmost of the two
        // that don't conflict with the current job i.
        if (_jobs[right].End <= target) {
          return right;
        } else if (_jobs[left].End <= target) {
          return left;
        } else {
          return numeric_limits<int>::min();
        }
      }
  };

  TEST_CLASS(JobSchedulingFindMaxValueScheduleForWeightedJobsTests) {
    public:
      TEST_METHOD(WhenFirstAndLastJobsAreGreaterThanMiddle_ExpectFirstAndLastTaken) {
        Scheduler sut({ { 1, 2, 50 }, { 3, 5, 20 }, { 6, 19, 100 }, { 2, 100, 200 } });
        auto result = sut.GetMaxValueSchedule();
        Assert::AreEqual(250, result.first);
        Assert::AreEqual(size_t(2), result.second.size());
        Assert::IsTrue(find_if(result.second.cbegin(), result.second.cend(), [](const Job& x) { return x.Start == 1; }) != result.second.cend());
        Assert::IsTrue(find_if(result.second.cbegin(), result.second.cend(), [](const Job& x) { return x.Start == 2; }) != result.second.cend());
      }
  };
}