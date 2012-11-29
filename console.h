class cCommand
{
	private:
	public:
	Uint32 time_start;
	Uint32 timer;
	bool loop;
	std::string command;
};

class cConsole //~Jurting
{
	private:
	unsigned char Vprint_log;
	unsigned char Vlog_level;
	std::ofstream log_file;
	std::string log_buffer;
	
	std::vector <cCommand>waitcom;
	
	int parse_num(std::string str);
	std::string parse_get_str(std::string str, int num);
	double parse_get_double(std::string str, int num);
	std::string parse_clean(std::string str, int *next);
	std::string parse_get_after(std::string str, int num);
	public:
	void update();
	
	void log_b_clear();
	void log_b_add(std::string str, int logl);
	void log_b_send(int logl);
	
	bool log(std::string str, int logl, bool show=1); //Sends a log if the log level is high enough.
	
	bool parse(std::string str, bool show=1); // Parses a string, prints it in console unless show=0.
	void print(std::string str); //Prints text in the console.
	bool parse_file(std::string filename); //Parses a whole file
	
	void init_log(); //Loads/creates the log file
	void print_logs(unsigned char value); //If the console should print the logs
	void log_level(unsigned char value); //The log level, 0-5
	
	void clear();
};
