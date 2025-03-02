# QR Decoder

This is a simple QR decoder using OpenCV

## Install OpenCV For Linux
```bash
apt-get install libstdc++-12-dev libopencv-dev -y
```

## How To Use

### 1. With Default Camera

```bash
$ ./qr_decoder

[INFO] USE CAM 0 BY DEFAULT
Usage: /home/koalko/qr_decoder/qr_decoder (cam_id | path)

****************************************************************************
DATA: http://en.m.wikipedia.org

****************************************************************************
```

### 2. With a Specific Camera Index

```bash
$ ./qr_decoder 0
****************************************************************************
DATA: http://en.m.wikipedia.org

****************************************************************************
```

### 3. Decode from Images
```bash
$ ./qr_decoder 1.png 2.jpg 3.jpg 4.png
****************************************************************************
IMAGE: /home/koalko/qr_decoder/1.png
DATA: https://upload.wikimedia.org/wikipedia/commons/7/7b/SelfieDuMacaque.ogv

****************************************************************************
IMAGE: /home/koalko/qr_decoder/2.jpg
DATA: sample qr code

****************************************************************************
IMAGE: /home/koalko/qr_decoder/3.jpg
DATA: http://www.sciencekiddo.com/2015/01/qr-codes-for-kids-introduction-to.html

****************************************************************************
IMAGE: /home/koalko/qr_decoder/4.png
DATA: http://qr.rs/v/675a0

****************************************************************************
```