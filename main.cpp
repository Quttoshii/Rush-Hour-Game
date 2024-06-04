//============================================================================
// Name        : .cpp
// Author      : FAST CS Department
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath> // for basic math functions such as cos, sin, sqrt

using namespace std;

void BackOption();	//function to access the back option
void TaxiColor();	//function to access the selection of taxi color
void Name();		//function to take name from player
void Score();		//function to take score of the player
void Building();	//function to draw buildings
void BoardBackEnd();	//function to generate elemants randomly in random positions
void drawCar();	//function to draw car
void passenger();	//function to draw passengers
char bottom_left_pos();	//function to find the bottom left position of the taxi
char bottom_right_pos();	//function to find the bottom right position of the taxi
char top_left_pos();		//function to find the top left position of the taxi
char top_right_pos();		//function to find the top right position of the taxi
void destination();		//function to get a random destination of the passenger
void PrintableKeys(unsigned char key, int x, int y);

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

bool picked = false;		//to check whether spacebar has been clicked to pick passenger
char board[20][20] = {1,};	//to create a 20 by 20 array for random generation
bool click = false;		//to get mouse left button click input from player
int y_coor;			//to get mouse y-axis position for menu options
char option = ' ';		//used in creating and selecting menu options
bool drawOnce = false;		//to generate random objects once per game
char carColor = ' ';		//to get selected car color

int xI = 200, yI = 689;

void drawCar() {
	
	//yellowtaxi.png pix[256];
	
	//ReadImage("yellowtaxi.png", pix);
	
	if (carColor == 'r')		//character corresponding to car color is choosen
		DrawSquare(xI, yI, 12, colors[RED]);
		
	else if (carColor == 'y')
		DrawSquare(xI, yI, 12, colors[LIGHT_YELLOW]);
	
	else if (carColor == 'm')	//random number is generated between 1 and 2 for random color selection
	{
		if (GetRandInRange(1,2) == 1)
			carColor = 'r';
		else if (GetRandInRange(1, 2) == 2)
			carColor = 'y';
	}
		
		
	glutPostRedisplay();
}

char bottom_left_pos()
{
	char pos;
	int x = 0;
	int y = 0;
	
	x = ((xI) - 200) / 30;		//current axis position is subtracted by initial axis position and divided by 30
	y = ((yI) - 101) / 30;		//30 is the number of pixels per block 
	
	pos = board[x][y];		//we are given block number out of the 20x20 block array.
	
	return pos;
}

char bottom_right_pos()
{
	char pos;
	int x = 0;
	int y = 0;
	
	x = ((xI + 11) - 200) / 30;	//current axis position is added with width of car
	y = ((yI) - 101) / 30;
	
	pos = board[x][y];
	
	return pos;
}

char top_right_pos()
{
	char pos;
	int x = 0;
	int y = 0;
	
	x = ((xI + 11) - 200) / 30;
	y = ((yI + 11) - 101) / 30;
	
	pos = board[x][y];
	
	return pos;
}

char top_left_pos()
{
	char pos;
	int x = 0;
	int y = 0;
	
	x = ((xI) - 200) / 30;
	y = ((yI + 11) - 101) / 30;
	
	pos = board[x][y];
	
	return pos;
}

void carBlue()		//function to draw blue car
{
	int x = 200, y = 101;		//initial coordinates of board
	
	for (int r = 0; r < 20; r++)	//loop to access the rows
	{
		for (int c = 0; c < 20; c++)	//loop to access the columns
		{
			if ((board[r][c] == 'e'))	//if element is generated on the corresonding block
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 12, colors[BLUE]);	//object will be drawn
		}			//initial position added with the multiplication of number of r/c with the number
	}				//of pixels in the block (30)
}

void carPink()		//function to draw pink car
{
	int x = 200, y = 101;		//same logic used for all objects
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if ((board[r][c] == 'p'))
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 12, colors[DEEP_PINK]);
		}
	}
}

void box()
{
	int x = 200, y = 101;
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if ((board[r][c] == 'x'))
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 14, colors[BROWN]);
		}
	}
}

void tree()
{
	int x = 200, y = 101;
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if ((board[r][c] == 't'))
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 14, colors[FOREST_GREEN]);
		}
	}
}

void passenger()
{
	int x = 200, y = 101;
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if ((board[r][c] == 'r'))
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 8, colors[GOLD]);
		}
	}
}

void destination()
{
	int x = 200, y = 101;
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if ((board[r][c] == 'd'))
				DrawSquare((x + (r * 30)), (y + ( c * 30)), 10, colors[GREEN]);
		}
	}
}

bool flag = true;
void moveCar() {	//function to move the object in left and right
	
	if (xI > 10 && flag) {
		xI -= 10;
		cout << "going left";
		if(xI < 100)
			flag = false;

	}
	else if (xI < 1010 && !flag) {
		cout << "go right";
		xI += 10;
		if (xI > 900)
			flag = true;
	}
}

