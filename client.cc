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
#include <unistd.h>
#include <boost/asio.hpp>
#include "/public/colors.h"
#include "new_battleship.h"
#include "common.h"
#include "jeopardy.h"
#include "volleyball.h"
using namespace std;
using boost::asio::ip::tcp;

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
		clearscreen();
		int message_code = 0;
		Battleship_Player p2;
		p2.setName("Player 2");
		//cout << "Player 2\n" << endl;
		vector<trivia_question> vec;
		input_questions(vec);


		//initialize battleship
		p2.initialize();

		s << MSG_READY_TO_PLAY << endl;
		s >> message_code;
		
		double time_to_beat = 60;
		while(true) {
			p2.printBoards();
			cout << "Player 1's Turn: \n" << endl;
			if(sendAttack(p2, s)) return 0;
			s >> time_to_beat;
			p2.printBoards();
			cout << "Your Turn: \n" << endl;
			
			if (!volleyball(time_to_beat, vec)) {
				//player 1 makes shots
				if(!receiveAttack(p2, s)) return 0;
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
