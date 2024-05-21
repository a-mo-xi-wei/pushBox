#pragma once
#include<SDL.h> 
#include<SDL_image.h>
#include<SDL_ttf.h>//文字
#include<SDL_mixer.h>//音乐


#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//地图行列
#define ROW			8
#define COLS		8
//小图大小
#define IMGW		60
#define IMGH		60
//窗口大小
#define WIDTH		ROW*IMGH
#define HEIGHT		COLS*IMGW

enum Element { Wall = 1, Road = 0, Ball = 4, Board = 3, Chick = 7, Role = 5, SRole = 8 };