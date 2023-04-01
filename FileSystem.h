#include "File.h"

class FileSystem
{
    File *files = nullptr;

    enum class SortBy
    {
        name,
        creationTime,
        lastModified,
        size,
    };

    int capacity = 0;
    int size = 0;

public:
    FileSystem(int capacity);

    void createEmpty(const char *fileName,
                     unsigned hours, unsigned mins, unsigned secs,
                     unsigned day, unsigned month, unsigned year,
                     const Right *accessRights);

    void editFile(const char *fileName, const char *newContent,
                  unsigned hours, unsigned mins, unsigned secs,
                  unsigned day, unsigned month, unsigned year,
                  Group group, bool append = false);

    void deleteFile(const char *fileName);

    void changeFileAccessRights(const char *fileName, const Right *accessRights, Group group);

    void printFileInfo(const char *fileName, Group group);
    void printFileContent(const char *fileName, Group userGroup);
    void printAll() const;
    void sort(SortBy sortBy);
};