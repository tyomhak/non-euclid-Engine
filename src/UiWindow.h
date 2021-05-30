#pragma once

class UiWindow
{
public: 
	UiWindow() : name("Window")
	{

	}
protected:
	UiWindow(std::string _name) 
	{
		name = _name;
	}

	static void render();

protected:
	std::string name;
};