#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "joystick.h"

typedef enum { false = 0, true = !false} bool;

/* a little test program */
int main(int argc, char *argv[])
{
	int joystick_x;
	int joystick_y;
	int joystick_z;
	bool fire_pressed = false;

	// true only if an event we are using is activated
	bool relevant = true;

	int fd, rc;
	int done = 0;

	struct js_event jse;

	fd = open_joystick(0);
	if (fd < 0) {
		printf("open failed.\n");
		exit(1);
	}

	while (!done) {
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
}