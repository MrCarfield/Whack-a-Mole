#include "show_left_time.h"
#include <graphics.h>
#include <string>
#include <algorithm>  // for std::max

using namespace std;

void show_timer(DWORD elapsed) {
    setbkmode(TRANSPARENT);
    settextstyle(25, 0, "微软雅黑");   // 使用多字节字符集
    settextcolor(BLUE);

    int remain = max(0, 60 - (int)(elapsed / 1000));  // 剩余秒数
    string timeStr = "Time: " + to_string(remain) + "s";

    outtextxy(50, 20, timeStr.c_str());
}
