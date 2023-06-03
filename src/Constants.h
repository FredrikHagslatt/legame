#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Core */
inline constexpr unsigned short WINDOWWIDTH{1200};
inline constexpr unsigned short WINDOWHEIGHT{720};
inline constexpr unsigned short FPS{144};
inline constexpr unsigned short MILLISECS_PER_FRAME{1000 / FPS};
inline constexpr bool MAX_FPS_UNLOCKED = false;

/*  Constants for TopDown Style Scenes  */
inline constexpr unsigned short USERINTERFACEHEIGHT{144};
inline constexpr unsigned short GAMEWINDOWWIDTH{1200};
inline constexpr unsigned short GAMEWINDOWHEIGHT{WINDOWHEIGHT - USERINTERFACEHEIGHT};
inline constexpr unsigned short TILESIZE{16};
inline constexpr double SCALE{3.0};

#endif