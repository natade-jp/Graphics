#include <stdlib.h>
#include <string.h>

using namespace std;

#ifndef DEFINED_CLASS_BINARY
#define DEFINED_CLASS_BINARY

enum Endian {
	LittleBigEndian	= 0,
	BigEndian		= 1
};

class Binary {
private:
	Endian eEndian = Endian::BigEndian;
	unsigned long ulSize = 0;
	unsigned char *pucData;
	
public:
	Binary(void) {
		this->pucData = nullptr;
	}
	
	~Binary(void) {
		this->dispose();
	}
	
	void dispose(void) {
		if(this->pucData != nullptr) {
			delete[] this->pucData;
		}
		this->pucData = nullptr;
		this->ulSize = 0;
	}
	
	unsigned long getLength(void) {
		return this->ulSize;
	}
	
	void setLength(unsigned long ulSize) {
		if(this->ulSize == ulSize) {
			return;
		}
		unsigned char *pucNewData = nullptr;
		pucNewData = new unsigned char[ulSize];
		if(this->pucData == nullptr) {
			this->ulSize  = ulSize;
			this->pucData = pucNewData;
			return;
		}
		memcpy(this->pucData, pucNewData, 
			(this->ulSize < ulSize) ? this->ulSize : ulSize );
		delete[] this->pucData; 
		this->ulSize = ulSize;
		this->pucData = pucNewData;
	}
	
	
};

#endif