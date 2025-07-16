#include "show_left_time.h"
#include <graphics.h>
#include <string>
#include <algorithm>  // for std::max

using namespace std;

void show_timer(DWORD elapsed) {
    setbkmode(TRANSPARENT);
    settextstyle(25, 0, "΢���ź�");   // ʹ�ö��ֽ��ַ���
    settextcolor(BLUE);

    int remain = max(0, 60 - (int)(elapsed / 1000));  // ʣ������
    string timeStr = "Time: " + to_string(remain) + "s";

    outtextxy(50, 20, timeStr.c_str());
}
