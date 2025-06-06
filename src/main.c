#include <stdio.h>
#include <string.h>
#include "stm8s.h"
#include "stm8s_it.h"
#define LED_GPIO_PORT (GPIOA)
#define LED_GPIO_PINS (GPIO_PIN_3)

#define IR_GPIO_PORT (GPIOB)
#define IR_GPIO_PINS (GPIO_PIN_3)

extern volatile uint16_t lastCapture;
extern volatile uint16_t pulseWidth;
extern volatile uint8_t newData;

extern volatile uint32_t millis_counter;

extern volatile uint16_t ir_times[];
extern volatile uint8_t ir_index;
extern volatile uint8_t ir_done;
bool ir_done_rev = 0;
uint16_t CODE_IR = 0;

#define FAN_LOW_PIN GPIO_PIN_3  // PD3
#define FAN_MID_PIN GPIO_PIN_2  // PD2
#define FAN_HIGH_PIN GPIO_PIN_5 // PD5
#define FAN_PORT GPIOD

#define BUZZER_PIN GPIO_PIN_1 // PD1

#define MOTOR_SWING_PIN GPIO_PIN_3 // PC3

#define LED_8H_PIN GPIO_PIN_7    // PC7
#define LED_4H_PIN GPIO_PIN_6    // PC6
#define LED_2H_PIN GPIO_PIN_5    // PC5
#define LED_1H_PIN GPIO_PIN_4    // PC4
#define LED_SWING_PIN GPIO_PIN_5 // PB5
#define LED_PORT GPIOC

#define BTN_OFF_PIN GPIO_PIN_3   // PA3
#define BTN_SPEED_PIN GPIO_PIN_6 // PD6
#define BTN_TIMER_PIN GPIO_PIN_2 // PA2
#define BTN_SWING_PIN GPIO_PIN_1 // PA1

#define BTN_PORT GPIOD

uint8_t speedLevel = 2;
uint8_t timerLevel = 0;
uint32_t timerStart = 0;
uint16_t capture = 0;
uint32_t old_millis = 0;

const uint32_t timerDurations[] = {0, 3600000UL, 7200000UL, 14400000UL, 28800000UL};

void Delay(uint16_t nCount);

void GPIO_Config(void)
{                                                                                                 // PD4 (TIM2_CH1) input floating
  GPIO_Init(GPIOD, FAN_LOW_PIN | FAN_MID_PIN | FAN_HIGH_PIN, GPIO_MODE_OUT_PP_LOW_FAST);          // PD3, PD2, PD1 output
  GPIO_Init(GPIOC, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN | LED_4H_PIN, GPIO_MODE_OUT_PP_LOW_FAST); // PC7, PC6, PC5, PC4, PB5 output
  GPIO_Init(GPIOB, BTN_OFF_PIN, GPIO_MODE_IN_PU_NO_IT);                                           // PB4, PA3 input pull-up
  GPIO_Init(GPIOA, BTN_TIMER_PIN | BTN_SWING_PIN, GPIO_MODE_IN_PU_NO_IT);                         // PA2, PA1 input pull-up
  GPIO_Init(GPIOD, BTN_SPEED_PIN, GPIO_MODE_IN_PU_NO_IT);                                         // PD6 input pull-up
  GPIO_Init(GPIOC, MOTOR_SWING_PIN, GPIO_MODE_OUT_PP_LOW_FAST);                                   // PC3 output cho Motor Swing
  GPIO_Init(GPIOB, LED_SWING_PIN, GPIO_MODE_OUT_PP_LOW_FAST);                                     // PB5 output cho LED Swing
  GPIO_Init(GPIOD, BUZZER_PIN, GPIO_MODE_OUT_PP_LOW_FAST);                                        // PB4 output cho Buzzer
}

void TIM2_Config(void)
{
  // // Cấu hình PD3 (TIM2_CH1) làm input capture
  // GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);

  // TIM2_TimeBaseInit(TIM2_PRESCALER_128, 0xFFFF); // Tốc độ thấp để đo xung
  // TIM2_ICInit(TIM2_CHANNEL_1,
  //             TIM2_ICPOLARITY_RISING,
  //             TIM2_ICSELECTION_DIRECTTI,
  //             TIM2_ICPSC_DIV1,
  //             0);
  // TIM2_Cmd(ENABLE);
  // TIM2_ITConfig(TIM2_IT_CC1, ENABLE);

  // enableInterrupts();
  // Bật clock cho TIM2
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER2, ENABLE);

  // Cấu hình PD4 là input floating
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT);

  // Timer prescaler = 16 → 1 tick = 1us (với 16MHz)
  TIM2->PSCR = 4; // 2^4 = 16
  TIM2->ARRH = 0xFF;
  TIM2->ARRL = 0xFF;

  // Cấu hình TIM2_CH1 input capture
  TIM2->CCMR1 = 0x01; // IC1 on TI1
  TIM2->CCER1 = 0x01; // Enable capture, rising edge

  // Bật ngắt CC1 (capture)
  TIM2->IER |= TIM2_IER_CC1IE;

  // Bật timer
  TIM2->CR1 |= TIM2_CR1_CEN;

  // Bật ngắt toàn cục
  enableInterrupts();
}

