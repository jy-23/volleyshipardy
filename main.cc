#include <iostream>
#include <time.h>
#include <cstdlib>
//#include "jeopardy.h"
//#include "volleyball.h"
#include "new_battleship.h"
#include <gtest/gtest.h>

using namespace std;

//Battleship_Player can't be a pointer here
Battleship_Player b;

TEST(battleship, oppAttack) {
	EXPECT_EQ(b.oppAttack('K', 5), MSG_OUT_OF_BOUNDS);
	EXPECT_EQ(b.oppAttack('J', 5), MSG_MISS);
	EXPECT_EQ(b.oppAttack(64, 5), MSG_OUT_OF_BOUNDS);
	EXPECT_EQ(b.oppAttack(65, 5), MSG_MISS);
	EXPECT_EQ(b.oppAttack(70, -1), MSG_OUT_OF_BOUNDS);
	EXPECT_EQ(b.oppAttack(70, 0), MSG_MISS);
    EXPECT_EQ(b.oppAttack(70, 10), MSG_OUT_OF_BOUNDS);
	EXPECT_EQ(b.oppAttack(70, 9), MSG_MISS);

   	//hitCount is private so you can't access it; same for myBoard[0][0]
	b.hitCount = 16;
	b.myBoard[0][0] = CRUISER;
	EXPECT_EQ(b.oppAttack('A', 0), MSG_YOU_WON);
	b.hitCount = 15;
    b.myBoard[0][0] = CRUISER;
    EXPECT_EQ(b.oppAttack('A', 0), MSG_HIT);
}

TEST(battleship, placeShip) {
	//Bounds check coordinates
	//placeShip is a private function so you can't access it
	EXPECT_EQ(b.placeShip(b.w, 'B', 1, 'Z'), false);
	EXPECT_EQ(b.placeShip(b.w, 64, 1, 'S'), false);
	EXPECT_EQ(b.placeShip(b.w, 'A', 1, 'S'), true);
	EXPECT_EQ(b.placeShip(b.w, 'K', 1, 'S'), false);
	EXPECT_EQ(b.placeShip(b.w, 'B', -1, 'S'), false);
	EXPECT_EQ(b.placeShip(b.w, 'B', 0, 'S'), true);
	EXPECT_EQ(b.placeShip(b.w, 'B', 10, 'S'), false);
	EXPECT_EQ(b.placeShip(b.w, 'B', 9, 'S'), true);
	//Bounds check ships
	EXPECT_EQ(b.placeShip(b.w, 'A', 8, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'A', 7, 'E'), true);
	EXPECT_EQ(b.placeShip(b.w, 'I', 0, 'S'), false);
	EXPECT_EQ(b.placeShip(b.w, 'H', 0, 'S'), true);
	//Check for conflict with other ship
	b.placeShip(b.w, 'B', 4, 'S');
	EXPECT_EQ(b.placeShip(b.w, 'B', 3, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'C', 3, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'D', 3, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'A', 2, 'E'), true);
	EXPECT_EQ(b.placeShip(b.w, 'B', 3, 'S'), true);
	EXPECT_EQ(b.placeShip(b.w, 'B', 4, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'C', 1, 'E'), false);
	EXPECT_EQ(b.placeShip(b.w, 'C', 6, 'E'), true);
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	//Battleship_Player p1;
	//p1.printBoards();
	//p1.initialize();
	
	/*
	srand(time(0));
	vector<trivia_question> vec;
	input_questions(vec);

	double time_to_beat = 60;
	while (true) {
		cout << "Player 1's Turn: " << endl;
		if (!volleyball(time_to_beat, vec)) {
			//player 2 makes shots (bulletpoint #2)
			cout << "player 2 makes shots\n" << endl;
			//reset timer
			time_to_beat = 60;
		}
		cout << "Player 2's Turn: " << endl;
		if (!volleyball(time_to_beat, vec)) {
			//player 1 makes shots (bulletpoint #1)
			cout << "player 1 makes shots\n" << endl;
			//reset time
			time_to_beat = 60;
		}
	}*/
}	
