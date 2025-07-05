#include <cassert>
#include <iostream>
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
