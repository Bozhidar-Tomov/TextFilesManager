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

    fileSystem.createEmpty("a.txt", 8, 8, 8, 8, 8, 2008, rights);
    fileSystem.createEmpty("c.txt", 7, 7, 7, 7, 7, 2007, rights);
    fileSystem.createEmpty("b.txt", 6, 6, 6, 6, 6, 2006, rights);
    fileSystem.createEmpty("d.txt", 10, 10, 10, 10, 10, 2015, rights);
    fileSystem.createEmpty("f.txt", 9, 9, 9, 9, 9, 2009, rights);

    fileSystem.printFileInfo("a.txt", Group::author);
    fileSystem.editFile("a.txt", "HELLO", 14, 30, 0, 20, 3, 2023, Group::author);
    fileSystem.printFileInfo("a.txt", Group::author);

    fileSystem.sortBy(SortBy::creationTime);

    fileSystem.printAll();

    int stor = 9;
}