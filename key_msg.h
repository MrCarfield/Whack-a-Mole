#pragma once

struct MouseInput {
    int x;
    int y;
    bool leftClick;
};

// ��ȡ��ǰ���״̬
MouseInput get_mouse_state();
