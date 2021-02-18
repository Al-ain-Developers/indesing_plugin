//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformCompFont.cpp $
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
#include "IBoolData.h"
#include "ICommand.h"
#include "ICompositeFont.h" // also contains CharacterRange, CharRangeCollection, and ICompFontDataSettings
#include "ICompositeFontMgr.h"
#include "IDataBase.h"
#include "IDocFontMgr.h"
#include "IDocument.h"
#include "IFontFamily.h"
#include "IFontMgr.h"
#include "IIdleTask.h"
#include "IIntData.h"
#include "ILayoutUtils.h"
#include "IPMFont.h"
#include "ITextAttrFont.h"
#include "ITextAttributes.h"
#include "ITextAttrUID.h"
#include "ISession.h"
#include "IStringData.h"
#include "IStyleNameTable.h"
#include "IUIDData.h"
#include "IWorkspace.h"

// General includes:
#include "CompositeFontMgrID.h"
#include "K2TypeTraits.h"
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "LocaleSetting.h"
#include "PMLocaleId.h"
#include "SystemUtils.h"
#include "TextAttrID.h"
#include "Utils.h"
#include "ErrorUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"


// TOD Why are we using struct's that have sideways copies
// of data stored elsewhere (sounds like ICompositeFont); see coding conventions
// TODO why structs rather than classes

/** Stores the composite font character classes used for 
 * 	ICompFontDataSettings.  This structure is a field in the 
 * 	SnpCompositeFontData structure. 
 * 	@see ICompFontDataSettings
 */
struct SnpCompFontDataSettings
{
	/** Flag to determine if this is a default character class. */
	bool16 fIsDefault;
    /** Name of the character class */
	PMString fName;
	/** Font UID used by this character class */
	UID fFontUID;
	/** Font style used by this character class */
	PMString fFontStyle;
	/** Font size for this character class. */
	PMReal fSizeValue;
	/** Baseline offset value for this character class */
	PMReal fBaselineValue;
	/** Horizontal scale for this character class. */
	PMReal fHScaleValue;
	/** Vertical scale for this character class. */
	PMReal fVScaleValue;
	/** Indicates if this character class can or cannot be edited */
	bool16 fIsLocked;
	/** Specifies the range of characters in this character class. 
	 * 	@see CharacterRange
	 * 	@see CharRangeCollection
	 */
	CharRangeCollection fRanges;
	/** Scale option in the user interface for this character class. */
	bool16 fScaleOption;
};

/** Typedef for K2Vector of SnpCompFontDataSettings
 */
typedef K2Vector<SnpCompFontDataSettings> SnpCompFontDataSettingList;
DECLARE_OBJECT_TYPE(SnpCompFontDataSettings);

/**	Stores all composite font related attributes in a single structure.
 * 	Note that this sample only sets a few of the members, however
 * 	all members are inspected.
 * 	All member variables correspond to a method in ICompositeFont.
 * 	@see ICompositeFont
 */
struct SnpCompositeFontData
{
	/** The based-on font.
	 * 	@see ICompositeFont::GetBasedOn() 
	 * 	@see ICompositeFont::SetBasedOn() */
	UID fBasedOn;
	/** The composite font name.
	 * 	@see ICompositeFont::SetFont() */
	PMString fName;
	/** The font family name (no set, only get).
	 * @see ICompositeFont::GetFontFamilyName()
	 */
	PMString fFontFamilyName;
	/** The native font family name (no set, only get).
	 * 	@see ICompositeFont::GetNativeFontFamilyName()
	 */
	PMString fNativeFontFamilyName;
	/** The name style.
	 * 	@see ICompositeFont::GetNameStyle()
	 * 	@see ICompositeFont::SetNameStyle() */
	PMString fNameStyle;
	/** The post script name.
	 * 	@see ICompositeFont::GetPostScriptName()
	 * 	@see ICompositeFont::SetPostScriptName() */
    PMString fPostScriptName;
    /** The CMap filename.
	 * 	@see ICompositeFont::GetCMapFileName()
	 * 	@see ICompositeFont::SetCMapFileName() */
	PMString fCMapFileName;
    /** Is the composite font locked?
	 * @see ICompositeFont::IsLocked()
	 * 	@see ICompositeFont::SetLocked() */
	bool16 fIsLocked;
	/** The font matrix adjustment factor.
	 * 	@see ICompositeFont::SetFontMatrixAdjustment()
	 * 	@see ICompositeFont::GetFontMatrixAdjustment() */
	uint16 fFontMatrixAdjustment;
	/** The character classes. 
	 * 	@see ICompositeFont::AppendCharClass()
	 * 	@see ICompositeFont::GetCharClass() */
	SnpCompFontDataSettingList fCharClasses;
	/** The document related to the composite font. 
	 * 	@see ICompositeFont::AddDocument()
	 * 	@see ICompositeFont::QueryDocument() */
	IDocument* fDocument;
};


