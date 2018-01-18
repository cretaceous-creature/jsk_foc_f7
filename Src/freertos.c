/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "main.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId enchallTaskHandle;
osThreadId controlTaskHandle;
osThreadId ledblueTaskHandle;
osThreadId ledgreenTaskHandle;
osThreadId iwdgTaskHandle;
osThreadId buzzertoneTaskHandle;
osThreadId buzzerrythmTaskHandle;
osMessageQId buzzerQueueHandle;
osMessageQId rythmQueueHandle;
osMessageQId enchallQueueHandle;
osMessageQId shuntQueueHandle;
osMessageQId conresQueueHandle;
osMutexId buzzerMutexHandle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartenchallTask(void const * argument);
void StartcontrolTask(void const * argument);
void StartledblueTask(void const * argument);
void StartledgreenTask(void const * argument);
void StartiwdgTask(void const * argument);
void StartbuzzertoneTask(void const * argument);
void StartbuzzerrythmTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* Create the mutex(es) */
  /* definition and creation of buzzerMutex */
  osMutexDef(buzzerMutex);
  buzzerMutexHandle = osMutexCreate(osMutex(buzzerMutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of enchallTask */
  osThreadDef(enchallTask, StartenchallTask, osPriorityNormal, 0, 128);
  enchallTaskHandle = osThreadCreate(osThread(enchallTask), NULL);

  /* definition and creation of controlTask */
  osThreadDef(controlTask, StartcontrolTask, osPriorityAboveNormal, 0, 128);
  controlTaskHandle = osThreadCreate(osThread(controlTask), NULL);

  /* definition and creation of ledblueTask */
  osThreadDef(ledblueTask, StartledblueTask, osPriorityIdle, 0, 128);
  ledblueTaskHandle = osThreadCreate(osThread(ledblueTask), NULL);

  /* definition and creation of ledgreenTask */
  osThreadDef(ledgreenTask, StartledgreenTask, osPriorityIdle, 0, 128);
  ledgreenTaskHandle = osThreadCreate(osThread(ledgreenTask), NULL);

  /* definition and creation of iwdgTask */
  osThreadDef(iwdgTask, StartiwdgTask, osPriorityIdle, 0, 128);
  iwdgTaskHandle = osThreadCreate(osThread(iwdgTask), NULL);

  /* definition and creation of buzzertoneTask */
  osThreadDef(buzzertoneTask, StartbuzzertoneTask, osPriorityIdle, 0, 128);
  buzzertoneTaskHandle = osThreadCreate(osThread(buzzertoneTask), NULL);

  /* definition and creation of buzzerrythmTask */
  osThreadDef(buzzerrythmTask, StartbuzzerrythmTask, osPriorityIdle, 0, 128);
  buzzerrythmTaskHandle = osThreadCreate(osThread(buzzerrythmTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Create the queue(s) */
  /* definition and creation of buzzerQueue */
  osMessageQDef(buzzerQueue, 1, uint16_t);
  buzzerQueueHandle = osMessageCreate(osMessageQ(buzzerQueue), NULL);

  /* definition and creation of rythmQueue */
  osMessageQDef(rythmQueue, 32, uint16_t);
  rythmQueueHandle = osMessageCreate(osMessageQ(rythmQueue), NULL);

  /* definition and creation of enchallQueue */
  osMessageQDef(enchallQueue, 1, ENCHD);
  enchallQueueHandle = osMessageCreate(osMessageQ(enchallQueue), NULL);

  /* definition and creation of shuntQueue */
  osMessageQDef(shuntQueue, 1, CURDATA);
  shuntQueueHandle = osMessageCreate(osMessageQ(shuntQueue), NULL);

  /* definition and creation of conresQueue */
  osMessageQDef(conresQueue, 1, CONRES);
  conresQueueHandle = osMessageCreate(osMessageQ(conresQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */

  /* USER CODE END RTOS_QUEUES */
}

/* StartenchallTask function */
__weak void StartenchallTask(void const * argument)
{

  /* USER CODE BEGIN StartenchallTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartenchallTask */
}

/* StartcontrolTask function */
__weak void StartcontrolTask(void const * argument)
{
  /* USER CODE BEGIN StartcontrolTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartcontrolTask */
}

/* StartledblueTask function */
__weak void StartledblueTask(void const * argument)
{
  /* USER CODE BEGIN StartledblueTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartledblueTask */
}

/* StartledgreenTask function */
__weak void StartledgreenTask(void const * argument)
{
  /* USER CODE BEGIN StartledgreenTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartledgreenTask */
}

/* StartiwdgTask function */
__weak void StartiwdgTask(void const * argument)
{
  /* USER CODE BEGIN StartiwdgTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartiwdgTask */
}

/* StartbuzzertoneTask function */
__weak void StartbuzzertoneTask(void const * argument)
{
  /* USER CODE BEGIN StartbuzzertoneTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartbuzzertoneTask */
}

/* StartbuzzerrythmTask function */
__weak void StartbuzzerrythmTask(void const * argument)
{
  /* USER CODE BEGIN StartbuzzerrythmTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartbuzzerrythmTask */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
