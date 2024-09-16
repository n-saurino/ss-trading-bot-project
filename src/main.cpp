#include <stdio.h>
#include "../include/SyncClient.h"
#include "../include/Receiver.h"

int main(int, char**){
    try
    {
    Client client;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
