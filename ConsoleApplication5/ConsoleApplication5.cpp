//#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string> 
#include <iterator>
//#include <charconv>

//#define fori(i, x) for(int i = 0; i < x; ++i)
//#define lang(language) std::setlocale(LC_ALL, "language")
//#define say std::cout << "f"
//void setLang(std::string lang)
//{
//	setlocale(LC_ALL, "lang");
//}

//// Глобальные переменные
static std::string left = "$";           // Хранит предыдущую строку ("ложная" строка в начале)
static std::string center;         // С этой строкой работает функция operStr (начальное значение будет получено в main())

//namespace temp
//{
//	//bool toEoStr = 0;
//}

//template <size_t N> 

//toupper() // Верхний регистр
//tolower() // Нижний регистр

// Логика: функция работает со средней строкой, имея значения левой и правой строки, чтобы правильно расставлять отступы и знаки препинания по краям. Правое значение каждый раз будет передаваться извне. В завершении функции operStr, значение центральной строки записывается в левую строку, а правой в центральную (left <-- center(но лучше newStr) <-- right(получаем извне)). Пошагово перебираем элементы центральной строки, записывая их в newStr, которую в итоге передаем обратно.
std::string operStr(std::string right, size_t N)
{
	// Готовая возвращаемая строка
	std::string newStr;

	//// Исключение повторений         //!!!!!!!!!!!
	//if (piece == clipboard)
	//	return newStr;

	// Если тере стоит в конце слова, значит это ненужное тере (сразу пропускаю его и выхожу из функции, возвращая пустую строку, и не меняя глобальные переменные)
	if (center == "-") return newStr = "";
	
	// Поправка съехавшей точки
	if (center == ".")
	{
		newStr += center;
		goto skipFor;
	}

	// Поправка съехавшей запятой
	if (center == ",")
	{
		newStr += center;
		goto skipFor;
	}
	


	for (int i = 0; i < center.length(); ++i)       //for (int i : piece)
	{
		switch (center[i])
		{
		case '.':

			// Повтор    #define ?
			if (true)
			{
				// Начало повторяющегося кода
				if ((i == 0) && (center[0]) == left[left.length() - 1])
					break;

				char* tmp_ch = &center[i] - sizeof(char);
				//std::cout << center[i] << " " << &center[i] << " " << tmp_ch << " " << *tmp_ch << " " << &tmp_ch << std::endl;
				if (center[i] == *tmp_ch)
					break;

				if ((i == center.length() - 1) && (center[i]) == right[0])
					goto noSpace;
				// Конец повторяющегося кода
			}

			newStr += center[i];
			if (i != center.length() - 1)
				newStr += " ";
			break;

		case ',':

			// Повтор    #define ?
			if (true)
			{
				// Начало повторяющегося кода
				if ((i == 0) && (center[0]) == left[left.length() - 1])
					break;

				char* tmp_ch = &center[i] - sizeof(char);
				//std::cout << center[i] << " " << &center[i] << " " << tmp_ch << " " << *tmp_ch << " " << &tmp_ch << std::endl;
				if (center[i] == *tmp_ch)
					break;

				if ((i == center.length() - 1) && (center[i]) == right[0])
					goto noSpace;
				// Конец повторяющегося кода
			}

			newStr += center[i];
			if (i != center.length() - 1)
				newStr += " ";
			break;

		case '-':
			if (i == (center.length() - 1))
				goto noSpace;

		default:
			newStr += center[i];
			if ((i == center.length() - 1) && (right[0] == ',')) goto noSpace;
			if ((i == center.length() - 1) && (right[0] == '.')) goto noSpace;
			break;
		}


	}

	/*якорь*/skipFor:
	newStr += " ";

	/*якорь*/noSpace:
	left = newStr;     //правильная средняя строка присваивается левой строке
	center = right;
	return newStr;
}

void Files(std::string input, std::string output)
{
	std::ifstream R(input);
	std::ofstream W(output);
	std::string tmp;

	//W << "//";
	R >> center;


	if (!R) { std::cout << "Файл не найден!"; return; }
	else
	{
		while (!R.eof())
		{
			R >> tmp;
			W << operStr(tmp, tmp.length());
		}
		// Отправка "ложной" строки для получения последней строки
		W << operStr("&", 1);
	}

	R.close();
	W.close();
}

void writePart(std::string input, std::string output)
{
	std::ifstream R(input);
	std::ofstream W(output);
	std::string tmp;
	W << "/*\n"; //чтобы не очищать файл постоянно

	if (!R) { std::cout << "Файл не найден!"; return; }
	else
	{
		int tabindex = 0;
		R >> tmp;
		for (int i = 0; i != tmp.size(); i++)
		{
			switch (tmp[i])
			{
			case ';':
				W << tmp[i];
				W << std::endl;
				if (tmp[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1] != '}')      // было if (tmp[i + 1] != '}')
					for (int i = 0; i < tabindex; i++)
					{
						W << "\t";
					}
				break;
			case '<':
				if (tmp[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1] != '<')      // было if (tmp[i + 1] != '<')
				{
					W << ' ';
					W << tmp[i];
				}
				break;
			case '>':
				if (tmp[static_cast<std::basic_string<char, std::char_traits<char>, std::allocator<char>>::size_type>(i) + 1] != '>')      // было if (tmp[i + 1] != '>')
				{
					W << tmp[i];
					W << std::endl;
				}
				break;
			case '{':
				tabindex++;
				W << std::endl;
				W << tmp[i];
				W << std::endl;
				for (int i = 0; i < tabindex; i++)
				{
					W << "\t";
				}
				break;
			case '}':
				tabindex--;
				W << tmp[i];
				W << std::endl;
				break;
			default:
				W << tmp[i];
			}
		}
	}
	W << "\n*/"; //закрыть комментарий
}





int main()
{
	/*std::string dx;
	std::cin >> dx;
	lang(dx);*/

	setlocale(LC_ALL, "ru");


	Files("input.txt", "output.txt");


	/*std::uint16_t dx;
	std::cin >> dx;
	fori(dx) {
		std::cout << i << '\n';
	}*/

}

