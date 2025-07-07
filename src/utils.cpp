#include <cassert>
#include <iostream>
#include <string>
#include "utils.hpp"

int cellToIndex(std::string s) {
    if (s.length() != 2) { 
        std::cerr << "ERROR: cell notation " << s << " incorrect";
        assert(true);
    }
    int row = 0;
    int col = s[1];
    switch (s[0]) {
        case 'a': row = 1; break;
        case 'b': row = 2; break;
        case 'c': row = 3; break;
        case 'd': row = 4; break;
        case 'e': row = 5; break;
        case 'f': row = 6; break;
        case 'g': row = 7; break;
        case 'h': row = 8; break;
    }
    return row * 8 + col;
}

std::string index_to_cell(int index) {
    std::string result = "";
    int row = index / 8 + 1;
    int col = index - (row-1) * 8 + 1;
    switch (row) {
        case 1: result += 'a'; break;
        case 2: result += 'b'; break;
        case 3: result += 'c'; break;
        case 4: result += 'd'; break;
        case 5: result += 'e'; break;
        case 6: result += 'f'; break;
        case 7: result += 'g'; break;
        case 8: result += 'h'; break;
    }
    result += std::to_string(col);
    return result; 
}
