#include<bits/stdc++.h>

using namespace std;
int dis[9][9] = {   //当前位置和目标位置间的曼哈顿距离
        {0, 1, 2, 1, 2, 3, 2, 3, 4},    //即从该点到其它8个点需要移动的步数
        {1, 0, 1, 2, 1, 2, 3, 2, 3},
        {2, 1, 0, 3, 2, 1, 4, 3, 2},
        {1, 2, 3, 0, 1, 2, 1, 2, 3},
        {2, 1, 2, 1, 0, 1, 2, 1, 2},
        {3, 2, 1, 2, 1, 0, 3, 2, 1},
        {2, 3, 4, 1, 2, 3, 0, 1, 2},
        {3, 2, 3, 2, 1, 2, 1, 0, 1},
        {4, 3, 2, 3, 2, 1, 2, 1, 0}
};
int yuan[9] = {4, 0, 1, 2, 5, 8, 7, 6, 3};      //每个数字的目标状态的位置
int chu[3][3];  //存储当前状态
char k;
int sx, sy;
int ax[4] = {0, -1, 1, 0};
int ay[4] = {1, 0, 0, -1}; //这两个数组一定要对称写，使搜索时不会返回上一状态
bool flag;

int h() {
    int ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (chu[i][j] == 0) continue;   //不考虑0
            ans += dis[yuan[chu[i][j]]][i * 3 + j]; //i*3+j表示数字现在位置
        }
    return ans;
}

void dfs(int ceng, int dep, int f, int x, int y) { //f表示上一次转移的方向
    int nx, ny;
    if (ceng == dep) {  //如果搜到了预期层数
        if (!h()) flag = 1; //如果达到了目标状态
        return;
    }
    for (int i = 0; i < 4; i++) {
        nx = x + ax[i];
        ny = y + ay[i];

        if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;//出界
        if (i + f == 3)  continue;//如果会返回上一个状态，就跳过，这个地方为剪枝因为当i+f == 3时，根据移动规律，一定会往回走，也就重复了，所以要舍去这种情况
        swap(chu[nx][ny], chu[x][y]);
        if (ceng + h() <= dep)//如果最优情况都会超出预期，就直接返回
            dfs(ceng + 1, dep, i, nx, ny);
        if (flag) return;//找到解就直接返回
        swap(chu[nx][ny], chu[x][y]);//回溯
    }
}

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> k;
            chu[i][j] = k - '0';
            if (k == '0') {
                sx = i;
                sy = j;//初始0的位置
            }
        }
    }
    if (!h()) {     //判特，如果一开始就达到目标，直接结束
        cout << "最短路径为：" << 0;
    }
    flag = 0;
    int maxdep;     //预期深度
    for (maxdep = 1;; maxdep++) {   //一层一层地搜
        dfs(0, maxdep, -1, sx, sy); //0表示从0层开始，一开始没有方向，所以传入-1
        if (flag) {     //找到解
            cout << "最短路径为：" << maxdep << endl;
            break;
        }
    }
    return 0;
}
