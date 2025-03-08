int lengthOfLongestSubstring(char *s)
{
    int lastIndexMap[128] = {0};
    int index = 0;
    int anchor = 1;
    int maxLength = 0;

    while (s[index] != '\0')
    {
        if (lastIndexMap[s[index]] != 0 && lastIndexMap[s[index]] >= anchor)
        {
            anchor = lastIndexMap[s[index]] + 1;
        }

        int length = (index + 1) - anchor + 1;

        if (maxLength < length)
            maxLength = length;

        lastIndexMap[s[index]] = index + 1;
        index++;
    }

    return maxLength;
}