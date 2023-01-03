# 2022_BIT_Microcontroller_course_design_Yu shiran_Wang yue_Xu jiayi_Crew
---
## 基础要求
### 下位机：完成电路设计与控制程序
check 1.采用按键控制方块左右移动位置，采用16*8 点阵LED 屏显示位置，以16*8 点阵LED 屏（MATRIX-8*8，2 片)构成XY 坐标，点阵屏驱动芯片MAX7219，初始下落为2*2 方块、2*1 竖块、1*1 点，当一行满格则消灭此行，剩余位置下落。

check 2.通过串口与上位机通讯，实时传输点阵屏状态。
### 上位机：完成界面设计与通讯程序
check 1.构造16*8 点阵LED，能够实时在构造的点阵LED 上点亮相应位置的灯，显示当前下落方块类型。按钮控制方块左右移动。

check 4.可以对串口进行设置（端口、波特率、数据位、停止位、校验位）

## 进阶要求

### 下位机：
check 1.按键可启动、暂停游戏、旋转方块、退出当前游戏回到初始状态。

check 2.当消灭累计10 行，显示V，三秒后回到初始状态。

check 3.可接收上位机新设置的下落方块。

### 上位机：
check 1.能够预设下落方块的类型，不少于3种。

check 2.能够提示下一个下落方块类型。

3.将消灭满格信息储存在文档中，需记录此时下落了方块的数量、消灭满格的行数。

## 自由发挥
check 1.利用上位机实现手势识别方块预设

check 2.能够播放开机视频

CHECK 3.有音乐配乐

---
# WARNING!
## 下位机：
1. 51单片机硬件设计使用proteus8.15进行设计，
文件是下位机文件夹中的game.pdsprj。
2. 51单片机软件程序是使用keil uVision 5.14.2进行编写，
文件是下位机文件夹中的game.uvproj

## 上位机：
1. 上位机文件夹中有两个文件，一个是上位机程序的代码，
另一个是打包出的可执行文件pyserial_demo。
2. 上位机程序文件夹可以使用pycharm社区版打开，编译器采用的是python3.8，按照要求安装引用的api后运行pyserial_demo.py就可以看到上位机程序了。
3. 为了方便使用可以直接测试上位机文件夹中的pyserial_demo文件夹中的pyserial_demo.exe的可执行文件，
上位机的图像文件都存储在image文件夹里，而游戏数据就存储在record.txt文档文件中，record.txt就在pyserial_demo文件夹内。
因为mediapipe库的原因，应将pyserial_demo文件夹复制到全英文绝对路径环境下才可以使用手部识别功能，建议将文件夹复制到桌面进行使用。

## 电脑配置：
CPU	Intel(R) Core(TM) i5-10400F CPU @ 2.90GHz   2.90 GHz

GPU AMD Radeon RX 6600

操作系统 Windows 10

内存 16.0 GB

硬盘 1T

# 视频演示

[![演示视频](https://i.ytimg.com/vi/8E7bCVscW8Q/hqdefault.jpg)](https://www.youtube.com/watch?v=8E7bCVscW8Q "演示视频")

