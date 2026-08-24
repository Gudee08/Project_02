#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <cassert>

using namespace std;

// assume maximum number of clients is 100
int SIZE = 100;
// creating a class
class Movie
{
public:
    //Declaring public variables
    string surname, name, title, type, seat, REF;
    double price;
};
// counting number of lines in the file function
int countlines (string filename)
{
    ifstream readFile (filename);
    string line;
    int lines = 0;

    while (getline(readFile, line))
    {
        lines++;
    }
    readFile.close();
    return lines;
}
//counting number of words in the file function
int countwords (string filename)
{
    ifstream readFile (filename);

     char ch;
     int words = 0;
     bool insideword =false;
     while (readFile.get(ch))
     {
         //checking if the character is part of the word
         if (isalnum(ch))
        {
         if (!insideword)
         {
             words++;
             insideword = true;
         }
        }
          else
         {
          insideword = false;
         }
     }
     readFile.close();
     return words;
}
// function to search for a character
char getCharacter()
{
    char ch;
    cout << "Enter a character your are searching: " << endl;
    cin >> ch;
    return ch;
}
// function to count how many times a character is
int countcharacter ( string filename, char searchchar)
{
    ifstream readFile (filename);
    char ch;
    int Count =0;

    while (readFile.get(ch))
    {
        if (tolower(ch)== tolower(searchchar))
        {
            Count++;
        }
    }
    readFile.close();
    return Count;
}
// function to replace first two digits of REf number
void replaceREF (Movie client[],int Count)
{
    for ( int i=0; i < Count; i++)
    {
        client[i].REF.replace(0,2, "99");
    }
}

