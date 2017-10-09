/*Tyler Allen
CS211
Lab 2
9/1/15
This program will output files based on an input file*/

#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>

using namespace std;
void readFile(vector<string>&vector);
void fillV(vector<string>&V,const vector<string>fileContents);

int main()
{
  vector<string>fileContents;
  vector<string>V;
  readFile(fileContents);
  fillV(V, fileContents);
  
  return 0;
}

void readFile(vector<string>&vector)
{
  ifstream fin;
  fin.open("data.txt");
  string command;
  int count=0;
  if(!fin)
    {
      cout<<"Cannot Open The File"<<endl;
    }
  else
    {
      fin>>command;
      while(fin)
        {
	  vector.push_back(command);
	  fin>>command;
        }
    }
  fin.close();
}

void fillV(vector<string>&V, const vector<string>fileContents)
{
  int in;
  for(int i =0; i<fileContents.size(); i++)
    {
      if(fileContents[i]=="Insert")
	{
	  i++;
	  in=atoi(fileContents[i+1].c_str());
	  if(V.size()>=in)
	    {
	     V.insert(V.begin()+in, fileContents[i]);
	    }
	  else
	    {
	      cout<<"Could not insert at "<<in<<endl;
	    }
	  i++;
	}
      else if(fileContents[i]=="Print")
	{
	  for(int i=0;i<V.size();i++)
	    {
	      cout<<V[i]<<endl;
	    }
	}
      else if(fileContents[i]=="Delete")
	{
	  i++;
	  in=atoi(fileContents[i].c_str());
	  if(V.size()>=in)
	    {
	      V.erase(V.begin()+in);
	    }
	  else
	    {
	      cout<<"Could not delete at "<<in<<endl;
	    }
	}
      else
	{
	  cout<<"There was an error in entering the contents."<<endl;
	}
    }
}
