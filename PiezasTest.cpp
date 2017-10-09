/**
 * Unit Tests for Piezas
 * Author: Caleb Boatsman
**/

#include <gtest/gtest.h>
#include "Piezas.h"
#include <vector> 

using std::vector;

class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

/**
 * @test      newBoardIsBlank
 * @requires  pieceAt() function to be working at a basic level
 * 
 * @desc      Initially assumes board is blank. Traverses board and returns
 *            each piece using the pieceAt() function. Tests that a new board
 *            is constructed properly. Additionally tests that pieceAt() is
 *            properly returning Blank when no tile is present.
 * 
 *            PASS: ALL pieces returned equal Blank
 *            FAIL: At least one piece returned is NOT equal to Blank
 * 
**/

TEST(PiezasTest, newBoardIsBlank)
{
	Piezas game;
	Piece piece;
	bool boardIsBlank = true; // assume board is blank

	for ( int row = 0; row < BOARD_ROWS; row++ ) {
		for ( int col = 0; col < BOARD_COLS; col++ ) {
			piece = game.pieceAt(row,col); // grab current piece
			// setup EXPECT_EQ to see what piece may be if it's not blank
			if ( piece != Blank ) {
			 EXPECT_EQ(piece, Blank); // helpful message to see what piece is
			 boardIsBlank = false;
				break; // no point in continuing
			}
		}
	}
	ASSERT_TRUE(boardIsBlank); // test is success if new board is blank
}


/**
 * @test      pieceAtOutOfBounds
 * @requires  Piezas() constructor
 * 
 * @desc      Tests pieceAt(int,int) by attempting to access a location that
 *            is out of bounds from the game board which is defined to be
 *            3x4 (3 rows, 4 columns) in size.
 * 
 *            PASS: Invalid is returned
 *            FAIL: Invalid is NOT returned
 * 
**/

TEST(PiezasTest, pieceAtOutOfBounds)
{
 Piezas game;
 Piece piece = Blank; // set piece initially to Blank
 piece = game.pieceAt(5,5);
 EXPECT_EQ(piece,Invalid);
 piece = game.pieceAt(-1,-1);
 EXPECT_EQ(piece,Invalid);
 piece = game.pieceAt(4,2);
 EXPECT_EQ(piece,Invalid);
}

/**
 * @test      dropPieceTest
 * @requires  pieceAt() functionality
 * 
 * @desc      Tests dropPiece by dropping a single piece and testing it with
 *            retrieving the new value from the board. If the piece dropped
 *            equals the piece found, test is success.
 * 
 *            PASS: Piece dropped will allocate to the board correctly
 *            FAIL: It won't return the correct piece or modify the board
 * 
**/

TEST(PiezasTest, dropPieceTest)
{
 Piezas game;
 Piece pieceDropped, pieceFound;
 pieceDropped = game.dropPiece(0);
 pieceFound = game.pieceAt(0,0); // its the first drop so it should be @ 0,0
 EXPECT_EQ(pieceDropped,X);
 EXPECT_EQ(pieceFound,X);
}

/**
 * @test      dropPieceSequenceXOXO
 * @requires  pieceAt() functionality
 * 
 * @desc      Tests dropPiece by attempting to drop an XOXO sequence into the
 *            same column. Result should be a full column, with O losing a turn
 *            and X successfully taking next turn in a free column
 * 
 *            PASS: Column will be full, and X will play in a free column
 *            FAIL: It won't return the correct piece
 * 
**/

TEST(PiezasTest, dropPieceSequenceXOXO)
{
 Piezas game;
 Piece pieceDropped;
 game.dropPiece(0);
 game.dropPiece(0);
 pieceDropped = game.dropPiece(0); // X's move
 EXPECT_EQ(pieceDropped,X);
 pieceDropped = game.dropPiece(0); // O's move
 EXPECT_EQ(pieceDropped,Blank); // return Blank because column is full
 pieceDropped = game.dropPiece(1); // X's move, drop into another column
 EXPECT_EQ(pieceDropped,X); // because O attempted to drop into a full column,
                            // and lost turn, this should return X
 
}

/**
 * @test      reset() function
 * @requires  dropPiece() functionality
 * 
 * @desc      Tests the reset() function to ensure that our board can properly
 *            reset to blank spaces.
 * 
 *            PASS: Board will return blank
 *            FAIL: Board will contain pieces dropped during test
 * 
**/

TEST(PiezasTest, resetBoard)
{
 Piezas game;
 Piece piece;
 
 game.dropPiece(0);
 game.dropPiece(0);
 game.dropPiece(1);
 game.dropPiece(2);
 game.dropPiece(3);
 game.dropPiece(2);
 
 bool boardIsBlank = true; // assume board is blank

 game.reset(); // call reset function
 
 // test for blank board
	for ( int row = 0; row < BOARD_ROWS; row++ ) {
		for ( int col = 0; col < BOARD_COLS; col++ ) {
			piece = game.pieceAt(row,col); // grab current piece
			// setup EXPECT_EQ to see what piece may be if it's not blank
			if ( piece != Blank ) {
			 EXPECT_EQ(piece, Blank); // helpful message to see what piece is
			 boardIsBlank = false;
				break; // no point in continuing
			}
		}
	}
	ASSERT_TRUE(boardIsBlank); // test is success if new board is blank
}