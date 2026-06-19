#include<iostream>
using namespace std ;

int main(){
	
	int year; 
	double rainfall, averageRF ;
	int month = 12, TM = 0 ;
	double totalRF = 0.0 ;
	
	cout << "Enter the number of years: " ;
	cin >> year ;
	
	while( year < 1 ){
		cout << "Invalid input and try again! " << endl ; 
		cout << "Enter the number of years: " ;
		cin >> year ; 
	}
	
	for( int Y = 1 ; Y <= year ; Y++ ){
		for( int M = 1 ; M <= month ; M++ ){
			
			cout << "Rainfall year " << Y << " month " << M << ": " ;
			cin >> rainfall ;
				
			while (rainfall < 0){
				cout << "Rainfall must be positive value" << endl ;
				cout << "Rainfall year " << Y << " month " << M << ": " ;
				cin >> rainfall ;
				}
		
			
			totalRF += rainfall ;
			TM++ ;
		
		}
		
	}
	
	averageRF = totalRF / TM ;
	cout << "\n\nNumber of months: " << TM << endl ;
	cout << "Total inches of rainfall: " << totalRF << endl ;
	cout << "average rainfall per month: " << averageRF << endl ;
	
	return 0 ; 
	
}  
