#include "Image.h"
#include <iostream>

int main() {
    std::cout << "Image Processing Program\n";

    // Task 1: Multiply blending (layer1 * pattern1)
    {
        Image layer1("input/layer1.tga");
        Image pattern1("input/pattern1.tga");
        Image result = layer1.multiply(pattern1);
        result.write("output/part1.tga");
        std::cout << "Task 1 completed: Multiply blending\n";
    }

    // Task 2: Subtract blending (layer2 - car)
    {
    Image layer2("input/layer2.tga");
    Image car("input/car.tga");
    Image result = car.subtract(layer2); // Swap the order: top (car) - bottom (layer2)
    result.write("output/part2.tga");
    std::cout << "Task 2 completed: Subtract blending\n";
}

    {
        Image layer2("input/layer2.tga");
        Image car("input/car.tga");
        Image result = layer2.subtract(car);
        result.write("output/part2.tga");
        std::cout << "Task 2 completed: Subtract blending\n";
    }

    // Task 3: Multiply layer1 with pattern2, then screen blend with text.tga.
    {
        Image layer1("input/layer1.tga");
        Image pattern2("input/pattern2.tga");
        Image temp = layer1.multiply(pattern2);
        Image text("input/text.tga");
        Image result = temp.screen(text);
        result.write("output/part3.tga");
        std::cout << "Task 3 completed: Multiply then Screen blending\n";
    }

    // Task 4: Multiply layer2 with circles, then subtract pattern2.
    {
        Image layer2("input/layer2.tga");
        Image circles("input/circles.tga");
        Image temp = layer2.multiply(circles);
        Image pattern2("input/pattern2.tga");
        Image result = temp.subtract(pattern2);
        result.write("output/part4.tga");
        std::cout << "Task 4 completed: Multiply then Subtract blending\n";
    }

    // Task 5: Overlay blending: layer1 (top) with pattern1 (bottom)
    {
        Image layer1("input/layer1.tga");
        Image pattern1("input/pattern1.tga");
        Image result = layer1.overlay(pattern1);
        result.write("output/part5.tga");
        std::cout << "Task 5 completed: Overlay blending\n";
    }

    // Task 6: Add 200 to green channel of car.tga.
    {
        Image car("input/car.tga");
        car.addGreen(200);
        car.write("output/part6.tga");
        std::cout << "Task 6 completed: Add to green channel\n";
    }

    // Task 7: Scale red channel by 4 and blue channel by 0 on car.tga using scaleColor.
    {
        Image car("input/car.tga");
        car.scaleColor(4.0f, 0.0f);
        car.write("output/part7.tga");
        std::cout << "Task 7 completed: Scale red and blue channels\n";
    }

    // Task 8: Split car.tga into separate channel images.
    {
        Image car("input/car.tga");
        car.separateChannels("output/part8_r.tga", "output/part8_g.tga", "output/part8_b.tga");
        std::cout << "Task 8 completed: Split channels\n";
    }

    // Task 9: Combine layer_red.tga, layer_green.tga, and layer_blue.tga into one image.
    {
        Image combined("input/layer_red.tga");
        combined.combineChannels("input/layer_red.tga", "input/layer_green.tga", "input/layer_blue.tga");
        combined.write("output/part9.tga");
        std::cout << "Task 9 completed: Combine channel images\n";
    }

    // Task 10: Rotate text2.tga 180 degrees.
    {
        Image text2("input/text2.tga");
        text2.rotate180();
        text2.write("output/part10.tga");
        std::cout << "Task 10 completed: Rotate 180 degrees\n";
    }

    std::cout << "All tasks completed.\n";
    return 0;
}
