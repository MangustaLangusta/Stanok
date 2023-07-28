#ifndef GCODES_CONF_H
#define GCODES_CONF_H


#include "parser.h"

namespace gcode{
	
enum COMMANDS {
	COMMAND_NONE,
	//
	COMMAND_G00,
	COMMAND_G01,
	COMMAND_G03,
	COMMAND_G17,
	COMMAND_G21,
	COMMAND_G28,
	COMMAND_G40,
	COMMAND_G41,
	COMMAND_G42,
	COMMAND_G43,
	COMMAND_G54,
	COMMAND_G80,
	COMMAND_G82,
	COMMAND_G90,
	COMMAND_G91,
	COMMAND_G98,
	//
	COMMAND_M03,
	COMMAND_M06,
	COMMAND_M08,
	COMMAND_M09,
	COMMAND_M30
};

enum PARAMS {
	PARAM_D,
	PARAM_F,
	PARAM_H,
	PARAM_I,
	PARAM_J,
	PARAM_R,
	PARAM_S,
	PARAM_T,
	PARAM_X,
	PARAM_Y,
	PARAM_Z
};


const std::map<std::string, PARAMS> PARAMS_MAP {
	{"D", PARAM_D},
	{"F", PARAM_F},
	{"H", PARAM_H},
	{"I", PARAM_I},
	{"J", PARAM_J},
	{"R", PARAM_R},
	{"S", PARAM_S},
	{"T", PARAM_T},
	{"X", PARAM_X},
	{"Y", PARAM_Y},
	{"Z", PARAM_Z}
};

const std::map<std::string, COMMANDS> COMMANDS_MAP {
	{"G0", COMMAND_G00},
	{"G00", COMMAND_G00},
	{"G1", COMMAND_G01},
	{"G01", COMMAND_G01},
	{"G3", COMMAND_G03},
	{"G03", COMMAND_G03},
	{"G17", COMMAND_G17},
	{"G21", COMMAND_G21},
	{"G28", COMMAND_G28},
	{"G40", COMMAND_G40},
	{"G41", COMMAND_G41},
	{"G42", COMMAND_G42},
	{"G43", COMMAND_G43},
	{"G54", COMMAND_G54},
	{"G80", COMMAND_G80},
	{"G82", COMMAND_G82},
	{"G90", COMMAND_G90},
	{"G91", COMMAND_G91},
	{"G98", COMMAND_G98},
	{"M3", COMMAND_M03},
	{"M03", COMMAND_M03},
	{"M6", COMMAND_M06},
	{"M06", COMMAND_M06},
	{"M8", COMMAND_M08},
	{"M08", COMMAND_M08},
	{"M9", COMMAND_M09},
	{"M09", COMMAND_M09},
	{"M30", COMMAND_M30}
};

	
const std::map<COMMANDS, std::set<PARAMS>> APPROPRIATE_PARAMS_MAP {
	{ COMMAND_G00, {PARAM_X, PARAM_Y, PARAM_Z, PARAM_F} },
	{ COMMAND_G01, {PARAM_X, PARAM_Y, PARAM_Z, PARAM_F} },
	{ COMMAND_G03, {PARAM_I, PARAM_J} },
	{ COMMAND_G17, {} },	
	{ COMMAND_G21, {} },
	{ COMMAND_G28, {PARAM_X, PARAM_Y, PARAM_Z} }, 
	{ COMMAND_G40, {} },	//disable cutter compensation
	{ COMMAND_G41, {PARAM_D} },	//enable left-compensation
	{ COMMAND_G42, {PARAM_D} },	//enable right-compensation
	{ COMMAND_G43, {PARAM_H, PARAM_Z} },	//tool height compensation - ignore
	{ COMMAND_G54, {} },	//change coordinate system - ignore
	{ COMMAND_G80, {} },	//cancel drilling cycle - ignore
	{ COMMAND_G82, {PARAM_X, PARAM_Y, PARAM_Z, PARAM_R, PARAM_F} },	//drilling with delay - ignore
	{ COMMAND_G90, {} },	//absolute positioning
	{ COMMAND_G91, {} },	//relative positioning
	{ COMMAND_G98, {PARAM_Z} }, //set retract of drill - ignore
	//
	{ COMMAND_M03, {PARAM_S} },	//start spindle clockwise - ignore
	{ COMMAND_M06, {PARAM_T} },	//change tool
	{ COMMAND_M08, {} }, //start coolant - ignore
	{ COMMAND_M09, {} },	//stop coolant - ignore
	{ COMMAND_M30, {}	}		//end of program
};

