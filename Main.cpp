#include <stdio.h>

#include "ColorData.cpp"
#include "File.cpp"
#include "Binary.cpp"
#include "Bitmap.cpp"

int main(void) {
	
	const char *pucFileName = "test.bin";
	
	{
		printf("* test [binary]\n");
		
		Binary binary;
		
		binary.setEndian(LittleEndian);
		
		binary.setUint32(0, 12345678);
		printf("%ld\n", binary.getUint32(0));
		binary.setLength(0);
		
		binary.setInt32(0, -12345678);
		printf("%ld\n", binary.getInt32(0));
		binary.setLength(0);
		
		binary.setUint16(0, 12345);
		printf("%d\n", binary.getUint16(0));
		binary.setLength(0);
		
		binary.setInt16(0, -12345);
		printf("%d\n", binary.getInt16(0));
		binary.setLength(0);
	}
	
	{
		printf("* test [file write]\n");
		
		Binary binary;
		binary.setUint32(0, 0x11223344);
		binary.setUint32(4, 0x55667788);
		
		File::writeBinary(pucFileName, binary);
	}
	
	{
		printf("* test [file read]\n");
		
		Binary binary;
		File::readBinary(pucFileName, binary);
		
		printf("%d\n", binary.getLength());
		printf("%x%x%x%x\n",
			binary.getUint8(0),
			binary.getUint8(1),
			binary.getUint8(2),
			binary.getUint8(3)
		);
		
		File::deleteFile(pucFileName);
	}
	
	return 1;
}
