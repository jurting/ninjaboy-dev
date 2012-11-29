class cXSDL_surface //~Jurting
{
	public:
	SDL_Surface *sur;
	std::string filename;
};
std::vector <cXSDL_surface> vXSDL_surface_list;

SDL_Surface* XSDL_LoadImg(std::string Afilename);//Loads an bitmap image and returns a surface pointer to it
SDL_Surface* XSDL_ReloadSurface(SDL_Surface *surface); //Reloads an image. The surface list remembers the filename
void XSDL_FreeSurface(SDL_Surface *surface); //Use this instead of SDL_FreeSurface() to remove them from the list.
void XSDL_ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* dest, SDL_Rect *clip=NULL);

bool XSDL_RefreshScreen(); //Refreshes the screen settings. Returns 0 on error.


std::string fXSDL_get_scaled_name(std::string Afilename, int value); //Used by LoadImg
