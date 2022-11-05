/*
최근에 변경된 사항: arrayCopy를 통한 게임 속도 개선 (0.9d)
재시작 시 최고 기록 출력 (0.9e)
앗! 이 뜨지 않는 문제 수정, 시간 제한 모드에서 도중에 죽으면 학점이 저장되지 않는 것으로 변경, 접근자(Accessor) 추가 및 인라인 함수화 (0.9f)
일정 이상의 학점을 수강하지 않으면 끝까지 버텨도 패배 처리 구현, 커서 자리에 학점 겹치지 않도록 개선, 매개 변수에 있던 속도 관련 상수들을 전부 함수에 작성 (0.9g)
난이도 조정, UI 전면 수정, 종료 함수 수정(0.9h)
빌드 전 확인 사항:	명령 프롬프트 [속성] - [옵션] 탭에서 레거시 콘솔 사용이 체크되어 있어야 함 (실행 환경이 Windows 7 이전이면 상관 없음)
- [글꼴] 탭에서 래스터 글꼴을 쓰지 말아야 함
*/
#include "header.h"
#include "F.h"
#include "grade.h"

int arrayGame[MAP_HEIGHT + 1][MAP_WIDTH + 1];	// 게임 맵 크기
int arrayCopy[MAP_HEIGHT + 1][MAP_WIDTH + 1];	// 게임 맵 복제
int gameTime;			// 게임 시작 후 시간
int life;				// 플레이어 목숨
static int maxEndless;	// 최고 기록 (버틴 시간)
static double maxGrade;	// 최고 기록 (평점)

