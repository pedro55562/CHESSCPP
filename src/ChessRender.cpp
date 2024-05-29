#include "ChessRenderer.hpp"

#include <list>
#include <raylib.h>
#include <iostream>
#include <board.hpp>

using std::cout;
using std::list;

namespace chess{
std::map<int, int> chessToRaylib = {
    {0, 7},
    {1, 6},
    {2, 5},
    {3, 4},
    {4, 3},
    {5, 2},
    {6, 1},
    {7, 0}
};

std::map<int, int> RaylibToChess = {
    {0, 7},
    {1, 6},
    {2, 5},
    {3, 4},
    {4, 3},
    {5, 2},
    {6, 1},
    {7, 0}
};



// Construtor da classe ChessRenderer
ChessRenderer::ChessRenderer(Board& chessboard) : board(chessboard)
{
  // Inicializa a posição da peça selecionada como (0,0) e indica que nenhuma peça está selecionada
  SelectedPiece = -1;
  isPieceSelected = false;

  // Inicializa a janela com o tamanho especificado, título "Chess" e uma taxa de atualização de 30 quadros por segundo
  InitWindow(pixels, pixels, "Chess");
  shouldclose_ = false; // Inicializa shouldclose_ como falso
  SetTargetFPS(30);

  // Carrega as texturas das peças a partir dos arquivos de imagem
  BISHOP_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/BISHOP_BLACK.png"));
  KING_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/KING_BLACK.png"));
  QUEEN_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/QUEEN_BLACK.png"));
  ROOK_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/ROOK_BLACK.png"));
  KNIGHT_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/KNIGHT_BLACK.png"));
  PAWN_BLACK = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/PAWN_BLACK.png"));

  BISHOP_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/BISHOP_WHITE.png"));
  KING_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/KING_WHITE.png"));
  QUEEN_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/QUEEN_WHITE.png"));
  ROOK_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/ROOK_WHITE.png"));
  KNIGHT_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/KNIGHT_WHITE.png"));
  PAWN_WHITE = LoadTextureFromImage(LoadImage("./assets/images/chess_pieces/PAWN_WHITE.png"));
}


// Renderiza o quadrado do tabuleiro na posição (row, col) com a cor apropriada (claro ou escuro).
void ChessRenderer::renderBoard(const int& row, const int& col) const
{
  // Verifica se a soma de linha e coluna é par ou ímpar para determinar a cor do quadrado
  bool isLight = (row + col) % 2 == 0;

  // Se for um quadrado claro, desenha um retângulo com a cor "light", caso contrário, com a cor "dark"
  if (isLight)
  {
    DrawRectangle(col * squaresize, row * squaresize, squaresize, squaresize, light);
  }
  else
  {
    DrawRectangle(col * squaresize, row * squaresize, squaresize, squaresize, dark);
  }
}


// Renderiza uma peça na posição especificada com a textura fornecida.
void ChessRenderer::renderPiece(const Texture2D& pieceTexture, const int& col, const int& row) const
{
  Vector2 temp;
  temp.x = col * squaresize; // Calcula a coordenada x na tela com base na coluna
  temp.y = row * squaresize; // Calcula a coordenada y na tela com base na linha

  // Desenha a textura da peça na posição (x, y) com uma rotação de 0 graus, escala de 0.125 e cor branca
  DrawTextureEx(pieceTexture, temp, 0, 0.125, WHITE);
}

// Renderiza visualmente as posições possíveis para mover uma peça a partir de uma posição específica no tabuleiro de xadrez.
void ChessRenderer::renderPossibleDestinations(const int &from) const
{
    list<int> lista_ = board.getPossibleDestinations(from);
    for (auto square : lista_) {
        int ranks = chessToRaylib[square >> 4];
        int files = square & 7;
        DrawRectangle(files * squaresize, ranks * squaresize, squaresize, squaresize, red_);

    }
}

// Função principal de renderização do jogo
void ChessRenderer::render()
{
  BeginDrawing(); 
  // Atualiza shouldclose com base na condição de fechamento da janela
  shouldclose_ = WindowShouldClose();

  // Renderiza o fundo do tabuleiro
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      renderBoard(row, col); // Chama a função para renderizar as posições possíveis para a peça selecionada
    }
  }

  // Destaca as posições possíveis se uma peça estiver selecionada
  for (int row = 0; row < size; row++)
  {
    for (int col = 0; col < size; col++)
    {
      if ( isPieceSelected){
        renderPossibleDestinations(SelectedPiece);
      }    
    }
  }

  // Renderiza as peças no tabuleiro
  for (int square = 0; square < 128; square++)
  { 
      int row = chessToRaylib[square >> 4];
      int col = square & 7;


      // Verifica o tipo e a cor da peça e renderiza a textura correspondente
      switch (board.getPiece(square).getCode())
      {
      case KING | BLACKn:
        renderPiece(KING_BLACK, col, row);
        break;
      case KING | WHITEn:
        renderPiece(KING_WHITE, col, row);
        break;
      case PAWN | BLACKn:
        renderPiece(PAWN_BLACK, col, row);
        break;
      case PAWN | WHITEn:
        renderPiece(PAWN_WHITE, col, row);
        break;
      case BISHOP | BLACKn:
        renderPiece(BISHOP_BLACK, col, row);
        break;
      case BISHOP | WHITEn:
        renderPiece(BISHOP_WHITE, col, row);
        break;
      case QUEEN | BLACKn:
        renderPiece(QUEEN_BLACK, col, row);
        break;
      case QUEEN | WHITEn:
        renderPiece(QUEEN_WHITE, col, row);
        break;
      case KNIGHT | BLACKn:
        renderPiece(KNIGHT_BLACK, col, row);
        break;
      case KNIGHT | WHITEn:
        renderPiece(KNIGHT_WHITE, col, row);
        break;
      case ROOK | BLACKn:
        renderPiece(ROOK_BLACK, col, row);
        break;
      case ROOK | WHITEn:
        renderPiece(ROOK_WHITE, col, row);
        break;
    }
  }
  EndDrawing();
}


