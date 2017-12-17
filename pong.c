/*
 *
 *	Purpose:
 *		This is commanline based one-person ping-pong game.Using signal 
 *		and timer management, various events are operations are handled 
 *		simultaneously during the game. The object of the game is to keep 
 *		the ball in play as long as possible. 
 *
 *	User Input:
 *		 	k: moves the paddle upward
 *		 	m: moves the paddle downward
 *			Q: quit
 *
 *
 *   Author: Osazuwa Omigie	
 *   Date: April 8,2014.		
 *   CSCI-E28
 *   Harvard University	
 */

#include	"pong.h"
#include	"AI.h"
#include	"clocktimer.h"

struct ppball the_ball;
static int balls_left;

static void change_ball_speed();
static void move_ball();

extern int display_menu();
extern int option_menu();

static struct pppaddle the_paddle;
static struct pppaddle the_paddle2;
static struct pppaddle AI_paddle;
static int scoreA, scoreB;
static int menu, level;
static int cnt = 0;

int main()
{
	int c;
	balls_left = INIT_BALLS-1; /* minus one ball currently in play */
	int temp = balls_left;
	menu = display_menu();
	if(menu==1) // AI mode
	{
		level=option_menu();
	}
	set_up();
	start_round(); //serves the balls and updates headers
	while ( (c = getch()) != 'Q'  && balls_left >= 0){
		if (c=='k' && menu == 2){
			paddle_up(&the_paddle);
		}
		else if (c=='m' && menu == 2){
			paddle_down(&the_paddle);
		}
		else if (c=='a'){
			paddle_up(&the_paddle2);
		}
		else if (c=='z'){
			paddle_down(&the_paddle2);
		}
		if((temp - balls_left) >= 1){ //lost a ball?
			start_round(); //restart round
		}
		temp = balls_left;
	}
	wrap_up();
	return 0;
}

/**
	Starting a new round: Initializes the ball's position, updates the headers and 
	serves the ball, starting a new round. 
	@params		none
	@return   	void
**/
void start_round(){
	clock_resume();
	init_ball_pos();
	update_left_header(balls_left);
	mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol); //serve ball
	refresh();
	signal(SIGALRM, sigarlm_handler);		/* re-enable handler	*/
	
}

/*	
	Initializes ppball struct, signal handler, curses	
	@param		void
	@return 	void
*/
void set_up()
{
	initscr();		/* turn on curses	*/
	noecho();		/* turn off echo	*/
	cbreak();		/* turn off buffering	*/
	init_walls();
	paddle_init(&the_paddle, RIGHT);
	paddle_init(&the_paddle2, LEFT);
	paddle_init(&AI_paddle, RIGHT);
	clock_init();
	print_headers();

	signal(SIGINT, SIG_IGN);	/* ignore SIGINT	*/
	refresh();
	signal( SIGALRM, sigarlm_handler );
	set_ticker( 1000 / 60 );	/* send millisecs per tick....60 ticks/second */
}


/*
	Calls the appropriate functions to update the balls left and clock header
	@param	void
	@return void
*/
void print_headers(){
	update_left_header(balls_left);
//	update_right_header();
}

/*
	Outputs the balls left by concatenating the actual number of balls left
	with the "BALLS LEFT:" string. 
	@params	ballnum: the number of balls left
	@return void
**/
void update_left_header(int ballnum){
	int i,j,header_len = 14;
	char char_array[header_len];
	char ball_num = (char) balls_left; 

	if(ballnum<0) return; //no need to update after game over.

	//build output string
	snprintf(char_array,header_len,"SCORE   %d : %d",scoreA, scoreB);

	//write output string to the screen
	for(i=LEFT_EDGE,j=0;j<header_len-1;i++,j++){
		mvaddch(TOP_ROW-2,i,char_array[j]);
	}
}

/*
	Gets the clock's current string ouput and writes it to the screen 
	@params	none
	@return void
**/
/*void update_right_header(){
	int header_len = 17;
	char char_array[header_len];
	memset(char_array, '\0', header_len); 
	int i,j,startingX=RIGHT_EDGE - header_len;
	get_time(char_array); 

	//write clock output to the screen
	for(i=startingX,j=0;j<header_len-1;i++,j++){
		mvaddch(TOP_ROW-2,i,char_array[j]);
	}
}

	Initializes the ball's starting position, speed, and direction
	@params	none
	@return void
*/
void init_ball_pos(){
	srand(getpid()); //initialize random number generator
	change_ball_speed(); /*start with a random speed*/
	/*initial ball postion*/
	the_ball.x_pos = X_INIT; 
	the_ball.y_pos = Y_INIT;
	the_ball.y_dir = 1  ;
	the_ball.x_dir = 1  ;
	the_ball.symbol = DFL_SYMBOL ;
}

