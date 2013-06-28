#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "ConfigFileExtractor.h"

using namespace std;


ConfigFileExtractor::ConfigFileExtractor()
	: m_paraNum(0) 
{
	m_params.clear();
}


ConfigFileExtractor::~ConfigFileExtractor()
{
}


void ConfigFileExtractor::DumpParameters(void)
{
	map<std::string, std::string>::iterator i;	

	for(i = m_params.begin() ; i != m_params.end() ; i++)
	{
		cout << "Key=" << (*i).first << "	" << "Value=" << (*i).second;

		cout << endl;
	}

	return;
}


void ConfigFileExtractor::Clear(void)
{
	m_params.clear();
	m_paraNum = 0;

	return;
}


std::string & ConfigFileExtractor::TrimSpaces(std::string &s)
{
	if (s.empty()) 
	{
		return s;
	}

	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}


std::string &ConfigFileExtractor::TrimComments(std::string &s, const char commToken)
{
	if (s.empty())
	{
		return s;
	}

	int pos = s.find_first_of(commToken);

	if( pos != s.npos )
	{
		s.erase(pos);
	}

	return s;
}


int ConfigFileExtractor::StringToInt(const std::string value)
{
	if(value == "")
	{
		return 0;
	}

	int result;
	istringstream iss(value);
	
	iss >> result;

	return result;
}


double ConfigFileExtractor::StringToDouble(const std::string value)
{
	if(value == "")
	{
		return 0.0;
	}

	double result;
	istringstream iss(value);
	
	iss >> result;

	return result;
}


bool ConfigFileExtractor::StringToBool(std::string value)
{
	if(value == "")
	{
		return false;
	}

	bool result;

	transform(value.begin(), value.end(), value.begin(), ::tolower);

	if( value == "0" || value == "false")
	{
		result = false;
	}
	else if( value == "1" || value == "true")
	{
		result = true;
	}

	return result;
}



int ConfigFileExtractor::StoreParameter(const std::string key, const std::string value)
{
	if( key == "" || value == "")
	{
		cerr << "ExtractParameter() error: parameter error!" << endl;
		return -1;
	}

	/** Store the Parameter in m_params  */

	if( m_params.insert(make_pair(key, value)).second == false )
	{
		/** If the parameter is already in m_params, update the value and give out a warning  */
		cerr << "ConfigFileExtractor::StoreParameter() warning: update value, key=" << key << " value=" << m_params[key] << " NewValue=" << value << endl;
		m_params[key] = value;
	}

	return 0;
}


int ConfigFileExtractor::PhaseLine(std::string line, const char delim)
{
	if( line == "" | delim == 0)
	{
		cerr << "PhaseLine() error: parameter error!" << endl;
		return -1;
	}

	/** Split the line into key and value using the delimiter  */
	string key;
	string value;

	int pos;

	pos = line.find(delim);
	if(pos == string::npos ||
	   pos == (line.length() - 1) ||
	   pos == 0)
	{
		return -1;
	}
	else
	{
		string strTem;
		strTem = line.substr(0, pos);
		key = TrimSpaces(strTem);

		strTem = line.substr(pos + 1);		
		value = TrimSpaces(strTem);
	}

	/** Store the parameter. Ignore unknown keywords, and gite warnings. If there are any syntax error, stop.*/

	if(0 != StoreParameter(key, value))
	{
		return -2;
	}
	
	return 0;
}



int ConfigFileExtractor::ExtractFile(const string filePath, const char delim, const char commToken)
{
	if( filePath == "" | delim == 0 | commToken == 0 )
	{
		cerr << "ExtractFile() error: parameter error!" << endl;
		return -1;
	}

	/** Open config file  */	
	ifstream infile;

	infile.open(filePath.c_str());
	if(!infile)
	{
		cerr << "ExtractFile() error: can not open file: " << filePath << endl;
		return -2;
	}
	
	/** Read every line in the file, trim heading and tail spaces, trim comments and extract parameters  */
	string line;
	while( infile )
	{
		getline(infile, line);
		TrimSpaces(line);
		TrimComments(line, commToken);
		transform(line.begin(), line.end(), line.begin(), ::tolower);

		if( line == "")
		{
			continue;
		}
		else
		{
			/** Extract Parameters. If there are any syntax errors, stop  */
			if( 0 != PhaseLine(line, delim))
			{
				cout << "ExtractFile() error: syntax error: " << line << endl;
				return -3;
			}
		}
	}

	return 0;
}



