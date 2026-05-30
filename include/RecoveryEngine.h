#ifndef RECOVERYENGINE_H
#define RECOVERYENGINE_H

#include "IFileSystem.h"
#include "DiskImageManager.h"
#include <string>

class RecoveryEngine {
private:
    IFileSystem* fileSystem;
    DiskImageManager& diskManager;

public:
    // Constructor
    RecoveryEngine(IFileSystem* fs, DiskImageManager& disk);

    // File recover function
    bool recoverFile(const FileRecord& file, const std::string& outputDir);
};

#endif // RECOVERYENGINE_H