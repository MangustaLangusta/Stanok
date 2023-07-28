#ifndef PARSER_H
#define PARSER_H

namespace parser{
	
std::string delimiter = " ";

typedef std::string descriptor;
typedef std::string parameter;
typedef std::list<parameter> ParametersList;

bool RemoveSymbols(std::string *source, unsigned char symbol_to_remove){
	long symb_pos = source->find(symbol_to_remove);
	bool result_bool = false;
	while(symb_pos != std::string::npos){
		source->replace(symb_pos, 1, "");
		symb_pos = source->find(symbol_to_remove);
		result_bool = true;
	}
	return result_bool;
}

bool ParseLine(std::string input_line, ParametersList *output_list){
	output_list->clear();

	while(!input_line.empty()){
		unsigned long pos = input_line.find(delimiter);
		if(pos == 0){
			input_line.erase(pos, 1);
			continue;
		}
		if(pos == std::string::npos){
			if(RemoveSymbols(&input_line, '\n'))
				std::cout<<"eol symb removed"<<std::endl;
			output_list->push_back("|" + input_line + "|");
			input_line.clear();
			break;
		}
		output_list->push_back("|" + input_line.substr(0, pos) + "|");
		input_line.erase(0, pos + 1);
	}
	
	if(output_list->empty())
		return false;
	return true;
}
	
}	//namespace parser


#endif	//PRSER_H
