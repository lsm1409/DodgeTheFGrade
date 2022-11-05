/*
�ֱٿ� ����� ����: arrayCopy�� ���� ���� �ӵ� ���� (0.9d)
����� �� �ְ� ��� ��� (0.9e)
��! �� ���� �ʴ� ���� ����, �ð� ���� ��忡�� ���߿� ������ ������ ������� �ʴ� ������ ����, ������(Accessor) �߰� �� �ζ��� �Լ�ȭ (0.9f)
���� �̻��� ������ �������� ������ ������ ���ߵ� �й� ó�� ����, Ŀ�� �ڸ��� ���� ��ġ�� �ʵ��� ����, �Ű� ������ �ִ� �ӵ� ���� ������� ���� �Լ��� �ۼ� (0.9g)
���̵� ����, UI ���� ����, ���� �Լ� ����(0.9h)
���� �� Ȯ�� ����:	��� ������Ʈ [�Ӽ�] - [�ɼ�] �ǿ��� ���Ž� �ܼ� ����� üũ�Ǿ� �־�� �� (���� ȯ���� Windows 7 �����̸� ��� ����)
- [�۲�] �ǿ��� ������ �۲��� ���� ���ƾ� ��
*/
#include "header.h"
#include "F.h"
#include "grade.h"

int arrayGame[MAP_HEIGHT + 1][MAP_WIDTH + 1];	// ���� �� ũ��
int arrayCopy[MAP_HEIGHT + 1][MAP_WIDTH + 1];	// ���� �� ����
int gameTime;			// ���� ���� �� �ð�
int life;				// �÷��̾� ���
static int maxEndless;	// �ְ� ��� (��ƾ �ð�)
static double maxGrade;	// �ְ� ��� (����)

