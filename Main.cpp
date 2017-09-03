#include <stdio.h>

#include "ColorData.cpp"
#include "Binary.cpp"

int main(void) {
	
	Binary binary;
	
	binary.setEndian(LittleBigEndian);
	
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
	
	
	return 1;
}
