# ASCII Art Converter & Image Converter

---

## Description

**ASCII Art Converter** is a C++ application that converts images into ASCII art using the OpenCV library for image processing. It allows users to select images via a native Windows file dialog, adjust the width of the generated ASCII art, and save the output to a text file.

This tool is perfect for anyone looking to transform graphical images into stylized ASCII character representations — ideal for artistic projects, terminal displays, or experimenting with image-to-text processing.

---

## Features

- Native Windows file dialog for easy image selection.
- Converts images to grayscale and resizes proportionally for ASCII conversion.
- Adjustable ASCII art width (from 10 to 500 characters).
- Console display of generated ASCII art.
- Save ASCII art output to a text file.
- Simple, user-friendly console menu interface.
- Efficient implementation in C++ using OpenCV.

---

## Requirements

- Operating System: Windows (due to native Windows file dialog usage).
- C++ compiler supporting C++11 or higher.
- OpenCV library (recommended versions 3.x or 4.x).
- Standard C++ libraries (`iostream`, `fstream`, `string`, etc.).
- [Git](https://git-scm.com/) (optional, for version control).

---

## Installation and Setup

### 1. Install OpenCV

Download OpenCV from [https://opencv.org/releases/](https://opencv.org/releases/) and follow the official installation instructions for your compiler and environment.

### 2. Compile the code

Example compilation command using `g++` (adjust OpenCV include and lib paths accordingly):

```bash
g++ -std=c++11 main.cpp -o ascii_converter -I<opencv_include_path> -L<opencv_lib_path> -lopencv_core -lopencv_imgproc -lopencv_imgcodecs
