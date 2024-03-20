#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <iostream>
#include <chrono>

class UnitTest {
    public:
        UnitTest(std::string name="Unnamed", bool performTests=true, int µsTarget=50, bool debug=false);

        //Start the testing (primarily starts a time counter)
        void startTests();

        //End the test by performing the real tests if neccessary, and end the time counter.
        void finalizeTests();

        //Output the result of the test to the logs.
        void displayResult(std::chrono::milliseconds timeElapsed);

        //Return the amount of time that the test has taken.
        int getTimeElapsed();
    private:
        std::string _name;
        bool _performTests;
        std::chrono::_V2::steady_clock::time_point _test_start;
        bool _testHasBegun=false;
        int _timeElapsed;
        int _µsTarget;
        int _totalTests;
        std::vector<int> _failedTests;
        bool _debugMode;
};

#endif