/** \li Inspects a composite font,
 * 	\li Creates a new composite font, and 
 * 	\li Deletes an existing composite font.
 * 
 *  (1) <B>Inspecting a composite font</B>:
 * 	Select one of the existing composite fonts to inspect. The
 * 	data associated with the composite font will be written to the SNIPLOG.
 * 
 *  (2) <B>Creating a Composite font</B>:
 * 	Enter the name of your new composite font, and select which existing 
 * 	composite font you want to base it on.  
 * 	After creating a composite font, you can apply the new composite font 
 * 	on your	text selection by simply using the Character Panel (or 
 * 	Text >> Font menu). If you want to do it programmatically, you can 
 * 	apply the kTextAttrFontUIDBoss attribute on the text model.
 * 
 * 	NOTE: If you are creating composite fonts using Japanese fonts and
 * 	Japanese character classes, it is recommeded that you create them based
 * 	on existing	composite fonts, such as the default composite font. 
 * 	When you add character classes to a composite font, the priority by which
 * 	a certain font setting is used is determined by how late it appears in the
 * 	character class lists. For instance, if the hiragana character "A" appears
 * 	in the "Kana" class (character class index 1) and a new character class 
 * 	"Hiragana Only" (character class index 7), then the font settings applied
 * 	to character class index 7 will be used for this character when it appears
 * 	on the layout.
 * 	It is for this reason that an AddCompFontCharClassCmd is available, and
 * 	a RemoveCompFontCharClassCmd isn't.
 * 
 *  NOTE: When you are creating composite fonts for CJK languages other than
 * 	Japanese (e.g. Chinese, Korean), make sure you do NOT use the default
 * 	composite font as a basis. The characters specified in the character 
 * 	classes of the default composite font do not apply to other CJK languages.
 * 
 *  (3) <B>Deleting a composite font</B>:
 * 	Select one of the existing composite fonts to delete. After deleting, 
 * 	go to the Character Panel to verify that the composite font is gone. 
 * 
 *  <B>About Composite Fonts</B>:
 * 
 * 	"Composite fonts" are meta-fonts where specific fonts are used for 
 * 	predetermined sets of characters. For instance, in a composite font,
 * 	you can use one font for Roman alphabet characters, another for
 * 	kanji characters, another for kana characters, and yet another 
 * 	font for numerical characters.
 * 
 * 	While you do not need the Japanese version of InDesign to run 
 * 	this snippet, you will need the Japanese version of InDesign to 
 * 	create or view a composite font using the application user interface. 
 * 	
 * 	@ingroup sdk_snippet
 * 	@ingroup sdk_cjk
 * 	@ingroup sdk_text
 */
class SnpPerformCompFont 
{
public:

	/** Constructor.
	 */
	SnpPerformCompFont() {}

	/** Destructor.
	 */
	virtual ~SnpPerformCompFont() {}

	/** Creates a new composite font
	 * 	@param ws IN The workspace on which the composite font will be created.  
	 * 		Either kWorkspaceBoss or kDocWorkspaceBoss. 
	 * 	@param data IN SnpCompositeFontData struct.  Prefill before calling.
	 * 	@param newCompFontUID OUT The UID of the newly created composite font.
	 * 	@return kSuccess on success, kFailure otherwise.
	 * 	@see kNewCompositeFontCmdBoss
	 * 	@see kAddCompFontClassCmdBoss
	 */
	ErrorCode CreateCompFont(IWorkspace* ws,
							 const SnpCompositeFontData& data,
							 UID& newCompFontUID);

	/** Delete a composite font.
	 *	@param ws IN The workspace that contains the composite font to be deleted.
	 * 	@param compFontUIDToDelete IN The UID for the composite font that should be deleted. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 * 	@see kDeleteCompositeFontCmdBoss
	 */
	ErrorCode DeleteCompFont(IWorkspace* ws, const UID& compFontUIDToDelete);
	
	/** Inspect a composite font.
	 *	@param ws IN The workspace that contains the composite font to be inspected.
	 * 	@param compFontUIDToInspect IN The UID for the composite font that is to be inspected.
	 * 	@param data OUT The composite font data for the given UID.
	 * 	@return kSuccess on success, kFailure otherwise.
	 *	@see ICompositeFont
	 * 	@see ICompFontDataSettings
	 */
	ErrorCode InspectCompFont(IWorkspace* ws, 
							  const UID& compFontUIDToInspect,
							  SnpCompositeFontData& data);
	
	/** Sets the composite font data structure with sensible defaults. 
	 * 	Call this method before calling the CreateCompFont() method. 
	 * 
	 * 	NOTE: You can modify the contents to suite your needs. 
	 * 	
	 * 	@param ws IN The workspace on which the composite font will be created.  
	 * 		Either kWorkspaceBoss or kDocWorkspaceBoss. 
	 * 	@param doc IN The to correlate with the composite font.  
	 * 		This is optional. 
	 * 	@param name IN The name of the new composite font.
	 * 	@param baseUID IN The UID of the composite font on which you want to 
	 * 		base the new one. If this is NOT kInvalidUID, that means you want
	 * 		to make a new composite font based on a specific existing composite font. 
	 * 		In that case, all of the composite font data settings will be
	 * 		inherited.  Also, any added character classes will simply be 
	 * 		added on to the inherited character classes from the baseUID font.
	 * 		If you set this to kInvalidUID, the new composite font will 
	 * 		be based on the default composite font in the workspace, with
	 * 		additional characteristics that you specify in the SnpCompositeFontData
	 * 		structure.
	 * 	@param data OUT SnpCompositeFontData struct. This method fills out the structure.
	 */
	void SetCompositeFontData(IWorkspace* ws, 
							  IDocument* doc, 
							  const PMString& name, 
							  const UID& baseUID, 
							  SnpCompositeFontData& data);


	/** Creates a CMap (character map) for the new composite font.  
	 * 	Used by CreateCompFont.
	 * 	@param ws IN The workspace on which the composite font is located.  
	 * 		Either kWorkspaceBoss or kDocWorkspaceBoss. 
	 * 	@param newCompFontUID IN The UID of the new composite font. 
	 * 	@return kSuccess on success, kFailure otherwise. 
	 * 	@see kCreateFontCMapCmdBoss
	 */
	ErrorCode DoCreateFontCMap(IWorkspace* ws, 
							   const UID& newCompFontUID);

	/** Forces the font subsystem to do an update so that the new 
	 * 	composite font is recognized. 
	 * 	@return kSuccess on success, kFailure otherwise.
	 *	@see IFontMgr
	 */
	ErrorCode DoForceCompFontUpdate(void);

