#include <iostream> //for cout,cin
#include <vector>
#include <fstream> //for open
#include <string>
#include <sstream> //for split

using namespace std;


// complement:::補間する
class Liner_Complement{
public:
    vector <float> newxArray;
    vector <float> newyArray;
    Liner_Complement(string filename,float step);
private:
    vector <float> xArray;
    vector <float> yArray;
    float step;
    void makenumbers();
    vector <string> split(const string& input , char delimiter);
};
Liner_Complement::Liner_Complement(string filename,float step){
    /*
    第一引数：ファイルの名前
    第二引数：結果の歩幅
    */

    //変数宣言
    string filestring;
    ifstream inputfile;
    vector<string> splitted;
    this->step = step;

    //ファイルダウンロード
    inputfile.open(filename);

    //ファイルの読み込み失敗時
    if (!inputfile){
        cout << "Error: cannot open file" << endl;
        inputfile.close();
        exit(1);
    }

    //テキストの読み込み
    while (getline(inputfile,filestring)){
        splitted = this->split(filestring,'\t');
        float x = stof(splitted[0]);
        float y = stof(splitted[1]);
        //cout << "(" << x << "," << y << ")" << endl;
        this->xArray.push_back(x);
        this->yArray.push_back(y);
    }
    this->makenumbers();

    //ファイルを閉じる
    inputfile.close();
};

//実際に数字を補間するところ
void Liner_Complement::makenumbers(){
    float a,b;
    float x1,y1,x2,y2;
    if (xArray.size()!=yArray.size()){
        cout<<"Error:xarray size is different from yarray size" << endl;
    }
    for(int i = 0; i != xArray.size(); ++i) {
        x1 = xArray[i];
        y1 = yArray[i];
        x2 = xArray[i+1];
        y2 = yArray[i+1];

        //傾き
        a = float(y2 - y1)/float(x2 - x1);
        //切片
        b = (y1 - a*x1);
        for (float i = x1; i < x2; i+=step){
            newxArray.push_back(i);
            newyArray.push_back(a*i+b);
            cout<<i<<","<<a*i+b<<endl;
        }
    }
}

//split関数をクラス内部に入れました。
vector <string> Liner_Complement::split(const string& input ,char delimiter){
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)){
        result.push_back(field);
    }
    return result;
}


int main(void){
    Liner_Complement Obj("input2.text",0.0001);

    return 0;
}

