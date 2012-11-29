int cConsole::parse_num(std::string str)
{
	int count=0;
	bool docount=1;
	for (int i=0; i<str.size(); i++)
	{
		if (str[i]==' ')
		{
			if (docount)
			{
				count++;
				docount=0;
			}
		}
		else
			docount=1;
	}
	if (docount && str.size()>0) count++;
	return count;
}

std::string cConsole::parse_get_str(std::string str, int num)
{
	int count=0;
	bool docount=1;
	int pos=0;
	for (int i=0; i<str.size(); i++)
	{
		if (str[i]==' ' || num==0)
		{
			if (docount)
			{
				count++;
				docount=0;
			}
		}
		else
		{
			if (count==num) {pos=i; break;}
			docount=1;
		}
	}
	if (pos==0 && num!=0) return "";
	std::string tempstr;
	for (int i=pos; i<str.size(); i++)
	{
		if (str[i]==' ') break;
		tempstr+=str[i];
	}
	return tempstr;
}

double cConsole::parse_get_double(std::string str, int num)
{
	int count=0;
	bool docount=1;
	int pos=0;
	for (int i=0; i<str.size(); i++)
	{
		if (str[i]==' ' || num==0)
		{
			if (docount)
			{
				count++;
				docount=0;
			}
		}
		else
		{
			if (count==num) {pos=i; break;}
			docount=1;
		}
	}
	if (pos==0 && num!=0) return 0;
	std::string tempstr;
	for (int i=pos; i<str.size(); i++)
	{
		if (str[i]==' ') break;
		tempstr+=str[i];
	}
	return atof(tempstr.c_str());
}

std::string cConsole::parse_clean(std::string str, int *next)
{
	std::string tempstr;
	int count=1;
	for (int i=0; i<str.size(); i++)
	{
		//Maybe replace this with an switch statement ~Jurting
		if (str[i]==' ')
		{
			count++;
		}
		else if (str[i]=='#')
		{
			*next=0;
			return tempstr;
		}
		else if (str[i]==';')
		{
			*next=count;
			return tempstr;
		}
		tempstr+=str[i];
	}
	*next=0;
	return str;
}

std::string cConsole::parse_get_after(std::string str, int num)
{
	int count=0;
	bool docount=1;
	int pos=0;
	for (int i=0; i<str.size(); i++)
	{
		if (str[i]==' ' || num==0)
		{
			if (docount)
			{
				count++;
				docount=0;
			}
		}
		else
		{
			if (count==num) {pos=i; break;}
			docount=1;
		}
	}
	if (pos==0 && num!=0) return "";
	std::string tempstr;
	for (int i=pos; i<str.size(); i++)
		tempstr+=str[i];
	return tempstr;
}



void cConsole::update()
{
	for (int i=0; i<waitcom.size(); i++) if (SDL_GetTicks()>=waitcom[i].time_start+waitcom[i].timer)
	{
		parse(waitcom[i].command);
		if (!waitcom[i].loop)
		{
			waitcom.erase(waitcom.begin()+i);
			i--;
		}
	}
}

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

bool cConsole::log(std::string str, int logl, bool show)
{
	if (logl<=Vlog_level)
	{
		log_file << str << std::endl;
		if (Vprint_log>=2 && show) print(str);
		else if (Vprint_log>=1 && show) std::cout << str << std::endl;
	}
}

//bool cConsole::parse(std::string str, bool show=1); // Parses a string, prints it in console unless show=0.

//bool cConsole::print(std::string str); //Prints text in the console.

//bool cConsole::parse_file(std::string); //Parses a whole file


