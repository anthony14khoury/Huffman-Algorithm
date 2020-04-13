#include "frequency_table.h"

//Constructors
frequency_table::frequency_table()
{
    this->frequencyTable["None"] = -100000;
}
frequency_table::frequency_table(unordered_map<string, int> frequency)
{
    this->frequencyTable = frequency;
}



// Given Functions

int frequency_table::intToAscii(int number)
{
    return '0' + number;
}

frequency_table::frequency_table(const std::string& file_name)
{
    // Constructs a frequency_table object. 
    // This should read the file passed and count and store the frequency of each ASCII character.
    // Throws a std::runtime_error if the file is not found or cannot be opened.

    vector<string> listOfCharacters;

    ifstream file;
    file.open(file_name);  
    if (file.is_open())
    {       
        char c;        
        while(file.get(c))
        {
            // cout << c << " ";
            string temp = "";
            temp.push_back(c);
            listOfCharacters.push_back(temp);
        }
    }
    else
    {
        throw std::runtime_error("");
    }

    // Instantiating all values to 0
    for (int i = 0; i < 128; i++)
    {
        int temp = intToAscii(i);

        string tempString = "";
        tempString.push_back(temp);

        frequencyTable.insert({ tempString, 0 });
    }

    // Increments the value of the key (creating the table)
    for (const auto& i : listOfCharacters)
    {
        ++frequencyTable[i];
    }
}


 

frequency_table::~frequency_table()
{
    //Destructs the frequency_table object. Should free any dynamically allocated memory. 
    //Can be left empty if no memory is dynamically allocated for the object

}

int frequency_table::get_frequency(char c) const
{
    //Returns the frequency of the character c in the file

    // Iterate through the map. If the character is found, return that value. If not, return 0.

    string charInput = "";
    charInput.push_back(c);

    if (frequencyTable.find(charInput) == frequencyTable.end())
    {
        return 0;
    }
    else
    {
        int temp = frequencyTable.at(charInput);
        return temp;
    }
}