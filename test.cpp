#include <iostream>
#include "ConfigFileExtractor.h"

using namespace std;

int main( int argc, char *argv[])
{
	ConfigFileExtractor cfg;
	int ret;

	/** Add normal keys test */
	cout << "** Add normal keys **" << endl;
	ret = cfg.AddKeyword(make_pair("bind_ip",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("port1",KEY_TYPE_STRING));
	cout << "AddKeyword2 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("port2",KEY_TYPE_STRING));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << endl;

	/** Update keys test */
	cout << "** Update keys test **" << endl;

	ret = cfg.AddKeyword(make_pair("bind_ip",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("port1",KEY_TYPE_STRING));
	cout << "AddKeyword2 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("port2",KEY_TYPE_STRING));
	cout << "AddKeyword3 ret = " << ret << endl;
	cout << endl;

	/** Add abnormal key test */

	cout << "** Add abnormal key test **" << endl;

	ret = cfg.AddKeyword(make_pair("",KEY_TYPE_STRING));
	cout << "AddKeyword1 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("port1",KEY_TYPE_ERROR));
	cout << "AddKeyword2 ret = " << ret << endl;

	ret = cfg.AddKeyword(make_pair("",KEY_TYPE_ERROR));
	cout << "AddKeyword2 ret = " << ret << endl;

	return 0;
}

