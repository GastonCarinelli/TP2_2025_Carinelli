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

#define TIME 12500

typedef enum {
	ON35=0,
	OFF35,
	ON23,
	OFF49,
	ON72,
	OFF19,

} enEstados;

void delay_ms (uint32_t ms)
{
	uint32_t i;
	while (ms)
	{
		//El for de 1ms
		for (i=0;i<TIME;i++);
		ms--;
	}

}

void arranqueGPIOS (void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

int main(void)
{
	arranqueGPIOS();
	enEstados EstadoActual= ON35;

	while (1)
	{
		switch (EstadoActual)
		{
		case ON35:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF35;
			delay_ms(35);
			break;
		case OFF35:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=ON23;
			delay_ms(35);
			break;
		case ON23:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF49;
			delay_ms(23);
			break;
		case OFF49:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
 			EstadoActual=ON72;
 			delay_ms(49);
 			break;
		case ON72:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF19;
			delay_ms(72);
			break;
		case OFF19:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=ON35;
		    delay_ms(19);
			break;

		}

	}

}