void TIM4_Config(void)
{
  CLK->PCKENR1 |= CLK_PCKENR1_TIM4; // Bật clock cho TIM4
  TIM4->PSCR = 0x07;                // Prescaler = 128 → f = 125kHz
  TIM4->ARR = 125 - 1;              // 125 ticks = 1ms (1 tick = 8 µs)
  TIM4->IER |= TIM4_IER_UIE;        // Cho phép ngắt update
  TIM4->CR1 |= TIM4_CR1_CEN;        // Bật Timer
  enableInterrupts();               // Cho phép toàn cục
}

// void UART_Config(void)
// {
//   UART1_DeInit();
//   UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1,
//              UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TX_ENABLE);
// }

uint32_t millis(void)
{
  return millis_counter;
}

uint8_t decodeNEC_fromHighs(uint8_t max, uint16_t *out)
{
  uint16_t result = 0;
  uint8_t byte_result = 0;
  for (uint8_t i = 0; i < max; i++)
  {

    // char buf[100];
    // sprintf(buf, "Edge %d: %u us", i, ir_times[i]);
    // // Gửi từng ký tự trong chuỗi buf
    // for (char *p = buf; *p != '\0'; p++)
    // {
    //   UART1_SendData8(*p);
    //   while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
    //     ;
    // }

    if (ir_times[i] < 3000)
    {
      byte_result++;
      uint32_t pulse = ir_times[i];

      result <<= 1;

      if (pulse > 800 && pulse < 2000)
        result |= 1; // bit 1
      else if (pulse < 700)
        ; // bit 0
      else
        return 3; // không hợp lệ
      if (byte_result > 14)
      {
        return 2;
      }

      if (ir_times[i + 1] > 3000)
      {
        *out = result;
        return 1;
      }
    }
    else
    {
      byte_result = 0;
    }
  }

  // *out = result;
  return 0;
}

// void UART1_SendString(const char *str)
// {
//   while (*str)
//   {
//     UART1_SendData8(*str++);
//     while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
//       ;
//   }
// }

void Fan_SetSpeed(uint8_t level)
{
  GPIO_WriteHigh(FAN_PORT, FAN_LOW_PIN | FAN_MID_PIN | FAN_HIGH_PIN);
  // char buf[64];
  // sprintf(buf, "Fan_SetSpeed %d !\n", level);
  // UART1_SendString(buf);

  switch (level)
  {
  case 0:
    GPIO_WriteHigh(FAN_PORT, FAN_LOW_PIN | FAN_MID_PIN | FAN_HIGH_PIN); // Tắt quạt
    break;
  case 1:
    GPIO_WriteLow(FAN_PORT, FAN_LOW_PIN);
    break;
  case 2:
    GPIO_WriteLow(FAN_PORT, FAN_MID_PIN);
    break;
  case 3:
    GPIO_WriteLow(FAN_PORT, FAN_HIGH_PIN);
    break;
  }
}

void BUZZER_Config(void)
{
  GPIO_WriteHigh(GPIOD, BUZZER_PIN); // Bật Buzzer
  Delay(100);                        // Giữ trong 1 giây
  GPIO_WriteLow(GPIOD, BUZZER_PIN);  // Tắt Buzzer
}

void HandleIR(void)
{
  if (newData)
  {
    newData = 0;
    ir_done_rev = 0;
    old_millis = millis();
    ir_times[ir_index++] = pulseWidth;
  }
  if (millis() - old_millis > 15 && ir_done_rev == 0)
  {
    ir_done_rev = 1;
    old_millis = millis();
    // GPIO_WriteReverse(LED_GPIO_PORT, (GPIO_Pin_TypeDef)LED_GPIO_PINS);

    // for (uint8_t i = 0; i < ir_index; i++)
    // {
    //   char buf[100];
    //   sprintf(buf, "Edge %d: %u us", i, ir_times[i]);
    //   // Gửi từng ký tự trong chuỗi buf
    //   for (char *p = buf; *p != '\0'; p++)
    //   {
    //     UART1_SendData8(*p);
    //     while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET)
    //       ;
    //   }
    // }

    if (ir_index > 30)
    {

      uint8_t a = decodeNEC_fromHighs(ir_index, &CODE_IR);
      if (a == 1)
      {
        // char buf[100];
        // sprintf(buf, "NEC OK: %d\r\n", CODE_IR);
        // UART1_SendString(buf);
      }
      else
      {
        CODE_IR = 0; // Reset mã lệnh nếu không hợp lệ
        // char buf[64];
        // sprintf(buf, "ERROR %d NEC!\n", a);
        // UART1_SendString(buf);
      }
    }

    ir_index = 0;
  }
}

