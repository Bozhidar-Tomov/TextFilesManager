#include <iostream>
#include "FileSystem.h"

int main()
{
    FileSystem fileSystem(5);

    fileSystem.createEmpty("a.txt", 8, 8, 8, 8, 8, 2008, "wrxr---wx");
    fileSystem.createEmpty("c.txt", 7, 7, 7, 7, 7, 2007, "rwxr--r--");
    fileSystem.createEmpty("b.txt", 6, 6, 6, 6, 6, 2006, "rwxr--r--");
    fileSystem.createEmpty("d.txt", 10, 10, 10, 10, 10, 2015, "rwxr--r--");
    fileSystem.createEmpty("f.txt", 9, 9, 9, 9, 9, 2009, "rwxr--r--");

    fileSystem.printFileInfo("b.txt", Group::other);
    fileSystem.editFile("b.txt", "HELLO", 14, 30, 0, 20, 3, 2023, Group::author);
    fileSystem.deleteFile("c.txt");
    fileSystem.changeFileAccessRights("b.txt", "rwxr--r--", Group::other);
    fileSystem.printFileInfo("b.txt", Group::other);

    fileSystem.sortBy(SortBy::name);

    fileSystem.printAll();
}