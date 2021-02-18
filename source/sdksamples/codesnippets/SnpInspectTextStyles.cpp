//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectTextStyles.cpp $
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
#include "IWorkspace.h"
#include "IStyleNameTable.h"
#include "IStyleGroupManager.h"
#include "IStyleGroupHierarchy.h"
#include "IStyleInfo.h"
#include "IAttrReport.h"
#include "ITextAttributes.h"
#include "ITextAttrSpecialGlyph.h"
#include "IPMStream.h"
#include "ITextAttrMissingImplData.h"

// General includes:
#include "AttributeBossList.h"
#include "PersistUtils.h"	// GetDatabase
#include "StreamUtil.h"
#include "Utils.h"
#include "ShuksanID.h" // for FileTypeInfoID's
#include "FileTypeRegistry.h"
#include "SDKFileHelper.h"
#include "UIDList.h"

// Framework includes:
#include "SnipRunLog.h"
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"

// NOTE: When you run this snippet in the Roman debug build, you will get a set of asserts, something like:
// "No translation of key 'force vertical glyphs', 'Str_Auto', etc. to English string". If you run this snippet
// under Japanese debug build or the release build, you won't get them. In order to quiet those asserts when
// you are running on Roman debug build, please go to Test >> UI menu, and select "Toggle Trace/Assert For Missing
// String Translations", then run this snippet. You may want to switch the assert back when you done with this snippet.


/**
	\li	Reports paragraph or character style table (IStyleGroupManager) information and defaults (ITextAttributes).

  	@ingroup sdk_snippet
  	@ingroup sdk_text
	@see IWorkspace
	@see IStyleGroupManager
	@see IStyleInfo
	@see ITextAttributes
 */
class SnpInspectTextStyles
{
public:

	/** Constructor.
		*/
	SnpInspectTextStyles() {}

	/** Destructor.
		*/
	virtual			~SnpInspectTextStyles() {}

	/**
		Report paragraph or character style table info.
		@param inspectPara kTrue to look at paragraph style table, kFalse for character.
		@param runnableContext see ISnpRunnableContext for documentation.
		@return kSuccess on success, other ErrorCode on failure.
	*/
	ErrorCode Inspect
	(
		const bool16 inspectPara, ISnpRunnableContext* runnableContext
	);

protected:

	/**
	*/
	ErrorCode helperDisplayStyleInformation(const InterfacePtr<IStyleInfo>& thisStyle, int32 tabAmount, IPMStream* stream);

	/**
	*/
	ErrorCode helperInspectStylesRecurse(const InterfacePtr<IStyleGroupManager>& iParaStyleNameTable, const UID& parentStyleUID, int32 tabAmount, IPMStream* stream);

	/**
	*/
	ErrorCode helperDisplayTextAttributes(const InterfacePtr<ITextAttributes>& iTextAttributes, const PMString& tabLevel, IPMStream* stream);

	/**
	*/
	ErrorCode reportAttribute(const ClassID& attrClass, IPMUnknown * unknown,IDataBase * theDB, PMString * Description, const AttributeBossList* attrList);


};

// TODO can we do this more elegantly please
#ifdef MACINTOSH
		static const char* kSnpExternalNewLine="\r";
#else
		static const char* kSnpExternalNewLine="\r\n";
#endif

