/*Tetris.h中定义*/
unsigned int code Box_Ram_data[]=
{
0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,
0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,0x0020,
0xffff,0x0000,0x0000//多出来的三行是为了能让方块落到最低位置
					//多出来的第一行置0xffff用于检测方块释放到底
					//显示行初值为0x0020表示右边界
};//游戏点阵缓存10*16(用前10位表示)（1表示亮，0表示灭）

unsigned int code game_data[]=
{
0x64DB,0x8AAA,0x8AAA,0x8AAB,0xEEAA,0xAAAA,0xEAAB,0x0000
};//game字模（0x64,0xDB,0x8A,0xAA,0x8A,0xAA,0x8A,0xAB,0xEE,0xAA,0xAA,0xAA,0xEA,0xAB,0x00,0x00,）

unsigned int code over_data[]=
{
0x6566,0x9549,0x9549,0x956F,0x954A,0x9549,0x6268,0x0000
};//over字模（0x65,0x66,0x95,0x49,0x95,0x49,0x95,0x6F,0x95,0x4A,0x95,0x49,0x62,0x68,0x00,0x00,）

unsigned int code tetris_data[]=
{
0xE000,0x4008,0x4000,0x5A6B,0x574A,0x5A4B,0x5249,0x5B4B
};//tetris字模（0xE0,0x00,0x40,0x08,0x40,0x00,0x5A,0x6B,0x57,0x4A,0x5A,0x4B,0x52,0x49,0x5B,0x4B,）

unsigned int code WIN_data[]=
{
0x0000,0x0000,0x0000,0x0000,0x55D1,0x5499,0x5495,0x5495,0x5495,0x5493,0x29D1,0x0000,0x0000,0x0000,0x0000,0x0000,
};//win字模

unsigned int code start_show[]= { 
//1
0xFFFF,0xFFFF,0xFDFF,0xFAFF,0xFC7F,0xF1BF,0xF75F,0xFA5F,
0xFD5F,0xFE3F,0xFE3F,0xFE1F,0xFCCF,0xFDEF,0xF9E7,0xF9F7,
//2
0xFFFF,0xFFFF,0xFF3F,0xFEBF,0xFF0F,0xFED7,0xFE5B,0xFCB7,
0xFCAF,0xFD1F,0xFF1F,0xFE0F,0xFCE7,0xF9F7,0xFBF7,0xF3F3,
//3
0xFFFF,0xFFFF,0xFFFF,0xFF9F,0xFF5F,0xFF87,0xFE6B,0xFEAB,
0xFEDB,0xFED7,0xFF4F,0xFF0F,0xFE07,0xFCF3,0xFBFB,0xFBFB,
//4
0xFFFF,0xFFFF,0xFE7F,0xFD7F,0xFE7F,0xF807,0xF9F7,0xFAEB,
0xFD5B,0xFEBB,0xFF37,0xFF0F,0xFE07,0xFCF3,0xFBFB,0xFBFB,
//5
0xFFFF,0xFFFF,0xFFFF,0xFF9F,0xFF5F,0xFF87,0xFE6B,0xFEAB,
0xFEDB,0xFED7,0xFF4F,0xFF0F,0xFE07,0xFCF3,0xFBFB,0xFBFB,
//6
0xFFFF,0xFFFF,0xFF3F,0xFEBF,0xFF0F,0xFED7,0xFE5B,0xFCB7,
0xFCAF,0xFD1F,0xFF1F,0xFE0F,0xFCE7,0xF9F7,0xFBF7,0xF3F3,
};//ikun字模，六个动作帧


unsigned int code num_data[]=
{
0x002E,0x002A,0x002A,0x002A,0x002E,//数字0字模
0x002C,0x0024,0x0024,0x0024,0x002E,//数字1字模
0x002E,0x0022,0x002E,0x0028,0x002E,//数字2字模
0x002E,0x0022,0x002E,0x0022,0x002E,//数字3字模
0x002A,0x002A,0x002E,0x0022,0x0022,//数字4字模
0x002E,0x0028,0x002E,0x0022,0x002E,//数字5字模
0x002E,0x0028,0x002E,0x002A,0x002E,//数字6字模
0x002E,0x0022,0x0022,0x0022,0x0022,//数字7字模
0x002E,0x002A,0x002E,0x002A,0x002E,//数字8字模
0x002E,0x002A,0x002E,0x0022,0x0022,//数字9字模
};


