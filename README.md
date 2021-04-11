- Makefile has no run method due to the nature of the program requiring unique arguments every time it is run. There also is no support for clearing output images seperately to the input images as they are created in the same directory as the source files (possible solution have input images in separate directory)
- Program relies on arguments to follow requirements precisely, any invalid order of arguments will cause some errors. The specified format is:
	<filename> <-t or -p> [n](only for -p) <x1> <y1> <x2> <y2>.....<xn> <yn> <-s> <framesizex> <framesizey> <-w> <option> <outputname> [-w] .....
- The image is always created with the top left hand corner of the image starting at the given (x,y) and moving to the destination (x,y)
- The program support for images which move off of the original image size, allocates the missing parts of the image with pixel values of 255
- There is no support for the acceleration/deceleration function, but there is as previously mentioned polyline support 
