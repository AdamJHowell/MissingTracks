/*
This is a simple application that I wrote to find digital music that was missing the first track.
I used a media player, which once had a bug, where it deleted track one from the file system.
So this was my original solution.  This has been rewritten in Java with more features.

Input is expected to be a text file of the directory structure, sorted lexicographically.
Output will be a list of "track two" files where no "track one" was found.

If two file names are passed to this program, the first will be used as the input file, and the second will be used as the output file.
If any other number of command line parameters are passed to this program, "tracks.txt" will be used for the input file, and the output file will be the date and time.
Similarly named output files are overwritten without warning!  That's how I roll.
*/


#include "pch.h"
#include <iostream>
#include <time.h>
#include <fstream>
#include <string>
#include <ctime>


/*
	currentDateTime() will return a string representing the local date and time.
	Formatting specifiers can be found here: http://www.cplusplus.com/reference/ctime/strftime/
*/
const std::string currentDateTime()
{
	time_t now = time( 0 );
	struct tm tstruct;
	char buf[80];
	localtime_s( &tstruct, &now );
	strftime( buf, sizeof( buf ), "%Y-%m-%d_%H%M%S", &tstruct );

	return buf;
}


int main( int argc, char *argv[] )
{
	std::string inFilename = "tracks.txt";	// Default input filename.
	std::string outFilename;				// Output filename.
	std::string track1String = " - 01 - ";	// The text we suspect may be missing.
	std::string track2String = " - 02 - ";	// The text we search for to know we have passed track 1.
	std::string currentLine = "";			// Current line contents.
	std::string prevLine = "";				// Previous line contents.
	int track1Count = 0;					// Counter for how many times a track 1 was found.
	int track2Count = 0;					// Counter for how many times a track 2 was found.
	int missingTracks = 0;					// Counter for how many tracks are missing.
	clock_t startClock;						// A temporary variable to hold the current clock time.
	clock_t endClock;						// A temporary variable to hold the current clock time.

	// If we are passed two command line parameters, use the first as the input filename and the second as the output filename.
	if( argc == 3 )
	{
		inFilename = argv[1];
		outFilename = argv[2];
	}
	else
	{
		// Set the output filename to be the current date and time.
		outFilename = std::string( currentDateTime() ) + std::string( ".txt" );
	}
	std::cout << "Adam Howell's missing track locator." << std::endl;
	// Odd things will happen if we write to the input file, so check for this.
	if( inFilename.compare(outFilename) == 0 )
	{
		std::cout << "Input and output filenames MUST NOT be the same!" << std::endl;
		return -1;
	}
	std::cout << "Reading from: " << inFilename << std::endl;
	std::cout << "Writing output to: " << outFilename << "\n" << std::endl;

	// Open a file stream based on the output filename.
	std::ofstream outFile( outFilename );

	// If the file stream creation failed...
	if( outFile.fail() )
	{
		// Announce that the file did not open properly.
		std::cout << "\nUnable to open the output file: " << outFilename << std::endl;
		return -1;
	}

	// Open a file stream based on the input filename.
	std::ifstream trackFile( inFilename );

	// If the file stream creation failed...
	if( trackFile.fail() )
	{
		// Announce that the file did not open properly.
		std::cout << "\nUnable to open the input file " << inFilename << " \nPlease ensure it is in the same directory as this executable." << std::endl;
		return -1;
	}
	else
	{
		std::cout << "Searching the input file: " << inFilename << std::endl;
		// Get the starting tick.
		startClock = clock();

		// Loop until the end of the file, processing each line.
		while( !trackFile.eof() )
		{
			getline( trackFile, currentLine );
			// Scan currentLine for " - 02 - ".
			currentLine.find( track2String );
			// If we find track 2...
			if( currentLine.find( track2String ) != std::string::npos )
			{
				track2Count++;
				// Test code.
				//cout << "Found track 2" << std::endl;
				// Scan prevLine for " - 01 - ", and if missing...
				if( prevLine.find( track1String ) != std::string::npos )
				{
					// Increment track1Count to show we located a track 1.
					track1Count++;
				}
				else
				{
					// Load the current line into the output file.
					outFile << currentLine << std::endl;
					// Increment missingTracks to show we located a missing track 1.
					missingTracks++;
				}
			}
			else
			{
				// Prepare to check the next line by loading currentLine into prevLine.
				prevLine = currentLine;
				// Restart this while loop.
				continue;
			}
		}
	}
	// Get the ending tick.
	endClock = clock();

	// Close the file handles.
	trackFile.close();
	outFile.close();

	// Display the results.
	if( endClock / CLK_TCK )
	{
		std::cout << "Scan completed in " << endClock / CLK_TCK << " second (" << endClock << " ticks)." << std::endl;
	}
	else
	{
		std::cout << "Scan completed in " << endClock / CLK_TCK << " seconds (" << endClock << " ticks)." << std::endl;
	}
	std::cout << "Found " << track1Count << " first tracks" << std::endl;
	std::cout << "Found " << track2Count << " second tracks" << std::endl;
	std::cout << missingTracks << " possible albums with missing first tracks written to: " << outFilename << std::endl;
}