unsigned int idata Box_Ram[19];//定义游戏点阵缓存10*16
unsigned int idata score;//定义分数寄存器
unsigned int idata box_num; //用来存储掉落个数
unsigned char a;//用来存储收到的信息
unsigned char a_flag;//用来判断是否收到信息
unsigned char box_down_reg;//定义方块下落累加寄存器
unsigned char time0_reg;//定义定时器0累加寄存器
unsigned char time1_reg;//定义定时器1累加寄存器
unsigned char next_mode;//定义下一个方块的类型
unsigned char next_shape;//定义下一个方块的形状
unsigned char next_mode_flag;//用来表示能否改变next_shape
unsigned char button_value;//用来存储按下的按钮值
unsigned char button_flag;//用来存储按下的按钮值
bit game_over_flag;//游戏结束标志位置0表示游戏未结束
bit pause_game_flag;//游戏暂停标志位置0表示游戏未暂停
bit restart_game_flag;//游戏重新开始功能键

struct
{
	unsigned char mode;//类型
	unsigned char shape;//形状
	unsigned char x;//x坐标
	unsigned char y;//y坐标
	unsigned int box;//定义方块缓存-
}s_box;	//定义方块结构体

//声明函数
void box_build();//方块生成函数
unsigned int box_read_data(unsigned char tpmode,unsigned char tpshape);//方块缓存数据函数（输入方块类型和形状即可获得方块缓存数据）
void box_load();//方块载入函数
void box_to_Box_Ram(unsigned char tpx,unsigned char tpy,unsigned int tpbox);//方块映射游戏点阵缓存函数（参数是原来方块的位置、缓存，先消去原有位置的方块）
void Box_Ram_to_Ram();//游戏点阵缓存映射显示点阵缓存函数
void game_execute();//游戏执行函数（控制方块下落，检测是否到底，如果到底调用消行函数）
void time0_initialize();//定时器0初始化函数
bit check_cover(unsigned char tpx,unsigned char tpy,unsigned int tpbox);//检查覆盖函数（检查此时带入的参数所确定的方块是否会覆盖原有图形，不会覆盖返回1，覆盖返回0）
void destroy_row();//消行函数
void next_box();//显示下一个方块函数
void Tetris_main();//俄罗斯方块游戏主函数
void game_over_show();//游戏失败结束画面显示函数
void game_victory_show();//游戏成功结束画面显示函数
void game_initialize();//游戏初始化函数
void game_start_show();//游戏开始显示画面
bit check_game_over();//检查游戏结束函数（游戏结束返回1，游戏没有结束返回0）
void check_pause_game();//检测暂停游戏函数
void game_a_get();//检测分类收到的信息

/*button_drive.h中定义*/
#define button_delay 600  //按键延时
sbit button_a = P0^7;
sbit button_b = P0^6;
sbit up = P3^4;
sbit down = P3^5;
sbit left = P3^6;
sbit right = P3^7;
sbit beep = P0^0;
									 
unsigned int up_reg=button_delay;       //按键up累加器
unsigned int down_reg=button_delay;     //按键down累加器
unsigned int left_reg=button_delay;     //按键left累加器
unsigned int right_reg=button_delay;    //按键right累加器
unsigned int button_a_reg=button_delay; //按键button_a累加器
unsigned int button_b_reg=button_delay; //按键button_a累加器

//声明函数
void game_button();//游戏中按键识别程序（有优先级，从高到低依次是button_a_reg>down>left>right）
unsigned char basic_button();//基本按键程序(返回0表示没按键被按下，返回1表示down被按下，返回2表示up被按下，返回3表示button_a被按下,返回4表示left被按下,返回5表示right被按下)
/*button_drive.h中定义*/