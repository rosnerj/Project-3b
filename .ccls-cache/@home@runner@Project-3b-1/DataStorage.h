#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#pragma once

class DataStorage {
  private:
    struct Node {
        string id, title, developers, publishers, platforms, genres;
        double main, mainPlus, completionist;
    };
    //This vector of nodes stores all of the data
    vector<Node> dataSet;
  public:
    //This function goes through the chosen dataset and inserts all of the data into an array.
    void insertDataset(string fileName);

    //These are the two sorting algorithms that will be compared.
    void quickSort();
    void timSort();

    //This function outputs all of the data from the stored nodes at once (will be modified)
    void outputDataset();
};


void DataStorage::insertDataset(string fileName) {    
  string input;
  Node node;
  ifstream openFile(fileName);
  //The first line isn't necessary because it only contains text, so it can be disregarded.
  getline(openFile, input);

  //This goes through the entirety of the csv file to take out all of the necessary data.
  while(openFile.peek() != EOF)
    {
      //This gets the id
      getline(openFile, input, ',');
      node.id=input;

      //This gets the game title
      getline(openFile, input, ',');
      node.title=input;

      //This gets the time to complete the main game
      getline(openFile, input, ',');
      node.main = stod(input);
      
      //This gets the time to complete the main game plus extra content
      getline(openFile, input, ',');
      node.mainPlus = stod(input);
      
      //This gets the time to complete the game while completing everything
      getline(openFile, input, ',');
      node.completionist = stod(input);
      
      //This gets the game developer
      getline(openFile, input, ',');
      //If there are multiple entries in this cell of the spreadsheet
      if(input[0]=='\"')
      {
        //Remove the quotation mark at the start
        input.erase(0,1);
        //This adds the corrected input
        node.developers=input+",";
        //This gets the rest of the input between the quotation marks
        getline(openFile, input, '\"');
        //This adds the rest of the input
        node.developers+=input;
        //This goes to the end of the quotation mark
        getline(openFile, input, ',');
      }
      else
      {
        node.developers=input;
      }
      
      //This gets the game publisher
      getline(openFile, input, ',');
      //If there are multiple entries in this cell of the spreadsheet
      if(input[0]=='\"')
      {
        //Remove the quotation mark at the start
        input.erase(0,1);
        //This adds the corrected input
        node.publishers=input+",";
        //This gets the rest of the input between the quotation marks
        getline(openFile, input, '\"');
        //This adds the rest of the input
        node.publishers+=input;
        //This goes to the end of the quotation mark
        getline(openFile, input, ',');
      }
      else
      {
        node.publishers=input;
      }
      
      //This gets the platforms you can play the game on
      getline(openFile, input, ',');
      //If there are multiple entries in this cell of the spreadsheet
      if(input[0]=='\"')
      {
        //Remove the quotation mark at the start
        input.erase(0,1);
        //This adds the corrected input
        node.platforms=input+",";
        //This gets the rest of the input between the quotation marks
        getline(openFile, input, '\"');
        //This adds the rest of the input
        node.platforms+=input;
        //This goes to the end of the quotation mark
        getline(openFile, input, ',');
      }
      else
      {
        node.platforms=input;
      }
      
      //This gets the game genre
      getline(openFile, input, '\n');
      //If there are multiple entries in this cell of the spreadsheet
      if(input[0]=='\"')
      {
        //Remove the quotation mark at the start and end
        input.erase(0,1);
        input.erase(input.size()-1);
      }
      //This adds the corrected input
      node.genres=input;
      
      //This adds the nodes to the vector which stores them
      dataSet.push_back(node);
    }
}

//This function sorts the stored dataSet by using quickSort
void DataStorage::quickSort() {

}

//This function sorts the stored dataSet by using timSort
void DataStorage::timSort() {

}


void DataStorage::outputDataset() {
  //For now this function just outputs the title of each of the stored nodes
  //This function will most likely be changed, this is temporary to make sure the data is stored correctly
  for(int i = 0; i < dataSet.size(); i++)
  {
    cout << dataSet[i].title << endl;
  }
}