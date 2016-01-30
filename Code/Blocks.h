#ifndef _BLOCKS_H_INCLUDED_
#define _BLOCKS_H_INCLUDED_

struct Block_Floor
{
	int BlockX, BlockY;
	int Floor1[4];
	int Floor2[4];
	int Floor3[4];
	int Floor4[4];
	int Floor5[4];
	int Floor6[4];
};

class Block
{
private:
	Block_Floor B_F; //initalise struct
	BITMAP* block;
	bool Difficulty; //Hard = true, Easy = false

public:
	Block();
	~Block(); 

	void Create_Block(BITMAP *Buffer);
	void Set_Floor();

	Block_Floor Get_BF() // Getter 
	{
		return B_F;
	};

	void Set_BF(int X, int Y) // Setter
	{
		B_F.BlockX = X;
		B_F.BlockY = Y; 
	};

};
#endif 
