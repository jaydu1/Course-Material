//
//  City.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/6/4.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"

City::City():num_airport(0),max_num(1){
    airport = new string[max_num];
}

void City::addAirport(string s){
    if(max_num==num_airport){
        string *p;
        max_num = 2*max_num;
        p = new string[max_num];
        for (int i=0; i<num_airport; i++) {
            p[i] = airport[i];
        }
        delete[] airport;
        airport = p;
    }
    airport[num_airport++] = s;
}

City::~City(){
    delete[] airport;
}

