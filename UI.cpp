#include <windows.h>
#include "UI.h"

void UI::start()
{
	ListOfObjects list;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	update(list);
}

void UI::update(ListOfObjects& list)
{
	int selectedAction = 0;
	while (selectedAction != -1)
	{
		std::cout << "Для выполнения выбранного действия введите цифру:\n"
			<< "1: Прочитать список объектов из файла\n"
			<< "2: Добавить объект в список\n"
			<< "3: Группировать объекты с сортировкой внутри групп и сохранить результаты в файл\n"
			<< "-1: Завершить работу программы" << std::endl;
		std::cin >> selectedAction;
		switch (selectedAction)
		{
		case 1: 
		{
			std::cout << "Введите название файла для чтения с указанием формата (например, прилагаемый тестовый файл: input.txt):" << std::endl;
			std::string filename;
			std::cin >> filename;
			list.readFromFile(filename);
			break;
		}
		case 2:
		{
			std::cout << "Введите данные для создания объекта через пробел в формате: имя_объекта координата_x координата_y тип_объекта:" << std::endl;
			std::string name="", type=""; long double xCoord = 0, yCoord = 0;
			std::cin >> name >> xCoord >> yCoord >> type;
			list.addObject(name, xCoord, yCoord, type);
			break;
		}
		case 3:
		{
			std::cout << "Введите минимальное количество объектов для группировки по типу:" << std::endl;
			int n;
			std::cin >> n;
			list.groupAndSaveToFile((n > 0) ? n-1 : 0);
			std::cout << "Данные сохранены в файле output.txt, для продолжения введите номер действия!" << std::endl;
			std::cin >> n;
			break;
		}
		case -1:
			break;
		default:
			std::cout << "Введён некорректный номер команды, попробуйте ещё раз!" << std::endl;
			break;
		}
		system("cls");
	}
}
