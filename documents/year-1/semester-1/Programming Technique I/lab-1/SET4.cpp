#include<iostream>
using namespace std ;

int main(){
	
	int num, modulus, result = 1 ;
	
	cout << "Enter a number: " ;
	cin >> num ;
	
	do{	
		modulus = num % 10 ;
		num /= 10 ;
		result *= modulus ;
		
	}while(num != 0) ; 
	
	cout << "Result: " << result << endl ;
	
	if(result%2==0 && result%3!=0 && result%5!=0){
		cout << "Result is an even number" << endl ;
 	}	
 	
 	else if(result%2==0 && result%3==0 && result%5!=0){
		cout << "Result is an even number and multiple of 3" << endl ;
	}	
	
	else if(result%2==0 && result%3!=0 && result%5==0){
		cout << "Result is an even number and multiple of 5" << endl ;
	}
		
	else if(result%2==0 && result%3==0 && result%5==0){
		cout << "Result is an even number and multiple of 3 and 5" << endl ;
	}
	
	else if(result%2!=0 && result%3!=0 && result%5!=0){
		cout << "Result is an odd number" << endl ;
	}
	
	else if(result%2!=0 && result%3==0 && result%5!=0){
		cout << "Result is an odd number and multiple of 3" << endl ;
	}
	
	else if(result%2!=0 && result%3!=0 && result%5==0){
		cout << "Result is an odd number and multiple of 5" << endl ;
	}
	
	else {
		cout << "Result is an odd number and multiple of 3 and 5" << endl ;
	}
	
	return 0 ;
	
}