int main()
{
	bool restart;	// ���� ����� ���� ����
	int buffer = 0;	// ����� �Է��� �����ϴ� ����

	// Magic Formula�� ���� ��� ����� �Ҽ� ��° �ڸ������� ������
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	srand((size_t)time(NULL));	// ���� �õ� ����
	hideCursor();				// Ŀ�� �����
	title();					// Ÿ��Ʋ ȭ�� ���

	// ���� ȭ�� ���
	do
	{
		gotoXY(SHOW_X, SHOW_Y + 0);cout << "��	   ���� ���� �� ��� ������Ʈ [�Ӽ�]��	       ��";
		gotoXY(SHOW_X, SHOW_Y + 1);cout << "��     [�ɼ�] �ǿ��� ���Ž� �ܼ� ����� üũ���ֽð�     ��";
		gotoXY(SHOW_X, SHOW_Y + 2);cout << "�� [�۲�] �ǿ��� ������ �۲� �̿��� ���� ������ �ֽʽÿ� ��";
		Sleep(CLOCKS_PER_SEC);
		gotoXY(SHOW_X, SHOW_Y + 4);cout << "�賭�� �� �бⰡ ���۵Ǿ����ϴ�.";
		gotoXY(SHOW_X, SHOW_Y + 5);cout << "F�� ���� �л��� ���ϰ� ���� ������ ����ϼ���.";
		Sleep(CLOCKS_PER_SEC / 2);
		gotoXY(SHOW_X, SHOW_Y + 7);cout << "���� ��带 �����ϼ���";
		gotoXY(SHOW_X, SHOW_Y + 9);cout << "1. ���� ���";
		gotoXY(SHOW_X, SHOW_Y + 10);cout << "�̹� �б� ���� �󸶳� ���� ������ ���";
		gotoXY(SHOW_X, SHOW_Y + 11);cout << "�󸶳� ���� ������ ���� �� �������?";
		gotoXY(SHOW_X, SHOW_Y + 13);cout << "2. ������ ���";
		gotoXY(SHOW_X, SHOW_Y + 14);cout << "����� (���� �Ϻ� ��) �Ƿ��� �����ϼ���.";
		gotoXY(SHOW_X, SHOW_Y + 15);cout << "�󸶳� ���� ��ƿ �� �������?";
		gotoXY(SHOW_X, SHOW_Y + 17);cout << "������ �ߴ��ϰ� ������ 1, 2���� ������ �ƹ� Ű�� ��������." << endl;

		//���ۿ� ��ϵ� Ű���� ����
		while (_kbhit())
			_getch();

		// ���� ��� ����
		buffer = _getch();
		if (buffer == 49)
			loadGame(SET_TIME, MAX_LIFE);
		else if (buffer == 50)
			loadGame(0, 1);
		else
			goto GAME_OVER;

		cout << endl
			<< "	������ ����Ǿ����ϴ�." << endl
			<< "	�ٽ� �Ϸ��� 1��, �׸� �Ϸ��� 2���� ��������." << endl;

		do
		{
			buffer = _getch();
			if (buffer == 49)
				restart = true;		// 1���� ������ �����
			else if (buffer == 50)
				restart = false;	// 2���� ������ ����
		} while (buffer != 49 && buffer != 50);	// 1���� 2�� �� �� �ϳ��� ������ ������ ���� ����

		system("cls");
	} while (restart);

GAME_OVER:
	return 0;
}
void title() // ���� ȭ��
{
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "������������������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "������С������ǡ��ϡ������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "������ǡ����͡�š�����";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "����౤�������С౳�����";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "�����ޡ�����Ρ�ס෡��֡��";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "�����̡భ���ơ౳�����ԡ���";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 6);cout << "�ѤѤѣԣţңͤѣУңϣʣţãԤѤ�";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "�����2014726037���̻�Ρ����";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "�����2014707040�������������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "�����2013610017��ȼ�ȣ�����";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "������������������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "���Уңţӣӡ���Σ١�ˣţ١��";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "������������������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "������������������";Sleep(300);
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "������������������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 0);cout << "������������������";
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "������С������ǡ��ϡ������";Sleep(100);
	gotoXY(SHOW_X, SHOW_Y + 1);cout << "������С������ǡ��ϡ������";
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "������ǡ����͡�š�����";Sleep(90);
	gotoXY(SHOW_X, SHOW_Y + 2);cout << "������ǡ����͡�š�����";
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "����ᱤ�������Сᱳ�����";Sleep(90);
	gotoXY(SHOW_X, SHOW_Y + 3);cout << "����౤�������С౳�����";
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "�����ޡ�����Ρ�סᷡ��֡��";Sleep(80);
	gotoXY(SHOW_X, SHOW_Y + 4);cout << "�����ޡ�����Ρ�ס෡��֡��";
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "�����̡ᰭ���ơᱳ�����ԡ���";Sleep(80);
	gotoXY(SHOW_X, SHOW_Y + 5);cout << "�����̡భ���ơ౳�����ԡ���";Sleep(70);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "�����2014726037���̻�Ρ����";Sleep(70);
	gotoXY(SHOW_X, SHOW_Y + 7);cout << "�����2014726037���̻�Ρ����";
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "�����2014707040�������������";Sleep(60);
	gotoXY(SHOW_X, SHOW_Y + 8);cout << "�����2014707040�������������";
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "�����2013610017��ȼ�ȣ�����";Sleep(60);
	gotoXY(SHOW_X, SHOW_Y + 9);cout << "�����2013610017��ȼ�ȣ�����";
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "������������������";Sleep(50);
	gotoXY(SHOW_X, SHOW_Y + 10);cout << "������������������";
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "���Уңţӣӡ���Σ١�ˣţ١��";Sleep(50);
	gotoXY(SHOW_X, SHOW_Y + 11);cout << "���Уңţӣӡ���Σ١�ˣţ١��";
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "������������������";Sleep(40);
	gotoXY(SHOW_X, SHOW_Y + 12);cout << "������������������";
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "������������������";Sleep(40);
	gotoXY(SHOW_X, SHOW_Y + 13);cout << "������������������";Sleep(300);

	while (true)
	{
		if (_kbhit())
			break;
		gotoXY(SHOW_X, SHOW_Y + 10); cout << "������������������";
		gotoXY(SHOW_X, SHOW_Y + 11); cout << "���Уңţӣӡ���Σ١�ˣţ١��";
		gotoXY(SHOW_X, SHOW_Y + 12); cout << "������������������"; Sleep(400);
		gotoXY(SHOW_X, SHOW_Y + 10); cout << "������������������";
		gotoXY(SHOW_X, SHOW_Y + 11); cout << "���Уңţӣӡ���Σ١�ˣţ١��";
		gotoXY(SHOW_X, SHOW_Y + 12); cout << "������������������"; Sleep(400);
	}
	system("cls");
}
// ȭ�鿡 ���ǵ� ������ �׸�
void draw(bool timer, Cursor &Cursor)
{
	// ���� �迭�� ���ؼ� �޶��� �κи� ����� ���� ����ó�� ���
	for (short _yPos = 0; _yPos < MAP_HEIGHT + 1; _yPos++)
		for (short _xPos = 0; _xPos < MAP_WIDTH + 1; _xPos++)
			if (arrayCopy[_yPos][_xPos] != arrayGame[_yPos][_xPos])
			{
				gotoXY(_xPos, _yPos);
				switch (arrayGame[_yPos][_xPos])
				{
				case BLANK:
					cout << "��";
					break;
				case CURSOR:
					cout << "��";
					break;
				case F_ZERO:
					cout << "��";
					break;
				case BORDER_ROW:
					cout << "��";
					break;
				case BORDER_COLUMN:
					cout << "��";
					break;
				case CORNER_UPPER_LEFT:
					cout << "��";
					break;
				case CORNER_UPPER_RIGHT:
					cout << "��";
					break;
				case CORNER_LOWER_RIGHT:
					cout << "��";
					break;
				case CORNER_LOWER_LEFT:
					cout << "��";
					break;
				case A_PLUS:
					cout << "A+";
					break;
				case A_ZERO:
					cout << "��";
					break;
				case B_PLUS:
					cout << "B+";
					break;
				case B_ZERO:
					cout << "��";
					break;
				case C_PLUS:
					cout << "C+";
					break;
				case C_ZERO:
					cout << "��";
					break;
				case D_ZERO:
					cout << "��";
					break;
				}
			}

	// ���� �迭�� ī�� �迭�� �״�� ����
	for (short _yPos = 0; _yPos < MAP_HEIGHT + 1; _yPos++)
		for (short _xPos = 0; _xPos < MAP_WIDTH + 1; _xPos++)
			arrayCopy[_yPos][_xPos] = arrayGame[_yPos][_xPos];

	// ������ ȭ�鿡 ����ϴ� �κ� (�ð� ����/������ ��忡 ���� ����)
	if (timer)
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 3);
		cout << "������ �� " << gameTime / GAME_SPEED << "��°";

		gotoXY(MAP_WIDTH + 7, MIDDLE_HEIGHT - 2);
		cout << Cursor.getCreditNum();

		gotoXY(MAP_WIDTH + 5, MIDDLE_HEIGHT - 1);
		cout << Cursor.getGradeAvg();

		gotoXY(MAP_WIDTH + 12, MIDDLE_HEIGHT);
		for (int i = 0; i < life; i++)
			cout << "��";
		for (int i = 0; i < (MAX_LIFE - life); i++)
			cout << "��";
		if (!life)
		{
			gotoXY(MAP_WIDTH + 9, MIDDLE_HEIGHT);
			cout << " (��! �������ȳ׿�...)";
		}
	}
	else
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 3);
		cout << "������ �� " << gameTime / GAME_SPEED / ENDLESS << "��°";
	}
}

