#include "stdio.h"

int main(int argc, char**argv)
{
    char arr[1024];
    scanf("%s", arr);
    printf("%s%s%s\n", "Hello, ", arr, "!");
    return 0;
}
