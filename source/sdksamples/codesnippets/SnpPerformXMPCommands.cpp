//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformXMPCommands.cpp $
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
#include "IActiveContext.h"
#include "IAppendMetaDataCmdData.h"
#include "ICommand.h"
#include "IDocument.h"
#include "IMetaDataAccess.h"
#include "IPMStream.h"
#include "IReplaceMetaDataCmdData.h"
#include "IStripForeignMetaDataCmdData.h"

// General includes:
#include "CmdUtils.h"
#include "CreateObject.h"
#include "MetaDataID.h"
#include "SDKFileHelper.h"
#include "StreamUtil.h"
#include "Utils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

// TODO this content is interesting- can we publish in Programmer's Guide or some other location
// that may be less obscure

/** \li Shows how to use XMP commands available in the InDesign/InCopy API.

	<B>A bit of background about XMP MetaData support in InDesign/InCopy:</B>
	
	In InDesign/InCopy, you can use the <B>File >> File Info...</B> menu item 
	to open a dialog that gives you access to the MetaData related operations 
	for your InDesign/InCopy document. In that dialog, you can do things such as:
	<UL>
	<LI>Set or view the MetaData for the document. 
    <LI>"Replace" MetaData from an *.XMP (text, XML) file.
	<LI>"Save" the MetaData to an *.XMP (text, XML) file.  
	</UL>
	
	Using XMP, you can attach metadata to your document, or information about 
	the content of your document.  For example, you can store these items as 
	MetaData:
	<UL>
	<LI>Standard InDesign/InCopy MetaData: author, title, keywords, etc.
	<LI>The source of the information contained in the document.
	<LI>Your own MetaData that needs to be part of the PDF you can export from 
		InDesign/InCopy. Please note that when you export your InDesign document 
		to PDF (with at least Acrobat 5.0 compatibility), the MetaData also 
  		becomes part of the PDF.
	</UL>	
	
	This codesnippet shows some of the API commands that do the 
	same thing, so you can automate your workflow involving MetaData.
	
	For more information about using MetaData in the InDesign/InCopy application,
	consult the InDesign/InCopy on-line help. 
	
	For general information about XMP, refer either to the XMP Overview Page 
	(http://www.adobe.com/products/xmp/main.html). 
	
	To incorporate XMP into your custom application outside of InDesign, refer 
	to the XMP Toolkit Download page (http://partners.adobe.com/asn/developer/xmp/download/).
	
	
	<B>How to use this snippet<B>
 
    First, 'save' the MetaData from the current document to a file.
  	Then using a text editor, modify the data inside some of the existing 
   	XMP MetaData "paths", and then 'replace'.
   	Make further changes, such as adding in new custom schemas, and then 
	'append'.  Then view how the MetaData changed in the File Information dialog.
 
	
	<B>XMP Programming Use cases:</B>
	<OL>
	<LI><B>How do I save MetaData to file?</B><BR>
			Query the IMetaDataAccess interface on the boss with the MetaData 
			model, and call the SaveToStream() method.  
			(See SnpPerformXMPCommands::SaveMetaDataToFile())</LI>
				
	<LI><B>How do I load MetaData from file?</B><BR>
			Process the kReplaceMetaDataCmdBoss (formerly known as 
  			kLoadMetaDataCmdBoss in 2.x). Specify the target boss (e.g. document) 
			and the IDFile in the IReplaceMetaDataCmdData data interface 
			(which used to be ILoadMetaDataCmdData in 2.x).
			Optionally, you can strip MetaData that is not part of the default 
			InDesign MetaData set, by processing kStripForeignMetaDataCmdBoss.
			This corresponds to the OFF state of the "Preseve additional MetaData" 
			checkbox in the File >> File Info... dialog.  
			(See SnpPerformXMPCommands::ReplaceMetaDataFromFile())</LI>
		
	<LI><B>How do I merge MetaData from file?</B><BR>
			Process the kAppendMetaDataCmdBoss (formerly known as 
			kMergeMetaDataCmdBoss in 2.x).  Specify the target boss (e.g. document) 
			and the IDFile in the IAppendMetaDataCmdData data interface 
			(which used to be IMergeMetaDataCmdData in 2.x)
			(See SnpPerformXMPCommands::AppendMetaDataFromFile())</LI>
		
	<LI><B>How do I get the value of a particular MetaData object?</B><BR>
			Query the IMetaDataAccess interface on the boss with the MetaData model, 
			and call the Enumerate() or Get() methods.
			(See SnpInspectXMPMetaData)</LI>
			
	<LI><B>How do I count the number of data elements of a particular MetaData 
  			tag?</B><BR>
			Query the IMetaDataAccess interface on the boss with the MetaData 
  			model, and call the Count() method.</LI>
		
	<LI><B>How do I modify (set, append, create a new path, remove) the value 
  			of a particular MetaData object?</B><BR>
			If you want to set the value of a default InDesign MetaData tag, 
			process one of the kSetAdobe...Cmd commands listed under "Low-level 
			MetaData commands" below. <BR> 
            If you want to set the value of a custom MetaData tag (a.k.a. foreign 
			MetaData), you will need to create a custom command.  Inside this 
			custom command, query the IMetaDataAccess interface on the boss with 
			the MetaData model, and call the AppendArrayItem() (if necessary), 
			Set(), Remove(), SetBoolean(), SetDateTime() or 
			ClearAllProperties() method.  <BR>
            To get a list of existing namespaces, run the 
			SnpInspectXMPMetaData snippet on an InDesign document, but without 
			any parameters for the snippet. Alternatively, you can refer to 
			the XMP Documentation.</LI>
	</OL>	
			
	<B>Reference:</B> 
		
		Related interfaces (in order of importance):
		<UL>
		<LI>IMetaDataAccess is a wrapper to IMetaData as well as the XMP 
  				Toolkit API.</LI>
		<LI>IMetaDataIterator is an iterator interface for MetaData 
  				objects.</LI>
		<LI>IAdobeBasicJobMetaData is a data interface to store and retrieve 
  				Adobe Basic Job MetaData. </LI>
		<LI>IAdobeCoreMetaData is a data interface to store and retrieve 
  				Adobe Core MetaData.</LI>
        <LI>IAdobeMediaMgmtMetaData is a data interface to store and retrieve 
  				Adobe Media Management MetaData.</LI>
        <LI>IAdobeRightsMgmtMetaData is a data interface to store and retrieve 
				Adobe Rights Management MetaData.</LI>
        <LI>ICalculateMetaData is a helper interface used by the MetaDataResponder 
				to calculate Adobe core MetaData.</LI>
        <LI>ILoadMetaData is a helper interface used by kLoadMetaDataCmdBoss and 
				kStripForeignMetaDataCmdBoss. (This interface was obsoleted in 3.0)</LI>
        <LI>IMergeMetaData is a helper interface used by kMergeMetaDataCmdBoss.
				(This interface was obsoleted in 3.0)</LI>
        <LI>IMetaData is used for the MetaData model, and should only be used from
  				 within a command.</LI>
		</UL>
		
		Other Includes to use:
		<UL>
		<LI>MetaDataID.h</LI>
		<LI>MetaDataTypes.h (included by various MetaData interfaces)</LI>
		</UL>
			
		Boss classes that have a MetaData model (look for IMetaData):
		<UL>
		<LI>kDocBoss is the MetaData model associated with a document.
		<LI>kMetaDataBoss is a generic MetaData model.
		</UL>
		
		High-level MetaData commands:
		<UL>
		<LI>kAppendMetaDataCmdBoss is in this codesnippet. Appends MetaData from a IDFile.  Uses IAppendMetaDataCmdData.
		<LI>kReplaceMetaDataCmdBoss is in this codesnippet. Loads MetaData from a IDFile and replaces the current document's metadata with it.  Uses IReplaceMetaDataCmdData.
		</UL>
		
		Low-level MetaData commands:
		<UL>
		<LI>kSetAdobeCoreMetaDataCmdBoss sets the Adobe Core MetaData.  Uses ISetAdobeCoreMDCmdData.
		<LI>kSetAdobeRightsMgmtMDCmdBoss sets the Adobe Core MetaData.  Uses ISetAdobeCoreMDCmdData.
		<LI>kSetAdobeBasicJobMDCmdBoss sets the Adobe Core MetaData.  Uses ISetAdobeCoreMDCmdData.
		<LI>kSetAdobeMediaMgmtMDCmdBoss sets the Adobe Core MetaData.  Uses ISetAdobeCoreMDCmdData.
		<LI>kStripForeignMetaDataCmdBoss removes the non-Adobe MetaData.  Uses IStripForeignMetaDataCmdData.
		</UL>
		
	@ingroup sdk_snippet
	@ingroup sdk_architecture
    
	@see IAdobeMediaMgmtMetaData
    @see IAdobeRightsMgmtMetaData
    @see ICalculateMetaData
    @see IMetaData
 	@see IMetaDataAccess
	@see IAdobeBasicJobMetaData
	@see IAdobeCoreMetaData
	@see IAppendMetaDataCmdData
	@see IMetaDataAccess
	@see IMetaDataIterator
	@see IReplaceMetaDataCmdData
	@see IStripForeignMetaDataCmdData


 */
