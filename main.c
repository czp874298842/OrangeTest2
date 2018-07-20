

/*	
	Code	程序代码存储区
	Data	直接寻址片内数据存储区（低128字节）
	Bdata	位寻址片内数据存储区（16字节）
	Idata	间接寻址片内数据存储区（256字节）
	Pdata	分页寻址外部数据存储区（256字节）
	Xdata	可寻址片外数据存储区(64KB）
*/

#include "common.h"
#include "task.h"

#include "LEDTask.h"
#include "LCD1602Task.h"
#include "InfraRedTask.h"

TaskTypeDef xdata Task_Array[] = {
	{SUSPEND, 	0, 		0,		NULL,				Idle_Task},
	{SUSPEND, 	500, 	500, 	LEDTask_Init,		LED_Task},
	{SUSPEND, 	50, 	50, 	LCD1602Task_Init,		LCD1602_Task},
	{SUSPEND, 	50, 	50, 	InfraRedTask_Init,	InfraRed_Task},
};

int main(void)  //reentrant //重入函数修饰符
{	
	//volatile u32 *pulSysTicks;							 //用于记录系统时钟地址
	
	//pulSysTicks = TM0_Init();
	
	//PCA_Init();
	
	
	
	TaskInitial(sizeof(Task_Array)/sizeof(Task_Array[0]), NULL);
	//LEDTask_Init(pulSysTicks);
	//LCD1602Task_Init(pulSysTicks);
	
	while(1)
	{
//		LED_Task();
//	
//		LCD1602_Task();
		
		TaskScheduler();
	}
	
	return 0;
}
