#include <iostream>
#include <cstdlib>  //rand(),time()
#include <ctime>    
#include <conio.h>  //getch()
#include <ctype.h>  //
#include <vector>
#include <math.h>   //pow
#include <iomanip>  //setw

using namespace std;

int _array[4][4] ={0};//申请全局数组作为方格里面的数


//0—3的随机数产生
int rand_pro()
{
    srand(time(0));
    int k = rand()%4;
    return k;
}

////////////////////////////////////界面函数////////////////////////////////////////////////////////////
//之前的界面
void display1()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            cout<<_array[i][j]<<"    ";
        }
        cout<<endl;
    }
    cout<<"----------------------------------"<<endl;
}

//界面美化，不显示0，显示外框
void display2()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if (_array[i][j] == 0)
            {
                cout<<" "<<"    ";
            }
            else
                cout<<_array[i][j]<<"    ";
        }
        cout<<endl;
    }
    cout<<"----------------------------------"<<endl;
}

void display() //显示棋盘  
{  
    cout<<setw(46)<<"X2048 by ziyunmumu"<<endl;  
    cout<<setw(50)<<" |-----------------------|"<<endl;  
    for(int i=0;i<=3;i++)   
    {  
        cout<<setw(24)<<"";  
        for(int j=0;j<=3;j++)  
        {  
            //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED); 
            if (_array[i][j] == 0)
            {
                cout<<setw(2)<<"|"<<setw(4)<<" ";  
            }
            else
                cout<<setw(2)<<"|"<<setw(4)<<_array[i][j];  

            if(j==3)  
            {  
                cout<<setw(2)<<"|"<<endl;  
                cout<<setw(50)<<" |-----------------------|"<<endl;  
            }  
        }  
    }  
}  
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////新游戏的开始////////////////////////////////////////////////////////////
void new_game()
{
    //初始化内容
    int i,j;
    for(i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            _array[i][j] = 0;
        }
    }

    int m = rand_pro();
    int n = rand_pro();
    _array[m][n] = 2;
    display();
}
////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////
//随机产生一个0-n-1的数字
int rand_pro_s(int n)
{
    srand(time(0));
    int k = rand()%n;
    return k;
}

//随机产生一个1-n的数字
int rand_pro_ss(int n)
{
    srand(time(0));
    int k = rand()%n+1;
    return k;
}

//统计0的个数,并且通过一个vector来存放坐标
//p需要判断
vector<vector<int>> zero_num(int* p)
{
    int i,j;
    int k = 0;

    vector<vector<int>> v(16 ,vector<int>());

    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            if (_array[i][j] == 0)
            {
                v[k].push_back(i);
                v[k].push_back(j);
                k++;
            }
        }
    }
    *p = k;
    return v;
}


//随机插入一个数字，通空格的个数随机插入
//返回值为true就说明成功插入，否则未能插入
bool insert_num()
{
    int k = 0;
    vector<vector<int>> v;
    v = zero_num(&k);

    if (k>0)
    {
        int m = rand_pro_s(k);
        int x = v[m][0];
        int y = v[m][1];
        _array[x][y] = pow(2.0,rand_pro_ss(2));
        return true;
    }
    return false;
}



////////////////////////////////////获得键盘方向////////////////////////////////////////////////////////////
//获取方向
//返回值
//  1   上   72
//  2   下   80
//  3   左   75
//  4   右   77
int get_direction()
{
    char c1,c2;
    int ret = 0;
    c1 = getch();
    if (!isascii(c1))
    {
        c2 = getch();
        switch(c2)
        {
        case 72: ret = 1;break;
        case 80: ret = 2;break;
        case 75: ret = 3;break;
        case 77: ret = 4;break;
        default: break;
        }
    }
    return ret;
}
////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////移动操作////////////////////////////////////////////////////////////
//上下左右操作
//操作分为两步，首先将相邻的相同数字加起来，然后去除空格
//操作完之后需要插入数字

//之前分为两步的想法有问题，假如是两个相同数字之间有0的话，也是可以结合的

void up_dir()
{
    //完成第一步
    int i,j;
    for (i=0; i<4; i++)
    {
        /*for (j=0; j<3;)
        {
            if (_array[j][i] == _array[j+1][i])
            {
                _array[j][i] = _array[j][i] + _array[j+1][i];
                _array[j+1][i] = 0;
                j += 2;
                continue;
            }
            j++;
        }*/
        int k = 0;
        int x = 0; 
        int y = 0;
        for (j=0; j<4; j++)
        {
            if (k==_array[j][i] && k!=0)
            {
                //_array[x][y] = 2*_array[x][y];
                //_array[x][y] = 2*k;
                _array[x][y] = 2*k;
                _array[j][i] = 0;
                k = 0;
                continue;
            }
            if (_array[j][i]!=0)
            {
                k = _array[j][i];
                //此处的bug是x和y分别应该存储j和i
                x = j;
                y = i;
            }
        }

    }

    for (i=0; i<4; i++)
    {
        int k = 0;
        for (j=0; j<4; j++)
        {
            //if (_array[j][i])//此处有bug，假如k和j相等
            if (_array[j][i])
            {
                if (k != j)
                {
                    _array[k][i] = _array[j][i];
                    _array[j][i] = 0;
                }
                k++;
            }
        }
    }


    insert_num();
    system("cls");//清屏
    display();
}

