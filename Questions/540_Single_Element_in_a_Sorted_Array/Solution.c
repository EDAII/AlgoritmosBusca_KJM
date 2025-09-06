#include <stdio.h>

int singleNonDuplicate(int* nums, int numsSize) {
    int left = 0, right = numsSize - 1;

    while (left < right) {
        int middle = left + ((right - left) / 2) & ~1;

        if (nums[middle] == nums[middle + 1]) {
            left = middle + 2;
        } else {
            right = middle;
        }
    }

    return nums[left];
}