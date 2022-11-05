#include "header.h"

extern int arrayGame[][MAP_WIDTH + 1], life;

// �� ���߾ӿ� Ŀ���� ��ġ��Ű�� ǥ��
Cursor::Cursor()
{
	_xPos = MIDDLE_WIDTH;
	_yPos = MIDDLE_HEIGHT;
	arrayGame[_yPos][_xPos] = CURSOR;
	creditNum = 0;
	gradeAvg = 0;
	gradeSum = 0;
}

// �� Ű �Է��� �޾��� �� Ŀ���� �����̴� �Լ�
void Cursor::move(int input)
{
	switch (input)
	{
	case KEY_LEFT:								// �ش� Ű�� �Է� �޾��� ��
		switch (arrayGame[_yPos][_xPos - 1])	// �̵��Ϸ��� ĭ�� ���°�
		{
		case BLANK:								// �����̸� �̵�
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			break;
		case F_ZERO:							// F�� ��� -1
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			life--;
			break;
		case A_PLUS:							// A+�� 4.5�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(4.5);
			break;
		case A_ZERO:							// A�� 4�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(4.0);
			break;
		case B_PLUS:							// B+�� 3.5�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(3.5);
			break;
		case B_ZERO:							// B�̸� 3�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(3.0);
			break;
		case C_PLUS:							// C+�� 2.5�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(2.5);
			break;
		case C_ZERO:							// C�� 2�� �߰��Ͽ� ����� ���
			arrayGame[_yPos][--_xPos] = CURSOR;
			arrayGame[_yPos][_xPos + 1] = BLANK;
			calcGrade(2.0);
			break;
		case D_ZERO:							// D�̸� 1�� �߰��Ͽ� ����� ���
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

// ������ ���� ���� ���
void Cursor::calcGrade(double grade)
{
	gradeSum += grade;
	gradeAvg = gradeSum / ++creditNum;
}