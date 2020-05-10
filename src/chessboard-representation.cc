#include "chessboard-representation.hh"
#include "piece-type.hh"

#include <cstdlib>
#include <vector>
#include <utility>
#include <optional>
#include <iostream>
#include "color.hh"

namespace board
{
    Chessboard_rpr::Chessboard_rpr()
    {
        boards = std::vector<BitBoard>(0);
        BitBoard white_queen = 1UL << 59u;
        boards.push_back(white_queen);
        BitBoard white_rook = 1UL << 56u | 1UL << 63u;
        boards.push_back(white_rook);
        BitBoard white_bishop = 1UL << 58u | 1UL << 61u;
        boards.push_back(white_bishop);
        BitBoard white_knight = 1UL << 57u | 1UL << 62u;
        boards.push_back(white_knight);
        BitBoard white_pawn = 1UL << 48u | 1UL << 49u | 1UL << 50u | 1UL << 51u |
                     1UL << 52u | 1UL << 53u | 1UL << 54u | 1UL << 55u;
        boards.push_back(white_pawn);
        BitBoard white_king = 1UL << 60u;
        boards.push_back(white_king);

        BitBoard black_queen = 1UL << 3u;
        boards.push_back(black_queen);
        BitBoard black_rook = 1UL << 0u | 1UL << 7u;
        boards.push_back(black_rook);
        BitBoard black_bishop = 1UL << 2u | 1UL << 5u;
        boards.push_back(black_bishop);
        BitBoard black_knight = 1UL << 1u | 1UL << 6u;
        boards.push_back(black_knight);
        BitBoard black_pawn = 1UL << 8u | 1UL << 9u | 1UL << 10u | 1UL << 11u |
                     1UL << 12u | 1UL << 13u | 1UL << 14u | 1UL << 15u;
        boards.push_back(black_pawn);
        BitBoard black_king = 1UL << 4u;
        boards.push_back(black_king);
    }

    Chessboard_rpr::Chessboard_rpr(Move move)
        : Chessboard_rpr()
    {
        alter_rpr(move);
    }

    void Chessboard_rpr::print()
    {
        std::string output;

        std::vector<char> chars {'Q', 'R', 'B', 'C', 'P', 'K', 'q', 'r', 'b', 'c', 'p', 'k'};

        for (int i = 0; i < 64; i++)
        {
            auto size = output.size();
            for (int j = 0; j < 12; ++j) {
                if ((boards.at(j) >> i) & 1U)
                    output += chars.at(j);
            }
            if (size == output.size())
                output += " ";
            if ((i + 1) % 8 == 0)
                output += "\n";
        }
        std::cout << output;
    }

    void Chessboard_rpr::alter_rpr(Move move)
    {
        auto dest = move.dest_pos_get();
        auto src = move.start_pos_get();

        auto piece = this->at(src);
        auto capture = this->at(dest);

        unsigned int source_int = ((int) src.file_get()) + (abs((int) src.rank_get() - 7)) * 8;
        unsigned int dest_int = ((int) dest.file_get()) + (abs((int) dest.rank_get() - 7)) * 8;

        int board_index = ((int) piece->first) + (piece->second == Color::WHITE ? 0 : 6);

        boards.at(board_index) = (boards.at(board_index) & ~(1UL << source_int)) | 1UL << dest_int;
        if (capture.has_value())
        {
            int capture_board_index = ((int) capture->first) + (capture->second == Color::WHITE ? 0 : 6);
            boards.at(capture_board_index) &= ~(1UL << dest_int);
        }
    }

    std::optional<std::pair<PieceType, Color>> Chessboard_rpr::at(Position pos)
    {
        unsigned int pos_int = ((int) pos.file_get()) + (abs((int) pos.rank_get() - 7)) * 8;

        for (size_t i = 0; i < 12; i++)
        {
            if ((boards.at(i) >> pos_int) & 1U)
            {
                auto type = static_cast<PieceType>(i % 6);
                auto color = (i >= 6) ? Color::BLACK : Color::WHITE;
                return std::pair<PieceType, Color>(type, color);
            }
        }
        return std::nullopt;
    }
}