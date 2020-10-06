// Author: Xiaoxuan Yang
// Description: This file is teh code file of CovidREcord, and it contains the function definition of CovidRecord.
// Date: Octber 5, 2020

#include "CovidRecord.h"

//constructor
CovidRecord::CovidRecord(string temp_country, string temp_countryCode, string temp_date, int temp_newConfirmed, int temp_newDeath, int temp_newRecovered, string temp_premium, string temp_slug, int temp_totalConfirmed, int temp_totalDeaths, int temp_totalRecovered)
    : country(temp_country), countryCode(temp_countryCode), date(temp_date), newConfirmed(temp_newConfirmed), newDeath(temp_newDeath), newRecovered(temp_newRecovered), premium(temp_premium), slug(temp_slug), totalConfirmed(temp_totalConfirmed), totalDeaths(temp_totalDeaths), totalRecovered(temp_totalRecovered)
{}

//getter method for country
string CovidRecord::getCountry(){
    return this->country;
}

//getter method for countryCode
string CovidRecord::getCountryCode(){
    return this->countryCode;
}

//getter method for newConfirmed
int CovidRecord::getNewConfirmed(){
    return this->newConfirmed;
}

//getter method for newDeath
int CovidRecord::getNewDeath(){
    return this->newDeath;
}

//getter method for newRecovered
int CovidRecord::getNewRecovered(){
    return this->newRecovered;
}

//getter method for totalConfirmed
int CovidRecord::getTotalConfirmed(){
    return this->totalConfirmed;
}

//getter method for totalDeaths
int CovidRecord::getTotalDeaths(){
    return this->totalDeaths;
}

//getter method for totalRecovered
int CovidRecord::getTotalRecovered(){
    return this->totalRecovered;
}
