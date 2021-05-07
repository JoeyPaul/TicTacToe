//references:
// I found a cool SDL ttf example of rendering text to the screen
// in real time that you input. So I used it as a bit of a base
// once I got my head around how it worked
//https://thenumbat.github.io/cpp-course/sdl2/07/07.html
//
#include <iostream>
#include <string>
#include <SDL.h>	
#include "GameBoard.h"
#include <SDL_ttf.h>

using namespace std;

void makeButton(int x, int y, int w, int h, const char* buttonName);
void setHeadingText(string inputString);
void setSecondaryText(int x, int y, int w, int h, string inputString);
void DisplayMainMenu();
int play(bool vsCPU, int playerScore, int cpuScore);

enum SCREENS {
	MAIN_MENU,
	VS_PLAYER,
	VS_CPU,
	SCORES,
	EXIT
};


bool init();
void quitSDL();
bool menuLoop();

// Pointers to our window, renderer, texture, and font
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture, * text;
TTF_Font* font;
string input;

int main(int argc, char** args) {
	
	bool quit = false;
	SDL_Event event;

	//check for errors
	//Makes sure the program is ready
	if (!init()) 
	{
		system("pause");
		return 1;
	}

	while (SDL_PollEvent(&event) != 0)
	{
		//user clicks close button
		//if (event.type == SDL_QUIT)
		//	quit = true;
		//if (event.type == SDL_KEYDOWN)
		//{
		//	//user presses escape key
		//	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		//	{
		//		quit = true;
		//		quitSDL();
		//		return 0;
		//	}
		//}
		

		while (menuLoop())
		{
			input = "TIK-TAC-TOE";
			// wait before processing the next frame
			
			SDL_Delay(10);
		

		}
		break;
	}

	quitSDL();
	return 0;
}

