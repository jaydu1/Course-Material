//
//  airplane.cpp
//  airplane
//
//  Created by 杜金鸿 on 2017/5/22.
//  Copyright © 2017年 杜金鸿. All rights reserved.
//

#include "airplane.hpp"


Airplane::Airplane(int num_city/*=5*/):num_city(num_city),cityname("City.txt"),planename("plane.txt"){
    city = new City[num_city];
    arc = new Arc[num_city];
    for(int i=0; i<num_city; i++){
        arc[i].Init(num_city);
    }
}

Airplane::~Airplane(){
    delete[] city;
    delete[] arc;
}

void Airplane::Init(){
    ifstream fileIn("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/City.txt");
    string s;
    if (fileIn) {
        int i=0;
        while (getline(fileIn,s)) {
            addCity(s,i++);
        }
        fileIn.close();
    }
    citytonum.addcity(city,num_city);
    fileIn.open("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/plane.txt");
    if (fileIn) {
        string year,month,day,date;
        while (getline(fileIn,s,'\n')) {
            istringstream str(s);
            getline(str,year,'\t');
            getline(str,month,'\t');
            getline(str,day,'\t');
            getline(str,date,'\t');
            if (getline(fileIn,s,'/') && s!="" ) {
                istringstream str2(s);
                while(getline(str2,s,'#')){
                    addPlane(year,month,day,date,s);
                    getline(str2,s,'\n');
                }
                getline(fileIn,s,'\n');
            }
        }
        fileIn.close();
    }
}

void Airplane::addCity(const string &s, int i){
    istringstream str(s);
    getline(str,city[i].name,'\t');
    getline(str,city[i].ID,'\t');
    string airport;
    while(getline(str,airport,'\t')){
        city[i].addAirport(airport);
    }
}

void Airplane::addPlane(string &year,string &month,string &day,string &date,const string &s){
    istringstream str(s);
    string list;
    string name,start,arrive;

    getline(str,name,'\t');
    getline(str,start,'\t');
    getline(str,arrive,'\t');
    int city0=-1,city1=-1,plat0,plat1;
    for (int i=0; i<num_city; i++) {
        if (city[i].ID==start.substr(0,3)) {
            city0 = i;
        }
        else if (city[i].ID==arrive.substr(0,3)){
            city1 = i;
        }
        if (city0>=0 && city1>=0) {
            break;
        }
    }
    plat0=atoi(start.substr(2,1).c_str());
    plat1=atoi(arrive.substr(2,1).c_str());
    addArc(year,month,day,date,s,city0,city1,plat0,plat1);
    int i=0;
    for (i=check_table_time.num_plane-1; i>=0; i--) {
        if (year+month+day>=check_table_time.time[i][0]+check_table_time.time[i][1]+check_table_time.time[i][2]) {
            break;
        }
    }
    if (i==check_table_time.num_plane-1) {
        check_table_time.addPlane(city0,city1,arc[city0].arc[city1].num_plane,year,month,day,date);
    }
    else{
        check_table_time.addPlane(city0,city1,arc[city0].arc[city1].num_plane,year,month,day,date);
        for (int j=check_table_time.num_plane-2; j>i; j--) {
            for (int k=0; k<3; k++) {
                check_table_time.plane[j+1][k] = check_table_time.plane[j][k];
            }
            for (int k=0; k<4; k++) {
                check_table_time.time[j+1][k] = check_table_time.time[j][k];
            }
        }
        check_table_time.plane[i+1][0] = city0;
        check_table_time.plane[i+1][1] = city1;
        check_table_time.plane[i+1][2] = arc[city0].arc[city1].num_plane;
        check_table_time.time[i+1][0] = year;
        check_table_time.time[i+1][1] = month;
        check_table_time.time[i+1][2] = day;
        check_table_time.time[i+1][3] = date;
    }
}

