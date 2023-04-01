#include <iostream>
#include "File.h"
#include "Utils.h"

// Public methods follow
File::File(const char *name, const Right *accessRights,
           unsigned creationDay, unsigned creationMonth, unsigned creationYear,
           unsigned creationTimeHours, unsigned creationTimeMins, unsigned creationTimeSecs)
{
    int contentSize = myStrLen(content);

    if (myStrLen(name) > MAX_NAME_SIZE ||
        contentSize > MAX_CONTENT_SIZE)
    {
        File();
    }

    setCreationTime(creationDay, creationMonth, creationYear,
                    creationTimeHours, creationTimeMins, creationTimeSecs);

    setLastModified(creationDay, creationMonth, creationYear,
                    creationTimeHours, creationTimeMins, creationTimeSecs);

    setName(name);
    setContent("");
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

const DateTime &File::getLastModified() const
{
    return this->lastModified;
}

const DateTime &File::getCreationTime() const
{
    return this->creationTime;
}

void File::setName(const char *name)
{
    if (!name)
    {
        return;
    }

    myStrCpy(this->name, name);
}

bool File::setContent(const char *newContent)
{
    if (!newContent || myStrLen(newContent) > MAX_CONTENT_SIZE)
    {
        return false;
    }

    this->sizeInBytes = myStrLen(newContent);
    this->lastModified = lastModified;
    myStrCpy(this->content, newContent);

    return true;
}

bool File::appendContent(const char *newContent)
{
    if (!newContent || myStrLen(newContent) + this->sizeInBytes > MAX_CONTENT_SIZE)
    {
        return false;
    }

    myStrCpy(this->content, newContent, this->sizeInBytes);
    this->lastModified = lastModified;
    this->sizeInBytes += myStrLen(newContent);

    return true;
}

void File::printCreationTime() const
{
    this->creationTime.print();
}

void File::printLastModified() const
{
    this->lastModified.print();
}

void File::setCreationTime(unsigned day, unsigned month, unsigned year,
                           unsigned hours, unsigned mins, unsigned secs)
{
    this->creationTime = DateTime(day, month, year, hours, mins, secs);
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
