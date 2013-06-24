#ifndef _CONFIGFILEEXTRACTOR_H
#define _CONFIGFILEEXTRACTOR_H

#include <vector>
#include <map>
#include <string>
#include <fstream>

enum KeywordType
{
	KEY_TYPE_INT,
	KEY_TYPE_DOUBLE,
	KEY_TYPE_STRING,
	KEY_TYPE_BOOL,
	KEY_TYPE_ERROR
};

typedef std::pair<std::string,enum KeywordType> Keyword;


class ConfigFileExtractor
{
	private:
		std::map<std::string, enum KeywordType> m_keywords;

	private:
		std::map< std::string, int > m_intMap;
		std::map< std::string, double > m_doubleMap;
		std::map< std::string, std::string > m_stringMap;
		std::map< std::string, bool > m_boolMap;
		int m_paraNum;

	private:
		void * GetValue(const std::string key);
		int StringToInt(const std::string value);
		double StringToDouble(const std::string value);
		bool StringToBool(const std::string value);

	public:
		ConfigFileExtractor();
		~ConfigFileExtractor();
		
	public:
		int AddKeyword(const Keyword keyword);
		int DelKeyword(const std::string key);
		enum KeywordType GetKeywordType(const std::string key);
		void DumpKeywords(void);
		void Clear(void);

	public:
		int ExtractFile(const std::string filePath);
		int GetValueInt(const std::string key);
		int GetValueDouble(const std::string key);
		int GetValueString(const std::string key);
		int GetValueBool(const std::string key);

};

#endif


