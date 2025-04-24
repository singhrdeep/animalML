#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "given.h"

/* Call structs */
struct Animal dataZoo[NUM_SAMPLES];
struct Animal testData[NUM_TEST_DATA];

/* Tasks */

/* Task 1 */
int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES]) {
  // open file
  FILE *file = fopen(fName, "r");

  // check if the file opened successfully
  if (file == NULL) {
    printf("Error opening file\n");
    return -1;
  }

  // for loop to read the animalName, features, and classlabel
  for (int i = 0; i < NUM_SAMPLES; i++) {
    // read the animal name
    fscanf(file, "%s", dataZoo[i].animalName);

    // read the features
    for (int j = 0; j < NUM_FEATURES; j++) {
      fscanf(file, "%d", &dataZoo[i].features[j]);
    }

    // read the class label
    fscanf(file, "%d", &dataZoo[i].classLabel);
  }

  // print the data 
  for (int i = 0; i < NUM_SAMPLES; i++) {
    // print animal name
    printf("%s ", dataZoo[i].animalName);

    // print features
    for (int j = 0; j < NUM_FEATURES; j++) {
      printf("%d ", dataZoo[i].features[j]);
    }

    // print class label
    printf("%d\n", dataZoo[i].classLabel);
  }

  // close file
  fclose(file);

  // return 1
  return 1;
}

/* Task 2 */
void distanceFunctions(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES], float *euclideanDistance, int *hammingDistance, float *jaccardSimilarity) {
  // declare and initialize variables for euclideanDistance
  int difference = 0;    // variable for the difference between corresponding features
  double eucDist = 0;    // variable to store the computed euclidean distance before sqrt

  // declare and initialize variables for hammingDistance
  int hammingCount = 0;  // variable to count the number of mismatches between vector1 and vector2

  // declare and initialize variables for jaccardSimilarity
  int oneToOneMatches = 0;   // variable to store the number of 1-1 matches
  int mismatches = 0;        // variable to store the number of mismatched features (1-0 or 0-1 cases)
  int denominator = 0;       // variable to store the denominator for Jaccard similarity
  float jacSim = 0;          // variable to store the computed Jaccard similarity

  // calculate the euclideanDistance
  for (int i = 0; i < NUM_FEATURES; i++) {
    // calculate the difference between corresponding features
    difference = vector1[i] - vector2[i];

    // add the square of the difference to the sum
    eucDist += difference * difference;
  }

  // take the square root of the sum to compute the final euclidean distance
  *euclideanDistance = sqrt(eucDist);

  // calculate the hammingDistance
  for (int i = 0; i < NUM_FEATURES; i++) {
    // increment the count if the features in vector1 and vector2 do not match
    if (vector1[i] != vector2[i]) {
      hammingCount++;
    }
  }

  // store the computed hamming distance
  *hammingDistance = hammingCount;

  // calculate the jaccardSimilarity
  for (int i = 0; i < NUM_FEATURES; i++) {
    // increment the count of 1-1 matches
    if (vector1[i] == 1 && vector2[i] == 1) {
      oneToOneMatches++;
    }
    // increment the count of mismatches (1-0 or 0-1)
    else if (vector1[i] != vector2[i]) {
      mismatches++;
    }
  }

  // calculate the denominator for Jaccard similarity
  denominator = oneToOneMatches + mismatches;

  // compute the jaccard similarity 
  if (denominator > 0) {
    jacSim = (float)oneToOneMatches / denominator;
  } 

  // store the computed jaccard similarity
  *jaccardSimilarity = jacSim;
}

