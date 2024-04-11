# Summary
This section describes how to use debug feature.
Debug feature is available when application is build with preprocessor symbol *DEBUG_PARAMETER*. To enable printing debuging information, add parameter -debug *number* to enable specific debuging information. The *number* is logic sum (OR) of bits.

# Bits definition
* 0x0001 - raw data written to the FTDI driver
* 0x0002 - raw data read from the FTDI driver
* 0x0004 - number of page started for processing
* 0x0008 - raw data of main data of page, only 16 bytes
* 0x0010 - raw data of main data of page, all bytes
* 0x0020 - raw data of spare (OOB) data of page, only 16 bytes
* 0x0040 - raw data of spare (OOB) data of page, all bytes
* 0x0080 - raw data of addressing page
* 0x0100 - raw data of ONFI sector

# Information
The definition and number of bits may be changed in future. To print the definition of current build use, parameter *-debug info*. 
