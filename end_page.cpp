//��Ϸʧ�ܽ���:
//������Ϸʧ�ܵ�ҳ��(һ��ͼƬ, �����з��ذ�ť), ������ذ�ť, ���ز˵�ҳ��
//��Ϸʱ�䵽֮������Ľ��� :
//ֱ����ת���̻�����, �̻�����������ʾmiss�� 5���ʼ�ͷ��̻�, 10�������̻���ӳ, ��ת���˵�ҳ��
#include <graphics.h>
#include <conio.h>
#include "end_page.h"
#include "fireworks.h"
#include "music.h"

// �������˵�����
extern void menu_page();

// ���ڴ�С
#define WINDOW_WIDTH 980
#define WINDOW_HEIGHT 980

// ���ذ�ťλ����ߴ�
#define BTN_X 390
#define BTN_Y 800
#define BTN_W 200
#define BTN_H 60

// �ж�����Ƿ����ڰ�ť��Χ��
bool is_click_back_button(int x, int y) {
	return x >= BTN_X+15 && x <= BTN_X+15 + BTN_W && y >= BTN_Y-150 && y <= BTN_Y + BTN_H-60;
}

// ���Ʒ��ذ�ť������ + �߿�
void draw_back_button() {
	setbkmode(TRANSPARENT);                // �������ֱ���͸��
	settextcolor(RGB(245, 245, 220));
	settextstyle(60, 0, _T("΢���ź�"));
	outtextxy(BTN_X + 50+15, BTN_Y + 15-60, _T("�� ��"));
}

// ��Ϸʧ��ҳ��
void fail_page() {
	stop_music();
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT); // �򿪻���

	// ��ʾ����ͼ
	IMAGE img_end;
	loadimage(&img_end, _T("./resources/image/end_page.png"), WINDOW_WIDTH, WINDOW_HEIGHT);
	putimage(0, 0, &img_end);
	end_music();

	// ���ơ����ء���ť
	draw_back_button();

	// �ȴ�����������ء���ť
	while (true) {
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (is_click_back_button(m.x, m.y)) {
					menu_page();  // �������˵�
					break;
				}
			}
		}
	}
}
// ��Ϸʤ��ҳ��ʵ��
void victory_page() {
	fireworks();
}

