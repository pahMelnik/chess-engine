#include "board.hpp"
#include "figure.hpp"
#include "utils.hpp"
#include <iostream>
#include <cstdlib>

ChessBoard::ChessBoard(GameState gs) {
  game_state = gs;
  for (auto fp : gs.figurePositions) {
    board_state[fp.position] = fp.figure;
  }
}

void ChessBoard::print_empty_board() {
  for (int row = 8; row > 0; row--) {
      std::cout << "--+--+--+--+--+--+--+--+--+" << std::endl;
    for (int col = 1; col <= 8; col++) {
      if (col == 1) {
          std::cout << " " << std::to_string(row) << "|";
      };
      int index = row * 8 - 8 + col - 1;
      if (index < 10) {
          std::cout << "0";
      }
      std::cout << std::to_string(index) << "|";
    }
    std::cout << std::endl;
  }
  std::cout << "--+--+--+--+--+--+--+--+--+" << std::endl;
  std::cout << "  |A |B |C |D |E |F |G |H |" << std::endl;
}

// FIX: Infinite loop
std::vector<Move> ChessBoard::get_pseudo_legal_moves() {
    std::cout << "INFO: generate pseudo legal moves" << std::endl;
    std::vector<Move> moves;
  // FIX: Infinite loop at index 0
  for (uint i = 0; i < 64; i++) {
    int row = i / 8 + 1;
    int col = i - (row - 1) * 8  + 1;
    Figure figure = board_state[i];
    std::cout << "INFO: process board index " << i << " row " << row << " col " << col << " figure " << figure << std::endl;

    // TODO: Добавить взятие на проходе
    // Основная проблема это узнать был ли прошлый ход вражеской пешки
    // на 2 поля, а не на одно. Нужно будет искать в истории ходов.

    // TODO: Добавить проверку, что полученный индекс в пределах поля.
    switch (figure.type) {
    case FigureType::Pawn:
      switch (figure.color) {
      case Color::White:
        // вверх 1 клетка
        if (board_state[i + 8].type == FigureType::Empty) {
          moves.push_back(Move{i, i + 8});
        }

        // вверх 2 клетки
        if (row == 2 && board_state[i + 8 * 2].type == FigureType::Empty) {
          moves.push_back(Move{i, i + 8 * 2});
        }

        // вверх-влево 1 клетка
        if (board_state[i + 7].color == Color::Black) {
          moves.push_back(Move{i, i + 7});
        }

        // вверх-вправо 1 клетка
        if (board_state[i + 9].color == Color::Black) {
          moves.push_back(Move{i, i + 9});
        }
        break;
      case Color::Black:
        // вниз 1 клетка
        if (board_state[i - 8].type == FigureType::Empty) {
          moves.push_back(Move{i, i - 8});
        }

        // вниз 2 клетки
        if (row == 7 && board_state[i - 8 * 2].type == FigureType::Empty) {
          moves.push_back(Move{i, i - 8 * 2});
        }

        // вниз-вправо 1 клетка
        if (board_state[i - 7].color == Color::White) {
          moves.push_back(Move{i, i - 7});
        }

        // вниз-влево 1 клетка
        if (board_state[i - 9].color == Color::White) {
          moves.push_back(Move{i, i - 9});
        }
        break;
      case Color::Empty:
        break;
      }

    case FigureType::Bishop:
      for (int modifier : {7, 9, -7, -9}) {
        for (int i_new = i + modifier; 0 >= i && i < 64; i += modifier) {
          if (board_state[i_new].color == Color::Empty) {
            moves.push_back(Move{i, uint(i_new)});
          } else if (board_state[i_new].color == figure.color) {
            break;
          } else if (board_state[i_new].color != figure.color) {
            moves.push_back(Move{i, uint(i_new)});
            break;
          }
        }
      }
      break;

    case FigureType::Rook:
      for (int modifier : {-1, 8, 1, -8}) {
          std::cout << "INFO: modifier " << modifier << std::endl;
        for (int i_new = i + modifier; 0 >= i_new && i_new < 64; i += modifier) {
            std::cout << "INFO: new index " << i_new << std::endl;
          if (i_new < 0 || i_new >= 64) {
              std::cout << "INFO: out of range" << std::endl;
            break;
          }
          if (board_state[i_new].color == Color::Empty) {
              std::cout << "INFO: no figure at index " << i_new << std::endl;
            moves.push_back(Move{i, uint(i_new)});
          } else if (board_state[i_new].color == figure.color) {
              std::cout << "INFO: figure at index " << i_new << " has same color" << std::endl;
            break;
          } else if (board_state[i_new].color != figure.color) {
              std::cout << "INFO: figure at index " << i_new << " has oposite color" << std::endl;
            moves.push_back(Move{i, uint(i_new)});
            break;
          }
        }
      }
      break;

    case FigureType::Queen:
      for (int modifier : {-1, 8, 1, -8, 7, 9, -7, -9}) {
        for (int i_new = i + modifier; 0 >= i && i < 64; i += modifier) {
          if (i_new < 0 || i_new >= 64) {
            continue;
          }
          if (board_state[i].color == Color::Empty) {
            moves.push_back(Move{i, uint(i_new)});
          } else if (board_state[i_new].color == figure.color) {
            break;
          } else if (board_state[i_new].color != figure.color) {
            moves.push_back(Move{i, uint(i_new)});
            break;
          }
        }
      }
      break;

    case FigureType::Knight:
      for (int modifier : {15, 17, 10, -6, -15, -17, -10, 6}) {
        int i_new = i + modifier;
        int row_new = i_new / 8 + 1;
        int col_new = i_new - (row_new - 1) * 8 + 1;
        int col_diff = std::abs(col - col_new);
        std::cout << "INFO: new i " << i_new << " row_new " << row_new << " col_new " << col_new << " col_diff " << col_diff << std::endl;
        if (i_new < 0 || i_new >= 64) {
            std::cout << "INFO: out of range" << std::endl;
          continue;
        }
        if (col_diff > 2) {
            std::cout << "INFO: wrong column" << std::endl;
          continue;
        }
        if (board_state[i_new].color == Color::Empty) {
          moves.push_back(Move{i, uint(i_new)});
        } else if (board_state[i_new].color != figure.color) {
          moves.push_back(Move{i, uint(i_new)});
        }
      }
      break;

    // TODO: Добавить рокировку
    case FigureType::King:
      for (int modifier : {7, 8, 9, 1, -7, -8, -9, -1}) {
        int i_new = i + modifier;
        if (i_new < 0 || i_new >= 64) {
          continue;
        }
        if (board_state[i_new].color == Color::Empty) {
          moves.push_back(Move{i, uint(i_new)});
        } else if (board_state[i_new].color != figure.color) {
          moves.push_back(Move{i, uint(i_new)});
        }
      }
      break;

    case FigureType::Empty:
      break;
    }
  }
  return moves;
}

std::ostream &operator<<(std::ostream &os, const ChessBoard &b) {
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

std::ostream &operator<<(std::ostream &os, const Move &move) {
  os << index_to_cell(move.from) << "->" << index_to_cell(move.to);
  return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<Move> &moves) {
  for (Move move : moves) {
    os << move << ", ";
  }
  return os;
}