void Airplane::addArc(string &year,string &month,string &day,string &date,const string &s,int city0,int city1,int plat0,int plat1){
    istringstream strings(s);
    string ss;
    getline(strings,ss,'\n');
    istringstream str(ss);
    getline(str,ss,'\t');
    string name=ss;
    getline(str,ss,'\t');getline(str,ss,'\t');
    getline(str,ss,'\t');
    string schedule=ss;
    getline(str,ss,'\t');
    string start=ss;
    getline(str,ss,'\t');
    string arrive=ss;
    getline(str,ss,'\t');
    string shape=ss;
    getline(str,ss,'\t');
    string discount=ss;
    string kind[3];
    int price[3],now[3],max[3];
    int num=0;
    while (getline(str,ss,'\t')) {
        kind[num] = ss;
        getline(str,ss,'\t');
        price[num]=atoi(ss.c_str());
        getline(str,ss,'\t');
        now[num]=atoi(ss.c_str());
        getline(str,ss,'\t');
        max[num]=atoi(ss.c_str());
        num++;
    }
    Plane p(name,year,month,day,date,schedule,start,arrive,shape,discount,num,kind,price,now,max,plat0,plat1);
    arc[city0].arc[city1].addPlane(p);
    
    
    getline(strings,ss,'\n');
    if (ss!="NA") {
        istringstream str(ss);
        string sss;
        while (getline(str,sss,',')) {
            istringstream s4(sss);
            getline(s4,sss,'\t');
            string name2=sss;
            getline(s4,sss,'\t');
            string kindID=sss;
            getline(s4,sss,'\t');
            string ID=sss;
            getline(s4,sss,'\t');
            string num2=sss;
            getline(s4,sss,'\t');
            string state=sss;
            getline(s4,sss,'\t');
            string kind2=sss;
            getline(s4,sss,'\t');
            string ticket=sss;
            arc[city0].arc[city1].plane[arc[city0].arc[city1].num_plane-1].customer.addBooked(name2, kindID, ID, num2, state, kind2, ticket);
        }
    }
    getline(strings,ss);
    if (ss!="NA") {
        stringstream str(ss);
        string sss;
        while (getline(str,sss,',')){
            istringstream s4(sss);
            getline(s4,sss,'\t');
            string name2=sss;
            getline(s4,sss,'\t');
            string kindID=sss;
            getline(s4,sss,'\t');
            string ID=sss;
            getline(s4,sss,'\t');
            string num2=sss;
            getline(s4,sss,'\t');
            string kind2=sss;
            arc[city0].arc[city1].plane[arc[city0].arc[city1].num_plane-1].customer.addAlternative(name2, kindID, ID, num2, kind2);
        }
    }
}

void Airplane::Sort(){
    check_table = check_table_time;
    for (int j=5; j>1; j--) {
        Check_Table q[10];
        Distribute(q,10,j);
        Collect(q,10);
    }
    for (int j=1; j>=0; j--) {
        Check_Table q[26];
        Distribute(q,26,j);
        Collect(q,26);
    }

}

void Airplane::Distribute(Check_Table q[], int m, int j){
    int k;
    for (int i=0; i<check_table.num_plane; i++) {
        char c=arc[check_table.plane[i][0]].arc[check_table.plane[i][1]].plane[check_table.plane[i][2]-1].name[j];
        if (j<2) {
            k = c;
            k = k-65;
        }
        else{
            k=atoi(&c);
        }
        q[k].addPlane(check_table.plane[i][0], check_table.plane[i][1], check_table.plane[i][2]);
    }
}

void Airplane::Collect(Check_Table q[], int m){
    Check_Table c;
    for (int i=0; i<m; i++) {
        for (int j=0; j<q[i].num_plane; j++) {
            c.addPlane(q[i].plane[j][0], q[i].plane[j][1], q[i].plane[j][2]);
        }
    }
    check_table = c;
}