//SORRY THIS FUNCTION IS MASSIVE
//It was where I figured out most my code
//If I could start this project over it would be so much cleaner. lol
//This loop creates the main menu and displays it 
bool menuLoop() 
{
	static const unsigned char* keys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	SDL_Rect dest;
	// Clear the window to Green
	SDL_SetRenderDrawColor(renderer, 163, 241, 158, 255);
	SDL_RenderClear(renderer);

	//Event loop
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT)
			return false;
		if (e.type == SDL_KEYDOWN)
		{
			//user presses escape key
			if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			{
				return false; //break out of this function
			}
		}
		//checking for mouse input
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			//if left mouse click
			if (e.button.button = SDL_BUTTON_LEFT)
			{
				//MAIN MENU CLICKS  
				//checking button x/y position + width/height 
				//if you click VS PLAYER
				if (e.button.x >= 180 && e.button.x <= 480 &&
					e.button.y >= 130 && e.button.y <= 210)
				{
					play(false, 1, 1);
				}
				//if you click VS CPU
				if (e.button.x >= 180 && e.button.x <= 480 &&
					e.button.y >= 220 && e.button.y <= 300)
				{
					play(true,1, 1); //TO DO SET UP SCORE
				}
				//if you click SCORE
				if (e.button.x >= 180 && e.button.x <= 480 &&
					e.button.y >= 310 && e.button.y <= 390)
				{
					//I WILL HAVE IT SAVE TO A TXT FILE
					//NEED TO SET UP A TXT FILE READER
				}
				//if you click QUIT
				if (e.button.x >= 250 && e.button.x <= 400 &&
					e.button.y >= 400 && e.button.y <= 440)
				{
					return false;
				}
			}
		}
		
		// commented out event that did real time text input
		/*switch (e.type) {
		case SDL_QUIT:
			return false;*/
		/*case SDL_TEXTINPUT:
			input += e.text.text;
			break;*/
		//case SDL_MOUSEBUTTONDOWN:
		//	/*if (e.key.keysym.sym == SDLK_BACKSPACE && input.size()) {
		//		input.pop_back();
		//	}*/
	}

	// Render texture
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_Color foreground = { 0, 0, 0 };
	//this cool part is from the reference, it was meant for keyboard input
	//so you can just type and it is written on the screen in real time
	//you just have to add the event that is commented out above
	if (input.size()) {
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
		text = SDL_CreateTextureFromSurface(renderer, text_surf);
		dest.x = 320 - (text_surf->w / 2.0f);
		dest.y = 25;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
		SDL_RenderCopy(renderer, text, NULL, &dest);
		SDL_DestroyTexture(text);
		SDL_FreeSurface(text_surf);
	}

	//Draw buttons
	//the long way sorry (this is where I figured out the logic)
	//VS PLAYER
	SDL_Rect rect1;
	rect1.x = 180;
	rect1.y = 130;
	rect1.w = 300;
	rect1.h = 80;
	SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
	SDL_RenderDrawRect(renderer, &rect1);
	SDL_RenderFillRect(renderer, &rect1);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Surface* text_VSPlayer = TTF_RenderText_Solid(font, "VS PLAYER", foreground);
	text = SDL_CreateTextureFromSurface(renderer, text_VSPlayer);
	dest.x = 225;
	dest.y = 150;
	dest.w = text_VSPlayer->w / 2;
	dest.h = text_VSPlayer->h / 2;
	SDL_RenderCopy(renderer, text, NULL, &dest);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_VSPlayer);
	//VS COM
	SDL_Rect rect2;
	rect2.x = 180;
	rect2.y = 220;
	rect2.w = 300;
	rect2.h = 80;
	SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
	SDL_RenderDrawRect(renderer, &rect2);
	SDL_RenderFillRect(renderer, &rect2);
	//TEXT
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Surface* text_VSCOM = TTF_RenderText_Solid(font, "VS CPU", foreground);
	text = SDL_CreateTextureFromSurface(renderer, text_VSCOM);
	dest.x = 255;
	dest.y = 240;
	dest.w = text_VSCOM->w / 2;
	dest.h = text_VSCOM->h / 2;
	SDL_RenderCopy(renderer, text, NULL, &dest);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_VSCOM);
	//SCORES
	SDL_Rect rect3;
	rect3.x = 180;
	rect3.y = 310;
	rect3.w = 300;
	rect3.h = 80;
	SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
	SDL_RenderDrawRect(renderer, &rect3);
	SDL_RenderFillRect(renderer, &rect3);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Surface* text_Score = TTF_RenderText_Solid(font, "Scores", foreground);
	text = SDL_CreateTextureFromSurface(renderer, text_Score);
	dest.x = 265;
	dest.y = 330;
	dest.w = text_Score->w / 2;
	dest.h = text_Score->h / 2;
	SDL_RenderCopy(renderer, text, NULL, &dest);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_Score);
	//QUIT
	SDL_Rect rect4;
	rect4.x = 250;
	rect4.y = 400;
	rect4.w = 150;
	rect4.h = 40;
	SDL_SetRenderDrawColor(renderer, 200, 255, 200, 255);
	SDL_RenderDrawRect(renderer, &rect4);
	SDL_RenderFillRect(renderer, &rect4);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Surface* text_Quit = TTF_RenderText_Solid(font, "Quit Game", foreground);
	text = SDL_CreateTextureFromSurface(renderer, text_Quit);
	dest.x = 265;
	dest.y = 407;
	dest.w = text_Quit->w / 3;
	dest.h = text_Quit->h / 3;
	SDL_RenderCopy(renderer, text, NULL, &dest);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_Quit);
	// Update window
	SDL_RenderPresent(renderer);

	return true;
}

