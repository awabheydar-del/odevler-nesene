#include "../include/SimulatedFAT32.h"
#include <iostream>

// Constructor
SimulatedFAT32::SimulatedFAT32(DiskImageManager& manager, int rootSector)
    : diskManager(manager), rootDirSector(rootSector) {}

// Scanning Logic
void SimulatedFAT32::scanForDeletedFiles() {
    std::cout << "[FAT32] Scanning for deleted files in Sector " << rootDirSector << "...\n";
    deletedFiles.clear();

    if (!diskManager.isDiskOpen()) {
        std::cerr << "[ERROR] Disk is not open.\n";
        return;
    }

    std::vector<char> sectorData = diskManager.readSector(rootDirSector);
    
    // FAT32 mein har directory entry 32 bytes ki hoti hai
    for (size_t i = 0; i < sectorData.size(); i += 32) {
        if (i + 32 > sectorData.size()) break;

        // 32 bytes ka ek block nikalein
        std::vector<char> entryBytes(sectorData.begin() + i, sectorData.begin() + i + 32);
        parseDirectoryEntry(entryBytes);
    }
}

// 32-Byte Entry ko decode karna
void SimulatedFAT32::parseDirectoryEntry(const std::vector<char>& entryBytes) {
    // Pehla byte check karein
    unsigned char firstByte = static_cast<unsigned char>(entryBytes[0]);

    // 0x00 ka matlab hai aagay koi data nahi hai
    if (firstByte == 0x00) return; 

    // 0xE5 ka matlab hai file DELETED hai!
    if (firstByte == 0xE5) {
        std::string fileName = "?"; // Pehla character lost ho gaya hai isliye '?' lagaya
        
        // Baki 10 characters file ke naam aur extension ke hote hain
        for (int i = 1; i < 11; ++i) {
            if (entryBytes[i] != ' ') {
                fileName += entryBytes[i];
            }
        }

        // Byte 26, 27 mein Start Cluster (jahan file ka actual data hai) hota hai
        int startCluster = (static_cast<unsigned char>(entryBytes[27]) << 8) | 
                           static_cast<unsigned char>(entryBytes[26]);
        
        // Byte 28 se 31 mein File Size hota hai
        int fileSize = (static_cast<unsigned char>(entryBytes[31]) << 24) |
                       (static_cast<unsigned char>(entryBytes[30]) << 16) |
                       (static_cast<unsigned char>(entryBytes[29]) << 8)  |
                       static_cast<unsigned char>(entryBytes[28]);

        // Agar valid size hai toh list mein add kar dein
        if (fileSize > 0) {
            deletedFiles.push_back(FileRecord(fileName, fileSize, startCluster, true));
        }
    }
}

// Result return karna
std::vector<FileRecord> SimulatedFAT32::getDeletedFiles() const {
    return deletedFiles;
}