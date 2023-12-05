#pragma once
#include "insurance.h"
class house_insurance :
    public insurance{
private:
    float price;//переменная цены
    float possible_pay;//переменная максимальной выплаты
    string house_id;//переменная id застрахованого дома
public:
    house_insurance();//конструктор по умолчанию
    house_insurance(time_t start_date, time_t end_date,
                    string policy_num, string name, string surname,
                    float price, float possible_pay, string house_id);//конструктор
    bool is_set();
    void print_info();
    void print_info_in_array(int num);
    void edit();
    //сетеры
    bool set_house_id(string new_id);
    void set_price(float new_price);
    void set_possible_pay(float new_possible_pay);
    //гетеры
    string get_house_id();
    float get_price();
    float get_possible_pay();
};

