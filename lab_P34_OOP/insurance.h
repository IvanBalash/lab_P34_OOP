#pragma once
#include <iostream>//библиотеа ввода-вывода
#include <string>//библиотека строк
#include <ctime>//библиотека работы со временем
#include <iomanip>//библиотека форматирования ввода-вывода

using namespace std;

class insurance{
private:
	time_t start_date;//переменная даты начала полиса
	time_t end_date;//переменная даты завершения полиса
	bool is_active;//переменная активности полиса
	string policy_num;//переменная номера полиса
	string name;//переменная имени владельца
	string surname;//переменная фамилии владельца

protected:
	bool set_policy_num(string new_policy_num);
	void set_start_date(time_t new_start_date);//сетеры для класов наследников
public:
	insurance();//конструктор по умолчанию
	insurance(time_t start_date, time_t end_date,
			  string policy_num, string name, string surname);//конструктор
	virtual void print_info();//метод вывода на экран
	virtual void print_info_in_array(int num);//метод вывода на экран в составе масива
	virtual void edit();//метод изменения
	virtual bool is_set();//проверка инициализаций свойст не по умолчанию
	bool update_is_active();//обновление is_active
	//сетеры
	bool set_end_date(time_t new_end_date);
	void set_name(string new_name);
	void set_surname(string new_surname);
	//гетеры
	time_t get_start_date();
	time_t get_end_date();
	bool get_is_active();
	string get_policy_num();
	string get_name();
	string get_surname();
};

