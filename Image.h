#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include <fstream>

// Ensure the Header struct is exactly 18 bytes with no padding.
#pragma pack(push, 1)
struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};
#pragma pack(pop)

class Image {
private:
    int width;
    int height;
    std::vector<unsigned char> data;
    Header header;

public:
    // Constructor: load image from file.
    Image(const std::string& filename);
    // Blank constructor: copy header/dimensions; 'blank' parameter now unused.
    Image(const Image& prototype, bool /*blank*/);
    // Write the image to a file.
    void write(const std::string& filename) const;

    // Blending functions.
    Image multiply(const Image& other) const;
    Image subtract(const Image& other) const;
    Image screen(const Image& other) const;
    Image overlay(const Image& other) const;

    // Channel operations.
    void addGreen(int value);
    // scaleColor: multiply red channel by redScale and blue channel by blueScale.
    void scaleColor(float redScale, float blueScale);
    // separateChannels: writes the red, green, and blue channels as grayscale images.
    void separateChannels(const std::string& redFilename, const std::string& greenFilename, const std::string& blueFilename) const;
    // combineChannels: loads three images and combines them into this image.
    void combineChannels(const std::string& redFilename, const std::string& greenFilename, const std::string& blueFilename);

    // Other operations.
    void rotate180();

    // Getters: non-const and const versions.
    std::vector<unsigned char>& getData() { return data; }
    const std::vector<unsigned char>& getData() const { return data; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    void readHeader(std::ifstream& file);
    void writeHeader(std::ofstream& file) const;
    unsigned char clamp(int value) const;
};

#endif
