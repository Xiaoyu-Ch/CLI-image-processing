#include "Image.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

// Constructor: reads header and pixel data.
Image::Image(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(1);
    }
    readHeader(file);
    width = header.width;
    height = header.height;
    data.resize(width * height * 3);
    file.read(reinterpret_cast<char*>(data.data()), data.size());
}

// Blank constructor: copies header/dimensions and allocates a zeroed pixel buffer.
Image::Image(const Image& prototype, bool /*blank*/) {
    header = prototype.header;
    width = prototype.width;
    height = prototype.height;
    data.resize(width * height * 3, 0);
}

// Write header and pixel data to file.
void Image::write(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to create file: " << filename << std::endl;
        exit(1);
    }
    writeHeader(file);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

// Multiply blending: multiply normalized pixel values.
Image Image::multiply(const Image& other) const {
    Image result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        float a = data[i] / 255.0f;
        float b = other.data[i] / 255.0f;
        result.data[i] = clamp(static_cast<int>(std::round(a * b * 255)));
    }
    return result;
}

// Subtract blending: subtract pixel values and clamp.
Image Image::subtract(const Image& other) const {
    Image result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        int diff = static_cast<int>(data[i]) - static_cast<int>(other.data[i]);
        result.data[i] = clamp(diff);
    }
    return result;
}

// Screen blending: result = 1 - (1 - a)*(1 - b)
Image Image::screen(const Image& other) const {
    Image result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        float a = data[i] / 255.0f;
        float b = other.data[i] / 255.0f;
        float screenVal = 1 - (1 - a) * (1 - b);
        result.data[i] = clamp(static_cast<int>(std::round(screenVal * 255)));
    }
    return result;
}

// Overlay blending: if bottom <= 0.5 then 2*a*b, else 1 - 2*(1 - a)*(1 - b)
Image Image::overlay(const Image& other) const {
    Image result = *this;
    for (size_t i = 0; i < data.size(); ++i) {
        float top = data[i] / 255.0f;
        float bottom = other.data[i] / 255.0f;
        float overlayVal = (bottom <= 0.5f) ? (2 * top * bottom)
                                          : (1 - 2 * (1 - top) * (1 - bottom));
        result.data[i] = clamp(static_cast<int>(std::round(overlayVal * 255)));
    }
    return result;
}

// Add a constant value to the green channel.
void Image::addGreen(int value) {
    for (size_t i = 1; i < data.size(); i += 3) {
        data[i] = clamp(static_cast<int>(data[i]) + value);
    }
}

// scaleColor: multiply red channel by redScale and blue channel by blueScale.
void Image::scaleColor(float redScale, float blueScale) {
    for (size_t i = 0; i < data.size(); i += 3) {
        data[i]   = clamp(static_cast<int>(data[i] * blueScale));    // Blue channel.
        // Green remains unchanged.
        data[i+2] = clamp(static_cast<int>(data[i+2] * redScale));     // Red channel.
    }
}

// separateChannels: write each channel as a grayscale image.
void Image::separateChannels(const std::string& redFilename, const std::string& greenFilename, const std::string& blueFilename) const {
    Image redImg(*this, true);
    Image greenImg(*this, true);
    Image blueImg(*this, true);
    size_t numPixels = data.size() / 3;
    for (size_t i = 0; i < numPixels; ++i) {
        unsigned char b = data[i*3+0];
        unsigned char g = data[i*3+1];
        unsigned char r = data[i*3+2];
        // For red image: fill all channels with r.
        redImg.data[i*3+0] = r;
        redImg.data[i*3+1] = r;
        redImg.data[i*3+2] = r;
        // For green image.
        greenImg.data[i*3+0] = g;
        greenImg.data[i*3+1] = g;
        greenImg.data[i*3+2] = g;
        // For blue image.
        blueImg.data[i*3+0] = b;
        blueImg.data[i*3+1] = b;
        blueImg.data[i*3+2] = b;
    }
    redImg.write(redFilename);
    greenImg.write(greenFilename);
    blueImg.write(blueFilename);
}

void Image::combineChannels(const std::string& redFilename, const std::string& greenFilename, const std::string& blueFilename) {
    Image redLayer(redFilename);     // expected to supply blue channel (0)
    Image greenLayer(greenFilename); // expected to supply green channel (0)
    Image blueLayer(blueFilename);   // expected to supply red channel (62)
    
    size_t numPixels = data.size() / 3;
    for (size_t i = 0; i < numPixels; ++i) {
        data[i*3+0] = redLayer.data[i*3+0];    // blue component from layer_red.tga
        data[i*3+1] = greenLayer.data[i*3+0];  // green component from layer_green.tga
        data[i*3+2] = blueLayer.data[i*3+2];   // red component from layer_blue.tga
    }
}


// rotate180: swap entire pixels (3 bytes per pixel).
void Image::rotate180() {
    size_t numPixels = data.size() / 3;
    for (size_t i = 0; i < numPixels / 2; ++i) {
        size_t j = numPixels - 1 - i;
        for (size_t k = 0; k < 3; ++k) {
            std::swap(data[i*3+k], data[j*3+k]);
        }
    }
}

// Read TGA header from file.
void Image::readHeader(std::ifstream& file) {
    file.read(reinterpret_cast<char*>(&header), sizeof(header));
}

// Write TGA header to file.
void Image::writeHeader(std::ofstream& file) const {
    file.write(reinterpret_cast<const char*>(&header), sizeof(header));
}

// Clamp a value between 0 and 255.
unsigned char Image::clamp(int value) const {
    return static_cast<unsigned char>(std::max(0, std::min(255, value)));
}
