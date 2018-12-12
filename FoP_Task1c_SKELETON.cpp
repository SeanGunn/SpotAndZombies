//TODO: change how the text looks (they are to joined up)
//---------------------------------------------------------------------------
//Program: Skeleton for Task 1c – group assignment
//Author: Sean Gunn, Samuel Haque and Tom Hutchins
//Last updated: 10 April 2018
//---------------------------------------------------------------------------


//Go to 'View > Task List' menu to open the 'Task List' pane listing the initial amendments needed to this program


//---------------------------------------------------------------------------
//----- include libraries
//---------------------------------------------------------------------------


//include standard libraries

#include <iostream>    
#include <iomanip> 
#include <conio.h> 
#include <cassert> 
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <fstream>
using namespace std;


//include our own libraries
#include "RandomUtils.h"    //for Seed, Random
#include "ConsoleUtils.h"    //for Clrscr, Gotoxy, etc.



//---------------------------------------------------------------------------
//----- define constants
//---------------------------------------------------------------------------


//defining the size of the grid
const int  SIZEX(25);        //horizontal dimension
const int  SIZEY(15);        //vertical dimension
							 //defining symbols used for display of the grid and content
const char SPOT('@');       //spot
const char SPOTMAD('M');     //spot when pill eaten
const char TUNNEL(' ');        //tunnel
const char WALL('#');        //border
const char ZOMBIE('Z');     //zombies
const char PILL('*');        //pills
const char HOLE('0');       //Hole
							//defining the command letters to move the spot on the maze
const int  UP(72);            //up arrow
const int  DOWN(80);         //down arrow
const int  RIGHT(77);        //right arrow
const int  LEFT(75);        //left arrow
							//defining the other command letters
const char QUIT('Q');        //to end the game
							 //defining publics
string name;
bool canMove = true;
bool eliminateZombies = false;
bool eatPill = false;
bool cheatApplied = false;
bool displayFloatingRules = false;
bool freezeSpot = false;
int highestScore;
int mapLayoutNum;
//stucture for appllling items to grid
struct Item {
	int x, y;
	char symbol;
};

struct gameData {
	int h, l, p, t;
};



//---------------------------------------------------------------------------
//----- run game
//---------------------------------------------------------------------------

int main()
{
	//function declarations (prototypes)
	void startUpScreen();
	void menuScreen(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter);

	//local variable declarations 
	char grid[SIZEY][SIZEX];            //grid for display
	char maze[SIZEY][SIZEX];            //structure of the maze
										//Items position and symbol
	Item spot = { 0, 0, SPOT };
	Item spotEaten = { 0, 0, SPOTMAD };
	Item pills = { 0, 0, PILL };
	Item zombies = { 0, 0, ZOMBIE };
	Item holes = { 0, 0, HOLE };
	string message("");    //current message to player
						   //local variables
	gameData gameDatalevel1;
	gameData gameDatalevel2;
	gameData gameDatalevel3;
	int zombiecounter = 4;
	//TODO: make it equal to level.h/level.p/...
	bool spotMad = false;
	//vectors
	vector<Item> ZOMBIES = { { 0, 0, ZOMBIE },{ 0, 0, ZOMBIE },{ 0, 0, ZOMBIE },{ 0, 0, ZOMBIE } };
	vector<Item> HOLES;
	vector<Item> PILLS;
	//action...
	Seed();                                //seed the random number generator
	SetConsoleTitle("Spot and Zombies Game - FoP 2017-18");
	startUpScreen();
	menuScreen(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter);
	return 0;
}



//---------------------------------------------------------------------------
//----- initialise game state
//---------------------------------------------------------------------------


void initialiseGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool spotMad, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3)
{
	void creatingHolesVector(vector<Item>& HOLES, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3);
	void creatingPillsVector(vector<Item>& PILLS, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3);
	creatingHolesVector(HOLES, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);
	creatingPillsVector(PILLS, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);
	//initialise grid and place spot in middle
	void setInitialMazeStructure(char maze[][SIZEX]);
	void setZombiesInitialCoords(char grid[][SIZEX], vector<Item>& ZOMBIES);
	void setPillInitialCoords(char grid[][SIZEX], vector<Item>& PILLS);
	void setHoleInitialCoords(char grid[][SIZEX], vector<Item>& HOLES);
	void setSpotInitialCoordinates(char grid[][SIZEX], Item& spot);
	void updateGrid(char grid[][SIZEX], const char maze[][SIZEX], const Item spot, const vector<Item>& ZOMBIES, const vector<Item>& PILLS, const vector<Item>& HOLES, const Item spotEaten, bool spotMad);
	setInitialMazeStructure(maze);        //initialise maze
	updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);        //prepare grid
	setZombiesInitialCoords(grid, ZOMBIES);
	updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);        //prepare grid
	setPillInitialCoords(grid, PILLS);
	updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);        //prepare grid
	setHoleInitialCoords(grid, HOLES);
	updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);        //prepare grid
	setSpotInitialCoordinates(grid, spot);
	updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);        //prepare grid
}


