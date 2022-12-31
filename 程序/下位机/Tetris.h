void box_build()
{
	box_num++;
	s_box.mode=next_mode;
	s_box.shape=next_shape;
	s_box.x=3;
	s_box.y=0;
	if(next_mode_flag==7)
	{
		next_mode=TL0%7;//²úÉúËæ»úÊı£¬µ«ÊÇÊÇÎ±Ëæ»úµ
	}
	else
	{
		next_mode=next_mode_flag;
		next_mode_flag=7;
	}	
	next_shape=TL0%4;//²úÉúËæ»úÊı£¬µ«ÊÇÊÇÎ±Ëæ»úµ  Ä
}//·½¿éÉú³Éº¯Êı


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
}//·½¿é»º´æÊı¾İº¯Êı£¨ÊäÈë·½¿éÀàĞÍºÍĞÎ×´¼´¿É»ñµÃ·½¿é»º´æÊı¾İ£©

void box_load()
{
	s_box.box=box_read_data(s_box.mode,s_box.shape);
}//·½¿éÔØÈëº¯Êı

void box_to_Box_Ram(unsigned char tpx,unsigned char tpy,unsigned int tpbox)
{
	unsigned char i;
	unsigned int temp;
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+tpy]=Box_Ram[3-i+tpy]&(~((temp&0x000f)<<(12-tpx))); 
		temp=temp>>4;
	}//´ÓÓÎÏ·µãÕó»º´æÖĞÉ¾³ıÒÔÇ°µÄ·½¿é
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//ÔÚÓÎÏ·µãÕó»º´æÖĞ¼ÓÈëĞÂµÄ·½¿é
}//·½¿éÓ³ÉäÓÎÏ·µãÕó»º´æº¯Êı£¨²ÎÊıÊÇÔ­À´·½¿éµÄÎ»ÖÃ¡¢»º´æ£¬ÏÈÏûÈ¥Ô­ÓĞÎ»ÖÃµÄ·½¿é£©

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
}//ÓÎÏ·µãÕó»º´æÓ³ÉäÏÔÊ¾µãÕó»º´æº¯Êı

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
		}//¼ì²âÊÇ·ñ»¹¿ÉÒÔÏÂ½µ£¬Èç¹û»¹ÄÜÏÂ½µÔò¼ÌĞøÏÂ½µ
		else
		{
			destroy_row();
			box_build();
			box_load();
			game_over_flag=check_game_over();//ÓÎÏ·½áÊø±êÖ¾Î»ÖÃ1±íÊ¾ÓÎÏ·½áÊø
			next_box();
			box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
			Box_Ram_to_Ram();
		}//Èç¹û²»ÄÜÏÂ½µÔòµ÷ÓÃÏûĞĞº¯Êı¼ì²éÊÇ·ñ¿ÉÒÔÏûĞĞ£¬Ö®ºóÖØĞÂ½¨Á¢·½¿é
	}
}//ÓÎÏ·Ö´ĞĞº¯Êı£¨¿ØÖÆ·½¿éÏÂÂä£¬¼ì²âÊÇ·ñµ½µ×£¬Èç¹ûµ½µ×µ÷ÓÃÏûĞĞº¯Êı£©


void time0_initialize()
{
	TMOD|=0x03;//¶¨Ê±Æ÷0£¬16Î»¹¤×÷·½Ê½
	TR0=1; //Æô¶¯¶¨Ê±Æ÷
	ET0=1; //´ò¿ª¶¨Ê±Æ÷0ÖĞ¶Ï
			//Ä¬ÈÏÖĞ¶ÏÓÅÏÈ¼¶ÎªµÍ
	EA=1; //´ò¿ª×ÜÖĞ¶Ï
}//¶¨Ê±Æ÷0³õÊ¼»¯º¯Êı

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
}//¶¨Ê±Æ÷0ÖĞ¶Ï·şÎñ

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

