/* - 计时器实验3 -60秒计数器,每1分钟LED反相1次 */
//==声明区================================
#include	<reg51.h>	// 定义8x51暂存器之标头档,P2-17~19 
#define	SEG	P2			// 定义七节显示器接至Port 2
#define	SCANP	P1		// 定义扫瞄线接至Port 1
sbit  LED=P0^7;			// 声明LED接至P0.7
/*声明T0计时相关声明*/  // THx TLx 计算参考 
#define  count_M1   50000			// T0(MODE 1)之计量值,0.05s 
#define  TH_M1  (65636-count_M1)/256// T0(MODE 1)计量高8位元 
#define  TL_M1  (65636-count_M1)%256// T0(MODE 1)计量低8位元 
int count_T0=0; 					// 计算 T0中断次数 
/*声明T1扫瞄相关声明*/
#define  count_M2   250			// T1(MODE 2)之计量值,0.25ms
#define  TH_M2  (256-count_M2)	// T1(MODE 2)自动载入计量  
#define  TL_M2  (256-count_M2)	// T1(MODE 2)计数量 
char count_T1=0;				// 计算 T1中断次数 	
/* 声明七节显示器驱动信号阵列(共阳) */
char code TAB[10]={	0xc0, 0xf9, 0xa4, 0xb0, 0x99,	//数字0-4
					0x92, 0x83, 0xf8, 0x80, 0x98 };	//数字5-9
char disp[2]={ 0xc0, 0xc0 };	// 声明显示区阵列初始显示00
/* 声明基本变量 */
char seconds=0;			// 秒数 
char scan=0;			// 扫瞄信号 
//==主程序================================
main()					// 主程序开始 
{	IE=0x8a;			// 1000 1010,启用TF0、TF1中断(6-4页)
	TMOD=0x21;			// 0010 0001,T1采mode 2、T0采mode 1
	TH0=TH_M1; TL0=TL_M1;// 设置T0计数量高8位元、低8位元 
	TR0=1;				// 启动T0(7-7页)
	TH1=TH_M2; TL1=TL_M2;// 设置T1自动载入值、计数量 
	TR1=1;				// 启动T1
	LED=1;				// 关闭LED
	while(1);			// 无穷回圈，程序停滞 
}						// 主程序结束  
//== T0中断子程序- 计算并显示秒数 ==================
void T0_1s(void) interrupt 1	// T0中断子程序开始 
{	TH0=TH_M1; TL0=TL_M1;		// 设置T0计数量高8位元、低8位元 
	if (++count_T0==20)			// 若中断20次,即0.05x20=1秒 
	{	count_T0=0;				// 重新计次 
		seconds++;				// 秒数加1
		if (seconds==60) 		// 若超过60秒 
		{	seconds=0;			// 秒数归0,重新开始 
			LED=~LED; 			// 切换LED
		}						// if叙述结束(超过60秒)
	}							// if叙述结束(中断20次)
	disp[1]=TAB[seconds/10]; 	// 填入十位数显示区 
	disp[0]=TAB[seconds%10]; 	// 填入个位数显示区 
}								// T0中断子程序结束 
//===T1中断子程序 - 扫瞄 =========================
void T1_8ms(void) interrupt 3	// T1中断子程序开始 
{	if (++count_T1==32)			// 若中断32次,即0.25mx32=8ms
		{	count_T1=0;			// 重新计次 
			if (++scan==3) scan=1;// 若超过十位数,显示个位 	
			SEG=0xff;			// 关闭7段显示器 
			SCANP=~scan;		// 输出扫瞄信号 
			SEG=disp[scan-1];	// 输出显示信号 
		}						// 结束if判断(中断32次)
}								// T0中断子程序结束 
