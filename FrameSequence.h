#ifndef __FRAMESEQUENCE__
#define __FRAMESEQUENCE__
#include <vector>
#include <string>
#include <iostream>

namespace MSPCAM001{
	class FrameSequence{
		std::vector<unsigned char **> imageSequence;
		int frameSizeX;
		int frameSizeY;
		public:
		FrameSequence();
		~FrameSequence();
		void write(std::string filename, std::string option std::string pgm, std::string comments);
		void setSize(int x, int y);
		void read(const unsigned char &pixels,int originx, int originy);
	};
}
#endif
		
