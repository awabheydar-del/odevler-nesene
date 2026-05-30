#ifndef SIMULATEDFAT32_H
#define SIMULATEDFAT32_H

#include "IFileSystem.h"
#include "DiskImageManager.h"
#include <vector>

class SimulatedFAT32 : public IFileSystem {
private:
    DiskImageManager& diskManager; // DiskManager ka reference taake read kar sakein
    std::vector<FileRecord> deletedFiles;
    int rootDirSector; // Wo sector jahan directory entries hoti hain

    // Helper function: 32-byte block ko parse karne ke liye
    void parseDirectoryEntry(const std::vector<char>& entryBytes);

public:
    // Constructor
    SimulatedFAT32(DiskImageManager& manager, int rootSector = 1);
    
    // Interface methods ko override kar rahe hain
    void scanForDeletedFiles() override;
    std::vector<FileRecord> getDeletedFiles() const override;
};

#endif // SIMULATEDFAT32_H