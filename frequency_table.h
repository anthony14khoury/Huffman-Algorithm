#pragma once
#include<stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

struct frequency_table {
    // Something to store the frequency of each character
    unordered_map<string, int> frequencyTable;

public:
    frequency_table();
    frequency_table(unordered_map<string, int> frequency);

    frequency_table(const std::string& file_name);
    ~frequency_table();
    int get_frequency(char c) const;

    int intToAscii(int number);
};