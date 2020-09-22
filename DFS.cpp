#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
typedef long UINT64; 
typedef struct
{
	char x; //λ�� x ��λ�� y �ϵ����ֻ�λ
	char y; //���� x �� 0 ���ڵ�λ��
} EP_MOVE;

#define SIZE 3 //8�������⣬�����ϱ�����Ҳ�ɽ��15�������⣬
#define NUM SIZE * SIZE //�� move_gen��Ҫ���ܶ��޸ģ������ʼ�ͽ���״̬�Ĳ��ֺ�check_inputҲҪ�޸�
#define MAX_NODE 1000000
#define MAX_DEP 100
#define XCHG(a, b) { a=a + b; b=a - b; a=a - b; } 
#define TRANS(a, b)
/*{ long iii; (b)=0; for(iii=0; iii < NUM; iii++) (b)=((b) << 4) + a[iii]; }*/ 
//������ a ת��Ϊһ��64 λ������ b 
#define RTRANS(a,b){long iii; UINT64 ttt=(a); for(iii=NUM-1;iii>=0;iii--){b[iii]=ttt & 0xf;ttt>>=4;}}

//��һ�� 64 λ���� a ת��Ϊ���� b

typedef struct EP_NODE_Tag
{
	UINT64 v; //����״̬��ÿ������ռ4��������λ,�ɽ��16��������
	struct EP_NODE_Tag *prev; //	���ڵ�
	struct EP_NODE_Tag *small, *big;
}EP_NODE;
EP_NODE m_ar[MAX_NODE];
EP_NODE *m_root;
long m_depth; //�������
EP_NODE m_out[MAX_DEP]; //���·��

long move_gen(EP_NODE *node, EP_MOVE *move)
{
	long pz; //0	��λ��
	UINT64 t=0xf;
	for(pz=NUM - 1; pz >= 0; pz--)
	{
		if((node->v & t) == 0)
		{ break; //	�ҵ� 0 ��λ��
		}
	t<<=4;
	}
	switch(pz)
	{
		case 0: move[0].x=0;
				move[0].y=1;
				move[1].x=0;
				move[1].y=3; 
				return 2;
		case 1: move[0].x=1;
				move[0].y=0;
				move[1].x=1;
				move[1].y=2;
				move[2].x=1;
				move[2].y=4; 
				return 3;
		case 2: move[0].x=2;
				move[0].y=1;
				move[1].x=2;
				move[1].y=5;
		case 3: move[0].x=3;
				move[0].y=0;
				move[1].x=3;
				move[1].y=6;
				move[2].x=3;
				move[2].y=4; 
				return 3;
		case 4: move[0].x=4;
				move[0].y=1;
				move[1].x=4;
				move[1].y=3;
				move[2].x=4;
				move[2].y=5;
				move[3].x=4;
				move[3].y=7; 
				return 4;
		case 5: move[0].x=5;
				move[0].y=2;
				move[1].x=5;
				move[2].x=5;
				move[2].y=8; return 3;
		case 6: move[0].x=6;
				move[0].y=3;
				move[1].x=6;
				move[1].y=7; 
				return 2;
		case 7: move[0].x=7;
				move[0].y=6;
				move[1].x=7;
				move[1].y=4;
				move[2].x=7;
				move[2].y=8; 
				return 3;
		case 8: move[0].x=8;
				move[0].y=5;
				move[1].x=8;
				move[1].y=7;
	}
	return 0;
}

long mov(EP_NODE *n1, EP_MOVE *mv, EP_NODE *n2)
// ��һ����������һ����Ľ��
{
	char ss[NUM];
	RTRANS(n1->v, ss);
	XCHG(ss[mv->x], ss[mv->y]); 
	TRANS(ss, n2->v);
	return 0;
}

long add_node(EP_NODE *node, long r)
{
	EP_NODE *p=m_root; 
	EP_NODE *q; 
	while(p)
	{ 
		q=p;
		if(p->v == node->v) 
			return 0; 
		else if(node->v > p->v) 
			p=p->big;
		else if(node->v < p->v) 
			p=p->small;
	}
	m_ar[r].v=node->v; 
	m_ar[r].prev=node->prev; 
	m_ar[r].small=NULL; 
	m_ar[r].big=NULL; 
	if(node->v > q->v)
		q->big= &m_ar[r];
	else if(node->v < q->v)
		q->small= &m_ar[r];
	return 1;

}

