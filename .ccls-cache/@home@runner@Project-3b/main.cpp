#include "DataStorage.h"

int main() {
  DataStorage data;
  int dataSet, dataType, sortType;
  cout << "Welcome to Game Time Sorter!" << endl;

  while (dataSet != 1 && dataSet != 2) {
    cout << "Please Select a Dataset:" << endl;
    cout << "1. Real World Data" << endl;
    cout << "2. Randomly Generated Data (100,000 Rows)" << endl;
    cin >> dataSet;
  }

  while (dataType != 1 && dataType != 2 && dataType != 3) {
    cout << "Please Select the Times to be Sorted:" << endl;
    cout << "1. Main Story" << endl;
    cout << "2. Main Story Plus Extra Content" << endl;
    cout << "3. Completionist" << endl;
    cin >> dataType;
  }

  while (sortType != 1 && sortType != 2) {
    cout << "Please Select a Sorting Option:" << endl;
    cout << "1. Tim Sort" << endl;
    cout << "2. Quick Sort" << endl;
    cin >> sortType;
  }

  // This changes the value to the correct selection for data type
  dataType--;

  // This selects the correct dataset to use
  switch (dataSet) {
  case 1:
    data.insertDataset("realWorldData.csv");
    break;
  case 2:
    data.insertDataset("randomlyGeneratedData.csv");
    break;
  }

  // This is used to record the time before the sorting occurs
  auto timeBeforeSort = chrono::high_resolution_clock::now();
  switch (sortType) {
  case 1:
    data.timSortMain(dataType, 64);
    break;
  case 2:
    data.quickSortMain(dataType);
    break;
  }
  // This is used to record how long the sorting took
  auto functionTime = chrono::duration_cast<chrono::microseconds>(
      chrono::high_resolution_clock::now() - timeBeforeSort);

  cout << "Sorting took " << functionTime.count() << " ms to complete." << endl;

  // The different sorts may result in different games with the same time
  // showing up; the sorting methods only sort numerically so this is
  // intentional.
  data.printList(dataType);

  return 0;
}