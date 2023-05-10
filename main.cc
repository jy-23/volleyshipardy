#include <iostream>
#include <time.h>
#include <cstdlib>
#include "jeopardy.h"
#include "volleyball.h"

using namespace std;

int main() {
	srand(time(0));
	vector<trivia_question> vec;
	input_questions(vec);

	double time_to_beat = 30;
	while (true) {
		cout << "Player 1's Turn: " << endl;
		if (!volleyball(time_to_beat, vec)) {
			//player 2 makes shots (bulletpoint #2)
			break;
		}
		cout << "Player 2's Turn: " << endl;
		if (!volleyball(time_to_beat, vec)) {
			//player 1 makes shots (bulletpoint #1)
			break;
		}
	}

}