void setZombiesInitialCoords(char grid[][SIZEX], vector<Item>& ZOMBIES) {
	int x1 = 0, y1 = 0;
	for (size_t i(0); i < ZOMBIES.size(); ++i)
	{
		switch (i)
		{
		case 0:
			ZOMBIES.at(i).x = 1;
			ZOMBIES.at(i).y = 1;
			break;
		case 1:
			ZOMBIES.at(i).x = SIZEX - 2;
			ZOMBIES.at(i).y = 1;
			break;
		case 2:
			ZOMBIES.at(i).x = 1;
			ZOMBIES.at(i).y = SIZEY - 2;
			break;
		case 3:
			ZOMBIES.at(i).x = SIZEX - 2;
			ZOMBIES.at(i).y = SIZEY - 2;
			break;
		}
	}
}


void setSpotInitialCoordinates(char grid[][SIZEX], Item& spot)//this is the last one create the others first
{
	//set spot coordinates inside the grid at random at beginning of game
	int x1 = 0, y1 = 0;
	x1 = rand() % (SIZEX - 2) + 1;
	y1 = rand() % (SIZEY - 2) + 1;
	while (grid[y1][x1] != TUNNEL) {
		x1 = rand() % (SIZEX - 2) + 1;
		y1 = rand() % (SIZEY - 2) + 1;
	}
	spot.x = x1;
	spot.y = y1;
}


void setPillInitialCoords(char grid[][SIZEX], vector<Item>& PILLS) {
	int x1 = 0, y1 = 0;
	for (size_t a(0); a < PILLS.size(); ++a)
	{
		x1 = rand() % (SIZEX - 2) + 1;
		y1 = rand() % (SIZEY - 2) + 1;
		while (grid[y1][x1] != TUNNEL) {
			x1 = rand() % (SIZEX - 2) + 1;
			y1 = rand() % (SIZEY - 2) + 1;
		}
		PILLS.at(a).x = x1;
		PILLS.at(a).y = y1;
	}
}


void setHoleInitialCoords(char grid[][SIZEX], vector<Item>& HOLES) {
	int x1 = 0, y1 = 0;
	for (size_t a(0); a < HOLES.size(); ++a)
	{
		x1 = rand() % (SIZEX - 2) + 1;
		y1 = rand() % (SIZEY - 2) + 1;
		while (grid[y1][x1] != TUNNEL) {
			x1 = rand() % (SIZEY - 2) + 1;
			y1 = rand() % (SIZEY - 2) + 1;
		}
		HOLES.at(a).x = x1;
		HOLES.at(a).y = y1;
	}
}


void setInitialMazeStructure(char maze[][SIZEX])
{	
	ifstream fin;
	string tostring(int x);
	fin.open("level"+ tostring(mapLayoutNum) +".txt", ios::in);
	
		for (int row(0); row < SIZEY; ++row) {
			for (int col(0); col < SIZEX; ++col) {
				char gridItem = fin.get();
				switch (gridItem) {
				case '#': maze[row][col] = WALL; break;
				case ' ': maze[row][col] = TUNNEL; break;
				case 'Z': maze[row][col] = ZOMBIE; break;
				case '*': maze[row][col] = PILL; break;
				case '0': maze[row][col] = HOLE; break;
				case '/n':
				default: col--; break;
				}
			}
		}
	
	//set the position of the walls in the maze
	//initialise maze configuration
	}

//---------------------------------------------------------------------------
//----- update grid state
//---------------------------------------------------------------------------

void level1(gameData& gameDatalevel1, bool& gameLevel1, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot ) {
	gameLevel1 = true;
	gameDatalevel1.h = 12;
	gameDatalevel1.l = 8;
	gameDatalevel1.p = 8;
	gameDatalevel1.t = 10;
	lifecounter = gameDatalevel1.l;
	pillcounter = gameDatalevel1.p;
	holecounter = gameDatalevel1.h;
	turnsLeftOfMadSpot = gameDatalevel1.t;
	
}

void level2(gameData& gameDatalevel2, bool& gameLevel2, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot) {
	gameLevel2 = true;
	gameDatalevel2.h = 5;
	gameDatalevel2.l = 5;
	gameDatalevel2.p = 5;
	gameDatalevel2.t = 8;
	lifecounter = gameDatalevel2.l;
	pillcounter = gameDatalevel2.p;
	holecounter = gameDatalevel2.h;
	turnsLeftOfMadSpot = gameDatalevel2.t;
	
}

void level3(gameData& gameDatalevel3, bool& gameLevel3, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot) {
	gameLevel3 = true;
	gameDatalevel3.h = 2;
	gameDatalevel3.l = 3;
	gameDatalevel3.p = 2;
	gameDatalevel3.t = 5;
	lifecounter = gameDatalevel3.l;
	pillcounter = gameDatalevel3.p;
	holecounter = gameDatalevel3.h;
	turnsLeftOfMadSpot = gameDatalevel3.t;
	
}

