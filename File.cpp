#include <iostream>
#include "File.h"
#include "Utils.h"

File::File(const char *name, const char *content, const Right *accessRights,
           unsigned creationDay, unsigned creationMonth, unsigned creationYear,
           unsigned creationTimeHours, unsigned creationTimeMins, unsigned creationTimeSecs)
{
    int contentSize = myStrLen(content);

    if (myStrLen(name) > MAX_NAME_SIZE ||
        contentSize > MAX_CONTENT_SIZE)
    {
        File();
    }

    this->creationTime = DateTime(creationDay, creationMonth, creationYear,
                                  creationTimeHours, creationTimeMins, creationTimeSecs);

    myStrCpy(this->name, name);
    setContent(content);

    setAccessRights(accessRights);

    this->sizeInBytes = contentSize;
}

void File::setAccessRights(const Right *rights)
{
    for (int i = 0; i < ACCESS_RIGHTS_STR_SIZE; ++i)
    {
        this->accessRights[i] = rights[i];
    }
};

int File::getSize() const
{
    return this->sizeInBytes;
}

const char *File::getName() const
{
    return this->name;
}

const char *File::getContent() const
{
    return this->content;
}

void File::setContent(const char *newContent)
{

    if (newContent && myStrLen(newContent) <= MAX_CONTENT_SIZE)
    {
        this->sizeInBytes = myStrLen(newContent);
        myStrCpy(this->content, newContent);
    }
}

void File::appendContent(const char *newContent)
{

    if (newContent && myStrLen(newContent) + this->sizeInBytes <= MAX_CONTENT_SIZE)
    {
        myStrCpy(this->content, newContent, this->sizeInBytes);
        this->sizeInBytes += myStrLen(newContent);
    }
}

void File::printCreationTime() const
{
    this->creationTime.print();
}

void File::printLastModified() const
{
    this->lastModified.print();
}

void File::setLastModified(unsigned day, unsigned month, unsigned year,
                           unsigned hours, unsigned mins, unsigned secs)
{
    this->lastModified = DateTime(day, month, year, hours, mins, secs);
}

bool File::hasRight(Group group, Right right) const
{
    int index = 0;
    switch (group)
    {
    case Group::author:
        index = 0;
        break;
    case Group::user:
        index = 3;
        break;
    case Group::other:
        index = 6;
        break;
    }

    switch (right)
    {
    case Right::read:
        return this->accessRights[index] == Right::read;
    case Right::write:
        return this->accessRights[index + 1] == Right::write;
    case Right::execute:
        return this->accessRights[index + 2] == Right::execute;
    }

    return false;
}
