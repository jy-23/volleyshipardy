#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "/public/read.h"
#include "/public/colors.h"

static const char CRUISER = 'C';
static const char BATTLESHIP = 'B';
static const char SUBMARINE = 'S';
static const char DESTROYER = 'D';
static const char AIRCRAFT_CARRIER = 'A';
static const char WATER = '~';
static const char HIT = '*';
static const char MISS = 'X';

static const int SIZE = 10;

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
	public:
		Battleship_Player() {}
		void setName(std::string userName) { name = userName; }
		std::string getName() { return name; }
		void printBoards() {
			if(system("figlet Volleyshipardy"));
			auto [rows,cols] = get_terminal_size();

			std::cout << std::setfill('-') << std::setw(SIZE*8+1) << "" << std::endl;
			std::cout << std::setfill(' ');
			std::cout << std::setw(SIZE+SIZE/2) << "" << std::setw(SIZE*3-SIZE/2) << std::left << "My Fleet" << "|";
			std::cout << std::setw(SIZE*3-SIZE/2) << std::right << "Enemy Fleet" << std::endl;
			std::cout << std::setfill('-') << std::setw(SIZE*8+1) << "" << std::endl << std::endl;
			std::cout << std::setfill(' ') << std::setw(SIZE) << "";
			for (int i = 0; i < SIZE; i++) std::cout << i << ' ';
			std::cout << std::setw(SIZE) << std::right << "" << '|';
			std::cout << std::setw(SIZE) << "";
			for (int i = 0; i < SIZE; i++) std::cout << i << ' ';
			std::cout << std::endl;
			for (int j = 0; j < SIZE; j++) {
				std::cout << std::setw(SIZE-2) << "";
				std::cout << char('A'+j) << " ";
				for (int k = 0; k < SIZE; k++) std::cout << myBoard[j][k] << " ";
				std::cout << std::setw(SIZE) << "" << '|';
				std::cout << std::setw(SIZE-2) << "";
				std::cout << char('A'+j) << " ";
				for (int k = 0; k < SIZE; k++) std::cout << myAttackBoard[j][k] << " ";
				std::cout << std::setw(SIZE) << "";
				std::cout << std::endl;
			}
			std::cout << std::endl;
			std::cout << std::setfill('-') << std::setw(SIZE*8+1) << "" << std::endl;
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
			std::cout << "Enter the coordinates for the stern of your warship and then the orientation(S = South, E = East) in the format: A 1 S" << std::endl;
			for (Battleship &ship : myWarships) {
				std::cout << ship.name << "{length " << ship.length << "): ";
				
				while(true) {
					char row = read();
					int column = read();
					char ori = read();
					if (placeShip(ship,row,column,ori)) break;
				}
				clearscreen();
				printBoards();
			}
		}

		std::string oppAttack(char row, int col) {
			if (row >= 'A' + SIZE or row < 'A' or col >= SIZE or col < 0) {
				return "Out of bounds! Please enter a valid coordinate";
			}
			else if (myBoard[row - 'A'][col] == HIT or myBoard[row - 'A'][col] == MISS) {
				return "Already attacked! Please enter a new coordinate to attack";
			}
			else if (myBoard[row - 'A'][col] == WATER) {
				myBoard[row - 'A'][col] = MISS;
				clearscreen();
				printBoards();
				return "MISS!";
			}
			else {
				++hitCount;
				myBoard[row - 'A'][col] = HIT;
				clearscreen();
				printBoards();
				if (hitCount == 17) return "VICTORY!";
				return "HIT";
			}
		}

		void myAttack(char row, int col, char symbol) {
			myAttackBoard[row - 'A'][col] = symbol;
			clearscreen();
			printBoards();
		}
	
};


