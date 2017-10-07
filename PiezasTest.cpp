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

// Board constructor test
// Result should be a 3x4 board of Blank pieces
// REQUIRES: pieceAt() function
TEST(PiezasTest, newBoardIsBlank)
{
	Piezas game; // create a new game
	Piece piece; // create a new piece
	
	bool boardIsBlank = true; // assume board is blank

	for ( int row = 0; row < BOARD_ROWS; row++ ) {
		for ( int col = 0; col < BOARD_COLS; col++ ) {
			piece = game.pieceAt(row,col); // grab current piece
			if ( piece != Blank ) {
			 EXPECT_TRUE(piece == Blank);
			 boardIsBlank = false;
				break;
			}	
		}
	}

	EXPECT_TRUE(boardIsBlank); // test is success if new board is blank
}
