int game_menu() //~Jurting
{
	return 1;
}

int game_game(std::string mapfile) //~Jurting
{
	console.log("location: game_game(); in game.cpp",3);
	
	for (int i=0; i<players.size(); i++)
	{
		players[i].init();
		players[i].move_direct(32,32);
	}
	
	while(!quit)
	{
		if (glob_reload_surfaces) glob_reload_surfaces=0;
		
		console.update();
		update_input();
		
		for (int i=0; i<players.size(); i++)
			players[i].step();
		
		
		for (int i=0; i<players.size(); i++)
			players[i].draw();
		
		SDL_Flip(screen);
		SDL_FillRect(screen,&screenrect,col_background);
		SDL_Delay(16);
	}
}

void draw_loading_screen(double current, double top, std::string text)
{
	SDL_Rect rect_back;
	SDL_Rect rect_bar[2];
	Uint32 col_bar[2];
	Uint32 col_back=SDL_MapRGB(screen->format,0,0,64);
	
	col_bar[0]=SDL_MapRGB(screen->format,255,128,0);
	col_bar[1]=SDL_MapRGB(screen->format,255,255,255);
	
	rect_back.x=16;
	rect_back.w=screenrect.w-32;
	rect_back.y=screenrect.h/2-16;
	rect_back.h=48;
	
	rect_bar[0].x=32;
	rect_bar[0].w=(current/top)*(screenrect.w-64);
	rect_bar[0].y=screenrect.h/2-8;
	rect_bar[0].h=16;
	
	rect_bar[1].x=32+(current/top)*(screenrect.w-64)+1;
	rect_bar[1].w=screenrect.w-32-rect_bar[1].x;
	rect_bar[1].y=screenrect.h/2-8;
	rect_bar[1].h=16;
	
	SDL_FillRect(screen,&rect_back,col_back);
	SDL_FillRect(screen,&rect_bar[0],col_bar[0]);
	SDL_FillRect(screen,&rect_bar[1],col_bar[1]);
	
	SDL_Flip(screen);
}
