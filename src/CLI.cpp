#include "../include/CLI.h"
#include <iostream>
#include <vector>

CLI::CLI(IFileSystem* fs, RecoveryEngine& eng) : fileSystem(fs), engine(eng) {}

void CLI::start() {
    std::cout << "\n=========================================" << std::endl;
    std::cout << "      DELETED FILE RECOVERY TOOL         " << std::endl;
    std::cout << "=========================================\n" << std::endl;

    fileSystem->scanForDeletedFiles();
    std::vector<FileRecord> deletedFiles = fileSystem->getDeletedFiles();

    if (deletedFiles.empty()) {
        std::cout << "No deleted files found on the disk.\n";
        return;
    }

    while (true) {
        std::cout << "\n--- Found Files ---\n";
        for (size_t i = 0; i < deletedFiles.size(); ++i) {
            std::cout << "[" << i + 1 << "] ";
            deletedFiles[i].displayFileInfo();
        }
        std::cout << "[0] Exit\n";

        std::cout << "\nEnter the number of the file to recover (or 0 to exit): ";
        int choice;
        std::cin >> choice;

        if (choice == 0) {
            std::cout << "Exiting tool...\n";
            break;
        }

        if (choice > 0 && choice <= static_cast<int>(deletedFiles.size())) {
            // '.' demek mevcut klasöre (root directory) kaydet demektir
            engine.recoverFile(deletedFiles[choice - 1], "."); 
        } else {
            std::cout << "[ERROR] Invalid choice. Please try again.\n";
        }
    }
}