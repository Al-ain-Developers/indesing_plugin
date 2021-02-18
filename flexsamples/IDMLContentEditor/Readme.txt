IDML Content Editor sample
ReadMe File
______________________________________________________________________

The IDML Content Editor is an Adobe AIR application that can be used to 
edit text or images in an IDML file. You must build and export the 
application before running it.

***********************************************************
Building with Flash Builder 4.7 or later
***********************************************************

To import the project into Flash Builder:

  1. Start Flash Builder (or Eclipse if you have Flash Builder installed
     as a plug-in for Eclipse).
  2. Choose File > Import > Existing Projects into Workspace.
  3. Select 'Select root directory' and Browse to the <SDK>/flexsamples.
  4. Check the desired project.
  5. Click finish.

To export an installable AIR bundle from Flash Builder:

  1. Choose File > Export.
  2. Select Flash Builder > Release Build.
  3. Follow the wizard to completion to export a signed AIR package.

***********************************************************
Using the Application
***********************************************************

This application allows you edit text or images in an IDML file where the 
TextFrames or Images are marked with a script label. Script labels are a 
way to give a text frame or image a name that can be associated with it 
in IDML. The examplefiles folder contains a sample business-card template 
to demonstrate the potential usefulness of this application.
  
To create an InDesign file that can be edited with IDML Content Editor:

  1. Open a document in InDesign.
  2. Select a TextFrame or Image.
  3. Choose Window > Utilities > Script Label, to open the Script Label panel.
  4. Add Text to the panel.
  5. Export the document to IDML.

When this IDML file is opened with IDML Content Editor, it will allow users 
to edit only the content that was marked with a script label.

_____________________________________________________________________________