#include "insurance.h"

insurance::insurance(){
	this->start_date = 0;
	this->end_date = 0;
	this->is_active = false;
	this->policy_num = "XXXXXXXXXXXX";
	this->name = "-";
	this->surname = "-";
}

insurance::insurance(time_t start_date, time_t end_date, 
					 string policy_num, string name, string surname){
	time_t now = time(NULL);
	this->start_date = start_date;
	this->end_date = end_date;
	if (now < end_date) {
		this->is_active = true;
	}
	else {
		this->is_active = false;
	}
	if (policy_num.length() != 12) {
		this->policy_num = "XXXXXXXXXXXX";
	}
	else { 
		this->policy_num = policy_num; 
	}
	this->name = name;
	this->surname = surname;
}

void insurance::print_info(){
	string _start_date, _end_date;
	time_t date = get_start_date();
	struct tm buf;
	gmtime_s(&buf, &date);
	_start_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);
	date = get_end_date();
	gmtime_s(&buf, &date);
	_end_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);
	cout << setw(20) << "policy_number:" << "| " << this->get_policy_num() << endl
		<< setw(20) << "name:" << "| " << this->get_name() << endl
		<< setw(20) << "surname:" << "| " << this->get_surname() << endl
		<< setw(20) << "is it active:" << "| " << noboolalpha << this->get_is_active() << endl
		<< setw(20) << "start_date:" << "| " << _start_date << endl
		<< setw(20) << "end_date:" << "| " << _end_date << endl
		<< endl;//������� ��� ���������� �� ���������� ��������
}

void insurance::print_info_in_array(int num){
	string _start_date, _end_date;
	time_t date = get_start_date();
	struct tm buf;
	gmtime_s(&buf, &date);
	_start_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);
	date = get_end_date();
	gmtime_s(&buf, &date);
	_end_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);
	cout << '|' << setw(8) << num << '|'
		 << setw(5) << "gnrl" << '|'
		 << setw(13) << this->get_policy_num() << '|'
		 << setw(15) << this->get_name() << '|'
		 << setw(15) << this->get_surname() << '|'
		 << setw(10) << noboolalpha << this->get_is_active() << '|'
		 << setw(12) << _start_date << '|'
		 << setw(12) << _end_date << '|'
		<< setw(13) << ' ' << '|'
		<< setw(10) << ' ' << '|'
		<< setw(16) << ' ' << '|'
		<< setw(13) << ' ' << '|'
		 << endl;
	cout << setfill('-') << setw(155) << '-' << setfill(' ') << endl; //������� ��� ���������� �� ���������� ��������
}

