#ifndef _TEST_H
#define _TEST_H

#include "ConfigFileExtractor.h"

class ConfigFileExtractorTest
{
	private:
		ConfigFileExtractor &m_cfg;

	public:
		ConfigFileExtractorTest( ConfigFileExtractor &cfg ): m_cfg(cfg) {};
		~ConfigFileExtractorTest() {};

	public:
		void NewExtractTest(void);
		void CCSMConfTest(void);
};

#endif
