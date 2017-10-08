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