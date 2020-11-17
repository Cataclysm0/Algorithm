#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

static int maxint = 32767;

template <class Type>
void Dijkstra(int n, int v, vector<Type> &dist, vector<int> &prev, vector<vector<Type>> &c)
{
    bool s[maxint];
    for (int i = 1; i <= n; i++)
    {
        dist[i] = c[v][i];
        s[i] = false;
        if (dist[i] == maxint)
            prev[i] = 0;
        else
            prev[i] = v;
    }
    dist[v] = 0;
    s[v] = true;
    for (int i = 1; i < n; i++)
    {
        int temp = maxint;
        int u = v;
        for (int j = 1; j <= n; j++)
            if (!s[j] && (dist[j] < temp))
            {
                u = j;
                temp = dist[j];
            }
        s[u] = true;
        for (int j = 1; j <= n; j++)
        {
            if ((!s[j]) && (c[u][j] < maxint))
            {
                Type newdist = dist[u] + c[u][j];
                if (newdist < dist[j])
                {
                    dist[j] = newdist;
                    prev[j] = u;
                }
            }
        }
    }
}

void Traceback(int v, int i, vector<int> prev)
{
    if (v == i)
    {
        cout << i;
        return;
    }
    Traceback(v, prev[i], prev);
    cout << "->" << i;
}

int main()
{
    int buffer;
    vector<int> temp;
    vector<int> dist(10,0);
    vector<int> prev(10,0);
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
    for (int i = 1, k = 0; i <= 5; i++)
    {
        for (int j = 1; j <= 5; j++)
            c[i][j] = temp[k++];
    }
    Dijkstra(5, 1, dist, prev, c);
    for (int i = 2; i <= 5; i++)
    {
        cout << "源点到 " << i << " 的最短路径: ";
        Traceback(1, i, prev);
        cout << "\t最短路径长度为：" << dist[i];
        cout << endl;
    }
    return 0;
}