	/** Reports the composite font data to SNIPLOG.
	 * 	@param db IN The database that contains the composite font.
	 * 		This is used to get other fonts interfaces in the 
	 * 		SnpCompositeFontData structure.
	 * 	@param data IN The composite font data to report.
	 */
	void ReportCompFontData(IDataBase* db, const SnpCompositeFontData& data);

	/** Gets the names of the composite fonts.
	 * 	@param compFontNameTable IN The IStyleNameTable interface for 
	 * 		composite fonts on a specific workspace. 
	 * 	@return A list of composite fonts.
	 */
	K2Vector<PMString> GetCompFontNames(IStyleNameTable* compFontNameTable);


};

/* CreateCompFont
*/
ErrorCode SnpPerformCompFont::CreateCompFont(IWorkspace* ws,
											 const SnpCompositeFontData& data,
											 UID& newCompFontUIDOut)
{
	ErrorCode status = kFailure;

	const PMString seqName("SnpPerformCompFont::CreateCompFont", PMString::kEncodingASCII);
	// start a new command sequence
	CmdUtils::SequenceContext cmdSequence(&seqName);

	do
	{
		if (ws == nil ||
			data.fName.empty())
		{
			ASSERT_FAIL("Preconditions not met - existing CreateCompFont()"); break;
		}
		IDataBase* db = ::GetDataBase(ws);
		if (db == nil) 
		{
			ASSERT_FAIL("could not get database for workspace!"); break;
		}


		// STEP 1: Create the new composite font.
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kNewCompositeFontCmdBoss));
		if(cmd == nil)
		{
			ASSERT(cmd); 
			break;
		}
		// store the workspace on the item list
		cmd->SetItemList(UIDList(ws));

		// get the ICompositeFont interface for the command
		InterfacePtr<ICompositeFont> compositeFont(cmd, UseDefaultIID());
		if (compositeFont == nil) 
		{
			ASSERT(compositeFont);
			break;
		}

		// required settings for ICompositeFont
		compositeFont->SetName(data.fName);
		compositeFont->SetBasedOn(data.fBasedOn);
#ifdef DEBUG
		// try to get the basedOn composite font 
		// - just to make sure it IS a composite font
		if (data.fBasedOn != kInvalidUID)
		{
			InterfacePtr<ICompositeFont> oldCompositeFont(db, data.fBasedOn, UseDefaultIID());
			if (oldCompositeFont == nil) 
			{ 
				ASSERT_FAIL("the UID passed in for fBasedOn is NOT a valid composite font!"); 
				break; 
			}
		}
#endif
        
		// optional settings for ICompositeFont
        if (data.fDocument != nil) 
		{
			compositeFont->SetDocument(data.fDocument);
		}
