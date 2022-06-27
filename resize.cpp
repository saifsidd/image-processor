// Project UID af1f95f547e44c8ea88730dfb185559d
#include "Matrix.h"
#include "Image.h"
#include "processing.h"
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (!(argc == 4 || argc == 5)) {
        cout << "Make sure you order properly!" << endl;
        cout << "Usage: ./resize.exe" << endl;
    }
    Image *img = new Image;
    ifstream fileName;
    fileName.open(argv[1]);
    if (!fileName.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
    }
    Image_init(img, fileName);
    int width = Image_width(img);
    int height = Image_height(img);
    int argWidth = atoi(argv[3]);
    int argHeight = atoi(argv[4]);
    if (!(argWidth > 0 && argWidth <= width && argHeight > 0 && argHeight <= height)) {
        cout << "Make sure you order properly!" << endl;
        cout << "Usage: ./resize.exe" << endl;
    }
    Image *newImg = new Image;
    newImg = img;
    seam_carve(newImg, argWidth, argHeight);

    ofstream outFile;
    outFile.open(argv[2]);
    Image_print(newImg, outFile);
    return 1;

    delete img;
    delete newImg;
}