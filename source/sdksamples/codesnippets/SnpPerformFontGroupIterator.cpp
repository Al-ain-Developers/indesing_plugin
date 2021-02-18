//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpPerformFontGroupIterator.cpp $
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
#include "ISession.h"
#include "IFontMgr.h"
#include "IPMFont.h"
#include "Utils.h"
#include "ITextUtils.h"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	Sample code snippet that shows how to implement a FontGroupIteratorCallBack 
	(see IFontMgr.h) to iterate all fonts.

	@ingroup sdk_snippet
	@ingroup sdk_text
*/
class SnpPerformFontGroupIterator : public FontGroupIteratorCallBack
{
public:

	/** Constructor.
		@param nativeNames kTrue if native names to be reported, kFalse otherwise. 
		@param verbose kTrue if every callback is to be logged, kFalse otherwise.
	 */
	SnpPerformFontGroupIterator(bool16 nativeNames = kFalse, bool16 verbose = kFalse);

	/**
		Called at the start of the iteration, first call	
	*/
    virtual void    OnStart();

	/**
		Called at the end of the iteration, last call	
	*/
    virtual void    OnEnd();

	/**
		Called before the fonts that use locale writing script are being collected.	
	*/
    virtual void    OnLocaleScriptFontsStart();

	/**
		Called after the fonts that use locale writing script are being collected.	
	*/
    virtual void    OnLocaleScriptFontsEnd();

	/**
		Called before multiple master fonts are being collected.	
	*/
	virtual void    OnMMFontsStart();

	/**
		Called after multiple master fonts are being collected.	
	*/
    virtual void    OnMMFontsEnd();

	/**
		Called for each multiple master instance
	
		@param	pFont		multiple master font
		@param	sourceAxes	axes
		@param	numAxes		number of axes
	*/
    virtual void    OnMMAxes( IPMFont* pFont, const Fixed* sourceAxes, int32 numAxes );

	/**
		Called for each item
	
		@param	pFont		font to iterate
		@param	fontGroup	font group the font belongs to
		@param	displayFamilyName	name for family as it shows in font menu
		@param	displayStyleName	name for font style as it shows in font menu
	*/
    virtual void    OnFont( IPMFont* pFont, IFontGroup* fontGroup, const PMString& displayFamilyName, const PMString& displayStyleName );

	/**
		Called at the start of a font group
	
		@param	fontGroup	font group we are starting to iterate
	*/
    virtual void    OnFontGroupStart( IFontGroup* fontGroup );

	/**
		Called at the end of a font group
	
		@param	fontGroup	font group we are done iterating
	*/
    virtual void    OnFontGroupEnd( IFontGroup* fontGroup );

	/**
		Called on script change
	
	*/
    virtual void    OnFontsAddedForLastScript();

	/** Called by FontGroupIterator; drives the iterator to skip styles
		@return	kTrue skip styles. kFalse iterate styles. 
	 */
    virtual bool16  RunFamilyOnly() const;

	/**	Determines the format of names returned in OnFont
		@return	Names flag value. See enum ITextUtils::DisplayNamesFlag.
	 */
	virtual int16  GetNamesFlag () const;

	/**	Called by FontGroupIterator; drives the iterator to flatten MM Fonts.
		@return  kTrue iterate MM axes. kFalse only show Regular Style for MM fonts.
	 */
    virtual bool16  RunMMFonts() const;

	/**	Called by FontGroupIterator; drives the iterator to skip a font entirely.
		@param *font	font to choose to skip
		@return bool16	kTrue skip this font. kFalse iterate this font.
	 */
    virtual bool16  SkipThisFont( IPMFont* font ) const;

	/**
		Called by FontGroupIterator. drives the iterator to flatten the menu to "Times Bold".
	
		@return	MissingFonts
	*/
    virtual MissingFonts    RunMissingFonts() const;

	/**
		Called before missing fonts are being collected
	
	*/
    virtual void            OnMissingFontsStart();

	/**
		Called after missing fonts are being collected.
	
	*/
    virtual void            OnMissingFontsEnd();
   
	/**
		Called by FontGroupIterator for missing fonts, usually front doc's IUsedFontList.
	
		@return	IUsedFontList*
	*/
	virtual IUsedFontList* QueryUsedFontList();

