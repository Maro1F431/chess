#include "chessboard-representation.hh"
#include "option.hh"
#include "engine.hh"
#include "chessboard.hh"
#include <iostream>



    int main(int argc, char **argv) {

        using namespace board;
 /*       Chessboard_rpr board = Chessboard_rpr();
        board.print();

        Position src = Position(File::A, Rank::TWO);
        Position dst = Position(File::A, Rank::SEVEN);


        Move move =  Move(src, dst, board::PieceType::PAWN);
        board.alter_rpr(move);
        board.print();*/


        Option option;
        board::Chessboard chessboard;
        HandleListener handler(option.get_listeners());
        Engine engine(option.get_pgn(), handler);
        engine.start_game(chessboard,handler);

        if (!option.parse_options(argc,argv))
        {
            std::cout << "Options are not valid" << "\n";
        }
        if (option.get_help())
        {
            Option::show_help();
            return 0;
        }
        if (option.get_pgn().empty())
        {
            std::cerr << "PGN file invalid" << "\n";
        }
        return 0;
    }