#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Core */
inline constexpr unsigned short WINDOWWIDTH{ 800 };
inline constexpr unsigned short WINDOWHEIGHT{ 600 };
inline constexpr unsigned short FPS {60};
inline constexpr unsigned short MILLISECS_PER_FRAME { 1000 / 60 };


/*  Constants for Stardew Style Scenes  */
inline constexpr unsigned short TILESIZE{ 16 };
inline constexpr double SCALE{ 3.0 };

//inline constexpr unsigned short CAMWIDTH{ 30 }; //Number or tiles to fit in camera
//inline constexpr float CAMHEIGHT{ CAMWIDTH * (float(SCREENHEIGHT) / float(SCREENWIDTH)) };
//inline constexpr unsigned short SCALE{ int(SCREENWIDTH / TILESIZE / CAMWIDTH) };

#endif //CONSTANTS_H