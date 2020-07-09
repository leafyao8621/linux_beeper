#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>


int console_fd = -1;

void handler(int signum) {
    switch(signum) {
    case SIGINT:
        if(console_fd >= 0) {
            ioctl(console_fd, KIOCSOUND, 0);
            close(console_fd);
            exit(signum);
        } else {
            exit(signum);
        }
    }
}


void play(const short *song) {
    signal(SIGINT, handler);
    console_fd = open("/dev/console", O_WRONLY);
    if (console_fd == -1) {
        puts("Cannot open /dev/console");
        return;
    }
    for (const short *iter = song; *iter != -1; iter += 2) {
        if (*iter) {
            ioctl(console_fd, KIOCSOUND, (int)(1190000 / *iter));
        }
        usleep(iter[1] * 1000);
        ioctl(console_fd, KIOCSOUND, 0);
    }
}
