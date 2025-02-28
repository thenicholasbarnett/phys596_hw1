This is my submission for homework assignment one of the computational physics course this Spring 2025 semester. I’ve uploaded two header files, the text file of data given, a c++ source code script, and screenshots of print statements produced when running the script.

I successfully did the following parts of the assignment:
Write header files with various functions to determine the best fit line through some given data.
Used these header files in a main source script to generate print statements of the fit information. 
Cast the values in the text file into arrays.
Determined where each event start and stops in the text file.
Determine the fitting parameters a and b, where y=a+bx, in the best fit line through the data in each of the six “events” in the data.
Determine the chi^2/ndf values for each of the fits found.

I did not successfully complete the following parts of the assignment:
Determine the variance or error in the fitting parameters.
Use vitis to execute the code.
Use hls types for integers and floats to optimize code.

I attempted finding the error in the fit parameters, but end up getting nans sadly. The functions I wrote in the math_functions.h file should correctly be generating these uncertainties, but I believe somewhere my types are causing the issue potentially. I’ve been working on getting correct values for these uncertainties, but did not ultimately give myself enough time to complete all of the assignment unfortunately. My next steps were to finish getting the uncertainties, then introduce these hls types as well as other optimization, and last would look to run this through vitis as opposed to my local terminal.
