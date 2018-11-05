#pragma once
#include <string>
#include <vector>
using namespace std;
class propertyholder
{
public:
	propertyholder();

	bool add(string key, string value);
	bool isin(string key);


	int getsize();


	string get(string key);
	string get(int index);

private:

	vector<string> keys;
	vector<string> values;


};