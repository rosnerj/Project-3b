#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once

class DataStorage {
private:
  struct Node {
    string id, title, developers, publishers, platforms, genres;
    double main, mainPlus, completionist;
    // This function retrives either main, mainPlus or completionist depending
    // on the int value This is done to prevent repeated function calls; 0 is
    // main, 1 is mainPlus, 2 is completionist
    double dataRetrieval(int selection);
  };
  // This vector of nodes stores all of the data
  vector<Node> dataSet;

  // The main recursive function for quicksort
  void quickSort(int start, int end, int selection);

  // Partition function for quick sort
  int Partition(int start, int end, int selection);

  // insertion sort for Tim sort
  void InsertionSort(vector<Node> &vec, int l, int r, int selection);

  // merge function for Tim sort
  void Merge(vector<Node> &vec, int l, int m, int r, int selection);

  // min function for Tim sort
  int min(int a, int b);

public:
  // This function goes through the chosen dataset and inserts all of the data
  // into an array.
  void insertDataset(string fileName);

  // These are the two sorting algorithms that will be compared.
  void quickSortMain(int selection);
  void timSortMain(int selection, const int TIM);
  // prints relevant data
  void printList(int data);
};

void DataStorage::insertDataset(string fileName) {
  string input;
  Node node;
  ifstream openFile(fileName);
  // The first line isn't necessary because it only contains text, so it can be
  // disregarded.
  getline(openFile, input);

  // This goes through the entirety of the csv file to take out all of the
  // necessary data.
  while (openFile.peek() != EOF) {
    // This gets the id
    getline(openFile, input, ',');
    node.id = input;

    // This gets the game title
    getline(openFile, input, ',');
    node.title = input;

    // This gets the time to complete the main game
    getline(openFile, input, ',');
    node.main = stod(input);

    // This gets the time to complete the main game plus extra content
    getline(openFile, input, ',');
    node.mainPlus = stod(input);

    // This gets the time to complete the game while completing everything
    getline(openFile, input, ',');
    node.completionist = stod(input);

    // This gets the game developer
    getline(openFile, input, ',');
    // If there are multiple entries in this cell of the spreadsheet
    if (input[0] == '\"') {
      // Remove the quotation mark at the start
      input.erase(0, 1);
      // This adds the corrected input
      node.developers = input + ",";
      // This gets the rest of the input between the quotation marks
      getline(openFile, input, '\"');
      // This adds the rest of the input
      node.developers += input;
      // This goes to the end of the quotation mark
      getline(openFile, input, ',');
    } else {
      node.developers = input;
    }

    // This gets the game publisher
    getline(openFile, input, ',');
    // If there are multiple entries in this cell of the spreadsheet
    if (input[0] == '\"') {
      // Remove the quotation mark at the start
      input.erase(0, 1);
      // This adds the corrected input
      node.publishers = input + ",";
      // This gets the rest of the input between the quotation marks
      getline(openFile, input, '\"');
      // This adds the rest of the input
      node.publishers += input;
      // This goes to the end of the quotation mark
      getline(openFile, input, ',');
    } else {
      node.publishers = input;
    }

    // This gets the platforms you can play the game on
    getline(openFile, input, ',');
    // If there are multiple entries in this cell of the spreadsheet
    if (input[0] == '\"') {
      // Remove the quotation mark at the start
      input.erase(0, 1);
      // This adds the corrected input
      node.platforms = input + ",";
      // This gets the rest of the input between the quotation marks
      getline(openFile, input, '\"');
      // This adds the rest of the input
      node.platforms += input;
      // This goes to the end of the quotation mark
      getline(openFile, input, ',');
    } else {
      node.platforms = input;
    }

    // This gets the game genre
    getline(openFile, input, '\n');
    // If there are multiple entries in this cell of the spreadsheet
    if (input[0] == '\"') {
      // Remove the quotation mark at the start and end
      input.erase(0, 1);
      input.erase(input.size() - 1);
    }
    // This adds the corrected input
    node.genres = input;

    // This adds the nodes to the vector which stores them
    dataSet.push_back(node);
  }
  openFile.close();
}

// This function retrieves either main, mainPlus or completionist based on a
// pre-determined int value (this is done to prevent having to make 3 separate
// functions for the each value passed into the sorts)
double DataStorage::Node::dataRetrieval(int selection) {
  switch (selection) {
  case 0:
    return main;
  case 1:
    return mainPlus;
  case 2:
    return completionist;
  }
  // The base case is covered within the input parsing from main
}

