/**
  ******************************************************************************
  * @file    stm32f4xx_hal_msp.c
  * @author  Central LAB
 * @version	3.0.0
 * @date	20-July-2018
  * @brief   HAL MSP module.
  *         
  @verbatim
 ===============================================================================
                     ##### How to use this driver #####
 ===============================================================================
    [..]
    This file is generated automatically by MicroXplorer and eventually modified 
    by the user

  @endverbatim
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

/* Includes ------------------------------------------------------------------*/
#include "TargetFeatures.h"


/** @addtogroup FFT_DEMO_NUCLEO_F429ZI
  * @{
  */

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration  
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  if(huart==&UartHandle) {
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* Enable peripherals and GPIO Clocks */
    /* Enable GPIO TX/RX clock */
    USART3_CMN_DEFAULT_RX_GPIO_CLK_ENABLE();
    USART3_CMN_DEFAULT_TX_GPIO_CLK_ENABLE();
    
    /* Enable USARTx clock */
    USART3_CMN_DEFAULT_CLK_ENABLE();
    
    /* Configure peripheral GPIO */
    /* UART TX GPIO pin configuration  */
    GPIO_InitStruct.Pin       = USART3_CMN_DEFAULT_TX_PIN;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLUP;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = USART3_CMN_DEFAULT_TX_AF;
    
    HAL_GPIO_Init(USART3_CMN_DEFAULT_TX_GPIO_PORT, &GPIO_InitStruct);
    
    /* UART RX GPIO pin configuration  */
    GPIO_InitStruct.Pin = USART3_CMN_DEFAULT_RX_PIN;
    GPIO_InitStruct.Alternate = USART3_CMN_DEFAULT_RX_AF;
    
    HAL_GPIO_Init(USART3_CMN_DEFAULT_RX_GPIO_PORT, &GPIO_InitStruct);
  } 
}


/**
  * @brief UART MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
  if(huart==&UartHandle) {
    /* Reset peripherals */
    USART3_CMN_DEFAULT_FORCE_RESET();
    USART3_CMN_DEFAULT_RELEASE_RESET();
    
    /* Disable peripherals and GPIO Clocks */
    /* Configure UART Tx as alternate function  */
    HAL_GPIO_DeInit(USART3_CMN_DEFAULT_TX_GPIO_PORT, USART3_CMN_DEFAULT_TX_PIN);
    /* Configure UART Rx as alternate function  */
    HAL_GPIO_DeInit(USART3_CMN_DEFAULT_RX_GPIO_PORT, USART3_CMN_DEFAULT_RX_PIN);
  }
}


/**
 * @brief  I2C MSP Initialization
 * @param hi2c: I2C handle pointer
 * @retval None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  GPIO_InitStruct;

  /* Enable I2C GPIO clocks */
  I2C1_CMN_DEFAULT_SCL_SDA_GPIO_CLK_ENABLE();

  /* I2C_EXPBD SCL and SDA pins configuration -------------------------------------*/
  GPIO_InitStruct.Pin = I2C1_CMN_DEFAULT_SCL_PIN |I2C1_CMN_DEFAULT_SDA_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Pull  = GPIO_NOPULL;
  GPIO_InitStruct.Alternate  =I2C1_CMN_DEFAULT_SCL_SDA_AF;
  HAL_GPIO_Init(I2C1_CMN_DEFAULT_SCL_SDA_GPIO_PORT, &GPIO_InitStruct);

  /* Enable the I2C_EXPBD peripheral clock */
  I2C1_CMN_DEFAULT_CLK_ENABLE();

  /* Force the I2C peripheral clock reset */
  I2C1_CMN_DEFAULT_FORCE_RESET();

  /* Release the I2C peripheral clock reset */
  I2C1_CMN_DEFAULT_RELEASE_RESET();

  /* Enable and set I2C_EXPBD Interrupt to the highest priority */
  HAL_NVIC_SetPriority(I2C1_CMN_DEFAULT_EV_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(I2C1_CMN_DEFAULT_EV_IRQn);

  /* Enable and set I2C_EXPBD Interrupt to the highest priority */
  HAL_NVIC_SetPriority(I2C1_CMN_DEFAULT_ER_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(I2C1_CMN_DEFAULT_ER_IRQn);
}

/**
  * @brief TIM OC MSP Initialization
  * This function configures the hardware resources used in this example:
  *  - Peripheral's clock enable
  *  - Peripheral's Interrupt Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_OC_MspInit(TIM_HandleTypeDef *htim)
{ 
  /* TIM1 Peripheral clock enable */
  __HAL_RCC_TIM1_CLK_ENABLE();

  /*  Enable the TIM1 global Interrupt & set priority */
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0x8, 0);
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
}

/**
  * @brief CRC MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspInit(CRC_HandleTypeDef *hcrc)
{
  /* CRC Peripheral clock enable */
  __HAL_RCC_CRC_CLK_ENABLE();
}

/**
  * @brief CRC MSP De-Initialization
  *        This function freeze the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hcrc: CRC handle pointer
  * @retval None
  */
void HAL_CRC_MspDeInit(CRC_HandleTypeDef *hcrc)
{
  /* Enable CRC reset state */
  __HAL_RCC_CRC_FORCE_RESET();

  /* Release CRC from reset state */
  __HAL_RCC_CRC_RELEASE_RESET();
}

/**
  * @brief RTC MSP Initialization 
  *        This function configures the hardware resources used in this example
  * @param hrtc: RTC handle pointer
  * 
  * @note  Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
  *        the RTC clock source; in this case the Backup domain will be reset in  
  *        order to modify the RTC Clock source, as consequence RTC registers (including 
  *        the backup registers) and RCC_BDCR register are set to their reset values.
  *             
  * @retval None
  */
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
  RCC_OscInitTypeDef        RCC_OscInitStruct;
  RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;
  
  /* To change the source clock of the RTC feature (LSE, LSI), You have to:
     - Enable the power clock using __HAL_RCC_PWR_CLK_ENABLE()
     - Enable write access using HAL_PWR_EnableBkUpAccess() function before to 
       configure the RTC clock source (to be done once after reset).
     - Reset the Back up Domain using __HAL_RCC_BACKUPRESET_FORCE() and 
       __HAL_RCC_BACKUPRESET_RELEASE().
     - Configure the needed RTc clock source */
  
  /* Configue LSE as RTC clock source */ 
  RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_OFF;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK){ 
    while(1);
  }
  
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK){
    while(1);
  }

  /* Enable RTC Clock */ 
  __HAL_RCC_RTC_ENABLE(); 
}

/**
  * @brief RTC MSP De-Initialization 
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrtc: RTC handle pointer
  * @retval None
  */
void HAL_RTC_MspDeInit(RTC_HandleTypeDef *hrtc)
{
  /*##-1- Reset peripherals ##################################################*/
   __HAL_RCC_RTC_DISABLE();
}

void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
  /* RNG Peripheral clock enable */
  __HAL_RCC_RNG_CLK_ENABLE();
}

/**
  * @brief RNG MSP De-Initialization 
  *        This function freeze the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  * @param hrng: RNG handle pointer
  * @retval None
  */
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng)
{
  /* Enable RNG reset state */
  __HAL_RCC_RNG_FORCE_RESET();
  
  /* Release RNG from reset state */
  __HAL_RCC_RNG_RELEASE_RESET();
}

/**
 * @}
 */

/******************* (C) COPYRIGHT 2018 STMicroelectronics *****END OF FILE****/
