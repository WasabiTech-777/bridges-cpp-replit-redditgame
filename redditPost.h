#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Bridges.h"
#include "DataSource.h"
#include "data_src/Reddit.h"

using namespace bridges;

class redditPostContainer{
  struct redditPost{
  //store: score, post title, id
    int score;
    string postTitle;
    string postId;
    // Constructor
    redditPost(int& _score, string& _title, string& _id) : score(_score), postTitle(_title), postId(_id) { }
  };


public:
  vector<redditPost*> postVec;

  //Constructor
  redditPostContainer()
  {
    //cout << "Object Created" << endl;
  }
  // Copy Constructor
  redditPostContainer(redditPostContainer& cpy);
  // Copy Overload
  //redditPostContainer& operator=(redditPostContainer& cpy);
  
  //Destructor
  ~redditPostContainer() // Deletes the vector of dynamic object Pointers
  {
    for(auto it : postVec)
      delete it;
    //cout << "Vector Deleted" << endl;
  }

  
  void insertPost(int& _score, string& _title, string& _id); // Method that inserts a dynamically allocated object into "postVec"
  void printSize();
  int getScore(int& index);
  int getScore(redditPost* postPtr);
  string getTitle(int& index);
  string getTitle(redditPost* postPtr);

  //Implement Merge Sort based on the "postVec[i]->score"

  //Implement Shell Sort based on the "postVec[i]->score"
  void shellSortHelper(int gap, int leftIndex);
  void insertionSort();
  void shellSort();

};

redditPostContainer::redditPostContainer(redditPostContainer& cpy)
{
  for(auto it : cpy.postVec)
    {
      postVec.push_back(new redditPost(it->score, it->postTitle, it->postId));
    }
}
//redditPostContainer& redditPostContainer::operator=(redditPostContainer& cpy)
//{}

void redditPostContainer::insertPost(int& _score, string& _title, string& _id)
  {
    postVec.push_back(new redditPost(_score, _title, _id));
  }
void redditPostContainer::printSize()
{
  cout << "Number of Posts Recorded: " << postVec.size() << endl;
  cout << endl;
}
int redditPostContainer::getScore(int& index)
{
  return postVec[index]->score;
}
int redditPostContainer::getScore(redditPost* postPtr)
{
  return postPtr->score;
}
string redditPostContainer::getTitle(int& index)
{
  return postVec[index]->postTitle;
}
string redditPostContainer::getTitle(redditPost* postPtr)
{
  return postPtr->postTitle;
}

  void redditPostContainer::shellSortHelper(int gap, int leftIndex)
{
    int rightIndex = leftIndex + gap;
    if (rightIndex < postVec.size()) //
    {
        if (postVec[leftIndex]->score > postVec[rightIndex]->score) // switch values
        {
            redditPost* temp = postVec[leftIndex];
            postVec[leftIndex] = postVec[rightIndex];
            postVec[rightIndex] = temp;
            if (leftIndex - gap >= 0) // check prevous replacements for the same gap
            {
                shellSortHelper(gap, leftIndex - gap);
            }
        }
    }
}
  void redditPostContainer::insertionSort() 
{// Complexity O(n^2) without considering shell sort
    for (int i = 1; i < postVec.size(); i++)
    {
        if (postVec[i - 1]->score > postVec[i]->score) // enters if the previous index > current index
        {
            for (int j = i; j > 0; j--)
            {
              // enter if current insertion is complete
              if (postVec[j - 1]->score < postVec[j]->score) 
                  break;
              redditPost* temp = postVec[j-1];
              postVec[j - 1] = postVec[j];
              postVec[j] = temp;
            }
        }
    }
}
  void redditPostContainer::shellSort()
{
  //cout << "Unsorted: " << endl;
  //for (int i = 0; i < postVec.size(); i++)
    //cout << postVec[i]->score << " ";
  //cout << endl;
  
  int gap = postVec.size() / 2;

  // Shell Sort
  while (gap > 1)
  {
      for (int i = 0; i < postVec.size(); i++)
      {
          shellSortHelper(gap, i);
      }
      gap = gap / 2;
  }
  // Insertion Sort on last iteration
  insertionSort();
  //cout << "Sorted: " << endl;
  //for (int i = 0; i < postVec.size(); i++)
    //cout << postVec[i]->score << " ";
  //cout << endl;
}