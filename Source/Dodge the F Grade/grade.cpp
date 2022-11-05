#include "header.h"
#include "grade.h"

extern int arrayGame[][MAP_WIDTH + 1], gameTime;

// ���� ���� ��ǥ�� ����(A+ ~ D) �������� ���� �� ǥ��
void Grade::appear(int appearPeriod)
{
	if (!(gameTime % (appearPeriod * GAME_SPEED)))
	{
		_xPos = rand() % (MAP_WIDTH - 1) + 1;
		_yPos = rand() % (MAP_HEIGHT - 1) + 1;
		if (arrayGame[_yPos][_xPos])
			appear(appearPeriod);
		else
			arrayGame[_yPos][_xPos] = rand() % 7 + A_PLUS;
	}
}