void Airplane::Search(Check_Table &c,string ID,string year,string month,string day,string start,string arrive,string start_city,string arrive_city){
    cout<<"***************************   直达航班信息   **************************"<<endl;
    c = check_table;
    if (ID!="NA") {
        int i=0,j= c.num_plane-1;
        int low = 0,high = c.num_plane-1;
        while (low<high) {
            int mid = (low+high)>>1;
            (ID<arc[c.plane[mid][0]].arc[c.plane[mid][1]].plane[c.plane[mid][2]-1].name)?high=mid:low=mid+1;
        }
        while (i<j) {
            int mid=(i+j)>>1;
            (ID>arc[c.plane[mid][0]].arc[c.plane[mid][1]].plane[c.plane[mid][2]-1].name)?i=mid+1:j=mid;
        }
        Check_Table ct;
        for(int k=i;k<low;k++)
            ct.addPlane(c.plane[k][0], c.plane[k][1], c.plane[k][2]);
        c = ct;
    }

    if (year!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(year == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].year){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (month!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(month == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].month){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (day!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(day == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].day){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (start!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(start == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].start){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (arrive!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(arrive == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].arrive){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (start_city!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(start_city == city[c.plane[i][0]].name || start_city == city[c.plane[i][0]].ID){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    if (arrive_city!="NA"&&c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(arrive_city == city[c.plane[i][1]].name || arrive_city == city[c.plane[i][1]].ID){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
            }
        }
        c = ct;
    }
    
    if (c.num_plane==0) {
        cout<<"无相应直达航班！"<<endl;
    }
    else{
        int price=99999;
        for (int i=0; i<c.num_plane; i++) {
            cout<<'('<<i+1<<')'<<endl;
            cout<<city[c.plane[i][0]].name+city[c.plane[i][0]].airport[arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].plat_start]+"🛫   ☁️  ☁️  ☁️  ☁️  ☁️  ☁️  ☁️  ☁️    🛬"+city[c.plane[i][1]].name+city[c.plane[i][1]].airport[arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].plat_arrive]<<endl;
            cout<<"\t航班号\t\t日期\t\t星期\t\t出发时间\t到达时间\t班期\t机型\t\t折扣\n\t";
            arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].show();
            price = min(price,arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].Minprice());
        }
        cout<<"最小费用航班为:";
        for (int i=0; i<c.num_plane; i++) {
            if(price ==arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].Minprice()){
                cout<<'('<<i+1<<')'<<'\t';
            }
        }
        cout<<endl;
    }
    bool is = c.num_plane;
    for (int i=0; i<c.num_plane; i++) {
        for (int j=0; j<arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].num; j++) {
            if (arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].num_max[j]>arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].num_now[j]) {
                is = false;
                break;
            }
        }
    }
    if (is || (ID=="NA" && start_city!="NA" && arrive_city!="NA")) {
        cout<<"***************************   中转航班信息   **************************"<<endl;
        Transfer(c,year,month,day,start_city,arrive_city);
    }

}

