#include "header.h"

extern int arrayGame[][MAP_WIDTH + 1], life;

// 판 정중앙에 커서를 위치시키고 표시
Cursor::Cursor()
{
	_xPos = MIDDLE_WIDTH;
	_yPos = MIDDLE_HEIGHT;
	arrayGame[_yPos][_xPos] = CURSOR;
	creditNum = 0;
	gradeAvg = 0;
	gradeSum = 0;
}

// 각 키 입력을 받았을 때 커서를 움직이는 함수
void Cursor::move(int input)
{
	switch (input)
	{
	case KEY_LEFT:								// 해당 키를 입력 받았을 때
		switch (arrayGame[_yPos][_xPos - 1])	// 이동하려는 칸의 상태가
		{
		case BLANK:								// 공백이면 이동
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			break;
		case F_ZERO:							// F면 목숨 -1
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			life--;
			break;
		case A_PLUS:							// A+면 4.5점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(4.5);
			break;
		case A_ZERO:							// A면 4점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(4.0);
			break;
		case B_PLUS:							// B+면 3.5점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(3.5);
			break;
		case B_ZERO:							// B이면 3점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(3.0);
			break;
		case C_PLUS:							// C+면 2.5점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(2.5);
			break;
		case C_ZERO:							// C면 2점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(2.0);
			break;
		case D_ZERO:							// D이면 1점 추가하여 평량평균 계산
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(1.0);
			break;
		}
		break;
	case KEY_RIGHT:
		switch (arrayGame[_yPos][_xPos + 1])
		{
		case BLANK:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			break;
		case F_ZERO:
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			life--;
			break;
		case A_PLUS:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(4.5);
			break;
		case A_ZERO:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(4.0);
			break;
		case B_PLUS:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(3.5);
			break;
		case B_ZERO:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(3.0);
			break;
		case C_PLUS:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(2.5);
			break;
		case C_ZERO:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(2.0);
			break;
		case D_ZERO:
			arrayGame[_yPos][++_xPos] = CURSOR;
			arrayGame[_yPos][_xPos - 1] = BLANK;
			calcGrade(1.0);
			break;
		}
		break;
	case KEY_UP:
		switch (arrayGame[_yPos - 1][_xPos])
		{
		case BLANK:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			break;
		case F_ZERO:
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			life--;
			break;
		case A_PLUS:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(4.5);
			break;
		case A_ZERO:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(4.0);
			break;
		case B_PLUS:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(3.5);
			break;
		case B_ZERO:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(3.0);
			break;
		case C_PLUS:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(2.5);
			break;
		case C_ZERO:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(2.0);
			break;
		case D_ZERO:
			arrayGame[--_yPos][_xPos] = CURSOR;
			arrayGame[_yPos + 1][_xPos] = BLANK;
			calcGrade(1.0);
			break;
		}
		break;
	case KEY_DOWN:
		switch (arrayGame[_yPos + 1][_xPos])
		{
		case BLANK:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			break;
		case F_ZERO:
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			life--;
			break;
		case A_PLUS:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(4.5);
			break;
		case A_ZERO:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(4.0);
			break;
		case B_PLUS:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(3.5);
			break;
		case B_ZERO:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(3.0);
			break;
		case C_PLUS:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(2.5);
			break;
		case C_ZERO:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(2.0);
			break;
		case D_ZERO:
			arrayGame[++_yPos][_xPos] = CURSOR;
			arrayGame[_yPos - 1][_xPos] = BLANK;
			calcGrade(1.0);
			break;
		}
	}
}

// 학점에 따라 평점 계산
void Cursor::calcGrade(double grade)
{
	gradeSum += grade;
	gradeAvg = gradeSum / ++creditNum;
}