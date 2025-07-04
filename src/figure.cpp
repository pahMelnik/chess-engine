#include <ostream>
#include "figure.hpp"

Figure::Figure() : color(Color::Black), type( FigureType::Empty) {}
Figure::Figure(Color c, FigureType t) : color(c), type(t) {}

std::ostream& operator<<(std::ostream& os, const Figure& f) {
    char c;
    switch (f.type) {
        case FigureType::Pawn:   c = 'P'; break;
        case FigureType::Knight: c = 'K'; break;
        case FigureType::Bishop: c = 'B'; break;
        case FigureType::Rook:   c = 'R'; break;
        case FigureType::Queen:  c = 'Q'; break;
        case FigureType::King:   c = 'K'; break;
        case FigureType::Empty:  c = '.'; break;
    }
    if (f.type != FigureType::Empty && f.color == Color::Black)
        c = tolower(c);
    os << c;
    return os;
} 
