# Whack-a-Mole
基于c++和easyx实现的打地鼠游戏,简单有趣,结尾有烟花哦
本项目是一个基于 C++ 和 EasyX 图形库开发的“打地鼠”小游戏，旨在通过学习图形绘制、多媒体播放、事件响应和动画处理等内容，提高学生对图形界面编程和模块化开发的掌握程度。项目采用模块化设计，共分为菜单页面、游戏主页面、地鼠逻辑、锤子动画、背景音乐、倒计时控制、胜利失败界面等多个功能模块，具有较好的可扩展性与可维护性。
项目运行后，用户首先看到游戏主菜单，可选择查看游戏规则或开始游戏。游戏过程中，地鼠会在 3×3 的九宫格随机出现，玩家通过鼠标点击控制锤子击打地鼠，并伴随打击音效与动画，游戏限时 45 秒，最终根据得分判断胜负。
 
（1）菜单界面：
•	背景图：卡通风格；
•	按钮：游戏规则、开始游戏、退出游戏；
•	Logo：左上角显示项目标题。

 <img width="654" height="674" alt="image" src="https://github.com/user-attachments/assets/6f9ef1fa-3633-4062-9582-0c4d90598fbe" />

（2）游戏界面：
•	背景图：草地/土洞样式；
•	地鼠洞：3×3 布局；
•	地鼠：动画贴图随机出现；
•	锤子：跟随鼠标，点击时播放动画；
•	倒计时：屏幕上方显示；
•	分数：右上角显示分数。

<img width="639" height="659" alt="image" src="https://github.com/user-attachments/assets/cf556115-6f36-460d-b728-823a49f64b8a" />


（3）规则页
•	规则页：简洁背景 + 文本框；

 <img width="614" height="634" alt="image" src="https://github.com/user-attachments/assets/abb97f05-6947-4f2f-9614-037389790add" />

 
 (4)胜利页
•		胜利页:显示”恭喜您胜利啦 !”,并播放烟花结算页面

 <img width="626" height="647" alt="image" src="https://github.com/user-attachments/assets/b2b8ebf6-15b8-4070-aedc-80de9245a2be" />
<img width="644" height="662" alt="image" src="https://github.com/user-attachments/assets/e86438c4-cb98-4679-bacb-6f23b62de341" />

 (5)失败页：
•	失败页：显示“失败”，有“返回”按钮。

 <img width="628" height="643" alt="image" src="https://github.com/user-attachments/assets/af9284e5-9e14-47ee-a6bc-7d445c31d691" />

流程设计
<img width="474" height="958" alt="image" src="https://github.com/user-attachments/assets/8b4858cc-2ccb-43d8-8bab-2307e0255552" />


模块/类名	文件	功能描述
GameManager	main.cpp	主流程控制器，负责游戏启动、页面跳转和模块初始化
PageManager	menu_page.h, end_page.h	控制菜单、规则、胜利、失败页面的显示与跳转
BackgroundView	background.h	背景图像加载与绘制
TimerSystem	time_manager.h	控制游戏倒计时（45 秒），提供时间状态
ShowLeftTime	show_left_time.h	在界面上实时绘制剩余时间文本
MouseInput	mouse.h	鼠标点击判定，获取点击坐标
HammerAnim	hammer.h	多帧锤子动画控制，响应点击动作
MusicCtrl	music.h	控制背景音乐、音效播放等音频交互
KeyMsgCtrl	key_msg.h	控制键盘输入响应（如 ESC 退出等）
Fireworks	fireworks.h	游戏胜利后播放烟花动画效果
地鼠控制	gaming.h	地鼠状态机实现，控制地鼠出现、消失和判定是否击中
