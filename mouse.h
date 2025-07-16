#pragma once

enum MouseStatus {
    MOUSE_HIDE,
    MOUSE_SHOW,
    MOUSE_HIT
};

void init_mouse();
void update_mouse();
void draw_mouse();

// �ж������Ƿ���е���
bool is_mouse_hit(int mouseX, int mouseY);

// ���󱻻��д���
void hit_mouse();

// ��ȡ��ǰ����״̬����ѡ��
MouseStatus get_mouse_status();
