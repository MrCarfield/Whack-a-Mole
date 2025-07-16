// hammer.cpp
#include "hammer.h"
#include <graphics.h>
#include <windows.h>
#include <cstdio>
#include "music.h"

#define HAMMER_FRAME_INTERVAL 30

static IMAGE hammerImgs[7];
static IMAGE hammerMasks[7];
static int hammerFrame = -1;
static DWORD lastUpdateTime = 0;
static bool hasPlayedSound = false;
static int lastX = 0, lastY = 0;

void init_hammer() {
    for (int i = 0; i < 7; ++i) {
        char imgPath[100], maskPath[100];
        sprintf_s(imgPath, sizeof(imgPath), ".\\resources\\image\\hammer_%d.png", i + 1);
        sprintf_s(maskPath, sizeof(maskPath), ".\\resources\\image\\hammer_%d_mask.png", i + 1);
        loadimage(&hammerImgs[i], imgPath, 170, 170);
        loadimage(&hammerMasks[i], maskPath, 170, 170);
    }
    hammerFrame = -1;
    lastUpdateTime = GetTickCount();
    hasPlayedSound = false;
}

bool is_hammer_striking() {
    return hammerFrame != -1;
}

void start_hammer() {
    if (!is_hammer_striking()) {
        hammerFrame = 0;
        lastUpdateTime = GetTickCount();
        hasPlayedSound = false;
    }
}

void update_hammer() {
    if (is_hammer_striking()) {
        DWORD now = GetTickCount();
        if (now - lastUpdateTime > HAMMER_FRAME_INTERVAL) {
            hammerFrame++;
            lastUpdateTime = now;
            if (hammerFrame == 1 && !hasPlayedSound) {
                punch_music();
                hasPlayedSound = true;
            }
            if (hammerFrame >= 7) {
                hammerFrame = -1;
                hasPlayedSound = false;
            }
        }
    }
}

void draw_hammer_controlled(int curMouseX, int curMouseY) {
    if (!is_hammer_striking()) {
        lastX = curMouseX;
        lastY = curMouseY;
    }
    int offsetX = -60, offsetY = -80;
    int frame = (hammerFrame == -1 ? 0 : hammerFrame);
    putimage(lastX + offsetX, lastY + offsetY, &hammerMasks[frame], SRCPAINT);
    putimage(lastX + offsetX, lastY + offsetY, &hammerImgs[frame], SRCAND);
}
