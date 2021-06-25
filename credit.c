#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long credit = get_long("Number: ");

    if ( credit / 1000000000000 % 10 == 4)
    {
        long vm = credit % 10;
        long vl = credit / 10 % 10 * 2;
        long vk = credit / 100 % 10;
        long vj = credit / 1000 % 10 * 2;
        long vi = credit / 10000 % 10;
        long vh = credit / 100000 % 10 * 2;
        long vg = credit / 1000000 % 10;
        long vf = credit / 10000000 % 10 * 2;
        long ve = credit / 100000000 % 10;
        long vd = credit / 1000000000 % 10 * 2;
        long vc = credit / 10000000000 % 10;
        long vb = credit / 100000000000 % 10 * 2;
        long va = credit / 1000000000000 % 10;

        int product = (vl / 10 % 10) + (vl % 10) + (vj % 10) + (vj / 10 % 10) + (vh % 10) + (vh / 10 % 10) + (vf % 10) + (vf / 10 % 10) + (vd % 10) + (vd / 10 % 10) + (vb % 10) + (vb / 10 % 10);

        int sum = product + vm + vk + vi + vg + ve + vc + va;

        if (sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 1000000000000000 % 10 == 4)
    {
        long vp = credit % 10;
        long vo = credit / 10 % 10 * 2;
        long vn = credit / 100 % 10;
        long vm = credit / 1000 % 10 * 2;
        long vl = credit / 10000 % 10;
        long vk = credit / 100000 % 10 * 2;
        long vj = credit / 1000000 % 10;
        long vi = credit / 10000000 % 10 * 2;
        long vh = credit / 100000000 % 10;
        long vg = credit / 1000000000 % 10 * 2;
        long vf = credit / 10000000000 % 10;
        long ve = credit / 100000000000 % 10 * 2;
        long vd = credit / 1000000000000 % 10;
        long vc = credit / 10000000000000 % 10 * 2;
        long vb = credit / 100000000000000 % 10;
        long va = credit / 1000000000000000 % 10 * 2;

        int product = (vo / 10 % 10) + (vo % 10) + (vm % 10) + (vm / 10 % 10) + (vk % 10) + (vk / 10 % 10) + (vi % 10) + (vi / 10 % 10) + (vg % 10) + (vg / 10 % 10) + (ve % 10) + (ve / 10 % 10) + (vc % 10) + (vc / 10 % 10) + (va % 10) + (va / 10 % 10);

        int sum = product + vp + vn + vl + vj + vh + vf + vd + vb;

        if (sum % 10 == 0)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 10000000000000 % 100 == 37)
    {
        long ap = credit % 10;
        long ao = credit / 10 % 10 * 2;
        long an = credit / 100 % 10;
        long am = credit / 1000 % 10 * 2;
        long al = credit / 10000 % 10;
        long ak = credit / 100000 % 10 * 2;
        long aj = credit / 1000000 % 10;
        long ai = credit / 10000000 % 10 * 2;
        long ah = credit / 100000000 % 10;
        long ag = credit / 1000000000 % 10 * 2;
        long af = credit / 10000000000 % 10;
        long ae = credit / 100000000000 % 10 * 2;
        long ad = credit / 1000000000000 % 10;
        long ac = credit / 10000000000000 % 10 * 2;
        long ab = credit / 100000000000000 % 10;


        int product = (ao % 10) + (ao / 10 % 10) + (am % 10) + (am / 10 % 10) + (ak % 10) + (ak / 10 % 10) + (ai % 10) + (ai / 10 % 10) + (ag % 10) + (ag / 10 % 10) + (ae % 10) + (ae / 10 % 10) + (ac % 10) + (ac / 10 % 10);

        int sum = product + ap + an + al + aj + ah + af + ad + ab;

        if (sum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 10000000000000 % 100 == 34)
    {
        long ap = credit % 10;
        long ao = credit / 10 % 10 * 2;
        long an = credit / 100 % 10;
        long am = credit / 1000 % 10 * 2;
        long al = credit / 10000 % 10;
        long ak = credit / 100000 % 10 * 2;
        long aj = credit / 1000000 % 10;
        long ai = credit / 10000000 % 10 * 2;
        long ah = credit / 100000000 % 10;
        long ag = credit / 1000000000 % 10 * 2;
        long af = credit / 10000000000 % 10;
        long ae = credit / 100000000000 % 10 * 2;
        long ad = credit / 1000000000000 % 10;
        long ac = credit / 10000000000000 % 10 * 2;
        long ab = credit / 100000000000000 % 10;


        int product = (ao % 10) + (ao / 10 % 10) + (am % 10) + (am / 10 % 10) + (ak % 10) + (ak / 10 % 10) + (ai % 10) + (ai / 10 % 10) + (ag % 10) + (ag / 10 % 10) + (ae % 10) + (ae / 10 % 10) + (ac % 10) + (ac / 10 % 10);

        int sum = product + ap + an + al + aj + ah + af + ad + ab;

        if (sum % 10 == 0)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 100000000000000 % 100 == 51)
    {
        long p = credit % 10;
        long o = credit / 10 % 10 * 2;
        long n = credit / 100 % 10;
        long m = credit / 1000 % 10 * 2;
        long l = credit / 10000 % 10;
        long k = credit / 100000 % 10 * 2;
        long j = credit / 1000000 % 10;
        long i = credit / 10000000 % 10 * 2;
        long h = credit / 100000000 % 10;
        long g = credit / 1000000000 % 10 * 2;
        long f = credit / 10000000000 % 10;
        long e = credit / 100000000000 % 10 * 2;
        long d = credit / 1000000000000 % 10;
        long c = credit / 10000000000000 % 10 * 2;
        long b = credit / 100000000000000 % 10;
        long a = credit / 1000000000000000 % 10 * 2;

        int product = (o/ 10 % 10) + (o % 10) + (m % 10) + (m / 10 % 10) + (k % 10) + (k / 10 % 10) + (i % 10) + (i / 10 % 10) + (g % 10) + (g / 10 % 10) + (e % 10) + (e / 10 % 10) + (c / 10 % 10) + (c % 10) + (a / 10 % 10) + (a % 10);

        int sum = product + p + n + l + j + h + f + d + b;

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 100000000000000 % 100 == 52)
    {
        long p = credit % 10;
        long o = credit / 10 % 10 * 2;
        long n = credit / 100 % 10;
        long m = credit / 1000 % 10 * 2;
        long l = credit / 10000 % 10;
        long k = credit / 100000 % 10 * 2;
        long j = credit / 1000000 % 10;
        long i = credit / 10000000 % 10 * 2;
        long h = credit / 100000000 % 10;
        long g = credit / 1000000000 % 10 * 2;
        long f = credit / 10000000000 % 10;
        long e = credit / 100000000000 % 10 * 2;
        long d = credit / 1000000000000 % 10;
        long c = credit / 10000000000000 % 10 * 2;
        long b = credit / 100000000000000 % 10;
        long a = credit / 1000000000000000 % 10 * 2;

        int product = (o/ 10 % 10) + (o % 10) + (m % 10) + (m / 10 % 10) + (k % 10) + (k / 10 % 10) + (i % 10) + (i / 10 % 10) + (g % 10) + (g / 10 % 10) + (e % 10) + (e / 10 % 10) + (c / 10 % 10) + (c % 10) + (a / 10 % 10) + (a % 10);

        int sum = product + p + n + l + j + h + f + d + b;

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 100000000000000 % 100 == 53)
    {
        long p = credit % 10;
        long o = credit / 10 % 10 * 2;
        long n = credit / 100 % 10;
        long m = credit / 1000 % 10 * 2;
        long l = credit / 10000 % 10;
        long k = credit / 100000 % 10 * 2;
        long j = credit / 1000000 % 10;
        long i = credit / 10000000 % 10 * 2;
        long h = credit / 100000000 % 10;
        long g = credit / 1000000000 % 10 * 2;
        long f = credit / 10000000000 % 10;
        long e = credit / 100000000000 % 10 * 2;
        long d = credit / 1000000000000 % 10;
        long c = credit / 10000000000000 % 10 * 2;
        long b = credit / 100000000000000 % 10;
        long a = credit / 1000000000000000 % 10 * 2;

        int product = (o/ 10 % 10) + (o % 10) + (m % 10) + (m / 10 % 10) + (k % 10) + (k / 10 % 10) + (i % 10) + (i / 10 % 10) + (g % 10) + (g / 10 % 10) + (e % 10) + (e / 10 % 10) + (c / 10 % 10) + (c % 10) + (a / 10 % 10) + (a % 10);

        int sum = product + p + n + l + j + h + f + d + b;

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 100000000000000 % 100 == 54)
    {
        long p = credit % 10;
        long o = credit / 10 % 10 * 2;
        long n = credit / 100 % 10;
        long m = credit / 1000 % 10 * 2;
        long l = credit / 10000 % 10;
        long k = credit / 100000 % 10 * 2;
        long j = credit / 1000000 % 10;
        long i = credit / 10000000 % 10 * 2;
        long h = credit / 100000000 % 10;
        long g = credit / 1000000000 % 10 * 2;
        long f = credit / 10000000000 % 10;
        long e = credit / 100000000000 % 10 * 2;
        long d = credit / 1000000000000 % 10;
        long c = credit / 10000000000000 % 10 * 2;
        long b = credit / 100000000000000 % 10;
        long a = credit / 1000000000000000 % 10 * 2;

        int product = (o/ 10 % 10) + (o % 10) + (m % 10) + (m / 10 % 10) + (k % 10) + (k / 10 % 10) + (i % 10) + (i / 10 % 10) + (g % 10) + (g / 10 % 10) + (e % 10) + (e / 10 % 10) + (c / 10 % 10) + (c % 10) + (a / 10 % 10) + (a % 10);

        int sum = product + p + n + l + j + h + f + d + b;

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    else if (credit / 100000000000000 % 100 == 55)
    {
        long p = credit % 10;
        long o = credit / 10 % 10 * 2;
        long n = credit / 100 % 10;
        long m = credit / 1000 % 10 * 2;
        long l = credit / 10000 % 10;
        long k = credit / 100000 % 10 * 2;
        long j = credit / 1000000 % 10;
        long i = credit / 10000000 % 10 * 2;
        long h = credit / 100000000 % 10;
        long g = credit / 1000000000 % 10 * 2;
        long f = credit / 10000000000 % 10;
        long e = credit / 100000000000 % 10 * 2;
        long d = credit / 1000000000000 % 10;
        long c = credit / 10000000000000 % 10 * 2;
        long b = credit / 100000000000000 % 10;
        long a = credit / 1000000000000000 % 10 * 2;

        int product = (o/ 10 % 10) + (o % 10) + (m % 10) + (m / 10 % 10) + (k % 10) + (k / 10 % 10) + (i % 10) + (i / 10 % 10) + (g % 10) + (g / 10 % 10) + (e % 10) + (e / 10 % 10) + (c / 10 % 10) + (c % 10) + (a / 10 % 10) + (a % 10);

        int sum = product + p + n + l + j + h + f + d + b;

        if (sum % 10 == 0)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}