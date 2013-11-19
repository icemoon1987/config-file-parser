#include <iostream>
#include "CConfigFileParser.h"
#include "CConfigFileParserTest.h"

using namespace std;

int main( int argc, char *argv[])
{
	CConfigFileParser cfg;
	CConfigFileParserTest cfgTest(cfg);
	
	//cfgTest.KeywordTest();
	//cfgTest.ExtractFileTest();
	cfgTest.NewExtractTest();

	//cfgTest.CCSMConfTest();

	return 0;
}