/*
*/
ErrorCode SnpInspectTextStyles::Inspect
(
	const bool16 inspectPara, ISnpRunnableContext* runnableContext
)
{
	SNIPLOG("IN SnpInspectTextStyles::Inspect");
	ErrorCode status = kFailure;
	do {

		IWorkspace* iWorkspace = runnableContext->GetActiveContext()->GetContextWorkspace();
		ASSERT(iWorkspace);
		if (iWorkspace == nil) {
			break;
		}


		// create a stream to write to.
		SDKFileSaveChooser fileChooser;
		PMString title("Style dump log", PMString::kTranslateDuringCall);
		fileChooser.SetTitle(title);
		SysOSType macFileCreator = FileTypeRegistry::GetCurrentFileCreator(kPublicationFileTypeInfoID);
		fileChooser.AddFilter(macFileCreator, 'TEXT', "txt", "TEXT file(txt)");
		fileChooser.ShowDialog();
		if (!fileChooser.IsChosen()) {
			break;
		}
		IDFile dumpFileName = fileChooser.GetIDFile();
		InterfacePtr<IPMStream> stream(StreamUtil::CreateFileStreamWriteLazy(dumpFileName, kOpenOut | kOpenTrunc, 'TEXT', macFileCreator));
		ASSERT(stream);
		if (!stream) {
			break;
		}

		// Dump styles
		if (inspectPara == kTrue)
		{
			// Paragraph style nametable
			InterfacePtr<IStyleGroupManager> iParaStyleNameTable(iWorkspace,IID_IPARASTYLEGROUPMANAGER);
			ASSERT(iParaStyleNameTable);
			if (iParaStyleNameTable == nil) {
				break;
			}
			UID rootStyleUID = iParaStyleNameTable->GetRootStyleUID();
			ASSERT(rootStyleUID != kInvalidUID);
			if(rootStyleUID == kInvalidUID) {
				break;
			}

			status = helperInspectStylesRecurse(iParaStyleNameTable, rootStyleUID, 0, stream);
		}
		else
		{
			// Character style nametable
			InterfacePtr<IStyleGroupManager> iCharStyleNameTable(iWorkspace,IID_ICHARSTYLEGROUPMANAGER);
			ASSERT(iCharStyleNameTable);
			if (iCharStyleNameTable == nil) {
				break;
			}
			UID rootStyleUID = iCharStyleNameTable->GetRootStyleUID();
			ASSERT(rootStyleUID != kInvalidUID);
			if(rootStyleUID == kInvalidUID) {
				break;
			}

			status = helperInspectStylesRecurse(iCharStyleNameTable, rootStyleUID, 0, stream);
		}


		// Dump defaults
		InterfacePtr<ITextAttributes> defaultTextAttributes(iWorkspace, UseDefaultIID());
		ASSERT(defaultTextAttributes);
		if (!defaultTextAttributes)
		{
			break;
		}
		PMString line = PMString("----------------- Defaults ------------------");
		line.Append(kSnpExternalNewLine);
		std::string sline = line.GetPlatformString();
		stream->XferByte((uchar*)sline.c_str(), static_cast<int32>(sline.length()));
		this->helperDisplayTextAttributes(defaultTextAttributes, PMString(""), stream);

		stream->Flush();
		stream->Close();

	} while(false);

	SNIPLOG("OUT SnpInspectTextStyles");
	return (status);
} // SnipInspectTextStyles


/*
*/
ErrorCode SnpInspectTextStyles::helperInspectStylesRecurse(const InterfacePtr<IStyleGroupManager>& iParaStyleNameTable, const UID&  parentStyleUID, int32 tabAmount, IPMStream* stream)
{
	ErrorCode myStatus = kFailure;
	do {
		// Get the styles style info
		InterfacePtr<IStyleInfo> parentStyleInfo(::GetDataBase(iParaStyleNameTable),parentStyleUID,UseDefaultIID());
		ASSERT(parentStyleInfo);
		if(parentStyleInfo == nil) {
			break;
		}

		// dump information on this style to trace - regard the indentation through tabAnount
		if(helperDisplayStyleInformation(parentStyleInfo, tabAmount, stream) != kSuccess) {
			break;
		}
		// now the recursive part:-
		ASSERT(iParaStyleNameTable);
		if(iParaStyleNameTable == nil) {
			break;
		}


		UIDList paraStyles(::GetDataBase(iParaStyleNameTable));
		iParaStyleNameTable->GetRootHierarchy()->GetDescendents(&paraStyles,IID_ISTYLEINFO);

		int32 numberOfStyles = paraStyles.Length();
		// need an internal error code variable
		ErrorCode internalStatus = kFailure;
		// for every style in the name table
		for(int styleCounter =0; styleCounter < numberOfStyles;styleCounter++)
		{
			internalStatus = kFailure;
			// look at every style
			UID childStyleUID = paraStyles[styleCounter];
			// get the style info for that style
			InterfacePtr<IStyleInfo> childStyleInfo(::GetDataBase(parentStyleInfo),childStyleUID,UseDefaultIID());
			ASSERT(childStyleInfo);
			if (childStyleInfo == nil) {
				break;
			}
			// find out who its parent is
			UID childsParentUID = childStyleInfo->GetBasedOn();

			// if the parent is the current style, dump this style, i.e. I am now the root dump my children.
			if (childsParentUID==parentStyleUID) // This parent is me!
			{
				// increase the indentation level and dump those children!
				internalStatus = helperInspectStylesRecurse(iParaStyleNameTable,childStyleUID,tabAmount+1, stream);
			}
			else
			{
				// This is the conclusive case, success is set here
				internalStatus = kSuccess;
			}
		}

		// if there is failure, we want to break
		if (internalStatus == kFailure)	{
			break;
		}

		myStatus = kSuccess;
	} while (false);
	return myStatus;
}

