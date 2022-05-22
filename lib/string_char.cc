#include <bits/stdc++.h>
using namespace std;

//split関数 delimで区切られたstring配列を返す
vector<string> spl(const string &s, char delim) {
    vector<string> elems;
    string item;
    for (char ch: s) {
        if (ch == delim) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}

int main(){

	string s;
	cin>> s;

	//文字列の表示
	cout<< s <<endl;
	cout<< s.size() <<endl;
	cout<< s[0] <<endl;

	//文字列の順序
	if("ABC"<"abc") cout<< "less" <<endl;
	if("0"<"A") cout<< "less" <<endl;

	//文字列の足し算
	cout<< s+"hello" <<endl;
	s+="hello";
	s+='!';
	
	//substr
	cout<< "123456789".substr(3) <<endl; //456789 添字3以降を取り出す
	cout<< "123456789".substr(3, 4) <<endl; //4567 添字3以降を4文字取り出す
	
	//erase
	cout<< "123456789".erase(3) <<endl; //123 添字3以降を消す
	cout<< "123456789".substr(3, 4) <<endl;	//12389 添字3以降を4文字消す

	//insert
	cout<< "12345".insert(3, "hey") <<endl;	//123hey45 添字3に割り込む

	//find
	cout<< "123456789".find("34") <<endl; //2 初めて出現する添字の位置
	if(s.find("5")!=string::npos){
		//found
		cout<< s.find("5") <<endl;
	}else{
		//not found
		cout<< "not found" <<endl;
	}

	//replace
	cout<< ("123456789".replace(3, 4, "xx") <<endl; //123xxxx89 添字3以降を4文字をxにする

	//sort
	sort(s.begin(), s.end());
	cout<< s <<endl;
	sort(s.begin(), s.end(), greater<char>());
	cout<< s <<endl;

	//reverse
	reverse(s.begin(), s.end());
	cout<< s <<endl;

	//push, pop
	s.push_back('%');
	s.pop_back();

	//変換
	cout<< stoi(s) <<endl;//int型へ
	cout<< stoll(s) <<endl;//long long int型へ?
	cout<< stod(s) <<endl;//double型へ
	cout<< to_string(n) <<endl;



	int n;
	char c;
	cin>> n;
	cin>> c;

	//char型のcinは1文字ずつ
	for(int i=0;i<0;i++){
		char tmp;
		cin>> tmp;
		cout<< tmp <<endl;
	}

	//文字コード
	cout<< (int)'0' <<endl;
	cout<< (int)'9' <<endl;
	cout<< (int)'A' <<endl;
	cout<< (int)'Z' <<endl;
	cout<< (int)'a' <<endl;
	cout<< (int)'z' <<endl;
	cout<< (char)65 <<endl;
	cout<< (char)90 <<endl;
	cout<< (int)c <<endl;
	cout<< (char)n <<endl;

	//A~Zを表示
	for(int i=0;i<26;i++){
		cout<< (char)('A'+i) << " ";
	}
	cout<< endl;

	//大小判定
	if('A'<=c && c<='Z'){
		//大文字
		cout<< "large" <<endl;

		//大文字を小文字に
		cout<< (char)(c+('a'-'A')) <<endl;;
	}
	if('a'<=c && c<='z'){
		//小文字
		cout<< "small" <<endl;

		//小文字を大文字に
		cout<< (char)(c-('a'-'A')) <<endl;
	}

	//整数を1桁ずつ
	cout<< (int)(c-'0') <<endl;

	return 0;
}