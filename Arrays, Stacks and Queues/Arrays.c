#include <stdio.h>
#include <stdlib.h>

int linearSearch(int *array, int size, int target) {
  for (int i = 0; i < size; i++) {
    if (array[i] == target) return 1;
  }

  return 0;
}

int binarySearch(int *array, int low, int high, int target) {
  if (low > high) return 0;

  int mid = (low + high) / 2;

  if (array[mid] == target) {
    return 1;
  } else if (array[mid] < target) {
    return binarySearch(array, mid + 1, high, target);
  } else {
    return binarySearch(array, low, mid - 1, target);
  }
}

void bubbleSort(int *array, int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
      }
    }
  }
}

void insertionSort(int *array, int size) {
  for (int i = 1; i < size; i++) {
    int key = array[i];
    int j = i - 1;
    while (j >= 0 && array[j] > key) {
      array[j + 1] = array[j];
      j--;
    }
    array[j + 1] = key;
  }
}

void selectionSort(int *array, int size) {
  for (int i = 0; i < size - 1; i++) {
    int minIndex = i;
    for (int j = i + 1; j < size; j++) {
      if (array[j] < array[minIndex]) {
        minIndex = j;
      }
    }
    int temp = array[minIndex];
    array[minIndex] = array[i];
    array[i] = temp;
  }
}

void merge(int *array, int low, int mid, int high) {
  int n1 = mid - low + 1;
  int n2 = high - mid;

  int left[n1], right[n2];
  for (int i = 0; i < n1; i++) left[i] = array[low + i];
  for (int i = 0; i < n2; i++) right[i] = array[mid + 1 + i];

  int i = 0, j = 0, k = low;
  while (i < n1 && j < n2) {
    if (left[i] <= right[j]) array[k++] = left[i++];
    else array[k++] = right[j++];
  }

  while (i < n1) array[k++] = left[i++];
  while (j < n2) array[k++] = right[j++];
}

void mergeSort(int *array, int low, int high) {
  if (low < high) {
    int mid = (low + high) / 2;
    mergeSort(array, low, mid);
    mergeSort(array, mid + 1, high);
    merge(array, low, mid, high);
  }
}

int partition(int *array, int low, int high) {
  int pivot = array[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (array[j] < pivot) {
      i++;
      int temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }

  int temp = array[i + 1];
  array[i + 1] = array[high];
  array[high] = temp;

  return i + 1;
}

void quickSort(int *array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void printArray(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d ", array[i]);
  }
  printf("\n");
}

int main() {
  int array[] = {64, 34, 25, 12, 22, 11, 90};
  int size = sizeof(array) / sizeof(array[0]);

  quickSort(array, 0, size - 1);

  printf("Sorted array: ");
  printArray(array, size);

  return 0;
}

