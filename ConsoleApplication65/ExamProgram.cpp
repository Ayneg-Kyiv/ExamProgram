#include <iostream>
#include<Windows.h>
#include <conio.h>
#include"Header.h"

#pragma warning (disable:4996)

using namespace std;

struct User* PhoneBook = nullptr;
int Size = 0;

int main()
{
	bool job = 1;
	int Index;
	MoveWindow(GetConsoleWindow(), 560, 290, 800, 550, true);

	while (job)
	{
		system("cls");
		cout << "Welcome to PhoneBook program!\n\n";

		if (Size == 0)
		{
			cout << "To start work with program you should\n\n";
			cout << "Create new Contact - press 1 \n";
			cout << "Import Contacts from file - press 2\n\n";

			switch (_getch())
			{
			case '1':
				Add(PhoneBook, Size);
				break;
			case '2':
				Read(PhoneBook, Size);
				break;
			case '0':
				cout << "GOOD BYE!\n";
				job = 0;
				break;
			default:
				cout << "Wrong choice\n";
				Sleep(1000);
				break;
			}
		}
		else
		{
			cout << "Choose action\n1-Add new user\n2-Add additional information to user\n3-Show\n4-Change info\n5-Delete\n6-Delete extra info\n7-Sort by name\n8-Search by name\n0-Exit\n";

			switch (_getch())
			{
			case '1':
				Add(PhoneBook, Size);
				break;
			case'2':
				cout << "\n\tEnter index of user you want to add additional info - ";
				cin >> Index;
				Index--;
				if (Index<0 || Index>Size)
					cout << "\tWrong index\n";
				else
					AddInfo(PhoneBook, Size, Index);
				break;
			case '3':
				Show(PhoneBook, Size);
				break;
			case '4':
				cout << "\n\tChoose Information you want to change in Book\n";
				cout << "\t1-Name\n\t2-Phone\n\t3-Email\n\t4-Additional information\n\t0-Back\n";
				switch (_getch())
				{
				case '1':
					Change(PhoneBook, Size, 1);
					break;
				case '2':
					Change(PhoneBook, Size, 2);
					break;
				case '3':
					Change(PhoneBook, Size, 3);
					break;
				case '4':
					Change(PhoneBook, Size, 4);
					break;
				case '0':
					break;
				default:
					cout << "\tWrong choice\n";
					Sleep(1000);
					break;
				}
				break;
			case '5':
				cout << "\n\tDelete last Press 1\n\tDelete other Press 2\n\tPrevious menu Press 0\n";
				switch (_getch())
				{
				case '1':
					Del(PhoneBook, Size, Size - 1);
					break;
				case '2':
					cout << "\n\tEnter index of element you want to delete - ";
					cin >> Index;
					Index--;
					if (Index<0 || Index>Size)
						cout << "\tWrong index\n";
					else
						Del(PhoneBook, Size, Index);
					break;
				case '0':
					break;
				default:
					cout << "\tWrong choice\n";
					Sleep(1000);
					break;
				}
				break;
			case '6':
					cout << "\n\tEnter index of user you want to delete - ";
					cin >> Index;
					Index--;
					if (Index<0 || Index>Size)
						cout << "\tWrong index\n";
					else
						DelInfo(PhoneBook, Size, Index);
				break;
			case'7':
				Sort(PhoneBook, Size);
				break;
			case '8':
				Search(PhoneBook, Size);
				break;
			case '0':
				Write(PhoneBook, Size);
				cout << "\nGOOD BYE!\n";
				job = 0;
				break;
			default:
				cout << "Wrong choice\n";
				Sleep(1000);
				break;
			}
		}
	}

	for (int i = 0; i < Size; i++)
	{
		delete[] PhoneBook[i].Name;
		delete[] PhoneBook[i].Email;
	}
	delete[] PhoneBook;
}
//
//1. Написати програму “Телефона книга”
//- Створити структуру User.Поля структури :
//-ПІБ
//- Номер телефона
//- Адреса електронної пошти.
//
//2. Написати функції
//- Додавання екземпляра у книгу
//- Перевірки номера телефона(не може бути літер, довжина)
//- перевірка адреси електронної пошти(наявність однієї і тільки однієї @, не може бути пробілів, довжина імені не менше 3 символів, після “собаки” повинна стояти ..Між “собакою” та крапкою повинен стояти хоча б один символ, після крапки повинно стояти не менше 2 символів.Крапка не може стояти перед “собакою” та безпосередньо після “собаки” та інші перевірки.
//	- функцію виводу книги на екран
//	- функцію пошук по ПІБ
//	- функцію редагування елементів книги
//	- функцію видалення користувача із книги
//	- функцію сортування по ПІБ
//	- функцію перевірки наявности користувача з таким ПІБ у книзі.
//
//	Поки що так.До екзамену можу ще додати перу функцію.За повне виконання цього завдання — максимум 10 балів.Для того, щоб отримати більше треба додати щось більш цікаве, наприклад інтерфейс тощо.
//