/*
		// These ICompositeFont::Set***() methods are setup internally 
		// in the command. These are intentionally left here for reference. 
		if (data.fNameStyle.empty() == kFalse) 
		{
			compositeFont->SetNameStyle(data.fNameStyle);
		}
		if (data.fPostScriptName.empty() == kFalse) 
		{
			compositeFont->SetPostScriptName(data.fPostScriptName);
		}
		if (data.fCMapFileName.empty() == kFalse)
		{
			compositeFont->SetCMapFileName(data.fCMapFileName);
		}
		if (data.fIsLocked != compositeFont->IsLocked())
		{
			compositeFont->SetLocked(data.fIsLocked);
		}
		if (data.fFontMatrixAdjustment != compositeFont->GetFontMatrixAdjustment())
		{
			compositeFont->SetFontMatrixAdjustment(data.fFontMatrixAdjustment);
		}
*/

		// process the command		
		status = CmdUtils::ProcessCommand(cmd); 
		if (status != kSuccess) 
		{
			ASSERT_FAIL("NewCompositeFontCmd failed!");
			break;
		}

		// Get the UID of the composite font just created.
		// NOTE: the new UID is not returned via the command's item list, so we have to 
		// go find it.  It *should* be the last on the composite font list.
		InterfacePtr<IStyleNameTable> compFontList(ws, IID_ICOMPOSITEFONTLIST);
		if (compFontList == nil) 
		{
			ASSERT(compFontList); 
			status = kFailure;
			break;
		}
        int32 numCompFonts = compFontList->GetNumStyles();
		newCompFontUIDOut = compFontList->GetNthStyle(numCompFonts - 1);
		
		if (newCompFontUIDOut == kInvalidUID) 
		{
			ASSERT_FAIL("kInvalidUID returned!");
			status = kFailure;
			break;
		}


		// STEP 2: iteratively set the ICompFontDataSettings if there is data
		int32 numNewCharClasses = data.fCharClasses.size();
		if (numNewCharClasses > 0)
		{	
			// NOTE: The character classes that get added later have priority.
			for (int32 i = 0 ; i < numNewCharClasses ; ++i) 
			{
				// add a composite font class (New command in 3.0!)
				// This creates and adds the the SnpCompFontDataSettings to the list.
				InterfacePtr<ICommand> addCompFontClassCmd(CmdUtils::CreateCommand(kAddCompFontClassCmdBoss));
				if (addCompFontClassCmd == nil) 
				{ 
					ASSERT(addCompFontClassCmd); 
					status = kFailure;
					break; // out of for-loop
				}

				// set the workspace into the item list 
				// for the command target
				addCompFontClassCmd->SetItemList(UIDList(ws));

				// get the useExistingCompFont flag
				InterfacePtr<IBoolData> useExistingCompFontFlag(addCompFontClassCmd, UseDefaultIID());
				if (useExistingCompFontFlag == nil) 
				{ 
					ASSERT(useExistingCompFontFlag); 
					status = kFailure;
					break; // out of for-loop
				}
				else
				{
					// Setting this to true means to use the composite font 
					// in the IUIDData interface of this command
					// The UID is set below.
					useExistingCompFontFlag->Set(kTrue);
				}

				// set the composite font UID
				InterfacePtr<IUIDData> useExistingCompFontUID(addCompFontClassCmd, UseDefaultIID());
				if (useExistingCompFontUID == nil) 
				{ 
					ASSERT(useExistingCompFontUID); 
					status = kFailure;
					break; // out of for-loop
				}
				else
				{
					useExistingCompFontUID->Set(UIDRef(db, newCompFontUIDOut));
				}

				// set the new composite font name 
				// - this isn't needed, since we already have created a new composite font
                InterfacePtr<IStringData> newCompFontName(addCompFontClassCmd, UseDefaultIID());
				if (newCompFontName == nil) 
				{ 
					ASSERT(newCompFontName); 
					status = kFailure;
					break; // out of for-loop
				}
				else
				{
					// Set the name only if you need to create a new composite font.
					// (By setting the IBoolData to kFalse)
					// If you set IBoolData above to kTrue, this is data interface 
					// is ignored.
					newCompFontName->Set(PMString(""));
				}

				// set the character class data
				InterfacePtr<ICompFontDataSettings> compFontData(addCompFontClassCmd, UseDefaultIID());
				if (compFontData == nil) 
				{ 
					ASSERT(compFontData); 
					status = kFailure;
					break; // out of for-loop
				}
				else
				{
					SnpCompFontDataSettings settings = data.fCharClasses[i];
					if (settings.fIsDefault) 
					{
						compFontData->SetDefault();
					}
					compFontData->SetName(settings.fName);
					compFontData->SetFontUID(settings.fFontUID);
					compFontData->SetFontStyle(settings.fFontStyle);
					compFontData->SetSizeValue(settings.fSizeValue);
					compFontData->SetBaselineValue(settings.fBaselineValue);
					compFontData->SetHScaleValue(settings.fHScaleValue);
					compFontData->SetVScaleValue(settings.fVScaleValue);
					compFontData->SetLocked(settings.fIsLocked);
					compFontData->SetCharRanges(settings.fRanges);
				}

				status = CmdUtils::ProcessCommand(addCompFontClassCmd);
				if (status != kSuccess) 
				{
					ASSERT_FAIL(FORMAT_ARGS("AddCompFontClassCmd failed on iteration %d!", i));
					status = kFailure;
					break; // out of for-loop
				}

			} // end - for (int32 i = 0 ; i < numNewCharClasses ; ++i) 
			
		} // end - if (numNewCharClasses > 0)

		// check if we had an error in the if statement
		if (status != kSuccess) 
		{
			break; 
		}
		
		// the following are necessary post-processing operations 
		// after creating a composite font. 
		
		// STEP 3: create the CMap
		status = this->DoCreateFontCMap(ws, newCompFontUIDOut);
		if (status != kSuccess) 
		{
			ASSERT_FAIL("Error from DoCreateFontCMap!"); 
			break;
		}

		// STEP 4: force an update for the character panel
		status = this->DoForceCompFontUpdate();
		if (status != kSuccess) 
		{
			ASSERT_FAIL("Error from DoForceCompFontUpdate!"); 
			break;
		}

	} while (false);

	if (status != kSuccess) 
	{
		// there was an error, so return a bad UID
		newCompFontUIDOut = kInvalidUID;
		ErrorUtils::PMSetGlobalErrorCode(status);
	}

	return status;
}

/* DeleteCompFont
*/
ErrorCode SnpPerformCompFont::DeleteCompFont(IWorkspace* ws, 
											 const UID& compFontUIDToDelete)
{
	ErrorCode status = kFailure;
	do 
	{
		if (ws == nil ||
			compFontUIDToDelete == kInvalidUID) 
		{
			ASSERT_FAIL("One or more input conditions are not met (DeleteCompFont()) - exiting");
			break;
		}

		IDataBase* db = ::GetDataBase(ws);
		// create the delete composite font command
		InterfacePtr<ICommand> cmd(CmdUtils::CreateCommand(kDeleteCompositeFontCmdBoss));
		// set the item list (workspace)
		cmd->SetItemList(UIDList(ws));
		// set the UID to delete
		InterfacePtr<IUIDData> fontUIDData(cmd, UseDefaultIID());
		fontUIDData->Set(db, compFontUIDToDelete) ;

		// process the command
		status = CmdUtils::ProcessCommand(cmd);
        ASSERT(status == kSuccess);

	} while (false);
	return status;
}


