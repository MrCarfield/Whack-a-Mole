#pragma once
// background.h
#pragma once
#include <graphics.h>

// 背景图缓存，用于游戏循环中重复使用
extern IMAGE bkImg;
extern void putimage_alpha(int x, int y, IMAGE* img);
// 背景绘制函数：加载背景、logo和老鼠洞并绘制到 bkImg 中
void loading_bk_page();
IMAGE* get_background_image();  // 提供背景图指针


