#include <iostream>
#include <iterator>
#include <string>
#include <sys/types.h>
#include "figure.hpp"
#include "utils.hpp"
#include "board.hpp"

ChessBoard::ChessBoard(GameState gs) {
    game_state = gs; 
    for (auto fp : gs.figurePositions) {
        board_state[fp.position] = fp.figure;
    }
}

std::vector<Move> ChessBoard::get_posible_moves() {
    std::vector<Move> moves;
    for (uint i = 0; i < std::size(board_state); i++) {
        uint row = i / 8 + 1;
        uint col = i - row / 8 + 1;
        Figure figure = board_state[i];

        // TODO: Добавить взятие на проходе
        // Основная проблема это узнать был ли прошлый ход вражеской пешки
        // на 2 поля, а не на одно. Нужно будет искать в истории ходов.
        //
        // TODO: Добавить проверку, что полученный индекс в пределах поля.
        if (figure.type == FigureType::Pawn) {
            if (figure.color == Color::White) {
                if (board_state[i + 8].type == FigureType::Empty) {
                    moves.push_back(Move{i, i + 8});
                }
                if (row == 2 && board_state[i + 8 * 2].type == FigureType::Empty) {
                    moves.push_back(Move{i, i + 8 * 2});
                }
                if (board_state[i+7].color == Color::Black) {
                    moves.push_back(Move{i, i + 7});
                }
                if (board_state[i+9].color == Color::Black) {
                    moves.push_back(Move{i, i + 9});
                }
            } else if (figure.color == Color::Black) {
                if (board_state[i - 8].type == FigureType::Empty) {
                    moves.push_back(Move{i, i - 8});
                }
                if (row == 2 && board_state[i - 8 * 2].type == FigureType::Empty) {
                    moves.push_back(Move{i, i - 8 * 2});
                }
                if (board_state[i - 7].color == Color::Black) {
                    moves.push_back(Move{i, i - 7});
                }
                if (board_state[i - 9].color == Color::Black) {
                    moves.push_back(Move{i, i - 9});
                }
            }
        }

    }
    return moves;
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

std::ostream& operator<<(std::ostream& os, const Move& move) {
    os << index_to_cell(move.from) << "->" << index_to_cell(move.to);
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Move>& moves) {
    for (Move move : moves) {
        os << move << ", ";
    }
    return os;
}
