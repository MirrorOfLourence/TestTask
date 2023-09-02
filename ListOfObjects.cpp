#include "ListOfObjects.h"

bool compareByDistance(Object& i, Object& j);
bool compareByName(Object& i, Object& j);
bool compareByTimeOfCreation(Object& i, Object& j);

void ListOfObjects::readFromFile(const std::string& filename)
{
	std::ifstream fin;
	fin.open(filename);
	if(!fin.is_open())
		std::cout << "Error during opening file for reading!" << std::endl;
	else
	{
		std::string line;
		while (getline(fin, line))
		{
			Object obj = Object(line);
			(obj.checkIfValid()) ? m_objects.push_back(obj) : obj.~Object();
		}
		fin.close();
	}
}

std::string getFieldFromLine(const std::string& line, size_t& posOfSpace)
{
	size_t temp = line.find(' ', posOfSpace+1);
	std::string result = (posOfSpace != std::string::npos) ? line.substr(posOfSpace, temp-posOfSpace) : "";
	posOfSpace = temp;
	return result;
}

void ListOfObjects::groupAndSaveToFile(int n)
{
	std::ofstream fout;
	fout.open("output.txt");
	if (!fout.is_open())
		std::cout << "Error during opening file for writing!" << std::endl;
	else
	{
		std::unordered_map<int, std::vector<Object>> groupsByDistance = groupByDistance();
		std::unordered_map<char, std::vector<Object>> groupsByName = groupByName();
		std::unordered_map<std::string, std::vector<Object>> groupsByTimeOfCreation = groupByTimeOfCreation();
		std::unordered_map<std::string, std::vector<Object>> groupsByType = groupByType(n);
		
		fout << std::setw(15) << "Имя\t" << std::setw(15) << "Тип\t"
			<< std::setw(15) << "Расстояние\t"
			<< std::setw(20) << "Время создания" << std::endl;
		fout << "\n\t\t\tГРУППИРОВКА ПО РАССТОЯНИЮ" << std::endl;
		for(auto pair : groupsByDistance)
		{
			if(!pair.second.empty())
			{
				if (pair.first == INT_MAX)
					fout << "Слишком далеко:" << std::endl;
				else
					fout << "До " << pair.first << " единиц:" << std::endl;
				for (Object obj : pair.second)
				{
					obj.print(fout);
				}
			}
		}

		fout << "\n\t\t\tГРУППИРОВКА ПО ИМЕНИ" << std::endl;
		for(char i = 'А'; i != '#'+1; ((i < 'я') || (i == '#')) ? i++ : i = '#')
		{
			if(groupsByName.find(i) != groupsByName.end())
			{
				fout << i << ": " << std::endl;
				for (Object obj : groupsByName[i])
					obj.print(fout);
			}
		}

		fout << "\n\t\t\tГРУППИРОВКА ПО ВРЕМЕНИ СОЗДАНИЯ" << std::endl;
		for (auto pair : groupsByTimeOfCreation)
		{
			if (!pair.second.empty())
			{
				fout << pair.first << ": " << std::endl;
				for (Object obj : pair.second)
				{
					obj.print(fout);
				}
			}
		}

		fout << "\n\t\t\tГРУППИРОВКА ПО ТИПУ" << std::endl;
		for (auto pair : groupsByType)
		{
			if(!pair.second.empty())
			{
				fout << pair.first << ": " << std::endl;
				for (Object obj : pair.second)
				{
					obj.print(fout);
				}
			}
		}
		fout.close();
	}
}

void ListOfObjects::addObject(std::string name, long double x, long double y, std::string type)
{
	m_objects.push_back(Object(name,x,y,type));
}

std::unordered_map<int, std::vector<Object>> ListOfObjects::groupByDistance()
{
	std::unordered_map<int, std::vector<Object>> result = {{100, std::vector<Object>()},
		{1000, std::vector<Object>()},
		{10000, std::vector<Object>()},
		{INT_MAX, std::vector<Object>()},
	};
	sortByDistance(m_objects);
	int limit = 100;
	for (int i = 0; i < m_objects.size();)
	{
		if (m_objects[i].getDistanceFromOrigin() <= limit)
		{
			result[limit].push_back(m_objects[i]);
			i++;
		}
		else
			if(limit < INT_MAX)
				if(limit < 10000)
					limit*=10;
				else
					limit = INT_MAX;	
	}
	return result;
}

