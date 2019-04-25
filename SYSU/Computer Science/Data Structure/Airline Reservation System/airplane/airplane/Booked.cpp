//
//  Booked.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

Booked::Booked(string name,string kindID,string ID,string num,string state,string kind,string ticket):name(name),kindID(kindID),ID(ID),num(num),state(state),kind(kind),ticket(ticket){
}


Booked& Booked::operator=(Booked &b){
    name=b.name;
    kindID=b.kindID;
    ID=b.ID;
    num=b.num;
    state=b.state;
    kind=b.kind;
    ticket=b.ticket;
    return *this;
}

void Booked::show(){
    cout<<name<<'\t'<<kindID<<'\t'<<ID<<'\t'<<num<<'\t'<<state<<'\t'<<kind<<'\t'<<ticket<<endl;
}

string Booked::Save(){
    ostringstream s;
    s<<name<<'\t'<<kindID<<'\t'<<ID<<'\t'<<num<<'\t'<<state<<'\t'<<kind<<'\t'<<ticket;
    return s.str();
}
