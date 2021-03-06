#include "header/RawImage.hpp"
#include "header/ProcessImage.hpp"
#include "header/Debayer.hpp"
#include "header/Ppm.hpp"

#define IMG_BASE "../Images/"

int main(int argc, char* argv[])
{
    if(argc != 4)
    {
    	std::cerr << "Missing Arguments ... Usage : ./Task_apertus width height image_path " << std::endl;
    	exit(1);
    }	
    clock_t start, end; 
    double timeTaken;
	
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    const char * inputFileName = argv[3];
    
    RawImage img(inputFileName,width,height);

    start = clock();
    //Extract Channels , Print Intensity
    ProcessImage processer(img);
    processer.SeperateChannels();
    processer.DisplayIntensityProcess();
    end = clock();
    timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken to process (SeperateChannels , Display Intensity) the image is : " << std::fixed << timeTaken << std::setprecision(5) << " seconds" << std::endl;

    start = clock();
    //Debayer image usign Billinear Interpolation
    Debayer debayer(img);
    debayer.DebayerProcess();
    end = clock();
    timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken to Debayer the image is : " << std::fixed << timeTaken << std::setprecision(5) << " seconds" << std::endl;

    start = clock();
    //Write the channels and Image
    Ppm ppmwrite(img);
    ppmwrite.WriteImageProcess(IMG_BASE);
    end = clock();
    timeTaken = double(end - start) / double(CLOCKS_PER_SEC);
    std::cout << "Time taken to Write the Colored and Channel images is : " << std::fixed << timeTaken << std::setprecision(5) << " seconds" << std::endl;

    std::cout << "Images Written in the Images folder " << std::endl;
}

