#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"alarmlib.h"

#define		PAD_SYMBOL	'#'
#define 	START_TOP	PADDING+3
#define		PAD_LEN		0.33*LINES  /*pad is one third of screen*/
#define		LEFT 		0
#define		RIGHT		1


struct pppaddle {
		int pad_top,  /* top row of the paddle */
			pad_bot,  /* bottom row of the paddle */
			pad_col;
		char pad_char;
};

/*
	Initialize the paddle's properties
	@params 	none
	@return 	void
*/
void paddle_init(struct pppaddle *paddle, int left_or_right);
/*
	Moves the paddle up one row. 
	@params		none
	@return 	void
*/
void paddle_up(struct pppaddle *paddle);

/*
	Moves the paddle down one row. 
	@params 	none
	@return 	void
*/
void paddle_down(struct pppaddle *paddle);

/*
	Checks if a given coordinate (usually the ball's) is in contact 
	with the paddle.
	@params		y: a given row position,
				x: a given column posiiton.
	@return		1 if in contact or 0 otherwise
*/

int paddle_contact(struct pppaddle paddle, int left_or_right, int y, int x);
