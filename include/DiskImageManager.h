#ifndef DISKIMAGEMANAGER_H
#define DISKIMAGEMANAGER_H

#include <string>
#include <fstream>
#include <vector>

class DiskImageManager {
private:
    std::string imagePath;     // Disk image ka path
    std::ifstream diskFile;    // File read karne ke liye stream
    size_t sectorSize;         // Ek sector ka size (Usually 512 bytes)

public:
    // Constructor & Destructor
    DiskImageManager(std::string path, size_t sectorSz = 512);
    ~DiskImageManager();

    // File Management Methods
    bool openDisk();
    void closeDisk();
    bool isDiskOpen() const;
    
    // Core Method: Kisi bhi specific sector ko read karna
    std::vector<char> readSector(int sectorNumber);
};

#endif // DISKIMAGEMANAGER_H