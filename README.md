# wxWidgets wxFFMPeg-Converter
wxWidgete C++ ffmpeg audio converter

This class helps to convert multimedia files to desired types, it is tested for audio files by wxWidgets but the procedure is the same for other types and platforms. 

**Basics :**
* the class uses rkApplication to find current directory, so all paths are relative based on the startup directory.
* the callback function is defined according to the rkDelegate in order to simplify using single callback event.

**How to install :** In order to use this class, you could add the header and cpp files to your wxWidgets project.

**class members :** class rkAudioConverter
* **rkAudioConverter( wxString FFMPegPath):** Class constructor, *FFMPegPath* is relative path to *ffmpeg.exe*, you need to download this file and put it in a folder in startuppath directory and pass the path to constructor.
* **onStatusChangedT onStatusChanged:** Conversion status changed during converting the file, the event can be used to show progress or to check if the process is finished or faced an error. it doesn't need to use this function pointer directly, the delegate helps to simplify using complicated class member function pointers!

*OnProgress* is the alternate to this pointer, it is simple to use it(see the example), otherwise *lambda* function is needed to call class member function.

* **double duration:** File length(second)
* **double currenttime:** total time of file which is converted currently
* **double getProgressPercentage():** get progress percent with accuracy in 0.1%

**Example code:**
````
Class myClass
{
public:

    // Audio converter pointer variable 
  	rkAudioConverter *Converter;
    
    // On Receive info event function
    void OnOutputLineReceived(rkAudioConverter* ac,wxString &s)
    {
      *myTextControl <<s<<" "<< ac->getProgressPercentage()<< " % \r\n";
    }

    myClass()
    {
    // Creating an instant and passing ffmpeg path to the class
      Converter = new rkAudioConverter("\\resources\\converter\\ffmpeg");
    // Assigning member function to the converter instance
      Converter->OnProgress(this->OnOutputLineReceived);
    }  
    void myButtonOnClick(wxCommandEvent& event)
    {
    // Starting conversion by passing relative input and output file paths
      Converter->Convert("\\resources\\converter\\k1505_.wav", "\\resources\\converter\\k1505_.mp3");
    }

}
````
**Sample output** Each line is generated by triggering OnProgress event
	
````
Start converting ...
Duration: 02:17:52.56 0.00 % 
Current time: 00:04:32.09 Duration: 02:17:52.56 3.20 % 
Current time: 00:09:01.73 Duration: 02:17:52.56 6.50 % 
Current time: 00:13:35.47 Duration: 02:17:52.56 9.80 % 
Current time: 00:18:17.28 Duration: 02:17:52.56 13.20 % 
Current time: 00:22:59.02 Duration: 02:17:52.56 16.60 % 
Current time: 00:27:45.86 Duration: 02:17:52.56 20.10 % 
Current time: 00:32:26.66 Duration: 02:17:52.56 23.50 % 
Current time: 00:37:09.48 Duration: 02:17:52.56 26.90 % 
Current time: 00:41:50.28 Duration: 02:17:52.56 30.30 % 
Current time: 00:46:00.70 Duration: 02:17:52.56 33.30 % 
Current time: 00:50:10.18 Duration: 02:17:52.56 36.30 % 
Current time: 00:54:29.74 Duration: 02:17:52.56 39.50 % 
Current time: 00:58:43.25 Duration: 02:17:52.56 42.50 % 
Current time: 01:03:15.98 Duration: 02:17:52.56 45.80 % 
Current time: 01:07:11.28 Duration: 02:17:52.56 48.70 % 
Current time: 01:11:30.91 Duration: 02:17:52.56 51.80 % 
Current time: 01:15:47.45 Duration: 02:17:52.56 54.90 % 
Current time: 01:20:01.97 Duration: 02:17:52.56 58.00 % 
Current time: 01:24:44.71 Duration: 02:17:52.56 61.40 % 
Current time: 01:28:56.21 Duration: 02:17:52.56 64.50 % 
Current time: 01:33:42.05 Duration: 02:17:52.56 67.90 % 
Current time: 01:38:26.88 Duration: 02:17:52.56 71.40 % 
Current time: 01:43:10.70 Duration: 02:17:52.56 74.80 % 
Current time: 01:47:58.56 Duration: 02:17:52.56 78.30 % 
Current time: 01:52:43.39 Duration: 02:17:52.56 81.70 % 
Current time: 01:57:14.04 Duration: 02:17:52.56 85.00 % 
Current time: 02:01:48.79 Duration: 02:17:52.56 88.30 % 
Current time: 02:06:30.53 Duration: 02:17:52.56 91.70 % 
Current time: 02:11:12.34 Duration: 02:17:52.56 95.10 % 
Current time: 02:15:57.17 Duration: 02:17:52.56 98.60 % 
Current time: 02:17:52.58 Duration: 02:17:52.56 100.00 % 
Finished 100.00 % 
````

* rkDelegate and lambda function :
* rkApplication :

# XCOMHZ / rkLib
