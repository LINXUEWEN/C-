#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>
#include <deque>
#include <numeric>
#include <fstream>
using namespace std;

enum Choice
{
	EXIT,
	START,
	SHOW,
	CLEAR
};

class Speaker
{
public:
	string m_name;
	double m_score[2];
};

class SpeechManager
{
public:
	SpeechManager();

	void showMenu();
	void exitSystem();
	void initSpeech();
	void creatSpeaker();

	void startSpeech();
	void speechDraw();//抽签
	void speechContest();

	void showScore();
	void saveRecord();

	void loadRecord();
	void showRecord();

	bool fileIsEmpty;
	map<int, vector<string>> m_record;

	void clearRecord();

	~SpeechManager();

	vector<int> speecher;				//比赛选手（12人）
	vector<int> speecher_first_round_win;//第一轮晋级选手（6人）
	vector<int> speecher_victory;		//胜利者（3人）

	map<int, Speaker> m_speaker;

	int m_index;//记录比赛轮数
};




