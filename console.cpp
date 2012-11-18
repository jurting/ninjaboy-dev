void cConsole::log_b_clear()
{
	log_buffer.clear();
}

void cConsole::log_b_add(std::string str, int logl)
{
	if (logl<=Vlog_level)
	{
		log_buffer+=str;
	}
}

void cConsole::log_b_send(int logl)
{
	if (log_buffer.size()>0 && logl<=Vlog_level) log(log_buffer,logl);
}

bool cConsole::log(std::string str, int logl)
{
	if (logl<=Vlog_level)
	{
		log_file << str << std::endl;
		if (Vprint_log>=1) std::cout << str << std::endl;
		//if (Vprint_log>=2) print(str);
	}
}

//bool cConsole::parse(std::string str, bool show=1); // Parses a string, prints it in console unless show=0.

//bool cConsole::print(std::string str); //Prints text in the console.

//bool cConsole::parse_file(std::string); //Parses a whole file


void cConsole::init_log()
{
	log_file.open("ninjaboy.log",std::ios_base::app);
}

void cConsole::print_logs(unsigned char value)
{
	Vprint_log=value;
}

void cConsole::log_level(unsigned char value)
{
	Vlog_level=value;
}

void cConsole::clear()
{
	log_file.close();
}