	/**
		Called for each missing font
	
		@param	fontFamily
		@param	faceIndex
		@param	displayFamilyName
		@param	displayStyleName
	*/
    virtual void  OnMissingFont( IFontFamily* fontFamily, int32 faceIndex, const PMString& displayFamilyName, const PMString& displayStyleName );

	/**
		Called by FontGroupIterator. drives the iterator to use the returned UIDList instead of the FontMgr.
	
		@return	UIDList*
	*/
    virtual const UIDList* UseFontUIDList() const;

	/**
		Called by FontGroupIterator. drives the iterator to allow duplicate font names.
	
		@return	bool16
	*/
    virtual bool16          RunDuplicateFonts() const;

private:
	bool16 fNativeNames;
	bool16 fVerbose;
	K2Vector<PMString> fontNames;
};

/*
*/
SnpPerformFontGroupIterator::SnpPerformFontGroupIterator(bool16 nativeNames, bool16 verbose) 
: fNativeNames(nativeNames), fVerbose(verbose)
{
	InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
	if (fontMgr != nil) {
		if (fNativeNames == kFalse) {
			SNIPLOG("FamilyName, StyleName, FontName");
		}
		else {
			SNIPLOG("FamilyName, StyleName, FontName, FullName, FamilyNameNative, StyleNameNative, FullNameNative");
		}
		fontMgr->IterateFontGroups(this);
	}
	else {
		SNIPLOG("Can't find IFontMgr on GetExecutionContextSession(), eh?");
	}
}

/*
*/
void SnpPerformFontGroupIterator::OnFont(IPMFont* pFont, 
	IFontGroup* fontGroup, 
	const PMString& displayFamilyName, 
	const PMString& displayStyleName
)
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnFont");
	}

	PMString fullName;
	PMString fontName;
	PMString familyNameNative;
	PMString styleNameNative;
	PMString fullNameNative;
	if (pFont != nil) {
		pFont->AppendFullName(fullName);
		pFont->AppendFontName(fontName);
		pFont->AppendFamilyNameNative(familyNameNative);
		pFont->AppendStyleNameNative(styleNameNative);
		pFont->AppendFullNameNative(fullNameNative);
	}

	if (fNativeNames == kTrue) {
		SNIPLOG("%s, %s, %s, %s, %s, %s, %s",
			displayFamilyName.GetPlatformString().c_str(), // same as IPMFont::AppendFamilyName
			displayStyleName.GetPlatformString().c_str(), // same as IPMFont::AppendStyleName
			fontName.GetPlatformString().c_str(),
			fullName.GetPlatformString().c_str(),
			familyNameNative.GetPlatformString().c_str(),
			styleNameNative.GetPlatformString().c_str(),
			fullNameNative.GetPlatformString().c_str()
		);
	}
	else {
		SNIPLOG("%s, %s, %s",
			displayFamilyName.GetPlatformString().c_str(), // same as IPMFont::AppendFamilyName
			displayStyleName.GetPlatformString().c_str(), // same as IPMFont::AppendStyleName
			fontName.GetPlatformString().c_str()
		);
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnStart()
{ 
	if (fVerbose == kTrue) {
	 SNIPLOG(" OnStart");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnEnd()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnEnd");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnLocaleScriptFontsStart()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnLocaleScriptFontsStart");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnLocaleScriptFontsEnd()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnLocaleScriptFontsEnd");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnMMFontsStart()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMMFontsStart");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnMMFontsEnd()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMMFontsEnd");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnMMAxes( IPMFont* pFont, const Fixed* sourceAxes, int32 numAxes )
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMMAxes");
	}
}

/*
*/
void SnpPerformFontGroupIterator::OnFontGroupStart( IFontGroup* fontGroup )
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnFontGroupStart");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnFontGroupEnd( IFontGroup* fontGroup )
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnFontGroupEnd");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnFontsAddedForLastScript()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnFontsAddedForLastScript");
	}
} 

/*
*/
bool16 SnpPerformFontGroupIterator::RunFamilyOnly() const
{ 
	bool16 result = kFalse;
	if (fVerbose == kTrue) {
		SNIPLOG(" RunFamilyOnly=%d", result);
	}
	return result; 
}

