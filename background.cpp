// background.cpp
#include "background.h"
#include <graphics.h>

// ��������ͼ��
IMAGE bkImg;

// ���ر���ͼָ��
IMAGE* get_background_image() {
    return &bkImg;
}

// ����λ�ã�3�� �� 3�У�
const int HOLE_ROWS = 3;
const int HOLE_COLS = 3;
const int HOLE_WIDTH = 340 * 0.5;
const int HOLE_HEIGHT = 235 * 0.5;
const int HOLE_SPACING_X = 100 * 0.8;
const int HOLE_SPACING_Y = 80 * 0.8;
const int HOLE_START_X = 160;
const int HOLE_START_Y = 240 + 20;


void loading_bk_page() {
    // ��ʼ����������ͼ��Ϊ��Ϸ�����ڴ�С
    bkImg.Resize(980, 980);
    SetWorkingImage(&bkImg); // �����������������ͼ����

    // ���ر���ͼƬ�������֣�ֱ����ͼ��
    IMAGE gaming_bg;
    loadimage(&gaming_bg, ".\\resources\\image\\bkimage.png", 980, 980);
    putimage(0, 0, &gaming_bg); // ������������

    // ���� logo ������ͼ��logo ʹ������ʵ��͸����
    IMAGE logo, logo_mask;
    loadimage(&logo, ".\\resources\\image\\logo.png", 250, 250);             // ��С��ʾ
    loadimage(&logo_mask, ".\\resources\\image\\logo_mask_image.png", 250, 250);
    putimage(10, 10,&logo_mask, SRCPAINT);  // ��������ͼ������͸������
    putimage(10, 10, &logo,SRCAND); // ����ͼƬ��ʵ��͸����ͼ

    // �������󶴼�������
    IMAGE hole, hole_mask;
    loadimage(&hole_mask, ".\\resources\\image\\hole_mask.png", HOLE_WIDTH, HOLE_HEIGHT);
    loadimage(&hole, ".\\resources\\image\\hole.png", HOLE_WIDTH, HOLE_HEIGHT);


    // ���λ���9�����󶴣�3��3������͸������
    for (int row = 0; row < HOLE_ROWS; row++) {
        for (int col = 0; col < HOLE_COLS; col++) {
            int x = HOLE_START_X + col * (HOLE_WIDTH + HOLE_SPACING_X);
            int y = HOLE_START_Y + row * (HOLE_HEIGHT + HOLE_SPACING_Y);
                putimage(x, y, &hole_mask, SRCPAINT);
                putimage(x, y, &hole, SRCAND);
                
        }
    }

    SetWorkingImage(nullptr); // �ָ�Ĭ�Ϲ�������
}