void down_dir()
{
    //完成第一步
    int i,j;
    for (i=0; i<4; i++)
    {
        /*for (j=3; j>0;)
        {
            if (_array[j][i] == _array[j-1][i])
            {
                _array[j][i] = _array[j][i] + _array[j-1][i];
                _array[j-1][i] = 0;
                j -= 2;
                continue;
            }
            j--;
        }*/
        int k = 0;
        int x = 0; 
        int y = 0;
        for (j=3; j>=0; j--)
        {
            if (k==_array[j][i] && k!=0)
            {
                _array[x][y] = 2*k;
                _array[j][i] = 0;
                k = 0;
                continue;
            }
            if (_array[j][i]!=0)
            {
                k = _array[j][i];
                x = j;
                y = i;
            }
        }
    }

    for (i=0; i<4; i++)
    {
        int k = 3;
        for (j=3; j>=0; j--)
        {
            if (_array[j][i])
            {
                if (k != j)
                {
                    _array[k][i] = _array[j][i];
                    _array[j][i] = 0;
                }
                k--;
            }
        }
    }

    insert_num();
    system("cls");//清屏
    display();
}


void left_dir()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        int k = 0;
        int x = 0; 
        int y = 0;
        for (j=0; j<4; j++)
        {
            if (k==_array[i][j] && k!=0)
            {
                _array[x][y] = 2*k;
                _array[i][j] = 0;
                k = 0;
                continue;
            }
            if (_array[i][j]!=0)
            {
                k = _array[i][j];
                x = i;
                y = j;
            }
        }

    }

    for (i=0; i<4; i++)
    {
        int k = 0;
        for (j=0; j<4; j++)
        {
            if (_array[i][j])
            {
                if (k != j)
                {
                    _array[i][k] = _array[i][j];
                    _array[i][j] = 0;
                }
                k++;
            }
        }
    }

    insert_num();
    system("cls");//清屏
    display();
}


void right_dir()
{
    //完成第一步
    int i,j;
    for (i=0; i<4; i++)
    {
        int k = 0;
        int x = 0; 
        int y = 0;
        for (j=3; j>=0; j--)
        {
            if (k==_array[i][j] && k!=0)
            {
                _array[x][y] = 2*k;
                _array[i][j] = 0;
                k = 0;
                continue;
            }
            if (_array[i][j]!=0)
            {
                k = _array[i][j];
                x = i;
                y = j;
            }
        }
    }

    for (i=0; i<4; i++)
    {
        int k = 3;
        for (j=3; j>=0; j--)
        {
            if (_array[i][j])
            {
                if (k != j)
                {
                    _array[i][k] = _array[i][j];
                    _array[i][j] = 0;
                }
                k--;
            }
        }
    }

    insert_num();
    system("cls");//清屏
    display();
}
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////游戏结束////////////////////////////////////////////////////////////
//判断游戏结束
//将求解最大值和判断2048糅合在一起
bool iswin()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        for (j=0; j<4; j++)
        {
            if (_array[i][j] == 2048)
            {
                return true;
            }
        }
    }
    return false;
}


//构造函数can_up...,不能改变全局变量的值
//只需要两个方向，水平或者垂直；
bool can_ver()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        int k = 0;
        for (j=0; j<4; j++)
        {
            if (k==_array[j][i] && k!=0)
            {
                return true;
            }
            if (_array[j][i]!=0)
            {
                k = _array[j][i];
            }
        }
    }
    return false;
}

bool can_hor()
{
    int i,j;
    for (i=0; i<4; i++)
    {
        int k = 0;
        for (j=3; j>=0; j--)
        {
            if (k==_array[i][j] && k!=0)
            {
                return true;
            }
            if (_array[i][j]!=0)
            {
                k = _array[i][j];
            }
        }
    }
    return false;
}

//怎么做到提前预判已经不能左右移动了
bool islose()
{
    int k = 0;
    zero_num(&k);
    if (k>0)
    {
        return false;
    }
    if (can_ver() || can_hor())
    {
        return false;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////



int main()
{
    new_game();
    int dir = 0;
    while(1)
    {
        if (iswin())
        {
            cout<<"you win"<<endl;
            break;
        }
        if (islose())
        {
            cout<<"you lose"<<endl;
            break;
        }
        dir = get_direction();
        switch(dir)
        {
        case 1: up_dir();break;
        case 2: down_dir();break;
        case 3: left_dir();break;
        case 4: right_dir();break;
        default:break;
        }
    }

    system("pause");
    return 0;
}