#include "fen.hpp"
#include "figure.hpp"
#include "utils.hpp"
#include <array>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/types.h>

void FenNotation::parce(std::string s) {
    std::array<std::string, 6> fenParts;
    std::stringstream ss(s);
    std::string part;
    int arrIndex = 0;
    while (std::getline(ss, part, ' ')) {
        fenParts[arrIndex] = part;
        arrIndex++;
    }

    std::string enPassantSquareNotation = fenParts[3];
    std::string halfmoveClockNotation = fenParts[4];
    std::string fullmoveNumberNotation = fenParts[5];

    parcePosition(fenParts[0]);
    parceActiveColor(fenParts[1]);
    parceCastingAvailability(fenParts[2]);
    parceEnPassantSquare(fenParts[3]);
    parceHalfmoveClock(fenParts[4]);
    parceFullmoveNumber(fenParts[5]);
}

void FenNotation::parcePosition(std::string s) {
    uint row = 7;
    uint col = 0;
    int index = 0;
    for (char c : s) {
        if (c == '/') {
            row--;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            /* Проверять, что буквы из списка доступных, иначе выводить ошибку */
            Color color = isupper(c) ? Color::White : Color::Black;
            FigureType type;

            switch (tolower(c)) {
                case 'p': type = FigureType::Pawn; break;
                case 'n': type = FigureType::Knight; break;
                case 'b': type = FigureType::Bishop; break;
                case 'r': type = FigureType::Rook; break;
                case 'q': type = FigureType::Queen; break;
                case 'k': type = FigureType::King; break;
                default: type = FigureType::Empty; break;
            }
            const uint position = row * 8 + col;
            const Figure f = Figure(color, type);
            FigurePosition fp = { f, position };
            figurePositions[index] = fp;
            index++;
            col++;
        }
    }
}

void FenNotation::parceActiveColor(std::string s) {
    if (s.length() != 1) {
        assert("ERROR: active color is not a single character");
    }
    switch (s[0]) {
        case 'w':
            activeColor = Color::White;
            break;
        case 'b':
            activeColor = Color::Black;
            break;
    }
}

void FenNotation::parceCastingAvailability(std::string s) {
    CastingAvailability ca = {};
    for (char c : s) {
        switch (c) {
            case 'k': castingAvailability.BlackKingSide = true; break;
            case 'q': castingAvailability.BlackQueenSide = true; break;
            case 'K': castingAvailability.WhiteKingSide = true; break;
            case 'Q': castingAvailability.WhiteQueenSide = true; break;
            case '-': break;
            default: 
                std::cerr << "ERROR: unknown character " << c << " for casting availability" << std::endl;
                assert(true);
                break;
        }
    }
}

void FenNotation::parceHalfmoveClock(std::string s) {
    if (s == "-") {
        halfmoveClock = 0;
    } else {
        for (char c : s) {
            if (! std::isdigit(c)) {
                std::cerr << "ERROR: char '" << c << "' is not a digit";
                assert(true);
            }
        }
        halfmoveClock = std::stoi(s);
    }
}

void FenNotation::parceFullmoveNumber(std::string s) {
    if (s == "-") {
        fullmoveNumber = 0;
    } else {
        for (char c : s) {
            if (! std::isdigit(c)) {
                std::cerr << "ERROR: char '" << c << "' is not a digit";
                assert(true);
            }
        }
        fullmoveNumber = std::stoi(s);
    }
}

void FenNotation::parceEnPassantSquare(std::string s) {
    if (s == "-") {
        enPassantSquare = -1;
    } else {
        enPassantSquare = cellToIndex(s);
    }
}

std::ostream& operator<<(std::ostream& os, CastingAvailability& c) {
    if (c.BlackKingSide) { os<<"k"; }
    if (c.BlackQueenSide) { os<<"q"; }
    if (c.WhiteKingSide) { os<<"K"; }
    if (c.WhiteQueenSide) { os<<"Q"; }
    if (!(c.BlackKingSide || c.BlackQueenSide || c.WhiteKingSide || c.WhiteQueenSide)) {
    os<<"-";
    }
    return os;
}
std::ostream& operator<<(std::ostream& os, FenNotation fen) {
    os << "Figure positions:";
    for(auto fp : fen.getFigurePositions()) {
        os << "\n\t" << fp;       
    }
    os << "\nActive color: " << fen.getActiveColor()
        << "\nCasting availability: " << fen.getCastingAvailability()
        << "\nEn passant square: " << fen.getEnPassantSquare()
        << "\nHalfmove Clock: " << fen.getHalfmoveClock()
        << "\nFullmove number: " << fen.getFullmoveNumber()
        << std::endl;
    return os;
}
