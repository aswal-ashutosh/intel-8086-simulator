#pragma once
#include"MainFrame.h"
#include<wx\wx.h>

class Simulator: public wxApp
{
	MainFrame* mainWindow = nullptr;
public:
	Simulator();
	~Simulator();
	virtual bool OnInit();
};

