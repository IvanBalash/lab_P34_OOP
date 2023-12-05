#pragma once
#include "insurance.h"
class med_insurance :
    public insurance{
private:
    string OMS_programm;
public:
    med_insurance();
    med_insurance(time_t start_date, time_t end_date,
                  string policy_num, string name, string surname,
                  string OMS_programm);
    bool set_oms_programm(string new_oms_programm);
    string get_oms_programm();
    void print_info();
    void print_info_in_array(int num);
    void edit();
};

