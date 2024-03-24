#ifndef FILTERS_H
#define FILTERS_H

#define WINDOW_SIZE 100

const int SALT_THRESHOLD = 100;
const int PEPPER_THRESHOLD = 900;
const int SALT_VALUE = 0;
const int PEPPER_VALUE = 1023;
int saltAndPepperFilter(int analogVal);
int weightedAverageFilter(int analogValues[], float weights[]);
void updateWeights();

#endif
