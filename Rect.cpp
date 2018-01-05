#ifndef DEFINED_CLASS_RECT
#define DEFINED_CLASS_RECT

struct Rect {
private:
	
	int iWidth;
	int iHeight;
	
public:
	
	Rect(void) {
		this->iWidth = 0;
		this->iHeight = 0;
	}
	
	Rect(Rect &rect) {
		this->setSize(rect);
	}
	
	Rect(int iWidth, int iHeight) {
		this->setSize(iWidth, iHeight);
	}
	
	~Rect(void) {
	}
	
	void setSize(Rect &rect) {
		*this = rect;
	}
	
	void setSize(int iWidth, int iHeight) {
		this->iWidth = iWidth;
		this->iHeight = iHeight;
	}
	
	void getSize(Rect &rect) {
		rect = *this;
	}
	
	void getWidth() {
		return this->iWidth;
	}
	
	void getHeight() {
		return this->iHeight;
	}
	
	bool isInRect(int x, int y) {
		if((x < 0) || (x >= iWidth) || (y < 0) || (y >= iHeight) ) {
			return false;
		}
		return true;
	}
	
	unsigned long getOffset(int x, int y) {
		if(!isInRect(x, y)) {
			throw "exception";
		}
		unsigned long ulOffset = y * iWidth + x;
		return ulOffset;
	}
	
};

#endif
