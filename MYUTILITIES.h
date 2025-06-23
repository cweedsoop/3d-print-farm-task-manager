/*
    Filename: MYUTILITIES.h
    Description: .h file for collection of personal utilities
    Author: [Jingfu Peng]
    Class: [CSCI 120-70]
    Date: [7/1/2024]
 */

#pragma once

#include <string>

using namespace std;

string GetlineEX(int maxlength = -1);
void RemoveStartingWhitespace(string& inputString);
void RemoveEndingWhitespace(string& inputString);
void WhitespaceCleanup(string& inputString);
bool CheckDigitString(string inputString);