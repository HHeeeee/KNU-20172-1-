#include "AI.h"
#include "paddle.h"
#include "pong.h"

void AI(struct pppaddle *AIpaddle, int difficulty) {
	int i;
	
	for(i = 0; i < difficulty; i++) {
		if(the_ball.y_pos > (AIpaddle->pad_top + AIpaddle->pad_bot) / 2)
			paddle_down(AIpaddle);
		else if(the_ball.y_pos < (AIpaddle->pad_top + AIpaddle->pad_bot) / 2)
			paddle_up(AIpaddle);
	}
}
