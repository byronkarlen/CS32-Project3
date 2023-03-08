//
//  anagrams.cpp
//  CS32Project3
//
//  Created by Byron Karlen on 7/20/22.
//

#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>

using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


int lexiconHelper(istream &dictfile, string dict[], int i){
    if(i > MAXDICTWORDS)
        return MAXDICTWORDS; //It cuts the dictionary short if there are too many words
    
    if(!getline(dictfile, dict[i])) //Take the next line in 'dictfile' (if it exists) and store it in dict[i]
        return i; //If there is no such next line, return the number of words in 'dict'
    
    else
        return lexiconHelper(dictfile, dict, i+1); //iterate to the next element/line
}

//Puts each string in dictfile into the array dict. Returns the number of words read into dict. This number should not be larger than MAXDICTWORDS since that is the size of the array.
int lexiconBuilder(istream &dictfile, string dict[]){
    return lexiconHelper(dictfile, dict, 0);
}


//returns a boolean indictating whether 'word' was found in the 'arr'
bool inArr(string word, const string arr[], int currentIndex, const int& arrSize){
    if(currentIndex == arrSize)
        return false;
    else if(arr[currentIndex] == word)
        return true;
    else{
        currentIndex++;
        return inArr(word, arr, currentIndex, arrSize);
    }
}

//returns a string equal to 'str', but with the letter at 'index' removed
string removeLetter(const string& str, const int& index){
    string output;
    
    if(index == str.size() - 1) //If the index refers to the last character in the string
        output = str.substr(0, index);
    else
        output = str.substr(0, index) + str.substr(index+1);
    
    return output;
}

void theJumblerHelper(string prefix, string rest, string results[], int& numResults, const string dict[], const int& dictSize); //Declaration

//This method recursively calls itself and 'theJumblerHelper' to essentially carry out a loop that generates all possible anagrams. It has extra paramaters so that it can call 'theJumblerHelper'
void loop(int i, const int& stop, const string prefix, const string rest, string results[], int &count, const string dict[], const int& dictSize){
    
    if(i == stop){ //If the word has been completely iterated through, exit the current iteration of the function
        return;
    }
    
    string prefixOutput = prefix + rest[i]; //Remove the first letter from 'rest' and append it to 'prefix'
    string restOutput = removeLetter(rest, i); //Remove the first letter from 'rest'
    theJumblerHelper(prefixOutput, restOutput, results, count, dict, dictSize); //Let 'theJumblerHelper' check to see if an anagram has been completed and continue to help generate all possible anagrams
    
    loop(i+1, stop, prefix, rest, results, count, dict, dictSize); //Continue to generate all possible anagrams recursively
}

void theJumblerHelper(string prefix, string rest, string results[], int & numResults, const string dict[], const int& dictSize) {
    
    if(rest == ""){
        if(inArr(prefix, dict, 0, dictSize) && !inArr(prefix, results, 0, numResults)){
            results[numResults] = prefix;
            numResults++;
        }
    }
    
    //If there is still space in results for more anagrams
    if(numResults != MAXRESULTS)
        loop(0, rest.size(), prefix, rest, results, numResults, dict, dictSize);
    
}


//Puts all the possibilities of word which are found in dict into results. Returns the number of matched words found. This number should not be larger than MAXRESULTS since that is the size of the array. The size is the number of words inside the dict array. There should be no duplicates in results
int theJumbler(string word, const string dict[], int size, string results[]){

    int numResults = 0;
    
    theJumblerHelper("", word, results, numResults, dict, size);
    
    return numResults;
}


void divulgeSolutionHelper(const string results[], const int& size, int count){
    if(count >= size){ //If the end of the 'results' array has been reaches
        return;
    }
    else{
        cout << results[count] << endl; //Print the current element
        divulgeSolutionHelper(results, size, count+1); //Iterate to the next element
    }
}
//Displays size number of strings from results. The results can be printed in any order.
void divulgeSolutions(const string results[], int size){
    divulgeSolutionHelper(results, size, 0);
}
//
//
//int main()
//{
//    string results[MAXRESULTS];
//    string dict[MAXDICTWORDS];
//
//    ifstream dictfile;         // file containing the list of words
//    int nwords;                // number of words read from dictionary
//    string word;
//
//    dictfile.open("/Users/byronkarlen/Desktop/CS32Project3/CS32Project3/words.txt");
////    dictfile.open("words.txt");
//    if (!dictfile) {
//        cout << "File not found!" << endl;
//        return (1);
//    }
//    nwords = lexiconBuilder(dictfile, dict);
//
//    cout << "Please enter a string for an anagram: ";
//    cin >> word;
//
//    int numMatches = theJumbler(word, dict, nwords, results);
//    if (!numMatches)
//        cout << "No matches found" << endl;
//    else
//        divulgeSolutions(results, numMatches);
//
//    return 0; //KEEP THIS!!!
//}



#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
#include <cassert>
using namespace std;
 
 
int main()
{
 string results[MAXRESULTS];
 string dict[MAXDICTWORDS];
 ifstream dictfile;         // file containing the list of words
 int nwords;                // number of words read from dictionary
 string word;
 
//  dictfile.open("/Users/byronkarlen/Desktop/words.txt");
 dictfile.open("words.txt");
 if (!dictfile) {
  cout << "File not found!" << endl;
  return (1);
 }
 
 nwords = lexiconBuilder(dictfile, dict);
 
#ifdef TEST1
 word = "rat";
#endif
#ifdef TEST2
 word = "babe";
#endif
#ifdef TEST3
 word = "plane";
#endif
#ifdef TEST4
 word = "maiden";
#endif
#ifdef TEST5
 word = "arrogant";
#endif
 

 int numMatches = theJumbler(word, dict, nwords, results);
    
 if (!numMatches)
  cout << "No matches found" << endl;
 else
  divulgeSolutions(results, numMatches);
#ifdef TEST1
 assert(numMatches == 3 && (results[0] == "rat" ||
results[0] == "art"
  || results[0] == "tar"));
#endif
#ifdef TEST2
 assert(numMatches == 2 && (results[0] == "abbe" ||
results[0] == "babe"));
#endif
#ifdef TEST3
 assert(numMatches == 3 && (results[0] == "plane" ||
results[0] == "panel"
  || results[0] == "penal"));
#endif
#ifdef TEST4
 assert(numMatches == 2 && (results[0] == "maiden" ||
results[0] == "median"));
#endif
#ifdef TEST5
 assert(numMatches == 2 && (results[0] == "arrogant" ||
results[0] == "tarragon"));
#endif
 
 return 0;
}
