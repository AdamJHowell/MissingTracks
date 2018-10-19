# MissingTracks
An update of my C++ missing track program.

This is a simple application that I wrote to find digital music that was missing the first track.
I used a media player, which once had a bug, where it deleted track one from the file system.
So this was my original solution.  This has been rewritten in Java with more features.

Input is expected to be a text file of the directory structure, sorted lexicographically.
Output will be a list of "track two" files where no "track one" was found.

If two file names are passed to this program, the first will be used as the input file, and the second will be used as the output file.
If any other number of command line parameters are passed to this program, "tracks.txt" will be used for the input file, and the output file will be the date and time.
Similarly named output files are overwritten without warning!  That's how I roll.
