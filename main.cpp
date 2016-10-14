//  
//

#include "stdafx.h"
#include "Binary_tree.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color 0A");
	ifstream file;
	Dictionary *d = NULL;
	Dictionary *root = NULL;
	bool flag = true;
	bool flag_for_buf = true;
	bool for_getline = true;
	char filename[] = "text1.txt";
	char buf[l_buf + 1];
	char *word = new char[25];
	char* word2 = new char[25];
	Dictionary *f, *p, *tree;
	Dir dir;

	file.open(filename);
	if (!file.is_open())
	{
		cout << "‘айл не найден!" << endl;
		_getch();
		return 1;
	}
	while (true)
	{
		switch (menu())
		{
		case 1:
			if (for_getline)
			{
				while (file.getline(buf, l_buf))
				{
					if (flag && !root)
					{
						root = root->add_root(root, buf, flag_for_buf);
						d = root;
						flag = false;
					}
					else
						root->search_and_add_second(root, buf, flag_for_buf);
				}
				for_getline = false;
			}
			else
				cout << "¬вод с файла уже произведен." << endl;
			cout << endl << endl;
			break;
		case 2:
			flag_for_buf = false;
			if (flag && !root)
			{
				root = root->add_root(root, buf, flag_for_buf);
				flag = false;
			}
			else
				root->search_and_add_second(root, buf, flag_for_buf);
			flag_for_buf = true;
			cout << endl << endl;
			break;
		case 3:
			cout << endl << "¬ведите английское слово, которое нужно перевести." << endl;
			cin.get();
			cin.getline(word, 25);
			root->translate(root, word);
			cout << endl << endl;
			break;
		case 4:
			cout << endl << "¬ведите слово дл¤ удалени¤." << endl;
			cin.get();
			cin.getline(word2, 25);
			f = root->search_for_delete(root, p, dir, word2);
			root->delete_word(root, p, f, dir);
			cout << endl << endl;
			break;
		case 5:
			cout << endl << "—ловарь." << endl;
			root->print_tree(root);
			cout << endl << endl;
			break;
		case 6:
			root->first();
			root->save(root);
			return 0;
		default:
			cout << endl << "¬водить надо числа от 1 до 6." << endl;
			cout << endl << endl;
			break;
		}
	}
	//file.close();
	//cout << endl << endl;
	//root->print_tree(d);
	
	
	_getch();
    return 0;
}

