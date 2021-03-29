/* 
 *   Load necessary libraries
 */ 

#include <zephyr.h>                                                            
#include <drivers/gpio.h>
#include <timing/timing.h>
#include <ctype.h>
#include <string.h>


/*
 *  Define constants related to the micro:bit's display
 */

#define LED_ROW3_GPIO_PIN 15                                                  
#define LED_ROW3_GPIO_PORT DT_LABEL(DT_NODELABEL(gpio0))                       
#define LED_COL3_GPIO_PIN 31 
#define LED_COL3_GPIO_PORT DT_LABEL(DT_NODELABEL(gpio0))
#define SLIP_TIME 16                     
   // 16 milliseconds 
/*
 *  Define constants necessary for describing International Morse Code 
 */

#define SHORT_MARK 1000     // 100 ms in nanoseconds, or a dit 
#define LONG_MARK 3 * SHORT_MARK         // 300 ms in nanoseconds, or a dah
#define INTER_ELEMENT_GAP SHORT_MARK     // the space between pulses 
#define SHORT_GAP SHORT_MARK * 3         // the space between letters 
#define LONG_GAP SHORT_MARK * 7        // the space between words 

/*
 *  Define functions to send morse code 
 */ 

void dit(const struct device* u, int pinA, int pinB) {
    int64_t time_stamp;
    int64_t milliseconds_spent;

    time_stamp = k_uptime_get();
    while (true) {
        gpio_pin_set(u, pinA, 0);
        gpio_pin_set(u, pinB, 0);
        gpio_pin_set(u, pinA, 1);
        gpio_pin_set(u, pinB, 1);
        milliseconds_spent = k_uptime_get() - time_stamp;
        if (milliseconds_spent >= SHORT_MARK) {
            return;
        }
    }
}  

void dah(const struct device* u, int pinA, int pinB) {
    int64_t time_stamp;
    int64_t milliseconds_spent;

    time_stamp = k_uptime_get();
    while (true) {
        gpio_pin_set(u, pinA, 0);
        gpio_pin_set(u, pinB, 0);
        gpio_pin_set(u, pinA, 1);
        gpio_pin_set(u, pinB, 1);
        milliseconds_spent = k_uptime_get() - time_stamp;   // k_uptime_delta(&time_stamp); was not working
        if (milliseconds_spent >= LONG_MARK) {
            return;
        }
    }
}

void tiny_gap(const struct device* u, int pinA, int pinB) {
    int64_t time_stamp;
    int64_t milliseconds_spent;

    time_stamp = k_uptime_get();
    while (true) {
        gpio_pin_set(u, pinA, 0);
        gpio_pin_set(u, pinB, 0);
        milliseconds_spent = k_uptime_get() - time_stamp;    
        if (milliseconds_spent >= INTER_ELEMENT_GAP) {
            return;
        }
    }
}

void letter_gap(const struct device* u, int pinA, int pinB) {
    int64_t time_stamp;
    int64_t milliseconds_spent;

    time_stamp = k_uptime_get();
    while (true) {
        gpio_pin_set(u, pinA, 0);
        gpio_pin_set(u, pinB, 0);
        milliseconds_spent = k_uptime_get() - time_stamp;
        if (milliseconds_spent >= SHORT_GAP) {
            return;
        }
    }
}

void word_gap(const struct device* u, int pinA, int pinB) {
    int64_t time_stamp;
    int64_t milliseconds_spent;

    time_stamp = k_uptime_get();
    while (true) {
        gpio_pin_set(u, pinA, 0);
        gpio_pin_set(u, pinB, 0);
        milliseconds_spent = k_uptime_get() - time_stamp;
        if (milliseconds_spent >= LONG_GAP) {
           
            return;
        }   
    }
}



