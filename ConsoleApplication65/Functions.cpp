#include <iostream>
#include <conio.h>
#include <regex>
#include"Header.h"
#pragma once
#pragma warning (disable:4996)

using namespace std;

//extern struct User* PhoneBook;
//extern int Size;

void Read(User*& PhoneBook, int& Size)
{
	FILE* In = fopen("PhoneBook.bin", "rb");
	fread(&Size, sizeof(int), 1, In);
	PhoneBook = new User[Size];
	for (int i = 0; i < Size; i++)
	{
		int Str_Size;
		fread(&Str_Size, sizeof(int), 1, In);
		PhoneBook[i].Name = new char[Str_Size + 1];
		fread(PhoneBook[i].Name, sizeof(char), Str_Size, In);
		PhoneBook[i].Name[Str_Size] = '\0';

		fread(PhoneBook[i].Phone, sizeof(char), 10, In);
		PhoneBook[i].Phone[10] = '\0';

		fread(&Str_Size, sizeof(int), 1, In);
		PhoneBook[i].Email = new char[Str_Size + 1];
		fread(PhoneBook[i].Email, sizeof(char), Str_Size, In);
		PhoneBook[i].Email[Str_Size] = '\0';

		fread(&PhoneBook[i].Info_Size, sizeof(int), 1, In);

		PhoneBook[i].Info = new char* [PhoneBook[i].Info_Size];
		for (int j = 0; j < PhoneBook[i].Info_Size; j++)
		{
			fread(&Str_Size, sizeof(int), 1, In);
			PhoneBook[i].Info[j] = new char[Str_Size + 1];
			fread(PhoneBook[i].Info[j], sizeof(char), Str_Size, In);
			PhoneBook[i].Info[j][Str_Size] = '\0';
		}
	}
	fclose(In);
}

