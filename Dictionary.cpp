#ifndef DICTIONARY_C
#define DICTIONARY_C

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include "Dictionary.h"

bool Dictionary::failure = false;//set constant failure to false
bool Dictionary::success = true;//set constant success to true
//default constructor with no parameters
Dictionary::Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)//initialize const variables maxWordsIn Dict to 10000 and maxWordsPerFile to 100
{
  totalWordsInDict = 0;//initializes totalWordsInDict to 0
  for(int i=0;i<26;i++)//cycles through 26 times which is equal to size of english alphabet
       {
         numOfWordsInFile[i] = 0;//Initializes all elements in array numOfWordsInFile to 0
       }
}
//2nd constructor that takes dictMaxWords and fileMaxWords as parameters
Dictionary::Dictionary(int dictMaxWords, int fileMaxWords):maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)//sets const variables to parameters:
{//sets maxWordsInDict to dictMaxWords and maxWordsPerFile to fileMaxWords
  // This routine sets the following values to the following attributes
     totalWordsInDict = 0;
     for(int i=0;i<26;i++)//cycles through 26 times which is equal to size of english alphabet
       {
         numOfWordsInFile[i]=0;//Initializes all elements in array numOfWordsInFile to 0
       }
}
//function that Adds a word to the dictionary
bool Dictionary::AddAWord(string word)//takes string parameter named word
{
  if(totalWordsInDict>=maxWordsInDict)//if the words are already over the limit than no more words can be added.
    return Dictionary::failure;//returns failure(false) if this is the case

  char ch = word[0];//take first character from word
  ch=toupper(ch);//capitalize the first character in word
  int index=ch-'A';//get the index of file relative to numOfWordsInFile
  string fileName=" .txt";//set fileName with .txt extenstion
  fileName[0]=ch;//set FileName's 1st character to ch which is the corresponding file name in the dictionary
  if(numOfWordsInFile[index]>=maxWordsPerFile)//if the file has too many words in it return failure(false)
    return Dictionary::failure;//return failure(false)
  bool found=SearchForWord(word);//set bool found variable to result of SearchForWord call which returns a bool
  if(found==Dictionary::failure)//if word is not found in the dictionary proceed to add it
    {
      ofstream fout;//declare outfile fout
      fout.open(fileName.data(), ios::app);//open fout and append it
      fout<<word<<" ";//print word and a space to the outfile
      totalWordsInDict++;//increment the totalWordsInDict since a word has been added
      numOfWordsInFile[index]++;//increment the integer element with subscript index of numOfWordsInFile array
      return Dictionary::success;//return success or true
    }
  return Dictionary::failure;//if nothing is added return false
}

//function that returns bool and deletes a word if successful or not
bool Dictionary::DeleteAWord(string word)//takes string parameter called word
{
    int numAdj=0;//set integer that will be used to measure length of output
  bool found = SearchForWord(word);//set bool found variable to result of SearchForWord call which returns a bool
  if(!found)//if found returns false
    return Dictionary::failure;//return failure(false)
  char ch = word[0];//take first character from word
  ch=toupper(ch);//capitalize the first character in word
  int index=ch-'A';//get the index of file relative to numOfWordsInFile
  string fileName=" .txt";//set fileName with .txt extenstion
  fileName[0]=ch;//set FileName's 1st character to ch which is the corresponding file name in the dictionary
  ifstream fin;//declare infile fin
  fin.open(fileName.data());//open infile fin
  string fileWord;//declare fileWord which will be used to store word from fin (inFile)
  fin>>fileWord;//stores string from infile(fin) into fileWord
  vector<string>fileContents;//declares vector that will contain the contents of infile(fin) called fileContents
  while(fin)//while the infile(fin) is being read
  {
    if(fileWord!=word)//if the fileWord is not equal to the word that is trying to be deleted
      {
        fileContents.push_back(fileWord);//add the fileWord (word from infile(fin)) to back of vector fileContents via push_back
      }
    else if(fileWord==word)//if the fileWord is equal to the word that is trying to be deleted
      {
        totalWordsInDict--;//decrement the totalWordsInDict since a word has been deleted
        numOfWordsInFile[index]--;//decrement the integer element with subscript index of numOfWordsInFile array
      }
    fin>>fileWord;//stores string from infile(fin) into fileWord
  }
  remove(fileName.data());//removes the file while deleting everything in it
  //don't worry all of the contents that shouldn't be deleted are stored in fileContents
  for(unsigned int i=0; i<fileContents.size();i++)//cycle through fileContents vector
    {
      numAdj++;//increment the integer that will be used to measure length of output
      //25 has been determined to be appropriate distance before extra line is added
      if(numAdj>=25)//if numAdj is larger than 25 than an extra line is added to make sure horizontal length of output isn't too ridiculous
        {
          AddAWord("\n");//extra line is added to the output
          numAdj=0;//resets numAdj for reusability
        }
      AddAWord(fileContents[i]);//adds word from fileContents to appropriate file by calling AddAWord function with fileContents[i] as a parameter
    }
  return Dictionary::success;//returns success(true)
}

