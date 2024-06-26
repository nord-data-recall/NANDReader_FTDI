#ifndef NANDCHIP_HPP
#define NANDCHIP_HPP

#include "FtdiNand.hpp"
#include "NandGeometry.hpp"
#include "NandData.hpp"
#include "NandOnfi.hpp"

using namespace std;

class NandChip {
public:
	NandChip(FtdiNand *fn, char* geometry);
	~NandChip();
	enum AccessType {
		accessNone=0,
		accessMain=1,
		accessOob=2,
		accessBoth=3,
		accessOnfi=8
	};
	void showInfo();
	void showInfoLong();
	int readPage(int page, char *buff, int count, AccessType access);
	int writePage(int page, char *buff, int count, AccessType access);
	NandGeometry *getIdPtr();
	bool hasOnfi();
private:
	void showCommon();
	FtdiNand *m_fn;
	NandOnfi *m_onfi;
	NandGeometry *m_id;
	NandData *m_data;
};

#endif