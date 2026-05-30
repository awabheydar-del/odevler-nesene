#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

#include <vector>
#include "FileRecord.h"

class IFileSystem {
public:
    // Virtual destructor zaroori hai memory leaks se bachne ke liye
    virtual ~IFileSystem() = default;

    // Pure virtual functions (Is interface ko inherit karne wali class inko implement karegi)
    virtual void scanForDeletedFiles() = 0;
    virtual std::vector<FileRecord> getDeletedFiles() const = 0;
};

#endif // IFILESYSTEM_H