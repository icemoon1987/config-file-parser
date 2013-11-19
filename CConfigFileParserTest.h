#ifndef _TEST_H
#define _TEST_H

#include "CConfigFileParser.h"

class CConfigFileParserTest
{
	private:
		CConfigFileParser &m_cfg;

	public:
		CConfigFileParserTest( CConfigFileParser &cfg ): m_cfg(cfg) {};
		~CConfigFileParserTest() {};

	public:
		void NewExtractTest(void);
		void CCSMConfTest(void);
};

#endif