void cConsole::init_log()
{
	log_file.open("ninjaboy.log",std::ios_base::out | std::ios_base::trunc);
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



bool cConsole::parse(std::string str, bool show)
{
	if (str.size()<=0) return 0;
	std::string orig_str=str;
	int next_command=0;
	str=parse_clean(str,&next_command);
	
	int temp_int[4];
	
	int words=parse_num(str);
	if (words==0) return 0;
	std::string com_str;
	com_str=parse_get_str(str,0);
	
	
	
	if (com_str=="move")
	{
		if (words==3)
		{
			if (show) print(str);
			players[0].move_direct(parse_get_double(str,1),parse_get_double(str,2));
		}
		else print("Arguments: <x> <y>");
	}
	else if (com_str=="move_player")
	{
		if (words==4)
		{
			if (show) print(str);
			temp_int[0]=parse_get_double(str,1);
			if (players.size()>temp_int[0])
			{
				players[temp_int[0]].move_direct(parse_get_double(str,2),parse_get_double(str,3));
			}
			else print("Player not found");
		}
		else print("Arguments: <player> <x> <y>");
	}
	
	
	else if (com_str=="setinput")
	{
		if (words==5)
		{
			if (show) print(str);
			temp_int[0]=parse_get_double(str,1);
			temp_int[1]=parse_get_double(str,2);
			temp_int[2]=parse_get_double(str,3);
			temp_int[3]=parse_get_double(str,4);
			players[temp_int[0]].input.add(temp_int[1],temp_int[2],temp_int[3]);
		}
		else print("Arguments: <Player> <Type 0-3> <Value> <Function> (Note: see ./scripts/commands file)");
	}
	else if (com_str=="echo")
	{
		if (words>1)
		{
			std::string temp_str;
			temp_str+='"';
			temp_str+=parse_get_after(str,1);
			temp_str+='"';
			print(temp_str);
			log(temp_str,1,0);
		}
		else print("Nothing to echo");
	}
	else if (com_str=="wait")
	{
		if (words>1)
		{
			cCommand tempcom;
			tempcom.time_start=SDL_GetTicks();
			tempcom.timer=parse_get_double(str,1);
			tempcom.command=parse_get_after(orig_str,2);
			
			tempcom.loop=0;
			
			waitcom.push_back(tempcom);
			next_command=0;
		}
		else print("Arguments: <time to wait> <command(s)>");
	}
	
	else if (com_str=="set_screen_bit")
	{
		if (words==2)
		{
			if (show) print(str);
			temp_int[0]=parse_get_double(str,1);
			glob_screen_bit=temp_int[0];
		}
		else print("Arguments: <integer>");
	}
	else if (com_str=="set_screen_scale")
	{
		if (words==2)
		{
			if (show) print(str);
			temp_int[0]=parse_get_double(str,1);
			scale_req=temp_int[0];
		}
		else print("Arguments: <integer>");
	}
	else if (com_str=="screen_refresh" || com_str=="screen_reload")
	{
		if (words==1)
		{
			if (show) print(str);
			XSDL_RefreshScreen();
		}
		else print("Command does not have arguments");
	}
	
	else if (com_str=="set_use_hd")
	{
		if (words==2)
		{
			if (show) print(str);
			temp_int[0]=parse_get_double(str,1);
			glob_use_hd=temp_int[0];
		}
		else print("arguments: 0/1");
	}
	
	else if (com_str=="load_file")
	{
		if (words==2)
		{
			if (show) print(str);
			if (!parse_file(parse_get_str(str,1)))
			{
				std::string temp_str;
				temp_str+="Console: File '";
				temp_str+=parse_get_str(str,1);
				temp_str+="' not found.";
				log(temp_str,1);
			}
		}
		else print("Arguments: <filename>");
	}
	else
	{
		std::string tempstr="Command '";
		tempstr+=str;
		tempstr+="' not found.";
		print(tempstr);
	}
	
	
	if (next_command>0)
		parse(parse_get_after(orig_str,next_command),show);
}

void cConsole::print(std::string str)
{
	if (str.size()<=0) return;
	//<-- Send stuffsen to the console here
	if (Vprint_log>=1) std::cout << str << std::endl;
}

bool cConsole::parse_file(std::string filename)
{
	if (filename.size()<=0) return 0;
	std::string tempstr;
	
	std::ifstream file;
	file.open(filename.c_str());
	if (!file.is_open()) return 0;
	while(file)
	{
		std::getline(file,tempstr);
		parse(tempstr,0);
	}
	return 1;
}
