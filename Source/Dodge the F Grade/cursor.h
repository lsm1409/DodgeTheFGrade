#pragma once

class Cursor
{
public:
	Cursor();
	void move(int);				// 사용자 커서 움직이게 하는 함수
	void calcGrade(double);		// 먹은 학점에 따라 점수를 계산하여 score 변수에 대입하는 함수
	int getCreditNum() const { return creditNum; }
	double getGradeAvg() const { return gradeAvg; }

private:
	int _xPos, _yPos, creditNum;
	double gradeAvg, gradeSum;
};