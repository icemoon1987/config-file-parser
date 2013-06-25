#include <iostream>
#include "ConfigFileExtractor.h"
#include "ConfigFileExtractorTest.h"

using namespace std;

int main( int argc, char *argv[])
{
	ConfigFileExtractor cfg;
	ConfigFileExtractorTest cfgTest(cfg);
	
	cfgTest.KeywordTest();

	return 0;
}

