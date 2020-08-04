#pragma once

class Input
{
private:
	struct Mouse
	{
		int x, y;
		bool left;
	};

public:
	// functions for controling key states
	void setKeyDown(int key);
	void setKeyUp(int key);
	void setMouseDown(int button);
	void setMouseUp(int button);
	bool isKeyDown(int key);
	bool isMouseDown(int button);


	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();

private:
	bool keys[256]{ false };
	bool buttons[2]{ false };
	Mouse mouse;
};