#ifndef DEFINED_CLASS_COLOR
#define DEFINED_CLASS_COLOR

struct Color {
private:
	
public:
	unsigned char r;
	unsigned char g;
	unsigned char b;
	
	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	}
	
	Color(unsigned char r, unsigned char g, unsigned char b) {
		setColor(r, g, b);
	}
	
	Color(Color &color) {
		setColor(color);
	}
	
	~Color() {
	}
	
	void setColor(unsigned char r, unsigned char g, unsigned char b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
	void setColor(Color &color) {
		this->r = color.r;
		this->g = color.g;
		this->b = color.b;
	}
	
	void getColor(Color &color) {
		color = *this;
	}
	
};

#endif