void Airplane::Transfer(Check_Table &c0, string year, string month, string day, string start_city, string arrive_city){
    Check_Table c;
    c=check_table_time;
    int n = c0.num_plane;
    if (year!="NA" && c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(year == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].year){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2], c.time[i][0],c.time[i][1],c.time[i][2],c.time[i][3]);
            }
        }
        c = ct;
    }
    if (month!="NA" && c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(month == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].month){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2], c.time[i][0],c.time[i][1],c.time[i][2],c.time[i][3]);
            }
        }
        c = ct;
    }
    if (day!="NA" && c.num_plane>0) {
        Check_Table ct;
        for (int i=0; i<c.num_plane; i++) {
            if(day == arc[c.plane[i][0]].arc[c.plane[i][1]].plane[c.plane[i][2]-1].day){
                ct.addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2], c.time[i][0],c.time[i][1],c.time[i][2],c.time[i][3]);
            }
        }
        c = ct;
    }
    string year1=c.time[0][0],month1=c.time[0][1],day1=c.time[0][2];
    Check_Table ct[num_city+1];
    ct[num_city] = c0;
    int num = c0.num_plane;
    int price;
    for (int i=0; i< c.num_plane; i++) {
        string year2=check_table_time.time[i][0],month2=check_table_time.time[i][1],day2=check_table_time.time[i][2];
        if (year1+month1+day1!=year2+month2+day2) {
            price = SearchTransfer(ct,start_city,arrive_city);
            if (price<9999) {
                for (int j=num; j<ct[num_city].num_plane; j++) {
                    cout<<'('<<num+j+1<<')'<<endl;
                    cout<<city[citytonum[start_city]].name+city[citytonum[start_city]].airport[arc[citytonum[start_city]].arc[ct[num_city].plane[j][1]].plane[ct[num_city].plane[j][0]-1].plat_start]+"  ✈️  ✈️  ✈️  "+city[ct[num_city].plane[j][1]].name+city[ct[num_city].plane[j][1]].airport[arc[citytonum[start_city]].arc[ct[num_city].plane[j][1]].plane[ct[num_city].plane[j][0]-1].plat_arrive]+"  ✈️  ✈️  ✈️  "+city[citytonum[arrive_city]].name+city[citytonum[arrive_city]].airport[arc[ct[num_city].plane[j][1]].arc[citytonum[arrive_city]].plane[ct[num_city].plane[j][2]-1].plat_arrive]<<endl;
                    cout<<"\t航班号\t\t日期\t\t星期\t\t出发时间\t到达时间\t班期\t\t机型\t\t折扣\n\t";
                    arc[citytonum[start_city]].arc[ct[num_city].plane[j][1]].plane[ct[num_city].plane[j][0]-1].show();
                    cout<<"\t航班号\t\t日期\t\t星期\t\t出发时间\t到达时间\t班期\t\t机型\t\t折扣\n\t";
                    arc[ct[num_city].plane[j][1]].arc[citytonum[arrive_city]].plane[ct[num_city].plane[j][2]-1].show();
                    cout<<endl;
                }
                cout<<"该日最低费用为:"<<price<<endl;
                year1=year2;month1=month2;day1=day2;
            }
            num = ct[num_city].num_plane;
            for (int i=0; i<num_city; i++) {
                ct[i].Clear();
            }
        }
        ct[c.plane[i][0]].addPlane(c.plane[i][0], c.plane[i][1], c.plane[i][2]);
    }
    price = SearchTransfer(ct,start_city,arrive_city);
    if (price<9999) {
        cout<<year1<<'.'<<month1<<'.'<<day1<<endl;
        for (int i=num; i<ct[num_city].num_plane; i++) {
            cout<<'('<<num+i+1<<')'<<endl;
            cout<<city[citytonum[start_city]].name+city[citytonum[start_city]].airport[arc[citytonum[start_city]].arc[ct[num_city].plane[i][1]].plane[ct[num_city].plane[i][0]-1].plat_start]+"  ✈️  ✈️  ✈️  "+city[ct[num_city].plane[i][1]].name+city[ct[num_city].plane[i][1]].airport[arc[citytonum[start_city]].arc[ct[num_city].plane[i][1]].plane[ct[num_city].plane[i][0]-1].plat_arrive]+"  ✈️  ✈️  ✈️  "+city[citytonum[arrive_city]].name+city[citytonum[arrive_city]].airport[arc[ct[num_city].plane[i][1]].arc[citytonum[arrive_city]].plane[ct[num_city].plane[i][2]-1].plat_arrive]<<endl;
            cout<<"\t航班号\t\t日期\t\t星期\t\t出发时间\t到达时间\t班期\t\t机型\t\t折扣\n\t";
            arc[citytonum[start_city]].arc[ct[num_city].plane[i][1]].plane[ct[num_city].plane[i][0]-1].show();
            cout<<"\t航班号\t\t日期\t\t星期\t\t出发时间\t到达时间\t班期\t\t机型\t折扣\n\t";
            arc[ct[num_city].plane[i][1]].arc[citytonum[arrive_city]].plane[ct[num_city].plane[i][2]-1].show();
            cout<<endl;
        }
        cout<<"该日最低费用为:"<<price<<endl;
    }
    num = ct[num_city].num_plane;
    c0 = ct[num_city];
    if (n==c0.num_plane) {
        cout<<"无相应中转航班!"<<endl;
    }
}

int Airplane::SearchTransfer(Check_Table c[], string start_city, string arrive_city){
    Check_Table ct;
    int price=9999;
    int start=citytonum[start_city],arrive=citytonum[arrive_city];
    for (int i=0; i<c[start].num_plane; i++) {
        int mid = c[start].plane[i][1];
        for (int j=0; j<c[mid].num_plane; j++) {
            if (c[mid].plane[j][1]==arrive && arc[start].arc[mid].plane[c[start].plane[i][2]-1].arrive<=arc[mid].arc[arrive].plane[c[mid].plane[j][2]-1].start) {
                if (arc[start].arc[mid].plane[c[start].plane[i][2]-1].Minprice()+arc[mid].arc[arrive].plane[c[mid].plane[j][2]-1].Minprice()<price) {
                    price=arc[start].arc[mid].plane[c[start].plane[i][2]-1].Minprice()+arc[mid].arc[arrive].plane[c[mid].plane[j][2]-1].Minprice();
                    ct.Clear();
                    ct.addPlane(c[start].plane[i][2], mid, c[mid].plane[j][2]);
                }
                else if (arc[start].arc[mid].plane[c[start].plane[i][2]-1].Minprice()+arc[mid].arc[arrive].plane[c[mid].plane[j][2]-1].Minprice()==price){
                    ct.addPlane(c[start].plane[i][2], mid, c[mid].plane[j][2]);
                }
            }
        }
    }
    for (int i=0; i<ct.num_plane; i++) {
        c[num_city].addPlane(ct.plane[i][0], ct.plane[i][1], ct.plane[i][2]);
    }
    return price;
}

