// Author: Xiaoxuan Yang
// Description: This file is header file of CovidRecord, and it contains the data memebesr, fucntion definitions of CovidRecord.
// Date: Octber 5, 2020

#ifndef COVID_RECORD_H
#define COVID_RECORD_H
#include <string>

class CovidRecord{
    private:
        std::string country, countryCode, date;
        int newConfirmed, newDeath, newRecovered;
        std::string premium, slug;
        int totalConfirmed, totalDeaths, totalRecovered;
    public:
        //contructor
        CovidRecord(std::string temp_country, std::string temp_countryCode, std::string temp_date, int temp_newConfirmed, int temp_newDeath, int temp_newRecovered, std::string temp_premium, std::string temp_slug, int temp_totalConfirmed, int temp_totalDeaths, int temp_totalRecovered); 
        
        //getter methods
        std::string getCountry();
        std::string getCountryCode();
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
