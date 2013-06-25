#include <iostream>
#include <vector>

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
}


ConfigFileExtractor::~ConfigFileExtractor()
{
}


int ConfigFileExtractor::AddKeyword(const Keyword keyword)
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
		if(m_keywords.insert(keyword).second == false)
		{
			m_keywords[keyword.first] = keyword.second;
			cerr << "AddKeyword() warning: updated the keyword:"<< keyword.first << endl;
		}
	}
	
	return 0;
}


int ConfigFileExtractor::DelKeyword(const std::string key)
{
	if( key == "" )
	{
		cerr << "DelKeyword() error: Key Error!" << endl;
		return -1;
	}
	else
	{
		if( 0 == m_keywords.erase(key))
		{
			cerr << "DelKeyword() warning: no key deleted!" << endl;
		}
	}

	return 0;
}


enum KeywordType ConfigFileExtractor::GetKeywordType(const std::string key)
{
	if( key == "" )
	{
		cerr << "DelKeyword() error: Key Error!" << endl;
		return KEY_TYPE_ERROR;
	}
	else
	{
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

	return;
}