// ���� ���� �迭 ��Ҹ� ����
void initialize(bool timer)
{
	// ���� ���� �������� ä��
	for (size_t i = 0; i < MAP_HEIGHT + 1; i++)
		for (size_t j = 0; j < MAP_WIDTH + 1; j++)
			arrayGame[i][j] = BLANK;

	for (size_t i = 0; i < MAP_HEIGHT + 1; i++)
		for (size_t j = 0; j < MAP_WIDTH + 1; j++)
			arrayCopy[i][j] = BLANK;

	// �� �׵θ� ����
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
	cout << "  ��   : �գ�";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 6);
	cout << "��  �� : �̣ţƣ� / �ңɣǣȣ�";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 7);
	cout << "  ��   : �ģϣף�";
	gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 8);
	cout << "�ãԣң� + �� : �ţΣ�";

	// Ÿ�̸Ӱ� �ִ� �����̸� ���
	if (timer)
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 5);
		cout << "������ 14���� �̻� ����ϼ���";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 2);
		cout << "�ְ��� ����: " << maxGrade;
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 2);
		cout << "�������: ";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT - 1);
		cout << "����: ";
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT);
		cout << "�л������ ���� F: ";
	}

	// Ÿ�̸Ӱ� ���� �����̸� ���
	else
	{
		gotoXY(MAP_WIDTH + 2, MIDDLE_HEIGHT + 2);
		cout << "�ְ� ��� �ϼ�: " << maxEndless << "��";
	}

	// ��� ���� �ʱ�ȭ
	gameTime = 0;
}

