#define MAX_DIGITS 18
#define CARRY_CHECK 1000000000000000000
const uint64_t DIGITS[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000,
    100000000000,
    1000000000000,
    10000000000000,
    100000000000000,
    1000000000000000,
    10000000000000000,
    100000000000000000,
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* result = NULL; 
    struct ListNode* last = NULL;

    uint64_t number1 = 0;
    int digit1 = 0;

    uint64_t number2 = 0;
    int digit2 = 0;

    while (l1 != NULL || l2 != NULL)
    {
        if (l1 != NULL)
        {
            number1 += l1->val * DIGITS[digit1];
            l1 = l1->next;
            digit1++;
        }

        if (l2 != NULL)
        {
            number2 += l2->val * DIGITS[digit2];
            l2 = l2->next;
            digit2++;
        }

        bool endOfList = l1 == NULL && l2 == NULL;

        if (digit1 == MAX_DIGITS || digit2 == MAX_DIGITS || endOfList)
        {
            uint64_t sum = number1 + number2;
            int increaseDigit = digit1 > digit2 ? digit1 : digit2;
            bool carried = sum >= CARRY_CHECK && !endOfList;

            if (carried)
            {
                sum -= CARRY_CHECK;
            }

            number1 = carried ? 1 : 0;
            digit1 = 0;

            number2 = 0;
            digit2 = 0;

            for (int i = 0; i < increaseDigit || sum; i++)
            {
                struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));

                newNode->val = (sum % 10);
                newNode->next = NULL;
                sum /= 10;

                if (result == NULL) result = newNode;
                if (last != NULL) last->next = newNode;

                last = newNode;
            }
        }
    }

    return result;
}