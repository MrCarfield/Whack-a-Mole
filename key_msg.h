#pragma once

struct MouseInput {
    int x;
    int y;
    bool leftClick;
};

// 获取当前鼠标状态
MouseInput get_mouse_state();
