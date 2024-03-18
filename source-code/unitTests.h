#ifndef UNITTESTS_H
#define UNITTESTS_H

#include <iostream>
#include <chrono>

void performTests(bool debug = false);
void displayResult(std::vector<int> results, std::chrono::milliseconds timeElapsed, bool timeFail);

#endif