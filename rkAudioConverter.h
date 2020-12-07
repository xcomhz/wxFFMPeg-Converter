#pragma once
#include "wx\wx.h"
#include <wx\process.h>
#include <wx/utils.h> 
#include <wx/txtstrm.h>
#include "rkApplication.h"
#include <wx/tokenzr.h>
#include"rkDelegate.h"


class rkAudioConverter
{
DelegateFunction(void(rkAudioConverter* ac, wxString s)) onStatusChangedT;
#define OnProgress(Function) CreateConnector(onStatusChanged,(rkAudioConverter* ac, wxString s),(ac,s),Function)

public:
	onStatusChangedT onStatusChanged = 0;
	bool Convert(wxString InputFile, wxString OutputFile)
	{
		if (Busy)return false;
		if (p)
		{
			p->Unbind(wxEVT_END_PROCESS, &rkAudioConverter::OnFinished, this);
			delete p;
		}
		p = new wxProcess();
		p->Redirect();
		bool isred = p->IsRedirected();
		p->Bind(wxEVT_END_PROCESS, &rkAudioConverter::OnFinished, this);
		wxString fin = rkApplication::StartupPath + InputFile;
		wxString fout = rkApplication::StartupPath + OutputFile;
		wxString cmd = this->FFMPegPath + " -y -i " + fin + " -acodec libmp3lame " + fout;
		long pid = wxExecute(cmd, wxEXEC_ASYNC , p);
		if (pid)
			p->SetPid(pid);
		else
			return false;
		Busy = true;
		return true;
	}
	//T* Target;
	//void (T::* OnConverted)(rkAudioConverter* e) = 0;
	//void (T::* OnOutputLineReceived)(rkAudioConverter* e,wxString &s) = 0;
	rkAudioConverter(/*T* Target,*/ wxString FFMPegPath)
	{
		//this->Target = Target;
     	this->FFMPegPath = rkApplication::StartupPath + FFMPegPath;

		timer = new wxTimer();
		timer->Bind(wxEVT_TIMER, &rkAudioConverter::OnTimer, this);
		timer->Start(100);

	}
	~rkAudioConverter() {
		if (p)
		{
		//	p->Unbind(wxEVT_END_PROCESS, &OnFinished, this);
			delete p;
		}
	}
	void OnFinished(wxProcessEvent& event)
	{
//		if (OnConverted != 0)
			//Target->OnConverted(this);
		Busy = false;
	}
	double duration = 0;
	double currenttime = 0;
	bool Busy = false;
	double getProgressPercentage()
	{
		double Percent = duration == 0 ? 0 : ((int)(currenttime * 1000.0 / duration)) / 10.0;
		return Percent;
	}
private:
	wxTimer* timer;
	wxString FFMPegPath;
	wxProcess *p=0;
	wxString outStr="";
	wxString DurationText;
	wxString CurrentTimeText;
	bool TimerIsBusy = false;
	void OnTimer(wxTimerEvent& event)
	{
	

		if (p && !TimerIsBusy)
		{
			TimerIsBusy = true;
			bool a = p->IsErrorAvailable();
			bool b = p->IsInputAvailable();
			wxInputStream* is = p->GetErrorStream();
			while (is->CanRead())
			{
				char c= (char)is->GetC();
				if (c == '\n' || c=='\r')
				{
					outStr.Trim();
					if (outStr.Contains("size=") && outStr.Contains("time="))
					{
						wxStringTokenizer tokenizer(outStr, "=: ");
						wxString token1;
						while (tokenizer.HasMoreTokens())
						{
							token1= tokenizer.GetNextToken();
							if (token1 != "time" && token1 != "size" && token1 != "" && !token1.Contains("B"))break;;

						}
						if (tokenizer.HasMoreTokens())
						{
							wxString token2 = tokenizer.GetNextToken();
							wxString token3 = tokenizer.GetNextToken();
							wxString token4 = tokenizer.GetNextToken();
							wxString token5 = tokenizer.GetNextToken();
							if (token1 != "" && token2 != "" && token3 != "")
							{
								double t;
								if (token1.ToDouble(&t))
								{
									currenttime = t * 3600;
									if (token2.ToDouble(&t))
									{
										currenttime += t * 60;
										if (token3.ToDouble(&t))
										{
											currenttime += t;
											CurrentTimeText = "Current time: " + token1 + ":" + token2 + ":" + token3;
											if (duration != 0)
											{
												CurrentTimeText += " " + DurationText;
											}
											outStr = CurrentTimeText;

										}
									}
								}
							}


						}
					}
					else if (outStr.Contains("Duration:"))
					{
						wxStringTokenizer tokenizer(outStr, ":, ");
						wxString token1;
						while (tokenizer.HasMoreTokens())
						{
							token1 = tokenizer.GetNextToken();
							if (token1 != "Duration" && token1!="")break;;

						}
						if (tokenizer.HasMoreTokens())
						{
							wxString token2 = tokenizer.GetNextToken();
							wxString token3 = tokenizer.GetNextToken();
							wxString token4 = tokenizer.GetNextToken();
							wxString token5 = tokenizer.GetNextToken();
							if (token1 != "" && token2 != "" && token3 != "")
							{
								double t;
								if (token1.ToDouble(&t))
								{
									duration = t * 3600;
									if (token2.ToDouble(&t))
									{
										duration += t * 60;
										if (token3.ToDouble(&t))
										{
											duration += t;
											outStr = DurationText = "Duration: " + token1 + ":" + token2 + ":" + token3;
										}
									}
								}
							}

						}
					}
					else if (outStr.Contains("video:") && outStr.Contains("audio:"))
						outStr = "Finished";
					else if (outStr.Contains("No such file or directory"))
					{
						outStr = "File error";
						p->Kill(p->GetPid());
					}
					else 
						outStr = "";
					
						if (onStatusChanged != 0 && outStr != "")
							onStatusChanged(this, outStr);
				//	if (OnOutputLineReceived != 0 && outStr != "")
					//	Target->OnOutputLineReceived(this, outStr);
					outStr = "";
				}
				else 
					outStr += c;
			}
			TimerIsBusy = false;
		}

	}


};



