#pragma once

enum MouseStatus {
    MOUSE_HIDE,
    MOUSE_SHOW,
    MOUSE_HIT
};

void init_mouse();
void update_mouse();
void draw_mouse();

// 判断坐标是否击中地鼠
bool is_mouse_hit(int mouseX, int mouseY);

// 地鼠被击中处理
void hit_mouse();

// 获取当前地鼠状态（可选）
MouseStatus get_mouse_status();
