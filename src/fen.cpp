#include "fen.hpp"
#include "figure.hpp"
#include "utils.hpp"
#include <array>
#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/types.h>

FigurePositions parceFigurePositions(std::string str) {
    FigurePositions figurePositions = {};
    uint row = 7;
    uint col = 0;
    int index = 0;
    for (char c : str) {
        if (c == '/') {
            row--;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
            /* TODO: Проверять, что буквы из списка доступных, иначе выводить ошибку */
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
            const Figure figure = Figure(color, type);
            FigurePosition figurePosition = { figure, position };

            figurePositions[index] = figurePosition;
            index++;
            col++;
        }
    }
    return figurePositions;
}

Color parceActiveColor(std::string str) {
    if (str.length() != 1) {
        assert("ERROR: active color is not a single character");
    }
    switch (str[0]) {
        case 'w':
            return Color::White;
        case 'b':
            return Color::Black;
        default:
            std::cerr << "ERROR: unknown character " << str[0] << " for active color" << std::endl;
            assert(true);
            break;
    }
    /* FIX: Правильно ловить ошибки */
    return Color::White;
}

CastingAvailability parceCastingAvailability(std::string str) {
    CastingAvailability castingAvailability = {};
    for (char c : str) {
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
    return castingAvailability;
}

int parceEnPassantSquare(std::string str) {
    if (str == "-") {
        return -1;
    } else {
        return cellToIndex(str);
    }
}

int parceHalfmoveClock(std::string str) {
    if (str == "-") {
        return 0;
    } else {
        for (char c : str) {
            if (! std::isdigit(c)) {
                std::cerr << "ERROR: char '" << c << "' is not a digit";
                assert(true);
            }
        }
        return std::stoi(str);
    }
}

int parceFullmoveNumber(std::string str) {
    if (str == "-") {
        return 0;
    } else {
        for (char c : str) {
            if (! std::isdigit(c)) {
                std::cerr << "ERROR: char '" << c << "' is not a digit";
                assert(true);
            }
        }
        return std::stoi(str);
    }
}

GameState parceFENNotaion(std::string str) {
    std::array<std::string, 6> fenParts;
    std::stringstream ss(str);
    std::string part;
    int arrIndex = 0;
    while (std::getline(ss, part, ' ')) {
        fenParts[arrIndex] = part;
        arrIndex++;
    }

    GameState gs;
    gs.figurePositions = parceFigurePositions(fenParts[0]);
    gs.activeColor = parceActiveColor(fenParts[1]);
    gs.castingAvailability = parceCastingAvailability(fenParts[2]);
    gs.enPassantSquare = parceEnPassantSquare(fenParts[3]);
    gs.halfmoveClock = parceHalfmoveClock(fenParts[4]);
    gs.fullmoveNumber = parceFullmoveNumber(fenParts[5]);
    return gs;
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

std::ostream& operator<<(std::ostream& os, GameState& gs) {
    os << "Figure positions:";
    for(auto fp : gs.figurePositions) {
        os << "\n\t" << fp;       
    }
    os << "\nActive color: " << gs.activeColor
        << "\nCasting availability: " << gs.castingAvailability
        << "\nEn passant square: " << gs.enPassantSquare
        << "\nHalfmove Clock: " << gs.halfmoveClock
        << "\nFullmove number: " << gs.fullmoveNumber
        << std::endl;
    return os;
}
