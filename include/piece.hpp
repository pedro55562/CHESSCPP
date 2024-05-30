#ifndef PIECE_HPP
#define PIECE_HPP


/*
    Piece encoding:

    type:   0000 0111
    color:  0001 1000

    Pieces:
        EMPTY:  0000 0000
        KING:   0000 0001
        QUEEN:  0000 0010
        ROOK:   0000 0011
        BISHOP: 0000 0100
        KNIGHT: 0000 0101
        PAWN:   0000 0110
        
    Colors:
        WHITE:  0000 1000
        BLACK:  0001 0000
*/
namespace chess
{
    
class Piece{

    private:
        int piece;


    public:
        Piece(const int& type, const int& color);

        Piece();

        Piece(const int& piece);

        ~Piece();

        bool isPiece(int piece);

        bool isEmpty();

        int getCode();

        bool isColor(const int& color);

        int getColor();

        bool isType(const int& type);

        int getType();

};


}

#endif