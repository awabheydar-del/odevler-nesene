#include <iostream>
#include <fstream>
#include <cstring>
#include "../include/FileRecord.h"
#include "../include/DiskImageManager.h"
#include "../include/SimulatedFAT32.h"
#include "../include/RecoveryEngine.h"
#include "../include/CLI.h"

// Dummy disk create karne ka function
void createDummyDisk(const std::string& path) {
    std::ofstream disk(path, std::ios::binary);
    if(!disk.is_open()) return;

    char zero[512] = {0};
    disk.write(zero, 512); // Sector 0 (Boot)

    char rootDir[512] = {0}; // Sector 1 (Root Dir)
    
    // File 1
    rootDir[0] = (char)0xE5; 
    std::memcpy(&rootDir[1], "SECRET   TXT", 11); 
    rootDir[26] = 0x05; 
    rootDir[28] = 0x00; rootDir[29] = 0x01; // Size 256 bytes
    
    // File 2
    rootDir[32] = (char)0xE5; 
    std::memcpy(&rootDir[33], "PASSWORDSCSV", 11);
    rootDir[58] = 0x0A; 
    rootDir[60] = 0x00; rootDir[61] = 0x01; // Size 256 bytes

    disk.write(rootDir, 512);

    // Dummy data in sectors (taake jab recover ho toh file khali na ho)
    disk.seekp(5 * 512); // Sector 5 (for File 1)
    disk.write("This is a recovered secret document!", 36);

    disk.seekp(10 * 512); // Sector 10 (for File 2)
    disk.write("user,password\nadmin,12345", 25);

    disk.close();
}

int main() {
    std::string diskPath = "data/dummy_disk.img"; 
    
    // 1. Setup disk
    createDummyDisk(diskPath);
    DiskImageManager disk(diskPath);
    if (!disk.openDisk()) {
        std::cerr << "Failed to open disk.\n";
        return 1;
    }

    // 2. Initialize OOP components
    IFileSystem* fs = new SimulatedFAT32(disk, 1);
    RecoveryEngine engine(fs, disk);
    CLI cli(fs, engine);

    // 3. Start Interface
    cli.start();

    // 4. Cleanup
    delete fs;
    disk.closeDisk();

    return 0;
}