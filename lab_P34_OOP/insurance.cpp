#include "insurance.h"

insurance::insurance(){
	this->start_date = 0;
	this->end_date = 0;
	this->is_active = false;
	this->policy_num = "XXXXXXXXXXXX";
	this->name = "-";
	this->surname = "-";//присваеваем значения по умолчанию
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
	if (policy_num.length() != 12) {//вызывая сетер проверем коректность данных
		this->policy_num = "XXXXXXXXXXXX";
	}
	else { 
		this->policy_num = policy_num; 
	}
	this->name = name;
	this->surname = surname; // присваеваем значения
}

void insurance::print_info(){
	string _start_date, _end_date;//строки под даты
	time_t date = get_start_date();//получаем дату начала
	struct tm buf;//структура времени
	gmtime_s(&buf, &date);//присваеваем дату структуре
	_start_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);//получаем строку с датой
	date = get_end_date();//получаем дату конца
	gmtime_s(&buf, &date);//присваеваем дату структуре
	_end_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);//получаем строку с датой
	cout << setw(20) << "policy_number:" << "| " << this->get_policy_num() << endl
		<< setw(20) << "name:" << "| " << this->get_name() << endl
		<< setw(20) << "surname:" << "| " << this->get_surname() << endl
		<< setw(20) << "is it active:" << "| " << noboolalpha << this->get_is_active() << endl
		<< setw(20) << "start_date:" << "| " << _start_date << endl
		<< setw(20) << "end_date:" << "| " << _end_date << endl
		<< endl;//выводим всю информацию по выбранному элементу
}

void insurance::print_info_in_array(int num){
	string _start_date, _end_date;//строки под даты
	time_t date = get_start_date();//получаем дату начала
	struct tm buf;//структура времени
	gmtime_s(&buf, &date);//присваеваем дату структуре
	_start_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);//получаем строку с датой
	date = get_end_date();//получаем дату конца
	gmtime_s(&buf, &date);//присваеваем дату структуре
	_end_date = to_string(buf.tm_mday) + "." +
		to_string(buf.tm_mon + 1) + "." +
		to_string(buf.tm_year + 1900);//получаем строку с датой
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
	cout << setfill('-') << setw(155) << '-' << setfill(' ') << endl; //выводим всю информацию по выбранному элементу
}

void insurance::edit(){
	struct tm new_date;
	string edit_cmd;//переменная команд
	bool icmd = 0;//флаг неверной команды
	bool ied = 0;
	bool ival = 0;//флаг некоректного значения
	bool equal = 0;
	while (edit_cmd != "EXIT") {//цикл работы в режиме редактирования
		this->print_info();
		if (icmd) cout << "incorrect command" << endl;
		if (ied) cout << "end date can't be before start date" << endl;
		if (ival) cout << "incorrect value" << endl;//выводим сообщения об ошибках
		cout << "commands:" << endl;
		cout << "\t[parametr name] x - change value of parametr to x" << endl;
		cout << "\tif you want to change a date print dd.mm.yyyy insted of x" << endl;
		cout << "\tplease be careful, incorrect date will break the programm" << endl;
		cout << "\tthe date should exist, and be after 1.1.1970" << endl;
		cout << "\tpolicy number shuld be 12 symbols length" << endl;
		cout << "\tis it active changes automatically" << endl;
		cout << "\tEXIT - return to main menu" << endl << endl;//выводим список команд
		cin >> edit_cmd;//запрашиваем ввод команды
		icmd = 0;
		ied = 0;
		ival = 0;//зануляем флаги после прошлой итерации
		if (edit_cmd == "policy_number") {
			string new_num;//переменная для нового значения
			cin >> new_num;//считываем новое значение
			if (new_num.length() != 12) {//проверяем, чтобы id не был < 1
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
			if (!icmd) {//если ошибок нет присваеваем новое значение
				this->set_policy_num(new_num);
			}
		}

		else if (edit_cmd == "name") {
			string new_name;//переменная для нового значения
			cin >> new_name;//считываем новое значение
			this->set_name(new_name);//присваеваем новое значение
		}

		else if (edit_cmd == "surname") {
			string new_surname;//переменная для нового значения
			cin >> new_surname;//считываем новое значение
			this->set_surname(new_surname);//присваеваем новое значение
		}

		else if (edit_cmd == "start_date") {
			time_t new_time = 0;
			struct tm new_date;//переменная для нового значения
			gmtime_s(&new_date, &new_time);//присваеваем дату структуре
			cin >> get_time(&new_date, "%d.%m.%Y");//считываем дату
			new_time = mktime(&new_date);//переводи дату в time_t
			new_time += 3 * 3600;//приводим к МСК
			this->set_start_date(new_time);//присваеваем новое значение
		}

		else if (edit_cmd == "end_date") {
			time_t new_time = 0;
			struct tm new_date;//переменная для нового значения
			gmtime_s(&new_date, &new_time);//присваеваем дату структуре
			cin >> get_time(&new_date, "%d.%m.%Y");//считываем дату
			new_time = mktime(&new_date);//переводи дату в time_t
			new_time += 3 * 3600;//приводим к МСК
			this->set_end_date(new_time);//присваеваем новое значение
		}

		else {
			icmd = 1;//выставляем флаг ошибки при неверной команде
		}
		system("cls");
	}
}

bool insurance::is_set(){
	if (this->get_name() != "-" && this->get_surname() != "-" &&
		this->get_policy_num() != "XXXXXXXXXXXX" && this->get_end_date() != 0) {//проверяем отличаются ли значения от значений по умолчанию
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
