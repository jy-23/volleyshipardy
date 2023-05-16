#include <iostream>
#include <time.h>
#include <cstdlib>
//#include "jeopardy.h"
//#include "volleyball.h"
#include "new_battleship.h"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	Battleship_Player p1;
	p1.printBoards();
	p1.initialize();
	
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
Battleship_Player *b;

TEST(battleship, oppAttack) {
	EXPECT_EQ(b->oppAttack('K', 5), "Out of bounds! Please enter a valid coordinate");
	EXPECT_EQ(b->oppAttack('J', 5), "MISS!");
	EXPECT_EQ(b->oppAttack(64, 5), "Out of bounds! Please enter a valid coordinate");
	EXPECT_EQ(b->oppAttack(65, 5), "MISS!");
	EXPECT_EQ(b->oppAttack(70, -1), "Out of bounds! Please enter a valid coordinate");
	EXPECT_EQ(b->oppAttack(70, 0), "MISS!");
    EXPECT_EQ(b->oppAttack(70, 10), "Out of bounds! Please enter a valid coordinate");
	EXPECT_EQ(b->oppAttack(70, 9), "MISS!");
	b->hitCount = 17;
	EXPECT_EQ(b->oppAttack(70, 9), "VICTORY!");
	b->hitCount = 16;
	b->myBoard[0][0] = CRUISER;
	EXPECT_EQ(b->oppAttack('A', 0), "VICTORY!");
	b->hitCount = 15;
    b->myBoard[0][0] = CRUISER;
    EXPECT_EQ(b->oppAttack('A', 0), "HIT");
}

TEST(battleship, placeShip) {
	//Bounds check coordinates
	EXPECT_EQ(b->placeShip(b->w, 'B', 1, 'Z'), false);
	EXPECT_EQ(b->placeShip(b->w, 'B', 1, 'S'), true);
	EXPECT_EQ(b->placeShip(b->w, 64, 1, 'S'), false);
	EXPECT_EQ(b->placeShip(b->w, 'A', 1, 'S'), true);
	EXPECT_EQ(b->placeShip(b->w, 'K', 1, 'S'), false);
	EXPECT_EQ(b->placeShip(b->w, 'J', 1, 'S'), true);
	EXPECT_EQ(b->placeShip(b->w, 'B', -1, 'S'), false);
	EXPECT_EQ(b->placeShip(b->w, 'B', 0, 'S'), true);
	EXPECT_EQ(b->placeShip(b->w, 'B', 10, 'S'), false);
	EXPECT_EQ(b->placeShip(b->w, 'B', 9, 'S'), true);
	//Bounds check ships
	EXPECT_EQ(b->placeShip(b->w, 'A', 7, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'A', 6, 'E'), true);
	EXPECT_EQ(b->placeShip(b->w, 'J', 0, 'S'), false);
	EXPECT_EQ(b->placeShip(b->w, 'I', 0, 'S'), true);
	//Check for conflict with other ship
	b->placeShip(b->w, 'B', 3, 'S');
	EXPECT_EQ(b->placeShip(b->w, 'B', 2, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'C', 2, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'D', 2, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'A', 2, 'E'), true);
	EXPECT_EQ(b->placeShip(b->w, 'B', 2, 'S'), true);
	EXPECT_EQ(b->placeShip(b->w, 'B', 3, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'C', 1, 'E'), false);
	EXPECT_EQ(b->placeShip(b->w, 'C', 0, 'E'), true);
}
