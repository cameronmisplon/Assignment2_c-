#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
	try{
		std::ifstream in("sloan_image.pgm", std::ios::binary | std::ios::in);
		if (in){
			std::string pgm,comments,sizedata,brightness;
			int Ncols, Nrows;
			std::istringstream iss(sizedata);
			getline(in,pgm);
			getline(in,comments);
			getline(in,sizedata);
			iss >> Ncols >> Nrows;
			getline(in,brightness);
			unsigned char * pixels = new unsigned char[Ncols*Nrows]; //Use unsigned char because it has range 0-255 which is good for the pixel values
			in.read(reinterpret_cast<char *>(pixels),Ncols*Nrows);
			float temp= 0.0f;
			std::cout << comments << std::endl;
			for (int i=0;i<700;i++)
			{
				temp = (float) pixels[i];
				std::cout << temp << std::endl;
			} 
			delete [] pixels;
		}
		in.close();
	}
	catch(const std::bad_alloc& e){
	}	
	return 0;
}
