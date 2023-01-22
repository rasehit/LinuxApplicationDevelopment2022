#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)
#define STRMAX 256

int main(int argc, char ** argv)
{
    setlocale (LC_ALL, "");
    bindtextdomain ("main", ".");
    textdomain ("main");

    int left_border = 0, right_border = 100, scanf_return;
    char answer[STRMAX];

    printf(_("Please pick a random number from 1 to 100\n"));
    printf(_("Let's get started\n"));

    while (42)
    {
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
            printf(_("You have picked number %d!\n"), right_border);
            break;
        }
    }

    return 0;
}