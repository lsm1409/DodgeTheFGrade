#pragma once

// ����� ���� ����� �ƴ� ����� ���� ����
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

// Ű �ڵ�
enum InputType { KEY_LEFT = 75, KEY_RIGHT = 77, KEY_UP = 72, KEY_DOWN = 80 };
// �� ���� ���
enum MapSize { MAP_WIDTH = 20, MAP_HEIGHT = 20, MIDDLE_WIDTH = MAP_WIDTH / 2, MIDDLE_HEIGHT = MAP_HEIGHT / 2 };
// F �߻� ����
enum StartType { START_LEFT, START_RIGHT, START_UP, START_DOWN };
// �� ���
enum MapElement { BLANK, CURSOR, F_ZERO, BORDER_ROW, BORDER_COLUMN, CORNER_UPPER_LEFT, CORNER_UPPER_RIGHT, CORNER_LOWER_RIGHT, CORNER_LOWER_LEFT, A_PLUS, A_ZERO, B_PLUS, B_ZERO, C_PLUS, C_ZERO, D_ZERO };
// ���� ����
enum GameOption { MAX_LIFE = 5, GAME_SPEED = 200, OBJECT_SPEED = 8, ENDLESS = 2, SET_TIME = 100, SET_CREDIT = 14, SHOW_X = 3, SHOW_Y = 3 };