#include <iostream>
#include <vector>
#include <queue>

using namespace std;


class Picture {
private:

    int **pictureArray = NULL;
    int hValue;
    int gValue;
    int fValue;
public:
    Picture *parente=NULL;
    int zeroRow, zeroColumn;
    static int rowSize, columnSize;

    static void setSize(int row, int column) {
        rowSize = row;
        columnSize = column;
    }

    Picture() {
        if (rowSize == 0 || columnSize == 0)
            throw "no init";
        pictureArray = new int *[rowSize];
        for (int i = 0; i < rowSize; ++i) {
            pictureArray[i] = new int[columnSize];
        }
        hValue = 0;
        gValue = 0;
        fValue = 0;
        setArray();
    }

    Picture(const Picture &sourse) {
        zeroRow = sourse.getZeroRow();
        zeroColumn = sourse.getZeroColumn();
        parente = sourse.parente;
        pictureArray = new int *[rowSize];
        for (int i = 0; i < rowSize; ++i) {
            pictureArray[i] = new int[columnSize];
        }
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < columnSize; ++j) {
                pictureArray[i][j] = sourse.getPicturePoint()[i][j];
            }
    }

    ~Picture() {
        delete[] pictureArray;
    }

    bool operator==(const Picture &source) const {
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < columnSize; ++j) {
                if (pictureArray[i][j] != source.getPicturePoint()[i][j])
                    return false;
            }
        return true;
    }

    void setArray() {
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < columnSize; ++j) {
                cin >> pictureArray[i][j];
                if (pictureArray[i][j] == 0) {
                    zeroRow = i;
                    zeroColumn = j;
                }
            }
        }
    }


    /*
    * 设置启发式函数的值
    */
    void setHValue(const Picture &endPicture) {
        int result = 0;
        int **tempPicture = endPicture.getPicturePoint();
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < columnSize; ++j) {
                if (pictureArray[i][j] != tempPicture[i][j])
                    ++result;
            }
        hValue = result;
    }

    void updateFvalue() {
        fValue = hValue + gValue;
    }

    void setGvalue(int value) {
        gValue = value;
    }

    int **getPicturePoint() const {
        return pictureArray;
    }

    int getFValue() const {
        return fValue;
    }

    int getGvalue() const {
        return gValue;
    }

    int getZeroRow() const {
        return zeroRow;
    }

    int getZeroColumn() const {
        return zeroColumn;
    }

    void showPicture() const {
        for (int i = 0; i < rowSize; ++i) {
            for (int j = 0; j < columnSize - 1; ++j) {
                cout << pictureArray[i][j] << ' ';
            }
            cout << pictureArray[i][columnSize - 1] << endl;
        }
        cout<<endl;
    }
};


int inVector(vector<Picture *> const &theVector, Picture const &element) {
    for (int i = 0; i < theVector.size(); ++i)
        if (element == *theVector[i])
            return i;
    return -1;
}

void deleteElement(vector<Picture *> &theVector, const Picture *element) {
    for (int i = 0; i < theVector.size(); ++i) {
        if (element == theVector[i]) {
            theVector.erase(theVector.begin() + i);
            return;
        }
    }
}

struct cmp {
    bool operator()(const Picture *a, const Picture *b) {
        return a->getFValue() > b->getFValue();
    }
};

bool Astart(Picture *&beginPicture, Picture *&endPicture) {
    priority_queue<Picture *, vector<Picture *>, cmp> openQueue;
    vector<Picture *> openTable, closeTable;
    beginPicture->setHValue(*endPicture);
    beginPicture->updateFvalue();
    openQueue.push(beginPicture);
    openTable.push_back(beginPicture);
    int move[4][2] = { {-1, 0},
                      {1,  0},
                      {0,  -1},
                      {0,  1}};
    while (!openQueue.empty()) {
        Picture *bestPicture = openQueue.top();
        if (*bestPicture == *endPicture) {
            delete endPicture;
            endPicture = bestPicture;
            return true;
        }
        closeTable.push_back(bestPicture);
        openQueue.pop();
        deleteElement(openTable, bestPicture);
        //向上下左右四个方向进行拓展
        for (int i = 0; i < 4; ++i) {
            int row = bestPicture->zeroRow + move[i][0];
            int column = bestPicture->zeroColumn + move[i][1];
            if (row >= 0 && row < Picture::rowSize && column >= 0 && column < Picture::columnSize) {
                Picture *successor = new Picture(*bestPicture);
                int **theArray = successor->getPicturePoint();
                theArray[successor->zeroRow][successor->zeroColumn] = theArray[row][column];
                theArray[row][column] = 0;
                successor->zeroRow = row;
                successor->zeroColumn = column;
                successor->parente = bestPicture;
                successor->setGvalue(bestPicture->getGvalue() + 1);
                int flag = inVector(openTable, *successor);
                if (flag >= 0) {
                    if (successor->getGvalue() < openTable[flag]->getGvalue()) {
                        openTable[flag]->setGvalue(successor->getGvalue());
                        openTable[flag]->parente = bestPicture;
                        openTable[flag]->updateFvalue();
                        delete successor;
                    }
                }
                flag = inVector(closeTable, *successor);
                if (flag >= 0) {
                    if (successor->getGvalue() < closeTable[flag]->getGvalue()) {
                        closeTable[flag]->setGvalue(successor->getGvalue());
                        closeTable[flag]->parente = bestPicture;
                        closeTable[flag]->updateFvalue();
                        delete successor;
                        openQueue.push(closeTable[flag]);
                        openTable.push_back(closeTable[flag]);
                        closeTable.erase(closeTable.begin() + flag);
                    }
                } else {
                    successor->setHValue(*endPicture);
                    successor->updateFvalue();
                    openQueue.push(successor);
                    openTable.push_back(successor);
                }
            }
        }
    }
    return false;
}

int Picture::rowSize = 0;
int Picture::columnSize = 0;

void showResult(const Picture *endPicture) {
    if (endPicture != NULL) {
        showResult(endPicture->parente);
        endPicture->showPicture();
    }
}

int main() {
    int rowSize = 0, columnSize = 0;
    cout << "Please input the size of the Picture" << endl;
    cout << "Input the size of row" << endl;
    cin >> rowSize;
    cout << "Input the size of column" << endl;
    cin >> columnSize;
    Picture::setSize(rowSize, columnSize);
    cout << "Please input the begin Picture" << endl;
    Picture *beginPicture = new Picture();
    cout << "Please input the end Picture" << endl;
    Picture *endPicture = new Picture();
    if (Astart(beginPicture, endPicture)) {
        cout<<"The Route is as following"<<endl;
        showResult(endPicture);
        cout << "All steps is " << endPicture->getGvalue() << endl;
    } else{
        cout<<"This A start algorithm can not find the answer"<<endl;
    }

}
