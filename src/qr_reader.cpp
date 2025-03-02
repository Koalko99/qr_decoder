#include "qr_reader.h"
#include <opencv2/opencv.hpp>

using namespace cv;

std::string decode_qr(const std::string& imagePath) {
    Mat image = imread(imagePath, IMREAD_GRAYSCALE);
    if (image.empty()) {
        return "ERROR OF LOAD IMAGE";
    }

    QRCodeDetector qrDecoder;
    std::string qrText = qrDecoder.detectAndDecode(image);

    if (qrText.empty()) {
        return "QR NOT FOUND";
    }
    return qrText;
}

void qr_by_cam(const unsigned int cam_index) {
    cv::VideoCapture cap(cam_index);
    if (!cap.isOpened()) {
        std::cerr << "[ERROR] CAN'T OPEN CAMERA " << cam_index << "\n";
        return;
    }

    cv::QRCodeDetector qrDecoder;
    cv::Mat frame;
    std::string windowName = "CAM " + std::to_string(cam_index);

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "[ERROR] EMPTY FRAME\n";
            break;
        }

        std::string decodedText = qrDecoder.detectAndDecode(frame);
        if (!decodedText.empty()) {
            std::cout << "****************************************************************************\n";
            std::cout << "DATA: " << decodedText << "\n\n";
        }

        cv::imshow(windowName, frame);
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    std::cout << "****************************************************************************\n";
    cap.release();
    cv::destroyAllWindows();
}