/* �õ��ڵ�������� */
long get_node_depth(EP_NODE *node)
{ 
	long d=0; 
	while(node->prev)
	{ 
		d++;
		node=node->prev;
	}
	return d;
}

/* ����ֵ���ɹ������������ڵ������ڵ���������	(-1) ���޽⣭ (-2)*/ 
long bfs_search(char *begin, char *end)
{
	long h=0,r=1,c,i,j;
	EP_NODE l_end, node, *pnode;
	EP_MOVE mv[4]; // ÿ���������4���߷�
	TRANS(begin, m_ar[0].v); 
	TRANS(end, l_end.v); 
	m_ar[0].prev=NULL; 
	m_root=m_ar;
	m_root->small=NULL; 
	m_root->big=NULL;
	while((h < r) && (r < MAX_NODE - 4))
	{ 
		c=move_gen(&m_ar[h], mv); 
		for(i=0; i < c; i++)
		{ 
			mov(&m_ar[h], &mv[i], &node); 
			node.prev= &m_ar[h];
			if(node.v == l_end.v)
			{ 
				pnode= &node; j=0;
				while(pnode->prev)
				{
					m_out[j]=*pnode; j++;
					pnode=pnode->prev;
				}
				m_depth=j;
				return r;
			}
			if(add_node(&node, r)) 
				r++; //	ֻ�ܶ���ʷ�ڵ���û�е��½ڵ��������������ֻ�
		} 
		h++;
		printf("\rSearch...%9d/%d @ %d", h, r, get_node_depth(&m_ar[h]));
	}
	if(h == r)
		return -2;
	else
		return -1; 

}

long check_input(char *s, char a, long r)
{
	long i;
	for(i=0; i < r; i++)
	{ 
		if(s[i] == a - 0x30) return 0; } 
	return 1;
}

long check_possible(char *begin, char *end)
{ 
	char fs;
	long f1=0, f2=0; 
	long i, j;
	for(i=0; i < NUM; i++)
	{	
		fs=0;
		for(j=0; j < i; j++)
		{
			if((begin[i] != 0) && (begin[j] != 0) && (begin[j] < begin[i])) 
				fs++;
		}
		f1+=fs; fs=0;
		for(j=0; j < i; j++)
		{ 
			if((end[i] != 0) && (end[j] != 0) && (end[j] < end[i]))
				fs++;
		}
		f2+=fs;
		if((f1 && 1) == (f2 && 1)) return 1; 
		else return 0;
	}
}

void output(void)
{ 
	long i, j, k; 
	char ss[NUM];
	for(i=m_depth - 1; i >= 0; i--)
	{
		RTRANS(m_out[i].v, ss); 
		for(j=0; j < SIZE; j++)
		{ 
			for(k=0; k < SIZE; k++)
				printf("%2d",ss[SIZE * j+k]);
		printf("\n");
		}
		printf("\n");
	}
}


int main(void)
{ 
	char s1[NUM]; 
	char s2[NUM]; 
	long r;
	char a;
	printf("�����뿪ʼ״̬ :"); 
	r=0;
	while(r < NUM)
	{ 
		a=getchar();
		if(a >= 0x30 && a < 0x39 && check_input(s1, a, r))
		{ 
			s1[r++]=a - 0x30;
		}
	}
	printf("\n���������״̬ :"); 
	r=0;
	while(r<NUM)
	{ 
		a=getchar();
		if(a >= 0x30 && a < 0x39 && check_input(s2, a, r))
		{ 
			s2[r++]=a - 0x30;
		}
	}

	printf("\n"); 
	if(check_possible(s1, s2))
	{ 
		r=bfs_search(s1, s2); 
		printf("\n");
		if(r >= 0)

		{ 
			printf("�������=%d,���еķ�ʽ =%ld\n", m_depth, r); 
			output();
		}
		else if(r == -1)
		{ 
			printf("û���ҵ�·�� .\n");
		}

		else if(r == -2)
		{
			printf("����״̬�任û��·������\n");
		}
		else
		{
			printf("��ȷ���Ĵ��� .\n");
		}
	}
	else
	{ 
		printf("�����������ƶ�!\n");
	}
	return 0;
}
