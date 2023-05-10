#pragma once

#include <iostream>
#include <time.h>
#include <chrono>
#include "/public/read.h"


bool volleyball(double &time_to_beat, std::vector<trivia_question> &vec) {
	auto start = std::chrono::steady_clock::now();
	//print random question
	int question_num = rand() % vec.size();
	trivia_question current = vec.at(question_num);
	current.print_question();

	std::cout << "Time to beat: " << time_to_beat << " seconds" << std::endl;
	char player_answer = read();
	while (!(player_answer > 96 && player_answer < 101) && !(player_answer > 64 && player_answer < 69)) {
		std::cout << "Please enter a,b,c, or d." << std::endl;
		player_answer = read();
	}
	//check player answer and time taken
	if (current.check_answer(player_answer)) {
		auto end = std::chrono::steady_clock::now();
		double elapsed_time = std::chrono::duration<double>(end - start).count(); 
		if (elapsed_time < time_to_beat) {
			std::cout << "Correct!" << std::endl;
			std::cout << "Time taken: " << elapsed_time << " seconds\n" << std::endl;
			time_to_beat = elapsed_time;
			return true;
		}
		std::cout << "Correct but too SLOW!" << std::endl;
		std::cout << "Time taken: " << elapsed_time << " seconds\n" << std::endl;
		return false;
	}
	else {
		std::cout << "Incorrect!\n" << std::endl;
		return false;
	}
}
