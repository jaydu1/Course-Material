//
//  Plane.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"


Plane::Plane(string name,string year,string month,string day,string date,string schedule,string start,string arrive,string shape,string discount,int num, string* kind,int* price,int* num_now,int* num_max,int plat_start,int plat_arrive):name(name),year(year),month(month),day(day),date(date),schedule(schedule),start(start),arrive(arrive),shape(shape),discount(discount),num(num),plat_start(plat_start),plat_arrive(plat_arrive){
    this->kind = new string[num];
    this->price = new int[num];
    this->num_now = new int[num];
    this->num_max = new int[num];
    for (int i=0; i<num; i++) {
        this->kind[i]=kind[i];
        this->price[i]=price[i];
        this->num_now[i]=num_now[i];
        this->num_max[i]=num_max[i];
    }
}

Plane::~Plane(){
    if (num>0) {
        delete[] kind;
        delete[] price;
        delete[] num_max;
        delete[] num_now;
    }
}

Plane& Plane::operator=(Plane &p){
    name = p.name;
    year = p.year;
    month = p.month;
    day = p.day;
    date = p.date;
    start = p.start;
    arrive = p.arrive;
    plat_start = p.plat_start;
    plat_arrive = p.plat_arrive;
    schedule =p.schedule;
    shape = p.shape;
    discount = p.discount;
    if (num>0) {
        delete[] kind;
        delete[] price;
        delete[] num_max;
        delete[] num_now;
    }
    num = p.num;
    kind = new string[num];
    price = new int[num];
    num_now = new int[num];
    num_max = new int[num];
    for (int i=0; i<num; i++) {
        kind[i] = p.kind[i];
        price[i] = p.price[i];
        num_now[i]=p.num_now[i];
        num_max[i]=p.num_max[i];
    }
    customer = p.customer;
    return *this;
}

void Plane::show(){
    cout<<name<<'\t'<<year<<'.'<<month<<'.'<<day<<'\t'<<date<<'\t'<<start<<'\t'<<arrive<<'\t'<<schedule<<'\t'<<shape<<'\t'<<discount<<'\n';
    for (int i=0; i<num; i++) {
        cout<<"\t\t"<<kind[i]<<'\t'<<price[i]<<"  "<<'\t'<<num_now[i]<<'/'<<num_max[i]<<endl;
    }
}

int Plane::Minprice(){
    int pri=99999;
    for (int i=0; i<num; i++) {
        if (pri>price[i]) {
            pri=price[i];
        }
    }
    return pri;
}

string Plane::Save(string start_city,string arrive_city){
    ostringstream s;
    
    s<<name+'\t'+start_city<<plat_start<<'\t'+arrive_city<<plat_arrive<<'\t'+schedule+'\t'+start+'\t'+arrive+'\t'+shape+'\t'+discount+'\t';
    for (int i=0; i<num; i++) {
        s<<kind[i]<<'\t'<<price[i]<<'\t'<<num_now[i]<<'\t'<<num_max[i]<<'\t';
    }
    s<<'\n';
    s<<customer.Save();
    
    return s.str();
}