void Add(User*& PhoneBook, int& Size)
{
	system("cls");
	bool job = 1;
	int flag;

	User* Try = new User[Size + 1];
	for (int i = 0; i < Size; i++)
	{
		Try[i] = PhoneBook[i];
	}

	delete[] PhoneBook;
	PhoneBook = Try;

	char temp[100];

	cout << "To Add User in Phone book\n";
	while (job)
	{
		flag = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter full name of user (example Steven Paul Jobs) - ";
		cin.getline(temp, 100);

		flag = NameCheck(temp);

		if (flag != 1)
			cout << "Wrong name format\n";
		else
		{
			PhoneBook[Size].Name = new char[strlen(temp) + 1];
			strcpy(PhoneBook[Size].Name, temp);
			job = 0;
		}
	}
	job = 1;
	while (job)
	{
		flag = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter user phone number (without + (example \"0123456789\")) - ";
		cin.getline(PhoneBook[Size].Phone, 11);
		
		flag = PhoneCheck(PhoneBook[Size].Phone);

		if (flag != 1)
			cout << "Wrong number!\n";
		else
			job = 0;
	}
	job = 1;
	while (job)
	{
		flag = 0;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter user email (Example@gmail.com) - ";
		cin.getline(temp, 100);

		flag = EmailCheck(temp);
		if (flag != 1)
			cout << "Wrong Email\n";
		else
		{
			PhoneBook[Size].Email = new char[strlen(temp) + 1];
			strcpy(PhoneBook[Size].Email, temp);
			job = 0;
		}
	}

	PhoneBook[Size].Info_Size = 0;
	cout << "Do you want to add extra information?\n1 - Yes\n0 - No\n";
	if (_getch() == '1')
	{
		job = 1;
		while (job)
		{
			char** ChTemp = new char* [PhoneBook[Size].Info_Size + 1];
			for (int i = 0; i < PhoneBook[Size].Info_Size; i++)
			{
				ChTemp[i] = PhoneBook[Size].Info[i];
			}
			delete[] PhoneBook[Size].Info;
			PhoneBook[Size].Info = ChTemp;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter additional information - ";
			cin.getline(temp, 100);
			PhoneBook[Size].Info[PhoneBook[Size].Info_Size] = new char[strlen(temp) + 1];
			strcpy(PhoneBook[Size].Info[PhoneBook[Size].Info_Size], temp);
			PhoneBook[Size].Info_Size++;

			cout << "Do you want to add extra information?\n1 - Yes\n0 - No\n";
			if (_getch() == '0')
			{
				job = 0;
			}
		}
	}

	Size++;
}

void AddInfo(User*& PhoneBook, int Size, int index)
{
	system("cls");
	char temp[100];
	bool job = 1;
	while (job)
	{
		char** ChTemp = new char* [PhoneBook[index].Info_Size + 1];
		for (int i = 0; i < PhoneBook[index].Info_Size; i++)
		{
			ChTemp[i] = PhoneBook[index].Info[i];
		}
		delete[] PhoneBook[index].Info;
		PhoneBook[index].Info = ChTemp;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Enter additional information - ";
		cin.getline(temp, 100);
		PhoneBook[index].Info[PhoneBook[index].Info_Size] = new char[strlen(temp) + 1];
		strcpy(PhoneBook[index].Info[PhoneBook[index].Info_Size], temp);
		PhoneBook[index].Info_Size++;

		cout << "Do you want to add extra information?\n1 - Yes\n0 - No\n";
		if (_getch() == '0')
		{
			job = 0;
		}
	}
}

int NameCheck (char* Name)
{
	// Possible variant of pattern "[A-Z a-z 0-9]+((\\s){1}[A-Z a-z 0-9]+)*"

	const regex pattern("[A-Z]{1}[a-z]+((\\s){1}[A-Z]{1}[a-z]+){2}");

	return regex_match(Name, pattern);
}

int PhoneCheck(char Phone[11])
{
	const regex pattern("[[:digit:]]{10}");

	return regex_match(Phone, pattern);
}

int EmailCheck(char* Email)
{	
	const regex pattern("(\\w){3,}((\\.|_){1}(\\w+))*@(\\w+)(\\.(\\w+))+");

	return regex_match(Email, pattern);
}

void Show(User* PhoneBook, int Size)
{
	system("cls");
	cout << "#\tFull name\tPhone number\tEmail\n";

	for (int i = 0; i < Size; i++)
	{
		cout << i + 1 << "\t" << PhoneBook[i].Name << "\t" << PhoneBook[i].Phone << "\t"<< PhoneBook[i].Email<<"\n";

		if (PhoneBook[i].Info_Size > 0)
		{
			cout << "# Extra information\n";
			for (int j = 0; j < PhoneBook[i].Info_Size; j++)
			{
				cout << j+1 << " " << PhoneBook[i].Info[j] << "\n";
			}
			cout << "\n";
		}
	}
	system("pause");
}

void Show(User* PhoneBook, int Size,int i)
{
	system("cls");
	
	cout << "#\tFull name\tPhone number\tEmail\n";
	cout << i + 1 << "\t" << PhoneBook[i].Name << "\t" << PhoneBook[i].Phone << "\t" << PhoneBook[i].Email << "\n";
	if (PhoneBook[i].Info_Size > 0)
	{
		cout << "# Extra information\n";
		for (int j = 0; j < PhoneBook[i].Info_Size; j++)
		{
			cout << j + 1 << " " << PhoneBook[i].Info[j] << "\n";
		}
		cout << "\n";
	}
}

void Change(User*& PhoneBook, int Size,int info)
{
	system("cls");
	int Index = 0, flag = 0;
	char temp[100];
	bool job = 1;
	switch (info)
	{
	case 1:
		cout << "Enter index of User - ";
		cin >> Index;
		if (Index < 1 || Index > Size)
			cout << "Wrong index\n";
		else 
		{
			Index--;
			while (job)
			{
				flag = 0;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter new full name of user (Example Steven Paul Jobs) - ";
				cin.getline(temp, 100);

				flag = NameCheck(temp);
				if (flag != 1)
					cout << "Wrong name format\n";
				else
				{
					PhoneBook[Index].Name = new char[strlen(temp) + 1];
					strcpy(PhoneBook[Index].Name, temp);
					job = 0;
				}
			}
		}
		break;
	case 2:
		cout << "Enter index of User - ";
		cin >> Index;
		if (Index < 1 || Index > Size)
			cout << "Wrong index\n";
		else
		{
			Index--;
			while (job)
			{
				flag = 0;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter user phone number (without + (example \"0123456789\")) - ";
				cin.getline(PhoneBook[Index].Phone, 11);

				flag = PhoneCheck(PhoneBook[Index].Phone);

				if (flag != 1)
					cout << "Wrong number!\n";
				else
					job = 0;
			}
		}
		break;
	case 3:
		cout << "Enter index of User - ";
		cin >> Index;
		if (Index < 1 || Index > Size)
			cout << "Wrong index\n";
		else 
		{
			Index--;
			while (job)
			{
				flag = 0;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Enter new email (Example@gmail.com) - ";
				cin.getline(temp, 100);

				flag = EmailCheck(temp);
				if (flag != 1)
					cout << "Wrong Email\n";
				else
				{
					PhoneBook[Index].Email = new char[strlen(temp) + 1];
					strcpy(PhoneBook[Index].Email, temp);
					job = 0;
				}
			}
		}
		break;
	case 4:

		cout << "Enter index of User - ";
		cin >> Index;
		if (Index < 1 || Index > Size)
			cout << "Wrong index\n";
		else
		{
			Index--;
			while (job)
			{
				cout << "Choose what additional information you want to change - ";
				cin >> flag;
				if (flag < 1 || flag > PhoneBook[Index].Info_Size)
					cout << "Wrong index\n";
				else
				{
					flag--;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Enter new information - ";
					cin.getline(temp, 100);
					PhoneBook[Index].Info[flag] = new char[strlen(temp) + 1];
					strcpy(PhoneBook[Index].Info[flag], temp);
					job = 0;
				}
			}
		}
		break;
	}
}

void Del(User*& PhoneBook, int& Size, int Index)
{
	User* Temp = new User[Size - 1];

	for (int i = 0; i < Size; i++)
	{
		if (i < Index)
			Temp[i] = PhoneBook[i];
		else if(i>Index)
			Temp[i - 1] = PhoneBook[i];
	}

	delete[] PhoneBook[Index].Name;
	delete[] PhoneBook[Index].Email;
	delete[] PhoneBook;

	PhoneBook = Temp;
	Size--;
}

void DelInfo(User*& PhoneBook, int Size, int index)
{
	system("cls");
	if (PhoneBook[index].Info_Size == 0)
	{
		cout << "No additional information\n";
	}
	else
	{
		int st = 0;
		cout << "Choose additional information you want to delete - ";
		cin >> st;
		if (st < 1 || st > PhoneBook[index].Info_Size)
			cout << "Wrong index\n";
		else
		{
			char** Temp = new char* [PhoneBook[index].Info_Size - 1];
			for (int i = 0; i < PhoneBook[index].Info_Size; i++)
			{
				if (i < st)
					Temp[i] = PhoneBook[index].Info[i];
				else if (i > index)
					Temp[i - 1] = PhoneBook[index].Info[i];
			}
			delete[] PhoneBook[index].Info;
			PhoneBook[index].Info = Temp;

			PhoneBook[index].Info_Size--;
		}
	}
}

void Sort(User*& PhoneBook, int Size)
{
	for (int i = 0; i < Size - 1; i++)
	{
		for (int j = 0; j<Size-i-1; j++)
		{
			int k = 0;
			while (true)
			{
				if (PhoneBook[j].Name[k] != PhoneBook[j + 1].Name[k])
					break;
				else
					k++;
			}

			if (PhoneBook[j].Name[k] > PhoneBook[j + 1].Name[k])
			{
				swap(PhoneBook[j], PhoneBook[j + 1]);
			}
		}
	}
}

void Search(User* PhoneBook, int Size)
{
	system("cls");
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	char temp[100];
	int flag = 0;
	cout << "Enter name of person you want to search for - ";
	cin.getline(temp, 100);

	flag = NameCheck(temp);

	if (flag != 1)
		cout << "Wrong name format\n";
	else 
	{
		flag = 0;
		for (int i = 0; i < Size; i++)
		{
			if (!strcmp(temp, PhoneBook[i].Name))
			{
				Show(PhoneBook, Size, i);
				flag++;
			}
		}
	}
	if (flag != 0)
		cout << "\nFound " << flag << " person\n";
	else
		cout << "\nThere is no User with this name "<< temp <<"\n";
	system("pause");
}

void Write(User* PhoneBook, int Size)
{
	FILE* In = fopen("PhoneBook.bin", "wb");
	fwrite(&Size, sizeof(int), 1, In);
	for (int i = 0; i < Size; i++)
	{
		int Str_Size = strlen(PhoneBook[i].Name);
		fwrite(&Str_Size, sizeof(int), 1, In);
		fwrite(PhoneBook[i].Name, sizeof(char), Str_Size, In);

		fwrite(PhoneBook[i].Phone, sizeof(char), 10, In);

		Str_Size = strlen(PhoneBook[i].Email);
		fwrite(&Str_Size, sizeof(int), 1, In);
		fwrite(PhoneBook[i].Email, sizeof(char), Str_Size, In);

		fwrite(&PhoneBook[i].Info_Size, sizeof(int), 1, In);

		for (int j = 0; j < PhoneBook[i].Info_Size; j++)
		{
			Str_Size = strlen(PhoneBook[i].Info[j]);
			fwrite(&Str_Size, sizeof(int), 1, In);
			fwrite(PhoneBook[i].Info[j], sizeof(char), Str_Size, In);
		}
	}
	fclose(In);
}
