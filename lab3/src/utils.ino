#include "utils.h"

float voltageToLux(float voltage) {
    float resistance = 2000 * voltage / (1 - voltage / 5);
    float lux = pow(RL10 * 1e3 * pow(10, GAMMA) / resistance, (1 / GAMMA));
    return lux;
}

void floatToString(float fVal, char *output) {
    int dVal, dec, i;
    bool isNegative = false;

    if (fVal < 0) {
        isNegative = true;
        fVal = -fVal;
    }

    fVal += 0.005;
    dVal = fVal;
    dec = (int)(fVal * 100) % 100;
    output[0] = (dec % 10) + '0';
    output[1] = (dec / 10) + '0';
    output[2] = '.';
    i = 3;
    while (dVal > 0) {
        output[i] = (dVal % 10) + '0';
        dVal /= 10;
        i++;
    }
    output[i] = '\0';

    int len = strlen(output);
    for (int j = 0; j < len / 2; j++) {
        char temp = output[j];
        output[j] = output[len - j - 1];
        output[len - j - 1] = temp;
    }

    if (isNegative) {
        for (int j = len + 1; j >= 0; j--) {
            output[j + 1] = output[j];
        }
        output[0] = '-';
    }
}
