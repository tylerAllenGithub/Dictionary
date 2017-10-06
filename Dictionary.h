#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Dictionary
{
 private:
  const int maxWordsInDict;
  const int maxWordsPerFile;
  int totalWordsInDict;
  int numOfWordsInFile[26];
  static bool failure;
  static bool success;

 public:
  Dictionary();
  Dictionary(int dictMaxWords, int fileMaxWords);
  bool AddAWord(string word);
  bool DeleteAWord(string word);
  bool SearchForWord(string word);
  bool PrintAFileInDict(string fileName);
  bool SpellChecking(string fileName);
  bool InsertWordIntoDict(string fileName);
  void ProcessTransactionFile();
};
#endif
