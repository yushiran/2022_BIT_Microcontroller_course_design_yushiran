void box_build()
{
	box_num++;
	s_box.mode=next_mode;
	s_box.shape=next_shape;
	s_box.x=3;
	s_box.y=0;
	if(next_mode_flag==7)
	{
		next_mode=TL0%7;//产生随机数，但是是伪随机?
	}
	else
	{
		next_mode=next_mode_flag;
		next_mode_flag=7;
	}	
	next_shape=TL0%4;//产生随机数，但是是伪随机?  ?
}//方块生成函数


unsigned int box_read_data(unsigned char tpmode,unsigned char tpshape)
{
	unsigned int tpbox;
	switch(tpmode)
	{
		case 0: switch(tpshape)
				{
					case 0: tpbox=0xf000;break;
					case 1: tpbox=0x8888;break;
					case 2: tpbox=0xf000;break;
					case 3: tpbox=0x8888;break;
					default:;
				}break;	
		case 1: switch(tpshape)
				{
					case 0: tpbox=0xe800;break;
					case 1: tpbox=0xc440;break;
					case 2: tpbox=0x2e00;break;
					case 3: tpbox=0x88c0;break;
					default:;
				}break;	
		case 2: switch(tpshape)
				{
					case 0: tpbox=0xe200;break;
					case 1: tpbox=0x44c0;break;
					case 2: tpbox=0x8e00;break;
					case 3: tpbox=0xc880;break;
					default:;
				}break;	
		case 3: switch(tpshape)
				{
					case 0: tpbox=0xcc00;break;
					case 1: tpbox=0xcc00;break;
					case 2: tpbox=0xcc00;break;
					case 3: tpbox=0xcc00;break;
					default:;
				}break;	
		case 4: switch(tpshape)
				{
					case 0: tpbox=0xc600;break;
					case 1: tpbox=0x4c80;break;
					case 2: tpbox=0xc600;break;
					case 3: tpbox=0x4c80;break;
					default:;
				}break;	
		case 5: switch(tpshape)
				{
					case 0: tpbox=0x6c00;break;
					case 1: tpbox=0x8c40;break;
					case 2: tpbox=0x6c00;break;
					case 3: tpbox=0x8c40;break;
					default:;
				}break;
		case 6: switch(tpshape)
				{
					case 0: tpbox=0x4e00;break;
					case 1: tpbox=0x8c80;break;
					case 2: tpbox=0xe400;break;
					case 3: tpbox=0x4c40;break;
					default:;
				}break;
		default:;
	}
	return(tpbox);
}//方块缓存数据函数（输入方块类型和形状即可获得方块缓存数据）

void box_load()
{
	s_box.box=box_read_data(s_box.mode,s_box.shape);
}//方块载入函数

void box_to_Box_Ram(unsigned char tpx,unsigned char tpy,unsigned int tpbox)
{
	unsigned char i;
	unsigned int temp;
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+tpy]=Box_Ram[3-i+tpy]&(~((temp&0x000f)<<(12-tpx))); 
		temp=temp>>4;
	}//从游戏点阵缓存中删除以前的方块
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//在游戏点阵缓存中加入新的方块
}//方块映射游戏点阵缓存函数（参数是原来方块的位置、缓存，先消去原有位置的方块）

void Box_Ram_to_Ram()
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		Ram[i]=(Box_Ram[i]>>8)&0x00ff;
		Ram[i+8]=Box_Ram[i]&0x00ff;
		Ram[i+16]=(Box_Ram[i+8]>>8)&0x00ff;
		Ram[i+24]=Box_Ram[i+8]&0x00ff;
	}
}//游戏点阵缓存映射显示点阵缓存函数

void game_execute()
{
	if(box_down_reg<20)
	{				  
		box_down_reg++;
	}
	else
	{
		box_down_reg=0;
		if(check_cover(s_box.x,s_box.y+1,s_box.box))
		{
			s_box.y++;
			box_to_Box_Ram(s_box.x,s_box.y-1,s_box.box);
			Box_Ram_to_Ram();
		}//检测是否还可以下降，如果还能下降则继续下降
		else
		{
			destroy_row();
			box_build();
			box_load();
			game_over_flag=check_game_over();//游戏结束标志位置1表示游戏结束
			next_box();
			box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
			Box_Ram_to_Ram();
		}//如果不能下降则调用消行函数检查是否可以消行，之后重新建立方块
	}
}//游戏执行函数（控制方块下落，检测是否到底，如果到底调用消行函数）


void time0_initialize()
{
	TMOD|=0x03;//定时器0，16位工作方式
	TR0=1; //启动定时器
	ET0=1; //打开定时器0中断
			//默认中断优先级为低
	EA=1; //打开总中断
}//定时器0初始化函数

void timer0() interrupt 1
{
	TH0=0x00;
	TL0=0x00;
	if(time0_reg<10)
	{				  
		time0_reg++;
	}
	else
	{
		time0_reg=0;
		game_execute();
		display();
	}
}//定时器0中断服务

