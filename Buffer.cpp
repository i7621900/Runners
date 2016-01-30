#include<allegro.h>
#include"Buffer.h"
#include"Global.h"

BITMAP * Buff::Buffer_Set_Up(void)
{
	//Create second buffer
	BITMAP * tmp;
	tmp = create_bitmap(ScreenEnd, ScreenHeight);
	return tmp; 
}

void Buff::Buffer_Clear_To_Color(BITMAP* Buffer)
{
	clear_to_color(Buffer, makecol(255,255,255)); // Clear screen to white
}

void Buff::Buffer_Destroy(BITMAP* Buffer)
{
	destroy_bitmap(Buffer);//destroy buffer
}

void Buff::Update_Screen(BITMAP* Buffer)
{
	blit(Buffer, screen, 0,0,0,0,ScreenWidth,ScreenHeight);//Draw buffer
}