int16  SnpPerformFontGroupIterator::GetNamesFlag () const            
{
	int16 result = ITextUtils::kCombineSingleStyleIntoFamilyName;
	if (fVerbose == kTrue) {
		result = ITextUtils::kSeparateFamilyAndStyleName;
		SNIPLOG(" GetNamesFlag=%d", result);
	}
	return result;
}

/*
*/
bool16 SnpPerformFontGroupIterator::RunMMFonts() const 
{ 
	bool16 result = kTrue;
	if (fVerbose == kTrue) {
		SNIPLOG(" RunMMFonts=%d", result);
	}
	return result; 
}

/*
*/
bool16 SnpPerformFontGroupIterator::SkipThisFont( IPMFont* font ) const 
{ 
	bool16 result = kFalse;
	if (fVerbose == kTrue) {
		SNIPLOG(" SkipThisFont=%d", result);
	}
	return result; 
}

/*
*/
FontGroupIteratorCallBack::MissingFonts SnpPerformFontGroupIterator::RunMissingFonts() const 
{ 
	MissingFonts result = kSkip;
	if (fVerbose == kTrue) {
		SNIPLOG(" RunMissingFonts=%d", result);
	}
	return kSkip; 
}

/*
*/
void SnpPerformFontGroupIterator::OnMissingFontsStart()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMissingFontsStart");
	}
} 

/*
*/
void SnpPerformFontGroupIterator::OnMissingFontsEnd()
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMissingFontsEnd");
	}
} 

/*
*/
IUsedFontList* SnpPerformFontGroupIterator::QueryUsedFontList() 
{
	IUsedFontList* result = nil;
	if (fVerbose == kTrue) {
		SNIPLOG(" QueryUsedFontList=0x%x", result);
	}
	return result; 
}

/*
*/
void SnpPerformFontGroupIterator::OnMissingFont( IFontFamily* fontFamily, int32 faceIndex, const PMString& displayFamilyName, const PMString& displayStyleName )
{
	if (fVerbose == kTrue) {
		SNIPLOG(" OnMissingFont");
	}
} 

/*
*/
const UIDList* SnpPerformFontGroupIterator::UseFontUIDList() const 
{ 
	UIDList* result = nil;
	if (fVerbose == kTrue) {
		SNIPLOG(" UseFontUIDList=0x%x", result);
	}
	return result; 
}

/*
*/
bool16 SnpPerformFontGroupIterator::RunDuplicateFonts() const 
{ 
	bool16 result = kFalse;
	if (fVerbose == kTrue) {
		SNIPLOG(" RunDuplicateFonts=%d", result);
	}
	return result; 
}


// --------------------------------- For SnippetRunner framework ---------------------------------------------------


class _SnpRunnerPerformFontGroupIterator : public SnpRunnable
{
public: 
	/** Constructor.
	*/
	_SnpRunnerPerformFontGroupIterator(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerPerformFontGroupIterator(void);

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
	virtual ISnipRunSuite::eSnpRunContextType GetContext(void){return ISnipRunSuite::kSnpRunNoContext;}
};


_SnpRunnerPerformFontGroupIterator::_SnpRunnerPerformFontGroupIterator(void) : SnpRunnable("PerformFontGroupIterator")
{
	this->SetDescription("Perform a FontGroupIteratorCallBack to display font information");
    this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerPerformFontGroupIterator::~_SnpRunnerPerformFontGroupIterator(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerPerformFontGroupIterator::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerPerformFontGroupIterator::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kFailure;

	do {
		// For testing purpose, we set nativeNames to kFalse, verbose to kFalse, meaning 
		// we don't log every callback. The output for each font would look like:
		// "FamilyName, StyleName, FontName" in the SnippetRunner log window.
		SnpPerformFontGroupIterator fontGroupIterator(kFalse, kFalse);
		status = kSuccess;

	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.

*/
static _SnpRunnerPerformFontGroupIterator instance_SnpRunnerPerformFontGroupIterator;
DEFINE_SNIPPET(_SnpRunnerPerformFontGroupIterator) 	


