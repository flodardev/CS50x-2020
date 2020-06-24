#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

typedef uint8_t BYTE;
BYTE byte;

int main(int argc, char *argv[])
{
    // Argument count must be two only
    if (argc != 2)
    {
        printf("Usage: %s (.raw file)\n", argv[0]);
        printf("Program purpose: To recover JPGS from .raw file\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[optind];
    
    // Open input file
    // *inptr is a pointer to infile with read function
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Output filename
    // char type is 8 bit = 1 byte
    char outfile[byte]; 
    
    // Create *pointer for output file
    FILE *outptr;

    // 512 bytes
    unsigned char bytes[512];
    
    // Bool if jpeg is opened
    bool jpg = false;

    // Numbering of jpegs
    int i = 0;
    
    // Function
    while (fread(bytes, 512, 1, inptr))
    {
        // If the first 512 bytes starts with the 4 bytes of a JPEG
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            // If a jpg file is opened
            if (jpg == true)
            {
                // Close it so that the next output file can be opened signifying the next jpg file
                fclose(outptr);
                jpg = false;
            }
            
            // Name the jpg file starting from 000.jpg, i++
            sprintf(outfile, "%03i.jpg", i);
            
            // Open output file with append function
            outptr = fopen(outfile, "a");
            
            // Write the first block into the output file
            fwrite(bytes, sizeof(bytes), 1, outptr);
            
            // Update boolean value to true
            jpg = true;
            
            // Update jpg name
            i++;
        }
        else
        {
            if (jpg == true)
            {
                // Append next 512 blocks of non-headers
                fwrite(bytes, sizeof(bytes), 1, outptr);
            }
        }
    }
    // Close input file
    fclose(inptr);
    
    // Close output file
    fclose(outptr);
    
    return 0;
}