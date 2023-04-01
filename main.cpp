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

    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.createEmpty("test.txt", 5, 5, 5, 5, 5, 2005, rights);
    fileSystem.editFile("test.txt", "NEW CONTENT", 6, 6, 6, 6, 6, 2006, Group::author);
    // fileSystem.createEmpty("raya.txt", 5, 5, 5, 5, 5, 2005, rights);
    // fileSystem.deleteFile("raya.txt");

    fileSystem.printFileInfo("test.txt", Group::author);
    fileSystem.printAll();

    int stor = 9;
}