void creatingHolesVector(vector<Item>& HOLES, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3) {
	if (gameLevel1 == true) {
		for (size_t i(0); i < gameDatalevel1.h; ++i) {
			const Item p = { 0,0, HOLE };
			HOLES.push_back(p);
		}
	}
	if (gameLevel2 == true) {
		for (size_t i(0); i < gameDatalevel2.h; ++i) {
			const Item p = { 0,0, HOLE };
			HOLES.push_back(p);
		}
	}
	if (gameLevel3 == true) {
		for (size_t i(0); i < gameDatalevel3.h; ++i) {
			const Item p = { 0,0, HOLE };
			HOLES.push_back(p);
		}
	}
}
void creatingPillsVector(vector<Item>& PILLS, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3) {
	if (gameLevel1 == true) {
		for (size_t i(0); i < gameDatalevel1.h; ++i) {
			const Item p = { 0,0, PILL };
			PILLS.push_back(p);
		}
	}
	if (gameLevel2 == true) {
		for (size_t i(0); i < gameDatalevel2.h; ++i) {
			const Item p = { 0,0, PILL };
			PILLS.push_back(p);
		}
	}
	if (gameLevel3 == true) {
		for (size_t i(0); i < gameDatalevel3.h; ++i) {
			const Item p = { 0,0, PILL };
			PILLS.push_back(p);
		}
	}
}
void updateGrid(char grid[][SIZEX], const char maze[][SIZEX], const Item spot, const vector<Item>& ZOMBIES, const vector<Item>& PILLS, const vector<Item>& HOLES, const Item spotEaten, bool spotMad)
{
	//update grid configuration after each move
	void setMaze(char grid[][SIZEX], const char b[][SIZEX]);
	void placeItem(char grid[][SIZEX], const Item spot, const Item spotEaten, bool spotMad);
	void placeItemZombies(char grid[][SIZEX], const vector<Item>& ZOMBIES);
	void placeItemPills(char grid[][SIZEX], const vector<Item>& PILLS);
	void placeItemHoles(char grid[][SIZEX], const vector<Item>& HOLES);
	setMaze(grid, maze);    //reset the empty maze configuration into grid
	placeItemHoles(grid, HOLES);
	placeItemPills(grid, PILLS);
	placeItemZombies(grid, ZOMBIES);
	placeItem(grid, spot, spotEaten, spotMad);    //set spot in grid
}


void setMaze(char grid[][SIZEX], const char maze[][SIZEX])
{
	//reset the empty/fixed maze configuration into grid
	for (int row(0); row < SIZEY; ++row)
		for (int col(0); col < SIZEX; ++col)
			grid[row][col] = maze[row][col];
}


void placeItem(char grid[][SIZEX], const Item item, const Item spotEaten, bool spotMad)//change back to original since doesn't need vector
{
	if (spotMad == false) {
		//place item at its new position in grid
		grid[item.y][item.x] = item.symbol;
	}
	else {
		grid[item.y][item.x] = spotEaten.symbol;
	}

}



void placeItemZombies(char grid[][SIZEX], const vector<Item>& zombies)
{
	//place item at its new position in grid
	int x1 = 0, y1 = 0;
	if (eliminateZombies == false) {
		for (size_t i(0); i < zombies.size(); ++i)
		{
			grid[zombies.at(i).y][zombies.at(i).x] = zombies.at(i).symbol;
		}
	}
}

void placeItemPills(char grid[][SIZEX], const vector<Item>& PILLS)
{
	//place item at its new position in grid
	for (size_t i(0); i < PILLS.size(); ++i)
	{
		grid[PILLS.at(i).y][PILLS.at(i).x] = PILLS.at(i).symbol;
	}
}


void eatAllPills(vector<Item>& PILLS) {
	size_t pillsMaxSize;
	pillsMaxSize = PILLS.size();
	for (size_t i(0); i < pillsMaxSize; ++i) {
		PILLS.pop_back();
	}
}


void placeItemHoles(char grid[][SIZEX], const vector<Item>& HOLES)
{
	//place item at its new position in grid
	for (size_t i(0); i < HOLES.size(); ++i)
	{
		grid[HOLES.at(i).y][HOLES.at(i).x] = HOLES.at(i).symbol;
	}
}

//---------------------------------------------------------------------------
//----- move items on the grid
//---------------------------------------------------------------------------

