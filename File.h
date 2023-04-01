#include "constants.h"
#include "DateTime.h"

enum class Group
{
    user,
    author,
    other,
};

enum class Right
{
    read,
    write,
    execute,
    none,
};

class File
{
    DateTime creationTime;
    DateTime lastModified;

    char content[MAX_CONTENT_SIZE + 1] = {'\0'};
    char name[MAX_NAME_SIZE + 1] = {'\0'};

    Right accessRights[ACCESS_RIGHTS_STR_SIZE + 1] = {Right::none};

    int sizeInBytes;

public:
    File() = default;

    File(const char *name, const Right *accessRights,
         unsigned creationDay, unsigned creationMonth, unsigned creationYear,
         unsigned creationTimeHours, unsigned creationTimeMins, unsigned creationTimeSecs);

    int getSize() const;
    const char *getName() const;
    const char *getContent() const;
    const DateTime &getLastModified() const;
    const DateTime &getCreationTime() const;

    bool setContent(const char *content);
    bool appendContent(const char *content);

    void setLastModified(unsigned day, unsigned month, unsigned year,
                         unsigned hours, unsigned mins, unsigned secs);
    void setAccessRights(const Right *rights);

    void printCreationTime() const;
    void printLastModified() const;

    bool hasRight(Group group, Right right) const;

private:
    void setName(const char *name);
    void setCreationTime(unsigned creationDay, unsigned creationMonth, unsigned creationYear,
                         unsigned creationTimeHours, unsigned creationTimeMins, unsigned creationTimeSecs);
};