#include "house_insurance.h"

house_insurance::house_insurance(){
	time_t null_time = 0;
	this->set_start_date(null_time);
	this->set_end_date(null_time);
	this->update_is_active();
	this->set_policy_num("XXXXXXXXXXXX");
	this->set_name("-");
	this->set_surname("-");
	this->price = 0;
	this->possible_pay = 0;
	this->house_id = "XXXXXXXXXXXX";
}

house_insurance::house_insurance(time_t start_date, time_t end_date, string policy_num,
								string name, string surname, float price, float possible_pay, string house_id){
	this->set_start_date(start_date);
	this->set_end_date(end_date);
	this->update_is_active();
	this->set_policy_num("XXXXXXXXXXXX");
	if (!this->set_policy_num(policy_num)) {
		this->set_policy_num("XXXXXXXXXXXX");
	}
	this->set_name(name);
	this->set_surname(surname);
	this->price = price;
	this->possible_pay = possible_pay;
	if (!this->set_house_id(house_id)) {
		this->house_id = "XXXXXXXXXXXX";
	}
	
}

bool house_insurance::is_set(){
	if (this->get_name() != "-" && this->get_surname() != "-" &&
		this->get_policy_num() != "XXXXXXXXXXXX" && this->get_end_date() != 0 &&
		this->get_house_id() != "XXXXXXXXXXXX" && this->get_price() != 0 && this->get_possible_pay() != 0) {
		return true;
	}
	return false;
}

void house_insurance::print_info(){
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
		<< setw(20) << "price:" << "| " << this->get_price() << endl
		<< setw(20) << "possible_pay:" << "| " << this->get_possible_pay() << endl
		<< setw(20) << "house_id:" << "| " << this->get_house_id() << endl
		<< endl;//������� ��� ���������� �� ���������� ��������
}

void house_insurance::print_info_in_array(int num){
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
		<< setw(5) << "house" << '|'
		<< setw(13) << this->get_policy_num() << '|'
		<< setw(15) << this->get_name() << '|'
		<< setw(15) << this->get_surname() << '|'
		<< setw(10) << noboolalpha << this->get_is_active() << '|'
		<< setw(12) << _start_date << '|'
		<< setw(12) << _end_date << '|'
		<< setw(13) << ' ' << '|'
		<< setw(10) << this->get_price() << '|'
		<< setw(16) << this->get_possible_pay() << '|'
		<< setw(13) << this->get_house_id() << '|'
		<< endl;
	cout << setfill('-') << setw(155) << '-' << setfill(' ') << endl; //������� ��� ���������� �� ���������� ��������
}

void house_insurance::edit(){
	struct tm new_date;
	string edit_cmd;//���������� ������
	bool icmd = 0;//���� �������� �������
	bool ied = 0;
	bool ival = 0;//���� ������������ ��������
	bool equal = 0;
	while (edit_cmd != "EXIT") {//���� ������ � ������ ��������������
		this->print_info();
		if (icmd) cout << "incorrect command" << endl;
		if (ied) cout << "end date can't be before start date" << endl;
		if (ival) cout << "incorrect value" << endl;//������� ��������� �� �������
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tif you want to change a date print dd.mm.yyyy insted of x" << endl;
		cout << "\tplease be careful, incorrect date will break the programm" << endl;
		cout << "\tthe date should exist, and be after 1.1.1970" << endl;
		cout << "\tpolicy number and house id shuld be 12 symbols length" << endl;
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
			cin >> get_time(&new_date, "%d.%m.%Y");
			new_time = mktime(&new_date);
			new_time += 3 * 3600;
			this->set_start_date(new_time);
		}

		else if (edit_cmd == "end_date") {
			time_t new_time = 0;
			struct tm new_date;//���������� ��� ������ ��������
			gmtime_s(&new_date, &new_time);
			cin >> get_time(&new_date, "%d.%m.%Y");
			new_time = mktime(&new_date);
			new_time += 3 * 3600;
			this->set_end_date(new_time);
		}

		else if (edit_cmd == "price") {
			float new_price;//���������� ��� ������ ��������
			cin >> new_price;//��������� ����� ��������
			this->set_price(new_price);//����������� ����� ��������
		}

		else if (edit_cmd == "possible_pay") {
			float new_possible_pay;//���������� ��� ������ ��������
			cin >> new_possible_pay;//��������� ����� ��������
			this->set_possible_pay(new_possible_pay);//����������� ����� ��������
		}

		else if (edit_cmd == "house_id") {
			string new_house_id;//���������� ��� ������ ��������
			cin >> new_house_id;//��������� ����� ��������
			if (!this->set_house_id(new_house_id)) {//���������, ����� id �� ��� < 1
				icmd = 1;
				ival = 1;//���������� ����� ������
			}
		}

		else {
			icmd = 1;//���������� ���� ������ ��� �������� �������
		}
		system("cls");
	}
}

bool house_insurance::set_house_id(string new_id){
	if (new_id.length() != 12) {
		return false;
	}
	else {
		this->house_id = new_id;
		return true;
	}
}

void house_insurance::set_price(float new_price){
	this->price = new_price;
}

void house_insurance::set_possible_pay(float new_possible_pay){
	this->possible_pay = new_possible_pay;
}

string house_insurance::get_house_id(){
	return this->house_id;
}

float house_insurance::get_price(){
	return this->price;
}

float house_insurance::get_possible_pay(){
	return this->possible_pay;
}