void updateGameData(const char g[][SIZEX], Item& spot, const int key, string& mess, int& lifecounter, int& pillcounter, int& zombiecounter, vector<Item>& PILLS, vector<Item>& ZOMBIES, vector<Item>& HOLES, int& turnsLeftOfMadSpot, bool& spotMad)
{
	//move spot in required direction
	bool isArrowKey(const int k);
	void setKeyDirection(int k, int& dx, int& dy);
	assert(isArrowKey(key));
	//reset message to blank
	mess = "                                         ";        //reset message to blank
															   //calculate direction of movement for given key
	int dx(0), dy(0);
	int enterOnce(0);
	setKeyDirection(key, dx, dy);
	//check new target position in grid and update game data (incl. spot coordinates) if move is possible
	if ((zombiecounter >= 1) && (lifecounter >= 1)) {
		switch (g[spot.y + dy][spot.x + dx])
		{            //...depending on what's on the target position in grid...
		case TUNNEL:        //can move
			if (lifecounter != 0) {
				if (spotMad == true) {
					--turnsLeftOfMadSpot;
					if (turnsLeftOfMadSpot == 0) {
						spotMad = false;
					}
				}
				spot.y += dy;    //go in that Y direction
				spot.x += dx;    //go in that X direction
			}
			break;
		case WALL:          //hit a wall and stay there
			mess = "CANNOT GO THERE!";
			break;
		case PILL:
			for (size_t i(0); i < PILLS.size(); ++i)
			{
				if ((spot.x + dx == PILLS.at(i).x) && (spot.y + dy == PILLS.at(i).y)) {
					PILLS.erase(PILLS.begin() + i);
				}
			}
			spot.y += dy;
			spot.x += dx;
			++lifecounter;
			--pillcounter;
			turnsLeftOfMadSpot = 10;
			spotMad = true;
			break;
		case HOLE:
			if (lifecounter == 0) {
				lifecounter = 0;
			}
			else {
				if (spotMad == true) {
					--turnsLeftOfMadSpot;
				}
				spot.y += dy;
				spot.x += dx;
				--lifecounter;
			}
			break;
		case ZOMBIE:
			if (lifecounter == 0) {
				lifecounter = 0;
			}
			else {
				if (spotMad == true) {
					--turnsLeftOfMadSpot;
				}
				for (size_t i(0); i < ZOMBIES.size(); ++i)
				{
					if ((spot.x + dx == ZOMBIES.at(i).x) && (spot.y + dy == ZOMBIES.at(i).y)) {
						switch (i)
						{
						case 0:
							ZOMBIES.at(i).x = 1;
							ZOMBIES.at(i).y = 1;
							break;
						case 1:
							ZOMBIES.at(i).x = SIZEX - 2;
							ZOMBIES.at(i).y = 1;
							break;
						case 2:
							ZOMBIES.at(i).x = 1;
							ZOMBIES.at(i).y = SIZEY - 2;
							break;
						case 3:
							ZOMBIES.at(i).x = SIZEX - 2;
							ZOMBIES.at(i).y = SIZEY - 2;
							break;
						}
					}
				}
				spot.y += dy;
				spot.x += dx;
				--lifecounter;
			}
			break;
		}
		if ((canMove == true) && (spotMad == false)) {
			for (size_t i(0); i < ZOMBIES.size(); ++i)
			{
				int d(1);
				if (spot.x > ZOMBIES.at(i).x) {
					if (g[ZOMBIES.at(i).y][ZOMBIES.at(i).x + d] != WALL) {
						ZOMBIES.at(i).x += d;
					}
					//bool statement that checks prevous zombies if true (if two +d) then = true
				}
				if (spot.x < ZOMBIES.at(i).x) {
					if (g[ZOMBIES.at(i).y][ZOMBIES.at(i).x - d] != WALL) {
						ZOMBIES.at(i).x -= d;
					}
				}
				if (spot.y > ZOMBIES.at(i).y) {
					if (g[ZOMBIES.at(i).y + d][ZOMBIES.at(i).x] != WALL) {
						ZOMBIES.at(i).y += d;
					}
				}
				if (spot.y < ZOMBIES.at(i).y) {
					if (g[ZOMBIES.at(i).y - d][ZOMBIES.at(i).x] != WALL) {
						ZOMBIES.at(i).y -= d;
					}
				}
				for (size_t a(0); a < HOLES.size(); ++a) {
					if ((ZOMBIES.at(i).x == HOLES.at(a).x) && (ZOMBIES.at(i).y == HOLES.at(a).y)) {
						if ((ZOMBIES.at(i).x == HOLES.at(a).x) && (ZOMBIES.at(i).y == HOLES.at(a).y) && (zombiecounter == 1)) {
							--zombiecounter;
						}
						else {
							ZOMBIES.erase(ZOMBIES.begin() + i);
							--zombiecounter;
						}
					}
				}
			}

		}
		if ((canMove == true) && (spotMad == true)) {
			for (size_t i(0); i < ZOMBIES.size(); ++i)
			{
				int d(1);

				if (spot.x > ZOMBIES.at(i).x) {
					if (g[ZOMBIES.at(i).y][ZOMBIES.at(i).x - d] != WALL) {
						ZOMBIES.at(i).x -= d;
					}

				}
				if (spot.x < ZOMBIES.at(i).x) {
					if (g[ZOMBIES.at(i).y][ZOMBIES.at(i).x + d] != WALL) {
						ZOMBIES.at(i).x += d;
					}

				}
				if (spot.y > ZOMBIES.at(i).y) {
					if (g[ZOMBIES.at(i).y - d][ZOMBIES.at(i).x] != WALL) {
						ZOMBIES.at(i).y -= d;
					}

				}
				if (spot.y < ZOMBIES.at(i).y) {
					if (g[ZOMBIES.at(i).y + d][ZOMBIES.at(i).x] != WALL) {
						ZOMBIES.at(i).y += d;
					}


				}
				for (size_t a(0); a < HOLES.size(); ++a) {
					if ((ZOMBIES.at(i).x == HOLES.at(a).x) && (ZOMBIES.at(i).y == HOLES.at(a).y)) {
						if ((ZOMBIES.at(i).x == HOLES.at(a).x) && (ZOMBIES.at(i).y == HOLES.at(a).y) && (zombiecounter == 1)) {
							--zombiecounter;
						}
						else {
							ZOMBIES.erase(ZOMBIES.begin() + i);
							--zombiecounter;
						}
					}
				}
			}
		}
	}
	//TODO:add if zombies collide they go back to their starts whileloop
}

