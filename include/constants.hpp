#include <map>
#include <string>

namespace chess
{ 

const int EMPTY = 0; 
const int KING = 1; 
const int QUEEN = 2;  
const int ROOK = 3;   
const int BISHOP = 4; 
const int KNIGHT = 5; 
const int PAWN = 6;   

const int WHITEn = 8; 
const int BLACKn = 16; 

const int typeMask = 0b00111;

const int blackMask = 0b10000;
const int whiteMask = 0b01000;

const int colorMask = whiteMask | blackMask;

}