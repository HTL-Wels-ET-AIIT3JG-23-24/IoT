/**
  ******************************************************************************
  * @file    stm32f4xx_periph_conf.h
  * @author  Central LAB
 * @version	3.0.0
 * @date	20-July-2018
  * @brief   peripherals configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2018 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F4xx_PERIPH_CONF_H
#define __STM32F4xx_PERIPH_CONF_H

/** @addtogroup FFT_DEMO_NUCLEO_F429ZI
  * @{
  */
   


#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* Exported constants --------------------------------------------------------*/
#ifdef STM32F429xx
/* USART3 */
#define USART3_CMN_DEFAULT_BAUDRATE    115200
#define USART3_CMN_DEFAULT_WORLDLENGTH UART_WORDLENGTH_8B
#define USART3_CMN_DEFAULT_STOPBITS    UART_STOPBITS_1
#define USART3_CMN_DEFAULT_PARITY      UART_PARITY_NONE
#define USART3_CMN_DEFAULT_HWFLOWCTL   UART_HWCONTROL_NONE
#define USART3_CMN_DEFAULT_MODE        UART_MODE_TX_RX

#define USART3_CMN_DEFAULT_CLK_ENABLE()         __USART3_CLK_ENABLE();
#define USART3_CMN_DEFAULT_RX_GPIO_CLK_ENABLE() __GPIOD_CLK_ENABLE()
#define USART3_CMN_DEFAULT_TX_GPIO_CLK_ENABLE() __GPIOD_CLK_ENABLE() 

#define USART3_CMN_DEFAULT_FORCE_RESET()        __USART3_FORCE_RESET()
#define USART3_CMN_DEFAULT_RELEASE_RESET()      __USART3_RELEASE_RESET()

#define USART3_CMN_DEFAULT_TX_PIN                    GPIO_PIN_8
#define USART3_CMN_DEFAULT_TX_GPIO_PORT              GPIOD
#define USART3_CMN_DEFAULT_TX_AF                     GPIO_AF7_USART3
#define USART3_CMN_DEFAULT_RX_PIN                    GPIO_PIN_9
#define USART3_CMN_DEFAULT_RX_GPIO_PORT              GPIOD
#define USART3_CMN_DEFAULT_RX_AF                     GPIO_AF7_USART3
#else /* STM32F429xx */
/* USART2 */
#define USART2_CMN_DEFAULT_BAUDRATE    115200
#define USART2_CMN_DEFAULT_WORLDLENGTH UART_WORDLENGTH_8B
#define USART2_CMN_DEFAULT_STOPBITS    UART_STOPBITS_1
#define USART2_CMN_DEFAULT_PARITY      UART_PARITY_NONE
#define USART2_CMN_DEFAULT_HWFLOWCTL   UART_HWCONTROL_NONE
#define USART2_CMN_DEFAULT_MODE        UART_MODE_TX_RX

#define USART2_CMN_DEFAULT_CLK_ENABLE()         __USART2_CLK_ENABLE();
#define USART2_CMN_DEFAULT_RX_GPIO_CLK_ENABLE() __GPIOA_CLK_ENABLE()
#define USART2_CMN_DEFAULT_TX_GPIO_CLK_ENABLE() __GPIOA_CLK_ENABLE() 

#define USART2_CMN_DEFAULT_FORCE_RESET()        __USART2_FORCE_RESET()
#define USART2_CMN_DEFAULT_RELEASE_RESET()      __USART2_RELEASE_RESET()

#define USART2_CMN_DEFAULT_TX_PIN       GPIO_PIN_2
#define USART2_CMN_DEFAULT_TX_GPIO_PORT GPIOA  
#define USART2_CMN_DEFAULT_TX_AF        GPIO_AF7_USART2
#define USART2_CMN_DEFAULT_RX_PIN       GPIO_PIN_3
#define USART2_CMN_DEFAULT_RX_GPIO_PORT GPIOA 
#define USART2_CMN_DEFAULT_RX_AF        GPIO_AF7_USART2
#endif /* STM32F429xx */

/* I2C1 */
#define I2C1_CMN_DEFAULT_CLOCKSPEED      400000
#define I2C1_CMN_DEFAULT_DUTYCYCLE       I2C_DUTYCYCLE_2
#define I2C1_CMN_DEFAULT_OWNADDRESS1     0x33
#define I2C1_CMN_DEFAULT_OWNADDRESS2     0
#define I2C1_CMN_DEFAULT_ADDRESSINGMODE  I2C_ADDRESSINGMODE_7BIT
#define I2C1_CMN_DEFAULT_DUALADDRESSMODE I2C_DUALADDRESS_DISABLED
#define I2C1_CMN_DEFAULT_GENERALCALLMODE I2C_GENERALCALL_DISABLED
#define I2C1_CMN_DEFAULT_NOSTRETCHMODE   I2C_NOSTRETCH_DISABLED

#define I2C1_CMN_DEFAULT_CLK_ENABLE()               __I2C1_CLK_ENABLE()
#define I2C1_CMN_DEFAULT_SCL_SDA_GPIO_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define I2C1_CMN_DEFAULT_SCL_SDA_AF                 GPIO_AF4_I2C1
#define I2C1_CMN_DEFAULT_SCL_SDA_GPIO_PORT          GPIOB
#define I2C1_CMN_DEFAULT_SCL_PIN                    GPIO_PIN_8
#define I2C1_CMN_DEFAULT_SDA_PIN                    GPIO_PIN_9

#define I2C1_CMN_DEFAULT_FORCE_RESET()              __I2C1_FORCE_RESET()
#define I2C1_CMN_DEFAULT_RELEASE_RESET()            __I2C1_RELEASE_RESET()

/* I2C interrupt requests */
#define I2C1_CMN_DEFAULT_EV_IRQn                    I2C1_EV_IRQn
#define I2C1_CMN_DEFAULT_ER_IRQn                    I2C1_ER_IRQn

#ifdef __cplusplus
}
#endif


/**
 * @}
 */

#endif /* __STM32F4xx_PERIPH_CONF_H */


/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
