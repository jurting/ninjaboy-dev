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

#include "console.h"
#include "global.h"


#include "console.cpp"

int main(int argc, char *argv[]) //~Jurting
{
	console.init_log();
	console.log_level(2);
	console.print_logs(1);
	
	console.log("Game started",1);
	console.log_b_clear();
	console.log_b_add("Compile date: ",1);
	console.log_b_add(__DATE__,1);
	console.log_b_send(1);
	
	
	
	console.log("Game closing",1);
	console.clear();
	return 1;
}
