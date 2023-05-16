#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "/public/read.h"
#include "/public/colors.h"
#include <gtest/gtest.h>


static const char CRUISER = 'C';
static const char BATTLESHIP = 'B';
static const char SUBMARINE = 'S';
static const char DESTROYER = 'D';
static const char AIRCRAFT_CARRIER = 'A';
static const char WATER = '~';
static const char HIT = '*';
static const char MISS = 'X';

static const int SIZE = 10;

static const int MSG_HIT = 105;
static const int MSG_MISS = 106;
static const int MSG_OUT_OF_BOUNDS = 107;
static const int MSG_ALREADY_ATTACKED = 108;
static const int MSG_YOU_WON = 109;

void clear_bottom_screen(int row_change) {
	auto[rows,cols] = get_terminal_size();
	movecursor(25 + row_change,0);
	//setbgcolor(255,255,255);
	for (int i = 25 + row_change; i <= rows; i++) std::cout << std::setw(cols) << "" << std::endl;
	//resetcolor();
}

class Battleship_Player {
	private:
		std::string name = "";
		struct Battleship {
			const std::string name = "NA";
			const char symbol = ' ';
			const int length = 0;
		};
		std::vector<Battleship> myWarships;
		std::vector<std::vector<char>> myBoard {SIZE, std::vector<char>(SIZE, '~')};
		std::vector<std::vector<char>> myAttackBoard {SIZE, std::vector<char>(SIZE, '~')};
		int hitCount = 0;
		bool placeShip(Battleship &warship, char row, int col, char o) {
			auto[rows,cols] = get_terminal_size();
			movecursor(27,cols/2-24);
			if (o != 'S' and o != 's' and o != 'E' and o != 'e') {
				std::cout << "Invalid orientation! Please enter S or E." << std::endl;
				return false;
			}
			if (row < 'A' or row >= 'A' + SIZE or col < 0 or col >= SIZE) {
				std::cout << "Invalid coordinate! Coordinate does not exist." << std::endl;
				return false;
			}
			if ((o == 'S' or o == 's') and row + warship.length-1 >= 'A' + SIZE) {
				std::cout << "Invalid placement! Off bottom edge of the board." << std::endl;
				return false;
			}
			if ((o == 'E' or o == 'e') and col + warship.length-1 >= SIZE) {
				std::cout << "Invalid placement! Off right edge of the board." << std::endl;
				return false;
			}
			if (o == 'S' or o == 's') {
				for (int i = 0; i < warship.length; i++) {
					if (myBoard[row - 'A' + i][col] != WATER) {
						std::cout << "Invalid placement! Conflict with another ship." << std::endl;
						return false;
					}
				}
				for (int i = 0; i < warship.length; i++) myBoard[row - 'A' + i][col] = warship.symbol;
				return true;
			}
			else {
				for (int i = 0; i < warship.length; i++) {
					if (myBoard[row - 'A'][col + i] != WATER) {
						std::cout << "Invalid placement! Conflict with another ship." << std::endl;
						return false;
					}
				}
				for (int i = 0; i < warship.length; i++) myBoard[row - 'A'][col + i] = warship.symbol;
				return true;
			}
		}
//<<<<<<< HEAD
		//Testing
		Battleship w {"w", 'w', 3};
		FRIEND_TEST(battleship, oppAttack);
		FRIEND_TEST(battleship, placeShip);

/*=======
		Battleship w {"w", 'w', 3};
		FRIEND_TEST(battleship, oppAttack);
		FRIEND_TEST(battleship, placeShip);
>>>>>>> af2f2a4a45ad7c37f21d6f80faa8ced06f30999c*/
	public:
		Battleship_Player() {}
		void setName(std::string userName) { name = userName; }
		std::string getName() { return name; }
		void printBoards() {
			auto [rows,cols] = get_terminal_size();
			movecursor(8,0);
			/*setcolor(214, 226, 233);
			if(system ("figlet -c -t *Volleyshipardy*")) {};
			resetcolor();*/


			std::cout << std::setfill('-') << std::setw(cols) << "" << std::endl;
			std::cout << std::setfill(' ');
			//setcolor(2, 62, 138);
			setbgcolor(188, 212, 230);//blue
			std::cout << BLUE << std::setw(cols/4-4) << "" << std::setw(cols/4+4) << std::left << "My Fleet" << RESET << "|";
			//setcolor(208, 0, 0);
			setbgcolor(253, 226, 228);//red
			std::cout << RED << std::setw(cols/4+5) << std::right << "Enemy Fleet" << std::setw(cols/4-2) << RESET << std::endl;
			resetcolor();
			std::cout << std::setfill('-') << std::setw(cols) << "" << std::endl << std::endl;
			std::cout << std::setfill(' ') << std::setw(cols/4-SIZE*2+SIZE/2) << "";
			for (int i = 0; i < SIZE; i++) {
				setbgcolor(88,111,124);//#s
				std::cout << BOLDWHITE << i << "  " << RESET; 
			}
			resetcolor();
			std::cout << std::setw(cols/4-SIZE*2+SIZE/2) << std::right << "" << '|';
			std::cout << std::setw(cols/4-SIZE*2+SIZE/2) << "";
			for (int i = 0; i < SIZE; i++) {
				setbgcolor(88,111,124);//#s	
				std::cout << BOLDWHITE << i << "  " << RESET;
			}
			resetcolor();
			std::cout << std::endl;
			for (int j = 0; j < SIZE; j++) {
				std::cout << std::setw(cols/4-(SIZE+3+SIZE/2)) << "";
				setbgcolor(88,111,124);//alpha

				std::cout << BOLDWHITE << char('A'+j) << "  " << RESET;
				std::string color = "";
				for (int k = 0; k < SIZE; k++) {
					char boardUnit = myBoard[j][k];
					if (boardUnit == WATER) color = BOLDCYAN;
					else if (boardUnit == MISS) color = RED;
					else if (boardUnit == HIT) color = YELLOW;
					else color = BOLDWHITE;
					setbgcolor(47,69,80);//water
					std::cout << color << myBoard[j][k] << "  " << RESET;
				}
				resetcolor();
				std::cout << std::setw(cols/4-(SIZE+SIZE/2)) << "" << '|';
				std::cout << std::setw(cols/4-(SIZE+3+SIZE/2)) << "";
				setbgcolor(88,111,124);//alpha
				
				std::cout << BOLDWHITE << char('A'+j) << "  " << RESET;
				for (int k = 0; k < SIZE; k++) {
					char boardUnit = myAttackBoard[j][k];
					if (boardUnit == WATER) color = CYAN;
					else if (boardUnit == MISS) color = RED;
					else color = YELLOW;//if HIT
					setbgcolor(47,69,80);//water
					std::cout << color << myAttackBoard[j][k] << "  " << RESET;
				}
				resetcolor();
				std::cout << std::setw(SIZE) << "";
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << std::setfill('-') << std::setw(cols) << "" << std::endl;
			std::cout << std::setfill(' ');
		}

		void initialize() {
			Battleship aircraftCarrier {"Aircraft Carrier", AIRCRAFT_CARRIER, 5};
			Battleship battleship {"Battleship", BATTLESHIP, 4};
			Battleship cruiser {"Cruiser", CRUISER, 3};
			Battleship submarine {"Submarine", SUBMARINE, 3};
			Battleship destroyer {"Destroyer", DESTROYER, 2};
			myWarships.push_back(aircraftCarrier);
			myWarships.push_back(battleship);
			myWarships.push_back(cruiser);
			myWarships.push_back(submarine);
			myWarships.push_back(destroyer);
			clearscreen();
			printBoards();
			auto [t_rows,t_cols] = get_terminal_size();
			
			for (Battleship &ship : myWarships) {
				
				while(true) {
					int row = 0;
					int column = 0;
					int ori = 0;
					movecursor(25, t_cols/8);
					std::cout << "Enter the coordinates for the stern of your warship and then the orientation(S = South, E = East) in the format: A1S" << std::endl;	
					movecursor(27, 3*t_cols/8);
					std::cout << ship.name << "{length " << ship.length << "): " <<std::flush;

					set_raw_mode(true);
					while(true) {
						row = quick_read();
						if (row >= 'A' and row != 127) break;
					}
					set_raw_mode(false);
					std::cout << (char)row << std::flush;
					set_raw_mode(true);
					while(true) {
						column = quick_read();
						if (column >= '0' and row != 127) break;
					}
					set_raw_mode(false);
					std::cout << (char)column << std::flush;
					set_raw_mode(true);
					while(true) {
						ori = quick_read();
						if (ori >= 'A' and row != 127) break;
					}
					set_raw_mode(false);
					std::cout << (char)ori << std::flush;
					usleep(200000);
					if (placeShip(ship,(char)row,column-'0',(char)ori)) break;
					sleep(2);
					clear_bottom_screen(2);
					movecursor(27, 3*t_cols/8);

				}
				set_raw_mode(false);
				clearscreen();
				printBoards();
			}
		}
		
		//returns message codes for networking
		int oppAttack(char row, int col) {
			//auto[t_rows,t_cols] = get_terminal_size();
			if (row >= 'A' + SIZE or row < 'A' or col >= SIZE or col < 0) {
				//return "Out of bounds! Please enter a valid coordinate";
				return MSG_OUT_OF_BOUNDS;
			}
			else if (myBoard[row - 'A'][col] == HIT or myBoard[row - 'A'][col] == MISS) {
				//return "Already attacked! Please enter a new coordinate to attack";
				return MSG_ALREADY_ATTACKED;
			}
			else if (myBoard[row - 'A'][col] == WATER) {
				myBoard[row - 'A'][col] = MISS;
				//clearscreen();
				//printBoards();
				return MSG_MISS;
			}
			else {
				++hitCount;
				myBoard[row - 'A'][col] = HIT;
				//clearscreen();
				//printBoards();
				if (hitCount == 17) return MSG_YOU_WON;
				return MSG_HIT;
			}
		}

		void myAttack(char row, int col, char symbol) {
			myAttackBoard[row - 'A'][col] = symbol;
			clearscreen();
			printBoards();
		}
	
};


