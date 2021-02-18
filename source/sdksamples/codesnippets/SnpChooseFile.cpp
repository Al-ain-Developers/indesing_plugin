//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpChooseFile.cpp $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// Interface includes:

// General includes:
#include "Utils.h"
#include "ShuksanID.h" // for FileTypeInfoID's
#include "FileTypeRegistry.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

#include "SDKFileHelper.h"

/** 
	\li	How to pop a browse dialog to choose a document to be opened,	
	\li	how to pop a browse dialog to choose a file to be opened,
	\li how to pop a browse dialog to choose a file to be saved,
	\li how to filter the files these dialogs show,
	\li how to pop a browse dialog to choose a file to be placed,
	\li how to pop a browse dialog to choose a folder.

	Note this snippet does not actually open, save or place any files, 
	it just shows how to use file browse dialogs to choose files.
	Taking an action such as opening, saving or placing the chosen
	file is not within the scope of this snippet.

  	@ingroup sdk_snippet
	
	@see SDKFileHelper
	@see FileTypeRegistry
	@see ShuksanID.h
 */
class SnpChooseFile 
{
	public:
		/** Constructor.
		 */
		SnpChooseFile() {}

		/** Destructor.
		 */
		virtual			~SnpChooseFile() {}

		/** Shows how to use SDKFileDocumentChooser to allow the user 
			to choose a document to be opened. Note that the file is not
			actually opened by this method, all that happens is the user
			is allowed to choose a document using a document file browse
			dialog.
			@param chosenFile is the file selected by the user.
			@return kSuccess if file was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseDocumentToOpen(IDFile& chosenFile);
		
		/** Shows how to use SDKFileOpenChooser to allow the user 
			to choose a file to be opened. Note that the file is not
			actually opened by this method, all that happens is the user
			is allowed to choose a file using an open file browse
			dialog.
			@param chosenFile is the file selected by the user.
			@return kSuccess if file was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseFileToOpen(IDFile& chosenFile);

		/** Shows how to use SDKFileOpenChooser to allow the user 
			to choose multiple files to be opened. Note that these files are not
			actually opened by this method, all that happens is the user
			is allowed to choose files using an open file browse
			dialog.
			@param chosenFileList is the file list selected by the user.
			@return kSuccess if file was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseMultiFilesToOpen(K2Vector<IDFile>& chosenFileList);

		/** Shows how to use SDKFileSaveChooser to allow the user 
			to choose a file. Note that the file is not
			actually saved by this method, all that happens is the user
			is allowed to choose a file using a save file browse
			dialog.
			@param chosenFile is the file selected by the user.
			@return kSuccess if file was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseFileToSave(IDFile& chosenFile);

		/** Shows how to use SDKFilePlaceChooser to allow the user 
			to choose a file. Note that the file is not
			actually placed by this method, all that happens is the user
			is allowed to choose a file using a place file browse
			dialog.
			@param chosenFile is the file selected by the user.
			@return kSuccess if file was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseFileToPlace(IDFile& chosenFile);

		/** Shows how to use SDKFolderChooser to allow the user 
			to choose a folder.
			@param chosenFolder is the folder chosen by the user.
			@return kSuccess if folder was chosen, kCancel otherwise.
		 */
		ErrorCode ChooseFolder(IDFile& chosenFolder);

	
};

/*
*/
ErrorCode SnpChooseFile::ChooseDocumentToOpen(IDFile& chosenFile)
{
	ErrorCode result = kCancel;
	do {
		// Browse for a document.
		SDKFileDocumentChooser fileChooser;
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}
		SNIPLOG("OpenFlags=%d", fileChooser.GetOpenFlags());		
		// Return the chosen file to the caller.
		chosenFile = fileChooser.GetIDFile();
		result = kSuccess;
	} while(false);
	return result;
}


