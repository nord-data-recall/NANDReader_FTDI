#include "Debug.hpp"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_SHORT_DATA_LIMIT		16
#define DEBUG_SHORT_DATA_LIMIT_STR		"16"

int Debug::debug_mask = DEBUG_ALL_OFF;

void Debug::setDebug(char* debug_str)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	debug_mask = strtol(debug_str, NULL, 0);
	printf("Setting debug mask as 0x%04X (%d)\n", debug_mask, debug_mask);
#endif
}

int Debug::getMask(void)
{
	return debug_mask;
}

void Debug::printParameterInfo(void)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	printf("Debugging system configuration:\n");
	printf("Run application with parameter -debug with numeric mask.\n");
	printf("In majority bits of mask independently turns on printing specific raw information.\n");
	printf("Currently supported bits of mask:\n");
	printf("0x%04X (%d) - FTDI data write, all bytes\n", DEBUG_FTDI_DATA_WRITE, DEBUG_FTDI_DATA_WRITE);
	printf("0x%04X (%d) - FTDI data read, all bytes\n", DEBUG_FTDI_DATA_READ, DEBUG_FTDI_DATA_READ);
	printf("0x%04X (%d) - NAND page number\n", DEBUG_APP_PAGE_NUMBER, DEBUG_APP_PAGE_NUMBER);
	printf("0x%04X (%d) - NAND data, first " DEBUG_SHORT_DATA_LIMIT_STR " bytes\n", DEBUG_NAND_MAIN_DATA_SHORT, DEBUG_NAND_MAIN_DATA_SHORT);
	printf("0x%04X (%d) - NAND data, all bytes (this override ""first " DEBUG_SHORT_DATA_LIMIT_STR " bytes"" printout)\n", DEBUG_NAND_MAIN_DATA_FULL, DEBUG_NAND_MAIN_DATA_FULL);
	printf("0x%04X (%d) - NAND OOB data, first " DEBUG_SHORT_DATA_LIMIT_STR " bytes\n", DEBUG_NAND_OOB_DATA_SHORT, DEBUG_NAND_OOB_DATA_SHORT);
	printf("0x%04X (%d) - NAND OOB data, all bytes (this override ""first " DEBUG_SHORT_DATA_LIMIT_STR " bytes"" printout)\n", DEBUG_NAND_OOB_DATA_FULL, DEBUG_NAND_OOB_DATA_FULL);
	printf("0x%04X (%d) - NAND addressing data, all bytes\n", DEBUG_NAND_ADDRESSING, DEBUG_NAND_ADDRESSING);
	printf("0x%04X (%d) - NAND ONFI data, all bytes\n", DEBUG_NAND_ONFI_DATA_FULL, DEBUG_NAND_ONFI_DATA_FULL);
#endif
}

void Debug::printParameterTemplate(void)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	printf("  -debug info to print supported debug masks\n");
	printf("  -debug mask set debug mask\n");
#endif
}

void Debug::printRawHeader(char* name, int len, char* extra)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	printf("\n"); //just to make progress indicator happy
	printf("DEBUG %s, size 0x%04X (%d)%s\n", name, len, len, extra);
#endif
}

void Debug::printInt(int level, char* name, int number)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	if (0 == (debug_mask & level))
		return;
	printf("DEBUG %s 0x%08X (%d)\n\n", name, number, number);
#endif
}

void Debug::printRawDataShort(int level, char* name, char* buffer, int len)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	if (0 == (debug_mask & level))
		return;
	if (len > DEBUG_SHORT_DATA_LIMIT)
	{
		printRawHeader(name, len, ", only " DEBUG_SHORT_DATA_LIMIT_STR " initial bytes");
		len = DEBUG_SHORT_DATA_LIMIT;//just for nice printout
	}
	else
		printRawHeader(name, len, "");
	printf("DEBUG ");
	for (int x=0; x<len; x++)
		printf("%02X ", buffer[x] & 0xFF);
	printf("\n");
#endif
}

void Debug::printRawDataShortLong(int level_short, int level_long, char* name, char* buffer, int len)
{
#ifdef DEBUG_PARAMETER_INTERNAL
	int last_part_offset;
	if (0 != (debug_mask & level_long))
	{//print long level long
		printRawHeader(name, len, "");
		for (int row = 0; row < len / 16; row++)
		{
			printf("DEBUG 0x%04X | ", row * 16);
			for (int col = 0; col < 16; col++)
			{
				printf("%02X ", buffer[row * 16 + col] & 0xFF);
			}
			printf("\n");
		}
		if (0 != len % 16)
		{
			last_part_offset = (len / 16) * 16;
			printf("DEBUG 0x%04X | ", last_part_offset);
			for (int col = 0; col < len%16; col++)
				printf("%02X ", buffer[last_part_offset + col] & 0xFF);
			printf("\n");
		}
		return;//exit earlier
	}
	printRawDataShort(level_short, name, buffer, len);
#endif
}
