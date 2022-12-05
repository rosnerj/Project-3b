#include "DataStorage.h"

int main() {
  DataStorage data;
  data.insertDataset("randomlyGeneratedData.csv");
  data.outputDataset();
  return 0;
}