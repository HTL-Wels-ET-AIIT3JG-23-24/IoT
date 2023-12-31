/**
  ******************************************************************************
  * @file    stm32f429zi_nucleo.h
  * @author  MEMS Application Team
  * @version V4.0.0
  * @date    1-May-2017
  * @brief   This file contains definitions for the STM32F429ZI_NUCLEO board
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
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
#ifndef __X_NUCLEO_IKS01A2_STM32F429ZI_NUCLEO_H
#define __X_NUCLEO_IKS01A2_STM32F429ZI_NUCLEO_H

#if (defined (USE_STM32F4XX_NUCLEO_144))

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/** @addtogroup BSP BOARD
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2 X_NUCLEO_IKS01A2
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2_STM32F429ZI_NUCLEO STM32F429ZI_NUCLEO
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A2_STM32F429ZI_NUCLEO_Public_Constants Public constants
 * @{
 */

/* I2C clock speed configuration (in Hz) */
#define BOARD_I2C_EXPBD_SPEED                      400000

/* I2C peripheral configuration defines */
#define BOARD_I2C_EXPBD                            I2C1
#define BOARD_I2C_EXPBD_CLK_ENABLE()               __I2C1_CLK_ENABLE()
#define BOARD_I2C_EXPBD_SCL_SDA_GPIO_CLK_ENABLE()  __GPIOB_CLK_ENABLE()
#define BOARD_I2C_EXPBD_SCL_SDA_AF                 GPIO_AF4_I2C1
#define BOARD_I2C_EXPBD_SCL_SDA_GPIO_PORT          GPIOB
#define BOARD_I2C_EXPBD_SCL_PIN                    GPIO_PIN_8  /* Ard D15 */
#define BOARD_I2C_EXPBD_SDA_PIN                    GPIO_PIN_9  /* Ard D14 */

#define BOARD_I2C_EXPBD_FORCE_RESET()              __I2C1_FORCE_RESET()
#define BOARD_I2C_EXPBD_RELEASE_RESET()            __I2C1_RELEASE_RESET()

#define BOARD_I2C_EXPBD_EV_IRQn                    I2C1_EV_IRQn
#define BOARD_I2C_EXPBD_ER_IRQn                    I2C1_ER_IRQn
#define BOARD_I2C_EXPBD_IRQ_PRI_LEVEL              0x00

#define BOARD_I2C_EXPBD_SET_CLK_SOURCE()           do { } while(0)

#define BOARD_I2C_EXPBD_SET_CLK_SPEED(x)           do { \
                                                      (x)->ClockSpeed = BOARD_I2C_EXPBD_SPEED; \
                                                      (x)->DutyCycle  = I2C_DUTYCYCLE_2; \
                                                    } while(0)

#define BOARD_I2C_EXPBD_SET_FAST_MODE()            do { } while(0)

#define BOARD_I2C_EXPBD_GPIO_SPEED                 GPIO_SPEED_FAST

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define BOARD_I2C_EXPBD_TIMEOUT_MAX                0x1000 /*<! The value of the maximal timeout for BUS waiting loops */

/* Definition for interrupt Pins */
#define LPS22H_INT1_O_GPIO_PORT                     GPIOE
#define LPS22H_INT1_O_GPIO_CLK_ENABLE()             __GPIOE_CLK_ENABLE()
#define LPS22H_INT1_O_GPIO_CLK_DISABLE()            __GPIOE_CLK_DISABLE()
#define LPS22H_INT1_O_PIN                           GPIO_PIN_9 /* Ard D6 */
#define LPS22H_INT1_O_EXTI_IRQn                     EXTI9_5_IRQn

#define LSM6DSL_INT1_O_GPIO_PORT                    GPIOF
#define LSM6DSL_INT1_O_GPIO_CLK_ENABLE()            __GPIOF_CLK_ENABLE()
#define LSM6DSL_INT1_O_GPIO_CLK_DISABLE()           __GPIOF_CLK_DISABLE()
#define LSM6DSL_INT1_O_PIN                          GPIO_PIN_14  /* Ard D4 */
#define LSM6DSL_INT1_O_EXTI_IRQn                    EXTI15_10_IRQn

#define M_INT1_O_GPIO_PORT                          GPIOF
#define M_INT1_O_GPIO_CLK_ENABLE()                  __GPIOF_CLK_ENABLE()
#define M_INT1_O_GPIO_CLK_DISABLE()                 __GPIOF_CLK_DISABLE()
#define M_INT1_O_PIN                                GPIO_PIN_10   /* Ard A5 */
#define M_INT1_O_EXTI_IRQn                          EXTI15_10_IRQn

#define M_INT2_O_GPIO_PORT                          GPIOF
#define M_INT2_O_GPIO_CLK_ENABLE()                  __GPIOF_CLK_ENABLE()
#define M_INT2_O_GPIO_CLK_DISABLE()                 __GPIOF_CLK_DISABLE()
#define M_INT2_O_PIN                                GPIO_PIN_5   /* Ard A4 */
#define M_INT2_O_EXTI_IRQn                          EXTI9_5_IRQn

#define LSM6DSL_INT2_O_GPIO_PORT                    GPIOE
#define LSM6DSL_INT2_O_GPIO_CLK_ENABLE()            __GPIOE_CLK_ENABLE()
#define LSM6DSL_INT2_O_GPIO_CLK_DISABLE()           __GPIOE_CLK_DISABLE()
#define LSM6DSL_INT2_O_PIN                          GPIO_PIN_11  /* Ard D5 */
#define LSM6DSL_INT2_O_EXTI_IRQn                    EXTI15_10_IRQn

/* Ready for use */
#define USER_INT_O_GPIO_PORT                        GPIOF
#define USER_INT_O_GPIO_CLK_ENABLE()                __GPIOF_CLK_ENABLE()
#define USER_INT_O_GPIO_CLK_DISABLE()               __GPIOF_CLK_DISABLE()
#define USER_INT_O_PIN                              GPIO_PIN_15 /* Ard D2 */
#define USER_INT_O_EXTI_IRQn                        EXTI15_10_IRQn

/* Ready for use */
#define LSM303AGR_DRDY_O_GPIO_PORT                  GPIOC
#define LSM303AGR_DRDY_O_GPIO_CLK_ENABLE()          __GPIOC_CLK_ENABLE()
#define LSM303AGR_DRDY_O_GPIO_CLK_DISABLE()         __GPIOC_CLK_DISABLE()
#define LSM303AGR_DRDY_O_PIN                        GPIO_PIN_3   /* Ard A2 */
#define LSM303AGR_DRDY_O_EXTI_IRQn                  EXTI3_IRQn

/* Ready for use */
#define LSM303AGR_INT_O_GPIO_PORT                   GPIOF
#define LSM303AGR_INT_O_GPIO_CLK_ENABLE()           __GPIOF_CLK_ENABLE()
#define LSM303AGR_INT_O_GPIO_CLK_DISABLE()          __GPIOF_CLK_DISABLE()
#define LSM303AGR_INT_O_PIN                         GPIO_PIN_3  /* Ard A3 */
#define LSM303AGR_INT_O_EXTI_IRQn                   EXTI3_IRQn

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* USE_STM32F429ZI_NUCLEO_BOARD */

#endif /* __X_NUCLEO_IKS01A2_STM32F429ZI_NUCLEO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
