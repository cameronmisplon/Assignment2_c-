#include "FrameSequence.h"

namespace MSPCAM001{
	MSPCAM001::FrameSequence::FrameSequence(): frameSizeX(0) , frameSizeY(0), imageSizeX(0), imageSizeY(0), gradient(0)
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
	void MSPCAM001::FrameSequence::gradientCalculator(int xcoord, int ycoord, int xend, int yend, unsigned char * pixels)
	{
		gradient = (float)(yend-ycoord)/float(xend-xcoord);
		read(pixels,xcoord,ycoord);
		if (fabs(gradient)<=1.0)
		{
			if(xcoord <xend){
				for(int i=xcoord+1;i<=xend; i++)
				{
					if (ycoord < yend)
					{
						ycoord+=fabs(gradient);
					}
					else{
						ycoord-=fabs(gradient);
					}
					read(pixels,i,std::round(ycoord));
				}
			}
			else{
				for(int j=xcoord-1;j>=xend; j--)
				{
					if (ycoord < yend)
					{
						ycoord+=fabs(gradient);
					}
					else{
						ycoord-=fabs(gradient);
					}
					read(pixels,j,std::round(ycoord));
				}
			}
		}
		else{
			gradient = (float)(xend-xcoord)/(float)(yend-ycoord);
			if(ycoord <yend){
				for(int k=ycoord+1;k<=yend; k++)
				{
					if (xcoord < xend)
					{
						xcoord+=fabs(gradient);
					}
					else{
						xcoord-=fabs(gradient);
					}
					read(pixels,std::round(xcoord),k);
				}
			}
			else{
				for(int l=ycoord-1;l>=yend; l--)
				{
					if (xcoord < xend)
					{
						xcoord+=fabs(gradient);
					}
					else{
						xcoord-=fabs(gradient);
					}
					read(pixels,std::round(xcoord),l);
				}
			}
		}
	}
		
}	
			
