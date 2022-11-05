#include "header.h"
#include "F.h"

extern int arrayGame[][MAP_WIDTH + 1], gameTime, life;

F_Shot::F_Shot()
{
	_xPos = 0;
	_yPos = 0;
	startType = 0;
	running = false;
}

// F�� �߻� ������ ���·� ������ִ� �Լ�
void F_Shot::set(int StartTime)
{
	if (!running && gameTime > (StartTime * GAME_SPEED))	// running�� false�̰� i�� SetStart�� �Ѿ�� �۵��Ͽ� ���ο� ��ǥ�� ����
	{
		startType = rand() % 4;				// F �߻� ������ 4���� �� ���Ƿ� ����

		switch (startType)
		{
		case START_LEFT:					// ���ʿ��� ����
			_xPos = 1;
			_yPos = rand() % (MAP_HEIGHT - 1) + 1;
			break;
		case START_RIGHT:					// �����ʿ��� ����
			_xPos = MAP_WIDTH - 1;
			_yPos = rand() % (MAP_HEIGHT - 1) + 1;
			break;
		case START_UP:						// ���ʿ��� ����
			_xPos = rand() % (MAP_WIDTH - 1) + 1;
			_yPos = 1;
			break;
		case START_DOWN:					// �Ʒ��ʿ��� ����
			_xPos = rand() % (MAP_WIDTH - 1) + 1;
			_yPos = MAP_HEIGHT - 1;
			break;
		}

		moveStart();
	}
}

// F�� �߻��ϴ� �Լ� (�߻� �� �ӵ� (�������� ������))
void F_Shot::move(int MovePeriod)
{
	if (running && !(gameTime % (MovePeriod * OBJECT_SPEED)))		// running�� true�� n�� �ֱ�� �۵��Ͽ� F�� ��������
	{
		switch (startType)
		{
		case START_LEFT:							// �ش� ������� ����� F��
			switch (arrayGame[_yPos][_xPos + 1])	// �̵��Ϸ��� ĭ�� ���°�
			{
			case CURSOR:							// Ŀ����� Life ����
				moveEnd();
				life--;
				break;
			case BORDER_COLUMN:						// �׵θ���� �̵� ����
				moveEnd();
				break;
			default:								// ������ ���� �̵�
				arrayGame[_yPos][++_xPos] = F_ZERO;
				arrayGame[_yPos][_xPos - 1] = BLANK;
				break;
			}
			break;
		case START_RIGHT:
			switch (arrayGame[_yPos][_xPos - 1])
			{
			case CURSOR:
				moveEnd();
				life--;
				break;
			case BORDER_COLUMN:
				moveEnd();
				break;
			default:
				arrayGame[_yPos][--_xPos] = F_ZERO;
				arrayGame[_yPos][_xPos + 1] = BLANK;
				break;
			}
			break;
		case START_UP:
			switch (arrayGame[_yPos + 1][_xPos])
			{
			case CURSOR:
				moveEnd();
				life--;
				break;
			case BORDER_ROW:
				moveEnd();
				break;
			default:
				arrayGame[++_yPos][_xPos] = F_ZERO;
				arrayGame[_yPos - 1][_xPos] = BLANK;
				break;
			}
			break;
		case START_DOWN:
			switch (arrayGame[_yPos - 1][_xPos])
			{
			case CURSOR:
				moveEnd();
				life--;
				break;
			case BORDER_ROW:
				moveEnd();
				break;
			default:
				arrayGame[--_yPos][_xPos] = F_ZERO;
				arrayGame[_yPos + 1][_xPos] = BLANK;
				break;
			}
			break;
		}
	}
}

// F ����� ������ Ȱ��ȭ
void F_Shot::moveStart()
{
	arrayGame[_yPos][_xPos] = F_ZERO;
	running = true;
}

// �������� ����� ������ ��Ȱ��ȭ
void F_Shot::moveEnd()
{
	arrayGame[_yPos][_xPos] = BLANK;
	running = false;
}
