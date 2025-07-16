#pragma once
#include <graphics.h>

// 初始化锤子资源
void init_hammer();

// 更新锤子动画状态
void update_hammer();


// 开始击打动画（点击时调用）
void start_hammer();

// 判断是否正在播放击打动画
bool is_hammer_striking();

void draw_hammer_controlled(int curMouseX, int curMouseY);

