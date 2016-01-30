#include<allegro.h>
#include<vector>
#include<fstream>
#include<string>
#include"Player.h"
#include"Buffer.h"
#include"Blocks.h"
#include"Global.h"
#include"Mouse.h"

BITMAP *Buffer;

volatile int Counter = 0;

void Init (void);
void Counter_Function(void); 

int main(void)
{
	Init();
	Play Player1; //Create each object
	Buff Buffer1;
	Mouse Mouse1;

	std::vector<Block*> BlockVector; //create a vector of a class

	std::ifstream Block_File; //create a ifstream component
	Block_File.open("BlocksXY.txt"); //open Txt file 
	if(Block_File.fail()) // check for failure
	{
		allegro_message("Error, Block_File Failed");
		exit(1);
	}

	int Line_Counter = 0;
	std::string Junk; 

	//No body - runs until end of file - linecounter will equal total amount of lines in txt file
	for (; std::getline(Block_File, Junk); Line_Counter++);
	Block_File.close();

	Block_File.open("BlocksXY.txt"); 
	for (int i = 0; i < Line_Counter; i++) //Run for each line in the text file
	{
		int X, Y;
		Block_File >> X >> Y; // Takes a value for X and Y 
		BlockVector.push_back(new Block); //Pushes current Blockvector to the back and creates a new copy of Block
		BlockVector.back()->Set_BF(X, Y); //Sets Blocks X and Y
		BlockVector.back()->Set_Floor(); // Sets Floor X and Y
	}

	Block_File.close();

	int Options = 0;
	int Lives = 1; 
	int Sound = 0; 

	SAMPLE *Main_Menu_M = load_sample("Main Menu Music.wav"); // Load music sample into the game
	if (!Main_Menu_M)
	{		
		allegro_message("Error, Block_File Failed");
		exit(1);
	}

	SAMPLE *InGame_M = load_sample("In-Game Music.wav");
	//if (!InGame_M)
	//{
	//	allegro_message("Error, Block_File Failed");
	//	exit(1);
	//}

	enum GameState {MENU, INSTRUCTIONS, INGAME, EXIT, LOSE, WIN}; // Creates multiple gamestates, each having a constant value
	GameState gamestate = MENU;

	Buffer = Buffer1.Buffer_Set_Up();

	install_int(Counter_Function,60); // start Allegro timer and call it every 60ms

	//game loop 
	while(!key[KEY_ESC])
	{
		if (Counter > 0) //basic FPS counter
		{
			Counter = 0;

			switch(gamestate)
			{
			case MENU:// Gamestate Menu controls the main menu of the game
				if (Sound == 0){play_sample(Main_Menu_M, 255, 128, 1000, true);}

				Options = 0; 
				Lives = Player1.Player_Reset(Lives); // resets character
				Buffer1.Buffer_Clear_To_Color(Buffer); //Clears Buffer
				//Mouse1.Debugging(Buffer); //Shows Mouse Debugging
				Options = Mouse1.Display_Menu(Buffer, Options); // Runs menu 

				Sound = 1;

				if(Options == 1){gamestate = INSTRUCTIONS;}
				else if(Options == 2)
				{
					Sound = 0;
					stop_sample(Main_Menu_M);// stops music
					gamestate = INGAME;
				}
				else if(Options == 3){gamestate = EXIT;}
				else {gamestate = MENU;}

				Mouse1.MouseXY(Buffer); 
				Buffer1.Update_Screen(Buffer); //Displays Buffer/Camera
				break;

			case INSTRUCTIONS: // Gamestate instructions leads to the instruction page
				Options = 0; 
				Buffer1.Buffer_Clear_To_Color(Buffer); //Clears Buffer
				//Mouse1.Debugging(Buffer);Debugging
				Options = Mouse1.Display_Instructions(Buffer, Options);

				if(Options == 1){gamestate = MENU;}
				else {gamestate = INSTRUCTIONS;}

				Mouse1.MouseXY(Buffer); 
				Buffer1.Update_Screen(Buffer); //Displays Buffer/Camera
				break;

			case INGAME://Game state Ingame plays the game for the player, only accessed from the main menu
				if (Sound == 0){play_sample(InGame_M, 255, 128, 1000, true);}

				Sound = 0;
				Buffer1.Buffer_Clear_To_Color(Buffer); //Clears Buffer
				Player1.Background(Buffer);  //Draws Background
				Player1.Player_To_Screen(Buffer); //Draws Player
				//Player1.Debugging(Buffer, Lives); //Draws Debugging
				

				for (unsigned int i = 0; i < BlockVector.size(); i++)
				{
					BlockVector[i]->Create_Block(Buffer);
				}

				Player1.Player_Movement();//Sets Players Position
				Player1.Set_Camera_Position();//Sets Camera Position
				Player1.Player_Jumping(); //Calls Jumping Function

				for (unsigned int i = 0; i < BlockVector.size(); i++)
				{
					Lives = Player1.Player_Collision(BlockVector[i], Lives);

				}

				Player1.Draw_Camera(Buffer); //Displays Buffer/Camera

				Sound = 1;

				if (Lives == 0)
				{
					stop_sample(InGame_M);
					Sound = 0;
					gamestate = LOSE;
				}
				else if (Lives == 2)
				{
					stop_sample(InGame_M);
					Sound = 0;
					gamestate = WIN;
				}
				break;

			case EXIT: // Quits the game
				return 0;
				break;

			case LOSE:
				Options = 0; 
				Buffer1.Buffer_Clear_To_Color(Buffer); //Clears Buffer
				//Mouse1.Debugging(Buffer); Debugging
				Options = Mouse1.Player_Lose(Buffer, Options);

				if(Options == 1){gamestate = MENU;}
				else if(Options == 2){gamestate = EXIT;}
				else {gamestate = LOSE;}

				Mouse1.MouseXY(Buffer); 
				Buffer1.Update_Screen(Buffer); //Displays Buffer/Camera
				break;

			case WIN:
				Options = 0; 
				Buffer1.Buffer_Clear_To_Color(Buffer); //Clears Buffer
				//Mouse1.Debugging(Buffer);
				Options = Mouse1.Player_Win(Buffer, Options);

				if(Options == 1){gamestate = MENU;}
				else if(Options == 2){gamestate = EXIT;}
				else {gamestate = WIN;}

				Mouse1.MouseXY(Buffer); 
				Buffer1.Update_Screen(Buffer); //Displays Buffer/Camera
				break;
			}
		}
	}

	remove_int(Counter_Function);//End Allegro timer
	Buffer1.Buffer_Destroy(Buffer);// Destroy buffer
	destroy_sample(Main_Menu_M);//Destroy music
	destroy_sample(InGame_M);

	for (unsigned int i = 0; i < BlockVector.size(); i++) // Delete each BlockVector 
	{
		delete BlockVector[i];
	}

	return 0;
}
END_OF_MAIN();
void Init(void)
{
	allegro_init();
	install_keyboard();
	install_timer();
	install_mouse(); 
	install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, ScreenWidth, ScreenHeight, 0, 0); 
	set_window_title("Allegro");
}

void Counter_Function(void)
{
	Counter++;
}
