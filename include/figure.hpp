#pragma once

#include <ostream>

enum class FigureType {
    Empty,
    Pawn,
    Knight,
    Bishop,
    Rook,
    Queen,
    King
};

enum class Color {
    Black,
    White
};


class Figure {
    public:
        Color color;
        FigureType type;
        Figure(Color c, FigureType t);
        Figure();
};

std::ostream& operator<<(std::ostream& os, const Figure& f);
