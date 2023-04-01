// Compiler - GCC
// author - Bozhidar Tomov 0MI0600171

#include <iostream>
#include "FileSystem.h"

int main()
{
    FileSystem fileSystem(5);

    fileSystem.createEmpty("a.txt", 8, 8, 8, 8, 8, 2008, "rwxr---wx");      // invalid input (accessRights)
    fileSystem.createEmpty("c.txt", 7, 7, 7, 7, 7, 2007, "rwxr--r--");      // successful task
    fileSystem.createEmpty("b.txt", 6, 6, 6, 6, 6, 2006, "rwxr--r--");      // successful task
    fileSystem.createEmpty("d.txt", 10, 10, 10, 10, 10, 2015, "rwxr--r--"); // successful task
    fileSystem.createEmpty(nullptr, 9, 9, 9, 9, 9, 2009, "rwxr--r--");      // invalid input
    fileSystem.createEmpty("f.txt", 9, 9, 9, 9, 9, 2009, "rwxr--r--");      // successful task
    fileSystem.createEmpty("z.txt", 9, 9, 9, 9, 9, 2009, "rwxr--r--");      // fail task. Max capacity reached

    fileSystem.printFileInfo("b.txt", Group::author); // successful task

    fileSystem.editFile("b.txt", "HELLO", 14, 30, 0, 20, 3, 2023, Group::author); // successful task

    fileSystem.deleteFile("c.txt"); // successful task

    fileSystem.changeFileAccessRights("b.txt", "rwxr--r--", Group::other); // fail task. No execute rights.
    fileSystem.printFileInfo("b.txt", Group::other);                       // successful task

    fileSystem.sortBy(SortBy::name); // successful task
    fileSystem.printAll();           // successful task
}