void HandleButtonAndIRCode(void)
{
  if ((CODE_IR == 319) || (GPIO_ReadInputPin(GPIOA, BTN_TIMER_PIN) == 0))
  {
    CODE_IR = 0;    // Reset sau khi nhận lệnh
    speedLevel = 0; // Tắt quạt
    timerLevel = 0; // Tắt hẹn giờ
    Fan_SetSpeed(speedLevel);
    BUZZER_Config(); // Bật buzzer
  }
  else if ((CODE_IR == 311) || (GPIO_ReadInputPin(GPIOD, BTN_SPEED_PIN) == 0))
  {
    CODE_IR = 0; // Reset sau khi nhận lệnh
    // Fan_SetSpeed(0);
    speedLevel++;
    if (speedLevel > 3)
      speedLevel = 1; // Quay lại mức 1 nếu vượt quá 3
    Fan_SetSpeed(speedLevel);
    BUZZER_Config(); // Bật buzzer
  }
  else if (CODE_IR == 315 || GPIO_ReadInputPin(GPIOA, BTN_TIMER_PIN) == 0)
  {

    CODE_IR = 0; // Reset sau khi nhận lệnh
    if (speedLevel > 0)
    {
      timerLevel++;
      BUZZER_Config(); // Bật buzzer
    }

    if (timerLevel > 4)
      timerLevel = 0; // Quay lại mức 0 nếu vượt quá 4
  }
  else if (CODE_IR == 318 || GPIO_ReadInputPin(GPIOA, BTN_SWING_PIN) == 0)
  {

    CODE_IR = 0; // Reset sau khi nhận lệnh
    uint8_t new_state = !GPIO_ReadInputPin(GPIOB, LED_SWING_PIN);
    if (new_state && speedLevel > 0)
    {
      // Bật chế độ swing
      GPIO_WriteHigh(GPIOB, LED_SWING_PIN);   // Bật LED
      GPIO_WriteHigh(GPIOC, MOTOR_SWING_PIN); // Bật Motor
    }
    else
    {
      // Tắt chế độ swing
      GPIO_WriteLow(GPIOB, LED_SWING_PIN);   // Tắt LED
      GPIO_WriteLow(GPIOC, MOTOR_SWING_PIN); // Tắt Motor
    }
    BUZZER_Config(); // Bật buzzer
  }
}

