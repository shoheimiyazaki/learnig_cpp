#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <vector>
using namespace std;
vector<string> list;
string str;
ifstream ifs("input.text");
ofstream fout( "results.text", ios::app );

#define LIMITUNUM 100000

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
    lenofarray=0.0;
    for (float i=from_num_x ; i<to_num_x ; i+=step){
        return_array[0][lenofarray] = i;
        return_array[1][lenofarray] = a*i + b;
        lenofarray+=1;
    }
};

///////////////////////////////////////////////

vector<string> split(const string& input, char delimiter){
    istringstream stream(input);

    string field;
    vector<std::string> result;
    while (std::getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

///////////////////////////////////////////////



int main(void){
    float x1,y1,x2,y2;
    bool isx=true;
    bool isfirstloop=true;
    //ファイルをダウンロード
    while (getline(ifs, str)){
        const std::string input = str;
        x1=x2;
        y1=y2;
        //ファイルの1つ目と２つ目を取り出す。
        for (const string& s : split(input, ' ')) {
            if(isx){
                isx=false;
                x2=(float)stoi(s);
            }else{
                isx=true;
                y2=(float)stoi(s);
            }
        }

        PredictNum Obj(x1,y1,x2,y2,0.01);
        Obj.make_numbers();
        for(int i=0; i<Obj.lenofarray ; i++){
            cout << Obj.return_array[0][i] << "   " << Obj.return_array[1][i]<<endl;
            fout << Obj.return_array[0][i] << "   " << Obj.return_array[1][i]<<endl;
        }
    }
    return 0;
};