int main()
{
	bool restart;	// 게임 재시작 결정 변수
	int buffer = 0;	// 사용자 입력을 저장하는 변수

	// Magic Formula로 학점 계산 결과를 소수 둘째 자리까지만 보여줌
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	srand((size_t)time(NULL));	// 랜덤 시드 설정
	hideCursor();				// 커서 숨기기
	title();					// 타이틀 화면 출력

	// 메인 화면 출력
	do
	{
		gotoXY(SHOW_X, SHOW_Y + 0);cout << "※	   게임 시작 전 명령 프롬프트 [속성]의	       ※";
		gotoXY(SHOW_X, SHOW_Y + 1);cout << "※     [옵션] 탭에서 레거시 콘솔 사용을 체크해주시고     ※";
		gotoXY(SHOW_X, SHOW_Y + 2);cout << "※ [글꼴] 탭에서 래스터 글꼴 이외의 것을 선택해 주십시오 ※";
		Sleep(CLOCKS_PER_SEC);
		gotoXY(SHOW_X, SHOW_Y + 4);cout << "험난한 한 학기가 시작되었습니다.";
		gotoXY(SHOW_X, SHOW_Y + 5);cout << "F를 피해 학사경고를 피하고 높은 학점을 취득하세요.";
		Sleep(CLOCKS_PER_SEC / 2);
		gotoXY(SHOW_X, SHOW_Y + 7);cout << "게임 모드를 선택하세요";
		gotoXY(SHOW_X, SHOW_Y + 9);cout << "1. 학점 모드";
		gotoXY(SHOW_X, SHOW_Y + 10);cout << "이번 학기 동안 얼마나 많은 학점을 모아";
		gotoXY(SHOW_X, SHOW_Y + 11);cout << "얼마나 높은 평점을 얻을 수 있을까요?";
		gotoXY(SHOW_X, SHOW_Y + 13);cout << "2. 무제한 모드";
		gotoXY(SHOW_X, SHOW_Y + 14);cout << "당신의 (운이 일부 들어간) 실력을 측정하세요.";
		gotoXY(SHOW_X, SHOW_Y + 15);cout << "얼마나 오래 버틸 수 있을까요?";
		gotoXY(SHOW_X, SHOW_Y + 17);cout << "게임을 중단하고 싶으면 1, 2번을 제외한 아무 키나 누르세요." << endl;

		//버퍼에 기록된 키값을 버림
		while (_kbhit())
			_getch();

		// 게임 모드 선택
		buffer = _getch();
		if (buffer == 49)
			loadGame(SET_TIME, MAX_LIFE);
		else if (buffer == 50)
			loadGame(0, 1);
		else
			goto GAME_OVER;

		cout << endl
			<< "	게임이 종료되었습니다." << endl
			<< "	다시 하려면 1번, 그만 하려면 2번을 누르세요." << endl;

		do
		{
			buffer = _getch();
			if (buffer == 49)
				restart = true;		// 1번을 누르면 재시작
			else if (buffer == 50)
				restart = false;	// 2번을 누르면 종료
		} while (buffer != 49 && buffer != 50);	// 1번과 2번 둘 중 하나를 누르지 않으면 무한 루프

		system("cls");
	} while (restart);

GAME_OVER:
	return 0;
}
void title() // 시작 화면
{
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "□□□□□□□□□□□□□□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "□□□□학□점□피□하□기□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "□□□□□Ｇ□Ａ□Ｍ□Ｅ□□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "□□□□광□운□대□학□교□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "□□고□급□프□로□그□래□밍□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "□□□이□강□훈□교□수□님□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 6);cout << "ㅡㅡㅡＴＥＲＭㅡＰＲＯＪＥＣＴㅡㅡ";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "□□□□2014726037□이상민□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "□□□□2014707040□유진혁□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "□□□□2013610017□안순호□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "□□□□□□□□□□□□□□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "□□ＰＲＥＳＳ□ＡＮＹ□ＫＥＹ□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "□□□□□□□□□□□□□□□□□";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "□□□□□□□□□□□□□□□□□";Sleep(300);
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "■■■■■■■■■■■■■■■■■";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "□□□□□□□□□□□□□□□□□";
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "■■■■학■점■피■하■기■■■■";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "□□□□학□점□피□하□기□□□□";
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "■■■■■Ｇ■Ａ■Ｍ■Ｅ■■■■■";Sleep(90);
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "□□□□□Ｇ□Ａ□Ｍ□Ｅ□□□□□";
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "■■■■광■운■대■학■교■■■■";Sleep(90);
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "□□□□광□운□대□학□교□□□□";
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "■■고■급■프■로■그■래■밍■■";Sleep(80);
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "□□고□급□프□로□그□래□밍□□";
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "■■■이■강■훈■교■수■님■■■";Sleep(80);
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "□□□이□강□훈□교□수□님□□□";Sleep(70);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "■■■■2014726037■이상민■■■■";Sleep(70);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "□□□□2014726037□이상민□□□□";
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "■■■■2014707040■유진혁■■■■";Sleep(60);
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "□□□□2014707040□유진혁□□□□";
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "■■■■2013610017■안순호■■■■";Sleep(60);
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "□□□□2013610017□안순호□□□□";
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "■■■■■■■■■■■■■■■■■";Sleep(50);
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "□□□□□□□□□□□□□□□□□";
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "■■ＰＲＥＳＳ■ＡＮＹ■ＫＥＹ■■";Sleep(50);
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "□□ＰＲＥＳＳ□ＡＮＹ□ＫＥＹ□□";
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "■■■■■■■■■■■■■■■■■";Sleep(40);
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "□□□□□□□□□□□□□□□□□";
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "■■■■■■■■■■■■■■■■■";Sleep(40);
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "□□□□□□□□□□□□□□□□□";Sleep(300);

	while (true)
	{
		if (_kbhit())
			break;
		gotoXY(SHOW_X, SHOW_Y + 10); cout << "■■■■■■■■■■■■■■■■■";
		gotoXY(SHOW_X, SHOW_Y + 11); cout << "■■ＰＲＥＳＳ■ＡＮＹ■ＫＥＹ■■";
		gotoXY(SHOW_X, SHOW_Y + 12); cout << "■■■■■■■■■■■■■■■■■"; Sleep(400);
		gotoXY(SHOW_X, SHOW_Y + 10); cout << "□□□□□□□□□□□□□□□□□";
		gotoXY(SHOW_X, SHOW_Y + 11); cout << "□□ＰＲＥＳＳ□ＡＮＹ□ＫＥＹ□□";
		gotoXY(SHOW_X, SHOW_Y + 12); cout << "□□□□□□□□□□□□□□□□□"; Sleep(400);
	}
	system("cls");
}
// 화면에 정의된 내용을 그림
void draw(bool timer, Cursor &Cursor)
{
	// 직전 배열과 비교해서 달라진 부분만 저장된 값을 다음처럼 출력
	for (short _yPos = 0; _yPos < MAP_HEIGHT + 1; _yPos++)
		for (short _xPos = 0; _xPos < MAP_WIDTH + 1; _xPos++)
			if (arrayCopy[_yPos][_xPos] != arrayGame[_yPos][_xPos])
			{
				gotoXY(_xPos, _yPos);
				switch (arrayGame[_yPos][_xPos])
				{
				case BLANK:
					cout << "　";
					break;
				case CURSOR:
					cout << "◇";
					break;
				case F_ZERO:
					cout << "Ｆ";
					break;
				case BORDER_ROW:
					cout << "─";
					break;
				case BORDER_COLUMN:
					cout << "│";
					break;
				case CORNER_UPPER_LEFT:
					cout << "┌";
					break;
				case CORNER_UPPER_RIGHT:
					cout << "┐";
					break;
				case CORNER_LOWER_RIGHT:
					cout << "┘";
					break;
				case CORNER_LOWER_LEFT:
					cout << "└";
					break;
				case A_PLUS:
					cout << "A+";
					break;
				case A_ZERO:
					cout << "Ａ";
					break;
				case B_PLUS:
					cout << "B+";
					break;
				case B_ZERO:
					cout << "Ｂ";
					break;
				case C_PLUS:
					cout << "C+";
					break;
				case C_ZERO:
					cout << "Ｃ";
					break;
				case D_ZERO:
					cout << "Ｄ";
					break;
				}
			}

	// 현재 배열을 카피 배열에 그대로 복사
	for (short _yPos = 0; _yPos < MAP_HEIGHT + 1; _yPos++)
		for (short _xPos = 0; _xPos < MAP_WIDTH + 1; _xPos++)
			arrayCopy[_yPos][_xPos] = arrayGame[_yPos][_xPos];

	// 정보를 화면에 출력하는 부분 (시간 제한/무제한 모드에 따라 갈림)
	if (timer)
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 3);
		cout << "개강한 지 " << gameTime / GAME_SPEED << "일째";

		gotoXY(MAP_WIDTH + 7, MIDDLE_HEIGHT - 2);
		cout << Cursor.getCreditNum();

		gotoXY(MAP_WIDTH + 5, MIDDLE_HEIGHT - 1);
		cout << Cursor.getGradeAvg();

		gotoXY(MAP_WIDTH + 12, MIDDLE_HEIGHT);
		for (int i = 0; i < life; i++)
			cout << "■";
		for (int i = 0; i < (MAX_LIFE - life); i++)
			cout << "□";
		if (!life)
		{
			gotoXY(MAP_WIDTH + 9, MIDDLE_HEIGHT);
			cout << " (앗! 끝나버렸네요...)";
		}
	}
	else
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 3);
		cout << "개강한 지 " << gameTime / GAME_SPEED / ENDLESS << "일째";
	}
}

