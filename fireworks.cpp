#include "fireworks.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <graphics.h>
#include <iostream>
#include "menu_page.h"
#include "music.h"

using namespace std;

#define PI 3.1415926
#define NUM 25           // �̻������̻����ŵ�����
#define WIDTH 980        // ���ڿ��
#define HEIGHT 980       // ���ڸ߶�

// ����һ���̻����ṹ��
struct Jet
{
	int x, y;           // �̻�����ǰ����
	int hx, hy;         // ��ߵ����꣨Ŀ��߶ȣ�
	bool is_launch;     // �Ƿ����ڷ���״̬
	IMAGE img[2];       // ��֡����ͼ��
	byte n : 1;         // λ�Σ�ֻ��Ϊ0��1�������л�����֡
} jet[NUM];

// ����һ���̻���
void creat_jet()
{
	int i = rand() % NUM;      // ���ѡ��һ���̻�����
	if (jet[i].is_launch == false) {
		jet[i].x = rand() % (WIDTH - 20);          // ���������
		jet[i].y = rand() % 100 + HEIGHT;          // ����ڴ��ڵײ�����һ��
		jet[i].hy = rand() % (HEIGHT / 2) + 80;    // ��ߵ����ϰ벿��(����С��y)
		jet[i].hx = jet[i].x;
		jet[i].is_launch = true;                    // ���Ϊ����״̬
	}
}

// �����̻����Žṹ��
struct Fire
{
	int cen_x, cen_y;     // �������ĵ���ͼƬ�ϵ�����
	int x, y;             // �����ڴ����ϵ�����
	int r;                // ��ǰ���Ű뾶
	int max_r;            // ������Ű뾶
	int width, height;    // ͼƬ���
	DWORD pixel[280][280];// �����̻�����ͼƬ����������
	bool is_show;         // �Ƿ�׼������ʾ����Ч��
	bool is_draw;         // �Ƿ����ڻ���
} fire[NUM];

// �����̻���������λ��
void launch() {
	for (int i = 0; i < NUM; i++) {
		if (jet[i].is_launch == true) {
			// ����SRCINVERTģʽ���Ƶ�ǰ֡ͼ�����ǰһ֡
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			if (jet[i].y > jet[i].hy)  // ��û����ߵ㣬�����ƶ�
			{
				jet[i].y -= 5;    // �����ƶ�5������
				jet[i].n++;       // �л�����֡
			}

			// ����SRCINVERTģʽ������֡��ʵ�ֶ���Ч��
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
		}
		// ������ߵ㣬ֹͣ���䣬׼������
		if (jet[i].y <= jet[i].hy)
		{
			jet[i].is_launch = false;
			fire[i].x = jet[i].x;
			fire[i].y = jet[i].y;
			fire[i].is_show = true;   // ����̻�׼������
		}
	}
}

// ��ʼ���̻���������
void Initdate(int i)
{
	fire[i].cen_x = 140;
	fire[i].cen_y = 140;
	fire[i].max_r = 70;
	fire[i].r = 0;
	fire[i].width = 280;
	fire[i].height = 280;
	fire[i].is_draw = false;
	fire[i].is_show = false;
}

// ��ӭ���֣���ʾʤ����ʾ
void welcome()
{
	settextstyle(120, 0, "΢���ź�");
	settextcolor(RGB(255, 166, 94));
	outtextxy(180, 200, "��ϲ��ʤ���� !");
	Sleep(3000);  // ��ʾ3��
}

// �����̻�ͼƬ��Դ����ʼ���������
void loadImg()
{
	// ��ʼ������Ч��ͼ
	IMAGE bloomImg, tImg;
	loadimage(&bloomImg, ".\\resources\\image\\bloom_bouquet.png", 2520, 280); // һ�Ŵ�ͼ����9��280x280�̻�
	for (int i = 0; i < NUM; i++)
	{
		Initdate(i);   // ��ʼ��ÿ���̻�����
		int bouquet_index = i % 9;   // ȡ9���е���һ��

		SetWorkingImage(&bloomImg);   // ���õ�ǰ��ͼĿ��Ϊ��ͼ
		getimage(&tImg, bouquet_index * 280, 0, 280, 280);  // ��ȡ�����̻�ͼ
		SetWorkingImage(&tImg);  // ���û�ͼĿ��Ϊ����ͼ

		// ����ÿ��������ɫֵ��fire[i].pixel�У��������ڻ���
		for (int a = 0; a < 280; a++)
		{
			for (int b = 0; b < 280; b++)
			{
				fire[i].pixel[a][b] = getpixel(a, b);
			}
		}
	}

	// ��ʼ���̻���ͼ��
	IMAGE jetImg;
	loadimage(&jetImg, ".\\resources\\image\\firework_bomb.png", 200, 50);
	SetWorkingImage(&jetImg);
	for (int i = 0; i < NUM; i++) {
		int n = rand() % 5;     // ���ѡ��֡
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], n * 20 + 100, 0, 20, 50);
		jet[i].is_launch = false;  // ��ʼ��Ϊδ����״̬
	}
	SetWorkingImage();   // �ָ�Ĭ�ϻ�ͼĿ��
}

