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
	ON25=0,
	OFF25,
	ON40,
	OFF40,
	ON110,
	OFF110,

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
	enEstados EstadoActual= ON25;

	while (1)
	{
		switch (EstadoActual)
		{
		case ON25:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF25;
			delay_ms(25);
			break;
		case OFF25:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=ON40;
			delay_ms(25);
			break;
		case ON40:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF40;
			delay_ms(40);
			break;
		case OFF40:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
 			EstadoActual=ON110;
 			delay_ms(40);
 			break;
		case ON110:
			GPIO_SetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=OFF110;
			delay_ms(110);
			break;
		case OFF110:
			GPIO_ResetBits(GPIOA,GPIO_Pin_5);
			EstadoActual=ON25;
		    delay_ms(110);
			break;

		}

	}


}
