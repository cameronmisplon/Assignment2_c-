#ifndef __FRAMESEQUENCE__
#define __FRAMESEQUENCE__
#include <vector>
#include <string>
#include <iostream>
#include <math.h>

namespace MSPCAM001{
	class FrameSequence{
		std::vector<unsigned char **> imageSequence;
		int frameSizeX,frameSizeY,imageSizeX,imageSizeY;
		float gradient;
		public:
		FrameSequence();
		~FrameSequence();
		// void write(std::string filename, std::string option std::string pgm, std::string comments);
		void setSize(int framex, int framey, int imagex, int imagey);
		void read(unsigned char *pixels,int originx, int originy);
		void gradientCalculator(int xcoord, int ycoord, int xend, int yend, unsigned char * pixels);
	};
}
#endif
		
