#include <zephyr.h>
                                                                               // because we are on the Zephyr Operating System
#include <drivers/gpio.h>

#include <timing/timing.h>

#define LED_ROW3_GPIO_PIN 15                                                  
                                                                               // because 15 is the pin number for the third row 
                                                                               
#define LED_ROW3_GPIO_PORT DT_LABEL(DT_NODELABEL(gpio0))                       
                                                                               // because 15 is the pin number on gpio device 0
#define LED_COL3_GPIO_PIN 31 
                                                                               // because 31 is the pin number for the middle column 
#define LED_COL3_GPIO_PORT DT_LABEL(DT_NODELABEL(gpio0))

int main() {
    const k_timeout_t SLIP_TIME = K_MSEC(16); 
    const k_timeout_t REMAINDER_TIME = K_MSEC(32 -  16);
    uint32_t cnt = 0;
    bool first_time = true; 
    struct device *dev;                                                        
                     
    dev = device_get_binding(DT_LABEL(DT_NODELABEL(gpio0)));                   // because we need to bind the device we call gpio0? 
                                                                               // because we need a mechanism to control access? 

    gpio_pin_configure(dev, LED_ROW3_GPIO_PIN, GPIO_OUTPUT);                  // because we need to set up row 3's gpio pin for output
    gpio_pin_configure(dev, LED_COL3_GPIO_PIN, GPIO_OUTPUT);                  // because we need to set up col 3's gpio pin for output

    while (true) {
        gpio_pin_set(dev, LED_COL3_GPIO_PIN, cnt % 2);
        k_sleep(SLIP_TIME);
        gpio_pin_set(dev, LED_ROW3_GPIO_PIN, cnt % 2);
        k_sleep(REMAINDER_TIME);
        first_time = false;
        cnt++;
        cnt %= 2;
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

