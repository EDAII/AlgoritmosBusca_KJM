#include <stdio.h>
#include <math.h>

int searchInsert(int* nums, int numsSize, int target) {
    int step = (int)sqrt(numsSize);
    int i = 0;

    while (i < numsSize && nums[(int)fmin(i + step - 1, numsSize - 1)] < target) {
        i += step;
    }
    for (; i < numsSize; i++) {
        if (nums[i] >= target) {
            return i;
        }
    }
    return numsSize;
}