// 시작 전에 배열 요소를 설정
void initialize(bool timer)
{
	// 맵을 전부 공백으로 채움
	for (size_t i = 0; i < MAP_HEIGHT + 1; i++)
		for (size_t j = 0; j < MAP_WIDTH + 1; j++)
			arrayGame[i][j] = BLANK;

	for (size_t i = 0; i < MAP_HEIGHT + 1; i++)
		for (size_t j = 0; j < MAP_WIDTH + 1; j++)
			arrayCopy[i][j] = BLANK;

	// 맵 테두리 생성
	for (size_t i = 0; i < MAP_WIDTH; i++)
	{
		arrayGame[0][i] = BORDER_ROW;
		arrayGame[MAP_HEIGHT][i] = BORDER_ROW;
		arrayGame[i][0] = BORDER_COLUMN;
		arrayGame[i][MAP_WIDTH] = BORDER_COLUMN;
	}

	arrayGame[MIDDLE_HEIGHT][MIDDLE_WIDTH] = CURSOR;
	arrayGame[0][0] = CORNER_UPPER_LEFT;
	arrayGame[0][MAP_WIDTH] = CORNER_UPPER_RIGHT;
	arrayGame[MAP_HEIGHT][MAP_WIDTH] = CORNER_LOWER_RIGHT;
	arrayGame[MAP_HEIGHT][0] = CORNER_LOWER_LEFT;

	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 5);
	cout << "  △   : ＵＰ";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 6);
	cout << "◁  ▷ : ＬＥＦＴ / ＲＩＧＨＴ";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 7);
	cout << "  ▽   : ＤＯＷＮ";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 8);
	cout << "ＣＴＲＬ + Ｃ : ＥＮＤ";

	// 타이머가 있는 게임이면 출력
	if (timer)
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 5);
		cout << "학점을 14학점 이상 취득하세요";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 2);
		cout << "최고기록 평점: " << maxGrade;
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 2);
		cout << "취득학점: ";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 1);
		cout << "평점: ";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT);
		cout << "학사경고까지 남은 F: ";
	}

	// 타이머가 없는 게임이면 출력
	else
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 2);
		cout << "최고 기록 일수: " << maxEndless << "일";
	}

	// 기록 변수 초기화
	gameTime = 0;
}

