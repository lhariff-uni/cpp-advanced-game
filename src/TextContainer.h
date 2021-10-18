#pragma once
class TextContainer
{
public:
	TextContainer(std::string text, int size, int colour)
	{
		this->text = text;
		this->size = size;
		this->colour = colour;

		width = text.length() * size;
		height = size;
	}
	~TextContainer() {}

	std::string getText() { return text; }
	int getSize() { return size; }
	int getColour() { return colour; }
	int getWidth() { return width; }
	int getHeight() { return height; }
	void setColour(int colour) { this->colour = colour; }

	void setSize(int size) { 
		this->size = size; 
		width = text.length() * size;
		height = size;
	}
	void setText(std::string text) { 
		this->text = text; 
		width = text.length() * size;
		height = size;
	}
private:
	std::string text;
	int size;
	int colour;

	int width;
	int height;
};