int play(bool vsCPU, int playerScore, int cpuScore)
{
	////ERRORS
	//if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	//{
	//	cout << "Error: " << SDL_GetError() << endl;
	//	system("pause");
	//	return 1; //back in the day, when 0 was returned it meant everything went well
	//			  //and if 1 was returned something went wrong
	//}
	////create window and check if it is there or not
	//SDL_Window* window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_CENTERED,
	//	SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	//if (window == NULL)
	//{
	//	cout << "Error: " << SDL_GetError() << endl;
	//	SDL_Quit();
	//	system("pause");
	//	return 1;
	//}
	////creates renderer and checks if it is working
	//SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
	//	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//if (renderer == NULL)
	//{
	//	cout << "Error: " << SDL_GetError() << endl;
	//	SDL_DestroyWindow(window);
	//	SDL_Quit();
	//	system("pause");
	//	return 1;
	//}
	//make the gameboard object, pass it the renderer

	GameBoard gameBoard(renderer);
	//while youlose is false the ai and player input will work
	bool stopInput = false;
	bool quit = false;
	bool player2Turn = false;
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
					//reset board
					gameBoard.clearBoard();
					stopInput = false;
					SDL_SetRenderDrawColor(renderer, 163, 241, 158, 255);
					SDL_RenderClear(renderer);
				}
				
			
			}
			//BUTTONS
			//if the player clicks the buttons quit or playagain
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				//if left mouse click
				if (e.button.button = SDL_BUTTON_LEFT)
				{
					//PLAY CLICKS  
					//if you QUIT
					if (e.button.x >= 30 && e.button.x <= 180 &&
						e.button.y >= 410 && e.button.y <= 450)
					{
						return 0;
					}
					//play again
					if (e.button.x >= 460 && e.button.x <= 610 &&
						e.button.y >= 410 && e.button.y <= 450)
					{
						//resets board
						gameBoard.clearBoard();
						stopInput = false;
						SDL_SetRenderDrawColor(renderer, 163, 241, 158, 255);
						SDL_RenderClear(renderer);
						
					}
				}
			}
			//PLAYER INPUT + AI LOGIC
			//It is player 1's turn to move
			if (!player2Turn)
			{
				//if player one clicks on the board
				if (gameBoard.checkForClick(e, GameBoard::CROSS, stopInput))
				{
					//is there a CPU?
					if (vsCPU)
					{
						//AI Logic 
						Move aiMove = gameBoard.findBestMove(gameBoard.opponent);
						if (aiMove.row != -1 && aiMove.col != -1)
						{
							if (stopInput == false)
							{
								gameBoard.setTile(gameBoard.opponent, aiMove.row, aiMove.col);
							}

						}
					}
					else //There isn't a CPU, so it is player 2's turn
					player2Turn = gameBoard.player2Activated();
				}
				
			}//player 2's turn
			if (!vsCPU && player2Turn)
			{
				if (gameBoard.checkForClick(e, GameBoard::NAUGHT, stopInput))
					player2Turn = false;//turn off player 2's turn after they go 
				
			}
			//SCORING + WINS/LOSSES
			//VS CPU
			if (vsCPU)
			{
				//Check if player wins
				if (gameBoard.checkForWin(GameBoard::CROSS))
				{
					setSecondaryText(280, 320, 100, 30, "You Win!");
					playerScore++;
	                //stop input so that you can't get a win after you lose.
					//(which is sometimes possible)
					stopInput = true;
				}
				//CPU wins
				if (gameBoard.checkForWin(GameBoard::NAUGHT))
				{
					setSecondaryText(280, 320, 100, 30, "You Lose");
					cpuScore++;
					//stops all input
					stopInput = true;
				}
			}
			//SCORING
			//VS PLAYER
			if (!vsCPU)// think about player scores for vsPlayer
			{
				//Check if player wins
				if (gameBoard.checkForWin(GameBoard::CROSS))
				{
					setSecondaryText(280, 320, 100, 30, "Cross Wins!");
					//playerScore++;
					//stop input
					stopInput = true;
				}
				//CPU wins
				if (gameBoard.checkForWin(GameBoard::NAUGHT))
				{
					setSecondaryText(280, 320, 100, 30, "Naught Wins!");
					//playerScore++;
					//stops all input
					stopInput = true;
				}
			}
		}
		
		//----------------OUTPUT------------------//
		//uses the draw color to fill the whole screen
		//render background color (green)
		SDL_SetRenderDrawColor(renderer, 163, 241, 158, 255); //rgba(0-255)
		//play mode		           
		//Sets Heading text & clears buffer
		if (vsCPU)
		{
			setHeadingText("VS COM");
		}else
		setHeadingText("VS PLAYER");
		//draw gameboard to screen
		gameBoard.draw();
		//buttons
		makeButton(30,410,150,40, "Quit");
		makeButton(460, 410, 150, 40, "Play Again");
		//swaps the buffers
		SDL_RenderPresent(renderer);
	}
	return 0;
}