class SnpPerformXMPCommands
{
public:

	/** Constructor.
	 */
	SnpPerformXMPCommands() {}

	/** Destructor.
	 */
	virtual ~SnpPerformXMPCommands() {}

	/** Replaces the XMP MetaData from a file with that of a boss class (e.g. document).
		@param targetObject IN The target boss class (e.g. document) to put MetaData into. 
		@param sysFile IN sysfile to read from.
		@param stripForeignData IN kTrue if you want to remove MetaData that is not 
			part of the InDesign default MetaData set.
			The default XMP data for InDesign consists of MetaData stored using 
			the following interfaces. 
			<UL>
			<LI>IAdobeBasicJobMetaData
			<LI>IAdobeCoreMetaData
			<LI>IAdobeMediaMgmtMetaData
			<LI>IAdobeRightsMgmtMetaData
			</UL>
		@return Status. Returns kSuccess if success. 
	*/
	virtual ErrorCode ReplaceMetaDataFromFile(IPMUnknown* targetObject, 
										   const IDFile& sysFile, 
										   bool16 stripForeignData = kFalse);

	/** Appends the MetaData from a file into a boss class (e.g. document).
		@param targetObject IN The target boss class (e.g. document) to merge MetaData into. 
		@param sysFile IN sysfile to read from.
		@return Status. Returns kSuccess if success. 
	*/
	virtual  ErrorCode AppendMetaDataFromFile(IPMUnknown* targetObject, 
											  const IDFile& sysFile);

