#include<bits/stdc++.h>

using namespace std;
int dis[9][9] = {   //��ǰλ�ú�Ŀ��λ�ü�������پ���
        {0, 1, 2, 1, 2, 3, 2, 3, 4},    //���Ӹõ㵽����8������Ҫ�ƶ��Ĳ���
        {1, 0, 1, 2, 1, 2, 3, 2, 3},
        {2, 1, 0, 3, 2, 1, 4, 3, 2},
        {1, 2, 3, 0, 1, 2, 1, 2, 3},
        {2, 1, 2, 1, 0, 1, 2, 1, 2},
        {3, 2, 1, 2, 1, 0, 3, 2, 1},
        {2, 3, 4, 1, 2, 3, 0, 1, 2},
        {3, 2, 3, 2, 1, 2, 1, 0, 1},
        {4, 3, 2, 3, 2, 1, 2, 1, 0}
};
int yuan[9] = {4, 0, 1, 2, 5, 8, 7, 6, 3};      //ÿ�����ֵ�Ŀ��״̬��λ��
int chu[3][3];  //�洢��ǰ״̬
char k;
int sx, sy;
int ax[4] = {0, -1, 1, 0};
int ay[4] = {1, 0, 0, -1}; //����������һ��Ҫ�Գ�д��ʹ����ʱ���᷵����һ״̬
bool flag;

int h() {
    int ans = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            if (chu[i][j] == 0) continue;   //������0
            ans += dis[yuan[chu[i][j]]][i * 3 + j]; //i*3+j��ʾ��������λ��
        }
    return ans;
}

void dfs(int ceng, int dep, int f, int x, int y) { //f��ʾ��һ��ת�Ƶķ���
    int nx, ny;
    if (ceng == dep) {  //����ѵ���Ԥ�ڲ���
        if (!h()) flag = 1; //����ﵽ��Ŀ��״̬
        return;
    }
    for (int i = 0; i < 4; i++) {
        nx = x + ax[i];
        ny = y + ay[i];

        if (nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;//����
        if (i + f == 3)  continue;//����᷵����һ��״̬��������������ط�Ϊ��֦��Ϊ��i+f == 3ʱ�������ƶ����ɣ�һ���������ߣ�Ҳ���ظ��ˣ�����Ҫ��ȥ�������
        swap(chu[nx][ny], chu[x][y]);
        if (ceng + h() <= dep)//�������������ᳬ��Ԥ�ڣ���ֱ�ӷ���
            dfs(ceng + 1, dep, i, nx, ny);
        if (flag) return;//�ҵ����ֱ�ӷ���
        swap(chu[nx][ny], chu[x][y]);//����
    }
}

int main() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> k;
            chu[i][j] = k - '0';
            if (k == '0') {
                sx = i;
                sy = j;//��ʼ0��λ��
            }
        }
    }
    if (!h()) {     //���أ����һ��ʼ�ʹﵽĿ�ֱ꣬�ӽ���
        cout << "���·��Ϊ��" << 0;
    }
    flag = 0;
    int maxdep;     //Ԥ�����
    for (maxdep = 1;; maxdep++) {   //һ��һ�����
        dfs(0, maxdep, -1, sx, sy); //0��ʾ��0�㿪ʼ��һ��ʼû�з������Դ���-1
        if (flag) {     //�ҵ���
            cout << "���·��Ϊ��" << maxdep << endl;
            break;
        }
    }
    return 0;
}
