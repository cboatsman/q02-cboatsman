#include "Piezas.h"
#include <vector>

using std::vector;
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
	turn = X; // set first turn to piece X
 // populate vectors with Blank pieces
	for ( int row = 0; row < BOARD_ROWS; row++) {
	 vector<Piece> * row_vector = new vector<Piece>;
		for ( int col = 0; col < BOARD_COLS; col++ ) {
			 row_vector->push_back(Blank);
		}
		board.push_back(*row_vector);
		delete row_vector;
	}
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
 turn = X; // reset the turn back to X

	for ( int row = 0; row < BOARD_ROWS; row++) {
	 board.erase(board.begin(),board.end());
	}
	
	 // populate vectors with Blank pieces
	for ( int row = 0; row < BOARD_ROWS; row++) {
	 vector<Piece> * row_vector = new vector<Piece>;
		for ( int col = 0; col < BOARD_COLS; col++ ) {
			 row_vector->push_back(Blank);
		}
		board.push_back(*row_vector);
		delete row_vector;
	}
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
 
 Piece * currentTurn = new Piece;
 
 *currentTurn = turn; // save the current turn value
 
 // Toggle the Turn
 // NOTE: It appears that, regardless, this function will toggle the turn
 //       whether a play was successful, invalid due to out of bounds, or
 //       invalid due to full column. So, let's take care of that first.
 
 if(turn == X) {
  turn = O;
 }
 else {
  turn = X;
 }
 
 // location is within bounds
 if(column >= 0 && column < BOARD_COLS) {
  
  for(int row = 0; row < BOARD_ROWS; row++) {
   
   Piece piece = pieceAt(row,column);
   
   if(piece == Blank) {
    // there is a location in this column available
    board.at(row).at(column) = *currentTurn;
    return *currentTurn; // piece drop was success
   }
   
  }
  
  return Blank; // column is full
 }
 
 return Invalid; // out of bounds
 
 delete currentTurn;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
 // location is within bounds
 if(
      (row >= 0 && row < BOARD_ROWS)
   && (column >= 0 && column < BOARD_COLS)
   ) {
    
  Piece pieceFound;
  pieceFound = board.at(row).at(column);

  if(pieceFound == Blank) {
   return Blank; // location is blank
  }
  
  return pieceFound; // location occupied
 }
 
 return Invalid; // location is out of bounds
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
 
 Piece current, previous;
 int highestX, highestO;
 
 // traverse the board for Blank spaces
 for (int i=0; i<BOARD_ROWS; i++) {
  for (int j=0; j<BOARD_COLS; j++) {
   current = pieceAt(i,j);
   if(current == Blank)
    return Invalid;
  }
 }
 
 // first check col-by-col for X's and O's
 for(int col=0; col<BOARD_COLS; col++) {
  
  previous = Blank;
  int xCount = 0, oCount = 0;
  
  for(int row=0; row<BOARD_ROWS; row++) {
   
   current = pieceAt(row,col);
   
   if(previous != Blank) {
     //this isn't the first run of the column
     if( current == X && previous == X )
      xCount++;
     
     if( current == O && previous == O )
      oCount++;
   }
   
   if ( xCount > highestX )
    highestX = xCount;
    
   if ( oCount > highestO )
    highestO = oCount;
   
   previous = current;
  }
  xCount = 0;
  oCount = 0;
 }

 // then check row-by-row for X's and O's
 for(int row=0; row<BOARD_ROWS; row++) {
  
  previous = Blank;
  int xCount = 0, oCount = 0;
  
  for(int col=0; col<BOARD_COLS; col++) {
   
   current = pieceAt(row,col);
   
   if(previous != Blank) {
     //this isn't the first run of the row
     if( current == X && previous == X )
      xCount++;
     
     if( current == O && previous == O )
      oCount++;
   }
   
   if ( xCount > highestX )
    highestX = xCount;
    
   if ( oCount > highestO )
    highestO = oCount;
   
   previous = current;

  }
  xCount = 0;
  oCount = 0;
 }
 
 if(highestX == highestO) // tie
  return Blank;
  
 if(highestX > highestO)
  return X;
 else
  return O;
}