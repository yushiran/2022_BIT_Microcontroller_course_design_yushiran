/* ch03-3-3.c - 流水灯实验程序  */
//==声明区============================================
#include	<reg51.h>  	// 定义8051暂存器之标头档,P2-17~19 
#define	LED	P1			// 定义LED接至Port 1
void delay(int);		// 声明延迟函数 
//==主程序============================================
main()					// 主程序开始 
{	unsigned char i;  	// 声明无号数字元变数i(占1Bytes) 	
	LED=0xfe;			// 初值=1111 1110,只有最右1灯亮	
	while(1)			// 无穷循环,程序一直跑 
	{	for(i=0;i<7;i++)// 左移7次 
		{	delay(100);	// 延迟100 5m=0.5s 
			LED=(LED<<1)|0x01;	// 左移1位,并设定最低位元为1 
		}				// 左移结束,只有最左1灯亮 
		for(i=0;i<7;i++)// 右移7次 
		{	delay(100);	// 延迟100 5m=0.5s 
			LED=(LED>>1)|0x80;	// 右移1位,并设定最高位元为1
		}				// 结束右移,只有最右1灯亮 
	}					// while循环结束 
}						// 主程序结束 
//==子程序=============================================
/* 延迟函数,延迟约x 5ms */
void delay(int x)		// 延迟函数开始 
{	int i,j;			// 声明整数变数i,j 
	for (i=0;i<x;i++)	// 计数x次,延迟x 5ms 
		for (j=0;j<600;j++);// 计数600次，延迟5ms 
}						// 延迟函数结束 