unsigned char uart_getchar()
{
	unsigned char rx_data = 0;
	while(0==RI);
	EA=0;
	rx_data = SBUF;
	RI = 0;
	EA=1;
	return rx_data;
}

void uart_putchar(unsigned char data1)
{
	SBUF = data1;
	while(0==TI);
	TI=0;
}

void uart_putstring(unsigned char *buffer)
{
	unsigned char *pIter = buffer;
	while((*pIter)!=0x00)
	{
		uart_putchar(*pIter);
		pIter++;
	}
}

void uart_init()//串口初始化
{
//	PCON=0;
//	//REN=1;
//	SCON= 0x50;		//串口方式1
//	EA=1;
//  ES= 1;		//开放串口
//	
//	TR1 = 0;		//停止计数
//	TMOD	= (TMOD & 0x0f) | 0x20;
//	TH1	= 0xfd;		//初始化Time1数据
//	TL1	= 0xfd;
//	ET1	= 0;		//没有Time1中断
//	TR1=1;		//开始计时
		  SCON=0x50;
    TMOD|=0x20;
    TH1=0xfd;
    TL1=0xfd; 
    TR1=1; 
	
	  SM0=0;
    SM1=1; 
    REN=1;
    EA=1; 
    ES=1; 
}

void serial() interrupt 4
{ 
	unsigned char i;
	unsigned char high;
	unsigned char low;
	unsigned int data_u16;
	ES=0;

	if(RI)
	{
		a=uart_getchar();//将数据发回电脑
		a_flag=1;
	}

	for(i=0;i<16;i++)
  {
		data_u16=Box_Ram[i];
		high=(data_u16>>8)&0xff;
    low=data_u16&0xff; 			
		uart_putchar(high);
		uart_putchar(low);
	}
	uart_putchar(s_box.mode);
	uart_putchar(next_mode);

	high=(score>>8)&0xff;
  low=score&0xff; 			
	uart_putchar(high);
	uart_putchar(low);
	
	high=(box_num>>8)&0xff;
  low=box_num&0xff; 			
	uart_putchar(high);
	uart_putchar(low);
	
	uart_putchar(0xff);
	ES=1;
} 

bit check_cover(unsigned char tpx,unsigned char tpy,unsigned int tpbox)
{
	unsigned char i;
	bit tpflag=1;
	unsigned int temp;
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=Box_Ram[3-i+s_box.y]&(~((temp&0x000f)<<(12-s_box.x))); 
		temp=temp>>4;
	}//先将现有的方块从游戏点阵缓存中删除
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		if((((temp&0x000f)<<(12-tpx))&Box_Ram[3-i+tpy])!=0x0000)
		{
			tpflag=0;
		}
		temp=temp>>4;
	}//检查方块是否和原有图形重叠,重叠置标志位tpflag为0,不重叠不置标志位，即tpflag为1
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//在游戏点阵缓存中恢复原有方块
	return(tpflag);
}//检查覆盖函数（检查此时带入的参数所确定的方块是否会覆盖原有图形，不会覆盖返回1，覆盖返回0）

void destroy_row()
{
	unsigned char i,j=0;
	unsigned char tpflag[4]={0,0,0,0};//最多一次只能消四行，所以设置四个标志位即可,初值为0
	for(i=0;i<16;i++)
	{
		if((Box_Ram[i]&0xffc0)==0xffc0)
		{
			tpflag[j]=i+1;//tpflag为0表示不标志，1表示第0行缓存为0xffff，n表示第n+1行缓存为0xffff
			j++;
			score++;
			if(j==4)
			{
				break;
			}//检查完有四行要消除则退出检查循环
		}
	}//依次检测是否有行缓存为0xffff，如果是则标志tpflag为此行的行号
	for(j=0;j<4;j++)
	{
		if(tpflag[j]!=0)
		{
			for(i=tpflag[j]-1;i>0;i--)
			{
			Box_Ram[i]=(Box_Ram[i-1]&0xffc0)|(Box_Ram[i]&0x003f);
			Box_Ram[0]=0x0000|(Box_Ram[0]&0x003f);
			}
		}
	}//被标志的行依次被上一行所取代，即被消去
}//消行函数

void next_box()
{
	unsigned char i;
	unsigned int temp;
	temp=box_read_data(next_mode,next_shape);
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i]=(temp&0x000f)|(Box_Ram[3-i]&0xfff0);
		temp=temp>>4;
	}//在游戏点阵缓存中显示下一个方块的样子
	for(i=5;i<10;i++)
	{
		Box_Ram[i]=num_data[i-5+5*score]|(Box_Ram[i]&0xfff0);
	}//在游戏点阵缓存中显示分数，上限为10
}//显示下一个方块函数

