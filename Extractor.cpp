#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "FrameSequence.h"
#include <math.h>

int main(int argc, char* argv[])
{
	std::ifstream in("sloan_image.pgm", std::ios::binary | std::ios::in);
	if (in){
		std::string pgm,comments,sizedata,brightness,origins,framesize;
		int Ncols, Nrows,framex,framey;
		float gradient,xend,xcoord,yend,ycoord;
		MSPCAM001::FrameSequence frames;
		getline(in,pgm);
		getline(in,comments);
		getline(in,sizedata);
		std::istringstream iss(sizedata);
		iss >> Ncols >> Nrows;
		getline(in,brightness);
		unsigned char * pixels = new unsigned char[Ncols*Nrows]; //Use unsigned char because it has range 0-255 which is good for the pixel values
		in.read(reinterpret_cast<char *>(pixels),Ncols*Nrows);
			
		iss.str("");
		iss.seekg(0);
		origins = std::string(argv[2]) +" "+ std::string(argv[3]) +" "+ std::string(argv[4]) +" "+ std::string(argv[5]);
		iss.str(origins);
		iss >> xcoord >> ycoord >> xend >>yend;
		iss.str("");
		iss.seekg(0);
		framesize = std::string(argv[7])+" "+std::string(argv[8]);
		iss.str(framesize);
		iss >> framex >> framey;
		frames.setSize(framex,framey,Ncols,Nrows);
			
		gradient = (float)(yend-ycoord)/float(xend-xcoord);
		frames.read(pixels,xcoord,ycoord);
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
					frames.read(pixels,i,std::round(ycoord));
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
					frames.read(pixels,j,std::round(ycoord));
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
					frames.read(pixels,std::round(xcoord),k);
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
					frames.read(pixels,std::round(xcoord),l);
				}
			}
		}	
		delete [] pixels;
	}
	in.close();	
	return 0;
}
