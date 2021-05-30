#pragma once

class UiWindow
{
public: 
	UiWindow(EventHandler* _eventHandler) :
		name("Window")
	{
		eventHandler = _eventHandler;
	}
protected:
	UiWindow(std::string _name, EventHandler* _eventHandler) :
		name(_name)
	{
		eventHandler = _eventHandler;
	}

	void render();

protected:
	EventHandler* eventHandler;
	std::string name;
};