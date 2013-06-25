#include <iostream>

#include "ConfigFileExtractorTest.h"

using namespace std;

void ConfigFileExtractorTest::KeywordTest(void)
{
	int ret;

	/** Keywords Test  */	
	cout << "-----------------------" << endl;
	cout << "|    Keywords Test    |" << endl;
	cout << "-----------------------" << endl;

	/** Add normal keys test */
	cout << "** Add normal keys **" << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword1",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword2",KEY_TYPE_STRING));
	cout << "AddKeyword2 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword3",KEY_TYPE_STRING));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword4",KEY_TYPE_STRING));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	cout << endl;

	/** Update keys test */
	cout << "** Update keys **" << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword1",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword2",KEY_TYPE_INT));
	cout << "AddKeyword2 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword3",KEY_TYPE_DOUBLE));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	ret = m_cfg.AddKeyword(make_pair("keyword4",KEY_TYPE_BOOL));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	cout << endl;

	/** Add abnormal key test */

	cout << "** Add abnormal keys **" << endl;

	ret = m_cfg.AddKeyword(make_pair("",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;

	ret = m_cfg.AddKeyword(make_pair("errKey",KEY_TYPE_ERROR));
	cout << "AddKeyword2 ret = " << ret << endl;

	ret = m_cfg.AddKeyword(make_pair("",KEY_TYPE_ERROR));
	cout << "AddKeyword2 ret = " << ret << endl;
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;

	/** Get key type */
	cout << "** Get Key Type **" << endl;
	cout << "Keyword1: " << m_cfg.GetKeywordType("keyword1") << endl; 	
	cout << "Keyword2: " << m_cfg.GetKeywordType("keyword2") << endl; 	
	cout << "Keyword3: " << m_cfg.GetKeywordType("keyword3") << endl; 	
	cout << "Keyword4: " << m_cfg.GetKeywordType("keyword4") << endl; 	
	cout << "errorKey: " << m_cfg.GetKeywordType("") << endl;
	cout << "errorKey: " << m_cfg.GetKeywordType("errKey") << endl;

	cout << endl;

	/** Delete key  */
	cout << "** Delete normal key **" << endl;

	ret = m_cfg.DelKeyword("keyword1");
	cout << "Del keyword1 ret = " << ret << endl;

	ret = m_cfg.DelKeyword("");
	cout << "Del errKey ret = " << ret << endl;
	
	ret = m_cfg.DelKeyword("errKey");
	cout << "Del errKey ret = " << ret << endl;
	cout << endl;

	/** Clear Key */
	cout << "** Clear Keys **" << endl;
	m_cfg.Clear();
	cout << "Dump keys:" << endl;
	m_cfg.DumpKeywords();
	cout << endl;
}
