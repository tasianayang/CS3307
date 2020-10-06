#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "CovidRecord.h"
using namespace std;

//helper function declarations
int parseStringToInt(string s);
bool compareByNewConfirmed (CovidRecord r1, CovidRecord r2);
bool compareByNewDeaths (CovidRecord r1, CovidRecord r2);
bool compareByNewRecovered (CovidRecord r1, CovidRecord r2);
bool compareByTotalConfirmed (CovidRecord r1, CovidRecord r2);
bool compareByTotalDeaths (CovidRecord r1, CovidRecord r2);
bool compareByTotalRecovered (CovidRecord r1, CovidRecord r2);
void generateGraph (vector<CovidRecord> vec, int optionNumber, int orderNumber);
int getBaseNumberForGraph (int first, int last, int orderNumber);

//main function
int main(){
    //ask user to enter a file name
    cout << "Please provide a file name:";
    string fileName;
    cin >> fileName;
    cout << endl;

    //try to open the file provided by the user, return an error if the file cannot be oponed
    ifstream file;
    file.open(fileName, ifstream::in);
    if (!file.good())
    {
        cerr << "Error: cannot open the file \""  << fileName <<  "\".";
        exit(EXIT_FAILURE);
    }

    //read the first line to determine whether the file is the right file
    string line;
    getline(file,line);  //read the first line (i.e. headers) in the file 
    if (line.find("\"NewConfirmed\",\"NewDeaths\",") == std::string::npos){
        cerr << "Error: wrong file!" << endl;
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
    cout << endl;
    
    //check whether the user entered a valid option
    if (option.empty() || !isdigit(option[0]) || option.length() > 2){ 
        cerr << "Error: The option entered is not a valid option." << endl;
        exit(EXIT_FAILURE); 
    }

    //convert string "option" to an integer
    int optionNumber = parseStringToInt(option);

    //prompt the user to choose the order
    cout << "Do you want to sort the data in ascending order or descending order?" <<endl;
    cout << "Please enter 1 for ascending order or 2 for descending order: ";
    string order;
    cin >> order;
    cout << endl;

    //check whether the user entered a valid order
    if (order.empty() || !isdigit(order[0]) || order.length() > 2){ 
        cerr << "Error: The choice entered is not valid." << endl;
        exit(EXIT_FAILURE); 
    }

    //convert string "order" to an integer
    int orderNumber = parseStringToInt(order);
    if (orderNumber> 2 || orderNumber < 1){
        cerr << "Error: The choice entered is not valid." << endl;
        exit(EXIT_FAILURE); 
    }
    
    //read data from the file & create vector 
    vector<CovidRecord> dataset;
    
    while(!file.eof()) {
        getline (file,line);
        
        if (line.empty()){      //in case the file has empty line at the end of the file
            break;
        }
        line.erase(line.begin()); //remove the first char (i.e. the first quotation mark) in line
        
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
            line.erase(0,line.find(delimiter) + delimiter.length());    //remove substring that is already tokenized from original string
        }
        data[10] = line;

        //convert string to int 
        int newConfirmed = parseStringToInt (data[3]);
        int newDeaths = parseStringToInt (data[4]);
        int newRecovered = parseStringToInt (data[5]);
        int totalConfirmed = parseStringToInt (data[8]);
        int totalDeaths = parseStringToInt (data[9]);
        int totalRecovered = parseStringToInt (data[10]);

        //create CovidRecord object
        CovidRecord covidRecord(data[0],data[1],data[2],newConfirmed,newDeaths,newRecovered,data[6],data[7],totalConfirmed,totalDeaths,totalRecovered);

        //add CovidRecord to vector
        dataset.push_back(covidRecord);
    }
    
    //close the file
    file.close();
    
    //sort data
    switch (optionNumber)
    {
    case 1:     //sort data by newConfirmed
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByNewConfirmed);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByNewConfirmed);
        }
        for (int i=0; i<10;i++){
            cerr << dataset[i].getNewConfirmed() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    case 2:     //sort data by newDeaths
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByNewDeaths);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByNewDeaths);
        }
        for (int i=0;i<10;i++){
            cerr << dataset[i].getNewDeath() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    case 3:     //sort data by newRecovered
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByNewRecovered);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByNewRecovered);
        }
        for (int i=0;i<10;i++){
            cerr << dataset[i].getNewRecovered() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    case 4:     //sort data by totalConfirmed
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByTotalConfirmed);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByTotalConfirmed);
        }
        for (int i=0;i<10;i++){
            cerr << dataset[i].getTotalConfirmed() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    case 5:     //sort data by totalDeaths
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByTotalDeaths);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByTotalDeaths);
        }
        for (int i=0;i<10;i++){
            cerr << dataset[i].getTotalDeaths() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    case 6:     //sort data by totalRecovered
        if (orderNumber == 2){   //descending order
            sort(dataset.begin(),dataset.end(),compareByTotalRecovered);
        }
        else {   //ascending order
            sort(dataset.rbegin(),dataset.rend(),compareByTotalRecovered);
        }
        for (int i=0;i<10;i++){
            cerr << dataset[i].getTotalRecovered() << ": " <<dataset[i].getCountry() << endl;
        }
        break;
    default:
        cerr << "Error: The option entered is out of bound.";
        exit(EXIT_FAILURE);
    }  

    cout << endl;

    //print graph
    generateGraph (dataset, optionNumber, orderNumber);
} 

