#include <reg52.h>
#include <display_drive.h>
#include <Tetris_define.h>
#include <button_drive.h>
#include <Tetris.h>

void main()
{	 
	Init_Max7219();
	uart_init();
  game_start_show();
}
