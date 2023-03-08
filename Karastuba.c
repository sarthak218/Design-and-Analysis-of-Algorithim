#include <stdio.h>
#include <math.h>
int getSizeOfNumber(long num)
{
    int count = 0;
    while (num > 0)
    {
        count++;
        num /= 10;
    }
    return count;
}
long karatsuba(long firstNumber, long secondNumber)
{
    if (firstNumber < 10 && secondNumber < 10)
        return firstNumber * secondNumber;
    int size = fmax(getSizeOfNumber(firstNumber), getSizeOfNumber(secondNumber));
    int n = (int)ceil(size / 2.0);
    long p = (long)pow(10, n);
    long a = (long)floor(firstNumber / (double)p);
    long b = firstNumber % p;
    long c = (long)floor(secondNumber / (double)p);
    long d = secondNumber % p;
    long ac = karatsuba(a, c);
    long bd = karatsuba(b, d);
    long e = karatsuba(a + b, c + d) - ac - bd;
    return (long)(pow(10 * 1L, 2 * n) * ac + pow(10 * 1L, n) * e + bd);
}

int main()
{
    long int num1,num2;
    printf("NAME: Sarthak Tripathi \n Reg. N0.: 22MCB0030  \n Karastuba Multiplication \n");
    printf("Enter first number : ");
    scanf("%ld",&num1);
    printf("Enter second number : ");
    scanf("%ld",&num2);
    printf("Result of multiplication : %ld",karatsuba(num1,num2));

    return 0;
}
