#include "rkApplication.h"
#include <wx\stdpaths.h>
#include <wx\dir.h>
#include <wx\filename.h>
#include "wx\wx.h"


wxString rkApplication::StartupPath;
rkApplication::rkApplication()
{
	wxString exePath = wxStandardPaths::Get().GetExecutablePath();
	wxFileName fn;
	fn.Assign(exePath);
	StartupPath = fn.GetPath();
}