//helper function definitions
//parseStringToInt() parses a string representation of a number to int 
int parseStringToInt(string s){
    stringstream stringStream(s);
    int num;
    stringStream >> num;
    return num;
}

//compare newConfirmed for the sort() funtion
bool compareByNewConfirmed (CovidRecord r1, CovidRecord r2){ 
    return r1.getNewConfirmed() > r2.getNewConfirmed();
}

//compare newDeaths for the sort() funtion
bool compareByNewDeaths (CovidRecord r1, CovidRecord r2){
    return r1.getNewDeath() > r2.getNewDeath();
}

//compare newRecovered for the sort() funtion
bool compareByNewRecovered (CovidRecord r1, CovidRecord r2){
    return r1.getNewRecovered() > r2.getNewRecovered();
}

//compare totalConfirmed for the sort() funtion
bool compareByTotalConfirmed (CovidRecord r1, CovidRecord r2){
    return r1.getTotalConfirmed() > r2.getTotalConfirmed();
}

//compare totalDeaths for the sort() funtion
bool compareByTotalDeaths (CovidRecord r1, CovidRecord r2){
    return r1.getTotalDeaths() > r2.getTotalDeaths();
}

//compare totalRecovered for the sort() funtion
bool compareByTotalRecovered (CovidRecord r1, CovidRecord r2){
    return r1.getTotalRecovered() > r2.getTotalRecovered();
}

//print data after sorting 
//parameter option is the attribute the user want to see:1 represents newConfirmed, 2 represents newDeaths, 3 represents newRecovered, 
    //4 represents totalConfirmed, 5 represents totalDeaths, 6 represents totalRecovered 
void generateGraph (vector<CovidRecord> vec, int optionNumber, int orderNumber){
    int base;
    switch (optionNumber)
    {
    case 1:     //show data by newConfirmed
        base = getBaseNumberForGraph(vec[0].getNewConfirmed(),vec[9].getNewConfirmed(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0  && vec[i].getNewConfirmed() != 0){
                int j;
                for (j = 1; j<=vec[i].getNewConfirmed()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "New Confirmed Cases; each # is approx. " << base << " cases";
        break;
    case 2:     //show data by newDeaths
        base = getBaseNumberForGraph(vec[0].getNewDeath(),vec[9].getNewDeath(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0  && vec[i].getNewDeath() != 0){
                int j;
                for (j = 1; j<=vec[i].getNewDeath()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "New Death Cases; each # is approx. " << base << " cases";
        break;
    case 3:     //show data by newRecovered
        base = getBaseNumberForGraph(vec[0].getNewRecovered(),vec[9].getNewRecovered(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0  && vec[i].getNewRecovered() != 0){
                int j;
                for (j = 1; j<=vec[i].getNewRecovered()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "New Recovered Cases; each # is approx. " << base << " cases";
        break;
    case 4:     //show data by totalConfirmed
        base = getBaseNumberForGraph(vec[0].getTotalConfirmed(),vec[9].getTotalConfirmed(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0  && vec[i].getTotalConfirmed() != 0){
                int j;
                for (j = 1; j<=vec[i].getTotalConfirmed()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "Totoal Confirmed Cases; each # is approx. " << base << " cases";
        break;
    case 5:     //show data by totalDeaths
        base = getBaseNumberForGraph(vec[0].getTotalDeaths(),vec[9].getTotalDeaths(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0  && vec[i].getTotalDeaths() != 0){
                int j;
                for (j = 1; j<=vec[i].getTotalDeaths()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "Total Death Cases; each # is approx. " << base << " cases";
        break;
    case 6:     //show data by totalRecovered
        base = getBaseNumberForGraph(vec[0].getTotalRecovered(),vec[9].getTotalRecovered(),orderNumber);
        for (int i =0;i<10;i++){
            cout << vec[i].getCountryCode() << " | ";
            if (base != 0 && vec[i].getTotalRecovered() != 0){
                int j;
                for (j = 1; j<=vec[i].getTotalRecovered()/base;j++){      //print #
                    cout << "#";
                }
                cerr <<"  "<< j-1;
            }
            cout << endl;
        }
        cout << "--------------------------------------------------------------------" << endl;
        cout << "Total Recovered Cases; each # is approx. " << base << " cases";
        break;
    default:
        cerr << "Unexpected Error occured when generating the graph.";
        exit(EXIT_FAILURE);
    }  
}

//calculate how many cases a # represents based on the order of the data
//parameter: first represent the first memebr of the vector; last represents the 9th member of the vector
int getBaseNumberForGraph (int first, int last, int orderNumber){
    if (orderNumber == 1){      //ascending order
        if (last == 0){
            return 0;
        }else{
            return 3;
        }
    }
    else{   //descending order
        return last/4;
    }
}