double cKeymap::get_data(unsigned char state)
{
	if      (state==STATE_PRESS   && state_press  ) return 1;
	else if (state==STATE_HOLD    && state_hold   ) return state_hold;
	else if (state==STATE_RELEASE && state_release) return 1;
	else return 0;
}

double cInput_profile::get(Uint16 Afunc, unsigned char state)
{
	for (int i=0; i<map.size(); i++)
	{
		if (map[i].func==Afunc)
		{
			double dtemp=map[i].get_data(state);
			if (dtemp) return dtemp;
		}
	}
	return 0;
}

void cInput_profile::update(Uint32 id, unsigned char type, unsigned char state)
{
	switch(type)
	{
		case BUT_T_KEYBOARD:
			for (int i=0; i<map.size(); i++) if (map[i].type==BUT_T_KEYBOARD)
			{
				if (map[i].data==id)
				{
					if (state==STATE_PRESS)
					{
						map[i].state_press=1;
						map[i].state_hold=1;
					}
					else if (state==STATE_RELEASE)
					{
						map[i].state_release=1;
						map[i].state_hold=0;
					}
				}
			}
		break;
	}
}

void cInput_profile::update_state()
{
	for (int i=0; i<map.size(); i++)
	{
		map[i].state_press=0;
		map[i].state_release=0;
	}
}

void cInput_profile::add(unsigned char Atype, Uint16 Adata, unsigned char Afunc)
{
	cKeymap temp_key;
	temp_key.type=Atype;
	temp_key.data=Adata;
	temp_key.func=Afunc;
	temp_key.state_press=0;
	temp_key.state_hold=0;
	temp_key.state_release=0;
	map.push_back(temp_key);
}

void cInput_profile::clear()
{
	map.clear();
}



void cPlayer::init()
{
	sur=NULL;
	
	sur=XSDL_LoadImg("./gfx/goal.bmp");
	if (sur==NULL) console.log("Player image file not found",1);
}

void cPlayer::move_direct(int Ax, int Ay)
{
	x=Ax;
	y=Ay;
}

void cPlayer::update_state()
{
	input.update_state();
}

void cPlayer::step()
{
	if (input.get(FUNC_RIGHT,STATE_HOLD)) x+=3;
	if (input.get(FUNC_LEFT ,STATE_HOLD)) x-=3;
	if (input.get(FUNC_DOWN ,STATE_HOLD)) y+=3;
	if (input.get(FUNC_UP   ,STATE_HOLD)) y-=3;
}

void cPlayer::draw()
{
	XSDL_ApplySurface(x+sur->w/2,y-sur->h,sur,screen);
	//XSDL_ApplySurface(x,y,screen,sur);
}

void cPlayer::clear_surface()
{
	XSDL_FreeSurface(sur);
}


void update_input()
{
	console.log("update_input()",4);
	for (int i=0; i<players.size(); i++)
	{
		players[i].input.update_state();
	}
	
	
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_MOUSEMOTION:
				mouse_x=event.motion.x*scale;
				mouse_y=event.motion.y*scale;
			break;
			
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button-1<3)
				{
					mouse_down [event.button.button-1]=1;
					mouse_press[event.button.button-1]=1;
				}
			break;
			
			case SDL_MOUSEBUTTONUP:
				if (event.button.button-1<3)
				{
					mouse_down   [event.button.button-1]=0;
					mouse_release[event.button.button-1]=1;
				}
			break;
			
			case SDL_KEYDOWN:
				if (event.key.keysym.sym==SDLK_F12)
				{
					std::string tempstr;
					std::cout << "Command: ";
					//std::cin.getline(&tempstr,IDK);
					std::getline(std::cin,tempstr);
					console.parse(tempstr);
				}
				for (int i=0; i<players.size(); i++)
					players[i].input.update(event.key.keysym.sym,BUT_T_KEYBOARD,STATE_PRESS);
			break;
			
			case SDL_KEYUP:
				for (int i=0; i<players.size(); i++)
					players[i].input.update(event.key.keysym.sym,BUT_T_KEYBOARD,STATE_RELEASE);
			break;
			
			case SDL_QUIT:
				quit=1;
			break;
		}
	}
}
