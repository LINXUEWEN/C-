#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define ADMIN_FILE "admin.txt"
#define STUDENT_FILE "student.txt"
#define TEACHER_FILE "teacher.txt"
#define COMPUTER_FILE "computer_room.txt"
#define ORDER_FILE "order.txt"

enum Class
{
	EXIT,
	STUDENT,
	TEACHER,
	MANAGER
};

class ComputerRoom
{
public:
	int m_comid;
	int m_maxnum;
};

class Identity//身份抽象类
{
public:
	virtual void operMenu() = 0;
	string m_name;
	string m_pwd;
};

class Student :public Identity
{
public:
	Student();
	Student(int id, string name, string pwd);
	virtual void operMenu();
	void applyOrder();
	void showMyOrder();
	void showAllOrder();
	void cancelOrder();

	vector<ComputerRoom> v_computer;

	int m_id;
};

class Teacher :public Identity
{
public:
	Teacher();
	Teacher(int empID, string name, string pwd);
	virtual void operMenu();
	void showAllOrder();
	void validOrder();

	int m_empID;
};

class Manager :public Identity
{
public:
	Manager();
	Manager(string name, string pwd);
	virtual void operMenu();
	void addPerson();
	void showPerson();
	void showComputer();
	void clearFile();

	void initVector();

	vector<Student> v_student;
	vector<Teacher> v_teacher;
	vector<ComputerRoom> v_computer;


	bool checkRepeat(int id, int type);

};

class OrderFile
{
public:
	OrderFile();
	void updateOrder();
	map<int, map<string, string>> m_orderdata;

	int m_size;
};

void LoginIn(string file_name, int type);
void managerMenu(Identity* &manager);
void studentMenu(Identity* &student);
void teacherMenu(Identity* &teacher);
