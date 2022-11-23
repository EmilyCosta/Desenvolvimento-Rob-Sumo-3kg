/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SLFL_Pin GPIO_PIN_1
#define SLFL_GPIO_Port GPIOC
#define SLFL_EXTI_IRQn EXTI1_IRQn
#define TEMP_Pin GPIO_PIN_4
#define TEMP_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_5
#define LED_GPIO_Port GPIOA
#define IR_Pin GPIO_PIN_6
#define IR_GPIO_Port GPIOA
#define SDR_Pin GPIO_PIN_7
#define SDR_GPIO_Port GPIOA
#define SF_Pin GPIO_PIN_5
#define SF_GPIO_Port GPIOC
#define SLL_Pin GPIO_PIN_0
#define SLL_GPIO_Port GPIOB
#define SD2L_Pin GPIO_PIN_10
#define SD2L_GPIO_Port GPIOB
#define SFR_Pin GPIO_PIN_7
#define SFR_GPIO_Port GPIOC
#define AUTO_Pin GPIO_PIN_8
#define AUTO_GPIO_Port GPIOC
#define SD2R_Pin GPIO_PIN_9
#define SD2R_GPIO_Port GPIOA
#define SLFR_Pin GPIO_PIN_11
#define SLFR_GPIO_Port GPIOC
#define SLFR_EXTI_IRQn EXTI15_10_IRQn
#define SLR_Pin GPIO_PIN_4
#define SLR_GPIO_Port GPIOB
#define SFL_Pin GPIO_PIN_5
#define SFL_GPIO_Port GPIOB
#define SDL_Pin GPIO_PIN_6
#define SDL_GPIO_Port GPIOB
#define SFS_Pin GPIO_PIN_7
#define SFS_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
