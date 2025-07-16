#include "time_manager.h"

static DWORD startTime = 0;
static int gameDuration = 45; // Ä¬ÈÏ 45 Ãë

void init_game_timer() {
    startTime = GetTickCount();
}

int get_remaining_time() {
    DWORD now = GetTickCount();
    int elapsed = (now - startTime) / 1000;
    int remain = gameDuration - elapsed;
    return remain > 0 ? remain : 0;
}

bool is_time_up() {
    return get_remaining_time() <= 0;
}

void set_game_duration(int seconds) {
    gameDuration = seconds;
}

