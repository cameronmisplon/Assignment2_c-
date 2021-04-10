#include "FrameSequence.h"

namespace MSPCAM001{
	MSPCAM001::FrameSequence::FrameSequence(): frameSizeX(0) , frameSizeY(0)
	{}
	MSPCAM001::FrameSequence::~FrameSequence()
	{
		if(!((this->imageSequence).empty()))
		{
			for(unsigned char ** frame : this->imageSequence)
			{
				for(int i=0;i<this->frameSizeY;i++)
				{
					delete [] frame[i];
				}
				delete [] frame;
			}
			imageSequence.clear();
		}
	}
	void MSPCAM001::FrameSequence::setSize(int framex, int framey, int imagex, int imagey)  
	{
		this->frameSizeX=framex;
		this->frameSizeY=framey;
		this->imageSizeX=imagex; 
		this->imageSizeY=imagey;
	}
	void MSPCAM001::FrameSequence::read(unsigned char *pixels, int originx, int originy)
	{
		unsigned char ** frame = new unsigned char * [this->frameSizeY];
		for (int i=0; i<this->frameSizeX; i++){
			frame[i] = new unsigned char[this->frameSizeX];
		}
		for (int j=originy;j<originy+this->frameSizeY;j++)
		{
			for (int k=originx;k<originx+this->frameSizeX;k++)
			{
				frame[j-originy][k-originx] = pixels[((this->imageSizeX)*j)+k];
			}
		}
		(this->imageSequence).push_back(frame);
	}
}	
			
