#pragma once

#include <array>
#include <ostream>
#include <string>
#include <sys/types.h>
#include "figure.hpp"

struct CastingAvailability {
    bool WhiteQueenSide;
    bool WhiteKingSide;
    bool BlackQueenSide;
    bool BlackKingSide;
};

class FenNotation {
private:
    std::array<FigurePosition, 32> figurePositions;
    Color activeColor;
    /* Возможность сделать рокировку */
    /* Указывается цвет и сторона в которую можно сделать рокировку */
    CastingAvailability castingAvailability;
    /* Индекс клетки над которой только прошла пешка. Для взятия на проходе */
    int enPassantSquare;
    /* Количество ходов с последнего взятия или хода пешки */
    /* Правило 50 ходов */
    int halfmoveClock;
    int fullmoveNumber;
public:
    FenNotation(std::string s) { parce(s); };
    void parce(std::string s);
    void parcePosition(std::string s);
    void parceActiveColor(std::string s);
    void parceCastingAvailability(std::string s);
    void parceEnPassantSquare(std::string s);
    void parceHalfmoveClock(std::string s);
    void parceFullmoveNumber(std::string s);
    std::array<FigurePosition, 32> getFigurePositions() { return figurePositions;};
    Color getActiveColor() { return activeColor; };
    /* Это структура, поэтому возращаю указатель */
    CastingAvailability& getCastingAvailability() { return castingAvailability;};
    int getEnPassantSquare() {return enPassantSquare; };
    int getHalfmoveClock() { return halfmoveClock; };
    int getFullmoveNumber() { return fullmoveNumber; };
};

std::ostream& operator<<(std::ostream& os, FenNotation fen);
std::ostream& operator<<(std::ostream& os, CastingAvailability& c);
