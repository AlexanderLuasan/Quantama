#include "propertiesholder.h"

propertyholder::propertyholder()
{
}

bool propertyholder::add(string key, string value)
{
	keys.push_back(key);
	values.push_back(value);


	return true;
}

bool propertyholder::isin(string key)
{
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i].compare(key)==0) {
			return true;
		}
	}



	return false;
}

int propertyholder::getsize()
{
	return keys.size();
}

string propertyholder::get(string key)
{
	for (int i = 0; i < keys.size(); i++) {
		if (key.compare(keys[i]) == 0) {
			return values[i];
		}
	}
	return "failed to find";
}

string propertyholder::get(int index)
{
	return values[index];
}
