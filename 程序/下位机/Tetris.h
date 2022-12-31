void box_build()
{
	box_num++;
	s_box.mode=next_mode;
	s_box.shape=next_shape;
	s_box.x=3;
	s_box.y=0;
	if(next_mode_flag==7)
	{
		next_mode=TL0%7;//�����������������α����
	}
	else
	{
		next_mode=next_mode_flag;
		next_mode_flag=7;
	}	
	next_shape=TL0%4;//�����������������α����  �
}//�������ɺ���


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
}//���黺�����ݺ��������뷽�����ͺ���״���ɻ�÷��黺�����ݣ�

void box_load()
{
	s_box.box=box_read_data(s_box.mode,s_box.shape);
}//�������뺯��

void box_to_Box_Ram(unsigned char tpx,unsigned char tpy,unsigned int tpbox)
{
	unsigned char i;
	unsigned int temp;
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+tpy]=Box_Ram[3-i+tpy]&(~((temp&0x000f)<<(12-tpx))); 
		temp=temp>>4;
	}//����Ϸ���󻺴���ɾ����ǰ�ķ���
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//����Ϸ���󻺴��м����µķ���
}//����ӳ����Ϸ���󻺴溯����������ԭ�������λ�á����棬����ȥԭ��λ�õķ��飩

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
}//��Ϸ���󻺴�ӳ����ʾ���󻺴溯��

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
		}//����Ƿ񻹿����½�����������½�������½�
		else
		{
			destroy_row();
			box_build();
			box_load();
			game_over_flag=check_game_over();//��Ϸ������־λ��1��ʾ��Ϸ����
			next_box();
			box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
			Box_Ram_to_Ram();
		}//��������½���������к�������Ƿ�������У�֮�����½�������
	}
}//��Ϸִ�к��������Ʒ������䣬����Ƿ񵽵ף�������׵������к�����


void time0_initialize()
{
	TMOD|=0x03;//��ʱ��0��16λ������ʽ
	TR0=1; //������ʱ��
	ET0=1; //�򿪶�ʱ��0�ж�
			//Ĭ���ж����ȼ�Ϊ��
	EA=1; //�����ж�
}//��ʱ��0��ʼ������

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
}//��ʱ��0�жϷ���

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

void uart_init()//���ڳ�ʼ��
{
//	PCON=0;
//	//REN=1;
//	SCON= 0x50;		//���ڷ�ʽ1
//	EA=1;
//  ES= 1;		//���Ŵ���
//	
//	TR1 = 0;		//ֹͣ����
//	TMOD	= (TMOD & 0x0f) | 0x20;
//	TH1	= 0xfd;		//��ʼ��Time1����
//	TL1	= 0xfd;
//	ET1	= 0;		//û��Time1�ж�
//	TR1=1;		//��ʼ��ʱ
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
		a=uart_getchar();//�����ݷ��ص���
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
	}//�Ƚ����еķ������Ϸ���󻺴���ɾ��
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		if((((temp&0x000f)<<(12-tpx))&Box_Ram[3-i+tpy])!=0x0000)
		{
			tpflag=0;
		}
		temp=temp>>4;
	}//��鷽���Ƿ��ԭ��ͼ���ص�,�ص��ñ�־λtpflagΪ0,���ص����ñ�־λ����tpflagΪ1
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//����Ϸ���󻺴��лָ�ԭ�з���
	return(tpflag);
}//��鸲�Ǻ���������ʱ����Ĳ�����ȷ���ķ����Ƿ�Ḳ��ԭ��ͼ�Σ����Ḳ�Ƿ���1�����Ƿ���0��

