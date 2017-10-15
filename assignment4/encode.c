/*
Darren Dawson
dwdawson@ucsc.edu
Huffman Encoder
*/

# include <stdio.h>
# include <stdlib.h>
# include <getopt.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>

# include "bitvector.h"
# include "hufftree.h"
# include "priorityqueue.h"

//---parseArguments------------------------------------------------------

// Uses command line flags to set up program
void parseArguments(int argc, char *argv[],
	char **filepath, char **destination, bool *verbose)
	{
		char arg; // use to hold argument

		while ((arg = getopt(argc, argv, "i:o:v")) != -1)
		{
			switch (arg)
			{
				case 'i': // input file
				*filepath = (char*)optarg;
				break;
				case 'o': // output destination
				*destination = (char*)optarg;
				break;
				case 'v': // verbose mode
				*verbose = true;
				break;

			}
		}
		return;
	}

	//---checkValidFile------------------------------------------------------

	// returns true if file can be opened
	// While slightly innefficient, this function is here to increase
	// readability of the general program
	bool checkValidFile(char *filepath)
	{
		FILE *file = fopen(filepath, "r");
		bool result = false;

		if (file != NULL)
		{
			result = true;
			fclose(file);
		}

		return result;
	}

	//---setHistogram--------------------------------------------------------

	// reads a file and creates a frequency measure for bytes
	// also sets determines number of bytes in file
	void setHistogram(int *histogram, uint64_t *size, char *filepath)
	{
		FILE *file;
		long fileSize;
		char *buffer;
		uint8_t currentByte;

		// open file
		file = fopen(filepath, "r");

		// get size of file
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		(*size) = (uint64_t)fileSize;
		rewind(file);

		// allocate memory and read file
		buffer = (char*)calloc(1, sizeof(char)*fileSize);
		fread(buffer, 1, fileSize, file);

		// set histogram
		for (int i = 0; i < fileSize; i++)
		{
			currentByte = (uint8_t)buffer[i];
			histogram[currentByte] += 1;
			//(*size)++;
		}
		histogram[0] += 1; // make sure there will always be a tree
		histogram[255] += 1; // This was Darrell Long's idea

		fclose(file);
		free(buffer);
		return;
	}

	//---printHistogram------------------------------------------------------

	// prints a histogram
	void printHistogram(int *histogram)
	{
		int uniqueBytes = 0;
		int totalBytes = 0;

		printf("\nHistogram----\n");
		for (int i = 0; i < 256; i++)
		{
			if (histogram[i] != 0)
			{
				uniqueBytes++;
				totalBytes += histogram[i];
				printf("%d: %d\n", i, histogram[i]);
			}
		}
		printf("Unique Bytes: %d\n", uniqueBytes);
		printf("Total Bytes: %d\n", totalBytes);
		printf("----Histogram\n\n");
		return;
	}

	//---findNumberOfLeaves--------------------------------------------------

	// uses histogram to return the number of leaves tree will have
	int findNumberOfLeaves(int *histogram)
	{
		int num = 0;
		for (int i = 0; i < 256; i++)
		{
			if (histogram[i] > 0)
			{
				num++;
			}
		}
		return num;
	}

	//---assignCodes---------------------------------------------------------

	// walks huffman tree and assigns huffman codes
	void assignCodes(treeNode *node, bitV **codes, bitV currentCode)
	{
		if (node->leaf)
		{
			codes[node->symbol] = newBitVector(8);
			appendCode(codes[node->symbol], &currentCode);
			return;
		}

		// walk left
		appendBit(&currentCode, false);
		assignCodes(node->left, codes, currentCode);

		// walk right
		removeBitFromEnd(&currentCode); // return to parent
		appendBit(&currentCode, true);
		assignCodes(node->right, codes, currentCode);
		return; // bubble up
	}

	//---deleteCodes---------------------------------------------------------

	// frees all the bitvectors in codes
	void deleteCodes(bitV **codes)
	{
		for (uint32_t i = 0; i < 256; i++)
		{
			if (codes[i] != NULL)
			{
				deleteBitVector(codes[i]);
			}
		}
		free(codes);
		return;
	}

	//---printCodes----------------------------------------------------------

	// prints out huff codes
	void printCodes(bitV **huffCodes)
	{
		for (uint32_t i = 0; i < 255; i++)
		{
			if (huffCodes[i] != NULL)
			{
				printBitVector(huffCodes[i]);
			}
		}
		return;
	}

	//---encodeFile----------------------------------------------------------

	// reads a file and converts each byte into its respective code
	// dumps those codes into a bitvector
	void encodeFile(bitV *encodedFile, bitV **codes, char *filepath)
	{
		FILE *file;
		long fileSize;
		char *buffer;
		uint8_t currentByte;

		// open file
		file = fopen(filepath, "r");

		// get size of file
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		rewind(file);

		// allocate memory and read file
		buffer = (char*)calloc(1, sizeof(char)*fileSize);
		fread(buffer, 1, fileSize, file);

		// convert bytes
		for (int i = 0; i < fileSize; i++)
		{
			currentByte = (uint8_t)buffer[i];
			appendCode(encodedFile, codes[currentByte]);

			// print it for debugging
			//printf("Original Byte: %u, code: ", currentByte);
			//printBitVector(codes[currentByte]);
			//printf("\n");

		}

		fclose(file);
		free(buffer);
		return;
	}

	//---findSpread----------------------------------------------------------

	// uses histogram to find and print average/sd of byte frequencies
	void findSpread(int *histogram)
	{
		float average = 0;
		float sum = 0;
		float sd = 0;
		uint8_t mostCommonByte = 0;
		int mostCommonFrequency = 0;
		float numBytes = 0;

		// find sum, most common bytes
		for (uint32_t i = 0; i < 256; i++)
		{
			if (histogram[i] != 0)
			{
				numBytes++;
				sum += histogram[i];

				if (histogram[i] > mostCommonFrequency)
				{
					mostCommonFrequency = histogram[i];
					mostCommonByte = i;
				}
			}
		}

		// find average
		average = sum / numBytes;

		// find sd
		for (uint32_t i = 0; i < 256; i++)
		{
			// sd = average distance to average
			if (histogram[i] != 0)
			{
				sd += pow(histogram[i] - average, 2);
			}
		}
		sd = sqrt(sd / numBytes);

		// print statistics
		printf("Average Byte Frequency: %f\n", average);
		printf("Standard Deviation of Byte Frequencies: %f\n", sd);
		printf("Most Common Byte: %u (%c)\n", mostCommonByte, mostCommonByte);
		printf("Frequency of Most Common Byte: %d\n", mostCommonFrequency);
		return;
	}

	//=======================================================================
	//---MAIN----------------------------------------------------------------

	int main(int argc, char *argv[])
	{
		//-------------------------------------------
		// 1) Declare Variables
		//-------------------------------------------
		char *filepath = NULL; // file to open and encode
		char *destination = NULL; // output file name
		bool verbose = false;
		int histogram[256] = {0};
		huffPQueue *treeQueue;

		treeNode *huffmanTree = NULL;
		treeNode *tempTree = NULL;

		bitV **huffCodes = (bitV**)calloc(256, sizeof(bitV*));
		bitV *currentCode = newBitVector(8); // use in step 6

		// ENCODED FILE
		bitV *encodedFile;
		uint32_t sizeOfEncodedFile;
		uint32_t magicNumber = 0xdeadd00d;
		uint64_t sizeOfOriginalFile;
		uint16_t sizeOfHuffTree;

		// ENCODED TREE INSTRUCTIONS
		char *encodedTree;
		int index = -1; // keep track of index when building instructions
		uint32_t numLeaves = 0;

		// STATISTICS
		float changeInSize = 0;



		//printf("Step 1 complete\n");


		//-------------------------------------------
		// 2) Parse Arguments
		//-------------------------------------------
		parseArguments(argc, argv, &filepath, &destination, &verbose);

		// make sure there is a filepath - if not, exit program
		if (filepath == NULL || !checkValidFile(filepath))
		{
			printf("Please input a correct file name to compress\n");
			deleteBitVector(currentCode);
			deleteCodes(huffCodes);
			return 1;
		}
		//printf("Step 2 complete\n");


		//-------------------------------------------
		// 3) set up histogram
		//-------------------------------------------
		setHistogram(histogram, &sizeOfOriginalFile, filepath);
		//printf("Step 3 complete\n");


		//-------------------------------------------
		// 4) determine sizes for data structures
		//-------------------------------------------
		// determine size of tree
		numLeaves = findNumberOfLeaves(histogram);
		treeQueue = newHuffPQueue(numLeaves + 1); // create queue for tree
		sizeOfHuffTree = 3 * numLeaves - 1; // find size of tree
		encodedTree = (char*)calloc(sizeOfHuffTree, sizeof(char));

		// determine size of bitvector that contains all encoded bits
		sizeOfEncodedFile = 112 + sizeOfHuffTree + sizeOfOriginalFile * 8;
		encodedFile = newBitVector(sizeOfEncodedFile);
		//printf("Step 4 complete\n");


		//-------------------------------------------
		// 5) Use histogram to set up priority queue
		//-------------------------------------------
		for (uint32_t i = 0; i < 256; i++)
		{
			if (histogram[i] >= 1)
			{
				treeNode *node = newNode(i, true, histogram[i]);
				enqueueHuffPQueue(treeQueue, node);
			}
		}

		//printf("Step 5 complete\n");


		//-------------------------------------------
		// 6) Use priority queue to create tree
		//-------------------------------------------
		// pop off top two items in queue
		// join them together and push them back into queue
		// if tree is empty, you've found root
		while (!emptyHuffPQueue(treeQueue))
		{
			huffmanTree = dequeueHuffPQueue(treeQueue); // get first treeNode

			if (!emptyHuffPQueue(treeQueue))
			{
				// join the 2 nodes together and push it back into queue
				tempTree = dequeueHuffPQueue(treeQueue);
				huffmanTree = join(huffmanTree, tempTree);
				enqueueHuffPQueue(treeQueue, huffmanTree);
			}
		}

		//printf("Step 6 complete\n");


		//-------------------------------------------
		// 7) Use huffman tree to create bit codes
		//-------------------------------------------
		assignCodes(huffmanTree, huffCodes, *currentCode);

		// encode the tree (instructions to recreate it)
		index = -1;
		generateTreeInstructions(huffmanTree, encodedTree, &index);

		// delete memory we don't need anymore
		deleteBitVector(currentCode);
		deleteTree(huffmanTree);
		//printf("Step 7 complete\n");


		//-------------------------------------------
		// 8) Encode the file
		//-------------------------------------------
		appendUInt32(encodedFile, magicNumber);
		appendUInt64(encodedFile, sizeOfOriginalFile);
		appendUInt16(encodedFile, sizeOfHuffTree);
		appendString(encodedFile, encodedTree, sizeOfHuffTree);

		encodeFile(encodedFile, huffCodes, filepath);
		//printBitVector(encodedFile);

		//printf("Step 8 complete\n");


		//-------------------------------------------
		// 9) Dump bit vector into encoded File
		//-------------------------------------------
		dumpBitVectorToFile(encodedFile, destination);

		if (destination != NULL)
		{
			printf("Compressed to file: %s\n", destination);
		}

		//-------------------------------------------
		// Print Statistics
		//-------------------------------------------
		if (verbose)
		{
			// get data
			changeInSize = (float)(encodedFile->lastBit/8) /
			(float)(sizeOfOriginalFile);

			// print data
			printf("\n---Statistics-------------------------------------\n");
			printf("# of bytes of original file: %lu\n", sizeOfOriginalFile);
			printf("# of Bytes of encoded file:  %u\n", encodedFile->lastBit/8);
			printf("Percent change: %f\n-\n", (1-changeInSize) * 100);
			findSpread(histogram);
			printf("-\nSize of Encoded Tree Instructions: %u\n", sizeOfHuffTree);
			printf("Number of leaves: %u\n", numLeaves);
			printf("---------------------------------------------------\n\n");
		}
		//---------------------------------------------------------------------
		// Exit program
		//---------------------------------------------------------------------
		// delete codes
		free(encodedTree);
		deleteBitVector(encodedFile);
		deleteCodes(huffCodes);
		deleteHuffPQueue(treeQueue);

		return 0;
	}
