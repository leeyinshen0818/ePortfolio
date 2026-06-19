#include<iostream>
using namespace std ;

int main(){
	
	int num, modulus, result = 1 ;
	
	cout << "Number: " ;
	cin >> num ;
	
	if(num == 0){
		result = 0 ;
		cout << "Enter a positive number!" ;
	}
		
		while(num != 0){
			modulus = num % 10 ;
			num /= 10 ;
			result *= modulus ;
		}
	
		cout << "Result: " << result << endl ;
		
		if(result%4==0 && result%5!=0 && result%7!=0){
			cout << "Result is a multiple of 4" << endl ;
		}
		
		else if(result%4!=0 && result%5==0 && result%7!=0){
			cout << "Result is a multiple of 5" << endl ;
		}	
		
		else if(result%4!=0 && result%5!=0 && result%7==0){
			cout << "Result is a multiple of 7" << endl ;
		}	
		
		else if(result%4==0 && result%5==0 && result%7!=0){
			cout << "Result is a multiple of 4 and 5" << endl ;
		}
		
		else if(result%4==0 && result%5!=0 && result%7==0){
			cout << "Result is a multiple of 4 and 7" << endl ;	
		}
		
		else if(result%4!=0 && result%5==0 && result%7==0){
			cout << "Result is a multiple of 5 and 7" << endl ;
		}
				
		else if(result%4==0 && result%5==0 && result%7==0){
			cout << "Result is a multiple of 4, 5, and 7" << endl ;
		}
		
		else {
			cout << "Result is not a multiple of 4, 5 and 7" << endl ; 
		}


	
	return 0 ; 
	
}

