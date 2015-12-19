# Remer-Bulk-Renamer

REQUIREMENTS for using this program as of NOW:
  1. GCC compiler for C++ (g++)
  2. Windows Operating System
  3. Show extension of known file types is turned on in windows explorer menu

This Bulk Renamer was created for people with lots of personal collections and the need for renaming the files (Only belonging to the same series) for use using Windows Operating System. Although this program currently suppoorts only video files with following extensions:
  1. mp4
  2. flv
  3. avi
  4. mkv
  5. wmv
however, it would be extended to support other file types and custom file types if required.

The contents of this project has three main files:
  1. Renamer.bat - windows batch executable which takes in input from user and creates the executable used for renaming;
  2. Renamer.cpp - cpp file containing the full program
  3. Renamer.min.cpp - minified version of Renamer.cpp with inserted escape characters for use with Renamer.bat

INSTRUCTIONS FOR USING: 
### For optional part of input, just press enter if you have no input
  1. Copy and paste the Renamer.bat file in the folder containing the files to be renamed;
  2. Run Renamer.bat
  3. [REQUIRED] Put the title of the series
  4. [OPTIONAL] Put any prefix string preceeding the Episode Number or Serial Number of the file. For example if the file name is:
        file-name EP345.mp4 -> put "EP" (without quotes) as input
  5. [OPTIONAL] Input any particular string or phrase that is present in any number of files that is not required
  6. [OPTIONAL] Input any phrase that you want to add to the end of string (before the extension)
