Adobe InDesign
Layout Helper (Sample Flex Extension)
ReadMe File
______________________________________________________________________

The Layout Helper sample extension is based on the liquid layout feature 
of InDesign CS6. It has three functions:

  * Easily view and set layout policy for pages in an InDesign document. 
  * Easily create alternative layouts for a document to target different
    devices by orientation.
  * Export a document to different file formats.

***********************************************************
Development Enviroment
***********************************************************

Required: 

  * InDesign CC (9.0 or higher) 
  * Flash Builder 4.5 
  * Extension Builder 2.1 (if using Extension Builder to build the 
    extension)
  * Creative Suite ActionScript Wrapper (CSAW) libraries and host 
    adapter library for InDesign (included if using Extension Builder).

***********************************************************
Installation
***********************************************************

1. Import the project into Extension Builder (File > Import > Existing Projects).
2. Compile and export the project to a ZXP package.
   For detailed instructions, refer to
     http://cssdk.host.adobe.com/sdk/1.5/docs/WebHelp/suitesdk.htm
3. Install the ZXP package into InDesign CS6.
   Ignore the warning message when installing.
   For detailed instructions, refer to
     http://help.adobe.com/en_US/extensionmanager/cs/using/WS4bebcd66a74275c3-43b40ca81266d538c7a-8000.html

***********************************************************
Using the Extension
***********************************************************

1. Launch InDesign CS6 and start the extension using
   Window > Extensions > LayoutHelper.
2. Create a new document and add a rectangle or text to it. 
   View the changes in the LayoutHelper. 
3. Using the extension's Layout Setting tab, set the document's 
   layout policy to guide-based and add some guides using the
   Layout Policy Options panel.
4. Set the document's layout policy to object-based, 
   then change its constraints in the Layout Policy Options panel.
5. Open the sample document great wall.indd, 
   click the Layout Creator tab, and check IpadV or other checkboxes. 
   Click Create Alternate Layout to generate the selected layouts. 
6. Click the Export tab, select a file format, and click Export Files 
   to export to a specific folder.

***********************************************************
SDK Support and Adobe Partner Programs
***********************************************************
Information on Adobe support, in general, may be found at:

  http://www.adobe.com/support/programs/

If you are a partner who extends, markets, or sells Adobe products
or solutions, you should consider membership in the Adobe Partner
Connection Solution Partner Program. The Solution Partner Program
provides development support, access to timely product information,
as well as various marketing benefits. To learn more about the
program, point your browser to:

  http://go.adobe.com/kb/cs_cpsid_50036_en-us

_____________________________________________________________________________
Copyright Adobe Systems Incorporated. All rights reserved.

Adobe and InDesign are registered trademarks or trademarks of Adobe Systems,
Incorporated in the United States and/or other countries. Microsoft and
Windows are registered trademarks or trademarks of Microsoft Corporation
in the United States and/or other countries. Apple and Mac OS are trademarks
of Apple Computer, Incorporated, registered in the United States and other
countries. IBM is a trademark of International Business Machines Corporation,
registered in the United States and other countries. All other trademarks
are the property of their respective owners.
_____________________________________________________________________________
