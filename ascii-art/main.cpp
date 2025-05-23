#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// ASCII Art Logo
const std::string logo = R"(
   _____                            _
  / ____|                          | |
 | |     ___  _ __ ___  _ __  _   _| |_ ___  ___
 | |    / _ \| '_ ` _ \| '_ \| | | | __/ _ \/ __|
 | |___| (_) | | | | | | |_) | |_| | ||  __/\__ \
  \_____\___/|_| |_| |_| .__/ \__,_|\__\___||___/
                       | |
                       |_|
        ASCII Art Converter & Image Converter
           <==>   [  Convert your images  ]   <==>
)";

// Open File Dialog
std::string openFileDialog() {
    OPENFILENAMEA ofn;
    CHAR szFile[260] = {0};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "Images\0*.bmp;*.jpg;*.jpeg;*.png;*.tiff;*.gif\0All Files\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(ofn.lpstrFile);
    }
    return std::string();
}

// Convert grayscale image to ASCII
std::string imageToAsciiString(const cv::Mat& grayImg, int width) {
    const std::string ascii_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";

    int originalWidth = grayImg.cols;
    int originalHeight = grayImg.rows;
    int height = static_cast<int>((double)originalHeight * width / originalWidth / 2);
    cv::Mat resized;
    cv::resize(grayImg, resized, cv::Size(width, height));

    std::string ascii_art;
    for (int i = 0; i < resized.rows; i++) {
        for (int j = 0; j < resized.cols; j++) {
            uchar pixel = resized.at<uchar>(i, j);
            int index = (pixel * (ascii_chars.size() - 1)) / 255;
            ascii_art += ascii_chars[index];
        }
        ascii_art += '\n';
    }
    return ascii_art;
}

// Menu display
void printMenu() {
    std::cout << "\n=== ASCII Art Converter Menu ===\n"
              << "1. Select Image\n"
              << "2. Set ASCII Width\n"
              << "4. Save ASCII Art to File\n"
              << "5. Exit\n"
              << "Choose an option: ";
}

int main() {
    std::cout << logo << std::endl;

    std::string filepath;
    cv::Mat image, gray;
    std::string asciiArt;
    int asciiWidth = 100;
    bool imageLoaded = false;
    bool asciiGenerated = false;

    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            filepath = openFileDialog();
            if (filepath.empty()) {
                std::cout << "No file selected.\n";
                imageLoaded = false;
                asciiGenerated = false;
            } else {
                image = cv::imread(filepath);
                if (image.empty()) {
                    std::cerr << "Failed to load image.\n";
                    imageLoaded = false;
                    asciiGenerated = false;
                } else {
                    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
                    asciiArt = imageToAsciiString(gray, asciiWidth);
                    asciiGenerated = true;
                    imageLoaded = true;
                    std::cout << "Image loaded and converted to ASCII: " << filepath << std::endl;
                    std::cout << "\n--- ASCII Art Output ---\n" << asciiArt << std::endl;
                }
            }
        } else if (choice == 2) {
            std::cout << "Enter ASCII art width (10 to 500): ";
            int w;
            std::cin >> w;
            if (w >= 10 && w <= 500) {
                asciiWidth = w;
                std::cout << "Width set to " << asciiWidth << std::endl;
                if (imageLoaded) {
                    asciiArt = imageToAsciiString(gray, asciiWidth);
                    asciiGenerated = true;
                    std::cout << "\n--- ASCII Art Updated ---\n" << asciiArt << std::endl;
                }
            } else {
                std::cout << "Invalid width. Please choose between 10 and 500.\n";
            }
        } else if (choice == 4) {
            if (!asciiGenerated) {
                std::cout << "No ASCII art generated yet. Please load an image first.\n";
                continue;
            }
            std::cout << "Enter output filename (e.g. output.txt): ";
            std::string outFile;
            std::cin >> outFile;
            std::ofstream ofs(outFile);
            if (ofs) {
                ofs << asciiArt;
                ofs.close();
                std::cout << "ASCII art saved to " << outFile << std::endl;
            } else {
                std::cerr << "Error saving file.\n";
            }
        } else if (choice == 5) {
            std::cout << "Exiting. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid option. Please select again.\n";
        }
    }

    return 0;
}
