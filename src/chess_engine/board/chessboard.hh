#pragma once

#include <stack>
#include <vector>

#include "../../parsing/perft-parser/fen-object.hh"
#include "chessboard-representation.hh"
#include "color.hh"
#include "move.hh"

namespace board
{
    class Chessboard
    {
    private:
        Chessboard_rpr boardRpr;
        bool white_turn_;
        std::stack<BitBoard> en_passant_;
        unsigned int turn_;
        unsigned int last_fifty_turn_;

    public:
        int white_king_rook_moved;
        int white_queen_rook_moved;
        int black_king_rook_moved;
        int black_queen_rook_moved;
        int white_king_moved;
        int black_king_moved;
        Chessboard();
        explicit Chessboard(perft_parser::FenObject fenObject);
        std::vector<Move> generate_legal_moves();
        void do_move(Move move);
        void undo_move(Move move);
        bool is_move_legal(Move move);
        bool is_check();
        bool is_checkmate();
        bool is_pat();
        bool is_draw();
        std::optional<std::pair<PieceType, Color>>
        operator[](const Position& position) const;
        Chessboard_rpr& getBoardRpr();

        std::stack<BitBoard>& getEnPassant();

        std::optional<Position> king_position();
        bool isWhiteTurn() const;
        void setWhiteTurn(bool whiteTurn);

        bool is_sq_attacked_by_color(int sq, Color color);

        void do_castling(Move& move);

        void undo_castling(Move& move);

        void undo_update_castling();

        void update_castling(Move& move);

        void generate_castling(std::vector<Move>& moves);

        void getMatchingLegalMoveAndDo(Move move);

        bool is_checkmate(const std::vector<Move>& moves);

        void print();

        bool is_pat(const std::vector<Move>& moves);
    };
} // namespace board