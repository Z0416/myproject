#include<iostream>
#include<map>
#include<queue>
using namespace std;

//队列数据结构 
queue<int>Q;
//标记数组 
map<int, int>isVisited;
//记录到这种状态的步数
map<int, int>step;

//可以在上下左右四个方向上移动 
int direction[4][2] = {-1,0,0,1,1,0,0,-1};
//初始状态矩阵 
int startState[3][3];
//目标状态矩阵 
int resultState[3][3];
//初始状态矩阵转为数字 
int startStateToNumber = 0;
//目标状态转为数字 
int resultStateToNumber = 0;
//矩阵行下标 
int rowIndex = 0;
//矩阵列下标
int columnIndex = 0;
//最小步数
int totalStep = 0; 

//输入矩阵状态并且转为数字 
int inputStateAndToNumber(int matrix[3][3]) {
	int temp = 0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			cin>>matrix[i][j];
			//将输入的矩阵转换为九位数 
			temp = temp*10 + matrix[i][j];
		}
	}
	//返回该九位数 
	return temp;
}

//判断某个方向是否可走
//返回1是可走，返回0是不可走
//dir是传的是数组下标     看111行 
bool isReachable(int currentState, int dir) {
	//将数字装换为3*3矩阵方可判断某个方向是否可走 
	for(int i=2; i>=0; i--) {
		for(int j=2; j>=0; j--) {
		 	startState[i][j] =  currentState % 10;
		 	currentState = currentState / 10;
		 	//找到空格位置，即3*3矩阵中数值为0的元素的位置 
		 	if(startState[i][j]==0) {
		 		//记录行下标和列下标 
		 		rowIndex = i;
		 		columnIndex = j;
			}
		}	
	}
	//判断哪个方向能走
	if((dir==0&&rowIndex==0) || (dir==1&&columnIndex==2) || (dir==2&&rowIndex==2) || (dir==3&&columnIndex==0)) {
		return 0;
	} 
	return 1;
} 

//返回从当前状态可以到达的某个状态(一个九位数) 
int moveToState(int currentState, int reachableState) {
	int temp = 0;
	//修改下标参数，到达某一状态 
	int reachableStateRowIndex = rowIndex + direction[reachableState][0];
	int reachableStateColumnIndex = columnIndex + direction[reachableState][1];
	//交换0和可到达状态上的数据 
	startState[rowIndex][columnIndex] = startState[reachableStateRowIndex][reachableStateColumnIndex];
	startState[reachableStateRowIndex][reachableStateColumnIndex] = 0;
	//将新的状态变换成九位数 
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			temp = temp*10 + startState[i][j];
		}
	}
	//返回该新的九位数 
	return temp;
}

//广度优先遍历，返回从开始状态走到目标状态的最小的步数
//参数为开始状态和目标状态的九位数 
int bfs(int startNumber, int resultNumber) {
	//初始状态入队 
	Q.push(startNumber);
	//已经访问过 
	isVisited[startNumber] = 1;
	//到这种状态的步数初始化为0 
	step[startNumber] = 0;
	//当队列中有数据时
	while(Q.size()) {
		int currentState, reachableState;
		//当前状态为队列队头元素 
		currentState = Q.front();
		//对头元素出队
		Q.pop();
		//如果当前状态为目标状态
		if(currentState==resultNumber) {
			//返回到该目标状态的步数
			return step[currentState];
		}
		//判断当前状态可到达的方向(判断该状态上下左右什么方向可到达)
		for(int i=0; i<4; i++) {
			//如果当前状态的某个方向可到达 
			if(isReachable(currentState, i)) {
				//到达该方向对应的状态 
				reachableState = moveToState(currentState, i);
				//如果该状态没被访问过 
				if(!isVisited[reachableState]) {
					//访问该状态 
					isVisited[reachableState] = 1;
					//currentState的步数加1 
					step[reachableState] = step[currentState] + 1;
					//将reachableState放入队列 
					Q.push(reachableState); 
				}
			}
		} 
	} 
} 
 

int main() {
	cout<<"-----------------"<<endl;
	cout<<"初始状态："<<endl; 
	cout<<"-----------------"<<endl;
	startStateToNumber = inputStateAndToNumber(startState);
	cout<<"-----------------"<<endl;
	cout<<"目标状态："<<endl;
	cout<<"-----------------"<<endl;
	resultStateToNumber = inputStateAndToNumber(resultState);
	cout<<"-----------------"<<endl;
	totalStep = bfs(startStateToNumber, resultStateToNumber);
	cout<<"需要的步数为："<<totalStep<<endl;
	cout<<"-----------------"<<endl;
}

