#include<iostream>
#include<ctime>
#include<iomanip>
#include<easyx.h>
using namespace std;
#define ROW 10
#define COL 10
#define MineNum 10
void show(int map[][COL]);
void init(int map[][COL]);
int main()
{
	int map[ROW][COL] = {0};//地图
	init(map);
	show(map);
	return 0;
}
void show(int map[][COL])
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout <<fixed<<setw(2)<<map[i][j];
		}
		cout << endl;
	}
}
void init(int map[][COL])
{
	srand((unsigned int)time(NULL));
	//设置雷
	for (int i = 0; i < 10; ) {
		srand((unsigned int)time(NULL));
		int r = rand() % ROW;
		int c = rand() % COL;
		if (map[r][c] == 0) {
			map[r][c] = -1;
			i++;
		}
		
	}
	//雷周围的九宫格数据+1
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[i][j] == -1)
			{
				for (int r = i - 1; r <= i + 1; r++) {
					for (int c = j - 1; c <= j + 1; c++) {
						if ((r>=0&&r<ROW&&c>=0&&c<COL) && map[r][c] != -1)
						{
							map[r][c]++;
						}
					}
				}
			}
		}
		
	}
}