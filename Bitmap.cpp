#include <syslog.h>

#include "Binary.cpp"

#ifndef DEFINED_CLASS_BITMAP
#define DEFINED_CLASS_BITMAP

// ファイルヘッダ

struct BITMAPFILEHEADER {
private:
public:
	unsigned short	bfType;
	unsigned long	bfSize;
	unsigned short	bfReserved1;
	unsigned short	bfReserved2;
	unsigned long	bfOffBits;
	int				iNextHeaderSize;
	static const int iHeaderSize = 14;
	
	BITMAPFILEHEADER(void) {
		bfType = 0;
		bfSize = 0;
		bfReserved1 = 0;
		bfReserved2 = 0;
		bfOffBits = 0;
		iNextHeaderSize = 0;
	}
	
	bool readBinary(Binary &cBinary) {
		try {
			cBinary.setEndian(BinaryEndian::LittleEndian);
			bfType		= cBinary.getUint16(0);
			bfSize		= cBinary.getUint32(2);
			bfReserved1	= cBinary.getUint16(6);
			bfReserved2	= cBinary.getUint16(8);
			bfOffBits	= cBinary.getUint32(10);
			iNextHeaderSize = cBinary.getUint32(14);
		}
		catch ( ... ) {
			return false;
		}
		return true;
	}
	
};

// windows bitmap 情報ヘッダ
struct BITMAPINFOHEADER {
private:
public:
	unsigned long	biSize;
	long			biWidth;
	long			biHeight;
	unsigned short	biPlanes;
	unsigned short	biBitCount;
	unsigned long	biCompression;
	unsigned long	biSizeImage;
	long			biXPixPerMeter;
	long			biYPixPerMeter;
	unsigned long	biClrUsed;
	unsigned long	biClrImporant;
	
	static const int iHeaderSize = 40;
	
	BITMAPINFOHEADER(void) {
		biSize = 0;
		biWidth = 0;
		biHeight = 0;
		biPlanes = 0;
		biBitCount = 0;
		biCompression = 0;
		biSizeImage = 0;
		biXPixPerMeter = 0;
		biYPixPerMeter = 0;
		biClrUsed = 0;
		biClrImporant = 0;
	}
	
	bool readBinary(Binary &cBinary) {
		int iOffset = BITMAPFILEHEADER::iHeaderSize;
		try {
			cBinary.setEndian(BinaryEndian::LittleEndian);
			biSize			= cBinary.getUint32(iOffset);
			biWidth			= cBinary.getInt32(iOffset  + 4);
			biHeight		= cBinary.getInt32(iOffset  + 8);
			biPlanes		= cBinary.getUint16(iOffset + 12);
			biBitCount		= cBinary.getUint16(iOffset + 14);
			biCompression	= cBinary.getUint32(iOffset + 16);
			biSizeImage		= cBinary.getUint32(iOffset + 20);
			biXPixPerMeter	= cBinary.getInt32(iOffset + 24);
			biYPixPerMeter	= cBinary.getInt32(iOffset + 28);
			biClrUsed		= cBinary.getUint32(iOffset + 32);
			biClrImporant	= cBinary.getUint32(iOffset + 36);
		}
		catch ( ... ) {
			return false;
		}
		return true;
	}
};

// OS/2 Bitmap 情報ヘッダ*/
struct BITMAPCOREHEADER {
private:
public:
	unsigned long	bcSize;
	short			bcWidth;
	short			bcHeight;
	unsigned short	bcPlanes;
	unsigned short	bcBitCount;
	
	static const int iHeaderSize = 12;
	
	BITMAPCOREHEADER(void) {
		bcSize = 0;
		bcWidth = 0;
		bcHeight = 0;
		bcPlanes = 0;
		bcBitCount = 0;
	}
	
	bool readBinary(Binary &cBinary) {
		int iOffset = BITMAPFILEHEADER::iHeaderSize;
		try {
			cBinary.setEndian(BinaryEndian::LittleEndian);
			bcSize			= cBinary.getUint32(iOffset);
			bcWidth			= cBinary.getInt16(iOffset  + 4);
			bcHeight		= cBinary.getInt16(iOffset  + 6);
			bcPlanes		= cBinary.getUint16(iOffset + 8);
			bcBitCount		= cBinary.getUint16(iOffset + 10);
		}
		catch ( ... ) {
			return false;
		}
		return true;
	}
};

// ビットマップデータ構造体
struct BMPDATA {
private:

