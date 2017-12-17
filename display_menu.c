#include "pong.h"
#include "paddle.h"

int display_menu(void)
{
//	int input;
	char menu ;
	tty_mode(0);
	set_noecho();
		system("clear");
		printf("\n\t\t");
		printf("\n\n\t\t\t       P  O  N  G  \n");
		printf("\n\n\t"); 
		printf("\n\t\t\t       게 임 메 뉴\t\n");
		printf("\n\t\t");
		printf("\n\t");
		printf("\n\n\n\t\t\t     \t1) 1 인용\t   ");
		printf("\n\n\n\t\t\t     \t2) 2 인용\t   ");
//		printf("\n\n\t\t\t     \t3) Option\t   ");
//		printf("\n\t\t\t   =\t4) 기록 출력\t   =");
//		printf("\n\t\t\t   =\t5) 종료\t\t   =");
		printf("\n\n\n\n\n\t\t");
//		printf("\n\t\t\t\t\t 선택 : ");
//		scanf("%d",&menu);
		while(1)
		{
			switch( getchar()){

				case '1':
					tty_mode(1);
					system("clear");
					 return 1;
				case '2':
					tty_mode(1);
					system("clear");
					 return 2;
//				case '3':
//					tty_mode(1);
//					 return 3;
			}
		
		}
	endwin();
}
int option_menu(int num)
{
	int input;
	char menu;
	system("clear");
	tty_mode(0);
	set_noecho();
		printf("\n\t\t\t   	O P T I O N	\n");
		printf("\n\t\t\t   	   조 작 법 \t\n");
		printf("\t\t\t      | 1P |     | 2p |	\n");
		printf("\t\t\t UP   | A  |     | K  | \n");
		printf("\t\t\t DOWN | Z  |     | M  | \n");
		printf("\n\t");
		if(num==1)
		{
		printf("\n\t\t\t\t난이도설정\t");
		printf("\n\t\t\t\tEASY   : 1 \t");
		printf("\n\t\t\t\tNORMAL : 2 \t");
		printf("\n\t\t\t\tHARD   : 3 \t");
		}
		if(num==2)
		{
			printf("\n\t\t\t잠시후 게임을 시작합니다\n");
			sleep(3);
			tty_mode(1);
			system("clear");
			return;
		}
		while(1)
		{
			switch(getchar()){
				case '1':
					tty_mode(1);
					system("clear");
					return 1;
				case '2':
					tty_mode(1);
					system("clear");
					return 2;
				case '3':
					tty_mode(1);
					system("clear");
					return 3;
				}
		}
		endwin();
}
void game_over(int a,int b)
{
	system("clear");
	printf("\n\t\t");
	printf("\n\t\t  G A M E   O V E R\n");
	printf("\n\n\n");
	printf("\r\n\t\t\t\t     %d    :    %d \n",a,b);
	printf("\n\n\n\n");
	sleep(3);
	system("clear");
	exit(0);
}

void set_noecho()
{
	struct termios ttystate;

	tcgetattr(0,&ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&ttystate);
}

void tty_mode(int how)
{
	static struct termios original_mode;

	if(how==0)
		tcgetattr(0,&original_mode);
	else
		tcsetattr(0,TCSANOW,&original_mode);
}
