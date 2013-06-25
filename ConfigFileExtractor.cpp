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
	m_keywords.clear();
	m_intMap.clear();
	m_doubleMap.clear();
	m_stringMap.clear();
	m_boolMap.clear();

	m_intMap.insert(make_pair("default",0));
	m_doubleMap.insert(make_pair("default",0.0));
	m_stringMap.insert(make_pair("default",""));
	m_boolMap.insert(make_pair("default",false));
}


ConfigFileExtractor::~ConfigFileExtractor()
{
}


int ConfigFileExtractor::AddKeyword(Keyword keyword)
{
	/** If the keyword is not empty, try insert the keyword into m_keywords */
	if(keyword.first == "" || keyword.second == KEY_TYPE_ERROR)
	{
		cerr << "AddKeyword() error: Keyword Error!" << endl;
		return -1;
	}
	else
	{
		/** If the keyword is already in m_keywords, update the value and give out a warning  */
		transform(keyword.first.begin(), keyword.first.end(), keyword.first.begin(), ::tolower);

		if(m_keywords.insert(keyword).second == false)
		{
			m_keywords[keyword.first] = keyword.second;
			cerr << "AddKeyword() warning: updated the keyword:"<< keyword.first << endl;
		}
	}
	
	return 0;
}


int ConfigFileExtractor::DelKeyword(std::string key)
{
	if( key == "" )
	{
		cerr << "DelKeyword() error: Key Error!" << endl;
		return -1;
	}
	else
	{
		transform(key.begin(), key.end(), key.begin(), ::tolower);
		if( 0 == m_keywords.erase(key))
		{
			cerr << "DelKeyword() warning: no key deleted!" << endl;
		}
	}

	return 0;
}


enum KeywordType ConfigFileExtractor::GetKeywordType(std::string key)
{
	if( key == "" )
	{
		cerr << "DelKeyword() error: Key Error!" << endl;
		return KEY_TYPE_ERROR;
	}
	else
	{
		transform(key.begin(), key.end(), key.begin(), ::tolower);

		map<std::string, enum KeywordType>::iterator i;

		i = m_keywords.find(key);

		if ( i == m_keywords.end() )
		{
			cerr << "GetKeywordType() error: " << key << " is not in m_keywords!" << endl;
			return KEY_TYPE_ERROR;
		}
		else
		{
			return (*i).second;
		}
	}

}


void ConfigFileExtractor::DumpKeywords(void)
{
	map<std::string, enum KeywordType>::iterator i;	

	for(i = m_keywords.begin() ; i != m_keywords.end() ; i++)
	{
		cout << "Key=" << (*i).first << "	" << "Value=";

		switch((*i).second)
		{
			case KEY_TYPE_STRING:
				{
					cout << "STRING";
					break;
				}
			case KEY_TYPE_DOUBLE:
				{
					cout << "DOUBLE";
					break;
				}
			case KEY_TYPE_INT:
				{
					cout << "INT";
					break;
				}
			case KEY_TYPE_BOOL:
				{
					cout << "BOOL";
					break;
				}
			default:
				{
					cout << endl << "DumpKeywords() error: unknown keyword type!" << endl;
					break;
				}
		}

		cout << endl;
	}

	return;
}


