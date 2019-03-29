#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

union three_type
{
    int x;
    long y;
    double z;
};

void function_vector_time_test(void)
{
    DWORD start = GetTickCount();
    int t = 100;
    int n =200000;
    while(t)
    {
        vector<int> a;
        for(int i=0;i<n;i++)
        {
            a.push_back(i);//在vector尾部加入一个数据
        }
        t--;
    }
    cout<<"Running time is "<<GetTickCount()-start<<endl;
}
void function_reserved_vector_time_test(void)
{
    DWORD start = GetTickCount();
    int t = 100;
    int n =200000;
    while(t)
    {
        vector<int> b;
        b.reserve(n+1);//调节vector的大小，使之可以容纳n+1个元素，若小于n个则扩充至n+1
        for(int i=0;i<n;i++)
        {
         b.push_back(i);
        }
        t--;
    }
    cout<<"Running time is "<<GetTickCount()-start<<endl;
}
void function_new_test(void)
{
    DWORD start = GetTickCount();
    int t=100;
    int n = 200000;
    while(t)
    {
        int a[200000];
        for(int i=0; i<n; i++)
        {
            a[i] = i;
        }
        t--;
    } 
    cout<<"Runing time of program:"<<GetTickCount()-start<<endl;  
}

#include <conio.h>
//get keboard up down left right value
//上：0x48  下：0x4d 左：0x50  右：0x4b
void key_board_get(void)
{
    char ch1;
    char ch2;
    ch1=getch();
    ch2=getch();
    printf("%x,%x",ch1,ch2);
    getchar();

}


int main()
{
    key_board_get();
    return 0;
}

//124