	//If one of these symbols found, whole line to be ignored
const std::set<std::string> WRONG_LINE_SYMBOLS {
	"(",
	")",
	"&"	
};

struct GCodeParameter{
	PARAMS descriptor;
	std::string value;
};

struct GCodeCommand{
	COMMANDS command;
	COMMANDS last_command;
	std::list<GCodeParameter> parameters;
	
	GCodeCommand();
	void clear();
	std::string ProperFormatLine();
	bool IsSingleCommand();
};
 

class GCodeParser{
	private:
		std::ifstream fin;
		std::string input_file_name;
		
		//utility
		COMMANDS last_command;
		
		bool IsLineValid(const std::string &source);
		std::string AdoptLine(std::string source);
	public:
		bool AssignInputFile();
		bool AdoptGcode();
		void PrintAllCodes();	//Prints all occuring codes and params letters
		void ReleaseInputFile();
};

GCodeCommand::GCodeCommand(){
	command = COMMAND_NONE;
	last_command = COMMAND_NONE;
	parameters = {};	
}

void GCodeCommand::clear(){
	command = COMMAND_NONE;
	parameters = {};
}

//makes proper line for each command with appropriate parameters
std::string GCodeCommand::ProperFormatLine(){
	if(command == COMMAND_NONE)
		return "";
	
	std::string result =  "";
	
	switch (command){
		case COMMAND_G00:
			result += "G0 ";
			for(auto it_params : parameters)
				result += it_params.value + " ";
			break;
		case COMMAND_G01:
			result += "G1 ";
			for(auto it_params : parameters)
				result += it_params.value + " ";
			break;
		case COMMAND_G03:
			result += "G3 ";
			for(auto it_params : parameters)
				result += it_params.value + " ";
			break;
		case COMMAND_G17:	//ignore
			break;
		case COMMAND_G21:
			result += "G21";
			break;
		case COMMAND_G28:
			result += "G28 ";
			for(auto it_params : parameters)
				result += it_params.value + " ";
			break;
		case COMMAND_G40:	//ignore
			break;
		case COMMAND_G41:	//ignore
			break;
		case COMMAND_G42:	//ignore
			break;
		case COMMAND_G43:	//ignore
			break;
		case COMMAND_G54:	//ignore
			break;
		case COMMAND_G80:	//ignore
			break;
		case COMMAND_G82:	//ignore
			break;
		case COMMAND_G90:
			result += "G90";
			break;
		case COMMAND_G91:
			result += "G91";
			break;
		case COMMAND_G98:	//ignore
			break;
		//
		case COMMAND_M03:	//ignore
			break;
		case COMMAND_M06: //ignore
			break;
		case COMMAND_M08:	//ignore
			break;
		case COMMAND_M09:	//ignore
			break;
		case COMMAND_M30:
			std::cout<<"M30 DETECTED"<<std::endl;
			result += "M30";
			break;
		default:
			;
	}
	if(result.length() > 0)
		result += "\n";
	return result;
}

bool GCodeCommand::IsSingleCommand(){
	auto it_appropriate_params = APPROPRIATE_PARAMS_MAP.find(command);
	if(it_appropriate_params == APPROPRIATE_PARAMS_MAP.end())
		return false;
	if(it_appropriate_params->second.empty())
		return true;
	return false;
}

bool GCodeParser::IsLineValid(const std::string &source){
	if(source.empty())
		return false;
	for(auto it : WRONG_LINE_SYMBOLS){
		if(source.find(it) != std::string::npos)
			return false;
	}
	return true;
}

