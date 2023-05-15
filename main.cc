#include <iostream>
#include <time.h>
#include <cstdlib>
#include "jeopardy.h"
#include "volleyball.h"
#include "new_battleship.h"

using namespace std;

int main() {
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
