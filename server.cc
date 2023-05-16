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
	  auto[t_rows,t_cols] = get_terminal_size();

	  movecursor(0,0);
	  setcolor(214, 226, 233);
	  if (system("figlet -c -t *Volleyshipardy*")) {};
	  resetcolor();
	  
	  movecursor(25,t_cols/2-17);
	  cout << "Waiting for player 2 to connect" << endl;
      acceptor.accept(stream.socket(), ec);
      if (!ec)
      { 
		clear_bottom_screen(0);
		movecursor(25,t_cols/2-5);
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
		movecursor(25,t_cols/2-26);
		//cout << "Player 1\n" << endl;

		stream << MSG_READY_TO_PLAY << endl;
		cout << "Waiting for Player 2 to finish deploying their battleships..." << flush;
		stream >> message_code;
		clear_bottom_screen(0);
		double time_to_beat = 60;
		while (true) {
			p1.printBoards();
			clear_bottom_screen(0);
			movecursor(25,t_cols/2-5);
			cout << "Your Turn\n" << endl;
			if (!volleyball(time_to_beat, vec)) {
				if(!receiveAttack(p1, stream)) return 0;
				time_to_beat = 60;
			}
			else {
				stream << MSG_YOUR_TURN << endl;
			}
			
			stream << time_to_beat << endl;
			p1.printBoards();
			clear_bottom_screen(0);
			movecursor(25,t_cols/2-7);
			cout << "Player 2's Turn" << flush;
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
