#define FUNC_RIGHT 0
#define FUNC_DOWN 1
#define FUNC_LEFT 2
#define FUNC_UP 3
#define FUNC_JUMP 4
#define FUNC_ITEM 5
#define FUNC_SPECIAL 6
#define FUNC_SLOMO 7
#define FUNC_MENU 8

#define BUT_T_KEYBOARD 0
#define BUT_T_JOYBUT 1
#define BUT_T_JOYAXIS_UP 2
#define BUT_T_JOYAXIS_DOWN 3

#define STATE_PRESS 0
#define STATE_HOLD 1
#define STATE_RELEASE 2

class cKeymap //~Jurting
{
	private:
	public:
	unsigned char func;
	unsigned char type;
	Uint32 data;
	bool state_press;
	double state_hold;
	bool state_release;
	
	double get_data(unsigned char state);
};

class cInput_profile //~Jurting
{
	private:
	std::vector <cKeymap> map;
	public:
	double get(Uint16 Afunc, unsigned char state);
	
	void update(Uint32 id, unsigned char type, unsigned char state);
	void update_state();
	
	void add(unsigned char Atype, Uint16 Adata, unsigned char Afunc);
	//void remove(int ID);
	void clear();
};

class cPlayer //~Jurting
{
	private:
	SDL_Surface *sur;
	double x;
	double y;
	public:
	void init(); //Loads the player image
	void move_direct(int Ax, int Ay);
	cInput_profile input;
	
	void update_state();
	
	void step();
	void draw();
	
	void clear_surface();
};
