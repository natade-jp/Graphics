
using namespace std;

#ifndef DEFINED_CLASS_COLORDATA
#define DEFINED_CLASS_COLORDATA

#include "Color.cpp"
#include "Rect.cpp"

class ColorData {
private:
	Color *pcColor = nullptr;
	Rect cRect;
	
public:
	ColorData(void) {
	}
	
	~ColorData(void) {
		this->dispose();
	}
	
	void dispose(void) {
		if(pcColor != nullptr) delete[] pcColor;
		pcColor	= nullptr;
	}
	
	void setSize(int x, int y) {
		cRect.setSize(x, y);
		this->dispose();
		pcColor = new Color[x * y];
	}
	
	void setColor(Color &color, int x, int y) {
		if(pcColor == nullptr) {
			throw "exception";
		}
		unsigned long ulOffset = cRect.getOffset(x, y);
		pcColor[ulOffset].setColor(color);
	}

	void getColor(Color &color, int x, int y) {
		if(pcColor == nullptr) {
			throw "exception";
		}
		unsigned long ulOffset = cRect.getOffset(x, y);
		pcColor[ulOffset].getColor(color);
	}
};

#endif