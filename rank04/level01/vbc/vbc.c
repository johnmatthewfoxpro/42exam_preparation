#include <stdio.h>
#include <ctype.h>

char *s;
int error = 0;

int ft_sum(void);
int ft_product(void);
int ft_factor(void);

void unexpected(char c)
{
    if (c)
        printf("Unexpected token '%c'\n", c);
    else
        printf("Unexpected end of input\n");
}

int fail(void)
{
    unexpected(*s);
    error = 1;
    return (0);
}

int ft_factor(void)
{
    int n;

    if (isdigit((unsigned char)*s))
        return (*s++ - '0');
    if (*s == '(')
    {
        s++;
        n = ft_sum();
        if (error)
            return (0);
        if (*s != ')')
        {
            if (*s == '\0')
                unexpected('(');
            else
                unexpected(*s);
            error = 1;
            return (0);
        }
        s++;
        return (n);
    }
    return (fail());
}

int ft_product(void)
{
    int a = ft_factor();

    while (!error && *s == '*')
    {
        s++;
        a *= ft_factor();
    }
    return (a);
}

int ft_sum(void)
{
    int a = ft_product();

    while (!error && *s == '+')
    {
        s++;
        a += ft_product();
    }
    return (a);
}

int main(int argc, char **argv)
{
    int result;

    if (argc != 2)
        return (1);
    s = argv[1];
    result = ft_sum();
    if (error)
        return (1);
    if (*s)
    {
        unexpected(*s);
        return (1);
    }
    printf("%d\n", result);
    return (0);
}

