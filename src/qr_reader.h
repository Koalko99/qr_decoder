#ifndef QR_READER_H
#define QR_READER_H

#include <string>

std::string decode_qr(const std::string& imagePath);

void qr_by_cam(const unsigned int cam_index);

#endif