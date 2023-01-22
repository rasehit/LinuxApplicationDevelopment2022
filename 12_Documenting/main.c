/*!
\file
\brief Основной файл с программой

OVERVIEW: number guesser

USAGE: main [options] 

OPTIONS:
	-r	Print number in roman numerals
usage: main [-r] 

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

/*!
	\brief Максимальное число символов в вводимой строке 
*/
#define STRMAX 256

/*!
	\brief Таблица соответствия чисел 
*/
char roman_dict[101][16] = 
{
    "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", 
    "XI", "XII", "XIII", "XIV", "XV", "XVI", "XVII", "XVIII", "XIX", "XX", 
    "XXI", "XXII", "XXIII", "XXIV", "XXV", "XXVI", "XXVII", "XXVIII", "XXIX", "XXX", 
    "XXXI", "XXXII", "XXXIII", "XXXIV", "XXXV", "XXXVI", "XXXVII", "XXXVIII", "XXXIX", "XL", 
    "XLI", "XLII", "XLIII", "XLIV", "XLV", "XLVI", "XLVII", "XLVIII", "XLIX", "L", 
    "LI", "LII", "LIII", "LIV", "LV", "LVI", "LVII", "LVIII", "LIX", "LX", 
    "LXI", "LXII", "LXIII", "LXIV", "LXV", "LXVI", "LXVII", "LXVIII", "LXIX", "LXX", 
    "LXXI", "LXXII", "LXXIII", "LXXIV", "LXXV", "LXXVI", "LXXVII", "LXXVIII", "LXXIX", "LXXX", 
    "LXXXI", "LXXXII", "LXXXIII", "LXXXIV", "LXXXV", "LXXXVI", "LXXXVII", "LXXXVIII", "LXXXIX", "XC", 
    "XCI", "XCII", "XCIII", "XCIV", "XCV", "XCVI", "XCVII", "XCVIII", "XCIX", "C"
};

/*!
	\brief Функция для перевода числа из позиционной десятичной системы исчисления в непозционную римскую
    \warning Если на вход передано число вне диапазона 1...100, то программа сломается

	Функция просматривает (хэш)-таблицу и возвращает строку с числов в римской системе счисления

*/
char * to_roman(int n)
{
    return roman_dict[n-1];
}


/*!
	\brief Функция для перевода числа из непозиционной римской системы исчисления в позционную десятичную

	Функция просматривает (хэш)-таблицу и возвращает число, если оно найдено, иначе -1
*/
int from_roman(char * n)
{
    for (int i = 0; i < 100; i++)
    {
        if (!strcmp(n, roman_dict[i]))
            return i+1;
    }
    return -1;
}

void print_help()
{
    printf(_("OVERVIEW: number guesser\n\n"));
    printf(_("USAGE: main [options] \n\n"));
    printf(_("OPTIONS:\n\t-r\tPrint numbers in roman numerals\n"));
}

int main(int argc, char ** argv)
{
    setlocale (LC_ALL, "");
    bindtextdomain ("main", ".");
    textdomain ("main");

    int left_border = 0, right_border = 100, scanf_return, roman_flag = 0;
    char answer[STRMAX];

    if (argc > 1)
    {
        if (!strcmp(argv[1], "--help"))
        {
            print_help();
            return 0;
        }
        if (!strcmp(argv[1], "-r"))
            roman_flag = 1;
    }

    printf(_("Please pick a random number from 1 to 100\n"));
    printf(_("Let's get started\n"));

    while (42)
    {
        if (roman_flag)
            printf(_("Is your number larger than %s?\n"), to_roman((int)((right_border+left_border)/2)));
        else 
            printf(_("Is your number larger than %d?\n"), (int)((right_border+left_border)/2));
        scanf_return = scanf("%s", answer);

        if (scanf_return != 1)
        {
            printf(_("Input went very wrong\nPlease, enter y or n\n"));
            continue;
        }

        if (!strcmp(answer, _("y")))
            left_border = (int)((right_border+left_border)/2);
        else if (!strcmp(answer, _("n")))
            right_border = (int)((right_border+left_border)/2);
        else 
            printf(_("Please, enter y or n\n"));

        if (right_border-left_border == 1)
        {
            if (roman_flag)
                printf(_("You have picked number %s!\n"), to_roman(right_border));
            else 
                printf(_("You have picked number %d!\n"), right_border);
            break;
        }
    }

    return 0;
}