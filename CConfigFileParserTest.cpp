#include <iostream>

#include "CConfigFileParserTest.h"

using namespace std;

void CConfigFileParserTest::NewExtractTest(void)
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
	cout << endl;

	/** Default Value Test */
	cout << "** Default Value Test **" << endl;

	val1 = m_cfg.GetValueInt("keyword5");
	val2 = m_cfg.GetValueString("keyword5");
	val3 = m_cfg.GetValueDouble("keyword5");
	val4 = m_cfg.GetValueBool("keyword5");

	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;
	cout << "val3 = " << val3 << endl;
	cout << "val4 = " << val4 << endl;
	cout << endl;

	return;
}

void CConfigFileParserTest::CCSMConfTest(void)
{
	string ip_c_1;
	short port_c_1;

	string ip_c_2;
	short port_c_2;

	string ip_ccsm;

	m_cfg.ExtractFile("./test_files/CCSM.conf", '=', '#');

	ip_c_1 = m_cfg.GetValueString("IP_C_1");
	port_c_1 = m_cfg.GetValueInt("PORT_C_1");

	ip_c_2 = m_cfg.GetValueString("IP_C_2");
	port_c_2 = m_cfg.GetValueInt("PORT_C_2");
	
	ip_ccsm = m_cfg.GetValueString("IP_CCSM");

	cout << "ip_c_1 = " << ip_c_1 << endl;
	cout << "port_c_1 = " << port_c_1 << endl;
	cout << "ip_c_2 = " << ip_c_2 << endl;
	cout << "port_c_2 = " << port_c_2 << endl;
	cout << "ip_ccsm = " << ip_ccsm << endl;

	return;
}


