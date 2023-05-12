//
// daytime_client.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "battleship.h"
#include "jeopardy.h"
#include "volleyball.h"
using namespace std;
using boost::asio::ip::tcp;

#define MSG_READY_TO_PLAY     100
#define MSG_START_QUIZ 		  101
#define MSG_YOUR_TURN 		  102
#define MSG_YOUR_ATTACK 	  103
#define MSG_ATTACK_COORDINATE 104
#define MSG_HIT 			  105
#define MSG_MISS 			  106

int main(int argc, char* argv[])
{ srand(time(0)+1);
	try
	{
		/*if (argc != 3)
		{
			cerr << "Usage: daytime_client <host> <port>" << endl;
			return EXIT_FAILURE;
		}*/

		//tcp::iostream s(argv[1], argv[2]); //[1] == host, [2] == port
		tcp::iostream s("localhost", "1898");
		if (!s) //Connection failed
		{
			cout << "Unable to connect: " << s.error().message() << endl;
			return EXIT_FAILURE;
		}
		int message_type = 0;
		cout << "Player 2\n" << endl;
		vector<trivia_question> vec;
		input_questions(vec);


		//initialize battleship
		initializeP2();
		s << MSG_READY_TO_PLAY << endl;
		s >> message_type;
		
		//string message = "";
		double time_to_beat = 60;
		while(true) {
			cout << "Player 1's Turn: \n" << endl;
			s >> message_type;
			if (message_type == MSG_YOUR_ATTACK) {
				cout << "Player 2 attacks" << endl;
				for (int i = 0; i < 3; i++) p2Turn();
			}
			s >> time_to_beat;
			cout << "Player 2's Turn: \n" << endl;
			
			if (!volleyball(time_to_beat, vec)) {
				//player 1 makes shots (bulletpoint #2)
				s << MSG_YOUR_ATTACK << endl;
				cout << "Player 1 attacks" << endl;
				//reset timer when one round of volleyardy ends
				time_to_beat = 60;
			}
			else {
				s << MSG_YOUR_TURN << endl;
			}
			s << time_to_beat << endl;

		}
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
	}
}