	bool checkBitmapSize(void) {
		if(isWinInfo) {
			iHeaderSize = kWinInfo.biSize;
			iPalletColorSize = 4;
			switch(kWinInfo.biBitCount) {
				// パレットあり
				case 1:
				case 4:
				case 8:
					iPalletLength = 1 << kWinInfo.biBitCount;
					break;
				// パレットなし
				case 24:
				case 32:
					iPalletLength = 0;
					break;
				// 対応していない色数
				default:
					return false;
					break;
			}
		}
		else if(isOS2Info) {
			iHeaderSize = kOS2Info.bcSize;
			iPalletColorSize = 3;
			switch(kOS2Info.bcBitCount) {
				// パレットあり
				case 1:
				case 4:
				case 8:
					iPalletLength = 1 << kOS2Info.bcBitCount;
					break;
				// パレットなし
				case 24:
				case 32:
					iPalletLength = 0;
					break;
				// 対応していない色数
				default:
					return false;
					break;
			}
		}
		else {
			return false;
		}
		
		// パレットのデータサイズ
		iPalletDataSize = iPalletColorSize * iPalletLength;
		
		// bfSize		（ファイルサイズ）
		// bfOffBits	（ファイルヘッダ + 情報ヘッダ + パレット情報　のサイズ）
		// (bfSize - bfOffBits) が画像データのサイズとなる
		iPixelDataSize = kFileHeader.bfSize - kFileHeader.bfOffBits;
		
		return true;
	}
	
	bool loadBitmapPallet(void) {
		return false;
	}
	
	bool loadBitmapData(void) {
		return false;
	}


public:
	// ヘッダー
	BITMAPFILEHEADER kFileHeader;
	BITMAPINFOHEADER kWinInfo;
	BITMAPCOREHEADER kOS2Info;
	// 有効無効
	bool isWinInfo = false;
	bool isOS2Info = false;
	// 画像データ
	unsigned char *pucPixels;
	// パレットデータ
	unsigned char *pucPallet;
	// データサイズ
	int iPixelDataSize;
	// 一色のパレットのサイズ
	int iPalletColorSize;
	// パレットの合計数
	int iPalletLength;
	// パレットの合計サイズ
	int iPalletDataSize;
	// 情報ヘッダのサイズ
	int iHeaderSize;
	
	BMPDATA(void) {
		this->dispose();
	}
	
	~BMPDATA(void) {
		this->dispose();
	}
	
	void dispose(void) {
		if(this->pucPixels != nullptr) {
			delete[] pucPixels;
		}
		if(this->pucPallet != nullptr) {
			delete[] pucPallet;
		}
		pucPixels = nullptr;
		pucPallet = nullptr;
		isWinInfo = false;
		isOS2Info = false;
		iPixelDataSize = 0;
		iPalletColorSize = 0;
		iPalletLength = 0;
		iPalletDataSize = 0;
		iHeaderSize = 0;
	}
	
	bool readBinary(Binary &cBinary) {
		bool bRet = true;
		
		// ファイルヘッダの構造体
		bRet = kFileHeader.readBinary(cBinary);
		if(!bRet) return false;
		
		// ファイルヘッダが"BM"であるかで、ビットマップかどうか調べる
		// JIS 0x4D='M' 0x42='B'
		bRet = kFileHeader.bfType != 0x4D42;
		if(!bRet) return false;
		
		// 40byte の情報ヘッダ（Windows bitmap）*/
		if(kFileHeader.iNextHeaderSize == BITMAPINFOHEADER::iHeaderSize) {
			bRet = kWinInfo.readBinary(cBinary);
			isWinInfo = true;
			if(!bRet) return false;
		}
		// 12byte の情報ヘッダ（OS/2 Bitmap）*/
		else if(kFileHeader.iNextHeaderSize == BITMAPCOREHEADER::iHeaderSize) {
			bRet = kOS2Info.readBinary(cBinary);
			isOS2Info = true;
			if(!bRet) return false;
		}
		else {
			return false;
		}
		
		// パレットやデータのサイズをチェックする
		bRet = checkBitmapSize();
		if(!bRet) return false;
		
		// パレット情報の取得
		if(iPalletDataSize != 0) {
			pucPallet = new unsigned char[iPalletDataSize];
			memcpy(	pucPallet,
					cBinary.getByteArray(BITMAPFILEHEADER::iHeaderSize + kFileHeader.iNextHeaderSize),
					iPalletDataSize );
		}
		
		// 画像データの取得
		pucPixels = new unsigned char[iPixelDataSize];
		memcpy(	pucPixels,
				cBinary.getByteArray(kFileHeader.bfOffBits),
				iPixelDataSize );
		
		return bRet;
	}
	
};




#endif
