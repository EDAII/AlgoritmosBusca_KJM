#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int low = 0, high = numsSize - 1;

    while (low <= high && target >= nums[low] && target <= nums[high]) {
        if (low == high) {
            if (nums[low] == target) return low;
            return -1;
        }

        double ratio = (double)(target - nums[low]) / (nums[high] - nums[low]);
        int middle = low + (int)((high - low) * ratio);
        
        if (nums[middle] == target) return middle;
        if (nums[middle] < target) low = middle + 1;
        else high = middle - 1;
    }
    return -1;
}