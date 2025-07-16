#include "key_msg.h"
#include <graphics.h>

MouseInput state = { 0 };
MouseInput get_mouse_state() {
    // ��ȡ��굱ǰ���꣨��ʹû�����
    ExMessage msg;
    while (peekmessage(&msg, EM_MOUSE)) {
        state.x = msg.x;
        state.y = msg.y;

        if (msg.message == WM_LBUTTONDOWN) {
            state.leftClick = true; // ������£������
        }
        if (msg.message == WM_LBUTTONUP)
        {
            state.leftClick = false;
        }
    }

    return state;
}

