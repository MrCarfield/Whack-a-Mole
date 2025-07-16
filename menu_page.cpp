//������ť:
//��һ����ť��Ϸ����, �ڶ�����ť : ��ʼ��Ϸ, ��������ť : �˳���Ϸ
//������һ�ſ�ͨ���ͼƬ, ��ȷ��ʶ�����, ������ּ�����ť,
//��һ����ť : ��ť���� : ��Ϸ����
//���֮�󵯳�С����, ��������Ϸ����(...), ���ڵ��·���ȷ����ť, ���֮�󷵻����˵�
//�ڶ�����ť : ��ť����:��ʼ��Ϸ
//���֮����ת����Ϸ����ҳ��, ���̿�ʼ��Ϸ
//��������ť : ��ť����:�˳���Ϸ
//���֮���˳�����, �رջ���
//����ʵ�� :
//ȫ���ú�������ʽ�Ͷ������ʽ���з�װ����ʵ����һ���������з�װ, �������������ֻ��Ҫ���������������
//���ȸ�����Ϸ����Ļ����ߴ罫��ʼ����ı���ͼƬ�����ȥ
//Ȼ�����������ť
//֮������ʵ�ָ�����ť�Ĺ���
//��һ����ť : ����֮�󵯳�С����, ���С�����Ǹ�ͼƬ, ͼƬ���·�����ȷ����ť, ���ȷ����ťʵ�ַ��ز˵�ҳ��
//�ڶ�����ť : ����֮��������˵�����
//��������ť : ����֮������������򲢹رջ���

//��һ������: ���ص�ǰ��ҳ��(�˵�ҳ��, ����Ҫ���ð�ť, ֻ��Ҫ�ѱ���ͼƬ�ͼ�����ȥ)������ǰҳ������Ϊ������
//�ڶ������� : ��ʾ��һ����ť������Ӧ�Ĺ���ʵ��
//���������� : ��ʾ�ڶ�����ť������Ӧ�Ĺ���ʵ��
//���ĸ����� : ��ʾ��������ť������Ӧ�Ĺ���ʵ��
//��������� : �������ĸ��������д��, ʵ������Ĺ���

#include "menu_page.h"
#include <graphics.h>
#include <windows.h>
#include <tchar.h>
#include <string>
#include"music.h"
#include"gaming.h"
using namespace std;

// ======================= ͼƬ·�� =======================
#define BG_IMAGE       ".\\resources\\image\\loading_screen.png"     // �˵�����ͼ
#define RULE_IMAGE     ".\\resources\\image\\rule_page.png"           // ��Ϸ���򵯴�ͼ

// ======================= ��ť�������� =======================
struct Button {
    int x, y, w, h;
    string text;
};

Button btn_rule = { 100, 650, 200, 50, "��Ϸ����" };
Button btn_start = { 100, 720, 200, 50, "��ʼ��Ϸ" };
Button btn_exit = { 100, 790, 200, 50, "�˳���Ϸ" };

// ======================= ���ߺ������ж��Ƿ����˰�ť =======================
bool isHit(Button btn, int x, int y) {
    return x >= btn.x && x <= btn.x + btn.w && y >= btn.y && y <= btn.y + btn.h;
}

// ======================= ����1�����ز˵�����ͼ =======================
void start_screen() {
    IMAGE bg;
    loadimage(&bg, _T(BG_IMAGE),980,980);
    putimage(0, 0, &bg);
}

// ======================= ����2����ʾ����ť =======================
void button_1() {
    setfillcolor(RGB(200, 200, 200));
    solidrectangle(btn_rule.x, btn_rule.y, btn_rule.x + btn_rule.w, btn_rule.y + btn_rule.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_rule.x + 50, btn_rule.y + 15, _T("��Ϸ����"));
}

