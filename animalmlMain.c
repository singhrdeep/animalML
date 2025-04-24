#include <stdio.h>
#include <string.h>
#include "given.h"

int main(int argc, char *argv[]) {
  
  // call structs
  struct Animal dataZoo[NUM_SAMPLES];
  struct Animal testData[NUM_TEST_DATA];

  // declare variables for task 1
  char fileName[30] = "a1Data.txt";  // filename

  // declare variables for task 2
  float eucDist = 0;  // euclidean distance
  float jaccSim = 0;  // jaccard similarity
  int hamDist = 0;    // hamming distance
  int vector1[NUM_FEATURES] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1}; // vector1 for testing
  int vector2[NUM_FEATURES] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1}; // vector2 for testing

  // declare variables for task 3
  int newSample[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1}; 
  int kNearestNeighbors[NUM_SAMPLES];  // store k-nearest neighbors
  int k = 5;    // number of neighbors

  // declare variables for task 4
  int predictedClass = 0;  // store the predicted class

  // declare variables for task 5
  float accuracy;  // store the accuracy of predictions

  // declare variables for menu
  int choice;  // user menu choice
  int case1 = 0;   // to ensure that user selects choice 1 before anything else

  // do-while for menu
  do {
    printf("\nHere is the menu - enter a number between 1 and 5 \n\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    // validate the user's choice
    if (choice < 1 || choice > 5) {
      printf("invalid input, exiting program\n");
      break;
    }

    // handler in case choice 1 isnt selected first
    if (!case1 && choice != 1) {
      printf("error, select choice 1 before selecting anything else\n");  // display error
      break;              // exit
    }

    // cases
    switch (choice) {
      case 1:
        // let handler know that choice 1 was selected
        case1 = 1;

        // call task 1 function
        readFromFile(fileName, dataZoo);

        // break
        break;

      case 2:
        // newline
        printf("\n");

        // call task 2 function
        distanceFunctions(vector1, vector2, &eucDist, &hamDist, &jaccSim);

        // print the distances
        printf("euclidean distance: %.6f\n", eucDist);
        printf("hamming distance: %d\n", hamDist);
        printf("jaccard similarity: %.6f\n", jaccSim);

        // break
        break;

      case 3:
        // newline
        printf("\n");

        // process nearest neighbors for all distance functions
        // by declaring a distFunc variable which ensures this
        for (int distFunc = 1; distFunc <= 3; distFunc++) {
          if (distFunc == 1)
            printf("nearest neighbors for new sample with euclidean distance: ");
          else if (distFunc == 2)
            printf("nearest neighbors for new sample with hamming distance: ");
          else
            printf("nearest neighbors for new sample with jaccard similarity: ");

          findKNearestNeighbors(dataZoo, newSample, k, distFunc, kNearestNeighbors);

          // print numbers
          for (int i = 0; i < k; i++) {
            printf("%d ", kNearestNeighbors[i]);
          }
          printf("\n");
        }
        break;

      case 4:
        // newline
        printf("\n");

        // call task 4 function
        predictedClass = predictClass(dataZoo, newSample, 1, k);
        
        // print the predicted class
        printf("the predicted class is: %d\n", predictedClass);
        
        // reset predictedClass variable 
        predictedClass = 0;
        
        // newline
        printf("\n");
        
        // call task 4 function
        predictedClass = predictClass(dataZoo, newSample, 2, k);
        
        // print the predicted class
        printf("the predicted class is: %d\n", predictedClass);
        
        // reset predictedClass variable 
        predictedClass = 0;
        
        // newline
        printf("\n");
        
        // call task 4 function
        predictedClass = predictClass(dataZoo, newSample, 3, k);

        // print the predicted class
        printf("the predicted class is: %d\n", predictedClass);

        // break
        break;

      case 5:
        // newline
        printf("\n");

        // open testData.csv
        FILE *file = fopen("testData.csv", "r");

        // check if the file opened successfully
        if (file == NULL) {
          printf("error opening file\n");
          return -1;
        }

        // read test data using CSV conversion codes
        // source: https://www.geeksforgeeks.org/scanfns-str-vs-getsstr-in-c-with-examples/
        
        /*
        Explaination: fscanf reads formatted data from the file. The format specifier %[^,], reads 
        characters up to the next comma (,) but does not include it. The ^ inside [^,] ensures all characters except the comma 
        are read, and the trailing , consumes the comma to move to the next field. This is ideal for parsing CSV files 
        where fields are separated by commas. The %d specifier reads integers after the comma-separated value.
        */

        // read the test data
        for (int i = 0; i < NUM_TEST_DATA; i++) {
        // read the animal name
        fscanf(file, "%[^,],", testData[i].animalName);

        // read the features
        for (int j = 0; j < NUM_FEATURES; j++) {
         fscanf(file, "%d,", &testData[i].features[j]);
        }

        // read the class label
        fscanf(file, "%d", &testData[i].classLabel);
        }

        // close file
        fclose(file);

        // loop through distance functions
        for (int distFunc = 1; distFunc <= 3; distFunc++) {
          // print test data (features and class labels)
          for (int i = 0; i < NUM_TEST_DATA; i++) {
            // print features
            for (int j = 0; j < NUM_FEATURES; j++) {
              printf("%d ", testData[i].features[j]);
            }

            // newline
            printf("\n");

            // print class label
            printf("%d\n", testData[i].classLabel);
          }

          // call findAccuracy function
          accuracy = findAccuracy(dataZoo, distFunc, testData, k);

          // print the accuracy for the current distance function
          printf("the accuracy for the test data is: %.6f\n", accuracy);
        }

        // break
        break;
    }
  } while (choice >= 1 && choice <= 5);

  return 0;
}
