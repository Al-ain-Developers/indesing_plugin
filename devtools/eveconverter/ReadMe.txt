Eve Converter Tool

The tool converts ODFRez resource definitions to use EVE. 
This tool will convert panels and dialogs to use EVE, however the recommended use for EVE is only in dialogs.
Note: this tool is meant as a starting point for converting dialogs to use EVE. You will most likely need 
to do some manual work with the output FR file (removing unnecessary spacer widgets, for example).

If you run the EVE converter and the UI is blank or tiny when you test it, try running the converter again 
but with the -n flag, which will provide coordinates for leaf widgets. You can then go through manually and 
remove these coordinates one by one.

If you do a manual conversion of a dialog and find that all you can see are the OK and Cancel buttons, this
is most likely because you have forgotten to specify the EVE arrangement settings for the dialog, at the end
of its definition. If you take a look at the BasicDialog SDK sample (BscDlg.fr), right at the end of the dialog
definition 'resource BscDlgDialogBoss (kSDKDefDialogResourceID + index_enUS)' you will see the dialog has 
EVE arrangement settings: 'kEVEArrangeChildrenInRow | kEVESmallMargin,'.


Tool usage
-------------------------------------------------------------------------------
Usage: eveconverter
eveconverter -i <filename> -s <sdk dir> -p <sdk dir>/build/win/prj/coreOpen.rsp [-o <outputDirPath>] [-e] [-n] [-x]
-i <filename>             Input FR file (absolute path)
-s <sdk dir>          	  SDK directory (absolute path)
-o <outputDirPath>        Output Directory where the output files will be placed (absolute path)
-p <searchPathsFile.rsp>  (Windows only) .rsp file containing the included files search path (<sdk dir>/build/win/prj/coreOpen.rsp)
-e                        Open the errors in the external editor - Notepad on Win and TextEdit on Mac
-n                        Generate the .fr files with non - zero width and height for leaf widgets
-x                        Suppress grouping of Static text widget with related widgets

Note : -o, -n, -x and -e are optional fields


Upon successfuly completion tool generates the following folders
1. Converted files inside "eveIzed" directory.
2. Simplified content of localized files inside the "localeFiles" directory

"eveIzed" and "localeFiles" directories are either created in outputDirPath or in input file's directory, dependent on user specifies the outputDirPath or not.


Tool Binary location
-------------------------------------------------------------------------------
Windows   - <sdk dir>/devtools/eveconverter/bin/win/eveconverter.exe
Macintosh - <sdk dir>/devtools/eveconverter/bin/mac/eveconverter


General Notes
-------------------------------------------------------------------------------
Following is a list of some errors given by tool, along with way to resolve those issues

1. Filename entered not found        - It can be resolved by specifying the header search paths using option -p <filename.rsp>.
                                       Tool picks the search paths from the input .rsp file, and may resolve this issue.

2. Unable to arrange in row/column   - There may be some widgets that can't be divided into row/columns based on their frame coordinates, i.e. some frames intersect

3. Incorrect Frame syntax            - Reasons for such failure could be 
                                       Frame coordinates are specified without using "Frame" string: for example '50,50,50,50,' instead of 'Frame(50,50,50,50),'
                                       Frame coordinates are specified as some function macro

4. If the tool runs successfully and the user sees a compilation error on win- "Error R32741: # Error: Expression must be numeric", then 
   possible reason could be that the widget is like eve generic panel/ eve cluster panel widget, which doesn’t panel name string. So, just remove that and it should work fine.
 
Things eveconverter cannot handle:

1. Frame coordinates which are not specified in the format Frame(left,top,right,bottom)
2. Function macros like #define SUM(x,y) x+y
3. In the dialog/widget definition, if there are some #include statements or conditional preprocessors,other than for WINDOWS and MACINTOSH
   like #ifdef WINDOWS or #ifdef MACINTOSH, then the tool ignores them. 
   (i)  For #include statements, if the included file contains some useful information regarding the widgets arrangement, 
        then user should copy the contents of that file manually
   (ii) For conditional preprocessors, user should take care of them
