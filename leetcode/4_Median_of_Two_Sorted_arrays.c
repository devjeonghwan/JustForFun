double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int totalSize = nums1Size + nums2Size;
    int medianIndex = totalSize / 2;

    int index1 = 0;
    int index2 = 0;

    double last1 = 0;
    double last2 = 0;

    for (int index = 0; index <= medianIndex; index++)
    {
        if ((index1 < nums1Size) && (index2 >= nums2Size || nums1[index1] < nums2[index2]))
        {
            last2 = last1;
            last1 = nums1[index1];
            index1++;
        }
        else
        {
            last2 = last1;
            last1 = nums2[index2];
            index2++;
        }
    }

    if (totalSize % 2 == 0)
    {
        return (last1 + last2) / 2.0;
    }

    return last1;
}