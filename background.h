#pragma once
// background.h
#pragma once
#include <graphics.h>

// ����ͼ���棬������Ϸѭ�����ظ�ʹ��
extern IMAGE bkImg;
extern void putimage_alpha(int x, int y, IMAGE* img);
// �������ƺ��������ر�����logo�����󶴲����Ƶ� bkImg ��
void loading_bk_page();
IMAGE* get_background_image();  // �ṩ����ͼָ��


