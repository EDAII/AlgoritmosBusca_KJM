#include <stdio.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        int* tempArr = nums1; nums1 = nums2; nums2 = tempArr;
        int tempSize = nums1Size; nums1Size = nums2Size; nums2Size = tempSize;
    }

    int total = nums1Size + nums2Size;
    int half = (total + 1) / 2;

    int left = 0, right = nums1Size;

    while (left <= right) {
        int nums1Middle = (left + right) / 2;
        int nums2Middle = half - nums1Middle;

        int nums1Left  = (nums1Middle == 0) ? -1000000 : nums1[nums1Middle - 1];
        int nums1Right = (nums1Middle == nums1Size) ? 1000000 : nums1[nums1Middle];

        int nums2Left  = (nums2Middle == 0) ? -1000000 : nums2[nums2Middle - 1];
        int nums2Right = (nums2Middle == nums2Size) ? 1000000 : nums2[nums2Middle];

        if (nums1Left <= nums2Right && nums2Left <= nums1Right) {
            if (total % 2 == 0) {
                int leftMax = nums1Left > nums2Left ? nums1Left : nums2Left;
                int rightMin = nums1Right < nums2Right ? nums1Right : nums2Right;
                return (leftMax + rightMin) / 2.0;
            } 
            else {
                int leftMax = nums1Left > nums2Left ? nums1Left : nums2Left;
                return leftMax;
            }
        }
        else if (nums1Left > nums2Right) right = nums1Middle - 1;
        else left = nums1Middle + 1;
    }
    return 0.0;
}