//makes a button on screen with text included
//parameters are x location, y, width, height and what the button will say.
void makeButton(int x, int y, int w, int h, const char* buttonName)
{
	SDL_Rect rect;
	SDL_Rect dest;
	SDL_Color foreground = { 0, 0, 0 };

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, 200, 255, 200, 255);
	SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Surface* text_Name = TTF_RenderText_Solid(font, buttonName, foreground);
	text = SDL_CreateTextureFromSurface(renderer, text_Name);
	dest.x = x + 15;
	dest.y = y + 7;
	dest.w = text_Name->w / 3;
	dest.h = text_Name->h / 3;
	SDL_RenderCopy(renderer, text, NULL, &dest);
	SDL_DestroyTexture(text);
	SDL_FreeSurface(text_Name);

	// Update window
	SDL_RenderPresent(renderer);
}

//This function changes the heading on top of the screen
//Use as the name of the screen
void setHeadingText(string inputString)
{
	input = inputString;

	//Setting up the heading
	SDL_Rect dest;
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_Color foreground = { 0, 0, 0 };
	
	//location etc
	if (input.size()) {
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
		text = SDL_CreateTextureFromSurface(renderer, text_surf);

		dest.x = 320 - (text_surf->w / 2.0f);
		dest.y = 25;
		dest.w = text_surf->w;
		dest.h = text_surf->h;
		SDL_RenderCopy(renderer, text, NULL, &dest);

		SDL_DestroyTexture(text);
		SDL_FreeSurface(text_surf);
	}
	

	// Update window
	SDL_RenderPresent(renderer);
}

//Changes/adds a secondary heading to the screen
//use to display information
void setSecondaryText(int x,int y, int w, int h, string inputString)
{
	input = inputString;

	//Setting up the heading
	SDL_Rect dest;
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_Color foreground = { 0, 0, 0 };

	//location etc
	if (input.size()) {
		SDL_Surface* text_surf = TTF_RenderText_Solid(font, input.c_str(), foreground);
		text = SDL_CreateTextureFromSurface(renderer, text_surf);

		dest.x = x;
		dest.y = y;
		dest.w = w;
		dest.h = h;
		/*dest.w = text_surf->w;
		dest.h = text_surf->h;*/
		SDL_RenderCopy(renderer, text, NULL, &dest);

		SDL_DestroyTexture(text);
		SDL_FreeSurface(text_surf);
	}


	// Update window
	SDL_RenderPresent(renderer);
}

bool init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Error initializing SDL: " << SDL_GetError() << endl;
		return false;
	}

	/*if (IMG_Init(IMG_INIT_PNG) < 0) {
		cout << "Error initializing SDL_image: " << IMG_GetError() << endl;
		return false;
	}*/

	// Initialize SDL_ttf
	if (TTF_Init() < 0) {
		cout << "Error intializing SDL_ttf: " << TTF_GetError() << endl;
		return false;
	}

	window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (!window) {
		cout << "Error creating window: " << SDL_GetError() << endl;
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		cout << "Error creating renderer: " << SDL_GetError() << endl;
		return false;
	}

	//SDL_Surface* buffer = IMG_Load("test.png");
	//if (!buffer) {
	//	cout << "Error loading image test.png: " << SDL_GetError() << endl;
	//	return false;
	//}

	/*texture = SDL_CreateTextureFromSurface(renderer, buffer);
	SDL_FreeSurface(buffer);
	buffer = NULL;
	if (!texture) {
		cout << "Error creating texture: " << SDL_GetError() << endl;
		return false;
	}*/

	// Load font
	font = TTF_OpenFont("arial.ttf", 72);
	if (!font) {
		cout << "Error loading font: " << TTF_GetError() << endl;
		return false;
	}

	// Start sending SDL_TextInput events
	SDL_StartTextInput();

	return true;
}

void quitSDL() {
	SDL_StopTextInput();

	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	texture = NULL;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}