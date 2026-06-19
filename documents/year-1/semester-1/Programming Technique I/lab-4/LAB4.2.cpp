#include<iostream>
#include<cctype>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;

double calculateKeywordPercentage(char[], int);

int main() {
    const int MAX_SIZE = 999;
    int wordCount = 0, keywordCount;
    char userInput[MAX_SIZE];
    double percentage ;
    
    ifstream inFile ;
    inFile.open("input2.txt");
    ofstream outFile ;
    outFile.open("output2.txt") ;
    
    if(outFile){
    	cout << "Results written to 'output.txt'" << endl;
	}
	
    inFile.getline(userInput, MAX_SIZE);

	outFile << "Input: " << endl ;
	
    for (int i = 0; userInput[i] != '\0'; i++) {
    	outFile << userInput[i]  ;
        if (isspace(userInput[i])) {
            wordCount++;
        }
    }
    percentage = calculateKeywordPercentage(userInput, wordCount+1);
    keywordCount = percentage/100 * (wordCount+1) ;
	outFile << "\n\nTotal words: " << wordCount + 1 << endl ;
	outFile << "Total keywords: " << keywordCount << endl ;
    outFile << "Percentage of lines containing 'data': " << fixed << setprecision(2) << percentage << "%" << endl ;

    return 0;
}

double calculateKeywordPercentage(char input[], int wc) {
    const char target[] = "data";
    int targetCount = 1;
    char *tar = strstr(input, target) ;

    while(tar != '\0'){
    	tar += 4 ;
    	tar = strstr(tar, target) ;
    	targetCount++ ;
	}
    double percentage = static_cast<double>(targetCount) / wc * 100.0;
    
    return percentage ;
}

