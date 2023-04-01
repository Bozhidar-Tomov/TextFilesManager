#include "File.h"

enum class SortBy
{
    name,
    creationTime,
    lastModified,
    size,
};
class FileSystem
{
    File *files = nullptr;

    int capacity = 0;
    int size = 0;

public:
    FileSystem(int capacity);
    FileSystem(const FileSystem &other);
    FileSystem &operator=(const FileSystem &other);
    ~FileSystem();

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

    void printFileInfo(const char *fileName, Group group) const;
    void printAll() const;
    void sortBy(SortBy sortBy);

private:
    void swapFiles(int, int);
    void copyFiles(const File *files, int filesCount);
    void copyFrom(const FileSystem &other);
    void free();
};