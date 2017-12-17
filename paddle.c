/*
 *	
 *	 Paddle.c
 *
 *	
 *	 Paddle object for pong game
 *	
 *	
 *
 *   Author: Osazuwa Omigie	
 *   Date: April 8,2014.		
 *   CSCI-E28
 *   Harvard University	
 */



#include	"paddle.h"
#include	"pong.h"

/*
	Initialize the paddle's properties
	@params 	none
	@return 	void
*/
void paddle_init(struct pppaddle *paddle, int left_or_right){ // 2-player-mode user
	paddle->pad_top = START_TOP;
	paddle->pad_bot = paddle->pad_top + PAD_LEN;
	if(left_or_right == RIGHT)
		paddle->pad_col = RIGHT_EDGE - 1;
	else
		paddle->pad_col = LEFT_EDGE;
	paddle->pad_char =  PAD_SYMBOL;

	mvvline(paddle->pad_top,paddle->pad_col,paddle->pad_char,PAD_LEN);
}

/*
	Moves the paddle up one row. 
	@params		none
	@return 	void
*/
void paddle_up(struct pppaddle *paddle){
	int bot_cur, moved;

	moved = 0;

	//check if pad_top is not trying to go outside the court
	if((paddle->pad_top-1)>TOP_ROW){
		bot_cur = paddle->pad_bot;
		paddle->pad_top-=1;
		paddle->pad_bot-=1;
		moved = 1;		
	} 

	if (moved){
		mvaddch(paddle->pad_top, paddle->pad_col, paddle->pad_char);
		mvaddch(bot_cur, paddle->pad_col, BLANK);
	}	
}

/*
	Moves the paddle down one row. 
	@params 	none
	@return 	void
*/
void paddle_down(struct pppaddle *paddle){
	int top_cur, moved;

	moved = 0;

	//check if pad_top is not trying to go outside the court
	if((paddle->pad_bot+1)<BOT_ROW){
		top_cur = paddle->pad_top;
		paddle->pad_top+=1;
		paddle->pad_bot+=1;
		moved = 1;		
	} 

	if (moved){
		mvaddch(paddle->pad_bot, paddle->pad_col, paddle->pad_char);
		mvaddch(top_cur, paddle->pad_col, BLANK);
	}
	
}

int paddle_contact(struct pppaddle paddle,int left_or_right, int y, int x){
	int i;
	if (x+2 == RIGHT_EDGE && left_or_right == RIGHT){
		for (i=paddle.pad_top; i<=paddle.pad_bot; i++){
			if (y == i){
				return 1;
			}
		}
	} else if(x-2 == LEFT_EDGE && left_or_right == LEFT) {
		for (i=paddle.pad_top; i<=paddle.pad_bot; i++){
			if (y == i){
				return 1;
			}
		}
	}
	return 0;
}
