#include <stdio.h>
#include <iostream>
#include <ctime>

using namespace std;

#define MAX_SIZE 1000
static int ori_array[MAX_SIZE];
static int length;

void execute();
void exchangeSort();
void insertionSort();
void mergeSort(int start, int end);
void merge(int start, int mid, int end);
void quickSort(int low, int high);
void userInput();
void generateArray();
void executeSorting();
void listArray();
void printArray();

int main(int argc, char const *argv[]) {
  execute();
  return 0;
}

// implementation

void execute(){
  string input = "";
  bool sign = true;
  srand((unsigned)time(NULL));
  while (sign) {
    userInput();
    generateArray();
    executeSorting();
    cout << "Press e to Exit." << endl;
    cout << "Press any other button to continue." << endl;
    cin >> input;
    if (input[0] == 'e' || input[0] == 'E') {
      sign = false;
    }
  }
  cout << "Successfully Exited" << endl;
}

void exchangeSort(){
  for (int i = 0; i < length-1; i++) {
    for (int j = i+1; j < length; j++) {
      if (ori_array[i] > ori_array[j]) {
        int temp = ori_array[i];
        ori_array[i] = ori_array[j];
        ori_array[j] = temp;
      }
    }
    if (length <= 20) {
      printArray();
    }
  }
}

void insertionSort() {
  if (length == 0) return;
  if (length <= 20) {
    printArray();
  }
  for (int i = 1; i < length; i ++) {
    int index = i -1;
    int temp = ori_array[i];
    while(index > -1) {
      if (temp < ori_array[index]) {
        ori_array[index+1] = ori_array[index];// shift right
        index --;
      } else {
        break;
      }
    }
    ori_array[index+1] = temp;
    if (length <= 20) {
      printArray();
    }
  }
}

void mergeSort(int start, int end) {
  if (start < end) {
    int mid = (end + start)/2;
    mergeSort(start, mid);
    mergeSort(mid+1, end);
    merge(start, mid, end);
    if (length <= 20) {
      printArray();
    }
  }
}

void merge(int start, int mid, int end) {
  int temparr[MAX_SIZE];
  int left = start;
  int right = mid +1;
  int write = 0;
  while (left <= mid && right <= end) {
    if (ori_array[left] < ori_array[right]){
      temparr[write] = ori_array[left];
      left ++;
    } else {
      temparr[write] = ori_array[right];
      right ++;
    }
    write ++;
  }
  if (left <= mid) {
    for (int i = left; i <= mid; i++ ) {
      temparr[write] = ori_array[i];
      write ++;
    }
  }
  if (right <= end) {
    for (int i = right; i <= end; i++) {
      temparr[write] = ori_array[i];
      write ++;
    }
  }
  int index = 0;
  for (int i = start; i <= end; i++) {
    ori_array[i] = temparr[index];
    index ++;
  }
  return;
}


void quickSort(int low, int high) {
  if (low >= high) return;
  int pivot = rand()%(high - low + 1) + low;
  int pivotitem = ori_array[pivot];
  ori_array[pivot] = ori_array[low];
  int j = low;
  for (int i = low +1; i <= high; i++) {
    if (ori_array[i] < pivotitem) {
      j++;
      int temp = ori_array[j];
      ori_array[j] = ori_array[i];
      ori_array[i] = temp;
    }
  }
  ori_array[low] = ori_array[j];
  ori_array[j] = pivotitem;
  quickSort(low, j-1);
  quickSort(j+1, high);
  if (length <= 20) {
    printArray();
  }
}

// void quickSort2(int low, int high) {
//   if (low >= high) return;
//   int pivot = rand()%(high - low + 1) + low;
//   int i = low;
//   int j = high;
//   while (i <= j) {
//     while (i <= j && ori_array[i] < ori_array[pivot]) i ++;
//     while (i <= j && ori_array[j] > ori_array[pivot]) j --;
//     if (i <= j) {
//       int temp = ori_array[i];
//       ori_array[i] = ori_array[j];
//       ori_array[j] = temp;
//       i ++;
//       j --;
//     }
//   }
//   quickSort2(low, j);
//   quickSort2(i, high);
// }

void userInput(){
  int n = -1;
  cout << "please input a number between 0 to 1000: ";
  cin >> n;
  while (n <= 0 || n > MAX_SIZE) {
    if (cin.fail()) {
      cin.clear();
      cin.ignore();
      cout << "please input a number between 0 to 1000: ";
      cin >> n;
    }
  }
  length = n;
  return;
}

void generateArray() {
  if (length <= 20) {
    for (int i = 0; i < length; i++) {
      ori_array[i] = rand()%15 + 1;
    }
    return;
  }
  for (int i = 0; i < length; i ++) {
    ori_array[i] = rand()%100 +1;
  }
  return;
}

void executeSorting(){
  cout << "Please select the sorting method." << endl;
  cout << "1 : Exchange Sort" << endl;
  cout << "2 : Insertion Sort" << endl;
  cout << "3 : Merge Sort" << endl;
  cout << "4 : Quick Sort" << endl;
  int choice  = 0;
  while (choice < 1 || choice > 4) {
    cin >> choice;
    if (choice < 1 || choice > 4) {
      cout << "Please select the sorting method." << endl;
      cout << "Please input between 1 to 4" << endl;
    }
  }
  cout << "Original Array:" << endl;
  listArray();
  switch (choice) {
    case 1:
      cout << "Starting Exchange Sort" << endl;
      exchangeSort();
      break;
    case 2:
      cout << "Starting Insertion Sort" << endl;
      insertionSort();
      break;
    case 3:
      cout << "Starting Merge Sort" << endl;
      mergeSort(0, length-1);
      break;
    case 4:
      cout << "Starting Quick Sort" << endl;
      quickSort(0, length-1);
  }
  listArray();
  return;
}

void listArray() {
  for (int i = 0; i < length; i ++) {
    cout << ori_array[i] <<" ";
  }
  cout << endl;
}

void printArray(){
  for (int i = 0; i < length; i ++) {
    cout << ori_array[i];
    for (int j = 0; j < ori_array[i]; j++) {
      cout << "*";
    }
    cout << endl;
  }
  cout << "========================"<< endl;
}
