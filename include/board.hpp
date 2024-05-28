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

        // keep track of pseudo-legal moves( maybe from - to)
        std::list<Move> pseudolegalMoves;

        // keep track of legal moves
        std::list<Move> legalMoves;

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

        bool isSquareUnderAttack(const int square, const bool iswhiteside);

        void printSquaresUnderAttack(const bool iswhiteside);

        Board();

        ~Board();

        void printBoard();

        void SetFen(const std::string& fen);

        int getBoardPosition(const std::string& s);

        Piece getPiece(const int& square);
        
        void getPseudoLegalMoves();

        std::list<int> getPossibleDestinations(int square){
            std::list<int> lista;
            for (int i = 0; i < 128; i++){
                lista.push_back(i);
            }
            
            
            return lista;
        }
};

}


std::vector<std::string> split(const std::string& s, char delimiter);
bool containsChar(const std::string& str, char target);
#endif