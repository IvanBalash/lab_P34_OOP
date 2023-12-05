#include "med_insurance.h"

med_insurance::med_insurance(){
	time_t null_time = 0;
	this->set_start_date(null_time);
	this->set_end_date(null_time);
	this->update_is_active();
	this->set_policy_num("XXXXXXXXXXXX");
	this->set_name("-");
	this->set_surname("-");
	this->OMS_programm = "fed_oms";//присваеваем значения по умолчанию
}

med_insurance::med_insurance(time_t start_date, time_t end_date, string policy_num, 
							 string name, string surname, string OMS_programm){
	this->set_start_date(start_date);
	this->set_end_date(end_date);
	this->update_is_active();
	this->set_policy_num("XXXXXXXXXXXX");
	if (!this->set_policy_num(policy_num)) {
		this->set_policy_num("XXXXXXXXXXXX");//вызывая сетер проверем коректность данных
	}
	this->set_name(name);
	this->set_surname(surname);
	if (!this->set_oms_programm(OMS_programm)) {
		this->OMS_programm = "XXXXXXXXXXXX";//вызывая сетер проверем коректность данных
	}//присваеваем значения
}


bool med_insurance::set_oms_programm(string new_oms_programm){
	if (new_oms_programm.length() > 10) {
		return false;
	}
	else {
		this->OMS_programm = new_oms_programm;
		return true;
	}
}

string med_insurance::get_oms_programm(){
	return this->OMS_programm;
}

bool med_insurance::is_set(){
	if (this->get_name() != "-" && this->get_surname() != "-" &&
		this->get_policy_num() != "XXXXXXXXXXXX" && this->get_end_date() != 0 &&
		this->get_oms_programm() != "XXXXXXXXXXXX") {//проверяем отличаются ли значения от значений по умолчанию
		return true;
	}
	return false;
}

void med_insurance::print_info(){
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
		 << setw(20) << "is it active:" << "| " << noboolalpha <<  this->get_is_active() << endl
		 << setw(20) << "start_date:" << "| " << _start_date << endl
		 << setw(20) << "end_date:" << "| " << _end_date << endl
		 << setw(20) << "OMS_programm:" << "| " << this->get_oms_programm() << endl
		 << endl;//выводим всю информацию по выбранному элементу
}

void med_insurance::print_info_in_array(int num){
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
	cout << '|' << setw( 8) << num << '|'
				<< setw( 5) << "med" << '|'
				<< setw(13) << this->get_policy_num() << '|'
				<< setw(15) << this->get_name() << '|'
				<< setw(15) << this->get_surname() << '|'
				<< setw(10) << noboolalpha << this->get_is_active() << '|'
				<< setw(12) << _start_date << '|'
				<< setw(12) << _end_date << '|'
				<< setw(13) << this->get_oms_programm() << '|'
				<< setw(10) << ' ' << '|'
				<< setw(16) << ' ' << '|'
				<< setw(13) << ' ' << '|'
				<< endl;
	cout <<setfill('-') << setw(155) << '-' << setfill(' ') << endl;//выводим всю информацию по выбранному элементу
}

void med_insurance::edit(){
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

		else if (edit_cmd == "OMS_programm") {
			string new_oms_programm = 0;
			cin >> new_oms_programm;//считываем новое значение
			if (!this->set_oms_programm(new_oms_programm)) {
				icmd = 1;
				ival = 1;//выставляем флаги ошибок
			}
		}

		else {
			icmd = 1;//выставляем флаг ошибки при неверной команде
		}
		system("cls");
	}
}


