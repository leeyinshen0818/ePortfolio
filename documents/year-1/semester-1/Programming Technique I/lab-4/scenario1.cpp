#include<iostream>
#include<cctype>
#include<cstring>
#include<iomanip>
using namespace std;

double calculateKeywordPercentage(const char[], int);

int main() {
    const int MAX_SIZE = 999;
    int wordCount = 0, keywordCount;
    char userInput[MAX_SIZE];
    double percentage ;
	
	cout << "Enter the input (up to 999 characters, end with an empty line): " << endl ;
    cin.getline(userInput, MAX_SIZE);

	cout << "Input: " << endl ;
	
    for (int i = 0; userInput[i] != '\0'; i++) {
    	cout << userInput[i]  ;
        if (isspace(userInput[i])) {
            wordCount++;
        }
    }
    percentage = calculateKeywordPercentage(userInput, wordCount+1);
    keywordCount = percentage/100 * (wordCount+1) ;
	cout << "\n\nTotal words: " << wordCount + 1<< endl ;
	cout << "Total keywords: " << keywordCount << endl ;
    cout << "Percentage of lines containing 'data': " << fixed << setprecision(2) << percentage << "%" << endl ;

    return 0;
}

double calculateKeywordPercentage(const char input[], int wc) {
    const char target[] = "data";
    int targetCount = 1;
    char *tar = strstr(input, target) ;
    double percentage;

    while(tar != '\0'){
    	tar += 4 ;
    	tar = strstr(tar, target) ;
    	targetCount++ ;
	}
    percentage = static_cast<double>(targetCount) / wc * 100.0;
    
    return percentage ;
}

