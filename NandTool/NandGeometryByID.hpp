#ifndef NANDGEOMETRYBYID_HPP
#define NANDGEOMETRYBYID_HPP

#include <string>
using namespace std;
#include "FtdiNand.hpp"
#include "NandGeometry.hpp"

class NandGeometryByID: public NandGeometry {
public:
	NandGeometryByID(FtdiNand *fn, unsigned char *idbytes);
	virtual string getDesc();
	virtual long getPagesCount();
	virtual int getSizeMB();
	virtual int getPageSize();
	virtual int getOobSize();
	virtual bool isLargePage();
	virtual int getAddrByteCount();
private:
	typedef struct {
		const char *name;
		unsigned char id;
		int pagesize;
		int chipsizeMB;
		int erasesize;
		int options;
		int addrcycles;
	} DevCodes;

	static const DevCodes m_devCodes[];
	string m_nandDesc;
	int m_nandPageSz;
	int m_nandbw;
	int m_nandOobSz;
	int m_nandEraseSz;
	int m_nandChipSzMB;
	int m_nandaddrcyc;
	bool m_nandIsLP;
};

#endif
