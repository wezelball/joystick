#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>      /* Errors */
#include <pthread.h>	/* POSIX Threads */

#include "joystick.h"

#define BUFSIZE 1024

typedef enum { false = 0, true = !false} bool;

/* prototype for thread routine */
void joystick_update ( void *ptr );

/* struct to hold data to be passed to a thread
this shows how multiple data items can be passed to a thread */
typedef struct struct_thdata
{
    int thread_no;
    char message[100];
} thdata;

/* a little test program */
int main(int argc, char *argv[])
{
	char buf[BUFSIZE];
	int joystick_x;
	int joystick_y;
	int joystick_z;
	bool fire_pressed = false;
	pthread_t joyThread;
	thdata joyData; // this is a structure we can pass to the thread

	// true only if an event we are using is activated
	bool relevant = true;

	int fd, rc;
	int done = 0;

	struct js_event jse;

	/* initialize data to pass to thread 1 */
    joyData.thread_no = 1;
    strcpy(joyData.message, "Joystick thread");
	
	pthread_create(&joyThread, NULL, (void *) &joystick_update, (void *) &joyData);
	
	fd = open_joystick(0);
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}

	while (!done) {
		/* get message line from the user */
		printf("Please enter msg: ");
		bzero(buf, BUFSIZE);
		fgets(buf, BUFSIZE, stdin);

		/*
		 *Check to see if we're killing the client
		 */
		if(strcmp(buf, "99\n") == 0)
		{
			done = 1;
  		}
		rc = read_joystick_event(&jse);
		usleep(1000);
		if (rc == 1) {
			//printf("Event: time %8u, value %8hd, type: %3u, axis/button: %u\n", 
				//jse.time, jse.value, jse.type, jse.number);
			if (jse.type == 2 && jse.number == 0) {
				joystick_x = jse.value;
				relevant = true;
			}
			else if (jse.type == 2 && jse.number == 1) {
				joystick_y = jse.value;
				relevant = true;
			}
			else if (jse.type == 2 && jse.number == 3) {
				joystick_z = jse.value;
				relevant = true;
			}
			else if (jse.value == 1 && jse.type == 1 && jse.number == 0) {
				fire_pressed = true;
				relevant = true;
			}
			else if (jse.value == 0 && jse.type == 1 && jse.number == 0) {
				fire_pressed = false;
				relevant = true;
			}
			else
				relevant = false;
				
			if (relevant)
				printf("X: %8hd, Y: %8hd, Z: %8hd, Fire: %d\n",
					joystick_x, joystick_y, joystick_z, fire_pressed);
		}
	}
	return(0);
}

/**
 * Joystick update function
 * it accepts a void pointer 
**/
void joystick_update ( void *ptr )
{
    thdata *jdata;            
    jdata = (thdata *) ptr;  /* type cast to a pointer to thdata */

	while(true)
	{
	
		/* do the work */
		printf("Thread %d says %s \n", jdata->thread_no, jdata->message);
		sleep(1);
    
		//pthread_exit(0); /* exit */
	}
} 