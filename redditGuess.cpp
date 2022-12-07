#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <map>
#include <stdlib.h> 
#include <chrono>
#include "redditPost.h"

using namespace std;
using namespace std::chrono;

#include "Bridges.h"
#include "DataSource.h"
#include "data_src/Reddit.h"

using namespace bridges;

// This program fragment illustrates how to access and read the Reddit Post data 

//merge helper method
/*void merge(int[] allScores, int begin,int middle,int end){
  
}*/
//merge sort method
/*void merge(int[] allScores, int begin, int middle, int end);

void mergeSort(int[] allScores, int begin, int end){
  if (begin >= end){
    return;
  }
  int middle = (begin+end)/2;
  mergeSort(allScores,begin,middle);
  mergeSort(allScores,middle+1,end);
  merge(allScores,begin,middle,end);
}*/

//Declare functions here
string subRedditSelect();
void printMenu1(redditPostContainer &redditObj);
void printMenu2(redditPostContainer &redditObj);
void printMenu3(redditPostContainer &redditObj);
void printMenu4(redditPostContainer &redditObj);
void writeCSV(vector<Reddit> &redLst);

int main(int argc, char** argv) {

	// create Bridges object
	Bridges bridges(1, "sbarreto", "209560685652");

	// create data source object
	DataSource ds(&bridges);

  // Our Custom Object
  redditPostContainer redditObj;

  //Take SubReddit selection, here are the supported subreddits: http://bridges-data-server-reddit.bridgesuncc.org/list
  string input = subRedditSelect();
  vector<Reddit> reddit_list;
  
  if(0 == input.compare("All SubReddits"))
  {
    string strHelper;
    vector<Reddit> tempVec;
  
  //read "subRedditList.txt"
    ifstream readTxt("subRedditList.txt");
    while (getline(readTxt, strHelper) && 0 != strHelper.compare("All SubReddits")) {
      tempVec =  ds.getRedditData(strHelper);
      cout << strHelper << endl;
      reddit_list.insert(reddit_list.end(), tempVec.begin(), tempVec.end());
      //cout << reddit_list.size() << endl;
    }
  }
  else if(0 == input.compare("100,000+ Post"))
  {
    // Duplicate All SubReddit Posts until reddit_list.size > 100,000
    while(reddit_list.size() < 100000)
      {
        string strHelper;
        vector<Reddit> tempVec;
  
        //read "subRedditList.txt"
      ifstream readTxt("subRedditList.txt");
      while (getline(readTxt, strHelper) && 0 != strHelper.compare("All SubReddits")) {
        tempVec =  ds.getRedditData(strHelper);
        //cout << strHelper << endl;
        reddit_list.insert(reddit_list.end(), tempVec.begin(), tempVec.end());
        cout << reddit_list.size() << endl;
        }
      }
  }
  else
	  reddit_list = ds.getRedditData(input);
  
  writeCSV(reddit_list);
  
  //int *allScores = new int[reddit_list.size()];
  //copy objects from vector into dynamic array to be sorted
  for(unsigned int i = 0; i < reddit_list.size();i++){
    
  }
	for (auto post : reddit_list) {
    int scor = post.getScore();
    string idPost = post.getID(), titlePost = post.getTitle();

    redditObj.insertPost(scor, titlePost, idPost);
    
		//std::cout << "CommentCount: " << post.getCommentCount() << "\n";
		//std::cout << "Subreddit: " << post.getSubreddit() << "\n";
		//std::cout << "\n";
	}
  redditObj.printSize();

  // Present "Menu 1"
  printMenu1(redditObj);
  
  //std::cout << "Array Size: "<< allScores.size()<<"\n";
  //delete[] allScores;
  
	return 0;
}

