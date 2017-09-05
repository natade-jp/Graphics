#include <stdio.h>

#include <stdlib.h>
#include <string.h>

using namespace std;

#ifndef DEFINED_CLASS_BINARY
#define DEFINED_CLASS_BINARY

enum BinaryEndian {
	LittleEndian	= 0,
	BigEndian		= 1
};

class Binary {
private:
	BinaryEndian eEndian = BinaryEndian::BigEndian;
	int iSize = 0;
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
		this->iSize = 0;
	}
	
	void setEndian(BinaryEndian eEndian) {
		this->eEndian = eEndian;
	}
	
	BinaryEndian getEndian() {
		return this->eEndian;
	}
	
	int getLength(void) {
		return this->iSize;
	}
	
	void setLength(int iSize) {
		if(iSize < 0) {
			throw "exception";
		}
		if(this->iSize == iSize) {
			return;
		}
		unsigned char *pucNewData = nullptr;
		pucNewData = new unsigned char[iSize];
		if(this->pucData == nullptr) {
			this->iSize  = iSize;
			this->pucData = pucNewData;
			return;
		}
		memcpy(pucNewData, this->pucData,
			(this->iSize < iSize) ? this->iSize : iSize );
		delete[] this->pucData; 
		this->iSize = iSize;
		this->pucData = pucNewData;
	}
	
	void setByte(int iOffset, unsigned char ucValue) {
		if(iOffset >= this->iSize) {
			this->setLength(iOffset + 1);
		}
		this->pucData[iOffset] = ucValue;
	}
	
	unsigned char getByte(int iOffset) {
		if((iSize < 0) || (iSize <= iOffset)) {
			throw "exception";
		}
		return this->pucData[iOffset];
	}
	
	void setByteArray(int iOffset, unsigned char *ucArray, int iArraySize) {
		if((iOffset + iArraySize) >= this->iSize) {
			this->setLength(iOffset + iArraySize);
		}
		memcpy(&(this->pucData[iOffset]), ucArray, iArraySize);
	}
	
	unsigned char *getByteArray(int iOffset) {
		if(iOffset >= this->iSize) {
			throw "exception";
		}
		return &(this->pucData[iOffset]);
	}
	
	void setUint8(int iOffset, unsigned char ucValue) {
		this->setByte(iOffset, ucValue);
	}
	
	void setInt8(int iOffset, signed char scValue) {
		this->setUint8(iOffset, (unsigned char) scValue);
	}
	
	unsigned char getUint8(int iOffset) {
		return this->getByte(iOffset);
	}
	
	signed char getInt8(int iOffset) {
		return (signed char) this->getUint8(iOffset);
	}
	
	void setUint16(int iOffset, unsigned short usValue) {
		if(this->eEndian == BinaryEndian::BigEndian) {
			this->setByte(iOffset,		(usValue >> 8)	& 0xFF);
			this->setByte(iOffset + 1,	usValue			& 0xFF);
		}
		else {
			this->setByte(iOffset,		usValue			& 0xFF);
			this->setByte(iOffset + 1,	(usValue >> 8)	& 0xFF);
		}
	}
	
	void setInt16(int iOffset, signed short ssValue) {
		this->setUint16(iOffset, (unsigned short) ssValue);
	}
	
	unsigned short getUint16(int iOffset) {
		unsigned short usValue = 0;
		if(this->eEndian == BinaryEndian::BigEndian) {
			usValue = (this->getByte(iOffset) << 8) | (this->getByte(iOffset + 1));
		}
		else {
			usValue = (this->getByte(iOffset)) | (this->getByte(iOffset + 1) << 8);
		}
		return usValue;
	}
	
	signed short getInt16(int iOffset) {
		return (signed short) this->getUint16(iOffset);
	}
	
	void setUint32(int iOffset, unsigned long ulValue) {
		if(this->eEndian == BinaryEndian::BigEndian) {
			this->setByte(iOffset,		(ulValue >> 24)	& 0xFF);
			this->setByte(iOffset + 1,	(ulValue >> 16)	& 0xFF);
			this->setByte(iOffset + 2,	(ulValue >> 8)	& 0xFF);
			this->setByte(iOffset + 3,	ulValue			& 0xFF);
		}
		else {
			this->setByte(iOffset,		ulValue			& 0xFF);
			this->setByte(iOffset + 1,	(ulValue >> 8)	& 0xFF);
			this->setByte(iOffset + 2,	(ulValue >> 16)	& 0xFF);
			this->setByte(iOffset + 3,	(ulValue >> 24)	& 0xFF);
		}
	}
	
	void setInt32(int iOffset, signed long slValue) {
		this->setUint32(iOffset, (unsigned long) slValue);
	}
	
	unsigned long getUint32(int iOffset) {
		unsigned long ulValue = 0;
		if(this->eEndian == BinaryEndian::BigEndian) {
			ulValue =	(this->getByte(iOffset) << 24) |
						(this->getByte(iOffset + 1) << 16) |
						(this->getByte(iOffset + 2) << 8) |
						(this->getByte(iOffset + 3));
		}
		else {
			ulValue =	(this->getByte(iOffset)) |
						(this->getByte(iOffset + 1) << 8) |
						(this->getByte(iOffset + 2) << 16) |
						(this->getByte(iOffset + 3) << 24);
		}
		return ulValue;
	}
	
	signed long getInt32(int iOffset) {
		return (signed long) this->getUint32(iOffset);
	}
	
};

#endif