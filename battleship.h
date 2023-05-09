#include <iostream>

struct BoardPiece {
	bool hasShip;
	bool isHit;
};

BoardPiece p1Board[7][7];
BoardPiece p2Board[7][7];
int p1HitCount;
int p2HitCount;

void placeShip(int shipLength, int x, int y, char o, BoardPiece board[7][7]) {
	if (o != 'N' && o != 'S' && o != 'E' && o != 'W' && o != 'n' && o != 's' && o != 'e' && o != 'w') throw std::runtime_error("Invalid orientation");
	else if (o == 'N' && y + shipLength > 7) throw std::runtime_error("Invalid placement: Off edge of board");
	else if (o == 'S' && y - shipLength < 0) throw std::runtime_error("Invalid placement: Off edge of board");
	else if (o == 'E' && x + shipLength > 7) throw std::runtime_error("Invalid placement: Off edge of board");
	else if (o == 'W' && x - shipLength < 0) throw std::runtime_error("Invalid placement: Off edge of board");
	else {
		for (int i = 0; i < shipLength; i++) {
			if (o == 'N') {
				if (!board[x][y + i].hasShip) board[x][y + i].hasShip = true;
				else throw std::runtime_error("Invalid placement: conflict with other ship");
			}
			if (o == 'S') {
				if (!board[x][y - i].hasShip) board[x][y - i].hasShip = true;
                else throw std::runtime_error("Invalid placement: conflict with other ship");
			}
			if (o == 'E') {
                if (!board[x + i][y].hasShip) board[x + i][y].hasShip = true;
                else throw std::runtime_error("Invalid placement: conflict with other ship");
            }
			if (o == 'W') {
                if (!board[x - i][y].hasShip) board[x - i][y].hasShip = true;
                else throw std::runtime_error("Invalid placement: conflict with other ship");
            }
		}
	}
}

void attack(int x, int y, BoardPiece board[7][7]) {
	if (x > 6 || x < 0 || y > 6 || y < 0) {
		std::cout << "Out of bounds. Please enter Valid coordinates\n";
        std::cin >> x >> y;
        attack(x, y, board);
	}
	else if (board[x][y].isHit) {
        std::cout << "This piece has already been hit. Please enter valid coordinates\n";
        std::cin >> x >> y;
        attack(x, y, board);
    }
	else {
		if (board[x][y].hasShip) {
			board[x][y].isHit = true;
			if (board == p1Board) p1HitCount++;
			else p2HitCount++;
			std::cout << "HIT!\n";
		}
		else std::cout << "MISS!\n";
		if (p1HitCount >= 17) {
			std::cout << "Player two has won!\n";
			exit(0);
		}
		else if (p2HitCount >= 17) {
            std::cout << "Player one has won!\n";
            exit(0);
        }
	}
}

void p1Turn() {
	int x;
	int y;
	std::cout << "Player One's turn. Please enter the coordinate to attack in the format: x y\n";
	std::cin >> x >> y;
	attack(x, y, p2Board);
}

void p2Turn() {
    int x;
    int y;
    std::cout << "Player Two's turn. Please enter the coordinate to attack in the format: x y\n";
    std::cin >> x >> y;
    attack(x, y, p1Board);
}

void initializeP1() {
	int x;
	int y;
	char ori;
	std::cout << "Player one, please enter the X and Y coordinates for the stern of your carrier and then the orientation in the format: 1 1 N\n";
	std::cin >> x >> y >> ori;
	if (!std::cin) throw std::runtime_error("Invalid Input");
	placeShip(5, x, y, ori, p1Board);
	std::cout << "Player one, please enter the X and Y coordinates for the stern of your battleship and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(4, x, y, ori, p1Board);
    std::cout << "Player one, please enter the X and Y coordinates for the stern of your cruiser and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(3, x, y, ori, p1Board);
    std::cout << "Player one, please enter the X and Y coordinates for the stern of your submarine and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(3, x, y, ori, p1Board);
    std::cout << "Player one, please enter the X and Y coordinates for the stern of your destroyer and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(2, x, y, ori, p1Board);
	//debugging
	/*for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (p1Board[i][j].hasShip) std::cout << "*";
			else std::cout << "0";
    	}
		std::cout << std::endl;
	}*/
}

void initializeP2() {
	int x;
    int y;
    char ori;
    std::cout << "Player two, please enter the X and Y coordinates for the stern of your carrier and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(5, x, y, ori, p2Board);
    std::cout << "Player two, please enter the X and Y coordinates for the stern of your battleship and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(4, x, y, ori, p2Board);
    std::cout << "Player two, please enter the X and Y coordinates for the stern of your cruiser and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(3, x, y, ori, p2Board);
    std::cout << "Player two, please enter the X and Y coordinates for the stern of your submarine and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(3, x, y, ori, p2Board);
    std::cout << "Player two, please enter the X and Y coordinates for the stern of your destroyer and then the orientation in the format: 1 1 N\n";
    std::cin >> x >> y >> ori;
    if (!std::cin) throw std::runtime_error("Invalid Input");
    placeShip(2, x, y, ori, p2Board);
}
