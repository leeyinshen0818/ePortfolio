#include<iostream>
#include<cctype>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;

double calculateKeywordPercentage(const char *, int);

int main() {
    const int MAX_SIZE = 999;
    int wordCount = 0, keywordCount;
    char userInput[MAX_SIZE];
    double percentage ;
    char *userIn ;
    userIn = new char[MAX_SIZE] ;
    
    ifstream inFile ;
    inFile.open("input2.txt");
    ofstream outFile ;
    outFile.open("output2.txt") ;
    
    if(outFile){
    	cout << "Results written to 'output.txt'" << endl;
	}
	
    inFile.getline(userIn, MAX_SIZE);

	outFile << "Input: " << endl ;
	
    for (int i = 0; userIn[i] != '\0'; i++) {
    	outFile << userIn[i]  ;
        if (isspace(userIn[i])) {
            wordCount++;
        }
    }
    percentage = calculateKeywordPercentage(userIn, wordCount+1);
    keywordCount = percentage/100 * (wordCount+1) ;
	outFile << "\n\nTotal words: " << wordCount+1 << endl ;
	outFile << "Total keywords: " << keywordCount << endl ;
    outFile << "Percentage of lines containing 'data': " << fixed << setprecision(2) << percentage << "%" << endl ;

    return 0;
}

double calculateKeywordPercentage(const char *input, int wc) {
    const char target[] = "data";
    int targetCount = 1;
    char *tar = strstr(input, target) ;
    double percentage ;

    while(tar != '\0'){
    	tar += 4 ;
    	tar = strstr(tar, target) ;
    	targetCount++ ;
	}
    percentage = static_cast<double>(targetCount) / wc * 100.0;
    
    return percentage ;
}

