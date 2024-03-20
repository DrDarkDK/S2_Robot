#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include "general.h"
#include "unitTests.h"
#include "functionality.h"
#include "visuals.h"

void performTests(bool debug) {
    auto start = std::chrono::steady_clock::now();
    std::vector<int> results = {0, 0}; // failed tests : tests total.

    try {
    if (!verifyPosition({0,0})) {
        if (debug) {std::cout << "Unit Test (1): Failed" << std::endl;}
        results[0]++;
    }; results[1]++;

    if (verifyPosition({999,999})) {
        if (debug) {std::cout << "Unit Test (2): Failed" << std::endl;}
        results[0]++;
    }; results[1]++;

    if (verifyPosition({-999,-999})) {
        if (debug) {std::cout << "Unit Test (3): Failed" << std::endl;}
        results[0]++;
    }; results[1]++;

    if (!verifyPosition({2,4})) {
        if (debug) {std::cout << "Unit Test (4): Failed" << std::endl;}
        results[0]++;
    }; results[1]++;

    {
        ChessPiece testPawn("PAW", ChessPiece::BLACK, PieceTexture::blackPawn); //Pawn
        ChessBoard testBoard;
        std::shared_ptr<ChessPiece> testPtr = std::make_shared<ChessPiece>(std::move(testPawn));
        testBoard.placePiece(testPtr, {0,0});
        
        if (testBoard.getPosition({0,0})->getType() == "BLACK") {
            if (debug) {std::cout << "Unit Test (5): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

        if (testBoard.getPosition({0,0})->getPosition()[1] != 0) {
            if (debug) {std::cout << "Unit Test (6): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

        testBoard.getPosition({0,0})->setPosition({1,1});
        if (testBoard.getPosition({0,0})->getPosition()[0] != 1) {
            if (debug) {std::cout << "Unit Test (7): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

        testBoard.movePiece({0,0}, {1,1});
        if (testBoard.getPosition({1,1})->getType() != testPtr->getType()) {
            if (debug) {std::cout << "Unit Test (8): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

        testBoard.wipePosition({1,1});
        if (testBoard.getPosition({1,1}) != nullptr) {
            if (debug) {std::cout << "Unit Test (9): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

        if (testBoard.getPosition({-999,-999}) != NULL) {
            if (debug) {std::cout << "Unit Test (10): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;
    }

    if (coordsToPosition({0.0, 0.0})[0] == 0.0) {
            if (debug) {std::cout << "Unit Test (12): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

    if (coordsToPosition({-999.0, -999.0})[0] >= 0) {
            if (debug) {std::cout << "Unit Test (13): Failed" << std::endl;}
            results[0]++;
        }; results[1]++;

    initializeTextures();

    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    bool timeTooLong = false;

    if (elapsed.count() >= 50) {
            if (debug) {std::cout << "Unit Test (11): Failed" << std::endl;}
            timeTooLong = true;
            results[0]++;
        }; results[1]++;
    
    displayResult(results, elapsed, timeTooLong);
    } catch (const std::runtime_error& e) {
        std::cerr << "\033[33mUNIT TESTS \033[0m: \033[31mFAILED\033[0m. Caught Exception: \033[38;5;187m" << e.what() << std::endl;
    }

}

void displayResult(std::vector<int> results, std::chrono::milliseconds elapsed, bool timeFail) {
    int successfulTests = results[1] - results[0];
    double passRatio = (double)successfulTests / results[1] * 10;
    std::string resultAnswer = "\033[33mUNIT TESTS \033[0m|";

    for (int i = 0; i < 10; i++) {
        if (i < passRatio) {
            resultAnswer += "\033[32m+"; //GREEN PLUS
        } else {
            resultAnswer += "\033[31m-"; //RED MINUS
        }
        if (i < 9) {
            resultAnswer += " ";
        } else {
            resultAnswer += "\033[0m| Passed: " + std::to_string(successfulTests) + " / " + std::to_string(results[1]) + " (" + std::to_string(int(double(successfulTests) / double(results[1]) * 100)) + "%)";
        }
    }

    std::cout << resultAnswer << std::endl;
    std::cout << "\033[33mTime Elapsed: " << (timeFail ? "\033[31m" : "\033[0m")  << elapsed.count() << " milliseconds" << (timeFail ? " (time limit exceeded)" : "") << std::endl;
    std::cout << "\033[0m";
}