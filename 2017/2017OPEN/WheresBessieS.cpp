#include <bits/stdc++.h>

using namespace std;

struct p{
    int x1, x2, y1, y2;
} PCL[100000];

bool Vis[25][25];
int N, Counter, Answer;
char Photo[25][25];

void Dfs(char Color, int x, int y, int x1, int y1, int x2, int y2){
    if (x < x1 || x > x2 || y < y1 || y > y2 || Vis[x][y] || Photo[x][y] != Color)
        return;
    Vis[x][y] = true;
    Dfs(Color, x + 1, y, x1, y1, x2, y2);
    Dfs(Color, x - 1, y, x1, y1, x2, y2);
    Dfs(Color, x, y + 1, x1, y1, x2, y2);
    Dfs(Color, x, y - 1, x1, y1, x2, y2);
}

bool IsPCL(int x1, int y1, int x2, int y2){
    char Color1 = ' ', Color2 = ' ';
    int ConnectedBlock1 = 0, ConnectedBlock2 = 0;
    memset(Vis, 0, sizeof(Vis));
    for (int i = x1; i <= x2; i++)
        for (int j = y1; j <= y2; j++){
            if (Color1 == ' ')
                Color1 = Photo[i][j];
            else if (Color2 == ' ')
                Color2 = Photo[i][j];
            if (Color1 != ' ' && Color2 != ' ' && Photo[i][j] != Color1 && Photo[i][j] != Color2)
                return false;
            if (ConnectedBlock1 > 1 && ConnectedBlock2 > 1)
                return false;
            if (Photo[i][j] == Color1 && !Vis[i][j])
                ConnectedBlock1++, Dfs(Color1, i, j, x1, y1, x2, y2);
            else if (Photo[i][j] == Color2 && !Vis[i][j])
                ConnectedBlock2++, Dfs(Color2, i, j, x1, y1, x2, y2);
        }
    if (ConnectedBlock1 == 1 && ConnectedBlock2 > 1 || ConnectedBlock1 > 1 && ConnectedBlock2 == 1)
        return true;
    return false;
}

bool Repetition(int x){
    for (int i = 1; i <= Counter; i++)
        if (i != x && PCL[x].x1 >= PCL[i].x1 && PCL[x].x2 <= PCL[i].x2 && PCL[x].y1 >= PCL[i].y1 && PCL[x].y2 <= PCL[i].y2)
            return false;
    return true;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> Photo[i] + 1;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            for (int k = i; k <= N; k++)
                for (int l = j; l <= N; l++)
                    if (IsPCL(i, j, k, l))
                        Counter++, PCL[Counter].x1 = i, PCL[Counter].x2 = k, PCL[Counter].y1 = j, PCL[Counter].y2 = l;

    for (int i = 1; i <= Counter; i++)
        if (Repetition(i))
            Answer++;
    
    cout << Answer << endl;
    return 0;
}

/*
4                                                                                          
ABBC
BBBC
AABB
ABBC

My output: 5
Correct : 2
*/