void send_unencapsulated_character(const struct device* u, int pinA, int pinB, char c) {
    c = toupper(c);
    
    char morse[8];

    if (c == 'A') strncpy(morse, ".*", 8);
    else if (c == 'B') strncpy(morse, "*...", 8);
    else if (c == 'C') strncpy(morse, "*.*.", 8);
    else if (c == 'D') strncpy(morse, "*..", 8);
    else if (c == 'E') strncpy(morse, ".", 8);
    else if (c == 'F') strncpy(morse, "..*.", 8);
    else if (c == 'G') strncpy(morse, "**.", 8);
    else if (c == 'H') strncpy(morse, "....", 8);
    else if (c == 'I') strncpy(morse, "..", 8);
    else if (c == 'J') strncpy(morse, ".***", 8);
    else if (c == 'K') strncpy(morse, "*.*.", 8);
    else if (c == 'L') strncpy(morse, ".*..", 8);
    else if (c == 'M') strncpy(morse, "**", 8);
    else if (c == 'N') strncpy(morse, "*.", 8);
    else if (c == 'O') strncpy(morse, "***", 8);
    else if (c == 'P') strncpy(morse, ".**.", 8);
    else if (c == 'Q') strncpy(morse, "**.*", 8);
    else if (c == 'R') strncpy(morse, ".*.", 8);
    else if (c == 'S') strncpy(morse, "...", 8);
    else if (c == 'T') strncpy(morse, "*", 8);
    else if (c == 'U') strncpy(morse, "..*", 8);
    else if (c == 'V') strncpy(morse, "...*", 8);   
    else if (c == 'W') strncpy(morse, ".**", 8);
    else if (c == 'X') strncpy(morse, "*..*", 8);
    else if (c == 'Y') strncpy(morse, "*.**", 8);
    else if (c == 'Z') strncpy(morse, "**..", 8);

    else if (c == '1') strncpy(morse, ".****", 8);
    else if (c == '2') strncpy(morse, "..***", 8);
    else if (c == '3') strncpy(morse, "...**", 8);
    else if (c == '4') strncpy(morse, "....*", 8);
    else if (c == '5') strncpy(morse, ".....", 8);
    else if (c == '6') strncpy(morse, "*....", 8);
    else if (c == '7') strncpy(morse, "**...", 8);  
    else if (c == '8') strncpy(morse, "***..", 8);
    else if (c == '9') strncpy(morse, "****.", 8);
    else if (c == '0') strncpy(morse, "*****", 8);
    else;

    size_t len = strlen(morse);

    for (int i = 0; i < len; ++i) {
        if (morse[i] == '.') {
            dit(u, pinA, pinB);
        }
        else if (morse[i] == '*') {
            dah(u, pinA, pinB);
        }
        else {
        }
        if (i < len - 1) {
            tiny_gap(u, pinA, pinB);
        }
    }
}

void send_prosign(const struct device* u, int pinA, int pinB, char c) {
    send_unencapsulated_character(u, pinA, pinB, c);
    tiny_gap(u, pinA, pinB);
}

void send_followed_character(const struct device* u, int pinA, int pinB, char c) {
    send_unencapsulated_character(u, pinA, pinB, c);
    letter_gap(u, pinA, pinB);
}

void send_end_of_word_character(const struct device* u, int pinA, int pinB, char c) {
    send_unencapsulated_character(u, pinA, pinB, c);
    word_gap(u, pinA, pinB);
}

int main() {

/*
 *  Set up the device for sending
 */

    const struct device *dev = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0)));      // Obtain a binding to the gpio, or whatever that means
    gpio_pin_configure(dev, LED_ROW3_GPIO_PIN, GPIO_OUTPUT);                     // Configure the pins for output
    gpio_pin_configure(dev, LED_COL3_GPIO_PIN, GPIO_OUTPUT);                     // Configure the pins for output
    

    while (1) {
	send_followed_character(dev, LED_ROW3_GPIO_PIN, LED_COL3_GPIO_PIN, 'C');
        send_followed_character(dev, LED_ROW3_GPIO_PIN, LED_COL3_GPIO_PIN, 'O');
        send_followed_character(dev, LED_ROW3_GPIO_PIN, LED_COL3_GPIO_PIN, 'D');
        send_followed_character(dev, LED_ROW3_GPIO_PIN, LED_COL3_GPIO_PIN, 'E');
        send_end_of_word_character(dev, LED_ROW3_GPIO_PIN, LED_COL3_GPIO_PIN, 'X');
    }

    return(0);
}

/*

Before banging the row, do we have to set our columns?
Before banging the column, do we have to set our rows?
After we set the row or column, is there slippage that must happen?
    Yes!
Is the first_time necessary?
*/

