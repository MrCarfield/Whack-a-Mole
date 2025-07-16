#pragma once
#include <windows.h>

// 初始化游戏时间（记录开始时间）
void init_game_timer();

// 获取游戏剩余时间（单位：秒）
int get_remaining_time();

// 是否时间结束（返回 true 表示倒计时已结束）
bool is_time_up();

// 设置游戏持续时间（默认 60 秒，可自定义）
void set_game_duration(int seconds);


