#include<allegro.h>
#include"Global.h"
#include"Mouse.h"

Mouse::Mouse()
{
	mouse = load_bitmap("Mouse.bmp", 0); //Load mouse bmp

	BITMAP *temp = create_bitmap(10400, 600);
	temp = load_bitmap("Menu.bmp", 0); 
	if(!temp )
	{
		allegro_message("Error, temp bitmap");
		exit(1);
	}

	for (int i = 0; i <= 12; i++)
	{
		Menu[i] = create_bitmap(800, 600);
		blit(temp, Menu[i], i * 800, 0, 0, 0, 800, 600);
	}
	destroy_bitmap(temp);

	Click_M = load_sample("Click.wav");

	//Left = false;  Debugging
}

/*void Mouse::Debugging(BITMAP *Buffer)
{
textprintf(Buffer, font, 840, 180, makecol(255,0,0), "Mouse X = %i", mouse_x);
textprintf(Buffer, font, 840, 190, makecol(255,0,0), "Mouse Y = %i", mouse_y);
textprintf(Buffer, font, 840, 200, makecol(255,0,0), "Left Click = %s", Left? "True" : "False");
}*/


void Mouse::MouseXY(BITMAP *Buffer)
{
	masked_blit(mouse, Buffer, 0,0 , mouse_x, mouse_y, 32, 32);//Blit Mouse icon to Mouse X and Y
}

Mouse::~Mouse()
{
	destroy_bitmap(mouse);//Destroy mouse icon
	destroy_sample(Click_M);//destroy click sound

	for (int i = 0; i <= 12; i++) // destroy menu array
	{
		destroy_bitmap(Menu[i]);
	}
}

int Mouse::Display_Menu(BITMAP *Buffer, int Options)
{
	//Display Menu 
	if(mouse_x > 290 && mouse_x < 514 && mouse_y > 382 && mouse_y < 454) // Play = Red
	{
		blit(Menu[1],Buffer,0,0,0,0,ScreenWidth, ScreenHeight); // Turn Play Red
		if(Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);//Click sound
			Options = 2;
		}
	}
	else if(mouse_x > 17 && mouse_x < 350 && mouse_y > 533 && mouse_y < 570) //Instructions = Red
	{
		blit(Menu[2],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 1;
		}
	}
	else if(mouse_x > 664 && mouse_x < 768 && mouse_y > 537 && mouse_y < 573) //Quit = Red
	{
		blit(Menu[3],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 3;
		}
	}
	else 
	{
		blit(Menu[0],Buffer,0,0,0,0,ScreenWidth, ScreenHeight); // Display Menu
	}
	return Options; 
}

int Mouse::Display_Instructions(BITMAP *Buffer, int Options)
{
	if (mouse_x > 319 && mouse_x < 483 && mouse_y > 197 && mouse_y < 246)//Back = Red
	{
		blit(Menu[5],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 1;
		}
	}
	else 
	{
		blit(Menu[4],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
	}

	return Options; 
}

int Mouse::Player_Lose(BITMAP *Buffer, int Options)
{
	if (mouse_x > 23 && mouse_x < 383 && mouse_y > 44 && mouse_y < 93) //main menu = red
	{
		blit(Menu[10],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 1;
		}
	}
	else if (mouse_x > 637 && mouse_x < 783 && mouse_y > 43 && mouse_y < 95)//Quit = red
	{
		blit(Menu[11],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if(Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 2; 
		}
	}
	else
	{
		blit(Menu[9],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
	}

	return Options;
}

int Mouse::Player_Win(BITMAP *Buffer, int Options)
{
	if (mouse_x > 14 && mouse_x < 376 && mouse_y > 44 && mouse_y < 92)//Main_Menu = Red
	{
		blit(Menu[7],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 1;
		}
	}
	else if (mouse_x > 620 && mouse_x < 772 && mouse_y > 44 && mouse_y < 92)//Quit = Red
	{
		blit(Menu[8],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
		if (Left_Click)
		{
			play_sample(Click_M,255, 128, 1000, false);
			Options = 2;
		}
	}
	else 
	{
		blit(Menu[6],Buffer,0,0,0,0,ScreenWidth, ScreenHeight);
	}


	return Options;
}