string subRedditSelect()
{
  int ret, numCount = 0;
  string strHelper;
  vector<string> subList;
  
  //read "subRedditList.txt" and put values into "vector<string> subList"
  ifstream readTxt("subRedditList.txt");
  while (getline(readTxt, strHelper)) {
    cout << ++numCount << ") "<< strHelper << endl;
    subList.push_back(strHelper);
  }

  //Ask for input here
  cout << "Input the number of the desired SubReddit: ";
  cin >> ret;
  cout << endl;
  
  return subList[ret - 1];
}
//Main Menu
void printMenu1(redditPostContainer &redditObj){
  int usrInput = 0;
  // cout a choice between sort algorithm analyzing menu or the game menu
  
  while(usrInput != 4)
    {
      cout << "Welcome to Menu 1" << endl;
      cout << "Input desired option's corresponding number \n" << "1) Algorithm Analysis Menu \n" << "2) Game Menu \n" << "3) SubReddit Stats Menu \n" << "4) Exit" << endl;
      
      cin >> usrInput;

      if(usrInput == 1)
      {
        cout << endl;
        cout << "Algorithm Analysis Menu" << endl;
        printMenu2(redditObj);
      }
      else if(usrInput == 2)
      {
        cout << endl;
        cout << "Game Menu" << endl;
        printMenu3(redditObj);
      }
      else if (usrInput == 3)
      {
        cout << endl;
        cout << "SubReddit Stats Menu" << endl;
        printMenu4(redditObj);
      }
      else if (usrInput == 4)
        cout << "Exiting" << endl;
    }
  
}
//Sort Algorithm Analysis Menu
void printMenu2(redditPostContainer &redditObj){
  cout << endl;
  
  int usrInput = 0;
  int sumMerge = 0, countMerge = 0;
  int sumShell = 0, countShell = 0;
  
  while(usrInput != 3)
    {
      // make a copy of our object to perform analysis on
      redditPostContainer cpy(redditObj);
      
      
      cout << "Input desired option's corresponding number \n" << "1) Merge Sort \n" << "2) Shell Sort \n" << "3) Previous Menu" << endl;
      
      cin >> usrInput;

      if(usrInput == 1)
      {//Merge Sort and Display time to Sort
        countMerge++;
        
        auto start = high_resolution_clock::now();
        cpy.mergeSort();
        auto stop = high_resolution_clock::now();
        auto time = duration_cast<microseconds>(stop-start);
        //Display time here
        cout << "Time taken by Merge Sort: "<<time.count()<<" microseconds"<<endl;
        sumMerge += time.count();
        cout << "Average Time taken by Merge Sort: "<< sumMerge / countMerge <<" microseconds after " << countMerge << " Merge Sorts"<<endl;
        cout << endl;
      }
      else if(usrInput == 2)
      {//Shell Sort and Display time to Sort
        countShell++;
        
        auto start = high_resolution_clock::now();
        cpy.shellSort();
        auto stop = high_resolution_clock::now();
        auto time = duration_cast<microseconds>(stop - start);
        //Display time here
        cout << "Time taken by Shell Sort: "
         << time.count() << " microseconds" << endl;
        sumShell += time.count();
        cout << "Average Time taken by Shell Sort: "<< sumShell / countShell <<" microseconds after " << countShell << " Shell Sorts"<<endl;
        cout << endl;
      }
      else if (usrInput == 3)
        cout << "Previous Menu" << endl;
    }
}
// Game Menu
void printMenu3(redditPostContainer &redditObj){
  // Pick 2 random post titles and display them
  int usrInput = 0;
  int usrPoints = 0;

  redditObj.shellSort();
  
  while(usrInput != 3) 
  {
    int randomIndex1 = rand() % redditObj.postVec.size();
    int randomIndex2 = rand() % redditObj.postVec.size();

    // Reselect a random index2 if index1 == index2 or if both of their positions give the same score
    while (randomIndex1 == randomIndex2 || redditObj.getScore(randomIndex1) == redditObj.getScore(randomIndex2)) 
      randomIndex2 = rand() % redditObj.postVec.size();

    // cout << randomIndex1 << " " << randomIndex2 << endl;

    // Prompt Player to select the one that seems to have a higher score
    cout << "Which Title has the higher Reddit Score OR Select Previous Menu \n" << "1) " << redditObj.getTitle(randomIndex1) << " \n"<< "2) " << redditObj.getTitle(randomIndex2) << " \n"<< "3) Previous Menu" << endl;
    cin >> usrInput;

    // If correct, add point
    if(redditObj.getScore(randomIndex1) < redditObj.getScore(randomIndex2) && usrInput == 2)
    {
      cout << "Correct!" << endl;
      usrPoints++;
    }
    else if(redditObj.getScore(randomIndex1) > redditObj.getScore(randomIndex2) && usrInput == 1)
    {
      cout << "Correct!" << endl;
      usrPoints++;
    }
    // If Wrong, Game Over, restart or main menu
    if(redditObj.getScore(randomIndex1) > redditObj.getScore(randomIndex2) && usrInput == 2)
    {
      cout << "GAME OVER" << endl;
      usrInput = 3;
    }
    else if(redditObj.getScore(randomIndex1) < redditObj.getScore(randomIndex2) && usrInput == 1)
    {
      cout << "GAME OVER" << endl;
      usrInput = 3;
    }

    // Output Answer and Current Game Score
    cout << "Score 1) " << redditObj.getScore(randomIndex1) << "\n" << "Score 2) " << redditObj.getScore(randomIndex2) << "\n";
    cout << "Game Score: " << usrPoints << "\n" << endl;
    }
}
// Stats Menu
void printMenu4(redditPostContainer &redditObj)
{
  redditPostContainer cpy(redditObj);
  //Sort 
  cpy.shellSort();
  int size = cpy.postVec.size();
  //Display top 5 Post Titles
  cout << "The top 5 Posts on this SubReddit are: \n";
  for (int i = 1; i < 6; i++)
    {
      cout << i << ") Score: " << cpy.getScore(cpy.postVec[size - i]) << " || Title: "<< cpy.getTitle(cpy.postVec[size - i]) << endl;
    }
  cout << endl;
  
}

void writeCSV(vector<Reddit> &redLst)
{
  ofstream fileReddit;
  fileReddit.open ("redditData.csv");
  for (auto post : redLst)
    {
      int scor = post.getScore();
      string idPost = post.getID(), titlePost = post.getTitle();
      fileReddit << scor <<","<< titlePost << "," << idPost << ",\n";
    }
  fileReddit.close();
}