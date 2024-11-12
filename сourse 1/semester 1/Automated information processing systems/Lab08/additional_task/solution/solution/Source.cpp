#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int main()
{
	system("chcp 1251");
	system("cls");
	int g = 0, i = 0;
	const int n = 4096;
	char str[n] = "";
	char letters[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	int counter = 0, len = 0, code = 0;
	cout << "Введите строку: ";
	cin.getline(str, n);
	for (; str[i] != '\0'; i++)
		len++;
	for (; g < len; g++)
	{
		if (str[g] == ' ')
			continue;
		else
		{
			counter = 0;
			for (; str[g] != ' ' && str[g] != '\0'; g++)
				counter++;
			if (counter % 2 == 0)
			{
				int l = 0;
				for (int p = g - counter; l < counter / 2; p++, l++)
					swap(str[p], str[g - l - 1]);
				for (int p = g - counter; p < g; p++)
					cout << str[p];
				cout << " ";
			}
			else
			{
				for (i = g - counter; i < g; i++)
				{
					if (str[i] == 'а' || str[i] == 'о' || str[i] == 'у' || str[i] == 'э' || str[i] == 'ы' || str[i] == 'я' || str[i] == 'ё' || str[i] == 'ю' || str[i] == 'е' || str[i] == 'и')
					{
						code = str[i];
						char* ring = strchr(letters, code);
						cout << (ring - letters + 1);
					}
					else
					{
						cout << str[i];
					}
				}
				if (i == g)
					cout << " ";
			}
		}
	}
	return(0);
}