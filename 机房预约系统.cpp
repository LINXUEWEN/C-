#include "System.h"

Student::Student()
{

}

Student::Student(int id, string name, string pwd)
{
	this->m_id = id;
	this->m_name = name;
	this->m_pwd = pwd;

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_comid&&ifs >> c.m_maxnum)
	{
		this->v_computer.push_back(c);
	}
	ifs.close();
}

void Student::operMenu()
{
	cout << "欢迎学生" << this->m_name << "登录！" << endl;
	cout << "\t\t------------------------\n";
	cout << "\t\t|                      |\n";
	cout << "\t\t|    1. 申请预约       |\n";
	cout << "\t\t|    2. 查看我的预约   |\n";
	cout << "\t\t|    3. 查看所有预约   |\n";
	cout << "\t\t|    4. 取消预约       |\n";
	cout << "\t\t|    0. 注销登录       |\n";
	cout << "\t\t|                      |\n";
	cout << "\t\t------------------------\n";
	cout << "请输入你的选择：> " << endl;
}

void Student::applyOrder()
{
	int date = 0;
	int interval = 0;
	int room = 0;
	while (true)
	{
		cout << "机房开放时间：周一至周五！" << endl;
		cout << "请输入申请预约的时间: " << endl;
		cout << "1.周一" << endl;
		cout << "2.周二" << endl;
		cout << "3.周三" << endl;
		cout << "4.周四" << endl;
		cout << "5.周五" << endl;

		cin >> date;
		if (date >= 1 && date <= 5)
		{
			break;
		}
		cout << "请输入正确时间！！！" << endl;
		system("pause");
		system("cls");
	}

	while (true)
	{
		cout << "请输入申请预约的时间段： " << endl;
		cout << "1.上午" << endl;
		cout << "2.下午" << endl;

		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "请输入正确的时间！！！" << endl;
		system("pause");
		system("cls");
	}


	while (true)
	{
		cout << "请选择机房： " << endl;
		cout << "1号机房容量：" << this->v_computer[0].m_maxnum << endl;
		cout << "2号机房容量：" << this->v_computer[1].m_maxnum << endl;
		cout << "3号机房容量：" << this->v_computer[2].m_maxnum << endl;

		cin >> room;
		if (room >=1 && room <= 3)
		{
			break;
		}
		cout << "请输入合法数字!!!!" << endl;
		system("pause");
		system("cls");
	}
	cout << "预约成功！审核中......" << endl;

	ofstream ofs(ORDER_FILE, ios::app);
	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuID:" << this->m_id << " ";
	ofs << "stuName" << this->m_name << " ";
	ofs << "roomID" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderdata[i]["stuID"].c_str()) == this->m_id)
		{
			cout << "预约日期： 周" << of.m_orderdata[i]["date"];
			cout << " 时段：" << (of.m_orderdata[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderdata[i]["roomID"];
			string status = "状态：";
			if (of.m_orderdata[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderdata[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderdata[i]["status"]=="-1")
			{
				status += "审核未通过，预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期： 周" << of.m_orderdata[i]["date"];
		cout << " 时段：" << (of.m_orderdata[i]["interval"] == "1" ? "上午" : "下午");
		cout << "学号：" << of.m_orderdata[i]["stuID"];
		cout << "姓名：" << of.m_orderdata[i]["stuName"];
		cout << " 机房：" << of.m_orderdata[i]["roomID"];
		string status = "状态：";
		if (of.m_orderdata[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderdata[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderdata[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
	vector<int>v;
	int index = 1;
	for (int i = 0; i < of.m_size; i++)
	{
		if (atoi(of.m_orderdata[i]["stuID"].c_str()) == this->m_id)
		{
			if (of.m_orderdata[i]["status"] == "1" || of.m_orderdata[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、 ";
				cout << "预约日期： 周" << of.m_orderdata[i]["date"];
				cout << " 时段：" << (of.m_orderdata[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderdata[i]["roomID"];
				string status = "状态：";
				if (of.m_orderdata[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderdata[i]["status"] == "2")
				{
					status += "预约成功";
				}
				else if (of.m_orderdata[i]["status"] == "-1")
				{
					status += "审核未通过，预约失败";
				}
				else
				{
					status += "预约已取消";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0表示返回" << endl;
	int select = 0;
	while (1)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				of.m_orderdata[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "请输入合法数字" << endl;
	}
	system("pause");
	system("cls");
}


Teacher::Teacher()
{

}

Teacher::Teacher(int empID, string name, string pwd)
{
	this->m_empID = empID;
	this->m_name = name;
	this->m_pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "欢迎教师" << this->m_name << "登录！" << endl;
	cout << "\t\t---------------------------\n";
	cout << "\t\t|                         |\n";
	cout << "\t\t|     1. 查看所有预约     |\n";
	cout << "\t\t|     2. 审核预约         |\n";
	cout << "\t\t|     0. 注销登录         |\n";
	cout << "\t\t|                         |\n";
	cout << "\t\t---------------------------\n";
	cout << "请选择您的选择： " << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_size; i++)
	{
		cout << i + 1 << "、 ";
		cout << "预约日期： 周" << of.m_orderdata[i]["date"];
		cout << " 时段：" << (of.m_orderdata[i]["interval"] == "1" ? "上午" : "下午");
		cout << "学号：" << of.m_orderdata[i]["stuID"];
		cout << "姓名：" << of.m_orderdata[i]["stuName"];
		cout << " 机房：" << of.m_orderdata[i]["roomID"];
		string status = "状态：";
		if (of.m_orderdata[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderdata[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderdata[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;
	if (of.m_size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "待审核的预约记录如下： " << endl;
	vector<int>v;
	int index = 0;
	for (int i = 0; i < of.m_size; i++)
	{
		if (of.m_orderdata[i]["status"] == "1")
		{
			v.push_back(i);
			cout << ++index << "、 ";
			cout << "预约日期： 周" << of.m_orderdata[i]["date"];
			cout << " 时段：" << (of.m_orderdata[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房：" << of.m_orderdata[i]["roomID"];
			string status = "状态：";
			if (of.m_orderdata[i]["status"] == "1")
			{
				status += "审核中";
			}
			cout << status << endl;
		}
	}
	cout << "请输入审核的预约记录，0表示返回" << endl;
	int select = 0;
	int ret = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果" << endl;
				cout << "1.通过" << endl;
				cout << "2.不通过" << endl;
				cin >> ret;
				if (ret == 1)
				{
					of.m_orderdata[v[select - 1]]["status"] == "2";
				}
				else
				{
					of.m_orderdata[v[select - 1]]["status"] == "-1";
				}
				of.updateOrder();
				cout << "审核完毕！" << endl;
				break;
			}
		}
		cout << "请输入合法数字" << endl;
	}
	system("pause");
	system("cls");
}

Manager::Manager()
{

}

Manager::Manager(string name, string pwd)
{
	this->m_name = name;
	this->m_pwd = pwd;

	this->initVector();

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom c;
	while (ifs >> c.m_comid&&ifs >> c.m_maxnum)
	{
		this->v_computer.push_back(c);
	}
	cout << "当前机房数量为：" << this->v_computer.size() << endl;
	ifs.close();
}

void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_name << "登录！" << endl;
	cout << "\t\t------------------\n";
	cout << "\t\t|                |\n";
	cout << "\t\t|   1. 添加账号  |\n";
	cout << "\t\t|   2. 查看账号  |\n";
	cout << "\t\t|   3. 查看机房  |\n";
	cout << "\t\t|   4. 清空预约  |\n";
	cout << "\t\t|   0. 注销登录  |\n";
	cout << "\t\t|                |\n";
	cout << "\t\t------------------\n";
	cout << "请输入您的选择： " << endl;
}

void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1.添加学生" << endl;
	cout << "2.添加老师" << endl;

	string file_name;
	string tip;
	ofstream ofs;
	string errorTip;
	int select = 0;
	cin >> select;
	//if (select == 1)
	//{
	//	file_name = STUDENT_FILE;
	//	tip = "请输入学号： >";
	//}
	//else
	//{
	//	file_name = TEACHER_FILE;
	//	tip = "请输入工号： >";
	//}
	switch (select)
	{
	case 1:
		file_name = STUDENT_FILE;
		tip = "请输入学号： >";
		errorTip = "学号重复，请重新输入";
		break;
	case 2:
		file_name = TEACHER_FILE;
		tip = "请输入工号： >";
		errorTip = "工号重复，请重新输入";
		break;
	default:
		cout << "请输入合法字符！" << endl;
		system("pause");
		system("cls");
		break;
	}

	ofs.open(file_name, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (1)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, 1);

		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名： >" << endl;
	cin >> name;
	cout << "请设置密码： >" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功！" << endl;

	system("pause");
	system("cls");
	ofs.close();

	this->initVector();
}

void printStudent(Student & s)
{
	cout << "学号： " << s.m_id << "\t\t姓名： " << s.m_name << "\t\t密码： " << s.m_pwd << endl;
}
void printTeacher(Teacher & t)
{
	cout << "工号： " << t.m_empID << "\t\t姓名： " << t.m_name << "\t\t密码： " << t.m_pwd << endl;

}

void Manager::showPerson()
{
	cout << "请输入查看内容： " << endl;
	cout << "1.查看所有学生" << endl;
	cout << "2.查看所有老师" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		cout << "所有学生信息如下： " << endl;
		for_each(this->v_student.begin(), this->v_student.end(), printStudent);
	}
	else
	{
		cout << "所有老师信息如下： " << endl;
		for_each(this->v_teacher.begin(), this->v_teacher.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "机房信息如下： " << endl;
	for (vector<ComputerRoom>::iterator it = this->v_computer.begin(); it != this->v_computer.end(); it++)
	{
		cout << "机房编号： " << it->m_comid << "\t\t机房最大容量： " << it->m_maxnum << endl;
	}
	system("pause");
	system("cls");
}

void Manager::clearFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

void Manager::initVector()
{
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	this->v_student.clear();
	this->v_teacher.clear();

	Student s;
	while (ifs >> s.m_id&&ifs >> s.m_name&&ifs >> s.m_pwd)
	{
		this->v_student.push_back(s);
	}
	cout << "当前录入学生数量： >" << this->v_student.size() << endl;
	ifs.close();

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	while (ifs >> t.m_empID&&ifs >> t.m_name&&ifs >> t.m_pwd)
	{
		this->v_teacher.push_back(t);
	}
	cout << "当前录入教师数量： >" << this->v_teacher.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = this->v_student.begin(); it != this->v_student.end(); it++)
		{
			if (id == it->m_id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = this->v_teacher.begin(); it != this->v_teacher.end(); it++)
		{
			if (id == it->m_empID)
			{
				return true;
			}
		}
	}
	return false;
}

void LoginIn(string file_name, int type)
{
	Identity * person = NULL;
	ifstream ifs;
	ifs.open(file_name, ios::in);

	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;
	
	if (type == STUDENT)
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == TEACHER)
	{
		cout << "请输入你的工号" << endl;
		cin >> id;
	}

	cout << "请输入用户名： " << endl;
	cin >> name;
	cout << "请输入密码： " << endl;
	cin >> pwd;

	if (type == STUDENT)
	{
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (id == fid&&name == fname&&pwd == fpwd)
			{
				cout << "学生验证成功!" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				studentMenu(person);
				return;
			}
		}
	}
	else if (type == TEACHER)
	{
		int fid;
		string fname;
		string fpwd;
		while (ifs >> fid && ifs >> fname && ifs >> fpwd)
		{
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (id == fid&&name == fname&&pwd == fpwd)
			{
				cout << "教师验证成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == MANAGER)
	{
		string fname;
		string fpwd;
		while (ifs >> fname&&ifs >> fpwd)
		{
			if (name == fname&&pwd == fpwd)
			{
				cout << "验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败！" << endl;
	system("pause");
	system("cls");
	return;
}

void managerMenu(Identity* &manager)
{
	while (1)
	{
		manager->operMenu();

		Manager* man = (Manager*)manager;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "添加账号" << endl;
			man->addPerson();
			break;
		case 2:
			cout << "查看账号" << endl;
			man->showPerson();
			break;
		case 3:
			cout << "查看机房" << endl;
			man->showComputer();
			break;
		case 4:
			cout << "清空预约" << endl;
			man->clearFile();
			break;
		case 0:
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "请输入合法数字！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void studentMenu(Identity* &student)
{
	while (1)
	{
		student->operMenu();
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		switch (select)
		{
		case 1:
			cout << "申请预约" << endl;
			stu->applyOrder();
			break;
		case 2:
			cout << "查看我的预约" << endl;
			stu->showMyOrder();
			break;
		case 3:
			cout << "查看所有预约" << endl;
			stu->showAllOrder();
			break;
		case 4:
			cout << "取消预约" << endl;
			stu->cancelOrder();
			break;
		case 0:
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
			break;
		default:
			cout << "请输入合法数字！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void teacherMenu(Identity* &teacher)
{
	while (1)
	{
		teacher->operMenu();
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			tea->showAllOrder();
		}
		else if (select==2)
		{
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;
	string interval;
	string stuID;
	string stuName;
	string roomID;
	string status;

	this->m_size = 0;

	while (ifs >> date&&ifs >> interval&&ifs >> stuID&&ifs >> stuName&&ifs >> roomID&&ifs >> status)
	{
		string key;
		string value;
		map<string, string> m;

		int pos = date.find(":");
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos);
			m.insert(make_pair(key, value));
		}

		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos);
			m.insert(make_pair(key, value));
		}

		pos = stuID.find(":");
		if (pos != -1)
		{
			key = stuID.substr(0, pos);
			value = stuID.substr(pos + 1, stuID.size() - pos);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos);
			m.insert(make_pair(key, value));
		}

		pos = roomID.find(":");
		if (pos != -1)
		{
			key = roomID.substr(0, pos);
			value = roomID.substr(pos + 1, roomID.size() - pos);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos);
			m.insert(make_pair(key, value));
		}

		this->m_orderdata.insert(make_pair(this->m_size, m));
		this->m_size++;
	}
}

void OrderFile::updateOrder()
{
	if (this->m_size == 0)
	{
		return;
	}
	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_size; i++)
	{
		ofs << "date:" << this->m_orderdata[i]["date"] << " ";
		ofs << "interval:" << this->m_orderdata[i]["interval"] << " ";
		ofs << "stuID" << this->m_orderdata[i]["stuID"] << " ";
		ofs << "stuName:" << this->m_orderdata[i]["stuName"] << " ";
		ofs << "roomID:" << this->m_orderdata[i]["roomID"] << " ";
		ofs << "status:" << this->m_orderdata[i]["status"] << endl;
	}
	ofs.close();
}
