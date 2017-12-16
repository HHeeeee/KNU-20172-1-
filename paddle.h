#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"alarmlib.h"

#define		PAD_SYMBOL	'#'
#define 	START_TOP	PADDING+3
#define		PAD_LEN		0.33*LINES  /*pad is one third of screen*/


struct pppaddle {
		int pad_top,  /* top row of the paddle */
			pad_bot,  /* bottom row of the paddle */
			pad_col;
		int pad_top2,
			pad_bot2,
			pad_col2;  /* the paddle's column (fixed through the game)*/
		char pad_char;
		char pad_char2; /* symbol for drawing/representing the paddle on screen*/
};

/*
	Initialize the paddle's properties
	@params 	none
	@return 	void
*/
void paddle_init();

/*
	Moves the paddle up one row. 
	@params		none
	@return 	void
*/
void paddle_up();

/*
	Moves the paddle down one row. 
	@params 	none
	@return 	void
*/
void paddle_down();

/*
	Checks if a given coordinate (usually the ball's) is in contact 
	with the paddle.
	@params		y: a given row position,
				x: a given column posiiton.
	@return		1 if in contact or 0 otherwise
*/
void paddle_up2();


void paddle_down2();

int paddle_contact(int y,int x);

int paddle_contact2(int y,int x);
