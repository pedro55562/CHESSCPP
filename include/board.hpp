#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <list> 

#include "piece.hpp"
#include "move.hpp"
#include "castle.hpp"

namespace chess
{ 



class Board
{
    private:
        std::vector<Piece> board;

        // if the move was made
        bool movemade;

        // list of pieces positions - you shoud use vector (32 elements)
        std::list<int> pieces;
        std::list<int> white_pieces;
        std::list<int> black_pieces;

        // keep track of legal moves
        std::list<Move> legalMoves;
        std::list<Move> move_LogBook;
        //king square
        int whiteking;
        int blacking;

        // castlings rights
        Castle castle;
        std::list<Castle> castle_LogBook;

        // is white to move
        bool iswhitetomove;

        // enpassant target square
        // if it's not avaliable enpassantSquare = -1
        int enpassantSquare;

    public:

        bool isSquareUnderAttack(const int square);

        void printSquaresUnderAttack();

        Board();

        ~Board();

        void printBoard();

        void SetFen(const std::string& fen);

        int getBoardPosition(const std::string& s);

        std::list<Move> pseudoMoveGenerator();

        Piece getPiece(const int& square){
            return this->board[square];
        }

        std::list<int> getPossibleDestinations(int square);

        void getLegalMoves();

        void movePiece(int start, int target);

        void makeMove(Move m);

        bool returnMoveMade();

        void setMoveMade();

        std::list<int> getWhitePiecesSquares();

        std::list<int> getBlackPiecesSquares();

        void updateCastlerights();
};

}


std::vector<std::string> split(const std::string& s, char delimiter);
bool containsChar(const std::string& str, char target);
#endif