void uart_init()//´®¿Ú³õÊ¼»¯
{
//	PCON=0;
//	//REN=1;
//	SCON= 0x50;		//´®¿Ú·½Ê½1
//	EA=1;
//  ES= 1;		//¿ª·Å´®¿Ú
//	
//	TR1 = 0;		//Í£Ö¹¼ÆÊı
//	TMOD	= (TMOD & 0x0f) | 0x20;
//	TH1	= 0xfd;		//³õÊ¼»¯Time1Êı¾İ
//	TL1	= 0xfd;
//	ET1	= 0;		//Ã»ÓĞTime1ÖĞ¶Ï
//	TR1=1;		//¿ªÊ¼¼ÆÊ±
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
		a=uart_getchar();//½«Êı¾İ·¢»ØµçÄÔ
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
	}//ÏÈ½«ÏÖÓĞµÄ·½¿é´ÓÓÎÏ·µãÕó»º´æÖĞÉ¾³ı
	temp=tpbox;
	for(i=0;i<4;i++)
	{
		if((((temp&0x000f)<<(12-tpx))&Box_Ram[3-i+tpy])!=0x0000)
		{
			tpflag=0;
		}
		temp=temp>>4;
	}//¼ì²é·½¿éÊÇ·ñºÍÔ­ÓĞÍ¼ĞÎÖØµş,ÖØµşÖÃ±êÖ¾Î»tpflagÎª0,²»ÖØµş²»ÖÃ±êÖ¾Î»£¬¼´tpflagÎª1
	temp=s_box.box;
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i+s_box.y]=((temp&0x000f)<<(12-s_box.x))|Box_Ram[3-i+s_box.y];
		temp=temp>>4;
	}//ÔÚÓÎÏ·µãÕó»º´æÖĞ»Ö¸´Ô­ÓĞ·½¿é
	return(tpflag);
}//¼ì²é¸²¸Çº¯Êı£¨¼ì²é´ËÊ±´øÈëµÄ²ÎÊıËùÈ·¶¨µÄ·½¿éÊÇ·ñ»á¸²¸ÇÔ­ÓĞÍ¼ĞÎ£¬²»»á¸²¸Ç·µ»Ø1£¬¸²¸Ç·µ»Ø0£©

void destroy_row()
{
	unsigned char i,j=0;
	unsigned char tpflag[4]={0,0,0,0};//×î¶àÒ»´ÎÖ»ÄÜÏûËÄĞĞ£¬ËùÒÔÉèÖÃËÄ¸ö±êÖ¾Î»¼´¿É,³õÖµÎª0
	for(i=0;i<16;i++)
	{
		if((Box_Ram[i]&0xffc0)==0xffc0)
		{
			tpflag[j]=i+1;//tpflagÎª0±íÊ¾²»±êÖ¾£¬1±íÊ¾µÚ0ĞĞ»º´æÎª0xffff£¬n±íÊ¾µÚn+1ĞĞ»º´æÎª0xffff
			j++;
			score++;
			if(j==4)
			{
				break;
			}//¼ì²éÍêÓĞËÄĞĞÒªÏû³ıÔòÍË³ö¼ì²éÑ­»·
		}
	}//ÒÀ´Î¼ì²âÊÇ·ñÓĞĞĞ»º´æÎª0xffff£¬Èç¹ûÊÇÔò±êÖ¾tpflagÎª´ËĞĞµÄĞĞºÅ
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
	}//±»±êÖ¾µÄĞĞÒÀ´Î±»ÉÏÒ»ĞĞËùÈ¡´ú£¬¼´±»ÏûÈ¥
}//ÏûĞĞº¯Êı

void next_box()
{
	unsigned char i;
	unsigned int temp;
	temp=box_read_data(next_mode,next_shape);
	for(i=0;i<4;i++)
	{
		Box_Ram[3-i]=(temp&0x000f)|(Box_Ram[3-i]&0xfff0);
		temp=temp>>4;
	}//ÔÚÓÎÏ·µãÕó»º´æÖĞÏÔÊ¾ÏÂÒ»¸ö·½¿éµÄÑù×Ó
	for(i=5;i<10;i++)
	{
		Box_Ram[i]=num_data[i-5+5*score]|(Box_Ram[i]&0xfff0);
	}//ÔÚÓÎÏ·µãÕó»º´æÖĞÏÔÊ¾·ÖÊı£¬ÉÏÏŞÎª10
}//ÏÔÊ¾ÏÂÒ»¸ö·½¿éº¯Êı

