
#include "LCD1602Task.h"
#include "LCD1602.h"
#include "EasyKey.h"
#include "usart.h"
#include "KEYTask.h"
#include "MotorTask.h"
#include "UsartTask.h"

#define		LCD1602_TASK_TIME_DELAY		20

static volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
static u32 ulOldTicks;							 //记录时间变量，与系统时间对比，查看延时时间是否到达

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LCD1602Task_Init(volatile u32 *ulSysClock)
{
	LCD_Init();
 	pulSysTicks = ulSysClock;	
//	LCD_Write_String(0,0," welcome to tri..");	
	LCD_Write_String(0, 0, "CYF  Mtr:");
	LCD_Write_String(0, 1, "HNow:    HSet:");
}

/**
  * @brief  LEDTask_Init
  * @param  
  * @retval 
  */
void LCD1602_Task(void)
{
	s8 array[16] = {0};
	static u16 ucTemp = 0;
	if ( (*pulSysTicks) - ulOldTicks >= LCD1602_TASK_TIME_DELAY )		  //记录时间变量与系统时间对比，查看延时时间是否到达
	{
		ulOldTicks = *pulSysTicks;					  //从新记录系统时间
		
		//运行任务	
	
		if( ON == GetMotorCtrlFlag() )
		{
			LCD_Write_String(9, 0, "ON ");
		}
		else
		{
			LCD_Write_String(9, 0, "OFF");
		}
		
		sprintf(array,"%4ld", (u32)((*pulSysTicks)/1000));
		LCD_Write_String(12,0,array);
		
		sprintf(array,"%02d  ", (u16)GetWaterLever());
		LCD_Write_String(5,1,array);
		sprintf(array,"%02d", (u16)GetWaterLeverLimit());
		LCD_Write_String(14,1,array);
		
//		sprintf(array,"%02X %02X %02X %02X %02X", (u16)Receive_Buff[0], (u16)Receive_Buff[1], (u16)Receive_Buff[2], (u16)Receive_Buff[3], (u16)Receive_Buff[4]);

				
	}
	else if(ulOldTicks > (*pulSysTicks))
	{
		ulOldTicks = (*pulSysTicks);
	}
	
}
/**/