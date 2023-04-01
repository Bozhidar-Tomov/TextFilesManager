#include "FileSystem.h"
#include "Utils.h"
#include "constants.h"

// No member functions follow
bool compareFiles(const File &a, const File &b, SortBy sortBy)
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

// private methods follow
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

void FileSystem::copyFiles(const File *newFiles, int filesCount)
{
    for (int i = 0; i < filesCount; ++i)
    {
        this->files[i] = newFiles[i];
    }

    this->size = filesCount;
}

void FileSystem::copyFrom(const FileSystem &other)
{
    copyFiles(other.files, other.size);
}

void FileSystem::free()
{
    delete[] files;

    files = nullptr;
    size = 0;
}
// end of private methods

// Public methods follow

// Big 4
FileSystem::FileSystem(int capacity)
{
    this->capacity = capacity;
    this->files = new File[capacity];
    this->size = 0;
}

FileSystem::FileSystem(const FileSystem &other)
{
    copyFrom(other);
}

FileSystem &FileSystem::operator=(const FileSystem &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

FileSystem::~FileSystem()
{
    free();
}
// end of Big 4

// custom methods
void FileSystem::createEmpty(const char *fileName,
                             unsigned hours, unsigned mins, unsigned secs,
                             unsigned day, unsigned month, unsigned year,
                             const Right *accessRights)
{
    if (!fileName)
    {
        std::cout << "Cannot create file. Name is not valid." << std::endl;
        return;
    }

    if (this->size >= capacity)
    {
        std::cout << "Cannot create file " << fileName << ". Max number of files (" << this->capacity << ") exceeded." << std::endl;
        return;
    }

    this->files[size++] = File(fileName, accessRights, day, month, year, hours, mins, secs);
}

void FileSystem::editFile(const char *fileName, const char *newContent,
                          unsigned hours, unsigned mins, unsigned secs,
                          unsigned day, unsigned month, unsigned year,
                          Group group, bool append)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) != 0)
        {
            continue;
        }

        if (!this->files[i].hasRight(group, Right::write))
        {
            std::cout << "You do not have the rights to edit this file." << std::endl;
            return;
        }

        if (append)
        {
            if (!this->files[i].appendContent(newContent))
            {
                std::cout << "Cannot append to file. Content max size exceeded." << std::endl;
                return;
            };
        }
        else
        {
            if (!this->files[i].setContent(newContent))
            {
                std::cout << "Cannot set file content. Content max size exceeded." << std::endl;
                return;
            };
        }

        this->files[i].setLastModified(day, month, year, hours, mins, secs);
        return;
    }
    std::cout << "File " << fileName << " not found." << std::endl;
}

void FileSystem::deleteFile(const char *fileName)
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) == 0)
        {
            this->files[i] = this->files[--this->size];
            return;
        }
    }
    std::cout << "File " << fileName << " not found." << std::endl;
}

void FileSystem::printFileInfo(const char *fileName, Group group) const
{
    for (int i = 0; i < this->size; ++i)
    {
        if (myStrCmp(this->files[i].getName(), fileName) != 0)
            continue;

        if (!this->files[i].hasRight(group, Right::read))
        {
            std::cout << "You do not have rights to view this file." << std::endl;
            return;
        }

        std::cout << "File name: " << this->files[i].getName() << std::endl;

        std::cout << "Created on: ";
        this->files[i].printCreationTime();
        std::cout << std::endl;

        std::cout << "Last modified on: ";
        this->files[i].printLastModified();
        std::cout << std::endl;

        std::cout << "Content: " << this->files[i].getContent() << std::endl;

        std::cout << std::endl;

        return;
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
        if (myStrCmp(this->files[i].getName(), fileName) != 0)
            continue;

        if (!this->files[i].hasRight(group, Right::execute))
        {
            std::cout << "Error: You do not have permission to execute changes to the file information!" << std::endl;
            return;
        }

        this->files[i].setAccessRights(accessRights);
        return;
    }
    std::cout << "Error: File " << fileName << " not found." << std::endl;
}

void FileSystem::swapFiles(int i, int j)
{
    File temp = this->files[i];

    this->files[i] = this->files[j];
    this->files[j] = temp;
}