/*
*/
ErrorCode SnpInspectTextStyles::helperDisplayStyleInformation(const InterfacePtr<IStyleInfo>& thisStyle, int32 tabAmount, IPMStream* stream)
{
	ErrorCode myStatus = kFailure;
	do {
		if (stream == nil)
			// can't write to stream! Just exit.
	        break;

		int32 localcnt = tabAmount;
		PMString tabLevel("\0");
		while ((localcnt--) > 0) {
			tabLevel.Append("\t\t");
		}

		// Get the parent style
		UID myParentUID = thisStyle->GetBasedOn();
		PMString parentName("Root");
		if (myParentUID!=kInvalidUID) // I am not the root
		{
			// get the parent's name
			InterfacePtr<IStyleInfo> parentStyleInfo(::GetDataBase(thisStyle),myParentUID, UseDefaultIID());
			ASSERT(parentStyleInfo);
			if (parentStyleInfo == nil){
				break;
			}

			parentName = parentStyleInfo->GetName();
		}

		// get our name
		PMString styleName = thisStyle->GetName();
		PMString str(tabLevel);
		str += styleName;
		str += " has parent: ";
		str += parentName;
		SnipRunLog::Instance()->Log(str);
		// we also want to out put the detailed attribute reports to file through standard file output stream
		PMString line = tabLevel + "-----------------" + styleName + " -- Based on " + parentName + "------------------";
		line.Append(kSnpExternalNewLine);
		std::string sline = line.GetPlatformString();
		stream->XferByte((uchar*)sline.c_str(), static_cast<int32>(sline.length()));

		// get the attributes for this style
		InterfacePtr<ITextAttributes> iTextAttributes(thisStyle,IID_ITEXTATTRIBUTES);
		if (iTextAttributes == nil)
		{
			ASSERT_FAIL("helperDisplayStyleInformation - no text attributes for style?");
			break;
		}

		myStatus = this->helperDisplayTextAttributes(iTextAttributes, tabLevel, stream);

	} while (false);
	return myStatus;
}

/*
*/
ErrorCode SnpInspectTextStyles::helperDisplayTextAttributes(const InterfacePtr<ITextAttributes>& iTextAttributes, const PMString& tabLevel, IPMStream* stream)
{
	ErrorCode myStatus = kFailure;
	do {
		int32 NumberOfBosses = iTextAttributes->CountBosses();
		PMString bossNumber;
		bossNumber.AppendNumber(NumberOfBosses);
		PMString line = tabLevel + "Number of bosses is " + bossNumber;
		line.Append(kSnpExternalNewLine);
		std::string sline = line.GetPlatformString();
		stream->XferByte((uchar*)sline.c_str(), static_cast<int32>(sline.length()));
		const AttributeBossList* iAttrList = iTextAttributes->GetBossList();
		PMString Description;
		Description.Append(tabLevel);
		if(NumberOfBosses==0) // indicate no change from parent
			Description.Append("Empty");
		// I need an internal error status control variable for this inner loop.
		ErrorCode innerStatus = kFailure;
		// we know how many text attributes are described by the boss, we now need to examine each of them individually
		for (int32 bossloop = 0; bossloop < NumberOfBosses; bossloop++)
		{
			innerStatus = kFailure;

			ClassID attrClass = iTextAttributes->GetClassN(bossloop);
			InterfacePtr<IPMUnknown>	unknown((IPMUnknown*)(iTextAttributes->QueryBossN(bossloop, IID_IUNKNOWN)));

			// Append the index of the boss in the list.
			Description.Append("(");
			Description.AppendNumber(bossloop);
			Description.Append(")");

			// append the description of the attribute
			if ((this->reportAttribute(attrClass, unknown, ::GetDataBase(iTextAttributes), &Description, iAttrList)) != kSuccess)
			{	// must be some problem with displaying the style info
				ASSERT_FAIL("helperDisplayStyleInformation - failed to report attribute!?");
				break;
			}
			// with every 5 descriptions, we append a newline to format our report
			if ((bossloop+1)%5==0)
			{
				Description.Append(kSnpExternalNewLine);
				// we want the new line to start at  the right level of indentation
				Description.Append(tabLevel);
			}
			innerStatus = kSuccess;
		}
		if (innerStatus == kFailure)
		{
			break;
		}
		line = tabLevel + "-:Description:-";
		line.Append(kSnpExternalNewLine);
		line.Append(Description);
		line.Append(kSnpExternalNewLine);
		sline = line.GetPlatformString();
		stream->XferByte((uchar*)sline.c_str(), static_cast<int32>(sline.length()));

		myStatus = kSuccess;
	} while(false);
	return myStatus;
}



