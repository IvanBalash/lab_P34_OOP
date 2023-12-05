#pragma once
#include <iostream>
#include <string>
#include <ctime>
//#include <time.h>
#include <iomanip>

using namespace std;

class insurance{
private:
	time_t start_date;
	time_t end_date;
	bool is_active;
	string policy_num;
	string name;
	string surname;

protected:
	bool set_policy_num(string new_policy_num);
	void set_start_date(time_t new_start_date);
public:
	insurance();
	insurance(time_t start_date, time_t end_date,
			  string policy_num, string name, string surname);
	virtual void print_info();
	virtual void print_info_in_array(int num);
	virtual void edit();
	virtual bool is_set();
	bool set_end_date(time_t new_end_date);
	bool update_is_active();
	void set_name(string new_name);
	void set_surname(string new_surname);
	time_t get_start_date();
	time_t get_end_date();
	bool get_is_active();
	string get_policy_num();
	string get_name();
	string get_surname();
};

