//wie jason funktioniert wie standartlib funktioniert 
// get opt long ? 

#include <jsoncpp/json/json.h>
#include <jsoncpp/json/value.h>  //This library is used for interacting with JSON file
#include <fstream>  // This library is used for reading and writing data to the files
#include <string>    // This library is used to store text
#include <iostream>

int main(){
    // Using fstream to get the file pointer in file
    std::ifstream file ("/jsonfiles/nurTest.json");
    Json::Value actualJson;
    Json::Reader reader;

    //reader gibt an perser dieser überprüft den Programmtext und zeigt potenzielle Fehler auf
    reader.parse(file, actualJson);

    std::cout << "Alle Daten: \n" << actualJson << std::endl; 

    std::cout << "Name: \n" << actualJson["name"] << std::endl; 

    return 0;

}