ErrorCode SnpPerformCompFont::InspectCompFont(IWorkspace* ws, 
											  const UID& compFontUIDToInspect,
											  SnpCompositeFontData& data)
{
	ErrorCode status = kFailure;
	do
	{
		if (ws == nil ||
			compFontUIDToInspect == kInvalidUID) 
		{
			ASSERT_FAIL("One or more input conditions are not met (InspectCompFont()) - exiting");
			break;
		}

		IDataBase* db = ::GetDataBase(ws);
		if (db == nil)
		{ 
			ASSERT(db);
			break;
		}

		// query the composite font from the UIDRef
		InterfacePtr<ICompositeFont> compFont(db, compFontUIDToInspect, UseDefaultIID());
		if (compFont == nil) 
		{ 
			ASSERT(compFont); 
			break; 
		}

		// unravel all of the composite font data
		data.fNameStyle = compFont->GetNameStyle();
		data.fBasedOn = compFont->GetBasedOn();
		data.fFontFamilyName = compFont->GetFontFamilyName();
		data.fNativeFontFamilyName = compFont->GetNativeFontFamilyName();
		data.fPostScriptName = compFont->GetPostScriptName();
		data.fCMapFileName = compFont->GetCMapFileName();
		data.fIsLocked = compFont->IsLocked();
		data.fFontMatrixAdjustment = compFont->GetFontMatrixAdjustment();
		data.fDocument = compFont->GetDocument();
		
		SnpCompFontDataSettingList charClasses;
		charClasses.clear();
		int32 numCharClasses = compFont->GetCharClassLength();
		for (int32 i = 0 ; i < numCharClasses ; ++i) 
		{
			InterfacePtr<ICompFontDataSettings> compFontData(compFont->GetCharClass(i));
			if (compFontData == nil) 
			{ 
				ASSERT_FAIL(FORMAT_ARGS("Can't get compFontData[%d]", i)); 
				break; /* out of for loop */ 
			}
			SnpCompFontDataSettings s;
			
			s.fName = compFontData->GetName();
			s.fFontUID = compFontData->GetFontUID();
			s.fFontStyle = compFontData->GetFontStyle();
			s.fSizeValue = compFontData->GetSizeValue();
			s.fBaselineValue = compFontData->GetBaselineValue();
			s.fHScaleValue = compFontData->GetHScaleValue();
			s.fVScaleValue = compFontData->GetVScaleValue();
			s.fIsLocked = compFontData->IsLocked();
			s.fRanges = compFontData->GetCharRanges();
			// add the SnpCompFontDataSettings to the K2Vector
			charClasses.push_back(s);
		}
		data.fCharClasses = charClasses;

		// now, go report the composite font data.
		this->ReportCompFontData(db, data);

		status = kSuccess;
	} while (false);
	return status;
    
}

/* SetCompositeFontData
	TODO: This is where you can customize your data a bit more...
*/
void SnpPerformCompFont::SetCompositeFontData(IWorkspace* ws, 
											  IDocument* document, 
											  const PMString& name, 
											  const UID& baseUID, 
											  SnpCompositeFontData& data)
{
	/* NOTE: This routine has been written simply to illustrate the kinds of 
		data and API use must use to set the composite font data. 
	*/
	// set various composite font settings
	data.fName = name;
	data.fBasedOn = baseUID;
	data.fDocument = document;
	data.fFontMatrixAdjustment = 0;
	data.fIsLocked = kFalse;
	data.fNameStyle = "";
	data.fPostScriptName = "";
	data.fCMapFileName = "";
	
	// check if this is running on the Japanese feature set
	bool16 isJapaneseFeatureSet = 
		(LocaleSetting::GetLocale().GetFeatureSetId() == kInDesignJapaneseFS) ? 
			kTrue : 
			kFalse;

	// create a new char class list
	SnpCompFontDataSettingList charClassList;
	charClassList.clear();

	// just create one for now - add more if needed
	SnpCompFontDataSettings charClass1;
	charClass1.fBaselineValue = 0;
	charClass1.fFontUID = kInvalidUID;
	charClass1.fFontStyle = "";
	
	if (ws) 
	{
		do {
			InterfacePtr<ITextAttributes> defaultTextAttributes(ws, UseDefaultIID());
			if (defaultTextAttributes == nil) 
			{
				ASSERT_FAIL("Can't find ITextAttributes on the workspace boss! Using blank defaults.");
				break; // out of do-while
			}
			InterfacePtr<ITextAttrUID> defaultFontUID((ITextAttrUID*)defaultTextAttributes->QueryByClassID(kTextAttrFontUIDBoss, ITextAttrUID::kDefaultIID));
			if (defaultFontUID == nil) 
			{
				ASSERT_FAIL("Can't find kTextAttrFontUIDBoss on the default text attributes! Using blank defaults.");
				break; // out of do-while
			}
			InterfacePtr<ITextAttrFont> defaultFontStyle((ITextAttrFont*)defaultTextAttributes->QueryByClassID(kTextAttrFontStyleBoss, ITextAttrFont::kDefaultIID));
			if (defaultFontStyle == nil) 
			{
				ASSERT_FAIL("Can't find kTextAttrFontStyleBoss on the default text attributes! Using blank defaults.");
				break; // out of do-while
			}

			// get the defaults
			charClass1.fFontUID = defaultFontUID->Get();
			charClass1.fFontStyle = defaultFontStyle->GetFontName();
		} while (false);
	}
	
	charClass1.fIsDefault = kFalse;
	charClass1.fIsLocked = kFalse;
	if (isJapaneseFeatureSet)
	{
		charClass1.fName = "HiraganaOnly";
    }
	else
	{
		charClass1.fName = "UpperCaseAlphabetOnly";
	}
	charClass1.fName.SetTranslatable(kFalse);
	charClass1.fSizeValue = 110.0; // 110%
	charClass1.fHScaleValue = 120; // 120%
	charClass1.fVScaleValue = 80; // 80%

	CharRangeCollection charRangeCollection;
	charRangeCollection.clear();
	
	// create a character range
	// Just do one range for now...specify as UNICODE
	CharacterRange charRange;
	UTF32TextChar firstChar;
	UTF32TextChar lastChar;
	UTF32TextChar destChar;

	if (isJapaneseFeatureSet)
	{
		// NOTE: 0x8280-0x82FC covers all of the hiragana characters
		firstChar = UTF32TextChar(0x3041); // ShiftJIS 0x829F 
		lastChar = UTF32TextChar(0x3093); // ShiftJIS 0x82F1
	}
	else
	{
		firstChar = UTF32TextChar('A');
		lastChar = UTF32TextChar('Z');
	}
	// no need to map (mapping is used primarily for 1-byte gaiji), 
	// so set the mapping destination to be the same as the first char.
	destChar = firstChar;
	// set the range
	charRange.SetRange(firstChar, lastChar, destChar);
	// add the character range to the list
	charRangeCollection.push_back(charRange);
	charClass1.fRanges = charRangeCollection;

	// if you want more character ranges, add them here...


	// add the character class to the list
	charClassList.push_back(charClass1);
	data.fCharClasses = charClassList;
}

