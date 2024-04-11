/*
Software to interface to a NAND-flash chip connected to a FT2232H IC.
Org (C) 2012 Jeroen Domburg (jeroen AT spritesmods.com)
New code and modifications (c) 2014 Bjoern Kerler (info AT revskills.de)

This program is free software: you can redistribute it and/or modify
t under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "NandDataLP.hpp"
#include "NandCmds.h"
#include "Debug.hpp"

//Data interface for large-page NAND chips

NandDataLP::NandDataLP(FtdiNand *ftdi, NandGeometry *id) :
 NandData(ftdi, id) {
	//NA
}

int NandDataLP::readPage(int pageno, char *buff, int max) {
	//Read a page
	char status=0;
	int bytes_read;
	m_ft->sendCmd(NAND_CMD_READ0);
	m_ft->sendAddr(pageno<<16L, m_id->getAddrByteCount());
	m_ft->sendCmd(NAND_CMD_READSTART);
	m_ft->waitReady();
	if (max>m_id->getPageSize()) max=m_id->getPageSize();
	if (max>0x1000)
	{
		int r1=m_ft->readData(buff, 0x1000);
		if (r1<0) return r1;
		max-=0x1000;
		bytes_read = r1+m_ft->readData(buff+0x1000, max);
		DEBUG_PRINT_RAW_SHORTLONG_DATA(DEBUG_NAND_MAIN_DATA_SHORT, DEBUG_NAND_MAIN_DATA_FULL, "NAND page data", buff, bytes_read);
		return bytes_read;
	}
	bytes_read = m_ft->readData(buff, max);
	DEBUG_PRINT_RAW_SHORTLONG_DATA(DEBUG_NAND_MAIN_DATA_SHORT, DEBUG_NAND_MAIN_DATA_FULL, "NAND page data", buff, bytes_read);
	return bytes_read;
}

int NandDataLP::readOob(int pageno, char *buff, int max) {
	int bytes_read;
	//Read the OOB for a page
	m_ft->sendCmd(NAND_CMD_READ0);
	m_ft->sendAddr((pageno<<16L)+m_id->getPageSize(), m_id->getAddrByteCount());
	m_ft->sendCmd(NAND_CMD_READSTART);
	m_ft->waitReady();
	if (max>m_id->getOobSize()) max=m_id->getOobSize();
	bytes_read = m_ft->readData(buff, max);
	DEBUG_PRINT_RAW_SHORTLONG_DATA(DEBUG_NAND_OOB_DATA_SHORT, DEBUG_NAND_OOB_DATA_FULL, "NAND page OOB data", buff, bytes_read);
	return bytes_read;
}

int NandDataLP::writePage(int pageno, char *buff, int len) {
	// Write page
	m_ft->sendCmd(NAND_CMD_SEQIN);
	m_ft->sendAddr(pageno<<16L, m_id->getAddrByteCount());
	m_ft->writeData(buff,len);
	m_ft->sendCmd(NAND_CMD_PAGEPROG);
	m_ft->waitReady();
	return !(m_ft->status() & NAND_STATUS_FAIL);
}

int NandDataLP::eraseBlock(int pageno) {
	m_ft->sendCmd(NAND_CMD_ERASE1);
	m_ft->sendAddr(pageno, m_id->getAddrByteCount());
	m_ft->sendCmd(NAND_CMD_ERASE2);
	m_ft->waitReady();
	m_ft->status();
	return !(m_ft->status() & NAND_STATUS_FAIL);
}
