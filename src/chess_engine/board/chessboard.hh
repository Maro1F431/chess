#pragma once

#include <vector>
#include <stack>
#include "move.hh"
#include "color.hh"
#include "chessboard-representation.hh"

namespace board
{
    class Chessboard
    {
    private:
        std::vector<Move> legalMoves;
        Chessboard_rpr boardRpr;
        bool white_turn_;
        bool white_king_rook_moved;
        bool white_queen_rook_moved;
        bool black_king_rook_moved;
        bool black_queen_rook_moved;
        bool king_moved;
        std::stack<BitBoard> en_passant_;
        unsigned int turn_;
        unsigned int last_fifty_turn_;

    public:
        Chessboard();
        std::vector<Move> generate_legal_moves();
        void do_move(Move &move);
        void undo_move(Move move);
        bool is_move_legal(Move move);
        bool is_check();
        bool is_checkmate();
        bool is_draw();
        std::optional<std::pair<PieceType, Color>> operator[](const Position &position) const;
        Chessboard_rpr &getBoardRpr();

        std::stack<BitBoard> & getEnPassant();

        Position king_position();
        bool isWhiteTurn() const;
        void setWhiteTurn(bool whiteTurn);
        bool isWhiteKingCastling() const;
        void setWhiteKingCastling(bool whiteKingCastling);
        bool isWhiteQueenCastling() const;
        void setWhiteQueenCastling(bool whiteQueenCastling);
        bool isBlackKingCastling() const;
        void setBlackKingCastling(bool blackKingCastling);
        bool isBlackQueenCastling() const;
        void setBlackQueenCastling(bool blackQueenCastling);

        Chessboard(std::string str);

        bool is_sq_attacked_by_color(int sq, Color color);

        void do_castling(Move &move);

        void update_castling(Move &move, Color color);

        void undo_castling(Move &move);
    };
}