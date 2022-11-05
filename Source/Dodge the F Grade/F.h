#pragma once

class F_Shot
{
public:
	F_Shot();
	void set(int);		// F를 발사 가능한 상태로 만들어주는 함수
	void move(int);		// F을 발사하는 함수
	void moveStart();	// F 만들고 움직임 활성화
	void moveEnd();		// 공백으로 만들고 움직임 비활성화

private:
	int _xPos, _yPos;
	int startType;			// F 학점 출발 위치
	bool running;			// 움직임 활성화 or 비활성화
};