std::unordered_map<char, std::vector<Object>> ListOfObjects::groupByName()
{
	std::unordered_map<char, std::vector<Object>> result;
	for (Object obj : m_objects)
	{
		char firstChar = obj.getName()[0];
		if(firstChar >= 'А' && firstChar <= 'я')
			result[obj.getName()[0]].push_back(obj);
		else
			result['#'].push_back(obj);
	}
		
	for (auto & pair : result)
		sortByName(pair.second);
	return result;
}

std::unordered_map<std::string, std::vector<Object>> ListOfObjects::groupByTimeOfCreation()
{
	std::unordered_map<std::string, std::vector<Object>> result = {
		{"Сегодня", std::vector<Object>()},
		{"Вчера", std::vector<Object>()},
		{"На этой неделе", std::vector<Object>()},
		{"В этом месяце", std::vector<Object>()},
		{"В этом году", std::vector<Object>()},
		{"Ранее", std::vector<Object>()},
	};
	time_t currentTime = time(0);
	struct tm currentDateTime;
	localtime_s(&currentDateTime, &currentTime);
	for (Object obj : m_objects)
	{
		time_t objectTime = floor(obj.getTimeOfCreation());
		struct tm objectDateTime;
		localtime_s(&objectDateTime, &objectTime);
		if(objectDateTime.tm_yday == currentDateTime.tm_yday)
			result["Сегодня"].push_back(obj);
		else
			if(objectDateTime.tm_yday == currentDateTime.tm_yday - 1)
				result["Вчера"].push_back(obj);
			else
				if(objectDateTime.tm_yday / 7 == currentDateTime.tm_yday / 7)
					result["На этой неделе"].push_back(obj);
				else
					if(objectDateTime.tm_mon == currentDateTime.tm_mon)
						result["В этом месяце"].push_back(obj);
					else
						if(objectDateTime.tm_year == currentDateTime.tm_year)
							result["В этом году"].push_back(obj);
						else
							result["Ранее"].push_back(obj);
	}
	for (auto& pair : result)
		sortByTimeOfCreation(pair.second);
	return result;
}

std::unordered_map<std::string, std::vector<Object>> ListOfObjects::groupByType(int n)
{
	std::unordered_map<std::string, std::vector<Object>> result{{"Разное", std::vector<Object>()}};
	for(Object obj : m_objects)
		result[obj.getType()].push_back(obj);
	for(auto& pair : result)
	{
		if ((pair.second.size() <= n) && (pair.first != "Разное"))
		{
			result["Разное"].insert(result["Разное"].begin(), pair.second.begin(), pair.second.end());
			result.erase(pair.first);
		}
		else
			sortByName(pair.second);
	}
	sortByName(result["Разное"]);
	return result;
}

void ListOfObjects::sortByDistance(std::vector<Object> & objects)
{
	if(!m_objects.empty())
		std::sort(m_objects.begin(), m_objects.end(), compareByDistance);
}


void ListOfObjects::sortByName(std::vector<Object>& objects)
{
	if(!objects.empty())
		std::sort(objects.begin(), objects.end(), compareByName);
}
void ListOfObjects::sortByTimeOfCreation(std::vector<Object> & objects)
{
	if(!m_objects.empty())
		std::sort(m_objects.begin(), m_objects.end(), compareByTimeOfCreation);
}

bool compareByDistance(Object& i, Object& j) 
{
	return (i.getDistanceFromOrigin() < j.getDistanceFromOrigin());
}

bool compareByTimeOfCreation(Object& i, Object& j)
{
	return (i.getTimeOfCreation() < j.getTimeOfCreation());
}

bool compareByName(Object& i, Object& j)
{
	bool iLessThenJ = true;
	int lengthI = i.getName().length();
	int lengthJ = j.getName().length();
	int iter = 0;
	while((iter < lengthI) && (iter < lengthJ) && (i.getName()[iter] == j.getName()[iter]))
		iter++;
	if(iter >= lengthI) 
		iLessThenJ = true;
	else
		if(iter >= lengthJ)
			iLessThenJ = false;
		else
			iLessThenJ = i.getName()[iter] < j.getName()[iter];
	return iLessThenJ;
}
