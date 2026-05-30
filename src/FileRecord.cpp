#include "../include/FileRecord.h"

// Constructor implementation
FileRecord::FileRecord(std::string name, int size, int cluster, bool deleted)
    : fileName(name), fileSize(size), startCluster(cluster), isDeleted(deleted) {}

// Getters implementation
std::string FileRecord::getFileName() const { return fileName; }
int FileRecord::getFileSize() const { return fileSize; }
int FileRecord::getStartCluster() const { return startCluster; }
bool FileRecord::getIsDeleted() const { return isDeleted; }

// Display function implementation
void FileRecord::displayFileInfo() const {
    std::cout << "File Name: " << fileName 
              << " | Size: " << fileSize << " bytes"
              << " | Start Cluster: " << startCluster 
              << " | Status: " << (isDeleted ? "[DELETED]" : "[ACTIVE]") 
              << std::endl;
}