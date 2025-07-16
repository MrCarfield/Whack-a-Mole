#include "music.h"
#include <graphics.h>
#include <mmsystem.h>
#include <thread>
#include <chrono>
#pragma comment(lib, "winmm.lib")

// ========== �������� ==========
void bk_music() {
    mciSendString("open .\\resources\\music\\bk_music.mp3 alias bk", NULL, 0, NULL);
    mciSendString("play bk repeat", NULL, 0, NULL);
}

void stop_bk_music() {
    mciSendString("stop bk", NULL, 0, NULL);
    mciSendString("close bk", NULL, 0, NULL);
}

// ========== ������Ч ==========
void punch_music() {
    mciSendString("open .\\resources\\music\\punch.mp3 alias punch", NULL, 0, NULL);
    mciSendString("play punch from 0", NULL, 0, NULL);
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    mciSendString("close punch", NULL, 0, NULL);
}

// ========== ���������Ч ==========
void mouse_show_music() {
    mciSendString("open .\\resources\\music\\mouse_show.mp3 alias show", NULL, 0, NULL);
    mciSendString("play show from 0", NULL, 0, NULL);
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    mciSendString("close show", NULL, 0, NULL);
}

// ========== ��Ϸ�������� ==========
void end_music() {
    mciSendString("open .\\resources\\music\\gameover.mp3 alias end", NULL, 0, NULL);
    mciSendString("play end from 0", NULL, 0, NULL);
}

// ========== ��Ϸ�������� ==========
void start_music() {
    mciSendString("open .\\resources\\music\\gamestart.mp3 alias start", NULL, 0, NULL);
    mciSendString("play start from 0", NULL, 0, NULL);
}

// ========== ʤ������ ==========
void victory_music() {
    mciSendString("open .\\resources\\music\\victory_music.mp3 alias victory", NULL, 0, NULL);
    mciSendString("play victory repeat", NULL, 0, NULL);
}

// ========== ֹͣ�������� ==========
void stop_music() {
    const char* aliases[] = { "bk", "punch", "show", "end", "start", "victory" };
    for (int i = 0; i < sizeof(aliases) / sizeof(aliases[0]); ++i) {
        char cmd[64];
        sprintf_s(cmd, sizeof(cmd), "close %s", aliases[i]);  // ʹ�ð�ȫ�汾
        mciSendString(cmd, NULL, 0, NULL);
    }
}

