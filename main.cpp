#include <iostream>
#include "FileSystem.h"

int main()
{
    FileSystem fileSystem(5);
    Right rights[9] = {
        Right::read,
        Right::write,
        Right::execute,
        Right::read,
        Right::none,
        Right::none,
        Right::read,
        Right::none,
        Right::none,
    };

    fileSystem.createEmpty("v.txt", 8, 8, 8, 8, 8, 2008, rights);
    fileSystem.createEmpty("r.txt", 6, 6, 6, 6, 6, 2006, rights);
    fileSystem.createEmpty("f.txt", 7, 7, 7, 7, 7, 2007, rights);
    fileSystem.createEmpty("k.txt", 10, 10, 10, 10, 10, 2015, rights);
    fileSystem.createEmpty("a.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("f.txt", 9, 9, 9, 9, 9, 2009, rights);

    fileSystem.sortBy(SortBy::creationTime);
    fileSystem.printAll();

    fileSystem.sortBy(SortBy::name);
    fileSystem.printAll();

    int stor = 9;
}