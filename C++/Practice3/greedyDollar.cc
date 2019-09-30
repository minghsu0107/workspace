#include<iostream>
using namespace std;

int main()
{
    int money[9]={10000,5000,1000,500,100,50,10,5,1};

    int n;
    
    int t=0;

    while( cin >> n )
    {
        cout << n << "=";
        for(int  i=0 ; i<9 ; i++ )
        {
            if( n >= money[i] )
            {
                t+=n/money[i];
                cout << money[i] << "*" << n/money[i] << " ";
                n = n%money[i];
            }
        }
        cout <<"coins in total = "<< t << endl;
    }

    return 0;
}