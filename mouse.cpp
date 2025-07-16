#include "mouse.h"
#include "key_msg.h"
#include <graphics.h>
#include <windows.h>
#include <cstdlib>
#include"music.h"

// �������˽�б���
static MouseStatus mouseState = MOUSE_HIDE;
static int mouseX = 0, mouseY = 0;
static DWORD appearTime = 0;
static DWORD duration = 0;

static IMAGE mouseImg;
static IMAGE mouseMaskImg;



// ����λ�ã�3�� �� 3�У�
const int HOLE_ROWS = 3;
const int HOLE_COLS = 3;
const int HOLE_WIDTH = 340 * 0.5;
const int HOLE_HEIGHT = 235 * 0.5;
const int HOLE_SPACING_X = 100 * 0.8; // ���붴������
const int HOLE_SPACING_Y = 80 * 0.8;  // ���붴������
const int HOLE_START_X = 160;    // ��һ������xƫ��
const int HOLE_START_Y = 240 + 20;   // ��һ������yƫ��

// ����ͼƬ��ߣ�����250*250��
const int MOUSE_WIDTH = 250*0.5;
const int MOUSE_HEIGHT = 250*0.5;

// ��ʼ��
void init_mouse() {
    loadimage(&mouseImg, ".\\resources\\image\\mouse.png", MOUSE_WIDTH, MOUSE_HEIGHT);
    loadimage(&mouseMaskImg, ".\\resources\\image\\mouse_mask_image.png", MOUSE_WIDTH, MOUSE_HEIGHT);
    mouseState = MOUSE_HIDE;
    appearTime = 0;
    duration = 0;
}

// ����״̬����״̬����
void update_mouse() {
    DWORD now = GetTickCount();

    switch (mouseState) {
    case MOUSE_HIDE:
        if (rand() % 100 < 3) {
            // ������ڱ��
            int row = rand() % HOLE_ROWS;
            int col = rand() % HOLE_COLS;

            int holeX = HOLE_START_X + col * (HOLE_WIDTH + HOLE_SPACING_X);
            int holeY = HOLE_START_Y + row * (HOLE_HEIGHT + HOLE_SPACING_Y);

            mouseX = holeX + (HOLE_WIDTH - MOUSE_WIDTH) / 2;
            mouseY = holeY - (int)(MOUSE_HEIGHT * 0.6)-7;  // ����ƫ��

            appearTime = now;
            duration = 1000 + (rand() % 1500);
            mouseState = MOUSE_SHOW;
            mouse_show_music();
        }
        break;

    case MOUSE_SHOW:
        if (now - appearTime > duration) {
            mouseState = MOUSE_HIDE;
        }
        break;

    case MOUSE_HIT:
        mouseState = MOUSE_HIDE;
        break;
    }
}


void draw_mouse() {
    if (mouseState == MOUSE_SHOW) {
        putimage(mouseX, mouseY, &mouseMaskImg, SRCPAINT);
        putimage(mouseX, mouseY, &mouseImg, SRCAND);
    }
}

bool is_mouse_hit(int mouseXClick, int mouseYClick) {
    if (mouseState != MOUSE_SHOW) return false;
    return mouseXClick >= mouseX && mouseXClick <= mouseX + MOUSE_WIDTH
        && mouseYClick >= mouseY && mouseYClick <= mouseY + MOUSE_HEIGHT;
}

void hit_mouse() {
    if (mouseState == MOUSE_SHOW) {
        mouseState = MOUSE_HIT;
    }
}

MouseStatus get_mouse_status() {
    return mouseState;
}
