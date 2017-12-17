#include "AI.h"
#include "pong.h"
extern struct ppball the_ball;
void AI(struct pppaddle *AIpaddle, int difficulty) {
	int i;
	
	for(i = 0; i < difficulty; i++) {
		if(the_ball.y_pos > (AIpaddle->pad_top + AIpaddle->pad_bot) / 2)
			paddle_down(AIpaddle);
		else if(the_ball.y_pos < (AIpaddle->pad_top + AIpaddle->pad_bot) / 2)
			paddle_up(AIpaddle);
	}
}
