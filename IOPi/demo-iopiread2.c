/*
 * demo-iopiread2.c
 *
 *  Created on: 23 Jan 2015
 *
 *      compile with "gcc ABE_helpers.c ABE_IoPi.c demo-iopiread2.c -o demo-iopiread2"
 *      run with "./demo-iopiread2"
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>


#include "ABE_IoPi.h"

void clearscreen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	IOPi_init(0x20); // initialise one of the io pi buses on i2c address 0x20, default address for bus 1

	set_port_direction(0x20,0, 0xFF); // set bank 0 to be inputs
	set_port_direction(0x20,1, 0xFF); // set bank 1 to be inputs
	set_port_pullups(0x20, 0, 0xFF); // enable internal pullups for bank 0
	invert_port(0x20,0,0xFF); // invert output so bank will read as 0
	set_port_pullups(0x20, 1, 0xFF); // enable internal pullups for bank 0
	invert_port(0x20,1,0xFF); // invert output so bank will read as 0


	while (1){
		clearscreen();
		printf("Port 0 %x \n", read_port(0x20,0)); // grounding a pins 1 to 8 will change the value
		printf("Port 1 %x \n", read_port(0x20,1)); // grounding a pins 1 to 8 will change the value
		usleep(200000); // sleep 0.2 seconds

	}

	return (0);
}