/*
*/
ErrorCode SnpChooseFile::ChooseFileToOpen(IDFile& chosenFile)
{
	ErrorCode result = kCancel;
	do {
		// Ask what kind of files the user should be shown.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back("Publication files");
		choices.push_back("JPEG files");
		choices.push_back("PDF files");
		choices.push_back("Text files");
		choices.push_back("XML files");
		enum {kPub, kJPEG, kPDF, kText, kXML};
		int32 choice  = parameterUtils->GetChoice("What kind of files do you want to choose from?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Set up the file chooser to show files of the requested kind.
		SDKFileOpenChooser fileChooser;
		PMString title;
		switch (choice) 
		{
		default:			
		case kPub:
			{
				// The default behaviour is to show publication files.
				// Under InDesign this will be InDesign documents.
				// Under InCopy this will be InCopy documents.
				break;
			}
		case kJPEG:
			{
				title = choices[choice];
				fileChooser.AddFilter(kJPEGFileTypeInfoID, "JPEG files(jpg)");
				fileChooser.AddAllFiles();
				break;
			}
		case kPDF:
			{
				title = choices[choice];
				fileChooser.AddFilter(kPDFFileTypeInfoID, "PDF(pdf)");
				fileChooser.AddAllFiles();
				break;
			}
		case kText:
			{
				title = choices[choice];
				fileChooser.AddFilter('TEXT', "txt", "TEXT files(txt)");
				fileChooser.AddFilter(kTEXTFileTypeInfoID, "TEXT files(text)");
				fileChooser.AddAllFiles();
				break;
			}
		case kXML:
			{
				title = choices[choice];
				fileChooser.AddFilter(kXMLFileTypeInfoID, "TEXT XML files(xml)");
				fileChooser.AddAllFiles();
				break;
			}
		}

		// Set the title if necessary then open the file browse dialog.
		if (!title.empty()) {
			fileChooser.SetTitle(title);
		}
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}

		// Return the chosen file to the caller.
		chosenFile = fileChooser.GetIDFile();
		result = kSuccess;
	} while(false);
	return result;
}

