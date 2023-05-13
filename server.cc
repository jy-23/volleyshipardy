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
#include "/public/colors.h"
#include "new_battleship.h"
#include "common.h"
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
	  clearscreen();
	  cout << "Waiting for player 2 to connect" << endl;
      acceptor.accept(stream.socket(), ec);
      if (!ec)
      { 
		clearscreen();
		cout << "Connected!" << endl;
		usleep(333333);
		int message_code = 0;
        srand(time(0));
		Battleship_Player p1;
		p1.setName("Player 1");
		vector<trivia_question> vec;
		input_questions(vec);
		
		//initialize battleship
		p1.initialize();
		//cout << "Player 1\n" << endl;

		stream << MSG_READY_TO_PLAY << endl;
		stream >> message_code;


		double time_to_beat = 60;
		while (true) {
			p1.printBoards();
			cout << "Your Turn: \n" << endl;
			if (!volleyball(time_to_beat, vec)) {
				if(!receiveAttack(p1, stream)) return 0;
				time_to_beat = 60;
			}
			else {
				stream << MSG_YOUR_TURN << endl;
			}
			
			stream << time_to_beat << endl;
			p1.printBoards();
			cout << "Player 2's Turn" << endl;
			if (sendAttack(p1, stream)) return 0;
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
