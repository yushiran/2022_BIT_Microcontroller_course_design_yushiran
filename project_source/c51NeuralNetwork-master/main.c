#include<reg51.h>	
#include"lcd.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Delay10ms(unsigned int c)   //��� 0us
{
    unsigned char a, b;

	//--c�Ѿ��ڴ��ݹ�����ʱ���Ѿ���ֵ�ˣ�������for����һ��Ͳ��ø�ֵ��--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}          
	}       
}

void cout(unsigned char *a,unsigned char *b,unsigned char tok)
{
    unsigned char a_len=strlen(a);
	unsigned char b_len=strlen(b);
	unsigned char i;

	LcdWriteCom(0x01);  //����
	//--д��һ��--//
	LcdWriteCom(0x80); //���������ڵ�1��
	for(i=0; i<a_len; i++)
	{
		LcdWriteData(a[i]);
	}

	//--д�ڶ���
	LcdWriteCom(0xC0); //���������ڵڶ���
	for(i=0; i<b_len; i++)
	{
		LcdWriteData(b[i]);
	}
	if(tok==1)
		LcdWriteCom(0x07); //����ÿдһ���������� */

	/*while(1)
	{			
		LcdWriteCom(0xC0); //���������ڵڶ���
		for(i=0; i<b_len; i++)
		{
			LcdWriteData(b[i]);
			Delay10ms(50);
		}
		
	}	*/			


}
unsigned char _i,_j,_k;
float  _sum;
void matrix_mult1(float a[3][2],unsigned char a_x,unsigned char a_y,float b[2][3],unsigned char b_y,float c[3][3]) 
{

//	char  str[10];
	
	//init_mempool(0x000,0x03ff);//����1k���ڴ�ռ� 
	//cout("for1","----",0);
	//Delay10ms(50);
	for (_i = 0; _i<a_x; ++_i)
	{
		for (_j = 0; _j<b_y; ++_j) {
			_sum = 0;
			for (_k = 0; _k<a_y; ++_k)
			{ 
				_sum += a[_i][_k] * b[_k][_j];
			//	sprintf(str,"%.1f--%s",a[i][k] * b[k][j],name);  //��ʾ������Ϣ
			//	cout( str ,"caulating-",0);
			//	Delay10ms(50);
			}
				
			c[_i][_j] = _sum;
		}
	}
   	//cout("for1ok","----",0);
	//Delay10ms(50);
}
void matrix_mult2(float  a[1][3],unsigned char a_x,unsigned char a_y,float b[3][1],unsigned char b_y,float c[1][1]) 
{
//	float  sum;
//	char  str[10];
//	unsigned  char i,j,k;
	//init_mempool(0x000,0x03ff);//����1k���ڴ�ռ�
	//cout("for2","----",0);
	//Delay10ms(50);
	for (_i = 0; _i<a_x; ++_i)
	{
		for (_j = 0; _j<b_y; ++_j) {
			_sum = 0;
			for (_k = 0; _k<a_y; ++_k)
			{ 
				_sum += a[_i][_k] * b[_k][_j];
			//	sprintf(str,"%.1f--%s",a[i][k] * b[k][j],name);  //��ʾ������Ϣ
			//	cout( str ,"caulating-",0);
			//	Delay10ms(50);
			}
				
			c[_i][_j] = _sum;
		}
	}
   	//cout("for2ok","----",0);
	//Delay10ms(50);
}		 
float f(float x)
{
 	//return 1.0f / (1 + exp(-x));
	return x>0?x:0;
}
float sigmoidf(float x)	 
{
 	//return f(x)*(1 - f(x));
	return 	x>0?1:0;
}  
void active1(float source[3][1],float target[3][1],int x,int y)	  //��source��sigmoid�������target
{
//	 char str[10];
 	 unsigned char i,j;
	 for(i=0;i<x;i++)
	 {
	 	for(j=0;j<y;j++)
		{
			target[i][j]=f(source[i][j]);
				//sprintf(str,"%.2f %.2f",source[i][j],f(source[i][j]));  //��ʾ������Ϣ
			//	cout( str ,"active-",0);
			//	Delay10ms(100);
		}
	 }
}			 
void active2(float source[1][1],float target[1][1],int x,int y)	  //��source��sigmoid�������target
{
	// char str[10];
 	 unsigned char i,j;
	 for(i=0;i<x;i++)
	 {
	 	for(j=0;j<y;j++)
		{
			target[i][j]=f(source[i][j]);
				//sprintf(str,"%.2f %.2f",source[i][j],f(source[i][j]));  //��ʾ������Ϣ
			//	cout( str ,"active-",0);
			//	Delay10ms(100);
		}
	 }
} 
void Trans(float source[3][1],float target[1][3],int x,int y)		//�����ת��
{
 	 unsigned char i,j;
	 for(i=0;i<x;i++)
	 {
	 	for(j=0;j<y;j++)
		{
			target[j][i]=source[i][j];
		}
	 }	
}		
void main()
{
	 float xdata input1[3][2]={{1,0},    //��׼����
	 				    	  {1,0},
							  {1,0}},input_t[2][3];
	 float xdata output1=0.0f;			//��׼���
	 float xdata input2[3][2]={{0,1},    //��׼����
	 				    	  {0,1},
							  {0,1}};
	 float xdata output2=0.0f;			//��׼���
	 float xdata input3[3][2]={{1,1},    //��׼����
	 				    	  {1,1},
							  {1,1}};
	 float xdata output3=1.0f;			//��׼���
	 float xdata input4[3][2]={{0,0},    //��׼����
	 				    	  {0,0},
							  {0,0}};
	 float xdata output4=0.0f;			//��׼���


     float xdata w1[2][3]={{0.3,0.7,0.5},
	 				 	   {0.5,0.8,0.1}};
	 float xdata q1[3][1]={{0.8},
	 			  	 	   {0.4},
				  	       {0.6}};
	 float xdata dfdw1[2][3],dfdw2[3][1],delta;
	 float xdata o[1][1];
	 float xdata res[4];
	 unsigned char xdata str[10];
	 float xdata t[3][3],h[3][1],h_t[1][3],z1[3][1],z[1][3],y[1][1];
	 float xdata err=0 ;  //�������
	 LcdInit();

	 while(1)
	 {	
		//cout("start","----",0);
		//Delay10ms(50);
	 	matrix_mult1(input1,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		err+=0.5*(o[0][0]-output1)*(o[0][0]-output1);//�������
		//���򴫵���ϡ������ݶ��½�
		delta=(o[0][0]-output1)*0.2*sigmoidf(y[0][0]);
		//����dfdw2
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   dfdw2[_i][_j]=delta*z1[_i][_j];
			}
		}
		//����dfdw1
	 	for(_i=0;_i<3;_i++)  //1.ת��input  3x2 -> 2x3
		 {
	 		for(_j=0;_j<2;_j++)
			{
				input_t[_j][_i]=input1[_i][_j];
			}
		 }
		 /*---------2.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
					_sum = 0;
				for (_k = 0; _k<3; ++_k)
				{ 
					_sum += input_t[_i][_k] * q1[_k][_j];
				}
				
				t[_i][_j] = _sum;  //��ʱ����t����2x1����
			}
		}
	 	for(_i=0;_i<3;_i++)  //3.ת��g  3x1 -> 1x3
		 {
	 		for(_j=0;_j<1;_j++)
			{
				h_t[_j][_i]=h[_i][_j];
			}
		 }
		 /*---------4.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
					_sum = 0;
				for (_k = 0; _k<1; ++_k)
				{ 
					_sum += t[_i][_k] * h_t[_k][_j];
				}
				
				dfdw1[_i][_j] = _sum*delta*0.2;  //��ʱ����t����2x1����
			}
		}
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   q1[_i][_j]-=dfdw2[_i][_j];
			}
		}
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
				   w1[_i][_j]-=dfdw1[_i][_j];
			}
		}
	 	matrix_mult1(input2,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		err+=0.5*(o[0][0]-output2)*(o[0][0]-output2);//�������
		//���򴫵���ϡ������ݶ��½�
		delta=(o[0][0]-output2)*0.2*sigmoidf(y[0][0]);
		//����dfdw2
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   dfdw2[_i][_j]=delta*z1[_i][_j];
			}
		}
		//����dfdw1
	 	for(_i=0;_i<3;_i++)  //1.ת��input  3x2 -> 2x3
		 {
	 		for(_j=0;_j<2;_j++)
			{
				input_t[_j][_i]=input2[_i][_j];
			}
		 }
		 /*---------2.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
					_sum = 0;
				for (_k = 0; _k<3; ++_k)
				{ 
					_sum += input_t[_i][_k] * q1[_k][_j];
				}
				
				t[_i][_j] = _sum;  //��ʱ����t����2x1����
			}
		}
	 	for(_i=0;_i<3;_i++)  //3.ת��g  3x1 -> 1x3
		 {
	 		for(_j=0;_j<1;_j++)
			{
				h_t[_j][_i]=h[_i][_j];
			}
		 }
		 /*---------4.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
					_sum = 0;
				for (_k = 0; _k<1; ++_k)
				{ 
					_sum += t[_i][_k] * h_t[_k][_j];
				}
				
				dfdw1[_i][_j] = _sum*delta*0.2;  //��ʱ����t����2x1����
			}
		}
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   q1[_i][_j]-=dfdw2[_i][_j];
			}
		}
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
				   w1[_i][_j]-=dfdw1[_i][_j];
			}
		}
	 	matrix_mult1(input3,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		err+=0.5*(o[0][0]-output3)*(o[0][0]-output3);//�������
		//���򴫵���ϡ������ݶ��½�
		delta=(o[0][0]-output3)*0.2*sigmoidf(y[0][0]);
		//����dfdw2
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   dfdw2[_i][_j]=delta*z1[_i][_j];
			}
		}
		//����dfdw1
	 	for(_i=0;_i<3;_i++)  //1.ת��input  3x2 -> 2x3
		 {
	 		for(_j=0;_j<2;_j++)
			{
				input_t[_j][_i]=input3[_i][_j];
			}
		 }
		 /*---------2.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
					_sum = 0;
				for (_k = 0; _k<3; ++_k)
				{ 
					_sum += input_t[_i][_k] * q1[_k][_j];
				}
				
				t[_i][_j] = _sum;  //��ʱ����t����2x1����
			}
		}
	 	for(_i=0;_i<3;_i++)  //3.ת��g  3x1 -> 1x3
		 {
	 		for(_j=0;_j<1;_j++)
			{
				h_t[_j][_i]=h[_i][_j];
			}
		 }
		 /*---------4.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
					_sum = 0;
				for (_k = 0; _k<1; ++_k)
				{ 
					_sum += t[_i][_k] * h_t[_k][_j];
				}
				
				dfdw1[_i][_j] = _sum*delta*0.2;  //��ʱ����t����2x1����
			}
		}
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   q1[_i][_j]-=dfdw2[_i][_j];
			}
		}
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
				   w1[_i][_j]-=dfdw1[_i][_j];
			}
		}
	 	matrix_mult1(input4,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		err+=0.5*(o[0][0]-output4)*(o[0][0]-output4);//�������
		//���򴫵���ϡ������ݶ��½�
		delta=(o[0][0]-output4)*0.2*sigmoidf(y[0][0]);
		//����dfdw2
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   dfdw2[_i][_j]=delta*z1[_i][_j];
			}
		}
		//����dfdw1
	 	for(_i=0;_i<3;_i++)  //1.ת��input  3x2 -> 2x3
		 {
	 		for(_j=0;_j<2;_j++)
			{
				input_t[_j][_i]=input4[_i][_j];
			}
		 }
		 /*---------2.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
					_sum = 0;
				for (_k = 0; _k<3; ++_k)
				{ 
					_sum += input_t[_i][_k] * q1[_k][_j];
				}
				
				t[_i][_j] = _sum;  //��ʱ����t����2x1����
			}
		}
	 	for(_i=0;_i<3;_i++)  //3.ת��g  3x1 -> 1x3
		 {
	 		for(_j=0;_j<1;_j++)
			{
				h_t[_j][_i]=h[_i][_j];
			}
		 }
		 /*---------4.����---------------------*/	
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
					_sum = 0;
				for (_k = 0; _k<1; ++_k)
				{ 
					_sum += t[_i][_k] * h_t[_k][_j];
				}
				
				dfdw1[_i][_j] = _sum*delta*0.2;  //��ʱ����t����2x1����
			}
		}
		for (_i = 0; _i<3; ++_i)
		{
			for (_j = 0; _j<1; ++_j) {
				   q1[_i][_j]-=dfdw2[_i][_j];
			}
		}
		for (_i = 0; _i<2; ++_i)
		{
			for (_j = 0; _j<3; ++_j) {
				   w1[_i][_j]-=dfdw1[_i][_j];
			}
		}

	 	sprintf(str,"ave_err:%.10f",err/4.0f);		  //�����ָ�ʽ��

		//����w1,q1
		cout( str ,"result-",0);	 
	 	Delay10ms(5);
		if(err<=0.00000001)
			break;   //ѵ������
	}
	while(1)
	{
	   matrix_mult1(input1,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		res[0]=o[0][0];
	   matrix_mult1(input2,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		res[1]=o[0][0];
	   matrix_mult1(input3,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		res[2]=o[0][0];
	   matrix_mult1(input4,3,2,w1,3,t); //�������ز�
		h[0][0]=t[0][0];
		h[1][0]=t[1][1];
		h[2][0]=t[2][2];
		active1(h,z1,3,1); //�������ز�
		Trans(z1,z,3,1);//ת�þ���
		matrix_mult2(z,1,3,q1,1,y);
		active2(y,o,1,1);//�������
		res[3]=o[0][0];
		sprintf(str,"%.1f %.1f %.1f %.1f",res[0],res[1],res[2],res[3]);		  //�����ָ�ʽ��
		cout( str ,"ok-",0);	 
	 	while(1)
		{

		}
	}


}