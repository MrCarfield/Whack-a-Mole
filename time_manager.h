#pragma once
#include <windows.h>

// ��ʼ����Ϸʱ�䣨��¼��ʼʱ�䣩
void init_game_timer();

// ��ȡ��Ϸʣ��ʱ�䣨��λ���룩
int get_remaining_time();

// �Ƿ�ʱ����������� true ��ʾ����ʱ�ѽ�����
bool is_time_up();

// ������Ϸ����ʱ�䣨Ĭ�� 60 �룬���Զ��壩
void set_game_duration(int seconds);


