# wxFFMPeg-Converter
wxWidgete C++ ffmpeg audio converter

This class helps to convert multimedia files to desire type, it is tested for audio files but the procedure is the same for other types.

**Basics :**
* the class uses rkApplication to find current directory, so all paths are reltive based on the startup directory.
* the callback function is defined according to the rkDelegate in order to simplify using single callback event.

**class members :** class rkAudioConverter
**rkAudioConverter( wxString FFMPegPath):** Class constractor, *FFMPegPath* is relative path to *ffmpeg.exe*, you need to download this file and put it in a folder in startuppath directory and pass the path to constractor.
**onStatusChangedT onStatusChanged:** Conversion status changed during converting the file, the event can be used to show progress or to check if the process is finished or faced to an error. it doesn't need to use this function pointer directly, the delegate helps to simplify using complicate class member function pointer!
**double duration:** File length(second)
**double currenttime:** total time of file which is converted curently
**double getProgressPercentage():** get progress percent with accuracy in 0.1%

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
      *txt1 <<s<<" "<< ac->getProgressPercentage()<< " % \r\n";
    }

    myClass()
    {
    // Creating an instant and passing ffmpeg path to the class
      Converter = new rkAudioConverter("\\resources\\converter\\ffmpeg");
    // Assigning member function to the converter instance
      Converter->OnProgress(this->OnOutputLineReceived);
    }  
    void OnClick(wxCommandEvent& event)
    {
    // Starting convertion by passing relative input and output file paths
      Converter->Convert("\\resources\\converter\\k1505_.wav", "\\resources\\converter\\k1505_.mp3");
    }

}
````

	
