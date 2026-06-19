#include<iostream>
#include<cstring>
using namespace std;
const int MAX_SIZE = 999 ;

void calculateKeywordPercentage(char[]);

int main(){
	
	char input[MAX_SIZE] ;
	
	cin.getline(input, MAX_SIZE) ;
	calculateKeywordPercentage(input) ;


	return 0 ; 
}

void calculateKeywordPercentage(char in[]){
	char target[] = {"data"}, t[MAX_SIZE] ;
	int count = 0, size = 0 ;
	while(true){
		t[MAX_SIZE] = in[size] ;
		if(t == target){
			count++ ;
			size++ ;

		}
		if(t == '\0'){
			break ;
		}
	}
	
	cout << count ;
}


