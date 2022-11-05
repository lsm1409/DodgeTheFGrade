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

// F를 발사 가능한 상태로 만들어주는 함수
void F_Shot::set(int StartTime)
{
	if (!running && gameTime > (StartTime * GAME_SPEED))	// running이 false이고 i가 SetStart를 넘어서면 작동하여 새로운 좌표를 설정
	{
		startType = rand() % 4;				// F 발사 방향을 4방향 중 임의로 설정

		switch (startType)
		{
		case START_LEFT:					// 왼쪽에서 생성
			_xPos = 1;
			_yPos = rand() % (MAP_HEIGHT - 1) + 1;
			break;
		case START_RIGHT:					// 오른쪽에서 생성
			_xPos = MAP_WIDTH - 1;
			_yPos = rand() % (MAP_HEIGHT - 1) + 1;
			break;
		case START_UP:						// 위쪽에서 생성
			_xPos = rand() % (MAP_WIDTH - 1) + 1;
			_yPos = 1;
			break;
		case START_DOWN:					// 아래쪽에서 생성
			_xPos = rand() % (MAP_WIDTH - 1) + 1;
			_yPos = MAP_HEIGHT - 1;
			break;
		}

		moveStart();
	}
}

// F을 발사하는 함수 (발사 후 속도 (높을수록 느려짐))
void F_Shot::move(int MovePeriod)
{
	if (running && !(gameTime % (MovePeriod * OBJECT_SPEED)))		// running이 true면 n의 주기로 작동하여 F를 날려보냄
	{
		switch (startType)
		{
		case START_LEFT:							// 해당 방향부터 출발한 F는
			switch (arrayGame[_yPos][_xPos + 1])	// 이동하려는 칸의 상태가
			{
			case CURSOR:							// 커서라면 Life 깎임
				moveEnd();
				life--;
				break;
			case BORDER_COLUMN:						// 테두리라면 이동 종료
				moveEnd();
				break;
			default:								// 나머지 경우면 이동
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

// F 만들고 움직임 활성화
void F_Shot::moveStart()
{
	arrayGame[_yPos][_xPos] = F_ZERO;
	running = true;
}

// 공백으로 만들고 움직임 비활성화
void F_Shot::moveEnd()
{
	arrayGame[_yPos][_xPos] = BLANK;
	running = false;
}
