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
        //CovidRecord (string country, string countryCode, string date, int newConfirmed, int newDeath, int newRecovered, string premium, string slug, int totalConfirmed, int totalDeaths, int totalRecovered); 
        CovidRecord(string temp_country, string temp_countryCode, string temp_date, int temp_newConfirmed, int temp_newDeath, int temp_newRecovered, string temp_premium, string temp_slug, int temp_totalConfirmed, int temp_totalDeaths, int temp_totalRecovered); 
        
        //getter methods
        string getCountry();
        string getCountryCode();
        // string getDate();
        int getNewConfirmed();
        int getNewDeath();
        int getNewRecovered();
        // string getSlug();
        int getTotalConfirmed();
        int getTotalDeaths();
        int getTotalRecovered();

        //destructor
        ~CovidRecord(){
        }
};

#endif