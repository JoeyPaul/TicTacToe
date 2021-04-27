#include <iostream>
#include <string>
#include <SDL.h>	
#include "GameBoard.h"

using namespace std;

int main(int argc, char** argv)
{
	//ERRORS
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		system("pause");
		return 1; //back in the day, when 0 was returned it meant everything went well
		          //and if 1 was returned something went wrong
	}
	//create window and check if it is there or not
	SDL_Window* window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		cout << "Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}
	//creates renderer and checks if it is working
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		system("pause");
		return 1;
	}
	//make the gameboard object, pass it the renderer
	GameBoard gameBoard(renderer);

	bool quit = false;
	//---------------------game loop-----------------//
	while (!quit)
	{
		//get user input
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//user clicks close button
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN)
			{
				//user presses escape key
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					quit = true;
				}
				//press enter
				if (e.key.keysym.scancode == SDL_SCANCODE_RETURN)
				{
					gameBoard.clearBoard();
				}
			}
			//if player clicks and can place down a CROSS
			if (gameBoard.checkForClick(e, GameBoard::CROSS))
			{
				//AI Logic 
				Move aiMove = gameBoard.findBestMove(gameBoard.opponent);
				if(aiMove.row != -1 && aiMove.col != -1)
				{
					gameBoard.setTile(gameBoard.opponent, aiMove.row, aiMove.col);
				}
			}
		}

		//----------------OUTPUT------------------//

		//render background color (green)
		SDL_SetRenderDrawColor(renderer, 163, 241, 158, 255); //rgba(0-255)
		//uses the draw color to fill the whole screen
		SDL_RenderClear(renderer);

		//draw gameboard to screen
		gameBoard.draw();

		//swaps the buffers
		SDL_RenderPresent(renderer);
	}

	return 0;
}