	/** Saves the MetaData in the boss class (e.g. document) to the file.
		@param targetObject The target boss class (e.g.: document) to obtain MetaData from. 
		@param sysFile IN sysfile to read from.
		@return Status. Returns kSuccess if success. 
	*/
	virtual ErrorCode SaveMetaDataToFile(IPMUnknown* targetObject,
										 const IDFile& sysFile);

	/** Obtains a pointer to the IMetaDataAccess interface in a boss class (e.g. kDocBoss).
		@param targetObject The target boss class (e.g. document) to obtain MetaData from.
		@return IMetaDataAccess*.  nil if not found in boss class.
	*/
	IMetaDataAccess* QueryMetaData(IPMUnknown* targetObject);


};

/* SaveMetaDataToFile
*/
ErrorCode SnpPerformXMPCommands::SaveMetaDataToFile(IPMUnknown* targetObject, 
													const IDFile& sysFile)
{
	ErrorCode status = kFailure;
	do 
	{
		bool16 result = kFalse;

		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}

		// create a stream (text file)
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWrite(sysFile, kOpenOut, 'TEXT'));
		if (stream == nil)
		{
			ASSERT_FAIL("stream is nil - failed to create stream to write!");
			break;
		}

		// obtain the IMetaDataAccess from boss class (e.g. kDocBoss)
		InterfacePtr<IMetaDataAccess> metaDataAccess(targetObject, UseDefaultIID());
		if (metaDataAccess == nil)
		{
			ASSERT_FAIL("metaDataAccess is nil - This boss class does not have IMetaDataAccess");
			break;
		}

		// save to stream
		result = metaDataAccess->SaveToStream(stream);
		if (result == kTrue) 
		{
			status = kSuccess;
		}

	} while(false);

	return status;
}

