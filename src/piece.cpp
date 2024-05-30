#include "piece.hpp"
#include "constants.hpp"

namespace chess
{  

Piece::Piece(const int &type, const int &color){
    this->piece = type | color;
}

Piece::Piece()
{
    this->piece = 0;
}

Piece::Piece(const int &piece)
{
    this->piece = piece;
}

Piece::~Piece()
{
}

bool Piece::isPiece(int piece)
{
    return this->piece == piece;
}

bool Piece::isEmpty()
{
    return !piece;
}

int Piece::getCode()
{
    return this->piece;
}

bool Piece::isColor(const int &color)
{
    return (piece & colorMask) == color;
}

int Piece::getColor()
{
    return (piece & colorMask);
}

bool Piece::isType(const int &type)
{
    return (piece & typeMask) == type;
}

int Piece::getType()
{
    return (piece & typeMask);
}

}