// 게임 실행 (제한 시간 (무제한이면 0), 제한 목숨)
void loadGame(int setTime, int setLife)
{
	Cursor Cursor;
	F_Shot F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20;
	Grade Grade;
	bool end = false;	// 게임 종료 변수 (무한 루프 탈출용)

	life = setLife;		// 라이프 설정

	system("cls");
	gotoXY(MIDDLE_WIDTH - 3, MIDDLE_HEIGHT);
	cout << "시작합니다." << endl;
	Sleep(CLOCKS_PER_SEC);
	system("cls");

	// 시간 무제한 모드
	if (!setTime)
	{
		initialize(false);
		draw(false, Cursor);

		while (!end)
		{
			gameTime++;

			if (_kbhit())
				Cursor.move(_getch());

			// F 출현 시기 (지정된 일수에 새 오브젝트 출현)
			F1.set(5 * ENDLESS);
			F2.set(7 * ENDLESS);
			F3.set(12 * ENDLESS);
			F4.set(10 * ENDLESS);
			F5.set(15 * ENDLESS);
			F6.set(17 * ENDLESS);
			F7.set(20 * ENDLESS);
			F8.set(22 * ENDLESS);
			F9.set(25 * ENDLESS);
			F10.set(27 * ENDLESS);
			F11.set(30 * ENDLESS);
			F12.set(32 * ENDLESS);
			F13.set(35 * ENDLESS);
			F14.set(37 * ENDLESS);
			F15.set(40 * ENDLESS);
			F16.set(42 * ENDLESS);
			F17.set(45 * ENDLESS);
			F18.set(47 * ENDLESS);
			F19.set(50 * ENDLESS);
			F20.set(52 * ENDLESS);

			// F 이동 속도 (높을수록 느려짐)
			F1.move(10 * ENDLESS);
			F2.move(10 * ENDLESS);
			F3.move(10 * ENDLESS);
			F4.move(9 * ENDLESS);
			F5.move(9 * ENDLESS);
			F6.move(9 * ENDLESS);
			F7.move(8 * ENDLESS);
			F8.move(8 * ENDLESS);
			F9.move(8 * ENDLESS);
			F10.move(7 * ENDLESS);
			F11.move(7 * ENDLESS);
			F12.move(7 * ENDLESS);
			F13.move(6 * ENDLESS);
			F14.move(6 * ENDLESS);
			F15.move(6 * ENDLESS);
			F16.move(5 * ENDLESS);
			F17.move(5 * ENDLESS);
			F18.move(5 * ENDLESS);
			F19.move(4 * ENDLESS);
			F20.move(4 * ENDLESS);

			draw(false, Cursor);

			if (!life)
				endGame(true, false, end, Cursor);
		}
	}

	// 시간 제한 모드
	else
	{
		initialize(true);
		draw(true, Cursor);

		while (!end)
		{
			gameTime++;

			if (_kbhit())
				Cursor.move(_getch());

			// F 출현 시기 (지정된 일수에 새 오브젝트 출현)
			F1.set(10);
			F2.set(20);
			F3.set(30);
			F4.set(40);
			F5.set(60);
			F6.set(85);

			// F 이동 속도 (높을수록 느려짐)
			F1.move(7);
			F2.move(7);
			F3.move(6);
			F4.move(6);
			F5.move(5);
			F6.move(5);

			Grade.appear(1); // 학점 출현 빈도 (지정된 일수마다 새 오브젝트 생성)
			draw(true, Cursor);

			if (!life)
				endGame(false, true, end, Cursor);
			else if (gameTime == setTime * GAME_SPEED)
				endGame(true, true, end, Cursor);
		}
	}
}

