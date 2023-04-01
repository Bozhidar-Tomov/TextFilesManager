#include <iostream>

void myStrCpy(char *destination, const char *source, int startIdx = 0)
{
    if (!destination || !source)
    {
        return;
    }

    int idx = 0;

    while (source[idx] != '\0')
    {
        destination[startIdx] = source[idx];
        ++startIdx;
        ++idx;
    }
    destination[startIdx] = '\0';
}

int myStrLen(const char *str)
{
    const char *s = str;

    while (*s)
    {
        ++s;
    }

    return (s - str);
}

/*
Here we allocate memory - titleCapacity*sizeof(char) bytes in heap and 4 bytes in the stack for the pointer.
Then we delete the stuff in the heap that title points to.
Then we make title to point to the content that new title points at the heap. now both pointers point to the same memory in heap.
At the end of the scope new title dies and title points to the new arr.
We pass the pointer as reference and not as copy so that after the function call title points to the new memory
*/
void resize(char *&title, int titleCapacity)
{
    char *newTitle = new char[titleCapacity];

    delete[] title;

    title = newTitle;
}

bool myStrCmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
    {
        return false;
    }
    while (*s1 && *s1 == *s2)
    {
        ++s1;
        ++s2;
    }
    return *s1 - *s2 == 0;
}

// only positive numbers!
int strToInt(const char *str)
{
    int x = 0;

    while (*str >= '0' && *str <= '9')
    {
        x = 10 * x + *str - '0';
        ++str;
    }

    return *str == '\0' ? x : -1;
}

void printStr(const char *str)
{
    if (!str)
    {
        return;
    }

    while (*str)
    {
        std::cout << *str++;
    }
}