	//raw source line as input, adopted line(s) as output
	//output can be zero line ( "" )
std::string GCodeParser::AdoptLine(std::string source){

	//std::cout<<"Started adopting line "<<source<<std::endl;
		//if line contains wrong symbols or empty, ignore it
	if(!IsLineValid(source))
		return "";
	
	//parser::RemoveSymbols(&source, "\n");
	//std::cout<<"Started adopting line "<<source<<std::endl;
	parser::ParametersList line_elements;

	if(!parser::ParseLine(source, &line_elements))
		return "";
	
	//std::cout<<"Line parsed"<<std::endl;

		//line_parameters now contains splitted line (i.e. { "N20", "G03", "X38.58", ... })
	std::string result = "";
	GCodeCommand next_command;
	next_command.last_command = last_command;
	for(auto it_elem : line_elements){
		std::cout<<"elem = "<<it_elem<<std::endl;
		//if next element is a command
		auto command_it = COMMANDS_MAP.find(it_elem);
		if(command_it != COMMANDS_MAP.end()){
			//std::cout<<"command = "<<it_elem<<std::endl;
			//if next_command already have any command, put it to result
			//and clear next_command for next line
			if(next_command.command != COMMAND_NONE){
				result += next_command.ProperFormatLine();
				next_command.clear();
			}
			//any case, next command to be added to next_command struct
			next_command.command = command_it->second;
			//check if this command is no-params command
			if(next_command.IsSingleCommand()){
				result += next_command.ProperFormatLine();
				next_command.clear();
			}
			//go to next element in input sequence
			continue;	
		}
		//if element is not a command, it maybe a parameter. 
		//check first symbol to determine
		std::string param_descriptor = it_elem.substr(0,1);
		//std::cout<<"param. descriptor = "<<param_descriptor<<std::endl;
		auto param_it = PARAMS_MAP.find(param_descriptor);
		//if such descriptor is not found, ignore
		if(param_it == PARAMS_MAP.end())
			continue;
		//if descriptor is valid, create parameter 
		//std::cout<<"descriptor is valid"<<std::endl;
		GCodeParameter new_param;
		new_param.descriptor = param_it->second;
		new_param.value = it_elem;
		//place new_parameter to new_command
		next_command.parameters.push_back(new_param);
	}
	//if new_command have only parameters, apply last command from previous line
	if(next_command.command == COMMAND_NONE){
		if(next_command.parameters.empty())
			return result;
		next_command.command = last_command;
	}
	result += next_command.ProperFormatLine();
	last_command = next_command.command;
	return result;
}

bool GCodeParser::AssignInputFile(){
	fin.close();
	
	std::cout<<"Enter input file name"<<std::endl;
	std::cin>>input_file_name;
	
	fin.open(input_file_name);
	
	if(fin.good()){
		std::cout<<"Input file "<<input_file_name<<" successfully opened"<<std::endl;
		return true;
	}
	else {
		std::cout<<"Cannot open file "<<input_file_name<<std::endl;
		return false;
	}
}

void GCodeParser::PrintAllCodes(){
	std::set<std::string> codes_G;
	std::set<std::string> params;
	std::set<std::string> codes_M;
	
	while(!fin.eof()){
		std::string this_item = "";
		fin>>this_item;
		if(this_item.empty())
			continue;
		switch(this_item[0]){
			case 'G':
				codes_G.insert(this_item);
				break;
			case 'M':
				codes_M.insert(this_item);
				break;
			default:
				params.insert(this_item.substr(0,1));
		}
	}
	
	std::cout<<"All codes G:"<<std::endl;
	for(auto it : codes_G)
		std::cout<<it<<std::endl;
	std::cout<<std::endl;
	std::cout<<"All codes M:"<<std::endl;
	for(auto it : codes_M)
		std::cout<<it<<std::endl;
	std::cout<<std::endl;
	std::cout<<"All params and unknown:"<<std::endl;
	for(auto it : params)
		std::cout<<it<<std::endl;
	std::cout<<std::endl;
}

bool GCodeParser::AdoptGcode(){
	//reopen file to read it from beginning
	//fin.open(input_file_name);
	
	std::ofstream output_file;
	output_file.open("out.txt");

	std::cout<<"Start Adopting GCode"<<std::endl;

	while(!fin.eof()){
		std::string new_line = "";
		std::getline(fin, new_line);
		output_file<<"	"<<new_line<<std::endl;
		std::string result_line = "";
		result_line = AdoptLine(new_line);
		output_file<<result_line;
	}
	
	std::cout<<"finish!"<<std::endl;

	output_file.close();
	return true;
}

void GCodeParser::ReleaseInputFile(){
	fin.close();
	std::cout<<"File "<<input_file_name<<" have been closed"<<std::endl;
}

}	//namespace gcode

#endif //GCODES_CONF_H
