#pragma once
#include <graphics.h>

// ��ʼ��������Դ
void init_hammer();

// ���´��Ӷ���״̬
void update_hammer();


// ��ʼ���򶯻������ʱ���ã�
void start_hammer();

// �ж��Ƿ����ڲ��Ż��򶯻�
bool is_hammer_striking();

void draw_hammer_controlled(int curMouseX, int curMouseY);

