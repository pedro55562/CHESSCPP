#ifndef PIECE_HPP
#define PIECE_HPP

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

        bool isEmpty();

        int getCode();

        bool isColor(const int& color);

        int getColor();

        bool isType(const int& type);

        int getType();

};


}

#endif