#include <iostream>
#include <fstream>

int main() {
    char header [4];
    int first = 0;

    const char* FName = "../work.png";
    std::ifstream in(FName,std::ios::binary);

    if (!in.is_open()){
        std::cout << "File is not opened, something wrong\n";
        return 0;
    }
        in.read(header, sizeof(header));
        if (header[0] == -119 && header [1] == 'P' && header [2] == 'N' && header [3] == 'G')
            std::cout << "\n Given file has really PNG format";
         else
            std::cout << "\n Given file is NOT a PNG format";


    in.close();
    return 0;
}
