#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

class trivia_question {
	private:
		std::string question;
		std::string options[4];
		char answer = 'a';
	public:
		trivia_question() {}
		void print_question() {
			std::cout << question << std::endl;
			int random_num = (rand() & 0b11);
			std::cout << "  a.) " << options[random_num] << std::endl;
			std::cout << "  b.) " << options[(random_num+1) & 0b11] << std::endl;
			std::cout << "  c.) " << options[(random_num+2) & 0b11] << std::endl;
			std::cout << "  d.) " << options[(random_num+3) & 0b11] << std::endl;
			answer += ((4 - random_num) & 0b11);
		}
		void add_answer(int num, std::string n_option) { options[num] = n_option; }
		void set_question(std::string n_question) { question = n_question; }
		bool check_answer(char user_answer) {
			if (user_answer == answer || user_answer == answer - 32) return true;
			return false;
		}
};

void input_questions(std::vector<trivia_question> &vec) {
	std::ifstream inFS;
	inFS.open("questions.txt");
	if (!inFS.is_open()) {
		std::cout << "Could not open file." << std::endl;
		exit(1);
	}
	trivia_question current_question;
	std::string input;
	while (true) {
		getline(inFS, input);
		if (inFS.eof()) break;
		size_t found = input.find("\\n");
		while (found != std::string::npos) {
			input.replace(found,2,"\n");
			found = input.find("\\n");
		}

		current_question.set_question(input);
		for (int i = 0; i < 4; i++) {
			getline(inFS,input);
			current_question.add_answer(i,input);
		}
		getline(inFS, input);
		vec.push_back(current_question);
	}
}
