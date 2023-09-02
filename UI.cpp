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
		std::cout << "��� ���������� ���������� �������� ������� �����:\n"
			<< "1: ��������� ������ �������� �� �����\n"
			<< "2: �������� ������ � ������\n"
			<< "3: ������������ ������� � ����������� ������ ����� � ��������� ���������� � ����\n"
			<< "-1: ��������� ������ ���������" << std::endl;
		std::cin >> selectedAction;
		switch (selectedAction)
		{
		case 1: 
		{
			std::cout << "������� �������� ����� ��� ������ � ��������� ������� (��������, ����������� �������� ����: input.txt):" << std::endl;
			std::string filename;
			std::cin >> filename;
			list.readFromFile(filename);
			break;
		}
		case 2:
		{
			std::cout << "������� ������ ��� �������� ������� ����� ������ � �������: ���_������� ����������_x ����������_y ���_�������:" << std::endl;
			std::string name="", type=""; long double xCoord = 0, yCoord = 0;
			std::cin >> name >> xCoord >> yCoord >> type;
			list.addObject(name, xCoord, yCoord, type);
			break;
		}
		case 3:
		{
			std::cout << "������� ����������� ���������� �������� ��� ����������� �� ����:" << std::endl;
			int n;
			std::cin >> n;
			list.groupAndSaveToFile((n > 0) ? n-1 : 0);
			std::cout << "������ ��������� � ����� output.txt, ��� ����������� ������� ����� ��������!" << std::endl;
			std::cin >> n;
			break;
		}
		case -1:
			break;
		default:
			std::cout << "����� ������������ ����� �������, ���������� ��� ���!" << std::endl;
			break;
		}
		system("cls");
	}
}