void insurance::edit(){
	struct tm new_date;
	string edit_cmd;//���������� ������
	bool icmd = 0;//���� �������� �������
	bool ied = 0;
	bool ival = 0;//���� ������������ ��������
	bool equal = 0;
	while (edit_cmd != "EXIT") {//���� ������ � ������ ��������������
		system("cls");
		this->print_info();
		if (icmd) cout << "incorrect command" << endl;
		if (ied) cout << "end date can't be before start date" << endl;
		if (ival) cout << "incorrect value" << endl;//������� ��������� �� �������
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tif you want to change a date print dd mm yyyy insted of x" << endl;
		cout << "\tpolicy number shuld be 12 symbols length" << endl;
		cout << "\tis it active changes automatically" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//������� ������ ������
		cin >> edit_cmd;//����������� ���� �������
		icmd = 0;
		ied = 0;
		ival = 0;//�������� ����� ����� ������� ��������
		if (edit_cmd == "policy_number") {
			string new_num;//���������� ��� ������ ��������
			cin >> new_num;//��������� ����� ��������
			if (new_num.length() != 12) {//���������, ����� id �� ��� < 1
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
			if (!icmd) {//���� ������ ��� ����������� ����� ��������
				this->set_policy_num(new_num);
			}
		}

		else if (edit_cmd == "name") {
			string new_name;//���������� ��� ������ ��������
			cin >> new_name;//��������� ����� ��������
			this->set_name(new_name);//����������� ����� ��������
		}

		else if (edit_cmd == "surname") {
			string new_surname;//���������� ��� ������ ��������
			cin >> new_surname;//��������� ����� ��������
			this->set_surname(new_surname);//����������� ����� ��������
		}

		else if (edit_cmd == "start_date") {
			time_t new_time = 0;
			struct tm new_date;//���������� ��� ������ ��������
			gmtime_s(&new_date, &new_time);
			int mon;
			int year;
			int day;
			cin >> day;//��������� ����� ��������
			cin >> mon;//��������� ����� ��������
			cin >> year;//��������� ����� ��������
			if ((mon > 0 && mon < 13) && (year >= 1970)) {
				new_time += (year - 1970) * 365 * 24 * 3600;
				new_time += (mon - 1) * 30 * 24 * 3600;
				new_time += (day - 1) * 24 * 3600;
				gmtime_s(&new_date, &new_time);
				while (!equal) {
					if (new_date.tm_year < (year - 1900)) {
						new_time += 1 * 365 * 24 * 3600;
					}
					else if (new_date.tm_year > (year - 1900)) {
						new_time -= 1 * 365 * 24 * 3600;
					}
					else {
						if (new_date.tm_mon > (mon - 1)) {
							new_time -= 1 * 28 * 24 * 3600;
						}
						else if (new_date.tm_mon < (mon - 1)) {
							new_time += 1 * 28 * 24 * 3600;
						}
						else {
							if (new_date.tm_mday > day) {
								new_time -= 1 * 24 * 3600;
							}
							else if (new_date.tm_mday < day) {
								new_time += 1 * 24 * 3600;
							}
						}
					}
					gmtime_s(&new_date, &new_time);
					if (((new_date.tm_mon + 1) == mon)
						&& ((new_date.tm_year + 1900) == year)
						&& (new_date.tm_mday == day)) {
						equal = 1;
					}
				}
				new_time = mktime(&new_date);
				this->set_start_date(new_time);
			}
			else {
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
		}

		else if (edit_cmd == "end_date") {
			time_t new_time = 0;
			struct tm new_date;//���������� ��� ������ ��������
			gmtime_s(&new_date, &new_time);
			int mon;
			int year;
			int day;
			cin >> day;//��������� ����� ��������
			cin >> mon;//��������� ����� ��������
			cin >> year;//��������� ����� ��������
			if ((mon > 0 && mon < 13) && (year >= 1970)) {
				new_time += (year - 1970) * 365 * 24 * 3600;
				new_time += (mon - 1) * 30 * 24 * 3600;
				new_time += (day - 1) * 24 * 3600;
				gmtime_s(&new_date, &new_time);
				while (!equal) {
					if (new_date.tm_year < (year - 1900)) {
						new_time += 1 * 365 * 24 * 3600;
					}
					else if (new_date.tm_year > (year - 1900)) {
						new_time -= 1 * 365 * 24 * 3600;
					}
					else {
						if (new_date.tm_mon > (mon - 1)) {
							new_time -= 1 * 28 * 24 * 3600;
						}
						else if (new_date.tm_mon < (mon - 1)) {
							new_time += 1 * 28 * 24 * 3600;
						}
						else {
							if (new_date.tm_mday > day) {
								new_time -= 1 * 24 * 3600;
							}
							else if (new_date.tm_mday < day) {
								new_time += 1 * 24 * 3600;
							}
							else {
								equal = 1;
							}
						}
					}
					gmtime_s(&new_date, &new_time);
				}
				new_time = mktime(&new_date);
				if (!this->set_end_date(new_time)) {
					icmd = 1;
					ied = 1;//���������� ����� ������
				}
			}
			else {
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
		}

		else {
			icmd = 1;//���������� ���� ������ ��� �������� �������
		}
	}
	system("cls");
}

bool insurance::is_set(){
	if (this->get_name() != "-" && this->get_surname() != "-" &&
		this->get_policy_num() != "XXXXXXXXXXXX" && this->get_end_date() != 0) {
		return true;
	}
	return false;
}

bool insurance::set_end_date(time_t new_end_date){
	if (new_end_date <= this->start_date) {
		return 0;
	}
	this->end_date = new_end_date;
	update_is_active();
	return 1;
}

bool insurance::update_is_active(){
	time_t now = time(NULL);
	if (now < this->end_date) {
		this->is_active = true;
	}
	else {
		this->is_active = false;
	}
	return this->is_active;
}

bool insurance::set_policy_num(string new_policy_num){
	if (new_policy_num.length() != 12) {
		return false;
	}
	else {
		this->policy_num = new_policy_num;
		return true;
	}
}

void insurance::set_start_date(time_t new_start_date){
	this->start_date = new_start_date;
}

void insurance::set_name(string new_name){
	this->name = new_name;
}

void insurance::set_surname(string new_surname){
	this->surname = new_surname;
}

time_t insurance::get_start_date(){
	return this->start_date;
}

time_t insurance::get_end_date(){
	return this->end_date;
}

bool insurance::get_is_active(){
	return update_is_active();
}

string insurance::get_policy_num(){
	return this->policy_num;
}

string insurance::get_name(){
	return this->name;
}

string insurance::get_surname(){
	return this->surname;
}
