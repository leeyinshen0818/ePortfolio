//LEE YIN SHEN A23CS0236
//NEO LI XIN A23CS0253
#include <iostream>
using namespace std;

int main()
{
    int itemNum;

    cout<<"Welcome to the Food Ordering System"<<endl;
    cout<<"1. Pizza - $10"<<endl<< "2. Burger - $5"<<endl<<"3. Sandwich - $7"<<endl;
    cout<<"Enter the number of item you want to order: ";
    cin>>itemNum;

    switch (itemNum)
    {
        case 1: cout<<"Your total bill is: $10" <<endl;
            break;

        case 2: cout<<"Your total bill is: $5" <<endl;
            break;

        default: cout<<"Your total bill is: $7" <<endl;

    }

    return 0;
}