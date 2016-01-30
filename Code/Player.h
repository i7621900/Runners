#ifndef _PLAYER_H_INCLUDED_
#define _PLAYER_H_INCLUDED_

#include"Blocks.h"//Include Blocks header

class Play
{

private:
	BITMAP *Player[10]; //create bitmap array
	BITMAP *Backgrounds[4]; 

	int PlayerSpeed;
	int PlayerX;
	int PlayerY;
	int Jumping;
	int animCounter;
	int PlayerCamX;
	int Velocity;
	int Back_Counter;
	int Score;
	int HighScore; 
	bool Floor_Collision; 
	bool Block_Collision;
	bool Player_Jump;
	//bool BoxTouch; // debugging
	
public:
	Play();//Constructor
	~Play(); //Destructor

	void Player_Movement();
	void Player_To_Screen(BITMAP *Buffer);
	void Player_Jumping();
	int Player_Reset(int Lives);
	int Player_Collision(Block *Block, int Lives);
	void Set_Camera_Position();
	void Draw_Camera(BITMAP *Buffer);
	void Background(BITMAP *Buffer);

	//Debugging:
	//void Debugging(BITMAP *Buffer, int Lives);
};

#endif
