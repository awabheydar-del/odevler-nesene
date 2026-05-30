#ifndef CLI_H
#define CLI_H

#include "IFileSystem.h"
#include "RecoveryEngine.h"

class CLI {
private:
    IFileSystem* fileSystem;
    RecoveryEngine& engine;

public:
    CLI(IFileSystem* fs, RecoveryEngine& eng);
    
    // Ana menü döngüsü
    void start();
};

#endif // CLI_H