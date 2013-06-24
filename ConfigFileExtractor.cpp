#include <iostream>
#include <vector>

#include "ConfigFileExtractor.h"

using namespace std;


ConfigFileExtractor::ConfigFileExtractor()
	: m_paraNum = 0 
{
	m_keywords.clear();
	m_intMap.clear();
	m_doubleMap.clear();
	m_stringMap.clear();
	m_boolMap.clear();
}


ConfigFileExtractor::ConfigFileExtractor(const std::vector<Keyword> keywords)
	: m_paraNum = 0,
	  m_keywords = keywords 
{
	this.ConfigFileExtractor();
}


ConfigFileExtractor::~ConfigFileExtractor()
{
}


int ConfigFileExtractor::AddKeyword(const Keyword keyword)
{
	/** If the keyword is not empty, try insert the keyword into m_keywords */
	if(keyword.first == "")
	{
		cerr << "AddKeyword() error: Key Error!" << endl;
		return -1;
	}
	else
	{
		if(m_keywords.insert(keyword).second == false)
		{
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
		return -1;
	}
	else
	{
		m_keywords::iterator i;

		i = m_keywords.find(key);

		if ( m_keywords.end == i )
		{
			cerr << "GetKeywordType() error: " << key << " is not in m_keywords!" << endl;
			return -2;
		}
		else
		{
			return (*i).second;
		}
	}

}


void ConfigFileExtractor::DumpKeywords(void)
{
	m_keywords::iterator i;	

	for(i = m_keywords.begin() ; i != m_keywords.end() ; i++)
	{
		cout << "Key=" << (*i).first << "	" << "Value=" << (*i).second << endl;
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