// ���� ���� (���� �ð� (�������̸� 0), ���� ���)
void loadGame(int setTime, int setLife)
{
	Cursor Cursor;
	F_Shot F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20;
	Grade Grade;
	bool end = false;	// ���� ���� ���� (���� ���� Ż���)

	life = setLife;		// ������ ����

	system("cls");
	gotoXY(MIDDLE_WIDTH - 3, MIDDLE_HEIGHT);
	cout << "�����մϴ�." << endl;
	Sleep(CLOCKS_PER_SEC);
	system("cls");

	// �ð� ������ ���
	if (!setTime)
	{
		initialize(false);
		draw(false, Cursor);

		while (!end)
		{
			gameTime++;

			if (_kbhit())
				Cursor.move(_getch());

			// F ���� �ñ� (������ �ϼ��� �� ������Ʈ ����)
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

			// F �̵� �ӵ� (�������� ������)
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

	// �ð� ���� ���
	else
	{
		initialize(true);
		draw(true, Cursor);

		while (!end)
		{
			gameTime++;

			if (_kbhit())
				Cursor.move(_getch());

			// F ���� �ñ� (������ �ϼ��� �� ������Ʈ ����)
			F1.set(10);
			F2.set(20);
			F3.set(30);
			F4.set(40);
			F5.set(60);
			F6.set(85);

			// F �̵� �ӵ� (�������� ������)
			F1.move(7);
			F2.move(7);
			F3.move(6);
			F4.move(6);
			F5.move(5);
			F6.move(5);

			Grade.appear(1); // ���� ���� �� (������ �ϼ����� �� ������Ʈ ����)
			draw(true, Cursor);

			if (!life)
				endGame(false, true, end, Cursor);
			else if (gameTime == setTime * GAME_SPEED)
				endGame(true, true, end, Cursor);
		}
	}
}

// ���� ���� (�¸�/�й�, �ð� ����/������, ���� ����)
void endGame(bool win, bool time, bool &end, Cursor &Cursor)
{
	Sleep(CLOCKS_PER_SEC);
	system("cls");

	// �ð� ������ ��尡 ������ ��
	if (!time)
	{
		if (maxEndless < gameTime / GAME_SPEED / ENDLESS)
			maxEndless = gameTime / GAME_SPEED / ENDLESS;
		gotoXY(SHOW_X, SHOW_Y);
		cout << " �����ߡ��� ����������������������������";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " <�� �� ��>     �� ����� ��ƾ �ð���   |";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "��������������   | " << gameTime / GAME_SPEED / ENDLESS << "���Դϴ�!            >";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " �� ���� |	���ߣߣߣߣߣߣߣߣߣ�";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "���߫�__��" << endl;
	}
	// �ð� ���� ��忡�� �׾��� ��
	else if (!win)
	{
		gotoXY(SHOW_X, SHOW_Y);
		cout << " �����ߡ��� ����������������������������";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " < �Т��� > ��  �� �л����Դϴ�  �Ф�  >";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "����������������  ���ߣߣߣߣߣߣߣߣߣ�";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " �� ���� |";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "���߫�__��" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "����� ��ƾ ���� " << gameTime / GAME_SPEED << "���Դϴ�." << endl;
	}

	// �ð� ���� ��忡�� �������� ������ �� �Ծ��� ��
	else if (Cursor.getCreditNum() < SET_CREDIT)
	{
		gotoXY(SHOW_X, SHOW_Y);
		cout << " �����ߡ��� ����������������������������";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " < �Т��� > ��  �� ������ ������ �Ծ����  >";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "����������������  ���ߣߣߣߣߣߣߣߣߣ�";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " �� ���� |";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "���߫�__��" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "�̹� �б� ���� ������ " << Cursor.getCreditNum() << " �Դϴ�." << endl;
	}
	// �ð� ���� ��忡�� ������ ��
	else if (Cursor.getCreditNum() >= SET_CREDIT)
	{
		if (maxGrade < Cursor.getGradeAvg())
			maxGrade = Cursor.getGradeAvg();
		gotoXY(SHOW_X, SHOW_Y);
		cout << " �����ߡ��� ����������������������������";
		gotoXY(SHOW_X, SHOW_Y + 1);
		cout << " <�� �� ��>     �� �����մϴ�!	    |";
		gotoXY(SHOW_X, SHOW_Y + 2);
		cout << "��������������	| �б⸦ ������ ��ġ�̳׿�! >";
		gotoXY(SHOW_X, SHOW_Y + 3);
		cout << " �� ���� |	���ߣߣߣߣߣߣߣߣߣ�";
		gotoXY(SHOW_X, SHOW_Y + 4);
		cout << "���߫�__��" << endl;
		gotoXY(SHOW_X, SHOW_Y + 5);
		cout << "�̹� �б� ������ " << Cursor.getGradeAvg() << "�Դϴ�." << endl;
		gotoXY(SHOW_X, SHOW_Y + 6);
		cout << "�̹� �б� ���� ������ " << Cursor.getCreditNum() << " �Դϴ�." << endl;
	}

	end = true;			// ���޹��� ���� ������ ����� ������
	Sleep(CLOCKS_PER_SEC);
}

// Ŀ���� �ش� ��ǥ�� �̵�
void gotoXY(short x, short y)
{
	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// �����Ÿ��� Ŀ���� ȭ�鿡�� ����
void hideCursor()
{
	CONSOLE_CURSOR_INFO ConsoleCursor;

	ConsoleCursor.dwSize = 1;
	ConsoleCursor.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}