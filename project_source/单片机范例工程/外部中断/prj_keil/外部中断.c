/*  两个外部中断实验 */
//==声明区===================================
#include	<reg51.h>	//	定义8x51暂存器之标头档,P2-17~19 
#define	LED	P1			//	定义LED接至Port 1
void delay1ms(int);		//	声明延迟函数 
void left(int);			//	声明单灯左移函数 
void right(int);		//	单灯右移函数开始
//==主程序===================================
main()					//	主程序开始 
{	IE=0x85;			//	准许INT 0,INT 1中断(6-4页)
	IP=0x01;			//	设定INT 0具有最高优先权(6-5页)
	LED=0x00;			//	初值=0000 0000,灯全亮	
	while(1)			//	无穷循环,程序一直跑 
	{	delay1ms(250);	//	延迟250 1m=0.25s 
		LED=~LED;		//	LED反相 
	}					//	while循环结束 
}						//	主程序结束 
//==子程序===================================
/* INT 0的中断子程序 - 单灯左移3圈 */
void my_int0(void) interrupt 0	//	INT0 中断子程序开始 
{	unsigned saveLED=LED;	//	储存中断前LED状态 
	left(3);			//	单灯左移3圈 
	LED=saveLED;		//	写回中断前ED状态   
}						//	结束INT0 中断子程序 
/* INT 1的中断子程序 - 单灯右移3圈 */
void my_int1(void) interrupt 2	//	INT1 中断子程序开始 
{	unsigned saveLED=LED;	//	储存中断前LED状态 
	right(3);			//	单灯右移3圈 
	LED=saveLED;		//	写回中断前LED状态 
}						//	结束INT1 中断子程序 
/* 延迟函数,延迟约x 1ms */
void delay1ms(int x)	//	延迟函数开始 
{	int i,j;			//	声明整数变数i,j 
	for (i=0;i<x;i++)	//	计数x次,延迟x 1ms 
		for (j=0;j<120;j++);	//	计数120次，延迟1ms 
}						//	延迟函数结束 
/* 单灯左移函数,执行x圈 */
void left(int x) 		//	单灯左移函数开始 
{	int i, j;			//	声明变数i,j
	for(i=0;i<x;i++)	//	i循环,执行x圈 
	{	LED=0xfe;		//	初始状态=1111 1110,最右灯亮 
		for(j=0;j<7;j++)	//	j循环,左移7次 
		{	delay1ms(250);	//	延迟250 1m=0.25s
			LED=(LED<<1)|0x01; 	//	左移1位後,LSB设为1
		}				//	j循环结束 
		delay1ms(250);	//	延迟250 1m=0.25s
	}					//	i循环结束*/
}						//	单灯左移函数结束 
/* 单灯右移函数,执行x圈 */
void right(int x) 		//	单灯右移函数开始
{	int i, j;			//	声明变数i,j
	for(i=0;i<x;i++)	//	i循环,执行x圈 
	{	LED=0x7f;		//	初始状态=0111 1111
		for(j=0;j<7;j++)//	j循环,右移7次 
		{	delay1ms(250);	//	延迟250 10m=0.25s
			LED=(LED>>1)|0x80; 	//	右移1位後,MSB设为1
		}				//	j循环结束 
		delay1ms(250);	//	延迟250 1m=0.25s
	}					//	i循环结束*/
}						//	单灯右移函数结束 
