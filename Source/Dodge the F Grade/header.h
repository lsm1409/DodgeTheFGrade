#pragma once

// 사용자 정의 헤더가 아닌 헤더를 전부 포함
#include <conio.h>
#include <ctime>
#include <iostream>
#include <string>
#include <Windows.h>
#include "cursor.h"

using namespace std;

void gotoXY(short, short);
void hideCursor();
void title();
void draw(bool, Cursor &);
void initialize(bool);
void loadGame(int, int);
void endGame(bool, bool, bool &, Cursor &);

// 키 코드
enum InputType { KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80 };
// 맵 관련 상수
enum MapSize { MAP_WIDTH = 20, MAP_HEIGHT = 20, MIDDLE_WIDTH = MAP_WIDTH / 2, MIDDLE_HEIGHT = MAP_HEIGHT / 2 };
// F 발사 방향
enum StartType { START_LEFT, START_RIGHT, START_UP, START_DOWN };
// 맵 요소
enum MapElement { BLANK, CURSOR, F_ZERO, BORDER_ROW, BORDER_COLUMN, CORNER_UPPER_LEFT, CORNER_UPPER_RIGHT, CORNER_LOWER_RIGHT, CORNER_LOWER_LEFT, A_PLUS, A_ZERO, B_PLUS, B_ZERO, C_PLUS, C_ZERO, D_ZERO };
// 게임 설정
enum GameOption { MAX_LIFE = 5, GAME_SPEED = 200, OBJECT_SPEED = 8, ENDLESS = 2, SET_TIME = 100, SET_CREDIT = 14, SHOW_X = 3, SHOW_Y = 3 };