ErrorCode SnpChooseFile::ChooseMultiFilesToOpen(K2Vector<IDFile>& chosenFileList)
{
	ErrorCode result = kCancel;
	do {
		// Ask what kind of files the user should be shown.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back("Publication files");
		choices.push_back("JPEG files");
		choices.push_back("PDF files");
		choices.push_back("Text files");
		choices.push_back("XML files");
		enum {kPub, kJPEG, kPDF, kText, kXML};
		int32 choice  = parameterUtils->GetChoice("What kind of files do you want to choose from?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Set up the file chooser to show files of the requested kind.
		SDKFileOpenMultipleFileChooser multiFileChooser;
		PMString title;
		switch (choice) 
		{
		default:			
		case kPub:
			{
				// The default behaviour is to show publication files.
				// Under InDesign this will be InDesign documents.
				// Under InCopy this will be InCopy documents.
				break;
			}
		case kJPEG:
			{
				title = choices[choice];
				multiFileChooser.AddFilter(kJPEGFileTypeInfoID, "JPEG files(jpg)");
				multiFileChooser.AddAllFiles();
				break;
			}
		case kPDF:
			{
				title = choices[choice];
				multiFileChooser.AddFilter(kPDFFileTypeInfoID, "PDF(pdf)");
				multiFileChooser.AddAllFiles();
				break;
			}
		case kText:
			{
				title = choices[choice];
				multiFileChooser.AddFilter('TEXT', "txt", "TEXT files(txt)");
				multiFileChooser.AddFilter(kTEXTFileTypeInfoID, "TEXT files(text)");
				multiFileChooser.AddAllFiles();
				break;
			}
		case kXML:
			{
				title = choices[choice];
				multiFileChooser.AddFilter(kXMLFileTypeInfoID, "TEXT XML files(xml)");
				multiFileChooser.AddAllFiles();
				break;
			}
		}

		// Set the title if necessary then open the file browse dialog.
		if (!title.empty()) {
			multiFileChooser.SetTitle(title);
		}
		multiFileChooser.ShowDialog();
		if (!multiFileChooser.IsChosen()) {
			break;
		}

		int32 idFileCount = multiFileChooser.GetFileCount();

		for(int32 i = 0; i < idFileCount; ++i)
		{
			chosenFileList.push_back(*(multiFileChooser.GetNthFile(i)));
		}

		result = kSuccess;
	} while(false);
	return result;
}
/*
*/
ErrorCode SnpChooseFile::ChooseFileToSave(IDFile& chosenFile)
{
	ErrorCode result = kCancel;
	do {
		// Ask what kind of files the user should be shown.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back("Save Publication");
		choices.push_back("Save InDesign document/template");
		choices.push_back("Save image");
		choices.push_back("Save text");
		choices.push_back("Save Xmedia");
		enum {kPub, kInDesign, kImage,kText, kXMedia};
		int32 choice  = parameterUtils->GetChoice("What kind of file do you want to choose to save?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Set up the file chooser to show files of the requested kind.
		SDKFileSaveChooser fileChooser;
		PMString title;
		SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);
		switch (choice) 
		{
		default:
		case kPub:
			{
				// The default behaviour is to show publication files.
				// Under InDesign this will be an InDesign document.
				// Under InCopy this will be an InCopy document.
				break;
			}
		case kInDesign:
			{
				title = choices[choice];
				fileChooser.AddFilter(kInDesignFileTypeInfoID, "InDesign document(indd)");
				fileChooser.AddFilter(kIDTemplateFileTypeInfoID, "InDesign template(indt)");
				break;
			}
		case kImage:
			{
				title = choices[choice];
				fileChooser.AddFilter(kJPEGFileTypeInfoID, "JPEG file(jpg)");
				fileChooser.AddFilter(kPICTFileTypeInfoID, "PICT file(pic)");
				fileChooser.AddFilter(kTIFFFileTypeInfoID, "TIFF file(tif)");
				fileChooser.AddFilter(kGIFFileTypeInfoID, "GIFf file(gif)");
				fileChooser.AddFilter(kPDFFileTypeInfoID, "PDF file(pdf)");
				fileChooser.AddFilter(kEPSFFileTypeInfoID, "EPSF file(eps)");
				fileChooser.AddFilter(kSVGFileTypeInfoID, "SVG file(svg)");				
				break;
			}
		case kText:
			{
				title = choices[choice];
				fileChooser.AddFilter(kTEXTFileTypeInfoID, "TEXT file(text)");
				fileChooser.AddFilter(macFileCreator, 'TEXT', "txt", "TEXT file(txt)");
				fileChooser.AddFilter(kRTFFileTypeInfoID, "TEXT file(rtf)");
				fileChooser.AddFilter(kCSVFileTypeInfoID, "TEXT comma separated file(csv)");
				break;
			}
		case kXMedia:
			{
				title = choices[choice];
				fileChooser.AddFilter(kXMLFileTypeInfoID, "TEXT XML file(xml)");
				fileChooser.AddFilter(kHTMLFileTypeInfoID, "TEXT HTML files(htm)");
				fileChooser.AddFilter(macFileCreator, 'TEXT', "html", "TEXT HTML files(html)");
				break;
			}
		}

		// Set the title if necessary then open the file browse dialog.
		if (!title.empty()) {
			fileChooser.SetTitle(title);
		}
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}

		// Return the chosen file to the caller.
		chosenFile = fileChooser.GetIDFile();
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpChooseFile::ChooseFileToPlace(IDFile& chosenFile)
{
	ErrorCode result = kCancel;
	do {
		SDKFilePlaceChooser fileChooser;
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}
		chosenFile = fileChooser.GetIDFile();
		result = kSuccess;
	} while(false);
	return result;
}

/*
*/
ErrorCode SnpChooseFile::ChooseFolder(IDFile& chosenFolder)
{
	ErrorCode result = kCancel;
	do {
		SDKFolderChooser folderChooser;
		PMString title("Choose a Folder");
		folderChooser.SetTitle(title);
		folderChooser.ShowDialog();
		if (!folderChooser.IsChosen()) {
			break;
		}
		chosenFolder = folderChooser.GetIDFile();
		result = kSuccess;
	} while(false);
	return result;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

/** Makes the snippet SnpChooseFile available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerChooseFile : public SnpRunnable
{
	

	public:
		// SnippetRunner framework hooks.

		/** Constructor.
		 */
		_SnpRunnerChooseFile();

		/** Destructor.
		 */
		virtual			~_SnpRunnerChooseFile();

		/** Return kTrue if the snippet can run.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kTrue if snippet can run, kFalse otherwise
		 */
		bool16			CanRun(ISnpRunnableContext* runnableContext);

		/** Run the snippet.
			@param runnableContext see ISnpRunnableContext for documentation.
			@return kSuccess on success, other ErrorCode otherwise.
		*/
		ErrorCode		Run(ISnpRunnableContext* runnableContext);
		
		/** 
			get the snippet context
			@return eSnpRunContextType for this snippet
		*/
		virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};

/* Constructor.
*/
_SnpRunnerChooseFile::_SnpRunnerChooseFile() : SnpRunnable("ChooseFile")
{
	this->SetDescription("Browses for documents or files and logs the chosen file.");
	this->SetPreconditions("none");
	this->SetCategories("sdk_snippet");
}

/* Destructor.
*/
_SnpRunnerChooseFile::~_SnpRunnerChooseFile()
{
}

/* No preconditions.
*/
bool16	_SnpRunnerChooseFile::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/*
*/
ErrorCode _SnpRunnerChooseFile::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpChooseFile instance;

		// Ask what type of file browse is wanted.
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back("Document open");
		choices.push_back("File open");
		choices.push_back("File multi-open");
		choices.push_back("File save");
		choices.push_back("File place");
		choices.push_back("Folder");
		enum {kOpenDocument, kOpenFile, kOpenMultiFiles, kSaveFile, kPlaceFile, kFolder};
		int32 choice  = parameterUtils->GetChoice("What type of file browse dialog do you want?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}

		// Perform the requested type of file browse.
		IDFile file;
		bool16 isMulltiFile = kFalse;
		K2Vector<IDFile> fileList;

		switch (choice) 
		{
		default:
		case kOpenDocument:
			{
				status = instance.ChooseDocumentToOpen(file);
				break;
			}
		case kOpenFile:
			{
				status = instance.ChooseFileToOpen(file);
				break;
			}
		case kOpenMultiFiles:
			{
				status = instance.ChooseMultiFilesToOpen(fileList);	
				isMulltiFile = kTrue;
				break;
			}
		case kSaveFile:
			{
				status = instance.ChooseFileToSave(file);
				break;
			}
		case kPlaceFile:
			{
				status = instance.ChooseFileToPlace(file);
				break;
			}
		case kFolder:
			{
				status = instance.ChooseFolder(file);
				break;
			}
		}

		if(status != kSuccess)
		{
			break;
		}

		if (isMulltiFile == kFalse) {
			SDKFileHelper fileHelper(file);
			SNIPLOG("Chosen file or folder was %s", fileHelper.GetPath().GetPlatformString().c_str());
		}
		else {	
			K2Vector<IDFile>::iterator it;
			K2Vector<IDFile>::iterator itEnd = fileList.end();
			for(it = fileList.begin(); it != itEnd; ++it)
			{
				SDKFileHelper fileHelper(*it);
				SNIPLOG("Chosen file or folder was %s", fileHelper.GetPath().GetPlatformString().c_str());
			}
		}
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerChooseFile instance_SnpRunnerChooseFile;
DEFINE_SNIPPET(_SnpRunnerChooseFile) 
// End, SnpChooseFile.cpp