// �����̻�����Ч��
void bloom(DWORD* pMem)
{
	for (int i = 0; i < NUM; i++)
	{
		if (fire[i].is_show)   // ֻ��׼�����˲Ÿ������Ű뾶
		{
			if (fire[i].r < fire[i].max_r)
			{
				fire[i].r++;    // �������Ű뾶
				fire[i].is_draw = true;
			}
			else
			{
				Initdate(i);   // �������뾶����������
			}
		}

		if (fire[i].is_draw)   // ��������
		{
			// ʹ�ü����귽�̻�Բ��
			for (double a = 0; a < 2 * PI; a += 0.01)
			{
				int img_x = fire[i].cen_x + fire[i].r * cos(a);  // ����ͼƬ�ϵ�x
				int img_y = fire[i].cen_y + fire[i].r * sin(a);  // ����ͼƬ�ϵ�y
				if (img_x > 0 && img_x < fire[i].width && img_y > 0 && img_y < fire[i].height)
				{
					int win_x = fire[i].x + fire[i].r * cos(a);   // ���ڻ���λ��x
					int win_y = fire[i].y + fire[i].r * sin(a);   // ���ڻ���λ��y
					if (win_x > 0 && win_x < WIDTH && win_y > 0 && win_y < HEIGHT)
					{
						pMem[win_y * WIDTH + win_x] = BGR(fire[i].pixel[img_x][img_y]);  // �������ص���ɫ
					}
				}
			}
		}
	}
}

// ���ذ�ť�ĳߴ��λ�ã��������
const int returnBtnWidth = 100;
const int returnBtnHeight = 40;
const int returnBtnMargin = 20; // �������½Ǳ߾�

// ���Ʒ��ذ�ť�������������true��ʾ����˷��ذ�ť
bool drawReturnButton() {
	int btnX = WIDTH - returnBtnWidth - returnBtnMargin;         // ��ťX����
	int btnY = HEIGHT - returnBtnHeight - returnBtnMargin;       // ��ťY����

	// �����ȡ��ע�����´�����ư�ť������������
	// setfillcolor(RGB(200, 200, 200));
	// solidrectangle(btnX, btnY, btnX + returnBtnWidth, btnY + returnBtnHeight);

	settextstyle(40, 0, "΢���ź�");
	settextcolor(WHITE);
	setbkmode(TRANSPARENT);
	outtextxy(btnX + 20, btnY - 30, "����");  // ���ư�ť���֣���΢����ƫ��

	// ���������¼�
	if (MouseHit()) {
		MOUSEMSG m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			// �жϵ��λ���Ƿ��ڰ�ť������
			if (m.x >= btnX && m.x <= btnX + returnBtnWidth &&
				m.y >= btnY - 30 && m.y <= btnY + returnBtnHeight - 30) {
				return true;  // ����˷��ذ�ť
			}
		}
	}
	return false;  // δ������ذ�ť
}

// �̻��������������̻���ʾ���߼�
void fireworks() {
	stop_music();         // ֹͣ�������֣��������

	victory_music();      // ����ʤ�����֣�ѭ�����ţ�

	initgraph(WIDTH, HEIGHT);
	srand((unsigned)time(NULL));

	welcome();            // ��ʾ��ӭ���֣�ͣ3��

	// ��ʼ���̻���״̬������
	for (int i = 0; i < NUM; i++) {
		jet[i].x = 0;
		jet[i].y = HEIGHT;
		jet[i].hx = 0;
		jet[i].hy = HEIGHT / 2;
		jet[i].n = 0;
		jet[i].is_launch = false;
		Initdate(i);
	}

	loadImg();                 // ������ԴͼƬ

	DWORD* pMem = GetImageBuffer();  // ��ȡͼ�񻺳���ָ��

	while (1)
	{
		// ��������������أ�ģ���̻���˸Ч��
		for (int i = 0; i < WIDTH; i++) {
			for (int k = 0; k < 4; k++) {
				int x = rand() % WIDTH;
				int y = rand() % HEIGHT;
				if (y < HEIGHT) {
					pMem[y * WIDTH + x] = BLACK;
				}
			}
		}

		creat_jet();  // �����µ��̻����������

		launch();     // �����̻���������λ��

		bloom(pMem);  // �����̻������Ƶ�������

		if (drawReturnButton()) {   // �������˷��ذ�ť
			stop_music();           // ֹͣ����
			closegraph();          // �ر�ͼ�δ���
			menu_page();           // ���ز˵�ҳ��
			return;
		}

		Sleep(10);  // ����ˢ��Ƶ�ʣ�����CPUռ�ù���
	}
}