int Airplane::addBooked(int m, int n, int l, string name, string kindID, string ID, string book_num, string state, string kind, string ticket){
    int i=0;
    for (; i<arc[m].arc[n].plane[l-1].num; i++) {
        if (arc[m].arc[n].plane[l-1].kind[i]==kind) {
            break;
        }
    }
    int num=atoi(book_num.c_str());
    if (arc[m].arc[n].plane[l-1].num_max[i]-arc[m].arc[n].plane[l-1].num_now[i]>=num) {
        arc[m].arc[n].plane[l-1].customer.addBooked(name, kindID, ID, book_num, state, kind, ticket);
        return num;
    }
    arc[m].arc[n].plane[l-1].customer.addAlternative(name, kindID, ID, book_num, kind);
    return 0;
}

int Airplane::addAlternative(int m, int n, int l, string name,string kindID,string ID,string book_num,string kind){
    arc[m].arc[n].plane[l-1].customer.addAlternative(name,kindID,ID,book_num,kind);
    return atoi(book_num.c_str());
}

void Airplane::showBooked(int m, int n, int l){
    arc[m].arc[n].plane[l-1].customer.showBooked();
}

void Airplane::showAlternative(int m, int n, int l){
    arc[m].arc[n].plane[l-1].customer.showAlternative();
}

string Airplane::deleteBooked(int m, int n, int l, string name, string ID){
    int i=0;
    for (; i<arc[m].arc[n].plane[l-1].customer.num_booked; i++) {
        if (arc[m].arc[n].plane[l-1].customer.booked[i].name==name && arc[m].arc[n].plane[l-1].customer.booked[i].ID==ID) {
            break;
        }
    }
    if (i==arc[m].arc[n].plane[l-1].customer.num_booked) {
        return "";
    }
    int num_booked = atoi(arc[m].arc[n].plane[l-1].customer.booked[i].num.c_str());
    string kind = arc[m].arc[n].plane[l-1].customer.deleteBooked(i);
    int j=0;
    for (j=0; j<arc[m].arc[n].plane[l-1].num; j++) {
        if (kind==arc[m].arc[n].plane[l-1].kind[j]) {
            break;
        }
    }
    arc[m].arc[n].plane[l-1].num_now[j] -= num_booked;
    return kind;
}

void Airplane::informAlternative(int m, int n, int l,string kind){

    int i;
    for (i=0; i<arc[m].arc[n].plane[l-1].num; i++) {
        if (arc[m].arc[n].plane[l-1].kind[i]==kind) {
            break;
        }
    }
    ofstream file("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/log.txt",ios::app);
    file<<"航班"<<arc[m].arc[n].plane[l-1].name<<'\t'<<arc[m].arc[n].plane[l-1].year<<'.'<<arc[m].arc[n].plane[l-1].month<<'.'<<arc[m].arc[n].plane[l-1].day<<'\t'<<kind<<"有余票"<<arc[m].arc[n].plane[l-1].num_max[i]-arc[m].arc[n].plane[l-1].num_now[i]<<"张,"<<"替补客户有:\n";
    file.close();
    arc[m].arc[n].plane[l-1].customer.informAlternative(kind);
}

