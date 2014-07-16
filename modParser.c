# include <stdio.h>
# include <stdlib.h>
# include <string.h>

FILE *fp;
FILE *fw;
int highestPattern = 0;
int highestNumber (int current);
int main (int argc, char *argv[]) {
	
	int c;
	char buffer[22];
	int sampleLength[2];
	int fineTune[1];
	int pattern[1];
	int sampleLenghts[32];
	int i = 0;
	int x = 0;
	int index = 0;
	int q=0;
	int songLength [1];
	int deltaCounter = 0;
	int highestPatternNumber = 0;
	#define songNameOffset 20
	#define sampleNameOffset 22
	#define nextSampleNameOffset 30
	#define sampleLengthOffset 2
	#define fineTuneOffset 1
	#define volumeOffset 1
	#define repeatOffset 2
	#define repleatLength 2
	#define patternTableOffset 952
	#define songLengthOffset 950
	#define patterns 1
	#define patternDataOffset 1084
	#define patternLength 1024
	int offset = 20;
	typedef int bool;
	#define true 1
	#define false 0
	
	fp = fopen(argv[1],"r");
	
	char *ptr;
	
		if (fp) {							
		for (i=0;i<31;i++){		// read sample names
		fseek( fp, offset, SEEK_SET );	
		fread(buffer, sampleNameOffset, 1, fp);											
		printf("%s""%d""%s""%s""\n","Sample",i,":",buffer);					
		fread(sampleLength,sampleLengthOffset,1,fp); // read sample lengths
		int64_t rightByte = *sampleLength & 0xFF ;		// read right byte < 512
		int64_t leftByte =  *sampleLength >> 7 ;		// how many times we go over 512
	//	printf("%d""\n", leftByte+(rightByte*512)); // length = rightByte + leftByte*512
		sampleLenghts[i] = leftByte+(rightByte*512);
		offset += nextSampleNameOffset;				// get next sample
	}
		printf("%s""\n","Samplelenghts");
		for (i=0;i<31;i++){		// read sample names
			printf("%s""%d""%s""%d""\n","sample",i,":",sampleLenghts[i]);
		}
	
		fseek( fp, songLengthOffset, SEEK_SET );	// how many patterns we have
		fread(songLength,1,1,fp);
	
		fseek( fp, patternTableOffset, SEEK_SET );	
		index = *pattern;
		for (x=0;x<*songLength;x++){
		fread(pattern,patterns,1,fp);
		highestPatternNumber = highestNumber ( *pattern-index);
		printf("%s""%d""%s""%d""\n","pattern",x,":", *pattern-index);
		}
		printf ("%s""%d""\n","highest pattern number is:",highestPatternNumber);
		
	    int *buffer = (int*)malloc(sampleLenghts[10]);
	
		fseek ( fp, patternDataOffset + (patternLength*highestPatternNumber+patternLength), SEEK_SET); // start of sample data

		char writeName[120];	// space for fileName
		char name[100];
		strcpy(name, argv[1]);
		printf ("%s",name);
		for (q=0;q<30;q++){	// go thru all samples
		sprintf(writeName, "%s sample:%d.raw",name, q);	// get individual filenames
		
			if (sampleLenghts[q]>0){	// write only if have sample larger than 0
				fw = fopen( writeName , "w" );
				fread(buffer, 1,sampleLenghts[q],fp); // read next sample to buffer
				fwrite (buffer,1,sampleLenghts[q],fw); // and write it to file
				fclose(fw);
				}
			}
		fclose(fp);
	
	}
		else {
			printf ("file not found\n");
			}
	}
	
	int highestNumber (int current) {
		if (current > highestPattern) {
			highestPattern = current;	
			
			}
	return highestPattern;	
	}