
   /***********************************************
   *
   *   file d:\cips\side.c
   *
   *   Functions: This file contains
   *      main
   *      print_side_usage
   *
   *   Purpose:
   *      This file contains the main calling
   *      routine for a program which
   *      takes two images and pastes them
   *      together side by side or top to bottom
   *      into a new image file.
   *
   *      There are three files: two input files
   *      (file1 and file2), and one output
   *      file (file3).
   *
   *   External Calls:
   *                  read_image_array
   *                  write_image_array
   *                  get_image_size
   *                  allocate_image_array
   *                  free_image_array
   *                  create_allocate_tiff_file
   *                  create_allocate_bmp_file
   *                  read_bm_header
   *                  read_bmp_file_header
   *                  read_bm_header
   *
   *   Modifications:
   *      19 April 1992 - created
   *      13 August 1998 - modified to work on an
   *           entire image at one time.
   *      19 September 1998 - modified to work with 
   *            all I O routines in imageio.c.
   *
   *************************************************/

	#include "side.h"

	void print_side_usage();

	int main(sint32_t argc, char_t *argv[])
	{
		errFlag_side = eReturnOK;
		char_t     method[80], name1[80], name2[80], name3[80];
	    sint32_t      i, j;
	   	uint32_t     length1, length2, length3, 
		        width1, width2, width3;
	   	sint16_t    **image1, **image2, **image3;
	   	 bmpfileheader      bmp_file_header;
	   	 bitmapheader       bmheader;
	   	 tiff_header_struct tiff_file_header;

		   /******************************************
		   *
		   *  Interpret the command line parameters.
		   *
		   *******************************************/

	   	if(argc != 5)
		{
			print_side_usage();
		  	errFlag_side = eNotSuffArg;
	   	}
		
		if(errFlag_side == eReturnOK)
		{
	   		strcpy(name1,  argv[argv1]);
	   		strcpy(name2,  argv[argv2]);
	   		strcpy(name3,  argv[argv3]);
	   		strcpy(method, argv[argv4]);

		   	if(method[0] != 't' && method[0] != 'T' && method[0] != 's' && method[0] != 'S')
			{
			  printf("\nERROR: Did not choose a valid method");
			  print_side_usage();
			  errFlag_side = eNotValidMethod;
		   	}

			if(errFlag_side == eReturnOK)
			{

		   		if(does_not_exist(name1))
				{
			  	printf("\nERROR: Input file %s does not exist", name1);
			  	print_side_usage();
			  	errFlag_side = eNoInputFile1;
		   		}

				if(errFlag_side == eReturnOK)
				{

		   			if(does_not_exist(name2))
					{
			  		printf("\nERROR: Input file %s does not exist", name2);
			  		print_side_usage();
			  		errFlag_side = eNoInputFile2;
		   			}

			   /*******************************************
			   *
			   *   Look at the sizes of the two input
			   *   files.  Ensure they are the correct
			   *   dimensions and set the dimensions
			   *   of the output image.
			   *
			   ********************************************/
					if(errFlag_side == eReturnOK)
					{
						get_image_size(name1, &length1, &width1);
					   	get_image_size(name2, &length2, &width2);

					   	if(method[0] == 'T' || method[0] == 't')
						{
						  	if(width1 != width2)
							{
							 	printf("\nERROR: input images are not the same width");
							 	errFlag_side = eNotSameWidth;
						  	}  /* ends if widths are unequal */
						  	else
							{
							 	width3  = width1;
							 	length3 = length1 + length2;
						  	}  /* ends else widths are ok */
					   	}  /* ends if method is T */

						if(errFlag_side == eReturnOK)
						{

					   		if(method[0] == 'S' || method[0] == 's')
							{
						  		if(length1 != length2)
								{
							 		printf("\nERROR: input images are not the same length");
							 		errFlag_side = eNotSameLength;
						  		}  /* ends if lengths are unequal */
						  		else
								{
							 	width3  = width1 + width2;
							 	length3 = length1;
						  		}  /* ends else lengths are ok */
					   		}  /* ends if method is S */

						   /*******************************************
						   *
						   *   Create the output image to be the same
						   *   type as the first input image.
						   *
						   ********************************************/
							if(errFlag_side == eReturnOK)
							{
					   			if(is_a_tiff(name1)){
						  		read_tiff_header(name1, &tiff_file_header);
						  		tiff_file_header.image_length = length3;
						  		tiff_file_header.image_width  = width3;
						  		create_allocate_tiff_file(name3, &tiff_file_header);
					   		}

					   		if(is_a_bmp(name1))
							{
						  		read_bmp_file_header(name1, &bmp_file_header);
						  		read_bm_header(name1, &bmheader);
						 		bmheader.height = length3;
						  		bmheader.width  = width3;
						  		create_allocate_bmp_file(name3, &bmp_file_header, &bmheader);
					   		}


						   /*******************************************
						   *
						   *   Allocate the image arrays and read the
						   *   two input images.
						   *
						   *********************************************/
					   
						   	image1 = allocate_image_array(length1, width1);
						   	image2 = allocate_image_array(length2, width2);
						   	image3 = allocate_image_array(length3, width3);

						   	read_image_array(name1, image1);
						   	read_image_array(name2, image2);

							   /*******************************************
							   *
							   *   First do the side by side option.
							   *
							   *********************************************/

						   	if(method[0] == 'S' || method[0] == 's')
							{
								for(i=0; i<length1; i++)
								 	for(j=0; j<width1; j++)
										image3[i][j] = image1[i][j];

							  	for(i=0; i<length2; i++)
								 	for(j=0; j<width2; j++)
										image3[i][j+width1] = image2[i][j];

						   	}  /* ends if side-by-side method */


							   /********************************************
							   *
							   *   Now do the top to bottom option.
							   *
							   *********************************************/

						   	if(method[0] == 'T' || method[0] == 't')
							{
								for(i=0; i<length1; i++)
								 	for(j=0; j<width1; j++)
										image3[i][j] = image1[i][j];

							  	for(i=0; i<length2; i++)
								 	for(j=0; j<width2; j++)
										image3[i+length1][j] = image2[i][j];

						   	}  /* ends top-to-bottom method */

						   	write_image_array(name3, image3);

						   	free_image_array(image1, length1);
						   	free_image_array(image2, length2);
						   	free_image_array(image3, length3);


							}
						}
					}
				}
			}
		}
	return errFlag_side;
	}
