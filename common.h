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
	s << MSG_YOUR_ATTACK << std::endl;
	std::cout << player.getName() << " attacks" << std::endl;
	std::string message_str = "";
	for (int i = 0; i < 3; i++) {
		char row = ' ';
		int col = -1;
		while(true) {
			s >> row;
			s >> col;
			message_str = player.oppAttack(row,col);
			s << message_str << std::endl;
			if (message_str.at(0) == 'O') s << MSG_OUT_OF_BOUNDS << std::endl;
			else if (message_str.at(0) == 'A') s << MSG_ALREADY_ATTACKED << std::endl;
			else if (message_str.at(0) == 'M') {
				s << MSG_MISS << std::endl;
				break;
			}
			else if (message_str.at(0) == 'H') {
				s << MSG_HIT << std::endl;
				break;
			}
			else if (message_str.at(0) == 'V') {
				s << MSG_YOU_WON << std::endl;
				std::cout << "DEFEAT! Your entire fleet has been destroyed!" << std::endl;
				return 0;
			}
			else {
				std::cout << "Bad message!" << std::endl;
				exit(1);
			}
		}
	}
	return 1;
}

bool sendAttack(Battleship_Player &player, boost::asio::ip::tcp::iostream &s) {
	std::string message_str = "";
	int message_code = 0;
	s >> message_code;
	if (message_code != MSG_YOUR_ATTACK) return 0;
	std::cout << "You attack!" << std::endl;
	for (int i = 0; i < 3; i++) {
		while(true) {
			std::cout << "Enter coordinate to attack in the format: A1" << std::endl;
			char row = read();
			int col = read();
			s << row << std::endl;
			s << col << std::endl;
			s >> message_str;
			s >> message_code;
			if (message_code == MSG_MISS) {
				player.myAttack(row, col, MISS);
				std::cout << message_str << std::endl;
				break;
			}
			else if (message_code == MSG_HIT) {
				player.myAttack(row, col, HIT);
				std::cout << message_str << std::endl;
				break;
			}/*
			else if (message_code == MSG_OUT_OF_BOUNDS) {
				std::cout << "Out of bounds! Please enter a valid coordinate" << std::endl;
			}
			else if (message_code == MSG_ALREADY_ATTACKED) {
				std::cout << "Already attacked! Please enter a new coordinate to attack" << std::endl;
			}*/
			else if (message_code == MSG_YOU_WON) {
				player.myAttack(row, col, HIT);
				std::cout << message_str << std::endl;
				return 1;
			}
		}
	}
	return 0;
}



