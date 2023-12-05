
#include <iostream>//библиотеа ввода-вывода
#include <string>//библиотека строк
#include <iomanip>//библиотека форматирования ввода-вывода
#include <regex>//библиотека работы с регулярными выражениями
#include <fstream>//библиотека фалового ввода вывода
#include "insurance.h"
#include "med_insurance.h"
#include "house_insurance.h"//подключаем созданые нами классы

using namespace std;

void data_write(insurance** data, int length) { // фунция вывода данных на экран
	cout << '|' << setw(7) << "number" << setw(2) << '|'
		<< setw(4) << "type" << setw(2) << '|'
		<< setw(12) << "policy num" << setw(2) << '|'
		<< setw(10) << "name" << setw(6) << '|'
		<< setw(12) << "surname" << setw(4) << '|'
		<< setw(10) << "is active" << setw(1) << '|'
		<< setw(11) << "start date" << setw(2) << '|'
		<< setw(10) << "end date" << setw(3) << '|'
		<< setw(11) << "OMS prog" << setw(3) << '|'
		<< setw(8)  << "price" << setw(3) << '|'
		<< setw(12)  << "max pay" << setw(5) << '|'
		<< setw(11) << "house id" << setw(3) << '|'
		<< endl;
	cout << setfill('=') << setw(155) <<'=' << setfill(' ') << endl;// делаем заголовок
	for (int i = 0; i < length; i++) { // цикл в котором выписываем все структуры по очереди
		(*(data[i])).print_info_in_array(i + 1);
	}
	cout << endl;
}

string MAX(insurance** data, int length){
	time_t max = 0;
	int num_of_max;
	for (size_t i = 0; i < length; i++){
		time_t time_length = (*(data[i])).get_end_date() - (*(data[i])).get_start_date();
		if (time_length > max) {
			max = time_length;
			num_of_max = i;
		}
	}
	return (*(data[num_of_max])).get_policy_num();
}

string ENDS_LAST(insurance** data, int length) {
	time_t max = 0;
	int num_of_max;
	for (size_t i = 0; i < length; i++) {
		time_t end_time = (*(data[i])).get_end_date();
		if (end_time > max) {
			max = end_time;
			num_of_max = i;
		}
	}
	return (*(data[num_of_max])).get_policy_num();
}

void ADD(insurance*** data, int length) {
	string add_cmd;
	bool icmd = 0;//флаг неверной команды
	bool type_chousen = 0;//флаг выбора типа страховки
	bool all_added = 0;
	insurance** old_data = *data;
	insurance** new_data = new insurance*[length + 1];
	for (size_t i = 0; i < length; i++) {
		new_data[i] = old_data[i];
	}
	while (!type_chousen) {
		system("cls");
		cout << "what type of insurance it will be?" << endl;
		cout << "\tmed - medical insurance" << endl;
		cout << "\thouse - house insurance" << endl;
		cout << "\tgnrl - general insurance" << endl << endl;
		cin >> add_cmd;
		icmd = 0;
		if (add_cmd == "med") {
			med_insurance* new_insurance = new med_insurance();
			new_data[length] = new_insurance;
			type_chousen = 1;
		}
		else if (add_cmd == "house") {
			house_insurance* new_insurance = new house_insurance();
			new_data[length] = new_insurance;
			type_chousen = 1;
		}
		else if (add_cmd == "gnrl") {
			insurance* new_insurance = new insurance();
			new_data[length] = new_insurance;
			type_chousen = 1;
		}
		else {
			icmd = 1;
		}
	}
	icmd = 0;
	
	while (!all_added){
		system("cls");
		if (icmd) {
			cout << "pleas enter all parametrs";
		}
		(*(new_data[length])).edit();
		if ((*(new_data[length])).is_set()) {
			all_added = 1;
			
		}
		else {
			icmd = 1;
		}
	}
	*data = new_data;// присваеваем новое значение исходному масиву
	delete[](old_data);//отчищаем ранее выделеную память
	system("cls");
}

void DEL(insurance*** data, int length, int line) {
	insurance** new_data = new insurance*[length - 1];//создаем новый масив маеньшего размера
	insurance** old_data = *data;//копируем исхлдный масив в новую переменную
	int j = 0;//счетчик нового масива
	for (size_t i = 0; i < length; i++) {//проходим по старому масиву
		if (i != line) {//игнорируем удаленный элемент
			new_data[j] = old_data[i];//копируем остальные в новый масив
			j++;
		}
	}
	*data = new_data;//присваеваем новый масив исходному
	delete[](old_data);//удаляем старый масив
}

