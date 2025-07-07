#include <ostream>
#include "figure.hpp"

std::ostream& operator<<(std::ostream& os, const Figure& f) {
    char c;
    switch (f.type) {
        case FigureType::Pawn:   c = 'P'; break;
        case FigureType::Knight: c = 'N'; break;
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

std::ostream& operator<<(std::ostream& os, FigurePosition &fp) {
    os << "Figure " << fp.figure << " Position " << fp.position;
    return os;
}

std::ostream& operator<<(std::ostream& os, Color c) {
    switch (c) {
        case Color::Black: os << "Black"; break;
        case Color::White: os << "White"; break;
        case Color::Empty: os << "Empty"; break;
    }
    return os;
}
