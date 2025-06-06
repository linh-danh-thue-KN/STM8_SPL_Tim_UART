/**
 ******************************************************************************
 * @file     stm8s_it.c
 * @author   MCD Application Team
 * @version  V2.0.4
 * @date     26-April-2018
 * @brief    Main Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/** @addtogroup GPIO_Toggle
 * @{
 */
#ifdef _COSMIC_
/**
 * @brief  Dummy interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(NonHandledInterrupt, 25)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*_COSMIC_*/

/**
 * @brief  TRAP interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
 * @brief  Top Level Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TLI_IRQHandler, 0)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Auto Wake Up Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(AWU_IRQHandler, 1)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Clock Controller Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CLK_IRQHandler, 2)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  External Interrupt PORTA Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTA_IRQHandler, 3)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  External Interrupt PORTB Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  External Interrupt PORTC Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  External Interrupt PORTD Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  External Interrupt PORTE Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTE_IRQHandler, 7)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#ifdef STM8S903
/**
 * @brief  External Interrupt PORTF Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EXTI_PORTF_IRQHandler, 8)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S903*/

#if defined(STM8S208) || defined(STM8AF52Ax)
/**
 * @brief CAN RX Interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CAN_RX_IRQHandler, 8)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  CAN TX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(CAN_TX_IRQHandler, 9)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S208 || STM8AF52Ax */

/**
 * @brief  SPI Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(SPI_IRQHandler, 10)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Timer1 Update/Overflow/Trigger/Break Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_BRK_IRQHandler, 11)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Timer1 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM1_CAP_COM_IRQHandler, 12)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#ifdef STM8S903
/**
 * @brief  Timer5 Update/Overflow/Break/Trigger Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM5_UPD_OVF_BRK_TRG_IRQHandler, 13)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
/**
 * @brief  Timer5 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM5_CAP_COM_IRQHandler, 14)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#else /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8S001 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
/**
 * @brief  Timer2 Update/Overflow/Break Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Timer2 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
volatile uint16_t lastCapture = 0;
volatile uint16_t pulseWidth = 0;
volatile uint8_t newData = 0;

#define MAX_EDGES 200

volatile uint16_t ir_times[MAX_EDGES];
volatile uint8_t ir_index = 0;
volatile uint8_t ir_done = 0;

INTERRUPT_HANDLER(TIM2_CAP_COM_IRQHandler, 14)
{

  //  if (TIM2_GetITStatus(TIM2_IT_CC1)) {
  // uint16_t capture = TIM2_GetCapture1();
  //     pulseWidth = capture - lastCapture;
  //     lastCapture = capture;
  //     newData = 1;
  //     TIM2_ClearITPendingBit(TIM2_IT_CC1);
  // }

  if (TIM2_GetITStatus(TIM2_IT_CC1))
  {
    static uint8_t last_edge = 0;
    static uint16_t last_time = 0;
    uint16_t current_time = ((uint16_t)TIM2->CCR1H << 8) | TIM2->CCR1L;
    // GPIO_WriteReverse(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_3);
    uint16_t duration;

    // Đổi bắt cạnh lên ↔ cạnh xuống luân phiên
    if (last_edge == 0)
    {
      TIM2->CCER1 |= (1 << 1); // Bắt cạnh xuống
      last_edge = 1;
      last_time = current_time;
    }
    else
    {
      TIM2->CCER1 &= ~(1 << 1); // Bắt cạnh lên
      last_edge = 0;
      pulseWidth = current_time - last_time;
      newData = 1;
    }

    // Xoá cờ capture
    TIM2_ClearITPendingBit(TIM2_IT_CC1);
  }
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S903*/

#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S105) || \
    defined(STM8S005) || defined(STM8AF62Ax) || defined(STM8AF52Ax) || defined(STM8AF626x)
/**
 * @brief Timer3 Update/Overflow/Break Interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM3_UPD_OVF_BRK_IRQHandler, 15)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  Timer3 Capture/Compare Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM3_CAP_COM_IRQHandler, 16)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S208, STM8S207 or STM8S105 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */

#if defined(STM8S208) || defined(STM8S207) || defined(STM8S007) || defined(STM8S103) || \
    defined(STM8S003) || defined(STM8S001) || defined(STM8AF62Ax) || defined(STM8AF52Ax) || defined(STM8S903)
/**
 * @brief  UART1 TX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART1_TX_IRQHandler, 17)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  UART1 RX Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART1_RX_IRQHandler, 18)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S105 || STM8S001 */

/**
 * @brief  I2C Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(I2C_IRQHandler, 19)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

#if defined(STM8S105) || defined(STM8S005) || defined(STM8AF626x)
/**
 * @brief  UART2 TX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART2_TX_IRQHandler, 20)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  UART2 RX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART2_RX_IRQHandler, 21)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /* STM8S105*/

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined(STM8AF52Ax) || defined(STM8AF62Ax)
/**
 * @brief  UART3 TX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART3_TX_IRQHandler, 20)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @brief  UART3 RX interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(UART3_RX_IRQHandler, 21)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#if defined(STM8S207) || defined(STM8S007) || defined(STM8S208) || defined(STM8AF52Ax) || defined(STM8AF62Ax)
/**
 * @brief  ADC2 interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(ADC2_IRQHandler, 22)
{

  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  return;
}
#else  /*STM8S105, STM8S103 or STM8S903 or STM8AF626x */
/**
 * @brief  ADC1 interrupt routine.
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{

  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  return;
}
#endif /*STM8S208 or STM8S207 or STM8AF52Ax or STM8AF62Ax */

#ifdef STM8S903
/**
 * @brief  Timer6 Update/Overflow/Trigger Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(TIM6_UPD_OVF_TRG_IRQHandler, 23)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#else  /*STM8S208, STM8S207, STM8S105 or STM8S103 or STM8S001 or STM8AF62Ax or STM8AF52Ax or STM8AF626x */
/**
 * @brief  Timer4 Update/Overflow Interrupt routine
 * @param  None
 * @retval None
 */
volatile uint32_t millis_counter = 0;  // Đếm số ms đã trôi qua
INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{

  if (TIM4_GetITStatus(TIM4_IT_UPDATE) != RESET)
    {
        TIM4_ClearITPendingBit(TIM4_IT_UPDATE);
        millis_counter++;
    }
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}
#endif /*STM8S903*/

/**
 * @brief  Eeprom EEC Interrupt routine
 * @param  None
 * @retval None
 */
INTERRUPT_HANDLER(EEPROM_EEC_IRQHandler, 24)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
}

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/