void EDIT(insurance** data, int line, int length) {
	(*(data[line])).edit();//вызываем метод для изменения свойств
}

int main() {
	system("mode con lines=40 cols=160");//задаем размер консоли
	string cmd = "";// создаем переменную для команд со значение по умолчанию READ
	int length = 5;//создаем переменную с длиной масива
	int line = 0; // переменная номера лини для взаимодействия
	bool icmd = 0;
	bool nl = 0;// флаг неверной команды
	bool is_added = 0;//флаг успешного добавления
	bool ans = 0;
	string answer = "";
	time_t start = 1600128000;
	time_t end = 1789430400;
	med_insurance* ins1 = new med_insurance(start, end,
											string("QER45672OP1F"),
											string("Petr"), string("Ivanov"),
											string("fed_oms"));

	start = 1523836800;
	end = 1650067200;
	insurance* ins2 = new insurance(start, end,
									string("QERHG8694LKN"),
									string("Viktor"), string("Sidorov"));
	start = 1626480000;
	end = 1721174400;
	house_insurance* ins3 = new house_insurance(start, end,
												string("TUNRE6734NPD"),
												string("Jon"), string("Filatov"),
												10000, 1000000, string("PONKLED67941"));

	start = 1693267200;
	end = 1861574400;
	med_insurance* ins4 = new med_insurance(start, end,
											string("POSRG5739JBF"),
											string("Anna"), string("Kuznetsov"),
											string("spb_oms"));

	start = 1693342800;
    end = 1756425600;
	house_insurance* ins5 = new house_insurance(start, end,
												string("IOMKD8942HLR"),
												string("Ivan"), string("Fedorov"),
												50000, 10000000, string("ZOHELEG97871"));
											
	insurance** data = new insurance*[5]{ins1, ins2, ins3, ins4, ins5};// создаем масив указателей на базовый класс

	while (cmd != "STOP") {//основной цикл программы, который будет работать пока мы не введем команду STOP
		data_write(data, length);// выводим данные масива
		cout << "commands:" << endl;
		cout << "\tADD - add new record" << endl;
		cout << "\tMAX - print number of police that works longest time" << endl;
		cout << "\tENDS_LAST - print number of police that ends last" << endl;
		cout << "\tEDIT x - edit record number x" << endl;
		cout << "\tDEL x - delete record number x" << endl;
		cout << "\tSTOP - exit the console app" << endl << endl;// выводим список команд

		if (icmd) {
			cout << "incorrect command" << endl;
		}
		if (nl) {
			cout << "there is no such number of record" << endl;
		}
		if (is_added) {
			cout << "successfuly added" << endl;//сообщение об успешном сохранении
		}
		if (ans) {
			cout << "answer is: " << answer << endl;//сообщение об успешном сохранении
		}
		cout << "command: ";
		cin >> cmd;//просим ввести команду
		system("cls");//отчищаем экран
		icmd = 0;
		nl = 0;
		is_added = 0;
		ans = 0;//зануляем флаги после прошлой итерации

		if (cmd == "ADD") {
			ADD(&data, length);
			length++;
			is_added = 1;
		}

		else if (cmd == "MAX") {
			answer = MAX(data, length);
			ans = 1;
		}

		else if (cmd == "ENDS_LAST") {
			answer = ENDS_LAST(data, length);
			ans = 1;
		}

		else if (cmd == "EDIT") {
			cin >> line;//считываем значение x
			if (line > length || line < 1) {//проверям коректность x
				icmd = 1;
				nl = 1;//выставляем флаги ошибок
			}
			else {
				line--;//дикриментируем line, чтобы проще работать с масивом
				EDIT(data, line, length);//вызываем функцию обработчик задачи
			}
		}

		else if (cmd == "DEL") {
			cin >> line;//считываем значение x
			if (line > length || line < 1) {//проверям коректность x
				icmd = 1;
				nl = 1;//выставляем флаги ошибок
			}
			else {
				line--;//дикриментируем line, чтобы проще работать с масивом
				DEL(&data, length, line);//вызываем функцию обработчик задачи
				length--;//дикриментируем переменную длины масива
			}
		}

		else {
			icmd = 1;//выставляем флаг ошибки при неверной команде
		}
		
	}
	delete[](data);//освобождаем память
	cout << "goodbay :)" << endl;//прощаемся с пользователем
	return 0;
}