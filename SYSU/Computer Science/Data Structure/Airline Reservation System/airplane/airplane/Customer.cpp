//
//  Customer.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

Customer::Customer():num_booked(0),num_alternative(0),max_booked(1),max_alternative(1){
    booked = new Booked[max_booked];
    alternative = new Alternative[max_alternative];
}

Customer::~Customer(){
    if(max_booked>0)
        delete[] booked;
    if(max_alternative>0)
        delete[] alternative;
}

Customer& Customer::operator=(Customer &p){
    if(max_booked>0)
        delete[] booked;
    if(max_alternative>0)
        delete[] alternative;
    num_booked = p.num_booked;
    num_alternative = p.num_alternative;
    max_booked = p.max_booked;
    max_alternative = p.max_alternative;
    booked = new Booked[max_booked];
    alternative = new Alternative[max_alternative];
    for (int i =0; i<num_booked; i++) {
        booked[i] = p.booked[i];
    }
    for (int i=0; i<num_alternative; i++) {
        alternative[i] = p.alternative[i];
    }
    
    return *this;
}

void Customer::addBooked(string name,string kindID,string ID,string num,string state,string kind,string ticket){
    if(max_booked==num_booked){
        Booked *p;
        max_booked = 2*max_booked;
        p = new Booked[max_booked];
        for (int i=0; i<num_booked; i++) {
            p[i] = booked[i];
        }
        delete[] booked;
        booked = p;
    }
    Booked b(name,kindID,ID,num,state,kind,ticket);
    booked[num_booked++] = b;
}

void Customer::addAlternative(string name,string kindID,string ID,string num,string kind){
    if(max_alternative==num_alternative){
        Alternative *p;
        max_alternative = 2*max_alternative;
        p = new Alternative[max_alternative];
        for (int i=0; i<num_alternative; i++) {
            p[i] = alternative[i];
        }
        delete[] alternative;
        alternative = p;
    }
    Alternative a(name,kindID,ID,num,kind);
    alternative[num_alternative++] = a;
}

void Customer::showBooked(){
    for (int i=0; i<num_booked; i++) {
        cout<<'('<<i+1<<')';
        booked[i].show();
    }
}

void Customer::showAlternative(){
    for (int i=0; i<num_alternative; i++) {
        cout<<'('<<i+1<<')';
        alternative[i].show();
    }
}

void Customer::informAlternative(string kind){
    int n=1;
    ofstream file("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/log.txt",ios::app);
    for (int i=0; i<num_alternative; i++) {
        if (alternative[i].kind==kind) {
            file<<'('<<n++<<')'<<alternative[i].inform();
        }
    }
    file.close();
}

string Customer::deleteBooked(int de){
    string s=booked[de].kind;
    if (num_booked>1) {
        booked[de]=booked[num_booked-1];
    }
    num_booked--;
    return s;
}

string Customer::Save(){
    ostringstream s;
    if (num_booked>0) {
        for (int i=0; i<num_booked; i++) {
            s<<booked[i].Save()<<',';
        }
    }
    else{
        s<<"NA";
    }
    s<<'\n';
    if (num_alternative>0) {
        for (int i=0; i<num_alternative; i++) {
            s<<alternative[i].Save()<<',';
        }
    }
    else{
        s<<"NA";
    }
    return s.str();
}

