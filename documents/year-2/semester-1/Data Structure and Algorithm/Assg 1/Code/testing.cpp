#include<iostream>
using namespace std;

//Program R1
int compute (int d)
{
if (d==0) return 2;
else
return (5 * compute(d-2));
}

int main()
{

cout << compute(4) << endl;

system("pause");
return 0;
}