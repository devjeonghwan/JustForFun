typedef struct
{
    int **triplets;
    int *sizes;
    int size;
    int capacity;
} TripletArrayList;

inline void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void SortQuickly(int *array, int size)
{
    int *stack = (int *)malloc(sizeof(int) * size * 2);
    int top = -1;

    int lowIndex = 0;
    int highIndex = size - 1;

    stack[++top] = lowIndex;
    stack[++top] = highIndex;

    while (top >= 0)
    {
        highIndex = stack[top--];
        lowIndex = stack[top--];

        int pivot = array[highIndex];
        int leftIndex = lowIndex;

        for (int rightIndex = lowIndex; rightIndex < highIndex; rightIndex++)
        {
            if (array[rightIndex] < pivot)
            {
                Swap(&array[leftIndex], &array[rightIndex]);
                leftIndex++;
            }
        }

        Swap(&array[leftIndex], &array[highIndex]);

        if (lowIndex < leftIndex - 1)
        {
            stack[++top] = lowIndex;
            stack[++top] = leftIndex - 1;
        }

        if (leftIndex + 1 < highIndex)
        {
            stack[++top] = leftIndex + 1;
            stack[++top] = highIndex;
        }
    }

    free(stack);
}

void InitializeTripletArrayList(TripletArrayList *tripletArrayList, int capacity)
{
    tripletArrayList->size = 0;
    tripletArrayList->capacity = capacity;
    tripletArrayList->triplets = (int **)malloc(sizeof(int *) * capacity);
    tripletArrayList->sizes = (int *)malloc(sizeof(int) * capacity);
}

void DestroyTripletArrayList(TripletArrayList *tripletArrayList)
{
    free(tripletArrayList->sizes);
    tripletArrayList->sizes = NULL;

    for (int index = 0; index < tripletArrayList->size; index++)
    {
        free(tripletArrayList->triplets[index]);
        tripletArrayList->triplets[index] = NULL;
    }

    free(tripletArrayList->triplets);
    tripletArrayList->triplets = NULL;
}

void AddTriplet(TripletArrayList *tripletArrayList, int triple1, int triple2, int triple3)
{
    if (tripletArrayList->size == tripletArrayList->capacity)
    {
        tripletArrayList->capacity *= 2;

        int **newTriplets = (int **)realloc(tripletArrayList->triplets, sizeof(int *) * tripletArrayList->capacity);
        int *newSizes = (int *)realloc(tripletArrayList->sizes, sizeof(int) * tripletArrayList->capacity);

        tripletArrayList->triplets = newTriplets;
        tripletArrayList->sizes = newSizes;
    }

    int *tripleCopy = (int *)malloc(sizeof(int) * 3);

    tripleCopy[0] = triple1;
    tripleCopy[1] = triple2;
    tripleCopy[2] = triple3;

    tripletArrayList->triplets[tripletArrayList->size] = tripleCopy;
    tripletArrayList->sizes[tripletArrayList->size] = 3;
    tripletArrayList->size++;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    SortQuickly(nums, numsSize);

    TripletArrayList tripletArrayList;

    InitializeTripletArrayList(&tripletArrayList, numsSize * 2);

    int lowIndex = 0;
    int highIndex = numsSize - 1;

    while (lowIndex < highIndex - 1 && nums[lowIndex] <= 0)
    {
        int minValue = nums[lowIndex] + nums[lowIndex + 1] + nums[highIndex];
        int maxValue = nums[lowIndex] + nums[highIndex - 1] + nums[highIndex];

        if (minValue > 0)
        {
            highIndex -= 1;
        }
        else if (maxValue < 0)
        {
            lowIndex += 1;
        }
        else
        {
            int correct = nums[lowIndex];
            int leftIndex = lowIndex + 1;
            int rightIndex = highIndex;

            while (leftIndex < rightIndex)
            {
                int sum = nums[leftIndex] + nums[rightIndex] + correct;

                if (sum < 0)
                {
                    leftIndex++;
                }
                else if (sum > 0)
                {
                    rightIndex--;
                }
                else
                {
                    AddTriplet(&tripletArrayList, correct, nums[leftIndex], nums[rightIndex]);

                    do
                    {
                        leftIndex++;
                    } while (leftIndex < rightIndex && nums[leftIndex] == nums[leftIndex - 1]);

                    do
                    {
                        rightIndex--;
                    } while (leftIndex < rightIndex && nums[rightIndex] == nums[rightIndex + 1]);
                }
            }

            do
            {
                lowIndex++;
            } while (lowIndex < highIndex && nums[lowIndex] == nums[lowIndex - 1]);
        }
    }

    *returnSize = tripletArrayList.size;
    *returnColumnSizes = tripletArrayList.sizes;

    return tripletArrayList.triplets;
}