void Tetris_main()
{
	unsigned char i;
	for(i=0;i<19;i++)
	{
		Box_Ram[i]=Box_Ram_data[i];
	};//载入游戏初始显示画面
	game_over_flag=0;//游戏结束标志位置0表示游戏未结束
	box_build();
	box_load();
	next_box();
	box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
	Box_Ram_to_Ram();
//	intermit0_initialize();
	time0_initialize();
	while((!game_over_flag)&&(score<1))//如果游戏结束标志位置1，表示游戏结束，打破循环，调用游戏结束画面显示函数
	{
		game_button();
		check_pause_game();
		if(restart_game_flag==1)
    {
			restart_game_flag=0;
			EA=0;
			game_start_show();
		}
		if(a_flag==1)
		{
			game_a_get();
			a_flag=0;
		}
	}
	EA=0;//游戏结束后关中断，要不缓存区数据不正确
	if(score>=1)
	{ 
	  game_victory_show();
	}else{			
		game_over_show(); 
	}
}//俄罗斯方块游戏主函数

void game_a_get()
{
	//判断是否是在初始化方块
	if(a==0||a==1||a==2||a==3||a==4||a==5||a==6)
	{next_mode_flag=a;}
	else{
		button_flag=1;
		switch(a)
	{
		case 'u':
			button_value=2;break;
		case 'd':
			button_value=1;break;
		case 'r':
			button_value=5;break;
		case 'l':
			button_value=4;break;
		case 'a':
			button_value=3;break;
		default: ;
	}
	}
}//得到信息的判断

void game_over_show()
{
	unsigned char i;
	bit tpflag=1;//置循环标志位为1
	for(i=0;i<8;i++)
	{
		Box_Ram[i]=game_data[i];
		Box_Ram[i+8]=over_data[i];
	}
	Box_Ram_to_Ram();
	while(tpflag)
	{
		display();
		switch(basic_button())
		{
			case 3: tpflag=0;
					break;
			default:;
		}
	}//game over画面循环
	game_start_show();//进入游戏开始显示画面
}//游戏失败结束画面显示函数

void game_victory_show()
{
	unsigned char i;
	bit tpflag=1;//置循环标志位为1
	for(i=0;i<16;i++)
	{
		Box_Ram[i]=WIN_data[i];
	}
	Box_Ram_to_Ram();
	while(tpflag)
	{
		display();
		switch(basic_button())
		{
			case 3: tpflag=0;
					break;
			default:;
		}
	}//victory画面循环
	game_start_show();//进入游戏开始显示画面
}//游戏成功结束画面显示函数

void game_initialize()
{
	box_down_reg=0;
	time0_reg=0;
	next_mode=6;
	next_shape=2;
	next_mode_flag=7;//表示一开始还是不能改变下一个形状的
	game_over_flag=0;
	restart_game_flag=0;
	pause_game_flag=0;
	button_flag=0;
	score=0;
	box_num=0;
	a_flag=0;
}//游戏初始化函数

void game_start_show()
{
	unsigned char i,j,n;
	bit tpflag=1;//置循环标志位为1
	game_initialize();//调用游戏初始化函数，初始化游戏所有变量
	for(i=0;i<16;i++)
	{
		Box_Ram[i]=0x0000;
	};//清除图像
	//ikun
	while(tpflag)
  {
	for(j=0;j<6;j++)			
	  	{
				for(n=0;n<4;n++)
        {
				   for(i=0;i<16;i++) 	
						{
								Box_Ram[i]=start_show[i+j*16];
	 	        }
				        Box_Ram_to_Ram();
				        display_for_ikun();
						switch(basic_button())
	         	{
			        case 3: tpflag=0;
				         	break;
			        default:;
		        }
        } 				
      }	
  }
  tpflag=1;
  for(i=0;i<16;i++)
	{
		Box_Ram[i]=0x0000;
	};//清除图像
	//tetris
	for(i=0;i<8;i++)
	{
		Box_Ram[i+3]=tetris_data[i];
	}
	Box_Ram_to_Ram();
	while(tpflag)
	{
		display();
		switch(basic_button())
		{
			case 3: tpflag=0;
					break;
			default:;
		}
	}//game_start_show循环
	Tetris_main();//进入俄罗斯方块游戏主函数
}//游戏开始显示画面

bit check_game_over()
{
	unsigned char i;
	bit tpflag=0;
	unsigned int temp;
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		if((((temp&0x000f)<<(12-s_box.x))&Box_Ram[3-i+s_box.y])!=0x0000)
		{
			tpflag=1;
		}
		temp=temp>>4;
	}//检查新建方块是否和原有图形重叠,重叠置标志位tpflag为1,不重叠不置标志位，即tpflag为0
	return(tpflag);
}//检查游戏结束函数（游戏结束返回1，游戏没有结束返回0）

void check_pause_game()
{
	if(pause_game_flag)
	{
		while(basic_button()!=2)
		{
		display();
		}
	}
	pause_game_flag=0;
	EA=1;//开中断，继续游戏
}//检测暂停游戏函数