//function that searches for a word and returns bool which determines success
bool Dictionary::SearchForWord(string word)//takes string parameter called word
{
  char ch = word[0];//sets ch to first character from word
  ch=toupper(ch);//capitalize the first character in word
  string fileName="?.txt";//set fileName with .txt extenstion
  fileName[0]=ch;//set FileName's 1st character to ch which is the corresponding file name in the dictionary
  ifstream fin;//declare infile(fin)
  fin.open(fileName.data());//open infile(fin)
  string fileWord;//declare fileWord which will be used to store word from fin (inFile)
  fin>>fileWord;//stores string from infile(fin) into fileWord

  while(fin)//while the infile(fin) is being read
    {
      if(fileWord==word)//if fileWord equals the word being searched for
        return Dictionary::success;//return success(true)
      fin>>fileWord;//stores string from infile(fin) into fileWord
    }
  return Dictionary::failure;//returns failure (false) if it couldn't be found
}
//function that prints a file in the dictionary in parameters
bool Dictionary::PrintAFileInDict(string fileName)//takes string parameter called fileName
{
  ifstream fin;//declare infile(fin)
  fin.open(fileName.data());//opens infile (fin)
  if(!fin)//if infile(fin) could not be opened
    {
      cout<<"Error Printing";//output Error Printing to screen
      return Dictionary::failure;//return failure (false)
    }
  string fileWord;//declare fileWord which will be used to store word from fin (inFile)
  fin>>fileWord;//stores string from infile(fin) into fileWord
  int count=1;//initialize count to assure that only 5 words are printed per line
  while(fin)//while the infile(fin) is being read
    {
      if(count>=5)//if count is greater than or equal to 5
        cout<<endl;//output a new line to the screen
      cout<<fileWord<<" ";//output fileWord and space to screen
      fin>>fileWord;//stores string from infile(fin) into fileWord
    }
  return Dictionary::success;//return success(true)
}
//function that checks spelling of all words in file
bool Dictionary::SpellChecking(string fileName)//takes string parameter called fileName
{
  ifstream fin;//declare infile(fin)
  fin.open(fileName.data());//opens infile (fin)
  if(!fin)//if infile(fin) could not be opened
    {
      cout<<"Could not open file";//output Error Printing to screen
      return Dictionary::failure;//return failure (false)
    }
  string fileWord;//declare fileWord which will be used to store word from fin (inFile)
  fin>>fileWord;//stores string from infile(fin) into fileWord
  while(fin)//while the infile(fin) is being read
    {
      if(!SearchForWord(fileWord))//if fileWord is not found in the dictionary
        cout<<fileWord<<" was not in the dictionary."<<endl;//output fileWord was not in the dictionary to the screen
      fin>>fileWord;//stores string from infile(fin) into fileWord
    }
  return Dictionary::success;//return success(true)
}
//function that inserts words from given file into the dictionary
bool Dictionary::InsertWordIntoDict(string fileName)
{
  int numAdj=0;//set integer that will be used to measure length of output
  ifstream fin;//declare infile(fin)
  fin.open(fileName.data());//opens infile (fin)
  if(!fin)//if infile(fin) could not be opened
    return Dictionary::failure;//return failure (false)
  string word;//declare string called word
  fin>>word;
  while(fin)//while the infile (fin) is being read
    {
      //25 has been determined to be appropriate distance before extra line is added
      if(numAdj>=25)//if numAdj is larger than 25 than an extra line is added to make sure horizontal length of output isn't too ridiculous
        {
          numAdj=0;//resets numAdj for reusability
          AddAWord("\n");//extra line is added to the output
        }
      AddAWord(word);//Add word to the dictionary by calling AddAWord with word argument
      numAdj++;//increment numAdj
      fin>>word;//stores string from infile(fin) into word
    }
  return Dictionary::success;//return success(true)
}
//function that reads commands and calls the corresponding function thus performing the desired task
void Dictionary::ProcessTransactionFile()//takes no parameters
{
  string fileName;//declares string called fileName
  cout<<"Please enter a transaction file: ";//asks user to enter a transaction file
  cin>>fileName;//user inputs transaction fileName

  ifstream fin;//declare infile (fin)
  fin.open(fileName.data());//opens infile (fin)
  if(!fin)//if file could not be opened
    cout<<"Could not open transaction file. ";//output file could not be opened
  string command;//declare string called command (For Commands)
  string word;//declare command called word (For fileNames and words)

  fin>>command;//store string from infile (fin) to command
  fin>>word;//store string from infile (fin) to word
  while(fin)//while inFile(fin) is being read
    {
      if(command=="AddW")//if command equals AddW
        AddAWord(word);//Add word to the dictionary by calling AddAWord with word argument
      else if(command=="InsertF")//if command equals InsertF
        InsertWordIntoDict(word);//Inserts words into the dictionary from a file called word by calling InsertWordIntoDict with word argument
      else if(command=="PrintF")//if command equals PrintF
        PrintAFileInDict(word);//Prints words in file called word by calling PrintAFileInDict with word argument
      else if(command=="DeleteW")//if command equals DeleteW
        DeleteAWord(word);//Deletes word from the dictionary by calling DeleteAWord with word argument
      else if(command=="SpellCheck")//if command equals SpellCheck
        SpellChecking(word);//SpellChecks words  from a file called word by calling SpellChecking with word argument
      else if(command=="SearchW")//if command equals SearchW
        SearchForWord(word);//Searches for word by calling SearchForWord with word argument
      else
        cout<<"Error in transaction file.";//outputs error in transaction file to screen

      fin>>command;//store string from infile (fin) to command
      fin>>word;//store string from infile (fin) to word
    }
    exit(1);
}
    int main()
{
  Dictionary  DictForCS211;//create dictionary object called DictForCS211
  DictForCS211.ProcessTransactionFile();//call ProcessTransactionFile from DictForCS211
  return 0;
}
#endif

