/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

typedef enum {
    LEDOFF = 0,
    LEDON = 1,
} EstadoLED;

void GPIOS(void);
void delay(uint32_t t);

int main(void) {
    GPIOS();

    EstadoLED EstadoLedActual = LEDOFF;
    uint8_t EstadoBoton = 0;
    uint8_t prevEstadoBoton = 0;

    while (1) {
        EstadoBoton = GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13);

        switch (EstadoLedActual) {
            case LEDOFF:
                if (EstadoBoton != prevEstadoBoton && EstadoBoton == Bit_SET) {
                    EstadoLedActual = LEDON;
                }
                break;
            case LEDON:
                if (EstadoBoton != prevEstadoBoton && EstadoBoton == Bit_RESET) {
                    EstadoLedActual = LEDOFF;
                }
                break;
        }

        switch (EstadoLedActual) {
            case LEDOFF:
                GPIO_SetBits(GPIOD, GPIO_Pin_10); // Enciende el LED
                break;
            case LEDON:
                GPIO_ResetBits(GPIOD, GPIO_Pin_10); // Apaga el LED
                break;
        }

        prevEstadoBoton = EstadoBoton;

        delay(100000);
    }
}

void GPIOS(void) {
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOD, ENABLE);

    // Configura PE13 como entrada del botón
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    // Configura PD10 como salida del LED
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void delay(uint32_t t) {
    while (t--);
}
