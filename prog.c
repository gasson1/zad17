#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LED_ON  "1"
#define LED_OFF "0"
#define DOT_DELAY 1
#define DASH_DELAY 3
#define LETTER_DELAY 7
#define WORD_DELAY 10

#define GPIO_PATH "/sys/class/leds/beagleboard:green:usr0"

void set_led_state(const char *state) {
    int fd = open(GPIO_PATH "/brightness", O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (write(fd, state, strlen(state)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

void morse_code(char c) {
    switch (c) {
        case 'A':
            set_led_state(LED_ON);
            usleep(DOT_DELAY * 100000);
            set_led_state(LED_OFF);
            usleep(LETTER_DELAY * 100000);
            break;
        case 'B':
            set_led_state(LED_ON);
            usleep(DASH_DELAY * 100000);
            set_led_state(LED_OFF);
            usleep(DOT_DELAY * 100000);
            set_led_state(LED_ON);
            usleep(DOT_DELAY * 100000);
            set_led_state(LED_OFF);
            usleep(DOT_DELAY * 100000);
            set_led_state(LED_ON);
            usleep(DOT_DELAY * 100000);
            set_led_state(LED_OFF);
            usleep(LETTER_DELAY * 100000);
            break;
        case ' ':
            usleep(WORD_DELAY * 100000);
            break;
        default:
            break;
    }
}

int main() {
    int fd = open(GPIO_PATH "/trigger", O_WRONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    if (write(fd, "none", 4) == -1) {
        perror("write");
        return EXIT_FAILURE;
    }
    close(fd);

    const char* name = "IVAN BIRKOVSKYI";
    for (int i = 0; i < strlen(name); i++) {
        morse_code(name[i]);
    }

    return EXIT_SUCCESS;
}
