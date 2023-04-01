#include "FileSystem.h"
#include "Utils.h"
#include "constants.h"

FileSystem::FileSystem(int capacity)
{
    this->capacity = capacity;
    this->files = new File[capacity];
    this->size = 0;
}

void FileSystem::createEmpty(const char *fileName,
                             unsigned hours, unsigned mins, unsigned secs,
                             unsigned day, unsigned month, unsigned year,
                             const Right *accessRights)
{
    if (this->size >= capacity)
    {
        return;
    }

    this->files[size++] = File(fileName, "", accessRights, day, month, year, hours, mins, secs);
}

void FileSystem::editFile(const char *fileName, const char *newContent,
                          unsigned hours, unsigned mins, unsigned secs,
                          unsigned day, unsigned month, unsigned year,
                          Group group, bool append)
{

    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0 && this->files[i].hasRight(group, Right::write))
        {
            if (append)
            {
                this->files[i].appendContent(newContent);
            }
            else
            {
                this->files[i].setContent(newContent);
            }
            this->files[i].setLastModified(day, month, year, hours, mins, secs);
        }
    }
}

void FileSystem::deleteFile(const char *fileName)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0)
        {
            this->files[i] = this->files[--this->size];
        }
    }
}

void FileSystem::printFileContent(const char *fileName, Group group)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0 && this->files[i].hasRight(group, Right::write))
        {
        }
    }
}

void FileSystem::printFileInfo(const char *fileName, Group group)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0 && this->files[i].hasRight(group, Right::read))
        {
            std::cout << "File name: " << this->files[i].getName() << std::endl;

            std::cout << "Created on: ";
            this->files[i].printCreationTime();
            std::cout << std::endl;

            std::cout << "Last modified on: ";
            this->files[i].printCreationTime();
            std::cout << std::endl;

            std::cout << "Content: " << this->files[i].getContent() << std::endl;

            std::cout << std::endl;

            return;
        }
    }
    std::cout << "File " << fileName << " not found." << std::endl;
}

void FileSystem::printAll() const
{
    std::cout << "Available files:" << std::endl;

    for (int i = 0; i < this->size; ++i)
    {
        std::cout << this->files[i].getName() << std::endl;
    }
    std::cout << std::endl;
}

void FileSystem::changeFileAccessRights(const char *fileName, const Right *accessRights, Group group)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0)
        {
            if (this->files[i].hasRight(group, Right::execute))
            {
                this->files[i].setAccessRights(accessRights);
            }
            else
            {
                std::cout << "Error, you do not have permission to execute changes to the file information!" << std::endl;
            }
            return;
        }
    }
}

void FileSystem::swapFiles(int i, int j)
{
    File temp = this->files[i];

    this->files[i] = this->files[j];
    this->files[j] = temp;
}

bool FileSystem::compareFiles(const File &a, const File &b, SortBy sortBy) const
{
    if (sortBy == SortBy::creationTime)
    {
        return a.getCreationTime() < b.getCreationTime();
    }
    if (sortBy == SortBy::lastModified)
    {
        return a.getLastModified() < b.getLastModified();
    }
    if (sortBy == SortBy::name)
    {
        return myStrCmp(a.getName(), b.getName()) < 0;
    }
    if (sortBy == SortBy::size)
    {
        return a.getSize() < b.getSize();
    }

    return false;
}

void FileSystem::sortBy(SortBy sortBy)
{

    for (int i = 0; i < this->size - 1; ++i)
    {
        int smallestIdx = i;

        for (int j = i + 1; j < this->size; ++j)
        {
            if (compareFiles(this->files[j], this->files[smallestIdx], sortBy))
            {
                smallestIdx = j;
            }
        }

        if (i != smallestIdx)
        {
            swapFiles(i, smallestIdx);
        }
    }
}
