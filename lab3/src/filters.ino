#include "filters.h"

int saltAndPepperFilter(int analogVal) {
    if (analogVal < SALT_THRESHOLD) {
        return SALT_VALUE;
    } else if (analogVal > PEPPER_THRESHOLD) {
        return PEPPER_VALUE;
    } else {
        return analogVal;
    }
}

int weightedAverageFilter(int analogValues[], float weights[]) {
    float sum = 0.0;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        sum += analogValues[i] * weights[i];
    }
    return int(sum);
}

void updateWeights() {
    for (int i = 0; i < WINDOW_SIZE; i++) {
        weights[i] = 1.0 / WINDOW_SIZE;
    }
}
