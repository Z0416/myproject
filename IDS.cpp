/*
    qwerta
    P1379 ����������
    Accepted
    100
    ���� C++��1.06KB
    �ύʱ�� 2018-10-01 21:50:56
    ��ʱ/�ڴ�
    2106ms, 816KB
*/
/*
���м��״̬��¼�ѾŹ������±�ţ�
1 2 3
4 5 6
7 8 9
*/
#include<iostream>
#include<cstdlib>
#include<cstdio>
using namespace std;
#define LL long long
int dep;//�������
int a[13];//��״̬��֮������
int chai(int x)//��
{
    int ret;//��һ��0���Ķ�
    for(register int i=9;i>=1;--i)
    {
        if(x%10==0)ret=i;
        a[i]=x%10;
        x/=10;
    }
    return ret;
}
LL ans=123804765;//Ŀ��̬
LL sub()//�Ѳ𿪵�ѹ����
{
    LL x=0;
    for(register int i=1;i<=9;++i)
    x=x*10+a[i];
    return x;
}
void dfs(int k,int d,int bef)// k:0���Ķ� d����ǰ��� bef:��һ�εĲ���
{
    if(sub()==ans){cout<<d-1;exit(0);}//�ҵ��˾����
    if(d>dep)return;//�����޶������
    //mvup �ѿո�������
    if(k>3&&bef!=1){swap(a[k-3],a[k]);dfs(k-3,d+1,3);swap(a[k-3],a[k]);}
    //mvdown �ѿո�����
    if(k<7&&bef!=3){swap(a[k+3],a[k]);dfs(k+3,d+1,1);swap(a[k+3],a[k]);}
    //mvleft ����
    if(k%3!=1&&bef!=2){swap(a[k-1],a[k]);dfs(k-1,d+1,4);swap(a[k-1],a[k]);}
    //mvright ����
    if(k%3!=0&&bef!=4){swap(a[k+1],a[k]);dfs(k+1,d+1,2);swap(a[k+1],a[k]);}
}
int main()
{
    //freopen("a.in","r",stdin);
    LL x;
    cin>>x;
    dep=0;
    while(1)
    {
        ++dep;//��������
        int k=chai(x);
        dfs(k,1,0);
    }
    return 0;
}