// Verifica se a janela do jogo deve ser fechada
bool ChessRenderer::shouldClose() const
{
  return shouldclose_;
}


// Lida com a entrada do mouse para obter a posição de clique
int ChessRenderer::handleMouseInput()
{
  int aux = 0;
  bool click = false;

  // Loop até que ocorra um clique ou a janela seja fechada
  while (click != true)
  {
    if (shouldClose() == true)
    {
      break;
    }
    render(); // Renderiza o jogo enquanto espera pelo click do jogador

    // Verifica se o botão esquerdo do mouse foi pressionado e se o cursor está na tela
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsCursorOnScreen())
    {
        int X_pos = GetMouseX();
        int Y_pos = GetMouseY();
        click = true;
        return RaylibToChess[Y_pos / squaresize]*16 + X_pos/squaresize;   // Retorna a posição do clique do mouse
    }
  }

  return -1; // Retorna a posição (0,0) se não houve clique
}


// Atualiza a peça selecionada e alterna o estado de isPieceSelected
void ChessRenderer::updateSelectedPiece(const int from)
{
  SelectedPiece = from; // Atualiza a posição da peça selecionada
  isPieceSelected = !isPieceSelected; // Alterna o estado de isPieceSelected (se era true, torna-se false, e vice-versa)
}


// Destrutor da classe ChessRenderer
ChessRenderer::~ChessRenderer()
{
  // Descarrega as texturas das peças e fecha a janela
  UnloadTexture(BISHOP_BLACK);
  UnloadTexture(KING_BLACK);
  UnloadTexture(QUEEN_BLACK);
  UnloadTexture(ROOK_BLACK);
  UnloadTexture(KNIGHT_BLACK);
  UnloadTexture(PAWN_BLACK);

  UnloadTexture(BISHOP_WHITE);
  UnloadTexture(KING_WHITE);
  UnloadTexture(QUEEN_WHITE);
  UnloadTexture(ROOK_WHITE);
  UnloadTexture(KNIGHT_WHITE);
  UnloadTexture(PAWN_WHITE);

  CloseWindow(); // Fecha a janela
}

}