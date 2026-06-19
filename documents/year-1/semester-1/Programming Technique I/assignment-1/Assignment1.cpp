#include<iostream>
using namespace std;

int main(){
	
	const int SIZE = 20 ;
	char name1[SIZE], name2[SIZE], matric1[SIZE], matric2[SIZE] ;
			
	cout << "What is your name? " << "\n- ";
	cin.getline(name1, SIZE) ;
	cout << "What is your matric number? " << "\n- ";
	cin.getline(matric1, SIZE) ;
		
	cout << "What is your member's name? " << "\n- ";
	cin.getline(name2, SIZE) ;
	cout << "What is your member's matric number? " << "\n- " ;
	cin.getline(matric2, SIZE) ; 
	
	cout << "\nHello " << name1 << " " << matric1 << endl ;
	
	cout << "\nHello " << name2 << " " << matric2 << endl ;
	
	return 0 ; 
	
} 
