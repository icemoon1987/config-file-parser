#include <iostream>

#include "ConfigFileExtractorTest.h"

using namespace std;

void ConfigFileExtractorTest::NewExtractTest(void)
{
		
	cout << "-------------------------------" << endl;
	cout << "|    New Extract File Test    |" << endl;
	cout << "-------------------------------" << endl;
	
	/** Normal Extract Test  */	
	cout << "** Normal Extract **" << endl;

	int val1;
	string val2;
	double val3;
	bool val4;

	m_cfg.ExtractFile("./test_files/test_file1.conf", '=', '#');

	val1 = m_cfg.GetValueInt("keyword1");
	val2 = m_cfg.GetValueString("keyword2");
	val3 = m_cfg.GetValueDouble("keyword3");
	val4 = m_cfg.GetValueBool("keyword4");

	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;
	cout << "val3 = " << val3 << endl;
	cout << "val4 = " << val4 << endl;

	return;
}