void * ConfigFileExtractor::GetValue(const std::string key)
{
	if ( key == "")
	{
		cout << "ConfigFileExtractor::GetValue() error: parameter error!" << endl;
		return NULL;
	}

	/** Get the value of the key */
	map< std::string, std::string>::iterator MapIndex;
	MapIndex = m_params.find(key);

	if ( MapIndex == m_params.end() )
	{
		cerr << "GetValue() warning: keyword not found: " << key << endl;
		return NULL;
	}

	return (void *)&m_params[key];
}


string ConfigFileExtractor::KeytypeToString(const enum KeywordType type)
{
	string result;

	switch(type)
	{
		case KEY_TYPE_STRING:
			{
				result = "KEY_TYPE_STRING";
				break;
			}
		case KEY_TYPE_INT:
			{
				result = "KEY_TYPE_INT";
				break;
			}
		case KEY_TYPE_DOUBLE:
			{
				result = "KEY_TYPE_DOUBLE";
				break;
			}
		case KEY_TYPE_BOOL:
			{
				result = "KEY_TYPE_BOOL";
				break;
			}
		default:
			{
				cerr << "KeytypeToString() error: unknown type!" << endl;
				result = "";
				break;
			}	

	}

	return result;
}


int ConfigFileExtractor::GetValueInt(std::string key)
{
	if( key == "" )
	{
		cerr << "ConfigFileExtractor::GetValue() error: keyword is empty!" << endl;
		return 0;
	}

	transform(key.begin(), key.end(), key.begin(), ::tolower);

	void * tmp;

	tmp = GetValue(key);
	if( NULL == tmp)
	{
		return 0;
	}

	int result;
	stringstream ssTem( *(string*)tmp );
	ssTem >> result;
	
	return result;
}


double ConfigFileExtractor::GetValueDouble(std::string key)
{
	if( key == "" )
	{
		cerr << "ConfigFileExtractor::GetValue() error: keyword is empty!" << endl;
		return 0.0;
	}

	transform(key.begin(), key.end(), key.begin(), ::tolower);

	void * tmp;
	
	tmp = GetValue(key);
	if( NULL == tmp)
	{
		return 0.0;
	}
	
	double result;
	stringstream ssTem( *(string*)tmp );
	ssTem >> result;

	return result;
}


string ConfigFileExtractor::GetValueString(std::string key)
{
	if( key == "" )
	{
		cerr << "ConfigFileExtractor::GetValue() error: keyword is empty!" << endl;
		return "";
	}

	transform(key.begin(), key.end(), key.begin(), ::tolower);

	void * tmp;

	tmp = GetValue(key);
	if( NULL == tmp)
	{
		return "";
	}
	
	return *(string*)tmp;
}


bool ConfigFileExtractor::GetValueBool(std::string key)
{
	if( key == "" )
	{
		cerr << "ConfigFileExtractor::GetValue() error: keyword is empty!" << endl;
		return false;
	}

	transform(key.begin(), key.end(), key.begin(), ::tolower);

	void * tmp;
	
	tmp = GetValue(key);
	if( NULL == tmp)
	{
		return false;
	}
	
	string result;
	result = *(string*)tmp;

	transform(result.begin(), result.end(), result.begin(), ::tolower);

	if( result == "1" || result == "true" )
	{
		return true;
	}
	else if( result == "0" || result == "false" )
	{
		return false;
	}
	else
	{
		cerr << "ConfigFileExtractor::GetValueBool() error: invalid value: " << result << endl;
		return false;	
	}

	return false;
}


