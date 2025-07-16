#include "fireworks.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <iostream>
#include "menu_page.h"
#include "music.h"

using namespace std;

#define PI 3.1415926
#define NUM 25           // 烟花弹和烟花绽放的数量
#define WIDTH 980        // 窗口宽度
#define HEIGHT 980       // 窗口高度

// 定义一个烟花弹结构体
struct Jet
{
	int x, y;           // 烟花弹当前坐标
	int hx, hy;         // 最高点坐标（目标高度）
	bool is_launch;     // 是否正在发射状态
	IMAGE img[2];       // 两帧动画图像
	byte n : 1;         // 位段，只能为0或1，用来切换动画帧
} jet[NUM];

// 产生一个烟花弹
void creat_jet()
{
	int i = rand() % NUM;      // 随机选择一个烟花弹槽
	if (jet[i].is_launch == false) {
		jet[i].x = rand() % (WIDTH - 20);          // 横坐标随机
		jet[i].y = rand() % 100 + HEIGHT;          // 起点在窗口底部以下一点
		jet[i].hy = rand() % (HEIGHT / 2) + 80;    // 最高点在上半部分(即较小的y)
		jet[i].hx = jet[i].x;
		jet[i].is_launch = true;                    // 标记为发射状态
	}
}

// 定义烟花绽放结构体
struct Fire
{
	int cen_x, cen_y;     // 绽放中心点在图片上的坐标
	int x, y;             // 绽放在窗口上的坐标
	int r;                // 当前绽放半径
	int max_r;            // 最大绽放半径
	int width, height;    // 图片宽高
	DWORD pixel[280][280];// 保存烟花绽放图片的像素数据
	bool is_show;         // 是否准备好显示绽放效果
	bool is_draw;         // 是否正在绘制
} fire[NUM];

// 发射烟花弹并更新位置
void launch() {
	for (int i = 0; i < NUM; i++) {
		if (jet[i].is_launch == true) {
			// 先用SRCINVERT模式绘制当前帧图像擦除前一帧
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y > jet[i].hy)  // 还没到最高点，向上移动
			{
				jet[i].y -= 5;    // 向上移动5个像素
				jet[i].n++;       // 切换动画帧
			}

			// 再用SRCINVERT模式绘制新帧，实现动画效果
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
		}
		// 到达最高点，停止发射，准备绽放
		if (jet[i].y <= jet[i].hy)
		{
			jet[i].is_launch = false;
			fire[i].x = jet[i].x;
			fire[i].y = jet[i].y;
			fire[i].is_show = true;   // 标记烟花准备绽放
		}
	}
}

// 初始化烟花绽放数据
void Initdate(int i)
{
	fire[i].cen_x = 140;
	fire[i].cen_y = 140;
	fire[i].max_r = 70;
	fire[i].r = 0;
	fire[i].width = 280;
	fire[i].height = 280;
	fire[i].is_draw = false;
	fire[i].is_show = false;
}

// 欢迎文字，显示胜利提示
void welcome()
{
	settextstyle(120, 0, "微软雅黑");
	settextcolor(RGB(255, 166, 94));
	outtextxy(180, 200, "恭喜您胜利啦 !");
	Sleep(3000);  // 显示3秒
}

// 加载烟花图片资源，初始化相关数据
void loadImg()
{
	// 初始化绽放效果图
	IMAGE bloomImg, tImg;
	loadimage(&bloomImg, ".\\resources\\image\\bloom_bouquet.png", 2520, 280); // 一张大图包含9个280x280烟花
	for (int i = 0; i < NUM; i++)
	{
		Initdate(i);   // 初始化每个烟花数据
		int bouquet_index = i % 9;   // 取9张中的哪一张

		SetWorkingImage(&bloomImg);   // 设置当前绘图目标为大图
		getimage(&tImg, bouquet_index * 280, 0, 280, 280);  // 截取单张烟花图
		SetWorkingImage(&tImg);  // 设置绘图目标为单张图

		// 保存每个像素颜色值到fire[i].pixel中，后面用于绘制
		for (int a = 0; a < 280; a++)
		{
			for (int b = 0; b < 280; b++)
			{
				fire[i].pixel[a][b] = getpixel(a, b);
			}
		}
	}

	// 初始化烟花弹图像
	IMAGE jetImg;
	loadimage(&jetImg, ".\\resources\\image\\firework_bomb.png", 200, 50);
	SetWorkingImage(&jetImg);
	for (int i = 0; i < NUM; i++) {
		int n = rand() % 5;     // 随机选择帧
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], n * 20 + 100, 0, 20, 50);
		jet[i].is_launch = false;  // 初始化为未发射状态
	}
	SetWorkingImage();   // 恢复默认绘图目标
}

