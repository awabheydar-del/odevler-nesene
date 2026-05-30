#include "../include/RecoveryEngine.h"
#include <iostream>
#include <fstream>
#include <algorithm>

RecoveryEngine::RecoveryEngine(IFileSystem* fs, DiskImageManager& disk)
    : fileSystem(fs), diskManager(disk) {}

bool RecoveryEngine::recoverFile(const FileRecord& file, const std::string& outputDir) {
    if (file.getFileSize() <= 0) {
        std::cerr << "[ERROR] Invalid file size. Cannot recover.\n";
        return false;
    }

    // Dosya ismindeki '?' işaretini '_' ile değiştiriyoruz ki Windows dosyayı kaydedebilsin
    std::string safeName = file.getFileName();
    if (safeName[0] == '?') {
        safeName[0] = '_'; 
    }
    std::replace(safeName.begin(), safeName.end(), ' ', '_'); 

    std::string outputPath = outputDir + "/" + safeName;

    std::ofstream outFile(outputPath, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "[ERROR] Could not create output file: " << outputPath << "\n";
        return false;
    }

    std::cout << "Recovering '" << file.getFileName() << "' to '" << outputPath << "'...\n";

    // Veriyi diskten oku
    std::vector<char> clusterData = diskManager.readSector(file.getStartCluster());

    // Veriyi yeni dosyaya yaz
    int bytesToWrite = std::min(file.getFileSize(), (int)clusterData.size());
    outFile.write(clusterData.data(), bytesToWrite);

    outFile.close();
    std::cout << "[SUCCESS] File recovered successfully!\n";
    return true;
}