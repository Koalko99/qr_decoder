#include <iostream>
#include "qr_reader.h"
#include <ctype.h>

int main(int argc, char* argv[]) {
    if (argc == 1){
        std::string prog = argv[0];
        std::cout << "\n[INFO] USE CAM 0 BY DEFAULT\n";
        std::cout << "Usage: " + prog + " (cam_id | path)\n\n";
        qr_by_cam(0);
    } else if (isdigit(argv[1][0])){
        qr_by_cam(atoi(argv[1]));
    } else if (argc >= 2){
        for (int i=1; i<argc; i++){
            std::cout << "****************************************************************************\n";
            std::cout << "IMAGE: " << argv[i] << "\n";
            std::cout << "DATA: " << decode_qr(argv[i]) << "\n\n";
        }
        std::cout << "****************************************************************************\n";
    }    
    return 0;
}