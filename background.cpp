// background.cpp
#include "background.h"
#include <graphics.h>

// 背景缓存图像
IMAGE bkImg;

// 返回背景图指针
IMAGE* get_background_image() {
    return &bkImg;
}

// 地鼠洞位置（3行 × 3列）
const int HOLE_ROWS = 3;
const int HOLE_COLS = 3;
const int HOLE_WIDTH = 340 * 0.5;
const int HOLE_HEIGHT = 235 * 0.5;
const int HOLE_SPACING_X = 100 * 0.8;
const int HOLE_SPACING_Y = 80 * 0.8;
const int HOLE_START_X = 160;
const int HOLE_START_Y = 240 + 20;


void loading_bk_page() {
    // 初始化背景缓存图像为游戏主窗口大小
    bkImg.Resize(980, 980);
    SetWorkingImage(&bkImg); // 后续操作都画到这个图像上

    // 加载背景图片（无遮罩，直接贴图）
    IMAGE gaming_bg;
    loadimage(&gaming_bg, ".\\resources\\image\\bkimage.png", 980, 980);
    putimage(0, 0, &gaming_bg); // 背景铺满窗口

    // 加载 logo 和遮罩图（logo 使用遮罩实现透明）
    IMAGE logo, logo_mask;
    loadimage(&logo, ".\\resources\\image\\logo.png", 250, 250);             // 缩小显示
    loadimage(&logo_mask, ".\\resources\\image\\logo_mask_image.png", 250, 250);
    putimage(10, 10,&logo_mask, SRCPAINT);  // 先贴遮罩图，保留透明区域
    putimage(10, 10, &logo,SRCAND); // 再贴图片，实现透明贴图

    // 加载老鼠洞及其遮罩
    IMAGE hole, hole_mask;
    loadimage(&hole_mask, ".\\resources\\image\\hole_mask.png", HOLE_WIDTH, HOLE_HEIGHT);
    loadimage(&hole, ".\\resources\\image\\hole.png", HOLE_WIDTH, HOLE_HEIGHT);


    // 依次绘制9个老鼠洞（3×3），带透明遮罩
    for (int row = 0; row < HOLE_ROWS; row++) {
        for (int col = 0; col < HOLE_COLS; col++) {
            int x = HOLE_START_X + col * (HOLE_WIDTH + HOLE_SPACING_X);
            int y = HOLE_START_Y + row * (HOLE_HEIGHT + HOLE_SPACING_Y);
                putimage(x, y, &hole_mask, SRCPAINT);
                putimage(x, y, &hole, SRCAND);
                
        }
    }

    SetWorkingImage(nullptr); // 恢复默认工作窗口
}
