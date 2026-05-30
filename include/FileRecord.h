#ifndef FILERECORD_H
#define FILERECORD_H

#include <string>
#include <iostream>

class FileRecord {
private:
    std::string fileName;
    int fileSize;      // Size in bytes
    int startCluster;  // Sector/Cluster jahan se file shuru hoti hai
    bool isDeleted;    // Flag check karne ke liye ke file deleted hai ya nahi

public:
    // Constructor
    FileRecord(std::string name, int size, int cluster, bool deleted);

    // Getter methods (Read-only)
    std::string getFileName() const;
    int getFileSize() const;
    int getStartCluster() const;
    bool getIsDeleted() const;

    // Utility function
    void displayFileInfo() const;
};

#endif // FILERECORD_H