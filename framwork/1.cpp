/*
 * @Author: xbybshd
 * @Date: 2020-03-09 18:06:40
 * @Last Modified by: xbybshd
 * @Last Modified time: 2020-03-11 22:39:00
 */
#include <bits/stdc++.h>

using namespace std;

ifstream fcin(".\\input.txt", ifstream::in);
ofstream fcout(".\\output.txt", ofstream::out);
#define MAX 100

string s1, s2, op;
char a[MAX];
void strcpy1(string &s0)
{
    int i;
    for (i = 0; i < s0.length(); i++)
    {
        a[i] = s0[i];
    }
    a[i] = 0;
}
char a0[MAX];
int atoi_1(string &sx)
{
    int sum = 0;
    int len = sx.length();
    for (int i = 0; i < len; i++)
    {
        sum *= 10;
        sum = sum + (sx[i] - '0');
    }
    return sum;
}

int gcd(int a, int b)
{
    if (b > a)
    {
        swap(a, b);
    }
    return a % b == 0 ? b : gcd(b, a % b);
}
int main()
{
    fcin >> s1 >> op >> s2;
    int x1 = s1.find('/');
    string u1 = s1.substr(0, x1);
    string u2 = s1.substr(x1 + 1, s1.length() - x1 - 1);
    int p1 = atoi_1(u1);
    int p2 = atoi_1(u2);

    int y1 = s1.find('/');
    string v1 = s2.substr(0, y1);
    string v2 = s2.substr(y1 + 1, s2.length() - y1 - 1);
    int q1 = atoi_1(v1);
    int q2 = atoi_1(v2);

    int mul = p2 * q2;
    p1 *= q2;
    q1 *= p2;
    int up;
    int negetive = 0;
    if (op[0] == '+')
    {
        up = p1 + q1;
        int g1 = gcd(mul, up);
        up /= g1;
        mul /= g1;
        fcout << up;
        if (mul != 1)
            fcout << '/' << mul;
    }
    else if (op[0] == '-')
    {
        up = p1 - q1;
        if (up < 0)
        {
            negetive = 1;
            up = abs(up);
        }
        if (up == 0)
        {
            fcout << "0";
            return 0;
        }
        int g1 = gcd(mul, up);

        up /= g1;
        mul /= g1;
        if (negetive)
            fcout << '-';
        fcout << up;
        if (mul != 1)
            fcout << '/' << mul;
    }
    else if (op[0] == '*')
    {
        up = (p1 * q1) / (p2 * q2);
        int g1 = gcd(mul, up);
        up /= g1;
        mul /= g1;
        fcout << up;
        if (mul != 1)
            fcout << '/' << mul;
    }
    else
    {
        int g1 = gcd(p1, q1);
        p1 /= g1;
        q1 /= g1;
        fcout << p1;
        if (q1 != 1)
            fcout << '/' << q1;
    }

    fcin.close();
    fcout.close();

    return 0;
}