#include<iostream>
#include "Image.h"
#include<map>
#include<iomanip>

using namespace std;


int kernel[3][3];
int object = 0;


std::map<int, int> conflict;
std::map<int, int>::iterator pntr;
std::map<int, int> images;


void print_image(GrayscaleImage objimage);
void prepare_kernels();
void convolution(GrayscaleImage img);
void AdaptiveTreshold(GrayscaleImage img);
void countPixels(GrayscaleImage img);
void objectDetection(GrayscaleImage objimage);
void dilation(GrayscaleImage img);
void inverse(GrayscaleImage img);
void erosion(GrayscaleImage img);
void print_kernel();

int main()
{
    GrayscaleImage imagee;
    imagee.Load("objnew.png");
    prepare_kernels();
    AdaptiveTreshold(imagee);
    print_image(imagee);
    objectDetection(imagee);
    erosion(imagee);
    inverse(imagee);
    dilation(imagee);
    print_kernel();
    
    return 0;
}


void print_image(GrayscaleImage objimage)
{
    for (int y = 0; y < objimage.GetHeight(); y++)
    {
        for (int x = 0; x < objimage.GetWidth(); x++)
        {
            int val = objimage(x, y);
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void prepare_kernels()
{
 
    kernel[0][1] = 1;
    kernel[1][0] = 1;
    kernel[1][1] = 1;
    kernel[1][2] = 1;
    kernel[2][1] = 1;
}
void print_kernel()
{
    for (int y = 0; y < 3; y++)
    {
        for (int x = 0; x < 3; x++)
        {
            std::cout << "[" << kernel[y][x] << "]"
                      << " ";
        }
        std::cout << std::endl;
    }
}

void convolution(GrayscaleImage img){
    
    GrayscaleImage newimage(img.GetWidth(), img.GetHeight());

    for (int y = 1; y < img.GetHeight() - 1; y++)
        for (int x = 1; x < img.GetWidth() - 1; x++)
        {
            newimage(x,y) = (img(x - 1, y) + img(x, y - 1) + img(x + 1, y) + img(x, y + 1) +img(x, y))/5;
            
            
        }
    
    newimage.Save("convolution.png");
}


void AdaptiveTreshold(GrayscaleImage img)
{
    int sum = 0;
    int countpix = 0;
    for (int i = 0; i < img.GetHeight(); i++)
        for (int j = 0; j < img.GetWidth(); j++)
        {
            sum += img(j, i);
            countpix++;
        }

    int treshold = sum / countpix;
    do
    {
        int sumup = 0;
        int sumdown = 0;
        int countup = 0;
        int countdown = 0;
        for (int i = 0; i < img.GetHeight(); i++)
            for (int j = 0; j < img.GetWidth(); j++)
            {
                if (img(j, i) > treshold)
                {
                    sumup += img(j, i);
                    countup++;
                }
                if (img(j, i) <= treshold)
                {
                    sumdown += img(j, i);
                    countdown++;
                }
            }
        if ((sumup / countup + sumdown / countdown) / 2 == treshold)
        {
            std::cout << (sumup / countup + sumdown / countdown) / 2 << std::endl;
            std::cout << treshold;
            break;
        }
        else
            treshold = (sumup / countup + sumdown / countdown) / 2;

    } while (1);

    for (int i = 0; i < img.GetHeight(); i++)
        for (int j = 0; j < img.GetWidth(); j++)
        {
            if (treshold > img(j, i))
                img(j, i) = 255;
            else
                img(j, i) = 0;
        }
    img.Save("AdaptiveTresh.png");
}




void countPixels(GrayscaleImage img)
{
    for (int y = 0; y < img.GetHeight(); y++)
        for (int x = 0; x < img.GetWidth(); x++)
            if (img(x, y) != 0)
            {
                if (images.find(img(x, y)) != images.end())
                {
                    images[img(x, y)]++; //*calculate
                    img(x, y) = 60;      //*paint to gray
                    continue;
                }
                images.insert(std::pair<int, int>(img(x, y), 1));
            }

    for (pntr = images.begin(); pntr != images.end(); pntr++)
    {
        std::cout << "Image : " << pntr->first << std::endl;
        std::cout << "contains :" << pntr->second << " pixels." << std::endl;
    }
    img.Save("color.png");
}

void objectDetection(GrayscaleImage objimage)
{
    for (int y = 0; y < objimage.GetHeight(); y++)
        for (int x = 0; x < objimage.GetWidth(); x++)
        {

            if (objimage(x, y) == 255)
            {
                int down = objimage(x, y + 1);
                int right = objimage(x + 1, y);
                int up = objimage(x, y - 1);
                int left = objimage(x - 1, y);
                if (up != 255 && up != 0 && left != 255 && left != 0 && up != left)
                {
                    objimage(x, y) = (left > up) ? up : left;
                    conflict.insert(std::pair<int, int>(left, up));
                }
                else if (up != 255 && up != 0)
                    objimage(x, y) = up;
                else if (left != 255 && left != 0)
                    objimage(x, y) = left;
                else
                    objimage(x, y) = ++object;
            }
            
        }

    print_image(objimage);
    for (pntr = conflict.begin(); pntr != conflict.end(); pntr++)
        if (conflict.find(pntr->second) != conflict.end())
            conflict[pntr->first] = conflict[pntr->second];

    for (int y = 0; y < objimage.GetHeight(); y++)
        for (int x = 0; x < objimage.GetWidth(); x++)
            if (objimage(x, y) != 0)
                if (conflict.find(objimage(x, y)) != conflict.end())
                    objimage(x, y) = conflict[objimage(x, y)];

    print_image(objimage);
    countPixels(objimage);
}

void dilation(GrayscaleImage img)
{
    GrayscaleImage newimage(img.GetWidth(), img.GetHeight());

    for (int y = 1; y < img.GetHeight() - 1; y++)
        for (int x = 1; x < img.GetWidth() - 1; x++)
        {
            if (img(x - 1, y) * kernel[0][1] == 255 &&
                img(x, y - 1) * kernel[1][0] == 255 && img(x + 1, y) * kernel[2][1] == 255 && img(x, y + 1) * kernel[1][2] == 255 && img(x, y) * kernel[1][1] == 255)
            {
                newimage(x, y) = 255;
            }
            else if (img(x - 1, y) * kernel[0][1] == 255 ||
                     img(x, y - 1) * kernel[1][0] == 255 ||
                     img(x + 1, y) * kernel[2][1] == 255 ||
                     img(x, y + 1) * kernel[1][2] == 255 ||
                     img(x, y) * kernel[1][1] == 255)
                newimage(x, y) = 255;
            else
                newimage(x, y) = 0;
        }

    

    newimage.Save("dilation.png");
}
void inverse(GrayscaleImage img)
{
    for (int y = 0; y < img.GetHeight(); y++)
        for (int x = 0; x < img.GetWidth(); x++)
        {
            img(x, y) = (img(x, y) == 255) ? 0 : 255;
        }
    img.Save("inverse.png");
}

void erosion(GrayscaleImage img)
{
    GrayscaleImage newimg(img.GetWidth(), img.GetHeight());
    for (int y = 1; y < img.GetHeight() - 1; y++)
        for (int x = 1; x < img.GetWidth() - 1; x++)
        {
            if (img(x - 1, y) * kernel[0][1] ==
                    255 &&
                img(x, y - 1) * kernel[1][0] == 255 && img(x + 1, y) * kernel[2][1] == 255 && img(x, y + 1) * kernel[1][2] == 255 && img(x, y) * kernel[1][1] == 255)
            {
                newimg(x, y) = 255;
            }
            else if (img(x - 1, y) * kernel[0][1] == 255 || img(x, y - 1) * kernel[1][0] == 255 || img(x + 1, y) * kernel[2][1] == 255 || img(x, y + 1) * kernel[1][2] == 255 || img(x, y) * kernel[1][1] == 255)
                newimg(x, y) = 0;
            else
                newimg(x, y) = 0;
        }
    newimg.Save("erosion.png");
}