/* DoCreateFontCMap
*/
ErrorCode SnpPerformCompFont::DoCreateFontCMap(IWorkspace* ws, const UID& newCompFontUID)
{
	ErrorCode status = kFailure;
	do {
		if ((ws == nil) || (newCompFontUID == kInvalidUID)) 
		{
			ASSERT_FAIL("Preconditions are not met!"); break;
		}

		InterfacePtr<ICommand> createCMapCmd(CmdUtils::CreateCommand(kCreateFontCMapCmdBoss));
		if(createCMapCmd == nil)
		{
			ASSERT(createCMapCmd); break;
		}
	
		// set the workspace UID into the item list
		createCMapCmd->SetItemList(UIDList(ws));

		// get the composite font list from the workspace
		InterfacePtr<IStyleNameTable> compositeFontList(ws, IID_ICOMPOSITEFONTLIST);
		if (compositeFontList == nil)
		{
			ASSERT(compositeFontList);
		}

		// set the font UID of the new composite font
		IDataBase* db = ::GetDataBase(compositeFontList);
        InterfacePtr<IUIDData> uidData(createCMapCmd, UseDefaultIID());
		if (uidData == nil) 
		{
			ASSERT(uidData); break;
		}
		uidData->Set(db, newCompFontUID);

		// copy details of the composite font to the command's ICompositeFont interface
		InterfacePtr<ICompositeFont> compFont(createCMapCmd, UseDefaultIID());
		InterfacePtr<ICompositeFont> newCompFont(db, newCompFontUID, UseDefaultIID());
		if (compFont == nil || newCompFont == nil) 
		{
			ASSERT_FAIL("Could not get ICompositeFont"); break;
		}
        compFont->SetName(newCompFont->GetNativeFontFamilyName());
		compFont->SetBasedOn(newCompFont->GetBasedOn());
		compFont->SetDocument(newCompFont->GetDocument());
		
		// process the command
		status = CmdUtils::ProcessCommand(createCMapCmd);	
		ASSERT_MSG(status == kSuccess, "kCreateFontCMapCmdBoss failed!");
	
	} while (false);
	return status;
}

/* DoForceCompFontUpdate
*/
ErrorCode SnpPerformCompFont::DoForceCompFontUpdate(void)
{
	ErrorCode status = kFailure;

	do
	{
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) 
		{
			ASSERT(fontMgr); break;
		}

		// specify a new seed value of the font system that indicates a font update has occurred.
		int32 newSeed;
		int32 nowTicks, startTicks = SystemUtils::TickCount();
		int32 oldSeed = fontMgr->CurrentFontSystemSeed(kFalse);
		
		do {
	    	// it takes at least 3 calls to CurrentFontSystemSeed to get a new seed for
			// our local CompositeFont folder. This is because call one searches the
			// CompositeFont folder. Call 2 searches the local font folder. Call 3 takes
			// the checksum of CompositeFont and Fonts folder and compares is against the
			// old value. However if we have even more folders in local fonts folder we
			// can need even more calls to CurrentFontSystemSeed.
			newSeed = fontMgr->CurrentFontSystemSeed(kTrue);
            nowTicks = SystemUtils::TickCount();
		} while ( (oldSeed == newSeed) && (nowTicks - startTicks < 200) );			
		
		// using a specific IID, not default
		InterfacePtr<IIdleTask> fontUpdateThread(GetExecutionContextSession(), IID_IFONTTHREAD);
		if (fontUpdateThread == nil)
		{
			ASSERT(fontUpdateThread); break;
		}
        fontUpdateThread->UninstallTask();
		fontUpdateThread->InstallTask(0);
		
		status = kSuccess;
	} while (false);
	return status;
}

