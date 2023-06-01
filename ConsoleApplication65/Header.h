#pragma once

struct User
{
	char* Name = nullptr;
	char Phone[11];
	char* Email = nullptr;
	int Info_Size;
	char** Info=nullptr;
};

void Read(User*&, int&);

void Add(User*&, int&);
void AddInfo(User*&, int, int);

int NameCheck(char*);
int PhoneCheck(char[11]);
int EmailCheck(char*);

void Show(User*, int);
void Show(User*, int, int);

void Change(User*&, int, int);

void Del(User*&, int&, int);
void DelInfo(User*&, int, int);

void Sort(User*&, int);

void Search(User*, int);

void Write(User*, int);