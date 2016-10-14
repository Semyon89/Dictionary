#pragma once
#ifndef FILENAME_H
#define FILENAME_H

#include<iostream>
#include<conio.h>
#include<fstream>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::ifstream;
using std::ofstream;

const int l_Eng_words = 25;
const int l_Rus_words = 25;
const int l_key = 4;
const int l_buf = l_Eng_words + l_Rus_words + l_key;

enum Dir
{
	LEFT, RIGHT
};

int menu();

class Dictionary
{
public:
	Dictionary() :key(0), left(NULL), right(NULL) 
	{
		cout << endl << "Construktor is working..." << endl;
		Eng_word = new char[25];
		Rus_word = new char[25];
	}
	~Dictionary() 
	{
		cout << endl << " Destructor is working..." << endl;
		//delete[]Eng_word;
		//delete[]Rus_word;
	}
	void print_tree(Dictionary*);
	Dictionary *add_root(Dictionary*, char*,bool);
	Dictionary *search_and_add_second(Dictionary*, char*, bool);
	Dictionary *translate(Dictionary*, char*);
	Dictionary *search_for_delete(Dictionary*, Dictionary*&, Dir&, char*);
	Dictionary *decent(Dictionary*);
	Dictionary *delete_word(Dictionary*&, Dictionary*, Dictionary*, Dir);
	void save(Dictionary*);
	ofstream first();
private:
	int key;
	char* Eng_word;
	char* Rus_word;
	Dictionary *left, *right;
};

#endif // !FILENAME_H

