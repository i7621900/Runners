#ifndef _MOUSE_H_INCLUDED_
#define _MOUSE_H_INCLUDED_

#include"Player.h"

class Mouse
{
private:
	BITMAP *mouse;
	BITMAP *Menu[13];
	SAMPLE *Click_M;
	//bool Left; Debugging

public:
	Mouse();
	~Mouse(); 
	//void Debugging(BITMAP *Buffer);
	void MouseXY(BITMAP *Buffer);
	int Display_Menu(BITMAP *Buffer, int Options);
	int Display_Instructions(BITMAP *Buffer, int Options);
	int Player_Lose(BITMAP *Buffer, int Options);
	int Player_Win(BITMAP *Buffer, int Options);
};
#endif 
