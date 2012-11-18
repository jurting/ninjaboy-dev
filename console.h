class cConsole //~Jurting
{
	private:
	unsigned char Vprint_log;
	unsigned char Vlog_level;
	std::ofstream log_file;
	std::string log_buffer;
	public:
	std::string command;
	
	
	void log_b_clear();
	
	void log_b_add(std::string str, int logl);
	
	void log_b_send(int logl);
	
	
	bool log(std::string str, int logl); //Sends a log if the log level is high enough.
	bool parse(std::string str, bool show=1); // Parses a string, prints it in console unless show=0.
	bool print(std::string str); //Prints text in the console.
	bool parse_file(std::string); //Parses a whole file
	
	void init_log(); //Loads/creates the log file
	void print_logs(unsigned char value); //If the console should print the logs
	void log_level(unsigned char value); //The log level, 0-5
	
	void clear();
};
