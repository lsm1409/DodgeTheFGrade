#pragma once

class F_Shot
{
public:
	F_Shot();
	void set(int);		// F�� �߻� ������ ���·� ������ִ� �Լ�
	void move(int);		// F�� �߻��ϴ� �Լ�
	void moveStart();	// F ����� ������ Ȱ��ȭ
	void moveEnd();		// �������� ����� ������ ��Ȱ��ȭ

private:
	int _xPos, _yPos;
	int startType;			// F ���� ��� ��ġ
	bool running;			// ������ Ȱ��ȭ or ��Ȱ��ȭ
};