//---------------------------------------------------------------------------
//----- process key
//---------------------------------------------------------------------------

void setKeyDirection(const int key, int& dx, int& dy)
{
	//calculate direction indicated by key
	bool isArrowKey(const int k);
	assert(isArrowKey(key));
	switch (key)    //...depending on the selected key...
	{
	case LEFT:      //when LEFT arrow pressed...
		dx = -1;    //decrease the X coordinate
		dy = 0;
		break;
	case RIGHT:     //when RIGHT arrow pressed...
		dx = +1;    //increase the X coordinate
		dy = 0;
		break;
	case UP:     //when UP arrow pressed...
		dx = 0;
		dy = -1; //decrease the y coorinate
		break;
	case DOWN:     //when DOWN arrow pressed...
		dx = 0;
		dy = +1; //increase the y coorinate
		break;
	}
}


int getKeyPress()
{
	//get key or command (in uppercase) selected by user
	//KEEP THIS FUNCTION AS GIVEN
	int keyPressed;
	keyPressed = _getch();            //read in the selected arrow key or command letter
	while (keyPressed == 224)         //ignore symbol following cursor key
		keyPressed = _getch();
	return keyPressed;        //return it in uppercase 
}


bool isArrowKey(const int key)
{
	//check if the key pressed is an arrow key (also accept 'K', 'M', 'H' and 'P')
	return (key == LEFT) || (key == RIGHT) || (key == UP) || (key == DOWN);
}

bool wantsToQuit(const int key)
{
	//check if the user wants to quit (when key is 'Q' or 'q')
	return key == QUIT;
}


//---------------------------------------------------------------------------
//----- display info on screen
//---------------------------------------------------------------------------


string tostring(int x)
{
	//convert an integer to a string
	std::ostringstream os;
	os << x;
	return os.str();
}

string tostring(char x)
{
	//convert a char to a string
	std::ostringstream os;
	os << x;
	return os.str();
}

void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message)
{
	//display a string using specified colour at a given position 
	Gotoxy(x, y);
	SelectBackColour(backColour);
	SelectTextColour(textColour);
	cout << message;
}

void paintGame(const char g[][SIZEX], string mess, int& lifecounter, int& pillcounter, int& zombiecounter)
{
	//display game title, messages, maze, spot and other items on screen
	string tostring(char x);
	string tostring(int x);
	string GetTime();
	string GetDate();
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	void paintGrid(const char g[][SIZEX]);
	//TODO: Change the colour of the messages
	//display game title
	showMessage(clBlack, clYellow, 0, 0, "___GAME___");
	//time and date
	showMessage(clDarkGrey, clYellow, 40, 12, "DATE: " + GetDate());
	showMessage(clDarkGrey, clYellow, 40, 13, "TIME: " + GetTime());
	//showMessage(clWhite, clRed, 40, 0, "FoP Task 1c: February 2018");
	//display menu options available
	showMessage(clRed, clYellow, 40, 2, "TO MOVE USE KEYBOARD ARROWS ");
	showMessage(clRed, clYellow, 40, 3, "TO QUIT ENTER 'Q'           ");
	showMessage(clRed, clYellow, 40, 4, "AMOUNT OF LIVES LEFT: " + tostring(lifecounter) + "     ");
	showMessage(clRed, clYellow, 40, 5, "AMOUNT OF PILLS LEFT: " + tostring(pillcounter) + "     ");
	showMessage(clRed, clYellow, 40, 6, "AMOUNT OF ZOMBIES LEFT: " + tostring(zombiecounter) + "    ");
	showMessage(clRed, clYellow, 40, 7, "TO SEE THE INFORMATION ABOUT THE GAME PRESS I");
	//print auxiliary messages if any
	showMessage(clBlack, clWhite, 40, 8, mess);    //display current message
												   //display grid contents
	paintGrid(g);
}


