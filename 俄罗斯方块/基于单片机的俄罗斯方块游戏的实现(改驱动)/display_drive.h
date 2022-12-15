#define Line P1
sbit CLK=P2^0;           //MAX7219����ʱ��        
sbit DIN=P2^1;           //MAX7219��������       
sbit LOAD1=P2^2;          //MAX7219_1Ƭѡ       
sbit LOAD2=P2^3;          //MAX7219_2Ƭѡ 
sbit LOAD3=P2^4;          //MAX7219_3Ƭѡ 
sbit LOAD4=P2^5;          //MAX7219_4Ƭѡ 

unsigned char Ram[]=
{
0x7F,0x02,0x1F,0x10,0x1F,0x10,0x1F,0x10,0xFE,0x00,0xF0,0x10,0xF0,0x10,0xF0,0x10,
0x1F,0x08,0x0F,0x08,0x16,0x21,0x0E,0x70,0xF0,0x00,0xF0,0x20,0x40,0x80,0x70,0x0E,
};//��ʾ���󻺴棨1��ʾ����0��ʾ��

void delay(unsigned char temp)
{
	unsigned char tp=temp;
	while(tp--);
}//��ʱ����		

void delay_new(unsigned int z)
{
	unsigned int x,y;
	for(x=z;x>0;x--)
		for(y=111;y>0;y--);
}//����ʱ����	

void Write_Max7219_byte( unsigned char DATA )
{
	unsigned char i;
	for ( i = 8; i >= 1; i-- )
	{
		CLK	= 0;
		DIN	= DATA & 0x80;
		DATA	= DATA << 1;
		CLK	= 1;
	}
}

void Write_Max7219_1( unsigned char address, unsigned char dat )
{
	LOAD1=0;
	Write_Max7219_byte( address );  /* �� */
  Write_Max7219_byte( dat );      /* �� */
	LOAD1=1;
}
void Write_Max7219_2( unsigned char address, unsigned char dat )
{
	LOAD2=0;
	Write_Max7219_byte( address );  /* �� */
  Write_Max7219_byte( dat );      /* �� */
	LOAD2=1;
}
void Write_Max7219_3( unsigned char address, unsigned char dat )
{
	LOAD3=0;
	Write_Max7219_byte( address );  /* �� */
  Write_Max7219_byte( dat );      /* �� */
	LOAD3=1;
}
void Write_Max7219_4( unsigned char address, unsigned char dat )
{
	LOAD4=0;
	Write_Max7219_byte( address );  /* �� */
  Write_Max7219_byte( dat );      /* �� */
	LOAD4=1;
}

void Init_Max7219()
{
  Write_Max7219_1(0x09,0x00);  //���뷽ʽΪBCD��
	Write_Max7219_1(0x0a,0x03);  //����
	Write_Max7219_1(0x0b,0x07);  //ɨ����ޣ�8��LED��ʾ
	Write_Max7219_1(0x0c,0x01);  //����ģʽΪ0.��ͨģʽΪ1��
	Write_Max7219_1(0x0f,0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0
	
  Write_Max7219_2(0x09,0x00);  //���뷽ʽΪBCD��
	Write_Max7219_2(0x0a,0x03);  //����
	Write_Max7219_2(0x0b,0x07);  //ɨ����ޣ�8��LED��ʾ
	Write_Max7219_2(0x0c,0x01);  //����ģʽΪ0.��ͨģʽΪ1��
	Write_Max7219_2(0x0f,0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0
	
	Write_Max7219_3(0x09,0x00);  //���뷽ʽΪBCD��
	Write_Max7219_3(0x0a,0x03);  //����
	Write_Max7219_3(0x0b,0x07);  //ɨ����ޣ�8��LED��ʾ
	Write_Max7219_3(0x0c,0x01);  //����ģʽΪ0.��ͨģʽΪ1��
	Write_Max7219_3(0x0f,0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0
	
	Write_Max7219_4(0x09,0x00);  //���뷽ʽΪBCD��
	Write_Max7219_4(0x0a,0x03);  //����
	Write_Max7219_4(0x0b,0x07);  //ɨ����ޣ�8��LED��ʾ
	Write_Max7219_4(0x0c,0x01);  //����ģʽΪ0.��ͨģʽΪ1��
	Write_Max7219_4(0x0f,0x00);  //��ʾ���ԣ�1�����Խ�����������ʾ��0
	
}//MAX7219��ʼ��������MAX7219�ڲ��Ŀ��ƼĴ���

void display()
{
	unsigned char i;
	for (i=1; i<9;i++)
	{
		Write_Max7219_1(i,Ram[i-1]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_2(i,Ram[i-1+8]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_3(i,Ram[i-1+16]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_4(i,Ram[i-1+24]);
	}
  delay_new(15);
}//������ʾ����

void display_for_ikun()
{
	unsigned char i;
	for (i=1; i<9;i++)
	{
		Write_Max7219_1(i,Ram[i-1]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_2(i,Ram[i-1+8]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_3(i,Ram[i-1+16]);
	}
		for (i=1; i<9;i++)
	{
		Write_Max7219_4(i,Ram[i-1+24]);
	}
  delay_new(15);
}//ikun������ʾ����