#include<allegro.h>
#include"Player.h"
#include"Global.h"

Play::Play()
{
	//Create Player Array
	BITMAP* temp = create_bitmap(608,32); //Size of Sprite BMP

	temp = load_bitmap("Allegro Game Walking Sprite Sheet.bmp", 0);
	if (!temp) // Error checking
	{
		allegro_message("Error, temp bitmap");
		exit(1);
	}

	//Fill Player Array
	for (int i = 0; i <= 10; i++)
	{
		Player[i] = create_bitmap(32,32);
		blit(temp, Player[i], i * 32, 0, 0, 0, 32, 32);
	}
	destroy_bitmap(temp);

	//Create Background Array
	BITMAP* B_Temp = create_bitmap(3200,600); //Size of Background Sprite

	B_Temp = load_bitmap("Background.bmp",0);
	if(!B_Temp)
	{
		allegro_message("Error, B_Temp bitmap");
		exit(1);
	}

	//Fill Background Array
	for (int i = 0; i <= 3; i++)
	{
		Backgrounds[i] = create_bitmap(800,600);
		blit(B_Temp, Backgrounds[i], i * 800, 0, 0, 0, 800, 600);
	}
	destroy_bitmap(B_Temp);

	PlayerSpeed = 10;
	PlayerX = 0;
	PlayerY = 0;
	animCounter = 0;
	Jumping = 0; 
	Velocity = 1;
	Back_Counter = 0; 
	Score = 0; 
	HighScore = 0; 
	PlayerCamX = 0;

	Floor_Collision = false; 
	Block_Collision = false; 
	Player_Jump = false; 
	//BoxTouch = false; 
}

void Play::Player_Movement()
{
	//Constant
	PlayerX += PlayerSpeed;
	Score++; 

	if (Score >= HighScore) {HighScore = Score;}
}

void Play::Player_To_Screen(BITMAP* Buffer)
{
	//Walking
	if (Player_Jump == false)
	{
		if(animCounter == 9) //After jumping check
			animCounter = 0; 

		masked_blit(Player[animCounter], Buffer, 0, 0, PlayerX, PlayerY, 32, 32);
		animCounter++;

		if(animCounter == 8) //Repeats animation
			animCounter = 0; 
	}

	//Jumping
	if (Player_Jump == true)
	{
		masked_blit(Player[8], Buffer, 0, 0, PlayerX, PlayerY, 32, 32);
	}
}

void Play::Player_Jumping()
{
	//Jumping:
	if (key[KEY_UP] && (Floor_Collision == true || Block_Collision == true) && Player_Jump == false && !key[KEY_SPACE])
	{
		Jumping = 6;
		Player_Jump = true; 
	}

	//Constantly Updating: 
	PlayerY -= Jumping;
	Jumping -= Velocity;	

	if(Jumping <= -20)
		Jumping = -20; 


}

/* Player Debugging
void Play::Debugging(BITMAP* Buffer, int Lives)
{
textprintf(Buffer, font, 840, 100, makecol(255,0,0), "Player X = %i", PlayerX);
textprintf(Buffer, font, 840, 110, makecol(255,0,0), "Player Y = %i", PlayerY);
textprintf(Buffer, font, 840, 120, makecol(255,0,0), "PlayerCamX = %i", PlayerCamX); 
textprintf(Buffer, font, 840, 130, makecol(255,0,0), "Jumping = %s", Player_Jump? "True" : "False");
textprintf(Buffer, font, 840, 140, makecol(255,0,0), "Collision With Blocks = %s", Block_Collision? "True" : "False");
textprintf(Buffer, font, 840, 150, makecol(255,0,0), "Collision With Floor = %s", Floor_Collision? "True" : "False");
textprintf(Buffer, font, 840, 160, makecol(255,0,0), "Jumping Height = %i", Jumping);
textprintf(Buffer, font, 840, 170, makecol(255,0,0), "Lives = %i", Lives);
textprintf(Buffer, font, 840, 180, makecol(255,0,0), "Box Touch = %s", BoxTouch? "True" : "false");

}
*/

void Play::Set_Camera_Position()
{
	//Centers Player
	PlayerCamX = PlayerX - ScreenWidth / 2;

	//Stops camera from going off screen
	if (PlayerCamX < 0) PlayerCamX = 0; 
	if (PlayerCamX > ScreenEnd) PlayerCamX = ScreenEnd;

}

void Play::Draw_Camera(BITMAP* Buffer)
{
	textprintf_ex(Buffer, font, PlayerCamX, 5, makecol(255,255,255),-1, "Score = %i", Score);
	textprintf_ex(Buffer, font, (PlayerCamX + ScreenWidth - 150), 5, makecol(255,255,255),-1, "HighScore = %i", HighScore);
	blit(Buffer, screen, PlayerCamX, 0, 0, 0, ScreenWidth, ScreenHeight); // Draw camera to screen
}

int Play::Player_Reset(int Lives) //Reset for every game
{
	PlayerX = 32;
	PlayerY = 520;
	PlayerSpeed = 10; 
	Lives = 1; 
	Score = 0; 
	return Lives; 
}

void Play::Background(BITMAP *Buffer)
{
	//Display background - Follows player
	blit(Backgrounds[Back_Counter],Buffer, 0, 0, PlayerCamX, 0, ScreenWidth, ScreenHeight);
	Back_Counter++;

	if(Back_Counter == 3){Back_Counter = 0;}
}

Play::~Play() //Destructor
{
	//Destroy Player and Background
	for (int i = 0; i <= 9; i++)
		destroy_bitmap(Player[i]);

	for (int i = 0; i <= 3; i++)
		destroy_bitmap(Backgrounds[i]);
}

int Play::Player_Collision(Block *Block, int Lives)
{
	// collision with top of blocks
	if ((PlayerY + Player[0]->h) > Block->Get_BF().BlockY && 
		(PlayerY - Player[0]->h) < Block->Get_BF().BlockY &&
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().BlockX && 
		(PlayerX - (Player[0]->w/2)) < Block->Get_BF().BlockX)
	{
		Block_Collision = true; 
		Player_Jump = false; 
		PlayerY = Block->Get_BF().BlockY - Player[0]->h;
	}

	//Collision With Floor
	if (((PlayerY+Player[0]->h) >= Block->Get_BF().Floor1[1] && 
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor1[2]) ||

		((PlayerY+Player[0]->h) >= Block->Get_BF().Floor2[1] &&
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().Floor2[0] &&
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor2[2]) ||

		((PlayerY+Player[0]->h) >= Block->Get_BF().Floor3[1] && 
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().Floor3[0] &&
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor3[2]) ||

		((PlayerY+Player[0]->h) >= Block->Get_BF().Floor4[1] && 
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().Floor4[0] &&
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor4[2])  ||

		((PlayerY+Player[0]->h) >= Block->Get_BF().Floor5[1] && 
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().Floor5[0] &&
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor5[2]) ||

		((PlayerY+Player[0]->h) >= Block->Get_BF().Floor6[1] && 
		(PlayerX + (Player[0]->w/2)) > Block->Get_BF().Floor6[0] &&
		(PlayerX + (Player[0]->w/2)) < Block->Get_BF().Floor6[2]))
	{
		Floor_Collision = true; 
		Player_Jump = false; 
		PlayerY = Block->Get_BF().Floor1[1] - Player[0]->h; 
	}
	else
	{
		Floor_Collision = false;
	}


	//Life check
	if (PlayerY > 575)
		Lives = 0;

	if (PlayerX > ScreenEnd)
		Lives = 2;

	return Lives;
}
