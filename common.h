#pragma once
#include <boost/asio.hpp>
#include <string>
#include "/public/read.h"
#include "/public/colors.h"

#define MSG_READY_TO_PLAY 100
#define MSG_START_QUIZ 101
#define MSG_YOUR_TURN 102
#define MSG_YOUR_ATTACK 103
#define MSG_ATTACK_COORDINATE 104
#define MSG_HIT 105
#define MSG_MISS 106
#define MSG_OUT_OF_BOUNDS 107
#define MSG_ALREADY_ATTACKED 108
#define MSG_YOU_WON 109

bool receiveAttack(Battleship_Player &player, boost::asio::ip::tcp::iostream &s) {
	auto[t_rows,t_cols] = get_terminal_size();
	s << MSG_YOUR_ATTACK << std::endl;
	clear_bottom_screen(0);
	//std::cout << player.getName() << " attacks" << std::endl;
	int message_code = 0;
	for (int i = 0; i < 3; i++) {
		char row = ' ';
		int col = -1;
		movecursor(25,t_cols/2-7);
		std::cout << "Incoming attack!" << std::flush;
		while(true) {
			s >> row;
			s >> col;
			message_code = player.oppAttack(row,col);
			clear_bottom_screen(0);
			s << message_code << std::endl;
			if (message_code == MSG_HIT) {
				movecursor(25,t_cols/2-2);
				std::cout << "HIT!" << std::flush;
				sleep(2);
				break;
			} 
			else if ( message_code == MSG_MISS) {
				movecursor(25,t_cols/2-2);
				std::cout << "MISS!" << std::flush;
				sleep(2);
				break;
			}
			else if (message_code == MSG_YOU_WON) {
				movecursor(25,t_cols/2-27);
				std::cout << "DEFEAT! Your entire fleet has been destroyed!\n" << std::endl;
				return 0;
			}
			movecursor(25,t_cols/2-7);
			std::cout << "Incoming attack!" << std::flush;
			/*
			else if (message_code == MSG_OUT_OF_BOUNDS) {
				movecursor(25,t_cols/2-27);
				std::cout << "Out of bounds! Please enter a valid coordinate" << std::flush;
				sleep(2);
			}
			else if (message_code == MSG_ALREADY_ATTACKED) {
				movecursor(25,t_cols/2-30);
				std::cout << "Already attacked! Please enter a new coordinate to attack" << std::flush;
				sleep(2);
			}*/
		}
	}
	return 1;
}

bool sendAttack(Battleship_Player &player, boost::asio::ip::tcp::iostream &s) {
	auto[t_rows,t_cols] = get_terminal_size();
	int message_code = 0;
	s >> message_code;
	if (message_code != MSG_YOUR_ATTACK) return 0;
	clear_bottom_screen(0);
	movecursor(25, t_cols/2-24);
	std::cout << "Your attack! You get 3 shots at the enemy." << std::flush;
	sleep(2);
	for (int i = 0; i < 3; i++) {
		while(true) {
			clear_bottom_screen(0);
			movecursor(25,t_cols/2-24);
			std::cout << "Enter coordinate to attack in the format: A1" << std::flush;
			movecursor(27,t_cols/2-1);
			int row = 0;
			int col = 0;
			set_raw_mode(true);
			while(true) {
				row = quick_read();
				if (row >= 'A' and row != 127) break;
			}
			set_raw_mode(false);
			std::cout << (char)row << std::flush;
			//usleep(200000);
			set_raw_mode(true);
			while(true) {
				col = quick_read();
				if (col >= '0' and col != 127) break;
			}
			set_raw_mode(false);
			col = col - '0';
			std::cout << col;
			usleep(333333);
			s << (char)row << std::endl;
			s << col << std::endl;
			s >> message_code;
			clear_bottom_screen(0);
			//movecursor(25,t_cols/2 - 20);
			if (message_code == MSG_MISS) {
				player.myAttack(row, col, MISS);
				movecursor(25,t_cols/2-2);
				std::cout << "MISS!" << std::flush;
				sleep(2);
				break;
			}
			else if (message_code == MSG_HIT) {
				player.myAttack(row, col, HIT);
				movecursor(25,t_cols/2-2);
				std::cout << "HIT!" << std::flush;
				sleep(2);
				break;
			}
			else if (message_code == MSG_OUT_OF_BOUNDS) {
				movecursor(25,t_cols/2-27);
				std::cout << "Out of bounds! Please enter a valid coordinate" << std::flush;
				sleep(2);
			}
			else if (message_code == MSG_ALREADY_ATTACKED) {
				movecursor(25,t_cols/2-30);
				std::cout << "Already attacked! Please enter a new coordinate to attack" << std::flush;
				sleep(2);
			}
			else if (message_code == MSG_YOU_WON) {
				player.myAttack(row, col, HIT);
				movecursor(25,t_cols/2-4);
				std::cout << "VICTORY!\n" << std::endl;
				return 1;
			}
			else {
				std::cout << "BAD MESSAGE!\n" << std::endl;
				return 1;
				
			}
		}
	}
	return 0;
}



