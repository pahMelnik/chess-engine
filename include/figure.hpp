#pragma once

#include <ostream>
#include <sys/types.h>

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

struct FigurePosition {
    Figure figure;
    uint position;
};

std::ostream &operator<<(std::ostream &os, FigurePosition &fp);
std::ostream &operator<<(std::ostream &os, Color c);
