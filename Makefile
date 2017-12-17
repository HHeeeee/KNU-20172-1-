CC = gcc -Wall 


pong: pong.c paddle.o clocktimer.o display_menu.o AI.o
	$(CC) paddle.o clocktimer.o display_menu.o AI.o pong.c alarmlib.c -lcurses -o pong

paddle.o: paddle.c
	$(CC) -c paddle.c

clocktimer.o: clocktimer.c
	$(CC) -c clocktimer.c

display_menu.o: display_menu.c
	$(CC) -c display_menu.c

AI.o: AI.c
	$(CC) -c AI.c

clean:
	rm -f pong *.o
