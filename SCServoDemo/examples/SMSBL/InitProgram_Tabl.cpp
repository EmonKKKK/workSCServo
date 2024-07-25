#include "stdafx.h"
#include "config.h"



void Init_program_table(void)//初始化配置参数
{
	param[0] = 1;//最小角度限制
	param[1] = 4094;//最大角度限制
	param[2] = 1000;//最大扭矩
	param[3] = 0;//运行模式 // 0:伺服位置模式 2:开环电机模式 1：恒速模式 3:步进电机模式 
	param[4] = 20;//保护扭矩 20 -> %20
	param[5] = 200; //保护时间 200 -> 2s
	param[6] = 80;//过载扭矩 80 -> %80
	param[7] = 0;//加速全部为0，即最大加速度
	param[8] = 500;//速度
	param[9] = 0;//保留
	//
	param[10] = 2048;//电机0 位移
	param[11] = 2048;//1
	param[12] = 2048;//2
	param[13] = 2048;//3
	param[14] = 2048;//4
	param[15] = 0;//5
	param[16] = 0;//6
	param[17] = 0;//7
	param[18] = 0;//8
	param[19] = 0;//9
	param[20] = 0;//10
	param[21] = 0;//11
	param[22] = 0;//12
	param[23] = 0;//13
	param[24] = 0;//14
	param[25] = 2048;//15
	param[26] = 2048;//16
	param[27] = 2048;//17
	param[28] = 2048;//18
	param[29] = 2048;//电机 19 位移


}
