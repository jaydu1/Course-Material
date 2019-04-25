//
//  CitytoNum.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/5.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

CitytoNum::CitytoNum():num(0){
}

CitytoNum::~CitytoNum(){
    if (num>0) {
        delete[] name;
        delete [] ID;
    }
}

int CitytoNum::operator[](string cityname){
    for (int i=0; i<num; i++) {
        if (cityname==name[i] || cityname==ID[i]) {
            return i;
        }
    }
    return -1;
}

void CitytoNum::addcity(City *city, int num){
    if (this->num>0) {
        delete[] name;
        delete [] ID;
    }
    this->num=num;
    name = new string[num];
    ID = new string[num];
    for (int i=0; i<num; i++) {
        name[i] = city[i].name;
        ID[i] = city[i].ID;
    }
}