// 게임 종료 (승리/패배, 시간 제한/무제한, 종료 변수)
void endGame(bool win, bool time, bool &end, Cursor &Cursor)
{
	Sleep(CLOCKS_PER_SEC);
	system("cls");

	// 시간 무제한 모드가 끝났을 때
	if (!time)
	{
		if (maxEndless < gameTime / GAME_SPEED / ENDLESS)
			maxEndless = gameTime / GAME_SPEED / ENDLESS;
		gotoXY(SHOW_X, SHOW_Y);
		cout << " 　∧＿∧　 　　　／￣￣￣￣￣￣￣￣￣￣";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " <ㅇ ㅅ ㅇ>     ＜ 당신이 버틴 시간은   |";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "（　　　　）　   | " << gameTime / GAME_SPEED / ENDLESS << "일입니다!            >";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " ｜ ｜　 |	＼＿＿＿＿＿＿＿＿＿＿";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "〈＿フ__フ" << endl;
	}
	// 시간 제한 모드에서 죽었을 때
	else if (!win)
	{
		gotoXY(SHOW_X, SHOW_Y);
		cout << " 　∧＿∧　 　　　／￣￣￣￣￣￣￣￣￣￣";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " < ㅠ∀ㅠ > 　  ＜ 학사경고입니다  ㅠㅠ  >";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "（　　　　）　　  ＼＿＿＿＿＿＿＿＿＿＿";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " ｜ ｜　 |";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "〈＿フ__フ" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "당신이 버틴 날은 " << gameTime / GAME_SPEED << "일입니다." << endl;
	}

	// 시간 제한 모드에서 버텼지만 학점을 덜 먹었을 때
	else if (Cursor.getCreditNum() < SET_CREDIT)
	{
		gotoXY(SHOW_X, SHOW_Y);
		cout << " 　∧＿∧　 　　　／￣￣￣￣￣￣￣￣￣￣";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " < ㅠ∀ㅠ > 　  ＜ 학점을 열심히 먹어야죠  >";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "（　　　　）　　  ＼＿＿＿＿＿＿＿＿＿＿";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " ｜ ｜　 |";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "〈＿フ__フ" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "이번 학기 수강 학점은 " << Cursor.getCreditNum() << " 입니다." << endl;
	}
	// 시간 제한 모드에서 버텼을 때
	else if (Cursor.getCreditNum() >= SET_CREDIT)
	{
		if (maxGrade < Cursor.getGradeAvg())
			maxGrade = Cursor.getGradeAvg();
		gotoXY(SHOW_X, SHOW_Y);
		cout << " 　∧＿∧　 　　　／￣￣￣￣￣￣￣￣￣￣";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " <ㅇ ∀ ㅇ>     ＜ 축하합니다!	    |";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "（　　　　）　	| 학기를 무사히 마치셨네요! >";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " ｜ ｜　 |	＼＿＿＿＿＿＿＿＿＿＿";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "〈＿フ__フ" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "이번 학기 평점은 " << Cursor.getGradeAvg() << "입니다." << endl;
		gotoXY(SHOW_X, SHOW_Y + 6);
		cout << "이번 학기 수강 학점은 " << Cursor.getCreditNum() << " 입니다." << endl;
	}

	end = true;			// 전달받은 종료 변수를 상수로 돌려줌
	Sleep(CLOCKS_PER_SEC);
}

// 커서를 해당 좌표로 이동
void gotoXY(short x, short y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 깜빡거리는 커서를 화면에서 감춤
void hideCursor()
{
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.dwSize = 1;
	ConsoleCursor.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}