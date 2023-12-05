#pragma once
#include "insurance.h"
class med_insurance :
    public insurance{
private:
    string OMS_programm;//переменная типа ОМС
public:
    med_insurance();//конструктор по умолчанию
    med_insurance(time_t start_date, time_t end_date,
                  string policy_num, string name, string surname,
                  string OMS_programm);//конструктор
    bool set_oms_programm(string new_oms_programm);//сетер OMS_programm
    string get_oms_programm();//гетер OMS_programm
    bool is_set();
    void print_info();
    void print_info_in_array(int num);
    void edit();
};

