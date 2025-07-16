#include "key_msg.h"
#include <graphics.h>

MouseInput state = { 0 };
MouseInput get_mouse_state() {
    // 获取鼠标当前坐标（即使没点击）
    ExMessage msg;
    while (peekmessage(&msg, EM_MOUSE)) {
        state.x = msg.x;
        state.y = msg.y;

        if (msg.message == WM_LBUTTONDOWN) {
            state.leftClick = true; // 左键按下（点击）
        }
        if (msg.message == WM_LBUTTONUP)
        {
            state.leftClick = false;
        }
    }

    return state;
}