void HandleTimerAndLED(void)
{
  // switch (timerLevel)
  // {
  // case 0:
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN | LED_8H_PIN); // Tắt tất cả đèn
  //   timerStart = 0;
  //   break;
  // case 1:
  //   GPIO_WriteLow(LED_PORT, LED_1H_PIN); // Bật đèn 1 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_2H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   if (timerStart == 0)
  //   {
  //     timerStart = millis();
  //   }
  //   if (millis() - timerStart >= timerDurations[1])
  //   {
  //     speedLevel = 0; // Tắt quạt sau 1 giờ
  //     Fan_SetSpeed(speedLevel);
  //     timerLevel = 0; // Reset hẹn giờ
  //     BUZZER_Config(); // Bật buzzer
  //   }
  //   break;
  // case 2:
  //   GPIO_WriteLow(LED_PORT, LED_2H_PIN); // Bật đèn 2 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   if (timerStart == 0)
  //   {
  //     timerStart = millis();
  //   }
  //   if (millis() - timerStart >= timerDurations[2])
  //   {
  //     speedLevel = 0; // Tắt quạt sau 2 giờ
  //     Fan_SetSpeed(speedLevel);
  //     timerLevel = 0; // Reset hẹn giờ
  //     BUZZER_Config(); // Bật buzzer
  //   }
  //   if(millis() - timerStart >= timerDurations[1])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_2H_PIN); // Bật đèn 2 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   else
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_1H_PIN); // Bật đèn 1 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_2H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   break;
  // case 3:
  //   GPIO_WriteLow(LED_PORT, LED_4H_PIN); // Bật đèn 4 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN);
  //   if (timerStart == 0)
  //   {
  //     timerStart = millis();
  //   }
  //   if (millis() - timerStart >= timerDurations[3])
  //   {
  //     speedLevel = 0; // Tắt quạt sau 4 giờ
  //     Fan_SetSpeed(speedLevel);
  //     timerLevel = 0; // Reset hẹn giờ
  //     BUZZER_Config(); // Bật buzzer
  //   }
  //   if(millis() - timerStart >= timerDurations[2])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_4H_PIN); // Bật đèn 4 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN);
  //   }
  //   else if (millis() - timerStart >= timerDurations[1])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_2H_PIN); // Bật đèn 2 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   else
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_1H_PIN); // Bật đèn 1 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_2H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   break;
  // case 4:
  //   // GPIO_WriteLow(LED_PORT, LED_8H_PIN); // Bật đèn 8 giờ
  //   // GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN);
  //   if (timerStart == 0)
  //   {
  //     timerStart = millis();
  //   }
  //   if (millis() - timerStart >= timerDurations[4])
  //   {
  //     speedLevel = 0; // Tắt quạt sau 8 giờ
  //     Fan_SetSpeed(speedLevel);
  //     timerLevel = 0; // Reset hẹn giờ
  //     BUZZER_Config(); // Bật buzzer
  //   }
  //   if(millis() - timerStart >= timerDurations[3])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_8H_PIN); // Bật đèn 8 giờ
  //   GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN);
  //   }
  //   else if ( millis() - timerStart >= timerDurations[2])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_4H_PIN); // Bật đèn 4 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN);
  //   }
  //   else if (millis() - timerStart >= timerDurations[1])
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_2H_PIN); // Bật đèn 2 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   else
  //   {
  //     GPIO_WriteLow(LED_PORT, LED_1H_PIN); // Bật đèn 1 giờ
  //     GPIO_WriteHigh(LED_PORT, LED_2H_PIN | LED_4H_PIN | LED_8H_PIN);
  //   }
  //   break;
  // default:
  //   break;
  // }

  switch (timerLevel)
  {
  case 0:
    GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN | LED_8H_PIN); // Tắt tất cả đèn
    timerStart = 0;
    break;
  default:
  {
    if (timerStart == 0)
      timerStart = millis();
    uint32_t elapsed = millis() - timerStart;

    // Kiểm tra hết giờ
    if (timerLevel > 0 && timerLevel < 5 && elapsed >= timerDurations[timerLevel])
    {
      speedLevel = 0; // Tắt quạt
      Fan_SetSpeed(speedLevel);
      timerLevel = 0;                                                              // Reset hẹn giờ
      BUZZER_Config();                                                             // Bật buzzer
      GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN | LED_8H_PIN); // Tắt tất cả đèn
      timerStart = 0;
      break;
    }

    // Xác định trạng thái LED theo thời gian còn lại
    if (elapsed >= timerDurations[4])
    {
      // Không cần xử lý vì đã reset ở trên
    }
    else if (elapsed >= timerDurations[3])
    {
      GPIO_WriteLow(LED_PORT, LED_8H_PIN);
      GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_4H_PIN);
    }
    else if (elapsed >= timerDurations[2])
    {
      GPIO_WriteLow(LED_PORT, LED_4H_PIN);
      GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN);
    }
    else if (elapsed >= timerDurations[1])
    {
      GPIO_WriteLow(LED_PORT, LED_2H_PIN);
      GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_4H_PIN | LED_8H_PIN);
    }
    else
    {
      GPIO_WriteLow(LED_PORT, LED_1H_PIN);
      GPIO_WriteHigh(LED_PORT, LED_2H_PIN | LED_4H_PIN | LED_8H_PIN);
    }
    break;
  }
  }
}
void main(void)
{
  // Cấu hình hệ thống
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // Chia 1 → 16MHz

  disableInterrupts();
  GPIO_Config();
  TIM2_Config();
  TIM4_Config();
  // UART_Config();
  BUZZER_Config(); // Bật buzzer
  enableInterrupts();
  Fan_SetSpeed(speedLevel);                                                                    // Tắt quạt ban đầu
  GPIO_WriteHigh(LED_PORT, LED_1H_PIN | LED_2H_PIN | LED_8H_PIN | LED_4H_PIN | LED_SWING_PIN); // Tắt tất cả đèn
  GPIO_WriteHigh(GPIOC, MOTOR_SWING_PIN);                                                      // Tắt Motor Swing
  GPIO_WriteHigh(GPIOB, LED_SWING_PIN);                                                        // Tắt LED Swing

  while (1)
  {
    HandleIR();
    HandleButtonAndIRCode();
    HandleTimerAndLED();
  }
}

/**
 * @brief Delay
 * @param nCount
 * @retval None
 */
void Delay(uint16_t nCount)
{

  for (uint16_t i = 0; i < nCount; i++)
  {
    for (uint16_t j = 0; j < 1600; j++)
    {
      // __asm__("nop"); // Lệnh chờ 1 chu kỳ, tránh tối ưu hóa
    }
  }
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