/* ReplaceMetaDataFromFile
*/
ErrorCode SnpPerformXMPCommands::ReplaceMetaDataFromFile(IPMUnknown* targetObject, 
														 const IDFile& sysFile, 
														 bool16 stripForeignData/*= kFalse*/)
{
	ErrorCode status = kFailure;
	
	do 
	{
		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}
		
		// start a command sequence (if we get multiple commands)
		CmdUtils::SequenceContext cmdSequence;
		
        // setup and process ReplaceMetaDataCmd
		InterfacePtr<ICommand> replaceMetaDataCmd(CmdUtils::CreateCommand(kReplaceMetaDataCmdBoss));
		if (replaceMetaDataCmd == nil)
		{
			ASSERT_FAIL("Failed to create replaceMetaDataCmd!");
			break;
		}
		InterfacePtr<IReplaceMetaDataCmdData> data(replaceMetaDataCmd, UseDefaultIID());
		if (data == nil)
		{
			ASSERT_FAIL("Failed to create data interface for replaceMetaDataCmd!");
			break;
		}

		// set the target object (e.g. document) an file path to load
		data->Set(targetObject, sysFile);

		// process the ReplaceMetaDataCmd
		status = CmdUtils::ProcessCommand(replaceMetaDataCmd);
        if (status != kSuccess)
		{
			ASSERT_FAIL("kReplaceMetaDataCmdBoss failed!");
			break;
		}

		if (stripForeignData) 
		{
			// strip down to just the basic InDesign MetaData
			InterfacePtr<ICommand> stripMetaDataCmd
				(CmdUtils::CreateCommand(kStripForeignMetaDataCmdBoss));
			if (stripMetaDataCmd == nil)
			{
				ASSERT_FAIL("Failed to create stripMetaDataCmd!");
				break;
			}
			
			InterfacePtr<IStripForeignMetaDataCmdData> 
				stripData(stripMetaDataCmd, UseDefaultIID());
			if (stripData == nil)
			{
				ASSERT_FAIL("Failed to create data interface for stripMetaDataCmd!");
				break;
			}
			
			// set the target object (e.g. document) that you want to strip the MetaData down to the basic InDesign set
			stripData->Set(targetObject);
			
			// process the stripMetaDataCmd
			status = CmdUtils::ProcessCommand(stripMetaDataCmd);
			if (status != kSuccess)
			{
				ASSERT_FAIL("kStripForeignMetaDataCmdBoss failed!");
				break;
			}
		}
	} while(false);

	return status;
}

/* AppendMetaDataFromFile
*/
ErrorCode SnpPerformXMPCommands::AppendMetaDataFromFile(IPMUnknown* targetObject, 
														const IDFile& sysFile)
{
	ErrorCode status = kFailure;
    do 
	{
		if (targetObject == nil)
		{
			ASSERT_FAIL("targetObject is nil!");
			break;
		}
		
		// set up AppendMetaDataCmd
		InterfacePtr<ICommand> appendMetaDataCmd
			(CmdUtils::CreateCommand(kAppendMetaDataCmdBoss));
		if (appendMetaDataCmd == nil)
		{
			ASSERT_FAIL("Failed to create appendMetaDataCmd!");
			break;
		}

		// setup the data interface
        InterfacePtr<IAppendMetaDataCmdData> 
			data(appendMetaDataCmd, UseDefaultIID());
		if (data == nil)
		{
			ASSERT_FAIL("Failed to create data interface for appendMetaDataCmd!");
			break;
		}

		// specify the data for the data interface (e.g. document)
		data->Set(targetObject, sysFile);

		// process the command
		status = CmdUtils::ProcessCommand(appendMetaDataCmd);
		if (status != kSuccess)
		{
			ASSERT_FAIL("kAppendMetaDataCmdBoss failed!");
			break;
		}

	} while(false);

	return status;
}

/* QueryMetaData
*/
IMetaDataAccess* SnpPerformXMPCommands::QueryMetaData(IPMUnknown* targetObject)
{
	IMetaDataAccess* metaDataAccess = nil;
	if (targetObject != nil) 
	{
		metaDataAccess = 
			(IMetaDataAccess*)targetObject->QueryInterface(IMetaDataAccess::kDefaultIID);
	} 
	return metaDataAccess;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
class _SnpRunnerPerformXMPCommands : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerPerformXMPCommands(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerPerformXMPCommands(void);

	/** Return kTrue if the snippet can run.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kTrue if snippet can run, kFalse otherwise
	 */
	bool16 CanRun(ISnpRunnableContext* runnableContext);

	/** Run the snippet.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode otherwise.
	*/
	ErrorCode Run(ISnpRunnableContext* runnableContext);
	
	/** 
		get the snippet context
		@return eSnpRunContextType for this snippet
	*/
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunFrontDocContext;}
};
/* Constructor.
*/
_SnpRunnerPerformXMPCommands::_SnpRunnerPerformXMPCommands(void) : SnpRunnable("PerformXMPCommands")
{
	this->SetDescription("Processes some of the fundamental XMP commands available in the InDesign/InCopy API");
    this->SetPreconditions("Front document must be available");
	this->SetCategories("sdk_snippet, sdk_architeture");
}