/* Task 3 */
void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]) {
  // declare and initialize arrays for distance and sample data
  float distanceData[NUM_SAMPLES];
  int sampleData[NUM_SAMPLES];

  // declare and initialize variables to store distances
  float euclideanDistance = 0;
  float jaccardSimilarity = 0;
  int hammingDistance = 0;

  for (int i = 0; i < NUM_SAMPLES; i++) {  // added loop for all samples
    // calculate the distances by calling distanceFunctions
    distanceFunctions(dataZoo[i].features, newSample, &euclideanDistance, &hammingDistance, &jaccardSimilarity);

    // store distances
    if (whichDistanceFunction == 1) {
      distanceData[i] = euclideanDistance;
    }

    else if (whichDistanceFunction == 2) {
      distanceData[i] = hammingDistance; 
    }

    else if (whichDistanceFunction == 3) {
      distanceData[i] = jaccardSimilarity;
    }

    // store samples into array
    sampleData[i] = i;
  }

  // sort indices using bubble sort
	/* algorithm from: https://www.geeksforgeeks.org/bubble-sort-algorithm/

	 Explanation: The bubble sort function sorts elements in an array by repeatedly
	 comparing adjacent elements and swapping them if they are out of order.
	 It continues this process in multiple passes until no swaps are needed,
	 ensuring the array is sorted. */
	 
    // declare swap variable
    int swapped;

    // outer loop to perform multiple passes through the array
    for (int i = 0; i < NUM_SAMPLES - 1; i++) {
    swapped = 0;  // reset the swapped variable

  // compare adjacent elements
  for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
    // check order based on the distance function
    // descending for jaccard similarity, ascending for others
    if ((whichDistanceFunction == 3 && distanceData[j] < distanceData[j + 1]) || (whichDistanceFunction != 3 && distanceData[j] > distanceData[j + 1])) {
      
      // swap distances
      float tempDist = distanceData[j];
      distanceData[j] = distanceData[j + 1];
      distanceData[j + 1] = tempDist;

      // swap indices
      int tempIndex = sampleData[j];
      sampleData[j] = sampleData[j + 1];
      sampleData[j + 1] = tempIndex;

      swapped = 1;  // mark that a swap occurred
    }
  }

  // if no swaps were made, the array is already sorted
  if (swapped == 0) {
    break;
  }
}

  // select k nearest neighbours
  for (int i = 0; i < k; i++) {
    kNearestNeighbors[i] = sampleData[i];
  }
}

/* Task 4 */
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int whichDistanceFunction, int k) {
  // declare an array to store the indices of the nearest neighbors
  int nearestNeighbors[NUM_SAMPLES];

  // declare an array to count the frequency of each class label
  int class[NUM_CLASSES] = {0};

  // declare variables to store the predicted class and the maximum frequency
  int predictedClass = 0, sum = 0;

  // call the function to find the k nearest neighbors
  findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, nearestNeighbors);

  // for loop to count the frequency of class labels among the nearest neighbors
  for (int i = 0; i < k; i++) {
    // get the class label of the current nearest neighbor
    int classNum = dataZoo[nearestNeighbors[i]].classLabel;

    // check boundary of classNum
    if (classNum >= 1 && classNum <= NUM_CLASSES) {
      // increment the frequency of the class label
      class[classNum - 1]++;
    } 
  }

  // for loop to find the class with the highest frequency
  for (int i = 0; i < NUM_CLASSES; i++) {
    // check if the class has higher frequency than the max 
    if (class[i] > sum) {
      // update the maximum frequency
      sum = class[i];
      // update the predicted class
      predictedClass = i + 1;
    } 
    
    // if two classes have the same frequency, choose the class with the smaller label
    else if (class[i] > sum || (class[i] == sum && (i + 1) < predictedClass)) {
        sum = class[i];
        predictedClass = i + 1;
    }
  }

  // return the predicted class
  return predictedClass;
}


/* Task 5 */
float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], int whichDistanceFunction, struct Animal testData[NUM_TEST_DATA], int k) {
  // declare variable to count the number of correct predictions
  int correctPredictions = 0;

  // for loop to test each sample in the test dataset
  for (int i = 0; i < NUM_TEST_DATA; i++) {
    // predict the class for the current test sample
    int predictedClass = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);

    // check if the predicted class matches the actual class label
    if (predictedClass == testData[i].classLabel) {
      // increment the count of correct predictions
      correctPredictions++;
    }
  }

  // calculate and return the accuracy as a float
  return (float)correctPredictions / NUM_TEST_DATA;
}
