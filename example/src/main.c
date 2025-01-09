#include <stdint.h>

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_flash_ex.h"
#include "led.h"

#define LED_PIN 5

static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  //__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSI Oscillator and activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 0x10;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 400;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;  
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
  
}

void main()
{

    HAL_Init();

    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_TypeDef* gpioa = (GPIO_TypeDef*)GPIOA;
    GPIO_InitTypeDef gpio_init =
    {

        .Pin =  GPIO_PIN_5,
        .Mode = MODE_OUTPUT,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_MEDIUM,
    };

    HAL_GPIO_Init( gpioa, &gpio_init);

    HAL_GPIO_WritePin(gpioa, GPIO_PIN_5, GPIO_PIN_SET);
    HAL_Delay(2000);
    HAL_GPIO_WritePin(gpioa, GPIO_PIN_5, GPIO_PIN_RESET);


    while (1)
    {
        HAL_GPIO_TogglePin( gpioa, GPIO_PIN_5);
        HAL_Delay(1000);
        //HAL_GPIO_WritePin(gpioa, GPIO_PIN_5, GPIO_PIN_RESET);
        //HAL_GPIO_WritePin(gpioa, GPIO_PIN_5, GPIO_PIN_SET);
    }

    //RCC_TypeDef* rcc = (RCC_TypeDef*)RCC;
    //ledPeripheralClockEnable(&(rcc->AHB1ENR), RCC_AHB1ENR_GPIOAEN_Pos);

    //volatile uint32_t dummy;    // Dummy reads to wait for peripheral clock to be enabled.
    //dummy = rcc->AHB1ENR;
    //dummy = rcc->AHB1ENR;

    //GPIO_TypeDef* gpio_a = (GPIO_TypeDef*)GPIOA;
    //ledOutputMode(&(gpio_a->MODER), GPIO_MODER_MODER5_Pos);

    //while (1)
    //{
    //    ledToggle(&(gpio_a->ODR), LED_PIN);
    //    for (uint32_t i = 0; i < 100000; i++);   // Delay.
    //}
}

void Systick_Handler()
{
    HAL_IncTick();
}