void Tetris_main()
{
	unsigned char i;
	for(i=0;i<19;i++)
	{
		Box_Ram[i]=Box_Ram_data[i];
	};//ÔØÈëÓÎÏ·³õÊ¼ÏÔÊ¾»­Ãæ
	game_over_flag=0;//ÓÎÏ·½áÊø±êÖ¾Î»ÖÃ0±íÊ¾ÓÎÏ·Î´½áÊø
	box_build();
	box_load();
	next_box();
	box_to_Box_Ram(s_box.x,s_box.y,s_box.box);
	Box_Ram_to_Ram();
//	intermit0_initialize();
	time0_initialize();
	while((!game_over_flag)&&(score<1))//Èç¹ûÓÎÏ·½áÊø±êÖ¾Î»ÖÃ1£¬±íÊ¾ÓÎÏ·½áÊø£¬´òÆÆÑ­»·£¬µ÷ÓÃÓÎÏ·½áÊø»­ÃæÏÔÊ¾º¯Êı
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
	EA=0;//ÓÎÏ·½áÊøºó¹ØÖĞ¶Ï£¬Òª²»»º´æÇøÊı¾İ²»ÕıÈ·
	if(score>=1)
	{ 
	  game_victory_show();
	}else{			
		game_over_show(); 
	}
}//¶íÂŞË¹·½¿éÓÎÏ·Ö÷º¯Êı

void game_a_get()
{
	//ÅĞ¶ÏÊÇ·ñÊÇÔÚ³õÊ¼»¯·½¿é
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
}//µÃµ½ĞÅÏ¢µÄÅĞ¶Ï

void game_over_show()
{
	unsigned char i;
	bit tpflag=1;//ÖÃÑ­»·±êÖ¾Î»Îª1
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
	}//game over»­ÃæÑ­»·
	game_start_show();//½øÈëÓÎÏ·¿ªÊ¼ÏÔÊ¾»­Ãæ
}//ÓÎÏ·Ê§°Ü½áÊø»­ÃæÏÔÊ¾º¯Êı

void game_victory_show()
{
	unsigned char i;
	bit tpflag=1;//ÖÃÑ­»·±êÖ¾Î»Îª1
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
	}//victory»­ÃæÑ­»·
	game_start_show();//½øÈëÓÎÏ·¿ªÊ¼ÏÔÊ¾»­Ãæ
}//ÓÎÏ·³É¹¦½áÊø»­ÃæÏÔÊ¾º¯Êı

void game_initialize()
{
	box_down_reg=0;
	time0_reg=0;
	next_mode=6;
	next_shape=2;
	next_mode_flag=7;//±íÊ¾Ò»¿ªÊ¼»¹ÊÇ²»ÄÜ¸Ä±äÏÂÒ»¸öĞÎ×´µÄ
	game_over_flag=0;
	restart_game_flag=0;
	pause_game_flag=0;
	button_flag=0;
	score=0;
	box_num=0;
	a_flag=0;
}//ÓÎÏ·³õÊ¼»¯º¯Êı

void game_start_show()
{
	unsigned char i,j,n;
	bit tpflag=1;//ÖÃÑ­»·±êÖ¾Î»Îª1
	game_initialize();//µ÷ÓÃÓÎÏ·³õÊ¼»¯º¯Êı£¬³õÊ¼»¯ÓÎÏ·ËùÓĞ±äÁ¿
	for(i=0;i<16;i++)
	{
		Box_Ram[i]=0x0000;
	};//Çå³ıÍ¼Ïñ
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
	};//Çå³ıÍ¼Ïñ
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
	}//game_start_showÑ­»·
	Tetris_main();//½øÈë¶íÂŞË¹·½¿éÓÎÏ·Ö÷º¯Êı
}//ÓÎÏ·¿ªÊ¼ÏÔÊ¾»­Ãæ

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
	}//¼ì²éĞÂ½¨·½¿éÊÇ·ñºÍÔ­ÓĞÍ¼ĞÎÖØµş,ÖØµşÖÃ±êÖ¾Î»tpflagÎª1,²»ÖØµş²»ÖÃ±êÖ¾Î»£¬¼´tpflagÎª0
	return(tpflag);
}//¼ì²éÓÎÏ·½áÊøº¯Êı£¨ÓÎÏ·½áÊø·µ»Ø1£¬ÓÎÏ·Ã»ÓĞ½áÊø·µ»Ø0£©

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
	EA=1;//¿ªÖĞ¶Ï£¬¼ÌĞøÓÎÏ·
}//¼ì²âÔİÍ£ÓÎÏ·º¯Êı

