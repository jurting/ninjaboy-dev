//This file contains all global variabels

cConsole console;
std::vector <cPlayer> players(1);


//Input
SDL_Event event;
bool quit=0;
int mouse_x;
int mouse_y;
bool mouse_press[3];
bool mouse_down[3];
bool mouse_release[3];

bool glob_error=0;

SDL_Surface *screen;
SDL_Rect screenrect;
int scale=1;
int scale_req=1;
int glob_screen_bit=32;
bool glob_use_hd=1; //When scaling, load higher defitintion images if possible
bool glob_reload_surfaces=0;

Uint32 col_background;
Uint32 col_alpha;