// function to count the number of movie types
void countMovietype( Movie client[], int Count)
{
    int Action =0;
    int Horror =0;
    int Animation = 0;

    for(int i =0; i< Count; i++)
    {
        if (client[i].type == "Action")
        {
            Action++;
        }
            else if (client[i].type == "Horror")
            {
                Horror++;
            }
            else if (client[i].type == "Animation")
            {
                Animation++;
            }

    }
    cout << "Movie type counts: "<< endl;
    cout << "Action: " << Action << endl;
    cout << "Horror: " << Horror << endl;
    cout << "Animation: " << Animation << endl;
}
// function to count total amount of each movie type
void totalMovieAmount ( Movie client[], int Count)
{
    double ActionTotal =0;
    double HorrorTotal =0;
    double AnimationTotal = 0;
    for (int i=0; i<Count; i++)
    {
       if (client[i].type == "Action")
       {
           ActionTotal += client[i].price;
       }
        else if (client[i].type == "Horror")
            {
                HorrorTotal += client[i].price;
            }
        else if (client[i].type == "Animation")
        {
            AnimationTotal += client[i].price;
        }
    }

    cout << "Total amount per movie type:" << endl;
    cout << "Action: " << ActionTotal << endl;
    cout << "Horror: " << HorrorTotal << endl;
    cout << "Animation: " << AnimationTotal << endl;

}
// function to calculate the grand total
double grandtotal (Movie client[], int Count)
{
    double total =0;
    for (int i=0; i< Count; i++)
    {
        total += client[i].price;
    }
    return total;
}
// Function to sort records by surname in descending order
void sortSurname(Movie client[], int Count)
{
    Movie temp;
    for (int i = 0; i < Count - 1; i++)
    {
        for (int j = i + 1; j < Count; j++)
        {
            if (client[i].surname < client[j].surname)
            {
                temp = client[i];
                client[i] = client[j];
                client[j] = temp;
            }
        }
    }
}
// Function to write the report to the output file
void writeReport(Movie client[], int Count, string outputFile)
{
    ofstream writeFile(outputFile);

    if (!writeFile)
    {
        cout << "Error creating output file." << endl;
        return;
    }

    writeFile << "MOVIE REPORT" << endl;
    writeFile << "==============================" << endl;

    for (int i = 0; i < Count; i++)
    {
        writeFile << client[i].surname << "\t"
                  << client[i].name << "\t"
                  << client[i].type << "\t"
                  << client[i].REF << endl;
    }

    writeFile.close();
    cout << "Report written successfully." << endl;
}
int main() {
   //object of movie in array
    Movie client [SIZE];

    // declaring variables for fstreams
    ifstream readFile; // read data from file stream
    ofstream writeFile; // write output to file stream
string inputfile, outputfile;

    //prompt user to input file name
    cout << "Enter input file name: " << endl;
    cin >> inputfile;

// open file to process data and validate
readFile.open (inputfile);
 if (!readFile)
 {
     cout << "Error; file not found!" << endl;
     return 1;
 }
 // loop to search for character
 char answer;
    do
    {
        char letter = getCharacter();
        cout << "The character: '" << letter << "'  appears " << countcharacter (inputfile, letter) << "' times." << endl;
        cout << "Do you want to search another character? (y/n): ";
        cin >> answer;

        // termination of program if answer is not y/n
        assert( answer == 'y' || answer == 'Y' || answer == 'n' || answer== 'N');

    }
    while (answer == 'y' || answer == 'Y');
   // prompt user to input output file name
    cout << "Enter output file name: " << endl;
    cin >> outputfile;

    // open file to write on it and validate
 writeFile.open (outputfile);
if (!writeFile)
{
    cout << "Error; output file not created!" << endl;
    return 1;
}
// calling counting functions
 cout << "Number of lines: " << countlines (inputfile) << endl;
 cout << "Number of words: " << countwords (inputfile) << endl;

// declaring count and comma
int Count =0;
char comma;
 // read records from file
 while (getline(readFile, client[Count].surname, ','))
 {
     readFile.ignore(); // skip space
     getline(readFile, client[Count].name, ',');
     readFile.ignore();
       getline(readFile, client[Count].title, ',');
     readFile.ignore();
       getline(readFile, client[Count].type, ',');
     readFile.ignore();
       getline(readFile, client[Count].seat, ',');
     readFile.ignore();

//THIS PIECE OF CODE IS FOR DEBUGGING PURPOSE
    // cout << "seat; " << client[Count].seat << endl;
    /*readFile >> client[Count].price;
    readFile >> comma;
    readFile.ignore();
        getline(readFile, client[Count].REF);
     */

     string price;
     getline(readFile, price, ',');
     client[Count].price = stod(price);
     if (readFile.fail())
     {
         cout <<"reading price failed" << endl;
     }
     readFile.ignore();
     getline(readFile, client[Count].REF);

     // THIS PIECE OF CODE IS FOR DEBUGGING PURPOSE
    /* cout << "price is: " << client[Count].price << endl;
     cout << "reference is: " << client[Count].REF << endl; */

     Count++;
 }
 cout << Count << " records successfully loaded" << endl;
// calling functions
replaceREF (client, Count);
countMovietype( client, Count);
totalMovieAmount( client, Count);
 // displaying grand total
 cout << "the grand total is:  R" << grandtotal(client , Count) << endl;

 readFile.close();
 writeFile.close();
 int choice;

do
{
    cout << "\n========== MENU ==========" << endl;
    cout << "1. Count lines" << endl;
    cout << "2. Count words" << endl;
    cout << "3. Count movie types" << endl;
    cout << "4. Calculate totals" << endl;
    cout << "5. Sort records and write report" << endl;
    cout << "6. Exit" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
            cout << "Number of lines: " << countlines(inputfile) << endl;
            break;

        case 2:
            cout << "Number of words: " << countwords(inputfile) << endl;
            break;

        case 3:
            countMovietype(client, Count);
            break;

        case 4:
            totalMovieAmount(client, Count);

            cout << "\nGrand Total: R"<< grandtotal(client, Count) << endl;
            break;

        case 5:
            sortSurname(client, Count);
            writeReport(client, Count, outputfile);
            break;

        case 6:
            cout << "Program terminated." << endl;
            break;

        default:
            cout << "Invalid choice." << endl;
    }

} while (choice != 6);

return 0;
}