void paintGrid(const char g[][SIZEX])
{
	//display grid content on screen
	SelectBackColour(clBlack);
	SelectTextColour(clWhite);
	Gotoxy(0, 2);
	for (int row(0); row < SIZEY; ++row)
	{
		for (int col(0); col < SIZEX; ++col) {
			switch (g[row][col]) {
			case WALL:
				SelectTextColour(clCyan);
				break;
			case ZOMBIE:
				SelectTextColour(clDarkGreen);
				break;
			case PILL:
				SelectTextColour(clMagenta);
				break;
			case HOLE:
				SelectTextColour(clGrey);
				break;
			case SPOT:
				SelectTextColour(clBlue);
				break;
			case SPOTMAD:
				SelectTextColour(clRed);
				break;
			}
			cout << g[row][col];    //output cell content
		}
		cout << endl;
	}
}

void startUpScreen() {
	//TODO: Show your course, your group number and names on screen
	//local variables
	string GetTime();
	string GetDate();
	//drawing startup
	showMessage(clDarkGrey, clYellow, 10, 4, "--------------------");
	showMessage(clDarkGrey, clYellow, 10, 5, "| SPOT AND ZOMBIES |");
	showMessage(clDarkGrey, clYellow, 10, 6, "--------------------");
	showMessage(clDarkGrey, clYellow, 40, 4, "DATE: " + GetDate());
	showMessage(clDarkGrey, clYellow, 40, 5, "TIME: " + GetTime());
	showMessage(clDarkGrey, clYellow, 40, 7, "TO MOVE USE KEYBOARD AROWS");
	showMessage(clDarkGrey, clYellow, 40, 8, "TO FREEZE ZOMBIES PRESS 'F'");
	showMessage(clDarkGrey, clYellow, 40, 9, "TO KILL ZOMBIES PRESS 'X'");
	showMessage(clDarkGrey, clYellow, 40, 10, "TO QUIT ENTER 'Q'");
	showMessage(clDarkGrey, clYellow, 10, 9, "ENTER YOUR NAME:");
	cin >> name;
}

void menuScreen(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter) {
	void selectingLevel(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3);
	void Clrscr();
	void highscoreMenu(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter);
	void displayHighScore();
	void displayRules(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter);
	int highScore();
	bool isArrowKey(const int k);
	int  getKeyPress();
	string message("");
	bool gameLevel1 = false;
	bool gameLevel2 = false;
	bool gameLevel3 = false;
	Clrscr(); //clear screen
	showMessage(clDarkGrey, clYellow, 10, 4, "Press the P key (for Play Game) – (re-)start the game");
	showMessage(clDarkGrey, clYellow, 10, 5, "Press the S key (for See Score) – display the player’s current score");
	showMessage(clDarkGrey, clYellow, 10, 6, "Press the R key (for See Rules) – show the rules of the game");
	showMessage(clDarkGrey, clYellow, 10, 7, "Press the Q key (for Quit Game) – terminate the application");
	int menu;
	do {
		menu = getKeyPress();
		menu = toupper(menu);
		if (menu == 'P') {
			selectingLevel(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter, gameLevel1, gameLevel2, gameLevel3);
		}
		else if (menu == 'S') {
			Clrscr(); //clear screen
			highscoreMenu(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter);
		}
		else if (menu == 'R') {
			Clrscr(); //clear screen
			displayRules(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter);
		}
		else
			message = "INVALID KEY!";    //set 'Invalid key' message
	} while (!wantsToQuit(menu));
}

void displayRules(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter) {
	void menuScreen(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter);
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	string message("");
	showMessage(clDarkGrey, clYellow, 10, 4, "At the start of the game Spot is given 3 lives, the player moves Spot using the arrow keys on the keyboard. ");
	showMessage(clDarkGrey, clYellow, 10, 5, "Spot can only be moved vertically or horizontally(up, down, left or right), one step at any time.");
	showMessage(clDarkGrey, clYellow, 10, 6, "After each of Spot’s moves the zombies chase him, homing in on him when it is their turn to move.");
	showMessage(clDarkGrey, clYellow, 10, 7, "They can move vertically, horizontally or on a diagonal(to any one of the 8 cells adjacent to their");
	showMessage(clDarkGrey, clYellow, 10, 8, "position) inside the grid, but they move blindly unable to avoid obstacles(such as holes or other zombies) in their paths");
	showMessage(clDarkGrey, clYellow, 10, 9, "The game ends when (a) the player decides to quit the game, (b) Spot runs out of lives or (c) there are no more zombies on the grid and all pills have been eaten.");
	showMessage(clDarkGrey, clYellow, 10, 10, "Press the R key (for Return to menu) - to change your menu pick");
	showMessage(clDarkGrey, clYellow, 10, 11, "Press the Q key (for Quit Game) – terminate the application");
	int returntoMenu;
	do {
		returntoMenu = getKeyPress();
		returntoMenu = toupper(returntoMenu);
		if (returntoMenu == 'R') {
			menuScreen(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter);
		}
		else
			message = "INVALID KEY!";    //set 'Invalid key' message
	} while (!wantsToQuit(returntoMenu));
}