void GameMenu(){	//to create the menu of the game.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors.
	
	ofstream dataFile("Highscores.txt", ios :: app);	//creating highscores file
	dataFile.close();
	
	DrawString(450, 800, "Rush Hour", colors[MISTY_ROSE]);
	DrawString(450, 700, "Start Game", colors[MISTY_ROSE]);
	DrawString(450, 600, "Leaderboard", colors[MISTY_ROSE]);
	
	if (((click == true) && ((y_coor >= 75) && (y_coor <= 125))) && option == ' ')	//if left click is true within given
	{											//y coordinates option will be updated
		option = 's';
		return;
	}
	else if (((click == true) && ((y_coor >= 160) && (y_coor <= 200))) && option == ' ')
	{
		option = 'l';
		return;
	}
}

void TaxiColor() {

	DrawString(450, 500, "RED", colors[RED]);
	DrawString(450, 400, "YELLOW", colors[LIGHT_YELLOW]);
	DrawString(450, 300, "RANDOM", colors[YELLOW]);
	
	if (((click == true) && ((y_coor >= 240) && (y_coor <= 280))) && option == 's')	//same logic as above
	{
		option = 'r';
		carColor = 'r';	//taxi color assigned a value
		return;
	}
	else if (((click == true) && ((y_coor >= 310) && (y_coor <= 350))) && option == 's')
	{
		option = 'y';
		carColor = 'y';
		return;
	}
	else if (((click == true) && ((y_coor >= 390) && (y_coor <= 430))) && option == 's')
	{
		option = 'm';
		carColor = 'm';
		return;
	}
		
}

void LeaderBoard() {		//function to display leaderboard

	DrawString(400, 700, "Leaderboard:", colors[MISTY_ROSE]);
	
	ifstream inDataFile("Highscores.txt");
	string line;		
	
	int y = 600;
	
	while (!inDataFile.eof() && !inDataFile.fail())	//loop reads until the end of file 
	{
		getline(inDataFile, line);		//input from file is taken line by line
		DrawString(400, y, line, colors[MISTY_ROSE]);
		y -= 50;
	}
}

void DrawBoard()	//function to draw the board of the game
{

	glClearColor(1/*Red Component*/, 1,	//148.0/255/*Green Component*/,
			1/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	for(int i = 0; i <= 600; i += 30 )	//line drawn on y axis after every block for 20 blocks, pixels(600) taken accordingly
		DrawLine( (200 + i) , 100 , (200 + i) , 700 , 1 , colors[BLACK] );
		
	DrawLine( 200 , 100 , 800 , 100 , 1 , colors[BLACK] );	//to draw top
	DrawLine( 200 , 700 , 800 , 700 , 1 , colors[BLACK] );	//and bottom line of the grid

	if (drawOnce == false)		//condition to generate objects randomly once per game
	{
		BoardBackEnd();	
		drawOnce = true;
	}
	
	Building();
		
	drawCar();
}

void BoardBackEnd()
{
	int r = 0, c = 0, buildings = 0, random = 0, pinkCars = 0, blueCars = 0, boxes = 0, trees = 0, passengers = 0, destination = 0;
	
	while (buildings < 140)	//since 20x20 = 400 and 35% of 400 is 140, so 140 buildings are generated
	{
		r = GetRandInRange(0, 20);	//random row and column number generated
		c = GetRandInRange(0, 20);
		
		if (board[r][c] == 0)	//condition to see if block is empty
		{
			if ((board[r - 1][c - 1] == 0) && (board[r - 1][c + 1] == 0) && (board[r + 1][c - 1] == 0) && (board[r + 1][c + 1] == 0))		//condition to see if blocks diagonal to selected block are empty or not
			{
				board[r][c] = 'b';	//character assigned to correspoding block which is
				buildings++;		//further drawn in a seperate function
			}
		}
	}
	
	while (pinkCars < 4)	//same logic applied for each object
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 'p';
			pinkCars++;
		}
			
	}
	
	while (blueCars < 4)
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 'e';
			blueCars++;
		}
			
	}
	
	while (boxes < 6)
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 'x';
			boxes++;
		}
			
	}
	
	while (trees < 6)
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 't';
			trees++;
		}
			
	}
	
	while (passengers < 3)
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 'r';
			passengers++;
		}
			
	}
	
	while (destination < 1)
	{
		r = GetRandInRange(0, 20);
		c = GetRandInRange(0, 20);
		
		if ((board[r][c] == 0) && (board[r][c] != 1))
		{
			board[r][c] = 'd';
			destination++;
		}
			
	}
}

void Building()
{
	int x = 199, y = 100;
	
	for (int r = 0; r < 20; r++)
	{
		for (int c = 0; c < 20; c++)
		{
			if (board[r][c] == 'b')
			{
				DrawSquare((x + (r * 30)), (y + (c * 30)), 32, colors[BLACK]);
			}
		}
	}
	
}

