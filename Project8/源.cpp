#include<iostream>
#include<iomanip>
#include<easyx.h>
#include<ctime>
using namespace std;
#define ROW 10
#define COL 10
#define MineNum 10
void show(int map[][COL]);
void init(int map[][COL]);
void draw(int map[][COL], IMAGE img[]);
void mouse(int map[][COL]);
void openNull(int map[][COL], int row, int col);
void judge(int map[][COL], int row, int col);
bool isOver = false;//点到雷结束
int main()
{

	initgraph(1300, 1300, EX_SHOWCONSOLE);
	IMAGE img[12];
	int map[ROW][COL] = { 0 };//地图
	init(map);
	loadimage(img + 0, "./images/0.jpg", 130, 130);
	loadimage(img + 1, "./images/1.jpg", 130, 130);
	loadimage(img + 2, "./images/2.jpg", 130, 130);
	loadimage(img + 3, "./images/3.jpg", 130, 130);
	loadimage(img + 4, "./images/4.jpg", 130, 130);
	loadimage(img + 5, "./images/5.jpg", 130, 130);
	loadimage(img + 6, "./images/6.jpg", 130, 130);
	loadimage(img + 7, "./images/7.jpg", 130, 130);
	loadimage(img + 8, "./images/8.jpg", 130, 130);
	loadimage(img + 9, "./images/9.jpg", 130, 130);
	loadimage(img + 10, "./images/10.jpg", 130, 130);
	loadimage(img + 11, "./images/11.jpg", 130, 130);
	draw(map, img);
	while (true)
	{
		mouse(map);
		draw(map, img);
		
		if (isOver)
		{
			int ret=MessageBox(GetHWnd(), "游戏结束，再来一把","hint", MB_OKCANCEL);
			if (ret == IDOK)
			{
				init(map);
				show(map);
				isOver = false;
			}

			else if(ret==IDCANCEL)
			{
				exit(666);
			}
		}
	
	}
	
	show(map);
	getchar();
	return 0;
}
void show(int map[][COL])
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << fixed<<setw(2)<<map[i][j];
		}
		cout << endl;
	}
}
void init(int map[][COL])
{
	memset(map, 0, ROW * COL * sizeof(int));
	srand((unsigned int)time(NULL));
	//设置雷
	for (int i = 0; i < 10; ) {
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
						if ((r >= 0 && r < ROW && c >= 0 && c < COL) && map[r][c] != -1)
						{
							map[r][c]++;
						}
					}
				}
			}
		}

	}
	//加密
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			map[i][j] += 20;
		}

	}
}
void draw(int map[][COL],IMAGE img[])
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (map[i][j] >= 0 && map[i][j] <= 8)
			{
				putimage(j * 130, i * 130, img + map[i][j]);
			}
			else if (map[i][j] == -1)
			{
				putimage(j * 130, i * 130, img + 9);
			}
			else if (map[i][j] >= 19 && map[i][j] <= 28) {
				putimage(j * 130, i * 130, img + 10);
			}
			else if (map[i][j] >= 30) {
				putimage(j * 130, i * 130, img + 11);
			}
		}

	}
}
void mouse(int map[][COL])
{
	ExMessage msg;
	if (peekmessage(&msg, WH_MOUSE))
	{
		int r = msg.y/130;
		int c = msg.x/130;
		if (msg.message == WM_LBUTTONDOWN)
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] -= 20;
				openNull(map, r, c);
				judge(map, r, c);
				show(map);
			}
			
		}
		else if (msg.message == WM_RBUTTONDOWN)
		{
			if (map[r][c] >= 19 && map[r][c] <= 28)
			{
				map[r][c] += 20;
				openNull(map, r, c);
				show(map);
			}
		}
	}
}
void openNull(int map[][COL], int row, int col)
{
	//判断当前点击的是不是空白
	if (map[row][col] == 0)
	{
		for (int i = row - 1; i <= row + 1; i++)
		{
			for (int j = col - 1; j <= col + 1; j++)
			{
				if ((i>=0&&i<ROW&&j>=0&&j<COL)&&map[i][j] >= 19 && map[i][j] <= 28)
				{
					map[i][j] -= 20;
					openNull(map, i, j);
				}
			}
		}
	}
}
void judge(int map[][COL], int row, int col) {
	//判断结束
	if (map[row][col] == -1)
	{
		for (int i = 0; i < ROW; i++)
		{
			for (int j = 0; j < COL; j++)
			{
				if (map[i][j] == 19)
				{
					map[i][j] -= 20;
				}
			}
		}
		isOver = true;

	}
	int cnt = 0;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (map[i][j] >= 19 && map[i][j] <= 28)
				cnt++;
		}
	}
	if (cnt == 0)
	{
		isOver = true;
	}


}