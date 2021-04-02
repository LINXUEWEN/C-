#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define FILENAME "empfile.txt"

enum Choice
{
	EXIT,
	ADD,
	DISPLAY,
	DELETE,
	MOD,
	FIND,
	SORT,
	CLEAR
};

class Worker{
public:
	virtual void show_info() = 0;//显示个人信息
	virtual string get_deptname() = 0;//获取岗位名称

	string m_name;
	int m_id;
	int m_did;//职工所在部门名称编号
};

class Work_manager
{
public:
	Work_manager();

	void Show_menu();
	void Exit_system();

	int m_empnum;
	Worker ** m_emparray;

	void add_emp();
	void save();
	bool m_File_is_empty;
	int get_empnum();
	void init_emp();

	void Show_emp();
	void Del_emp();
	int is_exist(int id);
	void Mod_emp();
	void find_emp();
	void sort_emp();

	void clear_emp();

	~Work_manager();
};

class Employee :public Worker{
public:
	Employee(string name, int id, int did);

	virtual void show_info();

	virtual string get_deptname();
};

class Manager :public Worker{
public:
	Manager(string name, int id, int did);

	virtual void show_info();

	virtual string get_deptname();
};

class Boss :public Worker{
public:
	Boss(string name, int id, int did);

	virtual void show_info();

	virtual string get_deptname();
};
