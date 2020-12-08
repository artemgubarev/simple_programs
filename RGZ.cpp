//Программа перевода числа из арабской записи в римскую

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

#define nums 13
#define NN 15

void arabic_in_roman(); // функция считывания числа в арабской записи и перевод его в римскую запись
void underline_string(char* Word); // функция взятие строки в круглые скобки
void converte(char *str, int *number, int power); // функция конвертирования арабского числа в римское
int Number_Enter(unsigned int min, unsigned int max, const char* mssg); // функция ввода числа с проверкой правильности

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // установка русскго языка консоли

	arabic_in_roman();	// вызов функции

	system("PAUSE");
}


void arabic_in_roman() // функция считывания числа в арабской записи и перевод его в римскую запись
{
	char String[100] = ""; // оператор описания
	int *number = new int;

	puts("Перевода числа из арабской записи в римскую запись.");

	*number = Number_Enter(0, 2147483648, "Введите число в арабской записи:"); // ввод числа с проверкой правильности

	puts("Число в римской записи:");

	if (*number < 0) // проверка числа на отрицательность
	{
		printf("-");
		*number *= -1;
	}

	if (*number > 3999000) // конвертирование миллионов
	{
		converte(String, number, 6);
	}
	if (*number > 3999) // конвертирование тысяч
	{
		converte(String, number, 3);
	}
	converte(String, number, 0); // конвертирование единиц

	puts(String); // вывод строки

	delete number; // освобождение памяти
}

void converte(char *str, int *number, int power) // функция конвертирования арабского числа в римское
{
	// структуры данных
	char roman_digits[nums][5] = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
	int arabic_digits[nums] = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };

	// описание необходимых переменных
	int indx_roman_number = nums - 1 ,underline = 0, factor = pow(10,power)/1000;

	//дополнительные проверки
	if (factor > 0) underline = 1;
	if (factor == 1000 && *number % 1000000 / 1000 <= 3) underline = 2;

	// конвертирование числа
	while (*number > 999 * factor) {

		while (*number >= arabic_digits[indx_roman_number] * pow(10 , power))
		{
			*number -= arabic_digits[indx_roman_number] * pow(10, power);
			strcat_s(str,100 ,roman_digits[indx_roman_number]);
		}

		indx_roman_number--;
	}

	//взятие в круглые скобки
	while(underline-- != 0) underline_string(str);
}

void underline_string(char* Word)// функция взятие строки в круглые скобки
{
	int len = strlen(Word);

	for (int i = len - 1; i >= 0; i--) { // смещение строки вправо на 1 байт
		Word[i + 1] = Word[i];
	}
	Word[0] = '(';  // подчеркивание строки
	Word[len + 1] = ')';
	Word[len + 2] = '\0';
}


int Number_Enter(unsigned int min, unsigned int max, const char* mssg) // функция ввода числа с проверкой правильности
{
	char begin[NN], end[NN], temp[NN];
	unsigned int number;
	int i1, i2, j = 0, l1, l2, len;


	_itoa_s(min, begin, 10); //перевод левой границы в строковое представление
	_itoa_s(max, end, 10); //перевод правой границы в строковое представление

	do //бесконечный цикл
	{
		printf("%s\n", mssg);
		gets_s(temp);
		len = strlen(temp);

		l1 = strlen(begin);
		l2 = strlen(end);

		if (temp[0] == '-' && temp[1] != '0') j = 1;

		for (j; j < len; j++)
			if (isdigit(temp[j]) == 0 || temp[0] == '0') break;
		if (j == len)
		{
			i1 = strcmp(begin, temp);
			i2 = strcmp(temp, end);

			if ((l1 < len) && (len < l2)) return atoi(temp);
			if ((l1 == len) && (i1 <= 0)) return atoi(temp);
			if ((l2 == len) && (i2 <= 0)) return atoi(temp);
		}

		printf("Числа в римской записи не существует\n");
	} while (1);
}