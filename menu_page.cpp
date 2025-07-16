//三个按钮:
//第一个按钮游戏规则, 第二个按钮 : 开始游戏, 第三个按钮 : 退出游戏
//背景是一张卡通类的图片, 明确标识打地鼠, 上面呈现几个按钮,
//第一个按钮 : 按钮内容 : 游戏规则
//点击之后弹出小窗口, 上面有游戏规则(...), 窗口的下方有确定按钮, 点击之后返回主菜单
//第二个按钮 : 按钮内容:开始游戏
//点击之后跳转到游戏进行页面, 即刻开始游戏
//第三个按钮 : 按钮内容:退出游戏
//点击之后退出程序, 关闭画布
//具体实现 :
//全部用函数的形式和对象的形式进行封装最终实现用一个函数进行封装, 最后在主函数中只需要调用这个函数就行
//首先根据游戏界面的画布尺寸将开始界面的背景图片导入进去
//然后放置三个按钮
//之后依次实现各个按钮的功能
//第一个按钮 : 按下之后弹出小窗口, 这个小窗口是个图片, 图片的下方放置确定按钮, 点击确定按钮实现返回菜单页面
//第二个按钮 : 按下之后结束主菜单函数
//第三个按钮 : 按下之后结束整个程序并关闭画布

//第一个函数: 加载当前的页面(菜单页面, 不需要设置按钮, 只需要把背景图片和加载上去)并将当前页面设置为主窗口
//第二个函数 : 显示第一个按钮并将相应的功能实现
//第三个函数 : 显示第二个按钮并将相应的功能实现
//第四个函数 : 显示第三个按钮并将相应的功能实现
//第五个函数 : 将上述四个函数进行打包, 实现整体的功能

#include "menu_page.h"
#include <graphics.h>
#include <windows.h>
#include <tchar.h>
#include <string>
#include"music.h"
#include"gaming.h"
using namespace std;

// ======================= 图片路径 =======================
#define BG_IMAGE       ".\\resources\\image\\loading_screen.png"     // 菜单背景图
#define RULE_IMAGE     ".\\resources\\image\\rule_page.png"           // 游戏规则弹窗图

// ======================= 按钮坐标设置 =======================
struct Button {
    int x, y, w, h;
    string text;
};

Button btn_rule = { 100, 650, 200, 50, "游戏规则" };
Button btn_start = { 100, 720, 200, 50, "开始游戏" };
Button btn_exit = { 100, 790, 200, 50, "退出游戏" };

// ======================= 工具函数：判断是否点击了按钮 =======================
bool isHit(Button btn, int x, int y) {
    return x >= btn.x && x <= btn.x + btn.w && y >= btn.y && y <= btn.y + btn.h;
}

// ======================= 函数1：加载菜单背景图 =======================
void start_screen() {
    IMAGE bg;
    loadimage(&bg, _T(BG_IMAGE),980,980);
    putimage(0, 0, &bg);
}

// ======================= 函数2：显示规则按钮 =======================
void button_1() {
    setfillcolor(RGB(200, 200, 200));
    solidrectangle(btn_rule.x, btn_rule.y, btn_rule.x + btn_rule.w, btn_rule.y + btn_rule.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_rule.x + 50, btn_rule.y + 15, _T("游戏规则"));
}

// ======================= 函数3：显示开始按钮 =======================
void button_2() {
    setfillcolor(RGB(150, 220, 150));
    solidrectangle(btn_start.x, btn_start.y, btn_start.x + btn_start.w, btn_start.y + btn_start.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_start.x + 50, btn_start.y + 15, _T("开始游戏"));
}

// ======================= 函数4：显示退出按钮 =======================
void button_3() {
    setfillcolor(RGB(220, 150, 150));
    solidrectangle(btn_exit.x, btn_exit.y, btn_exit.x + btn_exit.w, btn_exit.y + btn_exit.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("黑体"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_exit.x + 50, btn_exit.y + 15, _T("退出游戏"));
}

// ======================= 弹出规则窗口 =======================
void show_rule_popup() {
    IMAGE ruleImg;
    loadimage(&ruleImg, _T(RULE_IMAGE));

    int popup_w = 1024;
    int popup_h = 1024;
    int px = (getwidth() - popup_w) / 2;
    int py = (getheight() - popup_h) / 2;

    putimage(px, py, popup_w, popup_h, &ruleImg, 0, 0);

    RECT ok_rect = { px + popup_w / 2 -60, py + popup_h - 300, px + popup_w / 2 + 60, py + popup_h - 240 };
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(45, 0, _T("宋体"));
    outtextxy(ok_rect.left + 18, ok_rect.top + 10 - 156, _T("确定"));

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(15, 0, _T("宋体"));
    int x1 = 365;
    int y1 = 320;
    int line = 15;
    outtextxy(x1, y1, _T("- 游戏场景通常为带9个孔洞的"));
    outtextxy(x1, y1+line, _T(" 平台，地鼠会随机从孔洞中冒出。"));
    outtextxy(x1, y1+line*3, _T("- 玩家需在规定时间内，用锤子"));
    outtextxy(x1, y1+line*4, _T(" 敲击冒出的地鼠，击中即可得分。"));
	outtextxy(x1, y1 + line *6 , _T("- 每击中一只地鼠得1分，游戏"));
   outtextxy(x1, y1 + line * 7, _T(" 时间结束后显示总分。"));
	outtextxy(x1, y1 + line *9 , _T("- 游戏时间为45秒，时间结束"));
    outtextxy(x1, y1 + line * 10, _T("后如果分数 >= 10则为"));
     outtextxy(x1, y1 + line * 11, _T("胜利(有彩蛋), 否则为失败。"));
    

    MOUSEMSG m;
    while (true) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= ok_rect.left-7 && m.x <= ok_rect.right-7 && m.y >= ok_rect.top-156 && m.y <= ok_rect.bottom-156) {
                break;
            }
        }
    }

    start_screen();
    button_1(); button_2(); button_3();
}

// ======================= 函数5：整合菜单页面功能 =======================
void menu_page() {
    initgraph(980, 980);
    start_music();
    start_screen();
    button_1();
    button_2();
    button_3();
    Sleep(1000);
    bk_music();

    MOUSEMSG msg;
    while (true) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (isHit(btn_rule, msg.x, msg.y)) {
                show_rule_popup();
            }
            else if (isHit(btn_start, msg.x, msg.y)) {
                gaming();
                break;
            }
            else if (isHit(btn_exit, msg.x, msg.y)) {
                EndBatchDraw();				// 关闭批量绘图
                closegraph();
                exit(0);
            }
        }
    }
}
