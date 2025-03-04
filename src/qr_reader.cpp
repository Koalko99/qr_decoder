#include "qr_reader.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace cv;

void log_event(const std::string& message) {
    std::ofstream logFile("qr_log.txt", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        logFile << std::ctime(&now) << "[LOG] " << message << std::endl;
        logFile.close();
    }
}

std::string decode_qr(const std::string& imagePath) {
    Mat image = imread(imagePath, IMREAD_COLOR);
    if (image.empty()) {
        log_event("ERROR: Failed to load image " + imagePath);
        return "ERROR OF LOAD IMAGE";
    }
    QRCodeDetector qr;
    std::vector<Point> points;
    if (!qr.detect(image, points)) {
        log_event("QR NOT FOUND in " + imagePath);
        return "QR NOT FOUND";
    }
    std::string text = qr.decode(image, points);
    if (text.empty()) {
        log_event("QR decoding failed in " + imagePath);
        return "QR NOT FOUND";
    }
    log_event("QR decoded: " + text);
    return text;
}

void qr_by_cam(const unsigned int cam_index) {
    VideoCapture cap(cam_index);
    if (!cap.isOpened()) {
        std::cerr << "[ERROR] CAN'T OPEN CAMERA " << cam_index << "\n";
        log_event("ERROR: Failed to open camera " + std::to_string(cam_index));
        return;
    }

    cap.set(CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CAP_PROP_FRAME_HEIGHT, 800);

    Mat frame;
    std::string windowName = "CAM " + std::to_string(cam_index);
    
    std::ofstream qrOutput("qr_results.txt", std::ios::app);
    if (!qrOutput.is_open()) {
        std::cerr << "[ERROR] CAN'T OPEN OUTPUT FILE" << std::endl;
        return;
    }
    
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "[ERROR] EMPTY FRAME\n";
            log_event("ERROR: Empty frame from camera " + std::to_string(cam_index));
            break;
        }

        QRCodeDetector qr;
        std::vector<Point> points;
        if (qr.detect(frame, points)) {
            std::string decodedText = qr.decode(frame, points);
            if (!decodedText.empty()) {
                std::cout << "****************************************************************************\n";
                std::cout << "DATA: " << decodedText << "\n\n";
                qrOutput << decodedText << std::endl;
                log_event("QR decoded from camera: " + decodedText);
            }
        }

        imshow(windowName, frame);
        if (waitKey(30) == 27) {
            break;
        }
    }
    qrOutput.close();
    cap.release();
    destroyAllWindows();
}
