#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "FrameSequence.h"

int main(int argc, char* argv[])
{
	std::ifstream in(std::string(argv[1]), std::ios::binary | std::ios::in);
	if (in){
		std::string pgm,comments,sizedata,brightness,origins,framesize,filename,option;
		int Ncols, Nrows,framex,framey,polyLine,polyLineMultiplier;
		float xend,xcoord,yend,ycoord;
		MSPCAM001::FrameSequence frames;
		getline(in,pgm);
		getline(in,comments);
		if (comments.substr(0,1).compare("#")!=0){
			sizedata = comments;
		}
		else{
			getline(in,sizedata);
		}
		std::istringstream iss(sizedata);
		iss >> Ncols >> Nrows;
		getline(in,brightness);
		std::cout << brightness << std::endl;
		unsigned char * pixels = new unsigned char[Ncols*Nrows]; //Use unsigned char because it has range 0-255 which is good for the pixel values
		in.read(reinterpret_cast<char *>(pixels),Ncols*Nrows);
		unsigned char * temp = &(pixels[10]);
		unsigned char v = 255;
	        unsigned char temp2 = static_cast<unsigned char>(v - *temp);
		std::cout << static_cast<float>(temp2) << std::endl;	
			
		std::string polylinechoice = std::string(argv[2]);
		polyLine=0;
		polyLineMultiplier=2;
		if (polylinechoice.compare("-p")==0){
			iss.str("");
			iss.seekg(0);
			iss.str(std::string(argv[3]));
			iss >> polyLineMultiplier;
			std::cout << polyLineMultiplier << std::endl;
			polyLine=1;
		}
		for (int i=0 ;i<polyLineMultiplier-1;i++)
		{
			iss.str("");
			iss.seekg(0);
			origins = std::string(argv[(2*i)+3+polyLine]) +" "+ std::string(argv[(2*i)+4+polyLine]) +" "+ std::string(argv[(2*i)+5+polyLine]) +" "+ std::string(argv[(2*i)+6+polyLine]);
			iss.str(origins);
			iss >> xcoord >> ycoord >> xend >>yend;
			iss.str("");
			iss.seekg(0);
			framesize = std::string(argv[(polyLineMultiplier*2)+4+polyLine])+" "+std::string(argv[(polyLineMultiplier*2)+5+polyLine]);
			iss.str(framesize);
			iss >> framex >> framey;
			frames.setSize(framex,framey,Ncols,Nrows);
			frames.gradientCalculator(xcoord,ycoord,xend,yend,pixels);
		}
		delete [] pixels;
		for (int k=((polyLineMultiplier*2)+6+polyLine);k<argc;k+=3)
		{
			option = std::string(argv[k+1]);
			filename = std::string(argv[k+2]);
			frames.write(filename,option);
		} 
	}
	in.close();	
	return 0;
}
