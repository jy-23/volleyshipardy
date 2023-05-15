#pragma once

#include <iostream>
#include <time.h>
#include <chrono>
#include "/public/colors.h"


bool volleyball(double &time_to_beat, std::vector<trivia_question> &vec) {
	auto[t_rows,t_cols] = get_terminal_size();
	auto start = std::chrono::steady_clock::now();
	//print random question
	int question_num = rand() % vec.size();
	trivia_question current = vec.at(question_num);
	current.print_question();
	
	//movecursor(40, 5);
	std::cout << "Time to beat: " << time_to_beat << " seconds" << std::endl;
	int player_answer = 0;

	while (true) {
		set_raw_mode(true);
		while(true) {
			player_answer = quick_read();
			if(player_answer >= 'A' and player_answer != 127) break;
		}
		if((player_answer >= 'a' && player_answer <= 'd') or (player_answer >= 'A' && player_answer <= 'D')) break;
		set_raw_mode(false);

		std::cout << "Please enter a,b,c, or d." << std::endl;
		sleep(2);
	}
	set_raw_mode(false);
	//check player answer and time taken
	clear_bottom_screen(0);
	if (current.check_answer((char)player_answer)) {
		auto end = std::chrono::steady_clock::now();
		double elapsed_time = std::chrono::duration<double>(end - start).count(); 
		if (elapsed_time < time_to_beat) {
			movecursor(25,t_cols/2-4);
			std::cout << "Correct!" << std::endl;
			movecursor(27, t_cols/2-12);
			std::cout << "Time taken: " << elapsed_time << " seconds\n" << std::endl;
			sleep(2);
			time_to_beat = elapsed_time;
			return true;
		}
		movecursor(25,t_cols/2-10);
		std::cout << "Correct but too SLOW!" << std::endl;
		movecursor(27,t_cols/2-12);
		std::cout << "Time taken: " << elapsed_time << " seconds\n" << std::endl;
		sleep(2);
		return false;
	}
	else {
		movecursor(25, t_cols/2-5);
		std::cout << "Incorrect!\n" << std::endl;
		sleep(2);
		return false;
	}
}
