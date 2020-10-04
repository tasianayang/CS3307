//#define _GLIBCXX_USE_CXX11_ABI 0
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "CovidRecord.h"
using namespace std;

//helper function declarations
int parseStringToInt(string s);


int main(){
    //ask user to enter a file name
    cout << "Please provide a file name:";
    string fileName;
    cin >> fileName;

    //try to open the file provided by the user, return an error if the file cannot be oponed
    ifstream file;
    file.open(fileName, ifstream::in);
    if (!file.good())
    {
        cerr << "Error: cannot open the file \""  << fileName <<  "\".";
        exit(EXIT_FAILURE);
    }

    //prompt the user to choose how to sort the data
    cout << "How do you want to sort the data today?" << endl;
    cout << "1. By new confirmed cases" << endl;
    cout << "2. By new deaths" << endl;
    cout << "3. By new recovered cases" << endl;
    cout << "4. By total confirmed cases" << endl;
    cout << "5. By total deaths" << endl;
    cout << "6. By total recovered cases" << endl;
    cout <<"Please select an option from 1 to 6: ";
    string option;
    cin >> option;
    
    //check whether the user entered a valid option
    if (option.empty() || !isdigit(option[0]) || option.length() > 2){ 
        cerr << "Error: The option entered is not a valid option." << endl;
        exit(EXIT_FAILURE); 
    }

    //convert string "option" to an integer
        // stringstream stringStream(option);
        // int optionNumber = -1;
        // stringStream >> optionNumber;
    int optionNumber = parseStringToInt(option);
    //cerr << "______option chosen is: " << optionNumber << endl;
    
    //read data from the file & create vector 
    vector<CovidRecord> dataset;
    
    string line;
    getline(file,line);  //get rid of the first line (i.e. headers) in the file
    while(!file.eof()) {
        getline (file,line);
        line.erase(line.begin()); //remove the first char (i.e. ") in line
        cerr << line << endl;
        
        //tokenize data
        string data[11];
        for (int i=1; i<=10;i++){
            string delimiter; 
            if (i<=2 || i==7){
                delimiter ="\",\"";
            }
            else if (i==3 || i==8){
                delimiter ="\",";
            }
            else if (i==6){
                delimiter = ",\"";
            }
            else{
                delimiter = ",";
            }
            string token = line.substr(0, line.find(delimiter));
            data[i-1] = token;
            line.erase(0,line.find(delimiter) + delimiter.length());    //remove tokenized substring from original string
        }
        data[10] = line;

        //convert numbers in data to int 
        int newConfirmed = parseStringToInt (data[3]);
        int newDeaths = parseStringToInt (data[4]);
        int newRecovered = parseStringToInt (data[5]);
        int totalConfirmed = parseStringToInt (data[8]);
        int totalDeaths = parseStringToInt (data[9]);
        int totalRecovered = parseStringToInt (data[10]);
        string contry = data[0];
        string countryCode=data[1];
        string date= data[2];
        string slug= data[6];
        string premium = data[7];

        //create CovidRecord object
        CovidRecord covidRecord {contry,countryCode,date,newConfirmed,newDeaths,newRecovered,slug,premium,totalConfirmed,totalDeaths,totalRecovered};
        // CovidRecord covidRecord(data[0],data[1],data[2],newConfirmed,newDeaths,newRecovered,data[6],data[7],totalConfirmed,totalDeaths,totalRecovered);

        //add CovidRecord to vector
        //dataset.push_back(covidRecord);
    }
    
    //close the file
    file.close();
    
    //sort data
    switch (optionNumber)
    {
    case 1:
        cout << "1 is selected" << endl;
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    case 6:
        /* code */
        break;
    default:
        cerr << "Error: The option entered is out of bound.";
        exit(EXIT_FAILURE);
    }  
} 

//helper function definitions
//parseStringToInt() parses a string representation of a number to int 
int parseStringToInt(string s){
    stringstream stringStream(s);
    int num;
    stringStream >> num;
    return num;
}

