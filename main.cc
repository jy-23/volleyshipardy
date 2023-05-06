#include <iostream>
#include <time.h>

#include "volleyball.h"

using namespace std;

int main() {
	double time_to_beat = 30;
	while (true) {
		cout << "Player 1's Turn: " << endl;
		if (!volleyball(time_to_beat)) {
			//player 2 makes shots (bulletpoint #2)
			break;
		}
		cout << "Player 2's Turn: " << endl;
		if (!volleyball(time_to_beat)) {
			//player 1 makes shots (bulletpoint #1)
			break;
		}
	}

}
