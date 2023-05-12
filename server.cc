//
// daytime_server.cpp
// ~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <boost/asio.hpp>
#include "battleship.h"
#include "jeopardy.h"
#include "volleyball.h"
using namespace std;
using boost::asio::ip::tcp;

string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

#define MSG_READY_TO_PLAY     100
#define MSG_START_QUIZ 		  101
#define MSG_YOUR_TURN 		  102
#define MSG_YOUR_ATTACK 	  103
#define MSG_ATTACK_COORDINATE 104
#define MSG_HIT 			  105
#define MSG_MISS 			  106

int main()
{ 
  try
  {
    boost::asio::io_context io_context;

    tcp::endpoint endpoint(tcp::v4(), 1898);
    tcp::acceptor acceptor(io_context, endpoint);

    for (;;)
    {
      tcp::iostream stream;
      boost::system::error_code ec;
	  cout << "Waiting for player 2 to connect" << endl;
      acceptor.accept(stream.socket(), ec);
      if (!ec)
      {
		int message_type = 0;
        srand(time(0));
		cout << "Player 1\n" << endl;
		vector<trivia_question> vec;
		input_questions(vec);
		
		//initialize battleship
		initializeP1();
		
		stream << MSG_READY_TO_PLAY << endl;
		stream >> message_type;	

		double time_to_beat = 60;
		//string message = "";
		while (true) {
			cout << "Player 1's Turn: \n" << endl;
			if (!volleyball(time_to_beat, vec)) {
				//player 2 makes 3 shots (bulletpoint #2)
				stream << MSG_YOUR_ATTACK << endl;
				cout << "Player 2 attacks" << endl;
				//reset timer when one round of volleyardy ends
				time_to_beat = 60;
			}
			else {
				stream << MSG_YOUR_TURN << endl;
			}
			
			stream << time_to_beat << endl;
			cout << "Player 2's Turn" << endl;
			
			stream >> message_type;
			if (message_type == MSG_YOUR_ATTACK) {
				cout << "Player 1 attacks" << endl;
				for (int i = 0; i < 3; i++) p1Turn();
			}
			stream >> time_to_beat;
		}

      }
    }
  }
  catch (exception& e)
  {
    cerr << e.what() << endl;
  }
}
