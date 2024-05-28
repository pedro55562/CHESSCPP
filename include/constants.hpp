#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <map>
#include <string>

namespace chess
{ 

inline const int EMPTY = 0; 
inline const int KING = 1; 
inline const int QUEEN = 2;  
inline const int ROOK = 3;   
inline const int BISHOP = 4; 
inline const int KNIGHT = 5; 
inline const int PAWN = 6;   

inline const int WHITEn = 8; 
inline const int BLACKn = 16; 

inline const int typeMask = 0b00111;

inline const int blackMask = 0b10000;
inline const int whiteMask = 0b01000;

inline const int colorMask = whiteMask | blackMask;

}

#endif