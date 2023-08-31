//#include "ListOfObjects.h"
#include <fstream>
#include "Object.h"
int main() 
{
	std::ofstream out;
	out.open("output.txt", std::ios::out | std::ios::trunc);
	if (out.is_open())
	{
		Object a("Вася", 0.0, 1.0, "Человек");
		a.print(out);
	}
	out.close();
	return 0;
}
