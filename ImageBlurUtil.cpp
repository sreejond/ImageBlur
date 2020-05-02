#include "ImageBlurUtil.h"

void ImageBlurUtil::get3x3Neighbours(unsigned char* inputImage, unsigned char* mask, int index, int width, int height, int* neighbours)
{
    // initialize the neighbours with -1
    for (int i = 0; i < 9; i++)
    {
        neighbours[i] = -1;
    }

    int arrSize = width * height;
    if (index < 0 && index >= arrSize)    return;   // do nothing if index is not valid

    int rowBoundaryStart = ((index - width) < 0 ) ? -1 : ((index - width) / width) * width; // first row start position
    int rowBoundaryEnd = rowBoundaryStart + width; // first row end position

    // 1st row, 1st col
    if (rowBoundaryStart >= 0 && index - width - 1 >= rowBoundaryStart && mask[index - width - 1] == 1)
    {
        neighbours[0] = inputImage[index - width - 1];
    }
    // 1st row, 2nd col
    if (rowBoundaryStart >= 0 && mask[index - width] == 1)
    {
        neighbours[1] = inputImage[index - width];
    }
    // 1st row, 3rd col
    if (rowBoundaryStart >= 0 && index - width + 1 < rowBoundaryEnd && mask[index - width + 1] == 1)
    {
        neighbours[2] = inputImage[index - width + 1];
    }

    rowBoundaryStart = (index / width) * width; // second row start position
    rowBoundaryEnd = rowBoundaryStart + width;  // second row end position

    // 2nd row, 1st col
    if (index - 1 >= rowBoundaryStart && mask[index - 1] == 1)
    {
        neighbours[3] = inputImage[index - 1];
    }
    // 2nd row, 2nd col
    neighbours[4] = inputImage[index];
    // 2nd row, 3rd col
    if (index + 1 < rowBoundaryEnd && mask[index + 1] == 1)
    {
        neighbours[5] = inputImage[index + 1];
    }

    rowBoundaryStart = ((index + width) / width) * width;   // third row start position
    rowBoundaryEnd = rowBoundaryStart + width;  // third row end position

    // 3nd row, 1st col
    if (rowBoundaryStart < arrSize && index + width - 1 >= rowBoundaryStart && mask[index + width - 1] == 1)
    {
        neighbours[6] = inputImage[index + width - 1];
    }
    // 3nd row, 2nd col
    if (rowBoundaryStart < arrSize && mask[index + width] == 1)
    {
        neighbours[7] = inputImage[index + width];
    }
    // 3nd row, 3rd col
    if (rowBoundaryStart < arrSize && index + width + 1 < rowBoundaryEnd && mask[index + width + 1] == 1)
    {
        neighbours[8] = inputImage[index + width + 1];
    }
}

void ImageBlurUtil::applyFilter(unsigned char* inputImage, unsigned char* outputImage, unsigned char* mask, int index, int width, int height, int filter[3][3])
{
    int sum = 0;
    int neighbours[9];

    // find all the neighbours pixel for the given index
    // * * *
    // * x *
    // * * *
    get3x3Neighbours(inputImage, mask, index, width, height, neighbours);

    int validNeighboursCnt = 0;
    // loop up to kernel size
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int idx = i * 3 + j;
            if (neighbours[idx] != -1)
            {
                sum += neighbours[idx] * filter[i][j];
                validNeighboursCnt++;
            }
        }
    }

    outputImage[index] = (sum / validNeighboursCnt) % 255; // handle the overflow as unsigned char is 1 byte
}

void ImageBlurUtil::blurImage(unsigned char* inputImage, unsigned char* outputImage, unsigned char* mask, int width, int height, int filter[3][3])
{
    assert(width > 0 && height > 0);
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int index = row * width + col; // convert 2D to 1D
            if (mask[index] == 1) // apply filter on background pixel
            {
                applyFilter(inputImage, outputImage, mask, index, width, height, filter);
            }
            else    // for foreground pixel keep it as it is
            {
                outputImage[index] = inputImage[index];
            }
        }
    }
}