// ======================= ����3����ʾ��ʼ��ť =======================
void button_2() {
    setfillcolor(RGB(150, 220, 150));
    solidrectangle(btn_start.x, btn_start.y, btn_start.x + btn_start.w, btn_start.y + btn_start.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_start.x + 50, btn_start.y + 15, _T("��ʼ��Ϸ"));
}

// ======================= ����4����ʾ�˳���ť =======================
void button_3() {
    setfillcolor(RGB(220, 150, 150));
    solidrectangle(btn_exit.x, btn_exit.y, btn_exit.x + btn_exit.w, btn_exit.y + btn_exit.h);
    settextcolor(BLACK);
    settextstyle(20, 0, _T("����"));
    setbkmode(TRANSPARENT);
    outtextxy(btn_exit.x + 50, btn_exit.y + 15, _T("�˳���Ϸ"));
}

// ======================= �������򴰿� =======================
void show_rule_popup() {
    IMAGE ruleImg;
    loadimage(&ruleImg, _T(RULE_IMAGE));

    int popup_w = 1024;
    int popup_h = 1024;
    int px = (getwidth() - popup_w) / 2;
    int py = (getheight() - popup_h) / 2;

    putimage(px, py, popup_w, popup_h, &ruleImg, 0, 0);

    RECT ok_rect = { px + popup_w / 2 -60, py + popup_h - 300, px + popup_w / 2 + 60, py + popup_h - 240 };
    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(45, 0, _T("����"));
    outtextxy(ok_rect.left + 18, ok_rect.top + 10 - 156, _T("ȷ��"));

    settextcolor(BLACK);
    setbkmode(TRANSPARENT);
    settextstyle(15, 0, _T("����"));
    int x1 = 365;
    int y1 = 320;
    int line = 15;
    outtextxy(x1, y1, _T("- ��Ϸ����ͨ��Ϊ��9���׶���"));
    outtextxy(x1, y1+line, _T(" ƽ̨�����������ӿ׶���ð����"));
    outtextxy(x1, y1+line*3, _T("- ������ڹ涨ʱ���ڣ��ô���"));
    outtextxy(x1, y1+line*4, _T(" �û�ð���ĵ��󣬻��м��ɵ÷֡�"));
	outtextxy(x1, y1 + line *6 , _T("- ÿ����һֻ�����1�֣���Ϸ"));
   outtextxy(x1, y1 + line * 7, _T(" ʱ���������ʾ�ܷ֡�"));
	outtextxy(x1, y1 + line *9 , _T("- ��Ϸʱ��Ϊ45�룬ʱ�����"));
    outtextxy(x1, y1 + line * 10, _T("��������� >= 10��Ϊ"));
     outtextxy(x1, y1 + line * 11, _T("ʤ��(�вʵ�), ����Ϊʧ�ܡ�"));
    

    MOUSEMSG m;
    while (true) {
        m = GetMouseMsg();
        if (m.uMsg == WM_LBUTTONDOWN) {
            if (m.x >= ok_rect.left-7 && m.x <= ok_rect.right-7 && m.y >= ok_rect.top-156 && m.y <= ok_rect.bottom-156) {
                break;
            }
        }
    }

    start_screen();
    button_1(); button_2(); button_3();
}

// ======================= ����5�����ϲ˵�ҳ�湦�� =======================
void menu_page() {
    initgraph(980, 980);
    start_music();
    start_screen();
    button_1();
    button_2();
    button_3();
    Sleep(1000);
    bk_music();

    MOUSEMSG msg;
    while (true) {
        msg = GetMouseMsg();
        if (msg.uMsg == WM_LBUTTONDOWN) {
            if (isHit(btn_rule, msg.x, msg.y)) {
                show_rule_popup();
            }
            else if (isHit(btn_start, msg.x, msg.y)) {
                gaming();
                break;
            }
            else if (isHit(btn_exit, msg.x, msg.y)) {
                EndBatchDraw();				// �ر�������ͼ
                closegraph();
                exit(0);
            }
        }
    }
}
