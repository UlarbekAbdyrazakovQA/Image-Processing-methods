#include "Image.h"

int main(){


GrayscaleImage source;

source.Load("read.png");

source.Save("grayscale.png");

for (int y = 0; y < source.GetHeight(); y++)
{
    for (int x = 0; x<source.GetWidth() ; x++)
    {
        
    }
    
}


source.Save("out.png")


    return 0;
}