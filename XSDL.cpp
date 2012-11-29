bool XSDL_RefreshScreen() //~Jurting
{
	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
	
	if (scale!=scale_req) {scale=scale_req; glob_reload_surfaces=1;}
	
	screenrect.w=320*scale;
	screenrect.h=240*scale;

	screen=SDL_SetVideoMode(screenrect.w,screenrect.h,glob_screen_bit,SDL_SWSURFACE|SDL_RESIZABLE);
	col_alpha=SDL_MapRGB(screen->format,255,0,255); //The color that will be used for alpha
	col_background=SDL_MapRGB(screen->format,32,32,32); //The background color
	
	return 1;
}

SDL_Surface* XSDL_LoadImg(std::string Afilename) //~Jurting
{
	SDL_Surface* loadimg;
	SDL_Surface* optimg;
	
	bool loaded=0;
	if (scale>1 && glob_use_hd)
	{
		std::string tempstr=fXSDL_get_scaled_name(Afilename,scale);
		loadimg=SDL_LoadBMP(tempstr.c_str());
		if (loadimg!=NULL) loaded=1;
	}

	if (!loaded) loadimg=SDL_LoadBMP(Afilename.c_str());
	if (loadimg==NULL)
	{
		std::string tempstr;
		tempstr+="Image '";
		tempstr+=Afilename;
		tempstr+="' not found.";
		console.log(tempstr,1);
		glob_error=1;
		return NULL;
	}
	optimg=SDL_DisplayFormat(loadimg);
	SDL_FreeSurface(loadimg);

	SDL_SetColorKey(optimg,SDL_SRCCOLORKEY,col_alpha);
	
	cXSDL_surface tempsur;
	tempsur.sur=optimg;
	tempsur.filename=Afilename;
	vXSDL_surface_list.push_back(tempsur);
	
	return optimg;
}

SDL_Surface* XSDL_ReloadSurface(SDL_Surface *surface) //~Jurting
{
	for (int i=0; i<vXSDL_surface_list.size(); i++)
	{
		if (vXSDL_surface_list[i].sur==surface)
		{
			std::string filename=vXSDL_surface_list[i].filename;
			XSDL_FreeSurface(surface);
			return XSDL_LoadImg(filename);
		}
	}
}

void XSDL_FreeSurface(SDL_Surface *surface) //~Jurting
{
	for (int i=0; i<vXSDL_surface_list.size(); i++)
	{
		if (surface==vXSDL_surface_list[i].sur)
		{
			vXSDL_surface_list.erase(vXSDL_surface_list.begin()+i);
			break;
		}
	}
	SDL_FreeSurface(surface);
}

void XSDL_ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect *clip) //~Jurting
{
	SDL_Rect offset;
	offset.x=x*scale;
	offset.y=y*scale;
	SDL_BlitSurface(source,clip,dest,&offset);
}



std::string fXSDL_get_scaled_name(std::string Afilename, int value)
{
	std::string return_string;
	int dot_pos=-1;
	for (int i=0; i<Afilename.size(); i++)
	{
		if (Afilename[i]=='.') dot_pos=i;
	}
	if (dot_pos==-1) return Afilename;
	for (int i=0; i<dot_pos; i++)
		return_string+=Afilename[i];
	
	return_string+="_x";
	return_string+=value+48;
	for (int i=dot_pos; i<Afilename.size(); i++)
		return_string+=Afilename[i];
	
	return return_string;
}
