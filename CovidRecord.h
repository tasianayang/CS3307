// Author: Xiaoxuan Yang
// Description: This file is header file of CovidRecord, and it contains the data memebesr, fucntion definitions of CovidRecord.
// Date: Octber 5, 2020

#ifndef COVID_RECORD_H
#define COVID_RECORD_H
#include <string>
using namespace std;

class CovidRecord{
    private:
        string country, countryCode, date;
        int newConfirmed, newDeath, newRecovered;
        string premium, slug;
        int totalConfirmed, totalDeaths, totalRecovered;
    public:
        //contructor
        CovidRecord(string temp_country, string temp_countryCode, string temp_date, int temp_newConfirmed, int temp_newDeath, int temp_newRecovered, string temp_premium, string temp_slug, int temp_totalConfirmed, int temp_totalDeaths, int temp_totalRecovered); 
        
        //getter methods
        string getCountry();
        string getCountryCode();
        int getNewConfirmed();
        int getNewDeath();
        int getNewRecovered();
        int getTotalConfirmed();
        int getTotalDeaths();
        int getTotalRecovered();

        //destructor
        ~CovidRecord(){
        }
};

#endif
