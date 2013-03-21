#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <errno.h>

#include <libgpio.h>

#define TTY_TO_GPIO_DEV "/dev/ttyGPIO"

int main(void) {

	int TTYtoGPIO, pinsStatus, ret;

	ret = GPIOInit();

	if (ret) {
		printf("TTYtoGPIO: Could not initialize GPIO(s), exiting...\n");
		return -1;
	} else {
		printf("TTYtoGPIO: Initialized GPIO(s) successfully\n");
	}

	GPIOSetPinMode(PORTG, 9, MODE_OUTPUT);

	TTYtoGPIO = open(TTY_TO_GPIO_DEV, O_RDONLY); // O_RDWR

	if (TTYtoGPIO == -1) {
		printf("TTYtoGPIO: Could not open the virtual device, exiting...\n");
	}

	while (1) {

		if ( ioctl(TTYtoGPIO, TIOCMGET, &pinsStatus) != -1 ) {
			if (pinsStatus & TIOCM_DTR) {
				GPIOSetPin(PORTG, 9, 1);
				//printf("TEST: DTR=1\n");
			} else {
				GPIOSetPin(PORTG, 9, 0);
				//printf("TEST: DTR=0\n");
			}

		} else {
			printf("TTYtoGPIO: ioctl() returned an invalid value, exiting...\n");
			close(TTYtoGPIO);
			return -1;
		}

		usleep(50000);
	}

	//printf("State: %lu\r\n",my_gpio_get_input(SUNXI_PORT_G_BASE, SUNXI_PIO_09));
	//usleep(100000);
	//printf("State: %lu\r\n",my_gpio_get_input(SUNXI_PORT_G_BASE, SUNXI_PIO_09));
	//usleep(100000);

	close(TTYtoGPIO);

	return 0;
}