void destroy_row()
{
	unsigned char i,j=0;
	unsigned char tpflag[4]={0,0,0,0};//���һ��ֻ�������У����������ĸ���־λ����,��ֵΪ0
	for(i=0;i<16;i++)
	{
		if((Box_Ram[i]&0xffc0)==0xffc0)
		{
			tpflag[j]=i+1;//tpflagΪ0��ʾ����־��1��ʾ��0�л���Ϊ0xffff��n��ʾ��n+1�л���Ϊ0xffff
			j++;
			score++;
			if(j==4)
			{
				break;
			}//�����������Ҫ�������˳����ѭ��
		}
	}//���μ���Ƿ����л���Ϊ0xffff����������־tpflagΪ���е��к�
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
	}//����־�������α���һ����ȡ����������ȥ
}//���к���

void next_box()
{
	unsigned char i;
	unsigned int temp;
	temp=box_read_data(next_mode,next_shape);
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i]=(temp&0x000f)|(Box_Ram[3-i]&0xfff0);
		temp=temp>>4;
	}//����Ϸ���󻺴�����ʾ��һ�����������
	for(i=5;i<10;i++)
	{
		Box_Ram[i]=num_data[i-5+5*score]|(Box_Ram[i]&0xfff0);
	}//����Ϸ���󻺴�����ʾ����������Ϊ10
}//��ʾ��һ�����麯��

void Tetris_main()
{
	unsigned char i;
	for(i=0;i<19;i++)
	{
		Box_Ram[i]=Box_Ram_data[i];
	};//������Ϸ��ʼ��ʾ����
	game_over_flag=0;//��Ϸ������־λ��0��ʾ��Ϸδ����
	box_build();
	box_load();
	next_box();
	box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
	Box_Ram_to_Ram();
//	intermit0_initialize();
	time0_initialize();
	while((!game_over_flag)&&(score<1))//�����Ϸ������־λ��1����ʾ��Ϸ����������ѭ����������Ϸ����������ʾ����
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
	EA=0;//��Ϸ��������жϣ�Ҫ�����������ݲ���ȷ
	if(score>=1)
	{ 
	  game_victory_show();
	}else{			
		game_over_show(); 
	}
}//����˹������Ϸ������

void game_a_get()
{
	//�ж��Ƿ����ڳ�ʼ������
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
}//�õ���Ϣ���ж�

void game_over_show()
{
	unsigned char i;
	bit tpflag=1;//��ѭ����־λΪ1
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
	}//game over����ѭ��
	game_start_show();//������Ϸ��ʼ��ʾ����
}//��Ϸʧ�ܽ���������ʾ����

void game_victory_show()
{
	unsigned char i;
	bit tpflag=1;//��ѭ����־λΪ1
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
	}//victory����ѭ��
	game_start_show();//������Ϸ��ʼ��ʾ����
}//��Ϸ�ɹ�����������ʾ����

void game_initialize()
{
	box_down_reg=0;
	time0_reg=0;
	next_mode=6;
	next_shape=2;
	next_mode_flag=7;//��ʾһ��ʼ���ǲ��ܸı���һ����״��
	game_over_flag=0;
	restart_game_flag=0;
	pause_game_flag=0;
	button_flag=0;
	score=0;
	box_num=0;
	a_flag=0;
}//��Ϸ��ʼ������

void game_start_show()
{
	unsigned char i,j,n;
	bit tpflag=1;//��ѭ����־λΪ1
	game_initialize();//������Ϸ��ʼ����������ʼ����Ϸ���б���
	for(i=0;i<16;i++)
	{
		Box_Ram[i]=0x0000;
	};//���ͼ��
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
	};//���ͼ��
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
	}//game_start_showѭ��
	Tetris_main();//�������˹������Ϸ������
}//��Ϸ��ʼ��ʾ����

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
	}//����½������Ƿ��ԭ��ͼ���ص�,�ص��ñ�־λtpflagΪ1,���ص����ñ�־λ����tpflagΪ0
	return(tpflag);
}//�����Ϸ������������Ϸ��������1����Ϸû�н�������0��

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
	EA=1;//���жϣ�������Ϸ
}//�����ͣ��Ϸ����

