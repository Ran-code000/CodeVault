#include <iostream>
using namespace std;
int DaysInMonth(int month, int year){
    switch (month){
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:  
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) return 29;
            else return 28;
    }
}

class DATE{
public:
    DATE::DATE(int initYear = 2000, int initMonth = 1, int initDay = 1) : year(initYear), month(initMonth), day(initDay);
    void Set(int, int, int);
    int getMonth() const{return month;}
    int getDay() const{return day;}
    int getYear() const{return year;}
    void Print() const;
    void Increment(){
        day++;
        if (day > DaysInMonth(month, year)){
            day = 1;
            month++;
            if (month > 12){
                month = 1;
                year++;
            }
        }
    }
    void Decrement(){
        day--;
        if (day == 0){
            if(month == 1){ 
                day = 31;
                month = 12;
                year--;
            }else{
                month--;
                day = DaysInMonth(month, year);
            }
        }
    }                  
private:
    int month;
    int day;
    int year; 
};
void DATE::Print() const{
   	switch(month){
        case 1:
            cout << "January ";
            break;
        case 2:
            cout << "February ";
            break;
        case 3:
            cout << "March ";
            break;
        case 4:
            cout << "April ";
            break;
        case 5:
            cout << "May ";
            break;
        case 6:
            cout << "June ";
            break;
        case 7:
            cout << "July ";
            break;
        case 8:
            cout << "Aguest ";
            break;
        case 9:
            cout << "September ";
            break;
        case 10:
            cout << "October ";
            break;
        case 11:
            cout << "November ";
            break;
        case 12:
            cout << "December ";
            break;
    }
    cout << ' ' << day << ", " << year << endl << endl;
}
int main(){                         //client.cpp 
     DATE  date1;                    //initYear, initMonth, initDay分别为2000，1，1
     DATE  date2( 1976 );            //initYear, initMonth, initDay分别为1976，1，1
     DATE  date3( 1976, 12 );        //initYear, initMonth, initDay分别为1976，12，1
     DATE  date4( 1976, 12, 20 );    //initYear, initMonth, initDay分别为1976，12，10
     date1.Print();
     date2.Print();
     date3.Print();
     date4.Print();
     return 0;
     
}