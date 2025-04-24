
# easyML – Basic Machine Learning Classifier in C

This project is a C-based command-line program that implements a simple machine learning classifier using the **k-nearest neighbors (k-NN)** algorithm. The program can read structured data from files, compute distances between samples using multiple metrics, and predict classifications based on user-selected criteria.

## Features

- Reads a zoo dataset and test data in a structured format
- Implements distance metrics: Euclidean, Hamming, and Jaccard Similarity
- Predicts class labels using the k-NN algorithm
- Computes model accuracy on test datasets
- Provides a terminal-based menu interface

## Requirements

- GCC compiler (C99 standard)
- Make utility

## Build Instructions

To compile the project, run:

```bash
make
```

To clean up object files and executable:

```bash
make clean
```

## Run Instructions

```bash
./easyml
```

## About

This project was originally developed at the University of Guelph to help illustrate foundational programming and machine learning concepts in C. While it was built in an academic setting, it has been adapted for public sharing and broader learning.
