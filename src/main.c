/****************************************************************************

****************************************************************************/
#define __MAIN_C__


#include "stm32f10x.h"
#include "stm32f10x_conf.h"

/*=========================================================================*/
/*  DEFINE: All Structures and Common Constants                            */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: Prototypes                                                     */
/*=========================================================================*/

#define LED3                             3
#define LEDn                             2
#define LED1_PIN                         GPIO_Pin_1 // green
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOB

#define CONT_PIN                         GPIO_Pin_2
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOB


/*=========================================================================*/
/*  DEFINE: Definition of all local Data                                   */
/*=========================================================================*/
GPIO_InitTypeDef GPIO_Structure;
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN};

/*=========================================================================*/
/*  DEFINE: Definition of all local Procedures                             */
/*=========================================================================*/

/*=========================================================================*/
/*  DEFINE: All code exported                                              */
/*=========================================================================*/

void testloop()
{
    Remove me!
}

void delayLoop() {
    volatile uint32_t delayCount = 500000; // volatile, um "Wegoptimieren" zu vermeinden
    while (delayCount > 0) {
        delayCount--;
    }
}


/***************************************************************************/
/*  main                                                                   */
/***************************************************************************/
int main (void)
{
    SystemInit();    

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    

    while(1) {
        GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);
        GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);
        delayLoop();
        GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);
        GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
        delayLoop();
    }

  return(0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
