#include <iostream>
#include <vector>
#include <fstream>

#define maxint INT_MAX
#define inf INT_MAX

using namespace std;

template <class Type>
void Prim(int n, vector<vector<Type>> c)
{
    Type lowcost[n+1];
    int closest[n+1];
    bool s[n+1];
    s[1] = true;
    for (int i = 2; i <= n; i++)
    {
        lowcost[i] = c[1][i];
        closest[i] = 1;
        s[i] = false;
    }
    for (int i = 1; i < n; i++)
    {
        Type min = inf;
        int j = 1;
        for (int k = 2; k <= n; k++)
        {
            if ((lowcost[k] < min) && (!s[k]))
            {
                min = lowcost[k];
                j = k;
            }
        }
        cout << j << "  " << closest[j] << endl;
        s[j] = true;
        for (int k = 2; k <= n; k++)
        {
            if ((c[j][k] < lowcost[k]) && (!s[k]))
            {
                lowcost[k] = c[j][k];
                closest[k] = j;
            }
        }
        
    }
    
}

int main() 
{
    int buffer;
    vector<int> temp;
    vector<vector<int>> c(10, vector<int>(10, 0));
    ifstream readFile("data.txt");
    if (!readFile.is_open()) 
    { 
        cout << "文件打开失败" << endl;
        return -1;
    } 
    while (!readFile.eof())
    {
        readFile >> buffer;
        temp.push_back(buffer);
    }
    readFile.close();
    for (int i = 1, k = 0; i <= 6; i++)
    {
        for (int j = 1; j <= 6; j++)
            c[i][j] = temp[k++];
    }
    Prim(6, c);
    return 0;
}