void InGame() {
	
	DrawBoard();
	
	carBlue();
	carPink();
	tree();
	box();
	passenger();
	
	if (bottom_left_pos() == 'r')		//condition to see if car is on the passeger block
		glutKeyboardFunc(PrintableKeys);
	if (picked == true)		//to check if spacebar is pressed or not
	{
		destination();
	}
	
	//Display Score
	DrawString( 50, 800, "Score=", colors[BLACK]);	//to display score	
		
	drawCar();
}

/*
 * Main Canvas drawing function.
 * */

void GameDisplay()/* to display the game*/{
	
	GameMenu();	//menu is called 
	
	switch (option)	//case corresponding to each character is chosen and that function is then called
	{
		case 's':
			BackOption();
			TaxiColor();
			break;
		case 'l':
			BackOption();
			LeaderBoard();
			break;
		case 'r':
			Name();
			break;
		case 'y':
			Name();
			break;
		case 'm':
			Name();
			break;
		case 'g':
			InGame();
			break;
	}
	
	glutSwapBuffers(); // do not modify this line..

}

void BackOption() {
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors.
	
	DrawString(20, 800, "Back", colors[MISTY_ROSE]);
	
	if ((click == true) && ((y_coor >= 0) && (y_coor <= 50)))	//y coordinates of back option
	{
		switch (option)	//option is updated depending on in which menu back is pressed
		{
			case 's':
				option = ' ';
				return;
			case 'l':
				option = ' ';
				return;
			case 'r':
				option = 's';
				return;
			case 'y':
				option = 's';
				return;
			case 'm':
				option = 's';
				return;
		}
	}
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

	if ((key
			== GLUT_KEY_LEFT) && ((bottom_right_pos() != 'b') || (bottom_left_pos() != 'b') || (top_right_pos() != 'b') || (top_left_pos() != 'b')))/*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/ {
			//condition checks to see if car has entered a building block, if it has no movement is done
		xI -= 1;
		
		if ((bottom_right_pos() == 'b') || (bottom_left_pos() == 'b') || (top_right_pos() == 'b') || (top_left_pos() == 'b'))
			xI += 1;	//if car has entered a building block then it is sent back the direction it came
	
	} else if ((key
			== GLUT_KEY_RIGHT) && ((bottom_right_pos() != 'b') || (bottom_left_pos() != 'b') || (top_right_pos() != 'b') || (top_left_pos() != 'b')))/*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/ {
				//same logic is applied for all directions
				
			xI += 1;
			if ((bottom_right_pos() == 'b') || (bottom_left_pos() == 'b') || (top_right_pos() == 'b') || (top_left_pos() == 'b'))
				xI -= 1;
		
	} else if ((key
			== GLUT_KEY_UP) && ((bottom_right_pos() != 'b') || (bottom_left_pos() != 'b') || (top_right_pos() != 'b') || (top_left_pos() != 'b')))/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/ {
		yI += 1;
		if ((bottom_right_pos() == 'b') || (bottom_left_pos() == 'b') || (top_right_pos() == 'b') || (top_left_pos() == 'b'))
			yI -= 1;
	}

	else if ((key
			== GLUT_KEY_DOWN) && ((bottom_right_pos() != 'b') || (bottom_left_pos() != 'b') || (top_right_pos() != 'b') || (top_left_pos() != 'b')))/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/ 
	{
		yI -= 1;
		if ((bottom_right_pos() == 'b') || (bottom_left_pos() == 'b') || (top_right_pos() == 'b') || (top_left_pos() == 'b'))
			yI += 1;
		
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	
	if (key == ' ' || key == 32)
	{
		picked = true;
		cout << "spacebar" << endl;
	}
	
	glutPostRedisplay();
}

void DisplayName(unsigned char key, int x, int y)	//function to display name on leaderboard
{	
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	
	ofstream dataFile("Highscores.txt", ios :: app);	//file is edited to add highscore without removing the previous ones
	
	if ((key >= 65 && key <= 90) || (key >= 97 && key <= 122) || key == 32 )
	{
		cout << key;
		DrawString(390, 600, Num2Str(key), colors[MISTY_ROSE]);	//with each key stroke
		dataFile << key;						//it is written in the file
		
	}
	
	if (key == 13)			//once enter is pressed
	{
		option = 'g';		//option is updated to go to game
		dataFile << ":" << endl;
		dataFile.close();	//file is then closed
		return;
	}
	

		
}

void Name() {		//to display name on start of game
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors.
	
	DrawString(390, 700, "ENTER YOUR NAME:", colors[MISTY_ROSE]);
	
	glutKeyboardFunc(DisplayName);
	
	if (option == 'g')
		return;
	
}


/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	//moveCar();

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {
	
	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;
		click = true;		//after a left click, click is set to true
		y_coor = y;		//y coordinate of that click is saved in y_coor
		cout << "Left Click" << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	else 				//click is set to false again
		click = false;
	
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	
	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rush Hour by Afaq Alam"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* RushHour_CPP_ */
