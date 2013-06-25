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
		std::string KeytypeToString(const enum KeywordType type);
		int CheckType(const enum KeywordType expType, const enum KeywordType type);
		void * GetValue(const std::string key, enum KeywordType type);
		int StringToInt(const std::string value);
		double StringToDouble(const std::string value);
		bool StringToBool(std::string value);
		std::string &TrimSpaces(std::string &s);
		std::string &TrimComments(std::string &s, const char commToken);
		int PhaseLine(std::string line, const char delim);
		int ExtractParameter(const std::string key, const std::string value);

	public:
		ConfigFileExtractor();
		~ConfigFileExtractor();
		
	public:
		int AddKeyword(Keyword keyword);
		int DelKeyword(std::string key);
		enum KeywordType GetKeywordType(std::string key);
		void DumpKeywords(void);
		void Clear(void);

	public:
		int ExtractFile(const std::string filePath, const char delim = '=', const char commToken = '#');
		int GetValueInt(std::string key);
		double GetValueDouble(std::string key);
		std::string GetValueString(std::string key);
		bool GetValueBool(std::string key);

};

#endif


