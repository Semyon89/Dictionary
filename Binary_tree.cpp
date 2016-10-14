#include"stdafx.h"
#include "Binary_tree.h"

int menu()
{
	char *buf = new char[1];
	int option;
	do
	{
		cout << "Выберите один из пунктов, нажав одну из предложенных цифр." << endl;
		cout << "\t1 - Ввести словарь с файла." << endl
			<< "\t2 - Ввести английское слово и перевод с клавиатуры. " << endl
			<< "\t3 - Перевести английское слово на русский. " << endl
			<< "\t4 - Удалить английское слово и его перевод из словаря. " << endl
			<< "\t5 - Вывести словарь полностью." << endl
			<< "\t6 - Сохранить и выйти." << endl << endl;
		cin >> buf;
		option = atoi(buf);
	} while (!option);
	return option;
}

void Dictionary::print_tree(Dictionary *p)
{
	Dictionary *print = p;
	Dictionary *prev = NULL;
	if (print)
	{
		print_tree(print->left);
		cout << print->key << "  " << print->Eng_word <<"   ";
		cout << print->Rus_word << endl;
		print_tree(print->right);
		/*while(print)
		{   
			prev = print;
			cout<<print->key<<" "<<print->Eng_word
			<<" "<<print->Rus_word<<endl;
			print=print->left;
			if (!print)
			{
				print = prev;
				print = print->right;
			}

		}*/
	}
}

ofstream Dictionary::first()
{
	ofstream file;
	char name_file[] = "text1.txt";
	file.open(name_file, ios::out);
	if (!file.is_open())
	{
		cout << "Файл не найден!" << endl;
		_getch();
	}
	file.close();
	return file;
}

void Dictionary::save(Dictionary* root)
{
	Dictionary *print = root;
	Dictionary *prev = NULL;
	ofstream file;
	char name_file[] = "text1.txt";
	file.open(name_file, ios::app);
	if (print)
	{
		save(print->left);
		file << print->key << "  " << print->Eng_word << "   ";
		file << print->Rus_word << endl;
		save(print->right);
	}
}

Dictionary* Dictionary::add_root(Dictionary *root, char *buf, bool fl_buf)
{
	char *For_Eng = new char[25];
	root = new Dictionary;
	if (fl_buf)
	{
		root->key = atoi(buf);
		strncpy(For_Eng, buf + l_key, l_Eng_words);
		strcpy(root->Eng_word, For_Eng);
		root->Eng_word[25] = '\0';
		strncpy(root->Rus_word, buf + l_key + l_Eng_words, l_Rus_words);
		//strcpy(root->Rus_word, buf + l_key + l_Eng_words);
		root->Rus_word[25] = '\0';
	}
	else
	{
		cout << endl << "Введите ключ. ";
		cin >> root->key;
		cin.get();
		cout << endl << "Введите английское слово. ";
		cin.getline(root->Eng_word, 25);
		root->Eng_word[25] = '\0';
		cout << endl << "Введите перевод слова на русский.";
		cin.getline(root->Rus_word, 25);
		root->Rus_word[25] = '\0';
	}
	root->left = root->right = NULL;
	return root;
}

Dictionary* Dictionary::search_and_add_second(Dictionary *root, char *buf, bool fl_buf)
{
	Dictionary *t = root;
	Dictionary *prev;
	Dictionary *pnew = new Dictionary;
	char *For_Eng = new char[25];
	if (fl_buf)
	{
		pnew->key = atoi(buf);
		strncpy(For_Eng, buf + l_key, l_Eng_words);
		strcpy(pnew->Eng_word, For_Eng);
		pnew->Eng_word[25] = '\0';
		//wcsncpy(For_Rus, buf + l_key + l_Eng_words, l_Rus_words + 1);
		strcpy(pnew->Rus_word, buf + l_key + l_Eng_words);
		pnew->Rus_word[25] = '\0';
	}
	else
	{
		cout << endl << "Введите ключ. ";
		cin >> pnew->key;
		cin.get();
		cout << endl << "Введите английское слово. ";
		cin.getline(pnew->Eng_word, 25);
		pnew->Eng_word[25] = '\0';
		cout << endl << "Введите перевод слова на русский. ";
		cin.getline(pnew->Rus_word, 25);
		pnew->Rus_word[25] = '\0';
	}
	pnew->left = pnew->right = NULL;
	bool flag = false;
	while (t && !flag)
	{
		prev = t;
		if (strcmp(pnew->Eng_word, t->Eng_word) == 0)
			flag = true;
		else if (strcmp(pnew->Eng_word, t->Eng_word) < 0)
			t = t->left;
		else
			t = t->right;
	}
	if (flag)
		return t;
	if (strcmp(pnew->Eng_word, prev->Eng_word) < 0)
		prev->left = pnew;
	else
		prev->right = pnew;
	return pnew;
}

Dictionary* Dictionary::translate(Dictionary *root,  char *Eng_word)
{
	Dictionary *t = root;
	Dictionary *prev;
	bool flag = false;
	while (t && !flag)
	{
		prev = t;
		if (strstr(t->Eng_word,Eng_word))
		{
			flag = true;
			cout << endl << Eng_word << "  " << t->Rus_word << endl;
		}
		else if (strcmp(Eng_word, t->Eng_word) < 0)
			t = t->left;
		else
			t = t->right;
	}
	if (flag)
		return t;
	if (0 == strcmp(Eng_word, prev->Eng_word))
	{
		cout << endl << Eng_word << "  " << t->Rus_word << endl;
		return prev;
	}
	else
	{
		cout << "Нет слова для перевода в словаре." << endl;
		return nullptr;
	}
}

Dictionary* Dictionary::search_for_delete(Dictionary *root, Dictionary *&prev, Dir &dir, char *word)
{
	Dictionary *t;
	t = root;
	prev = NULL;
	bool found = false;
	while (t && !found)
	{
		if (strstr(t->Eng_word, word))
		{
			found = true;
			if (!prev)
				prev = t;
			
		}
		else if (strcmp(word, t->Eng_word) < 0)
		{
			prev = t;
			t = t->left;
			dir = LEFT;
		}
		else
		{
			prev = t;
			t = t->right;
			dir = RIGHT;
		}
	}

	if (found)
		return t;
}

Dictionary* Dictionary::decent(Dictionary *found)
{
	Dictionary *prev, *y = found->right;
	if (!y->left)
		y->left = found->left;
	else
	{
		do
		{
			prev = y;
			y = y->left;
		} while (y->left);
		y->left = found->left;
		prev->left = y->right;
		y->right = found->right;
	}
	return y;
}

Dictionary* Dictionary::delete_word(Dictionary *&root, Dictionary *prev, Dictionary *found, Dir dir)
{
	Dictionary *r = NULL;
	if (!found->left)
		r = found->right;
	else if (!found->right)
		r = found->left;
	else
		r = decent(found);
	if (found == root)
		root = r;
	else
	{
		if (dir == LEFT)
			prev->left = r;
		else
			prev->right = r;
	}
	delete found;
	return root;
}
