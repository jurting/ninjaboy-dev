/*~Jurting
NinjaBoy, a game by BitQube.

Code and big comments will be signed with "~<nick>"
Note: Signing does not mean that the entire function
is created by that person, it just means that he/she
was the one who made the base.
*/


/*~Jurting
Compiled with simple script

#!/bin/sh
cd "$GEDIT_CURRENT_DOCUMENT_DIR"
echo "$GEDIT_CURRENT_DOCUMENT_DIR"
g++ "${GEDIT_CURRENT_DOCUMENT_DIR}/main.cpp" -o "${GEDIT_CURRENT_DOCUMENT_DIR}/linux-86" -lSDL -lSDL_gfx -lSDL_ttf -lSDL_net -DPC
gnome-terminal -x "${GEDIT_CURRENT_DOCUMENT_DIR}/linux-86" 

Note: Following gedit script also runs the game
*/

/*~Jurting
Defines:

Compiles with platform settings, example: -DTARpc to compile with PC settings
TARdingoo, TARcaanoo
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include <SDL/SDL.h>

#include "console.h"
#include "input.h"
#include "XSDL.h"
#include "global.h"
#include "game.h"


const std::string VERSION="0.0.0-PREALPHA";


#include "console.cpp"
#include "input.cpp"
#include "XSDL.cpp"
#include "game.cpp"

int main(int argc, char *argv[]) //~Jurting
{
	console.init_log();
	console.log_level(5);
	console.print_logs(1);
	console.log("Game started",1);
	console.log(VERSION,1);
	console.log_b_clear(); console.log_b_add("Compile date: ",1); console.log_b_add(__DATE__,1); console.log_b_send(1);
	
	srand(std::time(NULL));
	
	console.parse_file("scripts/autorun");
	
	XSDL_RefreshScreen();
	
	if (glob_error)
	{
		console.log("Error detected during init. Shutting down",1);
		return 0;
	}
	
	/*SDL_Surface *temp_sur=XSDL_LoadImg("./gfx/goal.bmp");
	
	for (int i=0; i<32; i++)
	{
		draw_loading_screen(i,32,"Just testing");
		SDL_Delay(64+rand()%256);
	}
	
	while(!quit)
	{
		if (glob_reload_surfaces) glob_reload_surfaces=0;
		
		console.update();
		
		update_input();
		if (players[0].input.get(FUNC_RIGHT,STATE_HOLD)) players[0].x+=3;
		if (players[0].input.get(FUNC_LEFT ,STATE_HOLD)) players[0].x-=3;
		if (players[0].input.get(FUNC_DOWN ,STATE_HOLD)) players[0].y+=3;
		if (players[0].input.get(FUNC_UP   ,STATE_HOLD)) players[0].y-=3;
		
		if (glob_reload_surfaces) temp_sur=XSDL_ReloadSurface(temp_sur);
		XSDL_ApplySurface(players[0].x,players[0].y,temp_sur,screen);
		
		SDL_Flip(screen);
		SDL_FillRect(screen,&screenrect,col_background);
		SDL_Delay(16);
	}*/
	
	
	while(!quit) switch(game_menu())
	{
		case 0:
			break;
		break; //Idk
		
		case 1:
			game_game(".maps/dummyfile.umd");
		break;
	}
	
	
	if (rand()%128==0 && !glob_error) console.log("Why are you reading the logs?",1);
	console.log("Game closing",1);
	console.clear();
	return 1;
}
