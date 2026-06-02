/*
** EPITECH PROJECT, 2026
** test.c
** File description:
** Test file for the MNCC project
*/

int pow_recursive(int a, int b, int result)
{
    if (b == 0)
        return result;

    b = b - 1;
    result = result * a;
    return pow_recursive(a, b, result);
}

int my_pow(int num, int x)
{
    return pow_recursive(num, x, 1);
}

int main()
{
    int a = my_pow(3, 4);

    return a + 4;
}
