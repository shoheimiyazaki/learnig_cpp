#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>
#include <string.h>
#include "split.hpp"
using namespace std;
vector<string> list;

string str;
ifstream ifs("input2.text");
ofstream fout("result1.text");
vector<std::string> split(const std::string &str, char sep);
#define LIMITUNUM 1000000

class PredictNum{
private:
    float from_num_x;
    float from_num_y;
    float to_num_x ;
    float to_num_y ;
    float step ;
public:
    PredictNum(float fx ,float fy ,float tx ,float ty ,float s){
        from_num_x = fx;
        from_num_y = fy;
        to_num_x = tx;
        to_num_y = ty;
        step = s;
    };
    void make_numbers();
    void cheack_debag();
    float return_array[2][LIMITUNUM];
    int lenofarray;
};

//デバック用
void PredictNum::cheack_debag(){
    float a,b;
    cout << "("<<from_num_x << ","<<from_num_y <<")"<<endl;
    cout << "("<<to_num_x << ","<<to_num_y <<")"<<endl;
    cout <<to_num_y - from_num_y <<endl;
    cout << to_num_x - from_num_x<<endl;
    a = float(to_num_y - from_num_y)/float(to_num_x - from_num_x);
    b = (from_num_y - a*from_num_x);
    cout << from_num_y - a*from_num_x<<endl;
    cout << a <<"x +" <<  b<<endl;
    cout <<"len:"<< lenofarray<<endl;
    for(int i=0; i<10;i++){
        cout<<"\n";
    }
}
void PredictNum::make_numbers(){
    float a,b;
    //傾き
    a = float(to_num_y - from_num_y)/float(to_num_x - from_num_x);
    //切片
    b = (from_num_y - a*from_num_x);
    lenofarray=0;
    for (float i=from_num_x ; i<to_num_x ; i+=step){
        return_array[0][lenofarray] = i;
        return_array[1][lenofarray] = a*i + b;
        lenofarray+=1;
    }
};



///////////////////////////////////////////////

int main(void){
    float x1,y1,x2,y2;
    float results;
    char char1[40];
    char t[10];

    char *point;
    bool firstloop=true;
    //ファイルをダウンロード

    while (getline(ifs, str)){
        x1=x2;
        y1=y2;
        int i;
        for(i=0; i<40; i++ ){
            char1[i]=str[i];
        }

        point = strtok(char1,"\t");
        //cout<<point<<endl;
        x2=atof(point);
        point=strtok(NULL,"\t");
        //cout<<point<<endl;
        y2=atof(point);


        if(firstloop){
            firstloop=false;
            continue;
        }
        PredictNum Obj(x1,y1,x2,y2,0.0001);
        Obj.make_numbers();
        cout << x2 << ","<<y2<<endl;

        x1=x2;
        y1=y2;

        
        for(int i=0; i<Obj.lenofarray ; i++){
            cout << Obj.return_array[0][i] << '\t' << Obj.return_array[1][i]<<endl;
            fout << Obj.return_array[0][i] << '\t' << Obj.return_array[1][i]<<endl;
        }
        Obj.cheack_debag();
        

        
    }
    return 0;
};