void ConfigFileExtractor::Clear(void)
{
	m_keywords.clear();
	m_intMap.clear();
	m_doubleMap.clear();
	m_stringMap.clear();
	m_boolMap.clear();
	m_paraNum = 0;

	m_intMap.insert(make_pair("default",0));
	m_doubleMap.insert(make_pair("default",0.0));
	m_stringMap.insert(make_pair("default",""));
	m_boolMap.insert(make_pair("default",false));

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

	s.erase(s.find_first_of(commToken));
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



int ConfigFileExtractor::ExtractParameter(const std::string key, const std::string value)
{
	if( key == "" || value == "")
	{
		cerr << "ExtractParameter() error: parameter error!" << endl;
		return -1;
	}

	/** Find out keyword type, translate the value, and inserted into a map according to key type  */	
	map<std::string, enum KeywordType>::iterator i;

	i = m_keywords.find(key);

	/** Ignore, if the key is unknown.  */
	if ( i == m_keywords.end() )
	{
		cerr << "ExtractParameter() warning: unknown keyword: " << key << endl;
		return 0;
	}
	
	/** Translate and insert the key and value */
	switch((*i).second)
	{
		case KEY_TYPE_STRING:
			{
				m_stringMap.insert(make_pair(key, value));
				break;
			}
		case KEY_TYPE_INT:
			{
				m_intMap.insert(make_pair(key, StringToInt(value)));
				break;
			}
		case KEY_TYPE_DOUBLE:
			{
				m_doubleMap.insert(make_pair(key, StringToDouble(value)));
				break;
			}
		case KEY_TYPE_BOOL:
			{
				m_boolMap.insert(make_pair(key, StringToBool(value)));
				break;
			}
		default:
			{
				cerr << "ExtractParameter() error: unknown type in m_keywords!" << endl;
				return -2;
			}
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

	/** Extract the parameter. Ignore unknown keywords, and gite warnings. If there are any syntax error, stop.*/

	if(0 != ExtractParameter(key, value))
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



void * ConfigFileExtractor::GetValue(const std::string key, enum KeywordType type)
{
	/** Get the value of the key, if the key is not configured, a default value will be given.  */
	switch(type)
	{
		case KEY_TYPE_STRING:
			{
				map< std::string, std::string >::iterator MapIndex;
				MapIndex = m_stringMap.find(key);

				if ( MapIndex == m_stringMap.end() )
				{
					cerr << "GetValue() warning: keyword not configured: " << key << endl;
					return (void *)&m_stringMap["default"];
				}
				else
				{
					return (void *)&m_stringMap[key];
				}

				break;
			}

		case KEY_TYPE_DOUBLE:
			{
				map< std::string, double >::iterator MapIndex;
				MapIndex = m_doubleMap.find(key);

				if ( MapIndex == m_doubleMap.end() )
				{
					cerr << "GetValue() warning: keyword not configured: " << key << endl;
					return (void *)&m_doubleMap["default"];
				}
				else
				{
					return (void *)&m_doubleMap[key];
				}

				break;
			}
		case KEY_TYPE_INT:
			{
				map< std::string, int >::iterator MapIndex;
				MapIndex = m_intMap.find(key);

				if ( MapIndex == m_intMap.end() )
				{
					cerr << "GetValue() warning: keyword not configured: " << key << endl;
					return (void *)&m_intMap["default"];
				}
				else
				{
					return (void *)&m_intMap[key];
				}

				break;
			}
		case KEY_TYPE_BOOL:
			{
				map< std::string, bool >::iterator MapIndex;
				MapIndex = m_boolMap.find(key);

				if ( MapIndex == m_boolMap.end() )
				{
					cerr << "GetValue() warning: keyword not configured: " << key << endl;
					return (void *)&m_boolMap["default"];
				}
				else
				{
					return (void *)&m_boolMap[key];
				}

				break;
			}
		default:
			{
				cout << endl << "GetValue() error: unknown keyword type!" << endl;
				return NULL;
			}
	}

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


int ConfigFileExtractor::CheckType(const enum KeywordType expType, const enum KeywordType type)
{
	if( expType == KEY_TYPE_ERROR || type == KEY_TYPE_ERROR )
	{
		cerr << "CheckType() error: parameter error!" << endl;
		return -1;
	}

	if( expType != type )
	{
		cerr << "CheckType() error: the type of the input Key is " << KeytypeToString(type) << endl;
		return -2;
	}

	return 0;
}


int ConfigFileExtractor::GetValueInt(std::string key)
{
	if( key == "" )
	{
		cerr << "GetValue() error: keyword is empty!" << endl;
		return -1;
	}

	int tmp;

	transform(key.begin(), key.end(), key.begin(), ::tolower);
	
	enum KeywordType type = GetKeywordType(key);

	/** If key type is wrong, stop and give out a tip  */
	if( CheckType( KEY_TYPE_INT, type) != 0 )
	{
		return -2;
	}
	else
	{
		tmp = *(int*)GetValue(key, KEY_TYPE_INT);
	}
	
	return tmp;
}


double ConfigFileExtractor::GetValueDouble(std::string key)
{
	if( key == "" )
	{
		cerr << "GetValue() error: keyword is empty!" << endl;
		return -1;
	}

	double tmp;

	transform(key.begin(), key.end(), key.begin(), ::tolower);
	
	enum KeywordType type = GetKeywordType(key);

	/** If key type is wrong, stop and give out a tip  */
	if( CheckType( KEY_TYPE_DOUBLE, type) != 0 )
	{
		return -2;
	}
	else
	{
		tmp = *(double*)GetValue(key, KEY_TYPE_DOUBLE);
	}
	
	return tmp;
}


string ConfigFileExtractor::GetValueString(std::string key)
{
	if( key == "" )
	{
		cerr << "GetValue() error: keyword is empty!" << endl;
		return "";
	}

	string tmp;

	transform(key.begin(), key.end(), key.begin(), ::tolower);
	
	enum KeywordType type = GetKeywordType(key);

	/** If key type is wrong, stop and give out a tip  */
	if( CheckType( KEY_TYPE_STRING, type) != 0 )
	{
		return "";
	}
	else
	{
		tmp = *(string*)GetValue(key, KEY_TYPE_STRING);
	}
	
	return tmp;
}


bool ConfigFileExtractor::GetValueBool(std::string key)
{
	if( key == "" )
	{
		cerr << "GetValue() error: keyword is empty!" << endl;
		return -1;
	}

	bool tmp;

	transform(key.begin(), key.end(), key.begin(), ::tolower);
	
	enum KeywordType type = GetKeywordType(key);

	/** If key type is wrong, stop and give out a tip  */
	if( CheckType( KEY_TYPE_BOOL, type) != 0 )
	{
		return -2;
	}
	else
	{
		tmp = *(bool*)GetValue(key, KEY_TYPE_BOOL);
	}
	
	return tmp;
}


