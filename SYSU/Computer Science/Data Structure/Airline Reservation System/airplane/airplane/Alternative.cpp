//
//  Alternative.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

Alternative::Alternative(string name,string kindID,string ID,string num,string kind):name(name),kindID(kindID),ID(ID),num(num),kind(kind){}

Alternative& Alternative::operator=(Alternative &b){
    name=b.name;
    kindID=b.kindID;
    ID=b.ID;
    num=b.num;
    kind=b.kind;
    return *this;
}

void Alternative::show(){
    cout<<inform();
}

string Alternative::inform(){
    return name+'\t'+kindID+'\t'+ID+'\t'+'\t'+kind+'\n';
}

string Alternative::Save(){
    ostringstream s;
    s<<name<<'\t'<<kindID<<'\t'<<ID<<'\t'<<num<<'\t'<<kind;
    return s.str();
}
