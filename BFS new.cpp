#include<iostream>
#include<map>
#include<queue>
using namespace std;

//�������ݽṹ 
queue<int>Q;
//������� 
map<int, int>isVisited;
//��¼������״̬�Ĳ���
map<int, int>step;

//���������������ĸ��������ƶ� 
int direction[4][2] = {-1,0,0,1,1,0,0,-1};
//��ʼ״̬���� 
int startState[3][3];
//Ŀ��״̬���� 
int resultState[3][3];
//��ʼ״̬����תΪ���� 
int startStateToNumber = 0;
//Ŀ��״̬תΪ���� 
int resultStateToNumber = 0;
//�������±� 
int rowIndex = 0;
//�������±�
int columnIndex = 0;
//��С����
int totalStep = 0; 

//�������״̬����תΪ���� 
int inputStateAndToNumber(int matrix[3][3]) {
	int temp = 0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			cin>>matrix[i][j];
			//������ľ���ת��Ϊ��λ�� 
			temp = temp*10 + matrix[i][j];
		}
	}
	//���ظþ�λ�� 
	return temp;
}

//�ж�ĳ�������Ƿ����
//����1�ǿ��ߣ�����0�ǲ�����
//dir�Ǵ����������±�     ��111�� 
bool isReachable(int currentState, int dir) {
	//������װ��Ϊ3*3���󷽿��ж�ĳ�������Ƿ���� 
	for(int i=2; i>=0; i--) {
		for(int j=2; j>=0; j--) {
		 	startState[i][j] =  currentState % 10;
		 	currentState = currentState / 10;
		 	//�ҵ��ո�λ�ã���3*3��������ֵΪ0��Ԫ�ص�λ�� 
		 	if(startState[i][j]==0) {
		 		//��¼���±�����±� 
		 		rowIndex = i;
		 		columnIndex = j;
			}
		}	
	}
	//�ж��ĸ���������
	if((dir==0&&rowIndex==0) || (dir==1&&columnIndex==2) || (dir==2&&rowIndex==2) || (dir==3&&columnIndex==0)) {
		return 0;
	} 
	return 1;
} 

//���شӵ�ǰ״̬���Ե����ĳ��״̬(һ����λ��) 
int moveToState(int currentState, int reachableState) {
	int temp = 0;
	//�޸��±����������ĳһ״̬ 
	int reachableStateRowIndex = rowIndex + direction[reachableState][0];
	int reachableStateColumnIndex = columnIndex + direction[reachableState][1];
	//����0�Ϳɵ���״̬�ϵ����� 
	startState[rowIndex][columnIndex] = startState[reachableStateRowIndex][reachableStateColumnIndex];
	startState[reachableStateRowIndex][reachableStateColumnIndex] = 0;
	//���µ�״̬�任�ɾ�λ�� 
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			temp = temp*10 + startState[i][j];
		}
	}
	//���ظ��µľ�λ�� 
	return temp;
}

//������ȱ��������شӿ�ʼ״̬�ߵ�Ŀ��״̬����С�Ĳ���
//����Ϊ��ʼ״̬��Ŀ��״̬�ľ�λ�� 
int bfs(int startNumber, int resultNumber) {
	//��ʼ״̬��� 
	Q.push(startNumber);
	//�Ѿ����ʹ� 
	isVisited[startNumber] = 1;
	//������״̬�Ĳ�����ʼ��Ϊ0 
	step[startNumber] = 0;
	//��������������ʱ
	while(Q.size()) {
		int currentState, reachableState;
		//��ǰ״̬Ϊ���ж�ͷԪ�� 
		currentState = Q.front();
		//��ͷԪ�س���
		Q.pop();
		//�����ǰ״̬ΪĿ��״̬
		if(currentState==resultNumber) {
			//���ص���Ŀ��״̬�Ĳ���
			return step[currentState];
		}
		//�жϵ�ǰ״̬�ɵ���ķ���(�жϸ�״̬��������ʲô����ɵ���)
		for(int i=0; i<4; i++) {
			//�����ǰ״̬��ĳ������ɵ��� 
			if(isReachable(currentState, i)) {
				//����÷����Ӧ��״̬ 
				reachableState = moveToState(currentState, i);
				//�����״̬û�����ʹ� 
				if(!isVisited[reachableState]) {
					//���ʸ�״̬ 
					isVisited[reachableState] = 1;
					//currentState�Ĳ�����1 
					step[reachableState] = step[currentState] + 1;
					//��reachableState������� 
					Q.push(reachableState); 
				}
			}
		} 
	} 
} 
 

int main() {
	cout<<"-----------------"<<endl;
	cout<<"��ʼ״̬��"<<endl; 
	cout<<"-----------------"<<endl;
	startStateToNumber = inputStateAndToNumber(startState);
	cout<<"-----------------"<<endl;
	cout<<"Ŀ��״̬��"<<endl;
	cout<<"-----------------"<<endl;
	resultStateToNumber = inputStateAndToNumber(resultState);
	cout<<"-----------------"<<endl;
	totalStep = bfs(startStateToNumber, resultStateToNumber);
	cout<<"��Ҫ�Ĳ���Ϊ��"<<totalStep<<endl;
	cout<<"-----------------"<<endl;
}

