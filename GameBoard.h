#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "res_path.h"

using namespace std;

//struct existed before classes, they can't do inheritance but they hold data
//you can make a new data type
//Could make this a class instead, but include public:
struct Move
{
	int row, col;
};

class GameBoard
{
public:
	static char BLANK;
	static char CROSS;
	static char NAUGHT;

	//reference to the renderer, pointer to renderer
	SDL_Renderer* renderer;
	//reference to the images, load them into the graphics card to draw to the screen
	SDL_Texture * blank, * cross, * naught;

	//2d array
	char board[3][3];
	//board size
	int boardX = 500, boardY = 100;
	//tile size
	int tileSize = 50;
	//player is
	char player = CROSS, opponent = NAUGHT;

	int minimaxCount = 0;

	//functions
	GameBoard(SDL_Renderer* renderer);
	~GameBoard();
	void clearBoard();
	bool setTile(char type, int x, int y);
	void getTileXYBasesOnPixelXY(int pixelX, int pixelY, int& tileX, int& tileY);
	bool checkForClick(SDL_Event& event, char type);
	bool checkForWin(char type);
	bool checkIfAnyPlacesFree();

	void draw();

	//MINIMAX FUNCTIONs
	int evaluate();
	//recursive function
	int minimax(int depth, bool isMax);
	//minimax using alpha beta pruning
	int minimax(int depth, bool isMax, int alpha, int beta);

	Move findBestMove(char type);
};

