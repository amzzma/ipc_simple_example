#include "utils.h"

void solve_quadratic_equation_func(struct msg *m, double *arg_list)
{
    int a = arg_list[0], b = arg_list[1], c = arg_list[2];
    double discriminant = b * b - 4 * a * c;
    double root1, root2;

    if (discriminant > 0)
    {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
        sprintf(m->text, "root1 = %.2f, root2 = %.2f\n", root1, root2);
    }
    else if (discriminant == 0)
    {
        root1 = root2 = -b / (2 * a);
        sprintf(m->text, "root1 = root2 = %.2f\n", root1);
    }
    else
    {
        double realPart = -b / (2 * a);
        double imaginaryPart = sqrt(-discriminant) / (2 * a);
        sprintf(m->text, "root1 = %.2f + %.2fi, root2 = %.2f - %.2fi\n", realPart, imaginaryPart, realPart, imaginaryPart);
        m->ret_num[0] = realPart;
        m->ret_num[1] = imaginaryPart;
        m->ret_num[2] = realPart;
        m->ret_num[3] = -imaginaryPart;
        m->status = 4;
        return;
    }

    m->ret_num[0] = root1;
    m->ret_num[1] = root2;
    m->status = 2;
}

void find_prime_func(struct msg *m, double *arg_list)
{
    int index = 0;
    for (int i = arg_list[0]; i <= arg_list[1]; i++)
    {
        if (is_prime(i))
        {
            m->ret_num[index++] = i;
        }
    }
    sprintf(m->text, "prime find in range [%lf, %lf]", arg_list[0], arg_list[1]);
    m->status = index;
}
bool is_prime(int num)
{
    if (num <= 1)
    {
        return false; // 0 and 1 isn't prime
    }
    if (num <= 3)
    {
        return true; // 2 and 3 is prime
    }
    if (num % 2 == 0 || num % 3 == 0)
    {
        return false;
    }
    for (int i = 5; i * i <= num; i += 6)
    {
        if (num % i == 0 || num % (i + 2) == 0)
        {
            return false;
        }
    }
    return true;
}

void prime_factors_func(struct msg *m, double *arg_list)
{
    int index = 0;
    int n = (int)arg_list[0];
    while (n % 2 == 0)
    {
        m->ret_num[index++] = 2;
        n = n / 2;
    }

    for (int i = 3; i * i <= n; i = i + 2)
    {
        while (n % i == 0)
        {
            printf("%d ", i);
            m->ret_num[index++] = i;
            n = n / i;
        }
    }

    if (n > 2)
    {
        m->ret_num[index++] = n;
    }

    sprintf(m->text, "prime_factors");
    m->status = index;
}