// 绘制烟花绽放效果
void bloom(DWORD* pMem)
{
	for (int i = 0; i < NUM; i++)
	{
		if (fire[i].is_show)   // 只有准备好了才更新绽放半径
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;    // 增大绽放半径
				fire[i].is_draw = true;
			}
			else
			{
				Initdate(i);   // 超过最大半径后重置数据
			}
		}

		if (fire[i].is_draw)   // 绘制绽放
		{
			// 使用极坐标方程画圆弧
			for (double a = 0; a < 2 * PI; a += 0.01)
			{
				int img_x = fire[i].cen_x + fire[i].r * cos(a);  // 绽放图片上的x
				int img_y = fire[i].cen_y + fire[i].r * sin(a);  // 绽放图片上的y
				if (img_x > 0 && img_x < fire[i].width && img_y > 0 && img_y < fire[i].height)
				{
					int win_x = fire[i].x + fire[i].r * cos(a);   // 窗口绘制位置x
					int win_y = fire[i].y + fire[i].r * sin(a);   // 窗口绘制位置y
					if (win_x > 0 && win_x < WIDTH && win_y > 0 && win_y < HEIGHT)
					{
						pMem[win_y * WIDTH + win_x] = BGR(fire[i].pixel[img_x][img_y]);  // 设置像素点颜色
					}
				}
			}
		}
	}
}

// 返回按钮的尺寸和位置，方便调整
const int returnBtnWidth = 100;
const int returnBtnHeight = 40;
const int returnBtnMargin = 20; // 距离右下角边距

// 绘制返回按钮并检测点击，返回true表示点击了返回按钮
bool drawReturnButton() {
	int btnX = WIDTH - returnBtnWidth - returnBtnMargin;         // 按钮X坐标
	int btnY = HEIGHT - returnBtnHeight - returnBtnMargin;       // 按钮Y坐标

	// 你可以取消注释以下代码绘制按钮背景，更明显
	// setfillcolor(RGB(200, 200, 200));
	// solidrectangle(btnX, btnY, btnX + returnBtnWidth, btnY + returnBtnHeight);

	settextstyle(40, 0, "微软雅黑");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(btnX + 20, btnY - 30, "返回");  // 绘制按钮文字，稍微往上偏移

	// 检测鼠标点击事件
	if (MouseHit()) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			// 判断点击位置是否在按钮区域内
			if (m.x >= btnX && m.x <= btnX + returnBtnWidth &&
				m.y >= btnY - 30 && m.y <= btnY + returnBtnHeight - 30) {
				return true;  // 点击了返回按钮
			}
		}
	}
	return false;  // 未点击返回按钮
}

// 烟花主函数，控制烟花显示和逻辑
void fireworks() {
	stop_music();         // 停止所有音乐，避免叠音

	victory_music();      // 播放胜利音乐（循环播放）

	initgraph(WIDTH, HEIGHT);
	srand((unsigned)time(NULL));

	welcome();            // 显示欢迎文字，停3秒

	// 初始化烟花弹状态和数据
	for (int i = 0; i < NUM; i++) {
		jet[i].x = 0;
		jet[i].y = HEIGHT;
		jet[i].hx = 0;
		jet[i].hy = HEIGHT / 2;
		jet[i].n = 0;
		jet[i].is_launch = false;
		Initdate(i);
	}

	loadImg();                 // 加载资源图片

	DWORD* pMem = GetImageBuffer();  // 获取图像缓冲区指针

	while (1)
	{
		// 随机擦除部分像素，模拟烟花闪烁效果
		for (int i = 0; i < WIDTH; i++) {
			for (int k = 0; k < 4; k++) {
				int x = rand() % WIDTH;
				int y = rand() % HEIGHT;
				if (y < HEIGHT) {
					pMem[y * WIDTH + x] = BLACK;
				}
			}
		}

		creat_jet();  // 产生新的烟花弹（随机）

		launch();     // 发射烟花弹并更新位置

		bloom(pMem);  // 绽放烟花，绘制到缓冲区

		if (drawReturnButton()) {   // 如果点击了返回按钮
			stop_music();           // 停止音乐
			closegraph();          // 关闭图形窗口
			menu_page();           // 返回菜单页面
			return;
		}

		Sleep(10);  // 控制刷新频率，避免CPU占用过高
	}
}
