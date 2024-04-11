#ifndef DEBUG_HPP
#define DEBUG_HPP

#ifdef DEBUG_PARAMETER
#define DEBUG_PARAMETER_INTERNAL
#endif

class Debug{
public:
	static void setDebug(char* debug_str);
	static int getMask(void);
	static void printParameterTemplate(void);
	static void printParameterInfo(void);
	static void printInt(int level, char* name, int number);
	static void printRawDataShort(int level, char* name, char* buffer, int len);
	static void printRawDataShortLong(int level_short, int level_long, char* name, char* buffer, int len);
private:
	static int debug_mask;
	static void printRawHeader(char* name, int len, char* extra);
};

#ifdef DEBUG_PARAMETER_INTERNAL
	#define DEBUG_PRINT_INT(a, b, c) Debug::printInt(a, b, c)
	#define DEBUG_PRINT_RAW_SHORT_DATA(a, b, c, d) Debug::printRawDataShort(a, b, c, d)
	#define DEBUG_PRINT_RAW_SHORTLONG_DATA(a, b, c, d, e) Debug::printRawDataShortLong(a, b, c, d, e)
#else
	#define DEBUG_PRINT_INT(a, b, c)
	#define DEBUG_PRINT_RAW_SHORT_DATA(a, b, c, d)
	#define DEBUG_PRINT_RAW_SHORTLONG_DATA(a, b, c, d, e)
#endif

//info printout
#ifdef DEBUG_PARAMETER_INTERNAL
	#define DEBUG_PARAM_STR "|[-debug info|mask]"
#else
	#define DEBUG_PARAM_STR ""
#endif

#define DEBUG_ALL_OFF						0
#define DEBUG_FTDI_DATA_WRITE				1
#define DEBUG_FTDI_DATA_READ				2
#define DEBUG_APP_PAGE_NUMBER				4
#define DEBUG_NAND_MAIN_DATA_SHORT			8
#define DEBUG_NAND_MAIN_DATA_FULL			16
#define DEBUG_NAND_OOB_DATA_SHORT			32
#define DEBUG_NAND_OOB_DATA_FULL			64
#define DEBUG_NAND_ADDRESSING				128
#define DEBUG_NAND_ONFI_DATA_FULL			256

#endif
