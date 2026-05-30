#include "../include/DiskImageManager.h"
#include <iostream>

// Constructor: Variables ko initialize karta hai
DiskImageManager::DiskImageManager(std::string path, size_t sectorSz) 
    : imagePath(path), sectorSize(sectorSz) {}

// Destructor: Make sure file automatically close ho jaye jab object destroy ho
DiskImageManager::~DiskImageManager() {
    closeDisk();
}

// Disk image ko binary mode mein open karna
bool DiskImageManager::openDisk() {
    diskFile.open(imagePath, std::ios::binary);
    if (!diskFile.is_open()) {
        std::cerr << "[ERROR] Could not open disk image -> " << imagePath << std::endl;
        return false;
    }
    return true;
}

// Disk image ko close karna
void DiskImageManager::closeDisk() {
    if (diskFile.is_open()) {
        diskFile.close();
    }
}

// Check karna ke disk currently open hai ya nahi
bool DiskImageManager::isDiskOpen() const {
    return diskFile.is_open();
}

// Specific sector ko read karna aur bytes return karna
std::vector<char> DiskImageManager::readSector(int sectorNumber) {
    std::vector<char> buffer(sectorSize, 0); // Buffer ko zero se initialize kiya
    
    if (!isDiskOpen()) {
        std::cerr << "[ERROR] Disk is not open! Cannot read sector." << std::endl;
        return buffer; // Empty buffer return hoga
    }

    // Exact byte position calculate karna
    std::streampos position = static_cast<std::streampos>(sectorNumber) * sectorSize;
    
    // File pointer ko us position par le jana
    diskFile.seekg(position);
    if (!diskFile) {
        std::cerr << "[ERROR] Could not seek to sector " << sectorNumber << std::endl;
        return buffer;
    }

    // Sector ka data read karke buffer mein dalna
    diskFile.read(buffer.data(), sectorSize);
    if (!diskFile) {
        std::cerr << "[ERROR] Could not read data from sector " << sectorNumber << std::endl;
    }

    return buffer;
}