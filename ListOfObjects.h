#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include "Object.h"

class ListOfObjects
{
public:
	ListOfObjects()
		:m_objects(nullptr)
	{
	};
	~ListOfObjects()
	{
		delete m_objects;
	}

	
	void sortByDistanceAndPrintToFile();
private:
	std::vector<Object> *m_objects;
};

