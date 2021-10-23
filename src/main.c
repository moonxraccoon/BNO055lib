#include <stm32f4xx.h>
#include <stdbool.h>
#include "stm32/f4/gpio/gpio.h"
#include "stm32/f4/delay/delay.h"
#include "stm32/f4/uart/uart.h"
#include "stm32/f4/i2c/i2c.h" 
#include "drivers/mpu6050/mpu.h"
#include "bitutils.h"
#include "stm32/f4/rcc/rcc.h"
#include "stm32/f4/timer/timer.h"
#include "stm32/stm32.h"
#include "stm32/f4/timer/timer.h"
#include "bno/bno.h"
//#include "stm32/f4/exti/exti.h"

#define DEBUG_LED   PB8
#define TEST_LED    PA8


bno_t bno;

void toggle_test_led(void) {
    GPIO_toggle(DEBUG_LED);        
}



int main(void) {

    RCC_system_clock_config(rcc_hse_25_mhz_to_96_mhz);   
    cosmicOS_init();
    
    I2C_port i2c1 = {
        .i2c = I2C1,
        .frequency = 16,
        .mode = I2C_STD_MODE,
        .duty = 0,
    };

    USART_port port = {
        .usart = USART2,
        .baud = 115200,
        .mode = USART_RX_TX_MODE,
        .stop_bits = 0,
        .parity_enable = 0,
        .parity_even_odd = 0,
        .interrupt_driven = true,
    };
    timer_port_t tim5 = {
        .timer = TIM5,
        .prescaler = apb1_freq/1000,
        .autoreload = 200,
        .func = toggle_test_led,
        .interrup_en = true,
    };
    GPIO_enable(DEBUG_LED, GPIO_OUTPUT);
    GPIO_enable(PA8, GPIO_OUTPUT);
    
    USART_init(&port);   
    //USART_init(&gps);
    USART_printf(port, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    delayMs(2000);
    I2C_init(&i2c1);
    i2c_err_t i2c_err;
    bno_err_t bno_err;
    uint8_t i2c_data[2]; 
    bno.i2c = i2c1;
    bno.mode = BNO_MODE_IMU;
    //i2c_err = I2C_write(i2c1, MPU_ADDR, 0x6B, 0x00);
    USART_printf(port, "%s\n", I2C_get_err_str(i2c_err));
    if (BNO_init(&bno)) {
        USART_printf(port, "BNO init great-success\n");
    } else {
        USART_printf(port, "BNO init failed\n");
    }
    delayMs(2000);
    
    //const clock_t *test = &RCC_25MHZ_TO_84MHZ;
    char usart_test[512];
    unsigned long int cycle = 0; 
    uint8_t bit_test = 0;
    usart_err_t usart_err;
    USART_printf(port, "APB2 clock: %d\n", ahb_freq);
    uint32_t last_time = millis();
    TIM_init(&tim5);
    while (1) {
        USART_printf(port, "cycle: %d\n", cycle++);
        delayMs(500);
    }
}