/*
	 Sets the ball's current delay (speed determinant) to a random number not bigger
	 than the MAX_DELAY.
	 @params none
	 @return void
*/
static void change_ball_speed(){
	int delay=MAX_DELAY;
	/* find random value for x_delay and y_delay greater than 0 */
	while ((delay=rand() % MAX_DELAY) <= 0) {}
	the_ball.count = the_ball.delay = delay;
}

/*
	Draws the ping pong court/walls on the screen 
	@params none
	@return void
*/
void init_walls(){
	//ACS_HLINE ACS_VLINE
	clear();

	/* Draw top horizontal wall */
	mvhline(LEFT_EDGE,TOP_ROW,ACS_HLINE,COLS-(PADDING*2));


	/* Draw bottom horizontal wall */
	mvhline(BOT_ROW,LEFT_EDGE,ACS_HLINE,COLS-(PADDING*2));

	move(LINES-1, COLS-1);		/* park the cursor	*/
}

/* 
	Stop ticker and curses 
	@params none
	@return void
*/
void wrap_up(){
	set_ticker(0);
	endwin();		/* put back to normal	*/
}

/*
	Moves the ball to its new location on the screen.
	Determines if the ball's new location is against a paddle, wall
	or leaving the court (i.e game lose). And updates the balls left
	@params	none
	@return void 
*/
void move_ball(){
	int	y_cur, x_cur;
	y_cur = the_ball.y_pos ;		/* old spot		*/
	x_cur = the_ball.x_pos ;
	the_ball.y_pos += the_ball.y_dir ;	/* move	*/
	the_ball.x_pos += the_ball.x_dir ;	/* move	*/
	the_ball.count = the_ball.delay  ;	/* reset*/

	/* erase ball from previous location */
	mvaddch(y_cur, x_cur, BLANK); 
	
	/* draw the ball on the new location */
	mvaddch(the_ball.y_pos, the_ball.x_pos, the_ball.symbol); 

	move(LINES-1, COLS-1);		/* park cursor */

	/* check for collision or game lose */
	if (bounce_or_lose(&the_ball)==-1) {
		update_left_header(--balls_left); /* lost a ball*/
		clock_pause(); /*pause game clock*/
	}
	refresh();	
}

/* 
	This is the SIGARLM signal handler. It updates the clock timer first, 
	then updates the ball's position after its delay count reached.
	@params signal args
	@return void
*/

void sigarlm_handler(int s)
{
	int ball_moved;
	signal( SIGALRM , SIG_IGN );		/* dont get caught now 	*/
	
	ball_moved = ( the_ball.delay > 0 && --the_ball.count == 0); 
	clock_tick();  /* make a clock tick*/
	//update_right_header(); /* update the clock output*/

	if (ball_moved){
		move_ball();
		if(menu == 1) {
			if(cnt++ % 3 == 0)
				AI(&AI_paddle, level);
		}
	}
	signal(SIGALRM, sigarlm_handler);		/* re-enable handler	*/
}

/* 
 *	Checks if a ball hits the walls, paddle or goes leaves the court. 
 *   @params	args address to ppball
 *   @return    0 for no contact, 1 for a bounce, or -1 for a lose
 */
int bounce_or_lose(struct ppball *bp)
{
	int	return_val = 0 ;

	if ( (bp->y_pos-1) == TOP_ROW ){
		//ball bounces off top wall 
		bp->y_dir = 1; //change direction
		return_val = 1 ; 
	}
	else if ( (bp->y_pos+1) == BOT_ROW ){
		//ball bounces off bottom wall
		bp->y_dir = -1; //change direction
		return_val = 1;
	}
	if  (paddle_contact(the_paddle2, LEFT, bp->y_pos,bp->x_pos)){
		//ball bounces off left wall
		bp->x_dir = 1;	//change direction
		return_val = 1 ;
		change_ball_speed();
	}
	else if (paddle_contact(menu == 1 ? AI_paddle : the_paddle, RIGHT, bp->y_pos,bp->x_pos)){
		//ball bounces off paddle
		bp->x_dir = -1; //change direction
		return_val = 1;
		change_ball_speed();
	}
	else if ((bp->x_pos+1) == RIGHT_EDGE ){
		//no paddle contact: ball lose
		return_val = -1; 
	}
	else if ((bp->x_pos-1)==LEFT_EDGE){
		return_val = -1;
	}
		// (bp->x_pos+2) == RIGHT_EDGE ){
		// if (paddle_contact(bp->y_pos,bp->x_pos)){
		// 	//ball bounces off paddle
			
		// }else{
		// 	return_val = -1;
		// }		
	return return_val;	
}