int DataStorage::Partition(int start, int end, int selection) {
  double pivot = dataSet[end - 1].dataRetrieval(selection);
  int inc = start;
  int dec = end;
  while (inc <= dec) {
    while (dataSet[inc].dataRetrieval(selection) < pivot) {
      inc++;
    }
    while (dataSet[dec].dataRetrieval(selection) > pivot) {
      dec--;
    }
    if (inc <= dec) {
      swap(dataSet[inc], dataSet[dec]);
      inc++;
      dec--;
    }
  }
  return inc;
}

// This function sorts the stored dataSet by using quickSort
void DataStorage::quickSort(int start, int end, int selection) {
  if (start < end) {
    int pivot = Partition(start, end, selection);
    quickSort(start, pivot - 1, selection);
    quickSort(pivot, end, selection);
  }
}

void DataStorage::quickSortMain(int selection) {
  quickSort(0, dataSet.size() - 1, selection);
}

// This function sorts the stored dataSet by using timSort
void DataStorage::timSortMain(int selection, const int TIM) {
  int size = dataSet.size();

  for (unsigned int i = 0; i < size; i += TIM) {
    InsertionSort(dataSet, i, min(i + TIM - 1, size - 1), selection);
  }

  // merge sort
  for (unsigned int i = TIM; i < size; i *= 2) {
    for (int left = 0; left < size; left += 2 * i) {
      int middle = left + i - 1;
      int right = min(left + 2 * i - 1, size - 1);
      if (middle < right) {
        Merge(dataSet, left, middle, right, selection);
      }
    }
  }
}

// min function
int DataStorage::min(int a, int b) {
  if (a > b) {
    return b;
  }
  return a;
}

// insertion sort function
void DataStorage::InsertionSort(vector<Node> &vec, int l, int r,
                                int selection) {
  for (unsigned int i = l + 1; i <= r; i++) {
    Node temp = vec.at(i);
    int j = i - 1;
    while (j >= l &&
           vec.at(j).dataRetrieval(selection) > temp.dataRetrieval(selection)) {
      vec.at(j + 1) = vec.at(j);
      j--;
    }
    vec.at(j + 1) = temp;
  }
}

// merge function
void DataStorage::Merge(vector<Node> &vec, int l, int m, int r, int selection) {
  vector<Node> left;
  vector<Node> right;
  int temp = m - l + 1;
  int temp2 = r - m;
  for (unsigned int i = 0; i < temp; i++) {
    left.push_back(vec.at(l + i));
  }
  for (unsigned int i = 0; i < temp2; i++) {
    right.push_back(vec.at(m + 1 + i));
  }

  int i = 0;
  int j = 0;
  int k = l;

  while (i < temp && j < temp2) {
    if (left.at(i).dataRetrieval(selection) <=
        right.at(j).dataRetrieval(selection)) {
      vec.at(k) = left.at(i);
      i++;
    } else {
      vec.at(k) = right.at(j);
      j++;
    }
    k++;
  }

  while (i < temp) {
    vec.at(k) = left.at(i);
    i++;
    k++;
  }

  while (j < temp2) {
    vec.at(k) = right.at(j);
    j++;
    k++;
  }
}

void DataStorage::printList(int data) {
  int datatype = data;
  int counter = 1;
  cout << "Top Ten Fastest Games" << endl;
  for (int i = 0; i < 10; i++) {
    cout << i + 1 << ". " << dataSet[i].title << ": "
         << dataSet[i].dataRetrieval(datatype) << " Hours" << endl;
  }
  cout << endl;
  cout << "Middle Ten Games" << endl;
  for (int i = (dataSet.size() / 2) - 5; i < (dataSet.size() / 2) + 5; i++) {
    cout << counter << ". " << dataSet[i].title << ": "
         << dataSet[i].dataRetrieval(datatype) << " Hours" << endl;
    counter++;
  }
  cout << endl;
  counter = 1;
  cout << "Top Ten Slowest Games" << endl;
  for (int i = (dataSet.size() - 1); i > (dataSet.size() - 11); i--) {
    cout << counter << ". " << dataSet[i].title << ": "
         << dataSet[i].dataRetrieval(datatype) << " Hours" << endl;
    counter++;
  }
}