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
			imageSequence.clear()
		}
	}
	void MSPCAM001::FrameSequence::setSize(int x, int y) : frameSizeX(x), frameSizeY(y)
	{}
	void MSPCAM001::FrameSequence::read(const unsigned char &pixels, int originx, int originy)
	{
		unsigned char ** frame = new unsigned char * [this->frameSizeY];
		for (int i=0; i<this->frameSizeX; i++){
			frame[i] = new unsigned char[this->frameSizeX];
		}
		for 		