/* ReportCompFontData
*/
void SnpPerformCompFont::ReportCompFontData(IDataBase* db, const SnpCompositeFontData& data)
{
	do {
		if (db == nil) 
		{
			ASSERT_FAIL("db is nil!");
			break;
		}

		// unravel all of the composite font data
		SNIPLOG("=== Composite font data ===");
	
		const PMString nameStyle = data.fNameStyle;
		SNIPLOG(" nameStyle: \"%s\"", nameStyle.GetPlatformString().c_str());
	
		const UID basedOn = data.fBasedOn;
		if (basedOn == kInvalidUID)
		{
			SNIPLOG(" basedOn: <none>");
		}
		else
		{
			InterfacePtr<ICompositeFont> basedOnCompFont(db, basedOn, UseDefaultIID());
			SNIPLOG(" basedOn: UID 0x%X (%s)", basedOn.Get(), 
					((basedOnCompFont != nil) ? basedOnCompFont->GetNameStyle().GetPlatformString().c_str() : "<unknown>"));
		}
		
		const PMString fontFamilyName = data.fFontFamilyName;
		SNIPLOG(" fontFamilyName: \"%s\"", fontFamilyName.GetPlatformString().c_str());
		
		const PMString nativeFontFamilyName = data.fNativeFontFamilyName;
		SNIPLOG(" nativeFontFamilyName: \"%s\"", nativeFontFamilyName.GetPlatformString().c_str());
		
		const PMString postScriptName = data.fPostScriptName;
		SNIPLOG(" postScriptName: \"%s\"", postScriptName.GetPlatformString().c_str());
		
		const PMString cMapFileName = data.fCMapFileName;
		SNIPLOG(" cMapFileName: \"%s\"", cMapFileName.GetPlatformString().c_str());
		
		const bool16 isLocked = data.fIsLocked;
		SNIPLOG(" isLocked: %s", (isLocked ? "YES" : "No"));
		
		const uint16 fontMatrixAdjustment = data.fFontMatrixAdjustment;
		SNIPLOG(" fontMatrixAdj: %d", fontMatrixAdjustment);
		
		const IDocument* doc = data.fDocument;
		if (doc == nil) 
		{
			SNIPLOG(" document UID: <none>");
		}
		else
		{
			const UID docUID = ::GetUID(doc);
			SNIPLOG(" document UID: 0x%X", docUID.Get());
		}
		
		int32 numCharClasses = data.fCharClasses.size();
		for (int32 i = 0 ; i < numCharClasses ; ++i) 
		{
			SnpCompFontDataSettings s = data.fCharClasses[i];
						
			SNIPLOG(" ICompFontDataSettings[%d]:", i);
			
			const PMString cfdName = s.fName;
			SNIPLOG("  *Name*: \"%s\"", cfdName.GetPlatformString().c_str());
			
			const UID cfdUID = s.fFontUID;
			if (cfdUID == kInvalidUID) 
			{
				SNIPLOG("  FontUID: <none>");
			}
			else
			{
				InterfacePtr<IFontFamily> font(db, cfdUID, UseDefaultIID());
				ASSERT(font);
				SNIPLOG("  FontUID: 0x%X (%s)", 
						cfdUID.Get(), 
						((font != nil) ? font->GetFamilyNameNative().GetPlatformString().c_str() : "<unknown>"));
			}
			
			const PMString cfdFontStyle = s.fFontStyle;
			SNIPLOG("  FontStyle: \"%s\"", cfdFontStyle.GetPlatformString().c_str());
			
			const PMReal cfdSizeValue = s.fSizeValue;
			SNIPLOG("  SizeValue: %f %%", ::ToDouble(cfdSizeValue));
			
			const PMReal cfdBaselineValue = s.fBaselineValue;
			SNIPLOG("  BaselineValue: %f %%", ::ToDouble(cfdBaselineValue));
			
			const PMReal cfdHScaleValue = s.fHScaleValue;
			SNIPLOG("  HScaleValue: %f %%", ::ToDouble(cfdHScaleValue));
			
			const PMReal cfdVScaleValue = s.fVScaleValue;
			SNIPLOG("  VScaleValue: %f %%", ::ToDouble(cfdVScaleValue));
			
			const bool16 cfdIsLocked = s.fIsLocked;
			SNIPLOG("  isLocked: %s", (cfdIsLocked ? "YES" : "No"));
			
			CharRangeCollection charRangeList = s.fRanges;
			int32 numCharRanges = charRangeList.size();
			for (int32 j = 0 ; j < numCharRanges ; ++j) 
			{
				CharacterRange charRange = charRangeList[j];
				UTF32TextChar first(charRange.GetFirst());
				UTF32TextChar last(charRange.GetLast());
				UTF32TextChar dest(charRange.GetDest());
				// NOTE: These are in UTF32TextChars (UNICODE)
				SNIPLOG("   CharRange[%d]: (first,last,dest)=(0x%X, 0x%X, 0x%X)", 
						j, first.GetValue(), last.GetValue(), dest.GetValue());
			}
		}
	} while (false);
}

