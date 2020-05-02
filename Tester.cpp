/**
 *
 * \brief
 *
 * This is a Tester file to test ImageBlurUtil. It run two test cases on two different images and write the output image.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "ImageBlurUtil.h"
#include <png++/png.hpp>

using namespace std;

typedef vector<double> Array;
typedef vector<Array> Matrix;
typedef vector<Matrix> Image;

Image loadImage(const char *filename)
{
    png::image<png::rgb_pixel> image(filename);
    Image imageMatrix(3, Matrix(image.get_height(), Array(image.get_width())));

    unsigned int h, w;
    for (h = 0; h < image.get_height(); h++) 
    {
        for (w = 0; w < image.get_width(); w++) 
        {
            imageMatrix[0][h][w] = image[h][w].red;
            imageMatrix[1][h][w] = image[h][w].green;
            imageMatrix[2][h][w] = image[h][w].blue;
        }
    }

    return imageMatrix;
}

void saveImage(Image &image, const char *filename)
{
    assert(image.size() == 3);

    int height = image[0].size();
    int width = image[0][0].size();
    int x,y;

    png::image<png::rgb_pixel> imageFile(width, height);

    for (y = 0; y < height; y++) 
    {
        for (x = 0; x < width; x++) 
        {
            imageFile[y][x].red = image[0][y][x];
            imageFile[y][x].green = image[1][y][x];
            imageFile[y][x].blue = image[2][y][x];
        }
    }

    imageFile.write(filename);
}

void testCase1()
{
    int filter [3][3] = {1,1,1,
                         1,1,1,
                         1,1,1};

    Image image = loadImage("image_1.png");
    Image fgImage = loadImage("foreground_1.png");

    int height = image[0].size();
    int width = image[0][0].size();

    unsigned char inputImage[width*height];
    unsigned char outputImage[width*height];
    unsigned char mask[width*height];
    
    for (int d = 0; d < 3; d++)
    {
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int index = row * width + col; // convert 2D to 1D
                inputImage[index] = image[d][row][col];
                if (fgImage[d][row][col] == 0)
                {
                    mask[index] = 1;
                }
                else
                {
                    mask[index] = 0;   
                }
                outputImage[index] = 0;
            }
        }

        ImageBlurUtil::blurImage(inputImage, outputImage, mask, width, height, filter);

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int index = row * width + col; // convert 2D to 1D
                image[d][row][col] = outputImage[index];
            }
        }
    }

    saveImage(image, "outputImage_1.png");
}

void testCase2()
{
    int filter [3][3] = {1,1,1,
                         1,1,1,
                         1,1,1};

    Image image = loadImage("image_2.png");
    Image fgImage = loadImage("foreground_2.png");

    int height = image[0].size();
    int width = image[0][0].size();

    unsigned char inputImage[width*height];
    unsigned char outputImage[width*height];
    unsigned char mask[width*height];
    
    for (int d = 0; d < 3; d++)
    {
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int index = row * width + col; // convert 2D to 1D
                inputImage[index] = image[d][row][col];
                if (fgImage[d][row][col] == 0)
                {
                    mask[index] = 1;
                }
                else
                {
                    mask[index] = 0;   
                }
                outputImage[index] = 0;
            }
        }

        ImageBlurUtil::blurImage(inputImage, outputImage, mask, width, height, filter);

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                int index = row * width + col; // convert 2D to 1D
                image[d][row][col] = outputImage[index];
            }
        }
    }

    saveImage(image, "outputImage_2.png");
}

int main()
{
    cout << "Running testCase1..." << endl;
    testCase1();
    cout << "Running testCase2..." << endl;
    testCase2();

    return 0;
}

