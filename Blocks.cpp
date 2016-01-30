#include<allegro.h>
#include"Blocks.h"
#include"Global.h"

Block::Block()
{
	block = load_bitmap("Block.bmp", 0); //load Bitmap
	Difficulty = false;
}

void Block::Create_Block(BITMAP* Buffer)
{
	if (key[KEY_B] && Difficulty == false){Difficulty = true;}
	else if (key[KEY_B] && Difficulty == true){Difficulty = false;}


	//Draw Flor and Blocks
	rectfill(Buffer, B_F.Floor1[0], B_F.Floor1[1], B_F.Floor1[2], B_F.Floor1[3], makecol(0,0,0));
	rectfill(Buffer, B_F.Floor2[0], B_F.Floor2[1], B_F.Floor2[2], B_F.Floor2[3], makecol(0,0,0));
	rectfill(Buffer, B_F.Floor3[0], B_F.Floor3[1], B_F.Floor3[2], B_F.Floor3[3], makecol(0,0,0));
	rectfill(Buffer, B_F.Floor4[0], B_F.Floor4[1], B_F.Floor4[2], B_F.Floor4[3], makecol(0,0,0));
	rectfill(Buffer, B_F.Floor5[0], B_F.Floor5[1], B_F.Floor5[2], B_F.Floor5[3], makecol(0,0,0));
	rectfill(Buffer, B_F.Floor6[0], B_F.Floor6[1], B_F.Floor6[2], B_F.Floor6[3], makecol(0,0,0));

	//if space is pressed, display Blocks
	if(key[KEY_SPACE] && Difficulty == true) {blit(block, Buffer, 0, 0, B_F.BlockX, B_F.BlockY, block->w, block->h);}
	else if (Difficulty == false) {blit(block, Buffer, 0, 0, B_F.BlockX, B_F.BlockY, block->w, block->h);}
}

void Block::Set_Floor()
{
	//Set Floor X and Y
	B_F.Floor1[0] = 0;
	B_F.Floor1[1] = 550;
	B_F.Floor1[2] = 540;
	B_F.Floor1[3] = 600;

	B_F.Floor2[0] = 960;
	B_F.Floor2[1] = 550;
	B_F.Floor2[2] = 1500;
	B_F.Floor2[3] = 600;

	B_F.Floor3[0] = 2400;
	B_F.Floor3[1] = 550;
	B_F.Floor3[2] = 3000;
	B_F.Floor3[3] = 600;

	B_F.Floor4[0] = 3700;
	B_F.Floor4[1] = 550;
	B_F.Floor4[2] = 4100;
	B_F.Floor4[3] = 600;

	B_F.Floor5[0] = 7424;
	B_F.Floor5[1] = 550;
	B_F.Floor5[2] = 7900;
	B_F.Floor5[3] = 600;

	B_F.Floor6[0] = 9500;
	B_F.Floor6[1] = 550;
	B_F.Floor6[2] = 11000;
	B_F.Floor6[3] = 600;
}

Block::~Block()
{
	destroy_bitmap(block);//destroy Block
}

