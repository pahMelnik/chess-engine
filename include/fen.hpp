#pragma once

#include <array>
#include <ostream>
#include <string>
#include <sys/types.h>
#include "figure.hpp"

typedef std::array<FigurePosition, 32> FigurePositions;

struct CastingAvailability {
    bool WhiteQueenSide;
    bool WhiteKingSide;
    bool BlackQueenSide;
    bool BlackKingSide;
};

struct GameState {
    FigurePositions     figurePositions;
    Color               activeColor;
    CastingAvailability castingAvailability;
    int                 enPassantSquare;
    int                 halfmoveClock;
    int                 fullmoveNumber;
};

GameState           parceFENNotaion(std::string str);
FigurePositions     parceFigurePositions(std::string str);
Color               parceActiveColor(std::string str);
CastingAvailability parceCastingAvailability(std::string str);
int                 parceEnPassantSquare(std::string str);
int                 parceHalfmoveClock(std::string str);
int                 parceFullmoveNumber(std::string str);

std::ostream& operator<<(std::ostream& os, CastingAvailability& c);
std::ostream& operator<<(std::ostream& os, GameState& gs);
