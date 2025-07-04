#include <string>
#include "figure.hpp"
#include "board.hpp"


ChessBoard::ChessBoard() {
    loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
}

ChessBoard::ChessBoard(const std::string& fen) {
    loadFEN(fen);
}

const Figure& ChessBoard::get(int row, int col) const {
    return board[row * 8 + col];
}

void ChessBoard::loadFEN(const std::string& fen) {
    board.fill(Figure());
    int row = 7;
    int col = 0;

    for (char c : fen) {
        if (c == ' ') break;

        if (c == '/') {
            row--;
            col = 0;
        } else if (isdigit(c)) {
            col += c - '0';
        } else {
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

            board[row * 8 + col] = Figure{color, type};
            col++;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const ChessBoard& b) {
    for (int i = 7; i >= 0; --i) {
        std::string index = std::to_string(i + 1) + " ";
        os << index;
        for (int j = 0; j < 8; ++j) {
            os << b.get(i, j) << " ";
        }
        os << "\n";
    }
    os << "  a b c d e f g h\n";
    return os;
}