/* Destructor.
*/
_SnpRunnerPerformXMPCommands::~_SnpRunnerPerformXMPCommands(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformXMPCommands::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
		if (doc == nil) 
		{
			break;
		}
		// if we got here, we can run
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformXMPCommands::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpPerformXMPCommands instance;
		IDocument* doc = runnableContext->GetActiveContext()->GetContextDocument();
		if (doc == nil) 
		{
			SNIPLOG("You do not have a document open.  This snippet requires a front document.");
			break;
		}

		// get user choices
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.clear();
		choices.push_back(PMString("Replace metadata using .xmp file"));
		choices.push_back(PMString("Save metadata to .xmp file"));
		choices.push_back(PMString("Append metadata from .xmp file"));
		enum { kReplaceMetaData, kSaveMetaData, kAppendMetaData };
		int32 defaultChoice = kReplaceMetaData;
		PMString prompt = "What metadata operation would you like to perform?";
		int32 choice = parameterUtils->GetChoice(prompt, choices, defaultChoice);

		if (parameterUtils->WasDialogCancelled()) 
		{
			// cancelled
			break;
		}
		
		// set up constants and variables for fileChooser
		const SysOSType kXMPTextType = 'TEXT';
		const SysOSType kXMPCreator = 'ttxt';
		const PMString kXMPExtension("xmp");
		const PMString kXMPFilterName("XMP MetaData file(xmp)");
		IDFile sysFile;
		PMString filename;
		
		switch (choice) 
		{
		default:
			{
				SNIPLOG("Invalid choice, using default (Load)");
			}
			// fall through
		case kReplaceMetaData:
			{
				SDKFileOpenChooser fileChooser;
				fileChooser.AddFilter(kXMPTextType, kXMPExtension, kXMPFilterName);
  				fileChooser.SetTitle("Select XMP MetaData file to replace with");
				fileChooser.ShowDialog();
				if (fileChooser.IsChosen()) 
				{
					sysFile = fileChooser.GetIDFile();
				}
				if (fileChooser.IsExisting() == kFalse) 
				{
					filename = fileChooser.GetPath();
					SNIPLOG("\"%s\" does not exist! Cancelling.", filename.GetPlatformString().c_str()); 
					break; // out of switch statement
				}

				// replace the MetaData from file into document 
				status = instance.ReplaceMetaDataFromFile(doc, sysFile);
				if (status == kSuccess) 
				{
					SNIPLOG("Please open the File >> File Info menu to examine your MetaData."); 
				}
			}
			break;

		case kSaveMetaData:
			{
				SDKFileSaveChooser fileChooser;
				fileChooser.AddFilter(kXMPCreator, kXMPTextType, kXMPExtension, kXMPFilterName);
  				fileChooser.SetTitle("Specify XMP MetaData file to save");
				fileChooser.ShowDialog();
				if (fileChooser.IsChosen()) 
				{
					sysFile = fileChooser.GetIDFile();
				}

				// save the document MetaData to file
				// optional parameter using default
				status = instance.SaveMetaDataToFile(doc, sysFile); 
				if (status == kSuccess) 
				{
					filename = fileChooser.GetPath();
					SNIPLOG("Please look at %s to view the MetaData.", filename.GetPlatformString().c_str()); 
				}
			}
			break;

		case kAppendMetaData:
			{
				SDKFileOpenChooser fileChooser;
				fileChooser.AddFilter(kXMPTextType, kXMPExtension, kXMPFilterName);
  				fileChooser.SetTitle("Select XMP MetaData file to append with document");
				fileChooser.ShowDialog();
				if (fileChooser.IsChosen()) 
				{
					sysFile = fileChooser.GetIDFile();
				}
				if (fileChooser.IsExisting() == kFalse) 
				{
					filename = fileChooser.GetPath();
					SNIPLOG("\"%s\" does not exist! Cancelling.", filename.GetPlatformString().c_str()); 
					break; // out of switch statement
				}

				// append the MetaData from file into document
				status = instance.AppendMetaDataFromFile(doc, sysFile);
				if (status == kSuccess) 
				{
					SNIPLOG("Please open the File >> File Info menu to examine your MetaData."); 
				}
			}
			break;
		}
		
	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformXMPCommands instance_SnpRunnerPerformXMPCommands;
DEFINE_SNIPPET(_SnpRunnerPerformXMPCommands) 	

// End, SnpPerformXMPCommands.cpp

