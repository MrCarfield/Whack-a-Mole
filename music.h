#pragma once
//播放背景音乐 :
//播放击打音效:
//播放地鼠出现音效:
//播放结束音乐:
//播放启动音乐:
void bk_music();             // 循环播放背景音乐
void stop_bk_music();        // 停止背景音乐

void punch_music();          // 播放击打音效
void mouse_show_music();     // 播放地鼠出现音效

void end_music();            // 播放游戏结束音乐
void start_music();          // 播放游戏启动音乐
void victory_music();        // 播放胜利音乐（循环）

void stop_music();           // 停止所有正在播放的音乐
