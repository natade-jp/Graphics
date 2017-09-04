#include <Binary.h>

using namespace std;

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
	
	static int readBinary(const char *pcPath, Binary &cBinary) {
		FILE *fp = NULL;
		
		// ファイルの情報を取得する
		
		
		// ファイルを開く
		fp = fopen(pcPath, "r" );
		if(fp == NULL) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// ファイルを読み込む
		iReadSize = fread(vTarget, 1, iByteSize, fp); 
		
		fclose(fp);
		return iReadSize;
	}
	
	
	static int writeBinary(const char *pcPath, Binary &cBinary) {
		FILE *fp		= NULL;
		int iWriteSize	= 0;
		int iRet		= 0;
		
		// ファイルを開く
		if(isExist()) {
			// 既に存在していれば、「ストリームはファイルの先頭」で開く
			fp = fopen((char *)cPath, "r+" );
		}
		else {
			// ファイルを作成して、「ストリームはファイルの先頭」で開く
			fp = fopen((char *)cPath, "w" );
		}
		if(fp == NULL) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			return -1;
		}
		
		// 先頭からシークさせる。
		iRet = fseek(fp, uiOffset, SEEK_SET);
		if(iRet == -1) {
			printf("ERROR(%d) %s\n", errno, strerror(errno));
			fclose(fp);
			return -1;
		}
		
		// ファイルを書き込む
		iWriteSize = fwrite(vTarget, 1, iByteSize, fp); 
		
		fclose(fp);
		return iWriteSize;
	}
	
};

#endif