#include <stdio.h>
#include <termios.h>
#include<fcntl.h>

void tty_mode(int);
void set_noecho();

int display_menu(void)
{
//	int input;
	char menu ;
	system("clear");
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
					 return 1;
				case '2':
					tty_mode(1);
					 return 2;
//				case '3':
//					tty_mode(1);
//					 return 3;
			}
		
		}
	endwin();
}
void set_noecho()
{
	struct termios ttystate;
	
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&ttystate);
}

void tty_mode(int how){
	static struct termios original_mode;

	if(how == 0){
		tcgetattr(0, &original_mode);
	}
	else
		tcsetattr(0, TCSANOW, &original_mode);

}
