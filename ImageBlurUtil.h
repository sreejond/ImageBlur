# include <assert.h> 
/**
 * \class ImageBlurUtil
 *
 * \brief
 *
 * This class is a utility class to blur a given image.
 */
class ImageBlurUtil {

public:

    /** \brief blur the input image with the given 3x3 filter only for background pixel
      * \param inputImage input image
      * \param outputImage return output image
      * \param mask same size of the input image, 0 for foreground and 1 for background
      * \param width input image width
      * \param height output image height
      * \param filter a 3x3 filter for convolution
      */
    static void blurImage(unsigned char* inputImage, unsigned char* outputImage, unsigned char* mask, int width, int height, int filter[3][3]);

private:

    /**
      * \brief default constructor
      *
      * intentionally made it private so that no instance of the class will be available, as it is a utility class
      */
    ImageBlurUtil();

    /** \brief provide all the valid neighbours of the given pixel
      * \param inputImage input image
      * \param mask same size of the input image, 0 for foreground and 1 for background
      * \param index pixel index
      * \param width input image width
      * \param height output image height
      * \param neighbours return neighbours of size 9, -1 means no valid neighbours at that position
      */
    static void get3x3Neighbours(unsigned char* inputImage, unsigned char* mask, int index, int width, int height, int* neighbours);

    /** \brief apply the given filter on the pixel
      * \param inputImage input image
      * \param outputImage return output image
      * \param mask same size of the input image, 0 for foreground and 1 for background
      * \param index pixel index
      * \param width input image width
      * \param height output image height
      * \param filter a 3x3 filter for convolution
      */
    static void applyFilter(unsigned char* inputImage, unsigned char* outputImage, unsigned char* mask, int index, int width, int height, int filter[3][3]);
};
