#include "ListOfObjects.h"

void ListOfObjects::sortByDistanceAndPrintToFile()
{
	std::ofstream output;
	output.open("output.txt", std::fstream::out | std::fstream::trunc);
	if (!output.is_open())
	{
		std::cout << "Error during opening file for writing!" << std::endl;
	}
	else
	{
		//std::sort(m_objects->begin(), m_objects->end(), &Object::compareByDistance);

		float currentUpperBound = 0.f;
		output << "\t\t\tÃÐÓÏÏÈÐÎÂÊÀ ÏÎ ÐÀÑÑÒÎßÍÈÞ:" << std::endl;
		for (Object obj : *m_objects)
		{
			if ((obj.getDistanceFromOrigin() >= currentUpperBound) && (currentUpperBound <= 10000))
			{
				currentUpperBound = (currentUpperBound < 100) ?  100.f : currentUpperBound * 10;
				output << "Äî " << currentUpperBound << " åäèíèö:" << std::endl;
			}	
			obj.print(output);
		}
	}
	
}