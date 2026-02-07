#include <iostream>
#include <unistd.h> // For geteuid


int main(int argc, char* argv[]) {
    // check for sudo permissions
    if(geteuid() != 0){
        std::cout << "This app needs superuser permissions to run properly.\n"; 
    }

    return 0;
}
