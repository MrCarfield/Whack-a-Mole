#include "gaming.h"
#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "background.h"
#include "mouse.h"
#include "key_msg.h"
#include "music.h"
#include "time_manager.h"
#include "end_page.h"
#include "hammer.h"  // ✅ 加入锤子头文件

int score = 0;

void show_score(int remainTime) {
    settextstyle(50, 0, "微软雅黑");
    setbkmode(TRANSPARENT);
    settextcolor(RED);

    string scoreStr = "Score: " + to_string(score) + "     Time: " + to_string(remainTime) + "s";
    outtextxy(400, 40, scoreStr.c_str());
}

void show_countdown() {
    settextstyle(120, 0, "微软雅黑");
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    for (int i = 3; i > 0; --i) {
        cleardevice();
        outtextxy(440, 400, to_string(i).c_str());
        FlushBatchDraw();
        Sleep(1000);
    }
    cleardevice();
    outtextxy(390, 400, "开始!");
    FlushBatchDraw();
    Sleep(800);
    cleardevice();
}

void gaming() {

    initgraph(980, 980);
    BeginBatchDraw();

    loading_bk_page();
    show_countdown();  // ✅ 显示倒计时

    init_mouse();
    init_hammer();            // ✅ 初始化锤子
    init_game_timer();

    IMAGE* bk = get_background_image();

    while (true) {
        DWORD beginTime = GetTickCount();
        int remainTime = get_remaining_time();
        if (is_time_up()) break;

        putimage(0, 0, bk);

        update_mouse();
        draw_mouse();

        MouseInput m = get_mouse_state();

        if (m.leftClick) {
            start_hammer();       // ✅ 点击时触发锤子动画
            if (is_mouse_hit(m.x, m.y)) {
                hit_mouse();
                score++;
            }
        }

        update_hammer();           // ✅ 每帧更新动画状态
        draw_hammer_controlled(m.x, m.y);

        show_score(remainTime);

        FlushBatchDraw();
        DWORD endTime = GetTickCount();
        DWORD elapsedTime = endTime - beginTime;
        if (elapsedTime < 1000 / 60)
            Sleep(1000 / 60 - elapsedTime);
    }

    EndBatchDraw();
    closegraph();

    if (score >= 10) {
        victory_page();
    }
    else {
        fail_page();
    }
}