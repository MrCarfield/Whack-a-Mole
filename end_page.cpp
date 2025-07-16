//游戏失败界面:
//弹出游戏失败的页面(一张图片, 下面有返回按钮), 点击返回按钮, 返回菜单页面
//游戏时间到之后产生的界面 :
//直接跳转到烟花界面, 烟花界面里面显示miss数 5秒后开始释放烟花, 10秒后结束烟花放映, 跳转到菜单页面
#include <graphics.h>
#include <conio.h>
#include "end_page.h"
#include "fireworks.h"
#include "music.h"

// 引用主菜单函数
extern void menu_page();

// 窗口大小
#define WINDOW_WIDTH 980
#define WINDOW_HEIGHT 980

// 返回按钮位置与尺寸
#define BTN_X 390
#define BTN_Y 800
#define BTN_W 200
#define BTN_H 60

// 判断鼠标是否点击在按钮范围内
bool is_click_back_button(int x, int y) {
	return x >= BTN_X+15 && x <= BTN_X+15 + BTN_W && y >= BTN_Y-150 && y <= BTN_Y + BTN_H-60;
}

// 绘制返回按钮（文字 + 边框）
void draw_back_button() {
	setbkmode(TRANSPARENT);                // 设置文字背景透明
	settextcolor(RGB(245, 245, 220));
	settextstyle(60, 0, _T("微软雅黑"));
	outtextxy(BTN_X + 50+15, BTN_Y + 15-60, _T("返 回"));
}

// 游戏失败页面
void fail_page() {
	stop_music();
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // 打开画布

	// 显示背景图
	IMAGE img_end;
	loadimage(&img_end, _T("./resources/image/end_page.png"), WINDOW_WIDTH, WINDOW_HEIGHT);
	putimage(0, 0, &img_end);
	end_music();

	// 绘制“返回”按钮
	draw_back_button();

	// 等待鼠标点击“返回”按钮
	while (true) {
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (is_click_back_button(m.x, m.y)) {
					menu_page();  // 调用主菜单
					break;
				}
			}
		}
	}
}
// 游戏胜利页面实现
void victory_page() {
	fireworks();
}