void highscoreMenu(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter) {
	void menuScreen(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter);
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	int highScore();
	void displayHighScore();
	string message("");
	highestScore = highScore();
	displayHighScore();
	showMessage(clDarkGrey, clYellow, 10, 11, "Press the R key (for Return to menu) - to change your menu pick");
	showMessage(clDarkGrey, clYellow, 10, 12, "Press the Q key (for Quit Game) – terminate the application");
	int returntoMenu;
	do {
		returntoMenu = getKeyPress();
		returntoMenu = toupper(returntoMenu);
		if (returntoMenu == 'R') {
			menuScreen(gameDatalevel1, gameDatalevel2, gameDatalevel3, grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, zombiecounter);
		}
		else
			message = "INVALID KEY!";    //set 'Invalid key' message
	} while (!wantsToQuit(returntoMenu));
}

int highScore() {
	int highestScore;
	ifstream fin;
	fin.open(name + ".txt", ios::in);
	if (fin.fail()) {
		highestScore = -1;
	}
	else {
		fin >> highestScore;
	}
	fin.close();
	return highestScore;
}


void recordLives(int lifecounter) {
	ofstream ofstream;
	ofstream.open(name + ".txt", ios::out);
	ofstream << lifecounter;
	ofstream.close();
}


void displayHighScore() {
	string tostring(int highestScore);
	showMessage(clRed, clYellow, 40, 9, "Name: " + name);
	showMessage(clRed, clYellow, 40, 10, "Highscore: " + tostring(highestScore));
}



void endProgram(int lifecounter)
{
	void recordLives(int lifecounter);
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	if (cheatApplied == false)
	{
		recordLives(lifecounter);
	}
	showMessage(clRed, clYellow, 40, 8, "");
	system("pause");    //hold output screen until a keyboard key is hit
}

void selectingLevel(gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3, char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& zombiecounter, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3) {//TODO:ADD THE REST THEN ADD TO PREV
	void level1(gameData& gameDatalevel1, bool& gameLevel1, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot);
	void level2(gameData& gameDatalevel2, bool& gameLevel2, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot);
	void level3(gameData& gameDatalevel3, bool& gameLevel3, int& lifecounter, int& pillcounter, int& holecounter, int& turnsLeftOfMadSpot);
	void startTheGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& lifecounter, int& pillcounter, int& zombiecounter, int& holecounter, int& turnsLeftOfMadSpot, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3);
	void Clrscr();
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	int key;                            //current key selected by player
	string message("");
	Clrscr(); //clear screen
	int lifecounter;
	int pillcounter;
	int holecounter;
	int turnsLeftOfMadSpot;
	showMessage(clDarkGrey, clYellow, 10, 10, "Press the 1, key (for Level 1) - to enter Easy");
	showMessage(clDarkGrey, clYellow, 10, 11, "Press the 2, key (for Level 2) - to enter Medium");
	showMessage(clDarkGrey, clYellow, 10, 12, "Press the 3, key (for Level 3) - to enter Hard");
	showMessage(clDarkGrey, clYellow, 10, 13, "Press the Q key (for Quit Game) – terminate the application");
	do {
		key = getKeyPress();     //read in  selected key: arrow or letter command
		key = toupper(key);
		if (key == '1') {
			mapLayoutNum = 1;
			level1(gameDatalevel1, gameLevel1, lifecounter, pillcounter, holecounter, turnsLeftOfMadSpot);
			startTheGame(grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, lifecounter, pillcounter, zombiecounter, holecounter, turnsLeftOfMadSpot, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);
			
		}//TODO:HERE
		else if (key == '2') {
			mapLayoutNum = 2;
			level2(gameDatalevel2, gameLevel2, lifecounter, pillcounter, holecounter, turnsLeftOfMadSpot);
			startTheGame(grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, lifecounter, pillcounter, zombiecounter, holecounter, turnsLeftOfMadSpot, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);
			
		}
		else if (key == '3') {
			mapLayoutNum = 3;
			level3(gameDatalevel3, gameLevel3, lifecounter, pillcounter, holecounter, turnsLeftOfMadSpot);
			startTheGame(grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, lifecounter, pillcounter, zombiecounter, holecounter, turnsLeftOfMadSpot, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);
			
		}
		else
			message = "INVALID KEY!";    //set 'Invalid key' message
	} while (!wantsToQuit(key));        //while user does not want to quit
}

void startTheGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zombies, Item& pills, Item& holes, vector<Item>& ZOMBIES, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool& spotMad, int& lifecounter, int& pillcounter, int& zombiecounter, int& holecounter, int& turnsLeftOfMadSpot, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3) {
	void Clrscr();
	void displayHighScore();
	int highScore();
	void initialiseGame(char g[][SIZEX], char m[][SIZEX], Item& spot, Item& ZOMBIES, Item& pills, Item& holes, vector<Item>& zombies, vector<Item>& PILLS, vector<Item>& HOLES, Item& spotEaten, bool spotMad, bool& gameLevel1, bool& gameLevel2, bool& gameLevel3, gameData& gameDatalevel1, gameData& gameDatalevel2, gameData& gameDatalevel3);
	void paintGame(const char g[][SIZEX], string mess, int& lifecounter, int& pillcounter, int& zombiecounter);
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	void updateGameData(const char g[][SIZEX], Item& spot, const int key, string& mess, int& lifecounter, int& pillcounter, int& zombiecounter, vector<Item>& PILLS, vector<Item>& zombies, vector<Item>& HOLES, int& turnsLeftOfMadSpot, bool& spotMad);
	void updateGrid(char grid[][SIZEX], const char maze[][SIZEX], const Item spot, const vector<Item>& zombies, const vector<Item>& PILLS, const vector<Item>& HOLES, const Item spotEaten, bool spotMad);
	void eatAllPills(vector<Item>& PILLS);
	void endProgram(int lifecounter);
	string message("");
	Clrscr(); //clear screen
	initialiseGame(grid, maze, spot, zombies, pills, holes, ZOMBIES, PILLS, HOLES, spotEaten, spotMad, gameLevel1, gameLevel2, gameLevel3, gameDatalevel1, gameDatalevel2, gameDatalevel3);    //initialise grid (incl. walls and spot)
	paintGame(grid, message, lifecounter, pillcounter, zombiecounter);            //display game info, modified grid and messages
	highestScore = highScore();
	displayHighScore();
	int key;                            //current key selected by player
	do {
		key = getKeyPress();     //read in  selected key: arrow or letter command
		key = toupper(key);
		if (key == 'F') {
			if (canMove == true)
			{
				canMove = false;
				updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);
			}
			else {
				canMove = true;
			}
			cheatApplied = true;
		}
		else if (key == 'X') {
			if (eliminateZombies == false) {
				eliminateZombies = true;
				updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);
			}
			cheatApplied = true;
		}
		else if (key == 'E') {
			if (eatPill == false) {
				eatAllPills(PILLS);
				lifecounter = lifecounter + pillcounter;
				pillcounter = 0;
				updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);
			}
			cheatApplied = true;
		}
		else if (key == 'I') {
			if (displayFloatingRules == false) {
				displayFloatingRules = true;
				showMessage(clBlue, clBlack, 35, 15, "INFORMATION:                                                     ");
				showMessage(clBlue, clRed, 35, 16, "THE OBJECTIVE OF THE GAME IS TO SURVIVE THE WRATH OF THE ZOMBIES ");
				showMessage(clBlue, clRed, 35, 17, "TO DO THIS, KILL THE ZOMBIES BY MAKING THEM TRAVEL INTO HOLES,'0'");
				showMessage(clBlue, clRed, 35, 18, "IF YOU ARE IN TROUBLE MOVE TOWARDS THE MAGIC PILLS ,'*'          ");
				showMessage(clBlue, clRed, 35, 19, "EAT THEM TO MAKE THE ZOMBIES WALK AWAY FROM YOU                  ");
				showMessage(clBlue, clRed, 35, 20, "MAGIC PILLS ONLY LAST FOR 10 MOVES THOUGH SO PLAN WISELY         ");
				showMessage(clBlue, clRed, 35, 21, "TO RETURN TO THE GAME PRESS I AGAIN                              ");
				freezeSpot = true;
				canMove = false;
			}
			else {
				displayFloatingRules = false;
				showMessage(clDarkGrey, clYellow, 35, 15, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 16, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 17, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 18, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 19, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 20, "                                                                 ");
				showMessage(clDarkGrey, clYellow, 35, 21, "                                                                 ");
				freezeSpot = false;
				canMove = true;
			}
		}
		else {
			if (freezeSpot == false){
				if (isArrowKey(key))
				{
					updateGameData(grid, spot, key, message, lifecounter, pillcounter, zombiecounter, PILLS, ZOMBIES, HOLES, turnsLeftOfMadSpot, spotMad);        //move spot in that direction
					updateGrid(grid, maze, spot, ZOMBIES, PILLS, HOLES, spotEaten, spotMad);                    //update grid information
				}
				else
					message = "INVALID KEY!";    //set 'Invalid key' message
			}
		}
		paintGame(grid, message, lifecounter, pillcounter, zombiecounter);        //display game info, modified grid and messages
	} while (!wantsToQuit(key));        //while user does not want to quit
	endProgram(lifecounter);                        //display final message
}