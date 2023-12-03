#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_BUFFER_SIZE 2048

struct fileP {
  char* fileName;
  char fileContent[MAX_BUFFER_SIZE];
  int fileSize;
};

enum strNums {
  ONE = 1,
  TWO = 2,
  THREE = 3
};

void string_slice(char* original, char* result, size_t start, size_t end) {
  // result str, original str with offset, number of chars to copy
  strncpy(result, original + start, end - start);
  result[end - start] = '\0';
}

int _min(int a, int b) {
  return (a > b) ? b : a;
}

void checkThreeSubStr(char* subString, char* digit) {
  if (strcmp(subString, "one") == 0) {
    *digit = '1';
  }
  if (strcmp(subString, "two") == 0) {
    *digit = '2';
  }
  if (strcmp(subString, "six") == 0) {
    *digit = '6';
  }
}

void checkFourSubStr(char* subString, char* digit) {
  if (strcmp(subString, "four") == 0) {
    *digit = '4';
  }
  if (strcmp(subString, "five") == 0) {
    *digit = '5';
  }
  if (strcmp(subString, "nine") == 0) {
    *digit = '9';
  }
}

void checkFiveSubStr(char* subString, char* digit) {
  if (strcmp(subString, "three") == 0) {
    *digit = '3';
  }
  if (strcmp(subString, "seven") == 0) {
    *digit = '7';
  }
  if (strcmp(subString, "eight") == 0) {
    *digit = '8';
  }
}

int main() {
  struct fileP fileData;
  fileData.fileName = (char*)malloc(128 * sizeof(char));
  strcpy(fileData.fileName, "input.txt");

  FILE* filePtr = fopen(fileData.fileName, "r");
  assert(filePtr != NULL);

  int sumOfDigits = 0;

  while (fgets(fileData.fileContent, MAX_BUFFER_SIZE, filePtr)) {
    int len = strlen(fileData.fileContent);
    int numStringLen = 64;

    char numString[64]; // put all the converted and actual numbers in this
    int numStringIdx = 0;
    char digitToInsert = '\0';

    char lenThreeSubStr[4];
    char lenFourSubStr[5];
    char lenFiveSubStr[6];

    // convert all the strings: "NINE" -> 9; "TWO" -> 2; .. 

    for (int i = 0; i < len; i++) {
      // check for numbers in three length-based categories:

      // if slice.length == 3 => ONE, TWO, SIX
      // if slice.length == 4 => FOUR, FIVE, NINE
      // if slice.length == 5 => THREE, SEVEN, EIGHT

      if (isdigit(fileData.fileContent[i])) {
        numString[numStringIdx] = fileData.fileContent[i];
        numStringIdx++;
      }
      // _min sets a bound. No matter the position, we won't go past the length of the string
      string_slice(fileData.fileContent, lenThreeSubStr, _min(i, len - 3), i + 3); 
      string_slice(fileData.fileContent, lenFourSubStr, _min(i, len - 4), i + 4);
      string_slice(fileData.fileContent, lenFiveSubStr, _min(i, len - 5), i + 5);

      checkThreeSubStr(lenThreeSubStr, &digitToInsert);
      checkFourSubStr(lenFourSubStr, &digitToInsert);
      checkFiveSubStr(lenFiveSubStr, &digitToInsert);

      if (digitToInsert != '\0') {
        numString[numStringIdx] = digitToInsert;
        numStringIdx++;
        digitToInsert = '\0';
      }
    }
    numString[numStringIdx] = '\0'; // terminate the string once we're done inserting numbers

    int firstDigitIdx = 0;
    int lastDigitIdx = numStringIdx - 1; // parsing through the numString array. start behind the last termination char, that is '\0'
    numStringLen = numStringIdx; // in the case that all of the array is not used up, we set the termination character to be the length

    while (firstDigitIdx < numStringLen) {
      if (isdigit(numString[firstDigitIdx])) {
        break;
      }
      firstDigitIdx++;
    }

    while (lastDigitIdx >= 0) {
      if (isdigit(numString[lastDigitIdx])) {
        break;
      }
      lastDigitIdx--;
    }
    
    char calibrationNumber[3] = {numString[firstDigitIdx], numString[lastDigitIdx]};
    sumOfDigits += atoi(calibrationNumber);
    printf("%s\n", calibrationNumber);
  }

  fclose(filePtr);
  free(fileData.fileName);
  printf("%d\n", sumOfDigits);  
}