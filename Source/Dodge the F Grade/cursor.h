#pragma once

class Cursor
{
public:
	Cursor();
	void move(int);				// ����� Ŀ�� �����̰� �ϴ� �Լ�
	void calcGrade(double);		// ���� ������ ���� ������ ����Ͽ� score ������ �����ϴ� �Լ�
	int getCreditNum() const { return creditNum; }
	double getGradeAvg() const { return gradeAvg; }

private:
	int _xPos, _yPos, creditNum;
	double gradeAvg, gradeSum;
};