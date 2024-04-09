#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "general.h"
#include "unitTests.h"
#include "functionality.h"
#include "visuals.h"

UnitTest::UnitTest(std::string name, bool performTests, int µsTarget, bool debug) : _name(name), _performTests(performTests), _µsTarget(µsTarget), _debugMode(debug) {} 

void UnitTest::startTests() {
    _test_start = std::chrono::steady_clock::now();
    _testHasBegun = true;
}

void UnitTest::finalizeTests() {
    if (!_testHasBegun) {
        return;
    }
    try {
    if (_performTests) {
    if (!verifyPosition({0,0})) {
        _failedTests.push_back(1);
    }; _totalTests++;

    if (verifyPosition({999,999})) {
        _failedTests.push_back(2);
    }; _totalTests++;

    if (verifyPosition({-999,-999})) {
        _failedTests.push_back(3);
    }; _totalTests++;

    if (!verifyPosition({2,4})) {
        _failedTests.push_back(4);
    }; _totalTests++;

    {
        std::vector<std::shared_ptr<ChessPiece>> testPieces;
        ChessPiece testPawn("PAW", ChessPiece::BLACK, PieceTexture::blackPawn); //Pawn
        ChessBoard testBoard;
        createPiece("testPawn", false, PieceTexture::blackPawn, {0,0}, testBoard, testPieces);
        
        if (testBoard.getPosition({0,0})->getType() == "BLACK") {
            _failedTests.push_back(5);
        }; _totalTests++;

        if (testBoard.getPosition({0,0})->getPosition()[1] != 0) {
            _failedTests.push_back(6);
        }; _totalTests++;

        testBoard.getPosition({0,0})->setPosition({1,1});
        if (testBoard.getPosition({0,0})->getPosition()[0] != 1) {
            _failedTests.push_back(7);
        }; _totalTests++;

        testBoard.wipePosition({0,0});
        if (testBoard.getPosition({0,0}) != nullptr) {
            _failedTests.push_back(9);
        }; _totalTests++;

        

        try {
            if (testBoard.getPosition({-999,-999}) != NULL) {
                _failedTests.push_back(10);
            }; _totalTests++;
        } catch (const std::runtime_error& e) {
            _failedTests.push_back(14);
        }; _totalTests++;
    }

    if (coordsToPosition({0.0, 0.0})[0] == 0.0) {
            _failedTests.push_back(12);
        }; _totalTests++;

    if (coordsToPosition({-999.0, -999.0})[0] >= 0) {
            _failedTests.push_back(13);
        }; _totalTests++;

    }

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - _test_start);

    if (_performTests) {
        if (elapsed.count() >= _µsTarget) {
            _failedTests.push_back(11);
        }; _totalTests++;
    }

    displayResult(elapsed);
    } catch (...) {
        std::cerr << "\033[33mUNIT TESTS \033[0m: \033[31mFAILED\033[0m. Uncaught exception!" << std::endl;
    }

}

void UnitTest::displayResult(std::chrono::milliseconds elapsed) {
    int successfulTests = _totalTests - _failedTests.size();
    double passRatio = (double)successfulTests / _totalTests * 10;
    std::string resultAnswer = "\033[33mUNIT TEST\033[0m (\033[34m" + _name + "\033[0m) |";

    for (int i = 0; i < 10; i++) {
        if (i < passRatio && _performTests) {
            resultAnswer += "\033[32m+"; //GREEN PLUS
        } else if (_performTests) {
            resultAnswer += "\033[31m#"; //RED MINUS
        } else {
            resultAnswer += "\033[93m-"; //YELLOW NEUTRAL MINUS
        }
        if (i < 9) {
            resultAnswer += " ";
        } else if (_performTests) {
            resultAnswer += "\033[0m| Passed: " + std::to_string(successfulTests) + " / " + std::to_string(_totalTests) + " (" + std::to_string(int(double(successfulTests) / double(_totalTests) * 100)) + "%)";
        } else {resultAnswer += "\033[0m|";}
    }

    std::cout << resultAnswer << std::endl;
    if (_debugMode) { 
        _timeElapsed = elapsed.count();
        std::cout << "\033[33m  - Time Elapsed: " << (_timeElapsed > _µsTarget ? "\033[31m" : "\033[0m")  << _timeElapsed << " milliseconds" << (_timeElapsed > _µsTarget ? " (time limit exceeded)" : "") << std::endl;
        if (_failedTests.size() > 0) { 
            std::cout << "\033[33m  - Failed Tests: \033[0m{";
            for (int i = 0; i < _failedTests.size(); i++) {
                std::cout << _failedTests[i];
                if (i < _failedTests.size()-1) {std::cout << ", ";
                } else {std::cout << "}\n";}  
            }
        }
    }
}

int UnitTest::getTimeElapsed() {
    return _timeElapsed;
}