/* GetCompFontNames
*/
K2Vector<PMString> SnpPerformCompFont::GetCompFontNames(IStyleNameTable* compFontNameTable)
{
	K2Vector<PMString> fontNames;
	fontNames.clear();
	do 
	{
		if (compFontNameTable == nil) 
		{
			ASSERT_FAIL("compoFontNameTable is nil!  I can't get font names.");
			break;
		}
		IDataBase* db = ::GetDataBase(compFontNameTable);
		if (db == nil) 
		{
			ASSERT_FAIL("db is nil!");
			break;
		}
		int32 numStyles = compFontNameTable->GetNumStyles();
		
		// iterate through each composite font in the list
		for (int32 i = 0 ; i < numStyles ; i++) 
		{
			UID compFontUID = compFontNameTable->GetNthStyle(i);
			InterfacePtr<ICompositeFont> compFont(db, compFontUID, UseDefaultIID());
			if (compFont != nil) 
			{
				const PMString compFontName = compFont->GetNativeFontFamilyName();
				if (compFontName.empty()) 
				{
					fontNames.push_back(PMString("[No composite font]"));
				}
				else
				{
					fontNames.push_back(compFontName);
				}
			}
			else
			{
				PMString badCompFont("<invalid composite font ");
				badCompFont.AppendNumber(i);
				badCompFont.Append(">");
				fontNames.push_back(badCompFont);
			}
		}
					  
	} while (false);
	return fontNames;
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------

class _SnpRunnerPerformCompFont : public SnpRunnable
{

public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerPerformCompFont(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerPerformCompFont(void);

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
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunWorkspaceContext;}
};

/* Constructor.
*/
_SnpRunnerPerformCompFont::_SnpRunnerPerformCompFont() : SnpRunnable("PerformCompFont")
{
	this->SetDescription("Creates, Deletes, and Inspects a composite font");
	this->SetPreconditions("Active workspace with a composite font list");
	this->SetCategories("sdk_snippet, sdk_cjk");
}

/* Destructor.
*/
_SnpRunnerPerformCompFont::~_SnpRunnerPerformCompFont(void)
{
	// do nothing.
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformCompFont::CanRun(ISnpRunnableContext* runnableContext)
{
	bool16 result = kFalse;
	do {
		if (runnableContext == nil) 
		{
			// this would be bad!
			break; 
		}
		// get the active workspace.
		IWorkspace* ws = runnableContext->GetActiveContext()->GetContextWorkspace();
		if (ws == nil) 
		{
			break;
		}
		// get the composite font list from the workspace. 
        InterfacePtr<IStyleNameTable> compositeFontList(ws, IID_ICOMPOSITEFONTLIST);
		if (compositeFontList == nil) 
		{
			break;
		}

		// if we got here, we can run the snippet.
		result = kTrue;
	} while(false);
	return result;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformCompFont::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;
	// fontNumber increments as you make more fonts
    static int32 fontNumber = 0;

	do {
		SnpPerformCompFont instance;

		// -------------------------------------------------------
		// check preconditions
		// -------------------------------------------------------
		if (runnableContext == nil) 
		{
			// this would be bad!
			ASSERT_FAIL("runnableContext is nil!");
			break; 
		}
		// get the active workspace.
		IWorkspace* ws = runnableContext->GetActiveContext()->GetContextWorkspace();
		if (ws == nil) 
		{
			ASSERT_FAIL("There is no active workspace!");
			break;
		}
		// get the composite font list from the workspace. 
        InterfacePtr<IStyleNameTable> compositeFontList(ws, IID_ICOMPOSITEFONTLIST);
		if (compositeFontList == nil) 
		{
			ASSERT_FAIL("There is no IStyleNameTable/IID_ICOMPFONTLIST interface!");
			break;
		}

		// get document, if available.
		IDocument* document = runnableContext->GetActiveContext()->GetContextDocument();
		
		// -------------------------------------------------------
		// get user choices
		// -------------------------------------------------------
		Utils<ISnipRunParameterUtils> parameterUtils;
		
		// what do you want to do?
		// inspect, create, delete
		enum { kCompFontInspect, kCompFontCreate, kCompFontDelete };
		K2Vector<PMString> operations;
		operations.clear();
		operations.push_back("inspect a composite font"); // kInspect (default)
		operations.push_back("create new composite font"); // kCreate
		operations.push_back("delete a composite font"); // kDelete
		int32 operation = parameterUtils->GetChoice("What operation do you want to perform?", operations, kCompFontInspect);
		if (parameterUtils->WasDialogCancelled()) 
		{
			// user cancelled! get out of do-while loop
			break;
		}
		
		// get the current list of composite fonts on the workspace
		K2Vector<PMString> currentCompFonts = instance.GetCompFontNames(compositeFontList);
		// get the number of "actual" composite fonts on the workspace.
		int32 numAvailableFonts = currentCompFonts.size();
		
		SnpCompositeFontData data;

		switch (operation) 
		{
		default:
			{
				SNIPLOG("Invalid option - using default.");
				// no break, fall through.
			}
		case kCompFontInspect:
			{
				// get the choice of composite font to base 
				int32 choiceToInspect = parameterUtils->GetChoice("Which composite font do you want to inspect?", currentCompFonts, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
				UID compFontToInspect = compositeFontList->GetNthStyle(choiceToInspect);
				status = instance.InspectCompFont(ws, compFontToInspect, data);
			}
			break;
		case kCompFontCreate:
			{
				PMString defaultFontName("MyNewCompFont", PMString::kEncodingASCII);
				defaultFontName.AppendNumber(fontNumber++);
				PMString fontName = parameterUtils->GetPMString("Specify the name of the new composite font.", defaultFontName);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}
		
				// set up the basis for the new composite font.
				// kInvalidUID will make a completely new one. 
				UID basedOnUID = kInvalidUID;
				// specify default choice
				int32 defaultCompFontChoice = 0;
				// get the choice of composite font to base 
				int32 choiceToCreate = parameterUtils->GetChoice("Which composite font do you want to use as a basis?", currentCompFonts, defaultCompFontChoice);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! 
					break; // get out of switch
				}

				// Get the UID of the composite font on which to base the new one.
				// NOTE: Even if you programmatically set this to kInvalidUID,
				// 		the new composite font will be created based on the default one.
				basedOnUID = compositeFontList->GetNthStyle(choiceToCreate);
				
				// -------------------------------------------------------
				// now we are ready to create the composite font!!!
				// -------------------------------------------------------
				UID newCompFontUID;
		
				// set various comppsite font settings
				instance.SetCompositeFontData(ws, document, fontName, basedOnUID, data);
		
				// call the commands to create the composite font
				// the newly created UID is in 'newCompFontUID'
				status = instance.CreateCompFont(ws, data, newCompFontUID);
				if (status != kSuccess) 
				{
					ASSERT_FAIL("Error from CreateCompFont!"); 
					break; // get out of switch
				}
		
				SNIPLOG("New composite font %s (UID 0x%X) successfully created.", 
						fontName.GetPlatformString().c_str(), newCompFontUID.Get());
			}
			break;

		case kCompFontDelete:
			{
				// get the choice of composite font to base 
				int32 choiceToDelete = parameterUtils->GetChoice("Which composite font do you want to delete?", currentCompFonts, 0);
				if (parameterUtils->WasDialogCancelled()) 
				{
					// user cancelled! get out of switch
					break;
				}
				UID compFontToDelete = compositeFontList->GetNthStyle(choiceToDelete);

				// check if this is the "root" style 
				if (compFontToDelete == compositeFontList->GetRootStyleUID()) 
				{
					SNIPLOG("The selected composite font is \"root\" style and should not be deleted. Cancelling.");
					break; // get out of switch
				}
				status = instance.DeleteCompFont(ws, compFontToDelete);
			}
			break;
		}
		
	} while(false);
	return (status);

}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerPerformCompFont instance_SnpRunnerPerformCompFont;
DEFINE_SNIPPET(_SnpRunnerPerformCompFont) 	

// End, SnpPerformCompFont.cpp