void Airplane::Save(){
    ofstream fileOut("/Users/dujinhong/Documents/study/数据结构/数据结构实验/大作业/airplane/airplane/plane.txt");
    if (fileOut.is_open()) {
        string year=" ",month=" ",day=" ",date=" ";
        for (int i=0; i<check_table_time.num_plane; i++) {
            string year2=check_table_time.time[i][0],month2=check_table_time.time[i][1],day2=check_table_time.time[i][2],date2=check_table_time.time[i][3];
            if (year!=year2 || month!=month2 || day!=day2 || date !=date2) {
                if (i>0) {
                    fileOut<<'/'<<'\n';
                }
                fileOut<<year2<<'\t'<<month2<<'\t'<<day2<<'\t'<<date2<<'\n';
                year = year2; month = month2; day = day2; date = date2;
            }
            else{
                fileOut<<'\n';
            }
            fileOut<<arc[check_table_time.plane[i][0]].arc[check_table_time.plane[i][1]].plane[check_table_time.plane[i][2]-1].Save(city[check_table_time.plane[i][0]].ID,city[check_table_time.plane[i][1]].ID);
            fileOut<<'#';
        }
        fileOut<<'/';
    }

}

void Airplane::Change(int m, int n, int l){
    cout<<"---------------------------------------------------------------------"<<endl;
    cout<<"请输入航班信息（'NA'跳过,'-1'返回）:"<<endl;
    string in;
    cout<<"起飞时间:";cin>>in;
    if (in=="-1") {
        return;
    }
    else if (in!="NA") {
        arc[m].arc[n].plane[l-1].start = in;
    }
    cout<<"到达时间:";cin>>in;
    if (in=="-1") {
        return;
    }
    else if (in!="NA") {
        arc[m].arc[n].plane[l-1].arrive = in;
    }
    cout<<"折扣:";cin>>in;
    if (in=="-1") {
        return;
    }
    else if (in!="NA") {
        arc[m].arc[n].plane[l-1].discount = in;
    }
    cout<<"舱位类型数:";cin>>in;
    if (in=="-1") {
        return;
    }
    else if (in!="NA") {
        arc[m].arc[n].plane[l-1].num = atoi(in.c_str());
        for (int i=0; i<arc[m].arc[n].plane[l-1].num; i++) {
            cout<<"舱位类型"<<i+1<<":";
            cin>>arc[m].arc[n].plane[l-1].kind[i];
            cout<<"价格:";
            cin>>arc[m].arc[n].plane[l-1].price[i];
            cout<<"已订人数:";
            cin>>arc[m].arc[n].plane[l-1].num_now[i];
            cout<<"满载人数:";
            cin>>arc[m].arc[n].plane[l-1].num_max[i];
        }
    }
}

void Airplane::DeletePlane(int m, int n, int l){
    if (arc[m].arc[n].num_plane==l) {
        check_table.num_plane--;
        check_table_time.num_plane--;
    }
    else{
        arc[m].arc[n].plane[l] = arc[m].arc[n].plane[arc[m].arc[n].num_plane-1];
        int i;
        for (i=0; i<check_table.num_plane; i++) {
            if (check_table.plane[i][0]==m && check_table.plane[i][1]==n && check_table.plane[i][2]==l) {
                break;
            }
        }
        for (int j=i; i<check_table.num_plane-1; j++) {
            for (int k=0; k<3; k++) {
                check_table.plane[j][k] = check_table.plane[j+1][k];
            }
            for (int k=0; k<4; k++) {
                check_table_time.time[j][k] = check_table_time.time[j+1][k];
            }
        }
        check_table.num_plane--;
        for (i=0; i<check_table_time.num_plane; i++) {
            if (check_table_time.plane[i][0]==m && check_table_time.plane[i][1]==n && check_table_time.plane[i][2]==l) {
                break;
            }
        }
        for (int j=i; i<check_table_time.num_plane-1; j++) {
            for (int k=0; k<3; k++) {
                check_table_time.plane[j][k] = check_table_time.plane[j+1][k];
            }
            for (int k=0; k<4; k++) {
                check_table_time.time[j][k] = check_table_time.time[j+1][k];
            }
        }
        check_table_time.num_plane--;
    }
}

void Airplane::show(int i, int j, int k){
    cout<<arc[i].arc[j].plane[k-1].name<<','<<arc[i].arc[j].plane[k-1].year<<'.'<<arc[i].arc[j].plane[k-1].month<<'.'<<arc[i].arc[j].plane[k-1].day<<','<<arc[i].arc[j].plane[k-1].date<<','<<arc[i].arc[j].plane[k-1].start<<'-'<<arc[i].arc[j].plane[k-1].arrive<<endl;
}
