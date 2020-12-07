#pragma once
#include<wx/wx.h>
class rkApplication :public wxApp
{
public:
	static wxString StartupPath;
	rkApplication();
	~rkApplication() {};
};


