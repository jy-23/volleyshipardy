#pragma once

#include <iostream>
#include <time.h>
#include <chrono>
#include "/public/read.h"
void print_dummy_question() {
	//function to be replaced by bulletpoint #3
	std::cout << "  What is 4 + 2?\n";
	std::cout << "   a.) 5\n";
	std::cout << "   b.) 4\n";
	std::cout << "   c.) 6\n";
	std::cout << "   d.) 8\n" << std::endl;
}

bool volleyball(double &time_to_beat) {
	auto start = std::chrono::steady_clock::now();
	print_dummy_question();
	std::cout << "Time to beat: " << time_to_beat << " seconds" << std::endl;
	char player_answer = read();
	if (player_answer == 'c') {
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
