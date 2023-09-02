#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <unordered_map>

#include "Object.h"

class ListOfObjects
{
public:
	ListOfObjects()
		:m_objects(std::vector<Object>())
	{
	};
	
	void readFromFile(const std::string& filename);
	void groupAndSaveToFile(int n);
	void addObject(std::string name, long double x, long double y, std::string type);
	
	std::unordered_map<int, std::vector<Object>> groupByDistance();
	std::unordered_map<char, std::vector<Object>> groupByName();
	std::unordered_map<std::string, std::vector<Object>> groupByTimeOfCreation();
	std::unordered_map<std::string, std::vector<Object>> groupByType(int n);

	void sortByDistance(std::vector<Object> & objects);
	void sortByName(std::vector<Object> & objects);
	void sortByTimeOfCreation(std::vector<Object> & objects);
private:
	std::vector<Object> m_objects;
};

