#include"speech.h"

SpeechManager::SpeechManager()
{
	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();
}

void SpeechManager::showMenu()
{
	cout << "**************************" << endl;
	cout << "**** 欢迎参加演讲比赛 ****" << endl;
	cout << "****  1.开始演讲比赛  ****" << endl;
	cout << "****  2.查看往届记录  ****" << endl;
	cout << "****  3.清空比赛记录  ****" << endl;
	cout << "****  0.退出比赛程序  ****" << endl;
	cout << "**************************" << endl;
	cout << endl;
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	this->speecher.clear();
	this->speecher_first_round_win.clear();
	this->speecher_victory.clear();
	this->m_speaker.clear();

	this->m_index = 1;
	this->m_record.clear();
}

void SpeechManager::creatSpeaker()
{
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];

		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}

		this->speecher.push_back(i + 10001);//选手编号
		this->m_speaker.insert(make_pair(i + 10001, sp));
	}
}

void SpeechManager::speechDraw()
{

	cout << "第" << this->m_index << "轮比赛选手抽签" << endl;
	cout << "---------------------------------------------------" << endl;
	cout << "抽签结果如下：" << endl;
	if (this->m_index == 1)
	{
		random_shuffle(this->speecher.begin(), this->speecher.end());
		for (vector<int>::iterator it = this->speecher.begin(); it != this->speecher.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		random_shuffle(this->speecher_first_round_win.begin(),this->speecher_first_round_win.end());
		for (vector<int>::iterator it = this->speecher_first_round_win.begin(); it != this->speecher_first_round_win.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------" << endl;
	system("pause");
	cout << endl;
}

void SpeechManager::speechContest()
{
	cout << "--------------第" << this->m_index << "轮比赛正式开始------------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	int num = 0;
	vector<int> v_src;
	if (this->m_index == 1)
	{
		v_src = this->speecher;
	}
	else
	{
		v_src = this->speecher_first_round_win;
	}
	for (vector<int>::iterator it = v_src.begin(); it != v_src.end(); it++)
	{
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;	//600~1000
			d.push_back(score);
		}

		sort(d.begin(), d. end(), greater<double>());
		d.pop_front();
		d.pop_back();

		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();

		this->m_speaker[*it].m_score[this->m_index - 1] = avg;

		groupScore.insert(make_pair(avg, *it));
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号： " << it->second << "\t姓名： " << this->m_speaker[it->second].m_name << "\t成绩: " << this->m_speaker[it->second].m_score[this->m_index - 1] << endl;
			}

			int count = 0;

			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					this->speecher_first_round_win.push_back((*it).second);
				}
				else
				{
					this->speecher_victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "--------------第" << this->m_index << "轮比赛正式结束------------------" << endl;
	system("pause");
}

void SpeechManager::startSpeech()
{
	srand((unsigned int)time(NULL));
	this->speechDraw();
	this->speechContest();
	this->showScore();
	
	this->m_index++;
	this->speechDraw();
	this->speechContest();
	this->showScore();

	this->saveRecord();

	this->initSpeech();
	this->creatSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::showScore()
{
	cout << "-----------第" << this->m_index << "轮晋级选手信息如下：-----------" << endl;
	vector<int> v;
	if (this->m_index == 1)
	{
		v = this->speecher_first_round_win;
	}
	else
	{
		v = this->speecher_victory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "编号： " << *it << "\t姓名： " << m_speaker[*it].m_name << "\t得分： " << m_speaker[*it].m_score[this -> m_index - 1] << endl;
	}
	cout << endl;

	system("pause");
	system("cls");
	this->showMenu();
}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);

	for (vector<int>::iterator it = this->speecher_victory.begin(); it != this->speecher_victory.end(); it++)
	{
		ofs << *it << "," << m_speaker[*it].m_score[1] << ",";
	}
	ofs << endl;

	ofs.close();

	cout << "记录已经保存！" << endl;

	this->fileIsEmpty = false;
}

void SpeechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件存在！" << endl;
		ifs.close();
		return;
	}
	
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;

	ifs.putback(ch);

	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string> v;
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string tmp = data.substr(start, pos - start);

			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();

	/*for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
	{
		cout << it->first << "冠军编号： " << it->second[0] << "\t分数： " << it->second[1] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在，或记录为空" << endl;
	}
	for (int i = 0; i < this->m_record.size(); i++)
	{
		cout << "第" << i + 1 << "届" << "冠军编号： " << this->m_record[i][0] << "\t得分：" << this->m_record[i][1] << "\t"
			"亚军编号： " << this->m_record[i][2] << "\t得分：" << this->m_record[i][3] << "\t"
			"季军编号： " << this->m_record[i][4] << "\t得分：" << this->m_record[i][5] << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "0.返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc);//如果文件存在删除文件并重新创建
		ofs.close();

		this->initSpeech();
		this->creatSpeaker();
		this->loadRecord();
		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}


SpeechManager::~SpeechManager()
{

}
