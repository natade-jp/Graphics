#include <memory>
using namespace std;

#ifndef DEFINED_CLASS_COLORDATA
#define DEFINED_CLASS_COLORDATA

#include "Color.cpp"
#include "Rect.cpp"

class ColorData {
private:
	Color *pcColor = NULL;
	Rect cRect;
	
public:
	ColorData() {
	}
	
	~ColorData() {
		this->dispose();
	}
	
	void dispose() {
		if(pcColor != NULL) delete pcColor;
		pcColor	= NULL;
	}
	
	void setSize(int x, int y) {
		cRect.setSize(x, y);
		this->dispose();
		pcColor = new Color[x * y];
	}
	
	void setColor(Color &color, int x, int y) {
		if(pcColor == NULL) {
			throw "exception";
		}
		unsigned long ulOffset = cRect.getOffset(x, y);
		pcColor[ulOffset].setColor(color);
	}

	void getColor(Color &color, int x, int y) {
		if(pcColor == NULL) {
			throw "exception";
		}
		unsigned long ulOffset = cRect.getOffset(x, y);
		pcColor[ulOffset].getColor(color);
	}
};

#endif