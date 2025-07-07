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
    White,
    Empty
};

class Figure {
    public:
        Color color;
        FigureType type;
        Figure() : color(Color::Empty), type(FigureType::Empty) {}
        Figure(Color c, FigureType t) : color(c), type(t) {}
};

struct FigurePosition {
    Figure figure;
    uint   position;
};

std::ostream& operator<<(std::ostream& os, const Figure& f);
std::ostream& operator<<(std::ostream& os, FigurePosition &fp);
std::ostream& operator<<(std::ostream& os, Color c);
