#include <bits/stdc++.h>
#include <string>

using namespace std;

int ci(string s){
	int n;

	if(s=='a') n=0;

int main(){
	
	string s, sdash;
	sdash=s.substr(1, 2);//sの1文字目から2文字抽出しsdashに代入(0は不可)
	sdash=s.substr(3);//3文字目から末尾まで
	int x=atoi(sdash.c_str());//sdashをint型に変換しxに代入


	char ch = s[4];//文字型ch に文字列sの4番目(0から可)を代入


	string str = "abcde";		//
	str.insert(2, "zzz");		//挿入
	cout << str << endl; // abzzzcde//


	cout << s.size() << endl;//sの大きさを出力(lengthと同じ)

}
