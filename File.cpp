// errno
#include <errno.h>
#include <syslog.h>

// stat
#include <sys/stat.h>

// rmdir / unlink
#include <unistd.h>

#include "Binary.cpp"

#ifndef DEFINED_CLASS_FILE
#define DEFINED_CLASS_FILE

class File {

private:

public:

	static unsigned int isExist(const char *pcPath) {
		struct stat kStat;
		if(stat(pcPath, &kStat) != 0) {
			return false;
		}
		return true;
	}
	
	static unsigned int getSize(const char *pcPath) {
		struct stat kStat;
		if(stat(pcPath, &kStat) != 0) {
			return 0;
		}
		return kStat.st_size;
	}
	
	static unsigned int isFile(const char *pcPath) {
		struct stat kStat;
		if(stat(pcPath, &kStat) != 0) {
			return false;
		}
		if(S_ISREG(kStat.st_mode)) {
			return true;
		}
		return false;
	}
	
	static int deleteFile(const char *pcPath) {
		return unlink(pcPath);
	}
	
	static int readBinary(const char *pcPath, Binary &cBinary) {
		FILE *fp = NULL;
		int iReadSize	= 0;
		int iRet		= 0;
		
		// ファイルの存在を確認
		if(!isFile(pcPath)) {
			return -1;
		}
		
		// ファイルサイズを確認
		int iByteSize = getSize(pcPath);
		
		// ファイルを開く
		fp = fopen(pcPath, "r" );
		if(fp == NULL) {
			syslog(LOG_ERR, "ERROR(%d) %s", errno, strerror(errno));
			return -1;
		}
		
		// 先頭にシークする
		iRet = fseek(fp, 0, SEEK_SET);
		if(iRet == -1) {
			syslog(LOG_ERR, "ERROR(%d) %s", errno, strerror(errno));
			fclose(fp);
			return -1;
		}
		
		// ファイルを読み込む
		unsigned char *pucData = new unsigned char[iByteSize];
		iReadSize = fread(pucData, 1, iByteSize, fp); 
		
		// 保存してメモリを消去
		cBinary.setByteArray(0, pucData, iReadSize);
		delete[] pucData;
		
		fclose(fp);
		return iReadSize;
		
	}
	
	
	static int writeBinary(const char *pcPath, Binary &cBinary) {
		FILE *fp		= NULL;
		int iWriteSize	= 0;
		int iRet		= 0;
		
		// ファイルを開く
		if(isExist(pcPath)) {
			// 既に存在していれば、「ストリームはファイルの先頭」で開く
			fp = fopen(pcPath, "r+" );
		}
		else {
			// ファイルを作成して、「ストリームはファイルの先頭」で開く
			fp = fopen(pcPath, "w" );
		}
		if(fp == NULL) {
			syslog(LOG_ERR, "ERROR(%d) %s", errno, strerror(errno));
			return -1;
		}
		
		// 先頭にシークする
		iRet = fseek(fp, 0, SEEK_SET);
		if(iRet == -1) {
			syslog(LOG_ERR, "ERROR(%d) %s", errno, strerror(errno));
			fclose(fp);
			return -1;
		}
		
		// ファイルを書き込む
		iWriteSize = fwrite(cBinary.getByteArray(0), 1, cBinary.getLength(), fp);
		
		fclose(fp);
		return iWriteSize;
	}
	
};

#endif