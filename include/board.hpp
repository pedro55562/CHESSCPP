#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <map>
#include <string>
#include <list> 

#include "piece.hpp"
#include "move.hpp"

namespace chess
{ 



class Board
{
    private:
        std::vector<Piece> board;

        // list of pieces positions - you shoud use vector (32 elements)
        std::list<int> pieces;
        std::list<int> white_pieces;
        std::list<int> black_pieces;

        // keep track of pseudo-legal moves( maybe from - to)
        std::list<Move> pseudolegalMoves;

        // keep track of legal moves
        std::list<Move> legalMoves;

        //king square
        int whiteking;
        int blacking;

        // castlings rights
        bool whiteKingside;
        bool whiteQueenside;
        bool blackKingside;
        bool blackQueenside;

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

        void pseudoMoveGenerator();

        Piece getPiece(const int& square){
            return this->board[square];
        }

        std::list<int> getPossibleDestinations(int square){ 
            std::list<int> temp;
            for( Move m : pseudolegalMoves){
                if (m.getStart() == square){
                    temp.push_back(m.getTarget());
                }
            }
            return temp;
        }

        void getLegalMoves();

        void movePiece(int start, int target);

        void makeMove(Move m);
};

}


std::vector<std::string> split(const std::string& s, char delimiter);
bool containsChar(const std::string& str, char target);
#endif