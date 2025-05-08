#pragma once


//form GLFW(glfw 的键码符合 ASCII 编码的标准,将键码转换为 char 可以输出对应的键)
#define SAKURA_KEY_SPACE              32
#define SAKURA_KEY_APOSTROPHE         39  /* ' */
#define SAKURA_KEY_COMMA              44  /* , */
#define SAKURA_KEY_MINUS              45  /* - */
#define SAKURA_KEY_PERIOD             46  /* . */
#define SAKURA_KEY_SLASH              47  /* / */
#define SAKURA_KEY_0                  48
#define SAKURA_KEY_1                  49
#define SAKURA_KEY_2                  50
#define SAKURA_KEY_3                  51
#define SAKURA_KEY_4                  52
#define SAKURA_KEY_5                  53
#define SAKURA_KEY_6                  54
#define SAKURA_KEY_7                  55
#define SAKURA_KEY_8                  56
#define SAKURA_KEY_9                  57
#define SAKURA_KEY_SEMICOLON          59  /* ; */
#define SAKURA_KEY_EQUAL              61  /* = */
#define SAKURA_KEY_A                  65
#define SAKURA_KEY_B                  66
#define SAKURA_KEY_C                  67
#define SAKURA_KEY_D                  68
#define SAKURA_KEY_E                  69
#define SAKURA_KEY_F                  70
#define SAKURA_KEY_G                  71
#define SAKURA_KEY_H                  72
#define SAKURA_KEY_I                  73
#define SAKURA_KEY_J                  74
#define SAKURA_KEY_K                  75
#define SAKURA_KEY_L                  76
#define SAKURA_KEY_M                  77
#define SAKURA_KEY_N                  78
#define SAKURA_KEY_O                  79
#define SAKURA_KEY_P                  80
#define SAKURA_KEY_Q                  81
#define SAKURA_KEY_R                  82
#define SAKURA_KEY_S                  83
#define SAKURA_KEY_T                  84
#define SAKURA_KEY_U                  85
#define SAKURA_KEY_V                  86
#define SAKURA_KEY_W                  87
#define SAKURA_KEY_X                  88
#define SAKURA_KEY_Y                  89
#define SAKURA_KEY_Z                  90
#define SAKURA_KEY_LEFT_BRACKET       91  /* [ */
#define SAKURA_KEY_BACKSLASH          92  /* \ */
#define SAKURA_KEY_RIGHT_BRACKET      93  /* ] */
#define SAKURA_KEY_GRAVE_ACCENT       96  /* ` */
#define SAKURA_KEY_WORLD_1            161 /* non-US #1 */
#define SAKURA_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define SAKURA_KEY_ESCAPE             256
#define SAKURA_KEY_ENTER              257
#define SAKURA_KEY_TAB                258
#define SAKURA_KEY_BACKSPACE          259
#define SAKURA_KEY_INSERT             260
#define SAKURA_KEY_DELETE             261
#define SAKURA_KEY_RIGHT              262
#define SAKURA_KEY_LEFT               263
#define SAKURA_KEY_DOWN               264
#define SAKURA_KEY_UP                 265
#define SAKURA_KEY_PAGE_UP            266
#define SAKURA_KEY_PAGE_DOWN          267
#define SAKURA_KEY_HOME               268
#define SAKURA_KEY_END                269
#define SAKURA_KEY_CAPS_LOCK          280
#define SAKURA_KEY_SCROLL_LOCK        281
#define SAKURA_KEY_NUM_LOCK           282
#define SAKURA_KEY_PRINT_SCREEN       283
#define SAKURA_KEY_PAUSE              284
#define SAKURA_KEY_F1                 290
#define SAKURA_KEY_F2                 291
#define SAKURA_KEY_F3                 292
#define SAKURA_KEY_F4                 293
#define SAKURA_KEY_F5                 294
#define SAKURA_KEY_F6                 295
#define SAKURA_KEY_F7                 296
#define SAKURA_KEY_F8                 297
#define SAKURA_KEY_F9                 298
#define SAKURA_KEY_F10                299
#define SAKURA_KEY_F11                300
#define SAKURA_KEY_F12                301
#define SAKURA_KEY_F13                302
#define SAKURA_KEY_F14                303
#define SAKURA_KEY_F15                304
#define SAKURA_KEY_F16                305
#define SAKURA_KEY_F17                306
#define SAKURA_KEY_F18                307
#define SAKURA_KEY_F19                308
#define SAKURA_KEY_F20                309
#define SAKURA_KEY_F21                310
#define SAKURA_KEY_F22                311
#define SAKURA_KEY_F23                312
#define SAKURA_KEY_F24                313
#define SAKURA_KEY_F25                314
#define SAKURA_KEY_KP_0               320
#define SAKURA_KEY_KP_1               321
#define SAKURA_KEY_KP_2               322
#define SAKURA_KEY_KP_3               323
#define SAKURA_KEY_KP_4               324
#define SAKURA_KEY_KP_5               325
#define SAKURA_KEY_KP_6               326
#define SAKURA_KEY_KP_7               327
#define SAKURA_KEY_KP_8               328
#define SAKURA_KEY_KP_9               329
#define SAKURA_KEY_KP_DECIMAL         330
#define SAKURA_KEY_KP_DIVIDE          331
#define SAKURA_KEY_KP_MULTIPLY        332
#define SAKURA_KEY_KP_SUBTRACT        333
#define SAKURA_KEY_KP_ADD             334
#define SAKURA_KEY_KP_ENTER           335
#define SAKURA_KEY_KP_EQUAL           336
#define SAKURA_KEY_LEFT_SHIFT         340
#define SAKURA_KEY_LEFT_CONTROL       341
#define SAKURA_KEY_LEFT_ALT           342
#define SAKURA_KEY_LEFT_SUPER         343
#define SAKURA_KEY_RIGHT_SHIFT        344
#define SAKURA_KEY_RIGHT_CONTROL      345
#define SAKURA_KEY_RIGHT_ALT          346
#define SAKURA_KEY_RIGHT_SUPER        347
#define SAKURA_KEY_MENU               348

#define SAKURA_KEY_LAST               SAKURA_KEY_MENU