// this method attempts to report information about an attribute, if the attribute doesn't
// describe itself, the boss name is appended to description. If the boss name isn't registered with the object model
// the boss id is displayed (as a hex number).
ErrorCode
SnpInspectTextStyles::reportAttribute(const ClassID& id, IPMUnknown* unknown, IDataBase * theDB, PMString * Description, const AttributeBossList* attrList)
{
	ErrorCode myStatus = kFailure;
	do {

		if (unknown == nil)
		{
			Description->Append("***INVALID IPMUnknown***");
			myStatus = kSuccess;
			break;
		}

		// which boss are we dealing with?
		InterfacePtr<IAttrReport>	report(unknown, UseDefaultIID());
		if (report == nil)
		{
			InterfacePtr<ITextAttrMissingImplData> missing(unknown, UseDefaultIID());
			if (missing)
			{
				// The plug-in that implements this attribute is missing.
				ClassID missingClassID = missing->GetClassID();
				char buf[128];
				sprintf(buf, "***MISSING PLUG_IN ITextAttrMissingImplData::GetClassID=0x%x***", missingClassID.Get());
				Description->Append(buf);
			}
			else
			{
				Description->Append("***INVALID IAttrReport***");
			}
		}

		// cache the current value to allow us to check if it changes...
		PMString oldDescription(*Description);
		if (report)
		{
 			report->AppendDescription(Description, theDB, attrList);
		}

		// TODO Be nice to have a verbose report that dumped all the ClassID info.
		// Maybe add a parameter later to control this.
		if (Description->CharCount() == oldDescription.CharCount()) // no change
		{
			// if the attribute did not describe itself, attempt to get the boss name from the object model
			InterfacePtr <IObjectModel> iOM(GetExecutionContextSession(),IID_IOBJECTMODEL);
			if (iOM == nil)
			{
				ASSERT_FAIL("reportAttribute - no object model?");
				break;
			}
			const char * className = iOM->GetIDName(kClassIDSpace,id.Get());
			PMString myString("~ Boss ");
			if (className == nil)
			{
				// if we couldn't get the boss name, we can at least display the boss id
				char * buf = new char [11];
				if (buf == nil)
				{	// new fails?
					ASSERT_FAIL("reportAttribute - new fails");
					break;
				}
				sprintf(buf, "0x%x", id.Get());
				myString.Append(buf);
				delete[] buf;
				PMString inDec;
				// append the decimal number...
				inDec.Append("(");
				inDec.AppendNumber(id.Get());
				inDec.Append(")");
				myString.Append(inDec);
			}
			else
				myString.Append(className);
			myString.Append(" ");
			Description->Append(myString);
		}
		// if we get here, we have not had a failure we have tested for
		myStatus = kSuccess;
	} while (kFalse);
	return myStatus;
}



// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerInspectTextStyles : public SnpRunnable
{


public:
	// SnippetRunner framework hooks.

	/** Constructor.
		*/
	_SnpRunnerInspectTextStyles();

	/** Destructor.
		*/
	virtual			~_SnpRunnerInspectTextStyles();

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
_SnpRunnerInspectTextStyles::_SnpRunnerInspectTextStyles() : SnpRunnable("InspectTextStyles")
{
	// Describe what your snippet does.
	this->SetDescription("Inspects text styles");

	// Describe the preconditions your snippet requires.
	this->SetPreconditions("none");
	// e.g. "document open" or "layout selection set".

	// Provide the categories your snippet belongs to.
	this->SetCategories("sdk_snippet, sdk_text");
	// e.g. "sdk_snippet, sdk_layout"
	// Use a CSV string if you belong to more than one category.
}

/* Destructor.
*/
_SnpRunnerInspectTextStyles::~_SnpRunnerInspectTextStyles()
{
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerInspectTextStyles::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInspectTextStyles::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpInspectTextStyles instance;
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		choices.push_back("Paragraph styles");
		choices.push_back("Character styles");
		enum {kPara, kChar};
		int32 choice  = parameterUtils->GetChoice("Which style table do you want to inspect?", choices);
		if (parameterUtils->WasDialogCancelled()) {
			break;
		}
		bool16 inspectPara = kFalse;
		if (choice == kPara)
		{
			inspectPara = kTrue;
		}
		status = instance.Inspect(inspectPara, runnableContext);

	} while(false);
	return (status);
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectTextStyles instance_SnpRunnerInspectTextStyles;
DEFINE_SNIPPET(_SnpRunnerInspectTextStyles)

// End, SnpInspectTextStyles.cpp

