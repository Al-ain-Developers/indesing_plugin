//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IEndnoteSettings.h $
//  
//  Owner: Susmita Singh
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 2017 Adobe 
//  All Rights Reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in 
//  accordance with the terms of the Adobe license agreement accompanying 
//  it. If you have received this file from a source other than Adobe, 
//  then your use, modification, or distribution of it requires the prior 
//  written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __IEndnoteSettings__
#define __IEndnoteSettings__

/** Minimum starting footnote number. */
#define kMinStartingFootnoteNumber		1

/** Maximum starting footnote number. */
#define kMaxStartingFootnoteNumber	100000

#ifndef __ODFRC__	// when used for core resource compilation, provide just the parameter range constants

#include "IPMUnknown.h"
#include "TextID.h"
#include "CTextEnum.h"
#include "ITextAttrStrokeType.h"
#include "IWorkspace.h"
#include "ISwatchList.h"
#include "IStyleNameTable.h"
#include "IEndnoteSettings.h"
#include "IStyleGroupManager.h"
#include "UIDRef.h"
#include "PMReal.h"
#include "WideString.h"

#include "ILayoutUIUtils.h"
#include "LocaleSetting.h"

#include "TextID.h"
#include "InstStrokeFillID.h"

enum EndnotePageScope {
	kAtEndOfStory = 0,     /** add page at end of story */
	kAtEndOfSection,       /** add page at end of section. */
	kAtEndOfDocument,      /** add page at end of document. */
	kAtEndOfBook,		   /** add page at end of book. */
};

/** This interface is used to set or retrieve the settings associated with endnotes.
@ingroup text_layout
*/
class IEndnoteSettings : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IENDNOTESETTINGS };

	/** The different ways to restart numbering of endnotes.
	*/
	typedef enum { kContinuous, kRestartEveryStory, kUnknown } RestartNumberingOptions;

	/** Different scopes for endnote placement
	*/
	typedef enum {kStory, kDocument} Scope;

	/** Locations to place endnotes
	*/
	typedef enum {kPlacegun, kNewPage} Place;

	/** The different ways to apply prefixes and suffixes to the numbering of endnotes.
	*/
	typedef enum { kPrefixSuffixNone, kPrefixSuffixReference, kPrefixSuffixMarker, kPrefixSuffixBoth } SuffixPrefixUsageOptions;

	/** The different ways to apply positioning to the endnote marker.
	*/
	typedef enum { kPositionNormal, kPositionSuperscript, kPositionSubscript, kPositionRuby } MarkerPositionOptions;

	/** Return endnotes title
	*/
	virtual WideString GetTitle() const = 0;

	/** Set endnotes title
	*/
	virtual void SetTitle(WideString title) = 0;

	/** Return paragraph style for endnotes header
	*/
	virtual UID GetHeaderParaStyle() const = 0;

	/** Set paragraph style for endnotes header
	*/
	virtual void SetHeaderParaStyle(UID styleID) = 0;

	/** Return the option showing when endnotes restart numbering.
	*/
	virtual RestartNumberingOptions GetRestartOption() const = 0;
	/** Set the option showing when endnotes restart numbering.
	*/
	virtual void SetRestartOption(RestartNumberingOptions option) = 0;

	/** Return the number endnotes should start with.
	*/
	virtual int32 GetStartingNumber() const = 0;
	/** Set the number endnotes should start with.
	*/
	virtual void SetStartingNumber(int32 n) = 0;

	/** Return how the endnotes are numbered.  Arabic, roman numerals, etc.
	*/
	virtual ClassID GetNumberingMethod() const = 0;
	/** Set how the endnotes are numbered.  Arabic, roman numerals, etc.
	*/
	virtual void SetNumberingMethod(ClassID whichMethod) = 0;

	/** Return marker positioning
	*/
	virtual MarkerPositionOptions GetMarkerPositioning() const = 0;

	/** Set marker positioning
	*/
	virtual void SetMarkerPositioning(MarkerPositionOptions option) = 0;

	/** Get character style for endnote marker
	*/
	virtual UID GetMarkerStyle() const = 0;

	/** Get character style for endnote marker
	*/
	virtual void SetMarkerStyle(UID styleID) = 0;

	/** Return the paragraph style applied to the endnotes themselves
	*/
	virtual UID GetEndnoteParagraphStyle() const = 0;
	/** Set the paragraph style applied to the endnotes themselves
	*/
	virtual void SetEndnoteParagraphStyle(UID s) = 0;

	/** Return what text is automatically added between the endnote symbol and the endnote in the endnotes frame.
	*/
	virtual const WideString& GetEndnoteSeparator() const = 0;
	/** Set what text is automatically added between the endnote symbol and the endnote in the endnotes frame.
	*/
	virtual void  SetEndnoteSeparator(const WideString& sep) = 0;

	/** Return scope for endnotes placement
	*/
	virtual Scope GetScope() const = 0;
	/** Set scope for endnotes placement
	*/
	virtual void SetScope(Scope scope) = 0;

	/** Return where endnotes are placed (new page or placegun)
	*/
	virtual Place GetPlace() const = 0;
	/** Set place for positioning endnotes (new page or placegun)
	*/
	virtual void SetPlace(Place place) = 0;

	/** Return the string to appear before the endnote number
	*/
	virtual const WideString& GetMarkerPrefix() const = 0;
	/** Set the string to appear before the endnote number
	*/
	virtual void SetMarkerPrefix(const WideString& pre) = 0;

	/** Return the string to appear after the endnote number
	*/
	virtual const WideString& GetMarkerSuffix() const = 0;
	/** Set the string to appear after the endnote number
	*/
	virtual void SetMarkerSuffix(const WideString& suf) = 0;

	/** Return where the prefix/suffix strings should occur with regards to endnotes
	*/
	virtual SuffixPrefixUsageOptions GetPrefixSuffixUsage() const = 0;
	/** Set where the prefix/suffix strings should occur with regards to endnotes
	*/
	virtual void SetPrefixSuffixUsage(SuffixPrefixUsageOptions option) = 0;

	/** Copy setting into current object
	*/
	virtual void CopyFrom(IEndnoteSettings* settings) = 0;

	/** Get the document associated to these changes(when settings are used as command data).Returns nil, if no document.
	*/
	virtual const UIDRef& GetDocument() = 0;

	/** Return whether command data has settings or not.
	*/
	virtual bool16 GetHasSettings() const = 0;

	struct EndnotePrefs {
		EndnotePrefs() {
			bool16 isCCJK = (LocaleSetting::GetLocale().GetLanguageFS() == kJapaneseLanguageFS);
			bool16 isCCKOnly = (isCCJK && (LocaleSetting::GetLocale().GetUserInterfaceId() == k_zhCN		// simplified
				|| LocaleSetting::GetLocale().GetUserInterfaceId() == k_zhTW	// traditional
				|| LocaleSetting::GetLocale().GetUserInterfaceId() == k_koKR));	// Korean

			PMString titleText("ES Title Text", PMString::kTranslateDuringCall);
			fTitle = WideString(titleText);
			fHeaderStyle = kInvalidUID;
			fNumberingMethod = kArabicFootnoteNumberingBoss;
			fStartingNumber = 1;
			fRestartOption = IEndnoteSettings::kContinuous;			
			fMarkerPositioning = (!isCCJK || isCCKOnly) ? IEndnoteSettings::kPositionSuperscript: IEndnoteSettings::kPositionRuby;
			fMarkerStyle = kInvalidUID;
			fEndnoteStyle = kInvalidUID;
			fSeparator = WideString("");
			fSeparator.Append(isCCJK ? kTextChar_IdeographicSpace : kTextChar_Tab);
			fScope = IEndnoteSettings::kDocument;
			fPlace = IEndnoteSettings::kNewPage;
			fPrefixSuffixUsage = IEndnoteSettings::kPrefixSuffixNone;
			fMarkerPrefix = WideString("");
			fMarkerSuffix = WideString("");
		}
		EndnotePrefs(const EndnotePrefs &other) {
			fTitle = other.fTitle;
			fHeaderStyle = other.fHeaderStyle;
			fNumberingMethod = other.fNumberingMethod;
			fStartingNumber = other.fStartingNumber;
			fRestartOption = other.fRestartOption;
			fMarkerPositioning = other.fMarkerPositioning;
			fMarkerStyle = other.fMarkerStyle;
			fEndnoteStyle = other.fEndnoteStyle;
			fSeparator = other.fSeparator;
			fScope = other.fScope;
			fPlace = other.fPlace;
			fPrefixSuffixUsage = other.fPrefixSuffixUsage;
			fMarkerPrefix = other.fMarkerPrefix;
			fMarkerSuffix = other.fMarkerSuffix;
		}
		EndnotePrefs(IEndnoteSettings * settings) {
			fTitle = settings->GetTitle();
			fHeaderStyle = settings->GetHeaderParaStyle();
			fNumberingMethod = settings->GetNumberingMethod();
			fStartingNumber = settings->GetStartingNumber();
			fRestartOption = settings->GetRestartOption();
			fMarkerPositioning = settings->GetMarkerPositioning();
			fMarkerStyle = settings->GetMarkerStyle();
			fEndnoteStyle = settings->GetEndnoteParagraphStyle();
			fSeparator = settings->GetEndnoteSeparator();
			fScope = settings->GetScope();
			fPlace = settings->GetPlace();
			fPrefixSuffixUsage = settings->GetPrefixSuffixUsage();
			fMarkerPrefix = settings->GetMarkerPrefix();
			fMarkerSuffix = settings->GetMarkerSuffix();
		}

		void InitializeStyles(IWorkspace* workspace)
		{
			// Para style - go find the "NormalParagraphStyle"
			InterfacePtr<IStyleGroupManager> paraStyleNameTable(workspace, IID_IPARASTYLEGROUPMANAGER);
			UID defaultStyleUID = paraStyleNameTable->FindByName("NormalParagraphStyle");
			if (defaultStyleUID == kInvalidUID)
				defaultStyleUID = paraStyleNameTable->GetDefaultStyleUID();

			fHeaderStyle = defaultStyleUID;
			fEndnoteStyle = defaultStyleUID;

			// Char style - get the default (root) style.
			InterfacePtr<IStyleGroupManager> charStyleNameTable(workspace, IID_ICHARSTYLEGROUPMANAGER);
			defaultStyleUID = charStyleNameTable->GetRootStyleUID();

			fMarkerStyle = defaultStyleUID;
		}

		WideString fTitle;
		UID fHeaderStyle; //Paragraph style
		ClassID fNumberingMethod;
		int32 fStartingNumber;
		IEndnoteSettings::RestartNumberingOptions fRestartOption;
		IEndnoteSettings::MarkerPositionOptions fMarkerPositioning;
		UID fMarkerStyle; //Character style
		UID fEndnoteStyle; //Paragraph style
		WideString	fSeparator;
		IEndnoteSettings::Scope fScope;
		IEndnoteSettings::Place fPlace;
		IEndnoteSettings::SuffixPrefixUsageOptions fPrefixSuffixUsage;
		WideString	fMarkerSuffix, fMarkerPrefix;
	};

	/** Initialize the data.
	*/
	virtual void Set(const EndnotePrefs* prefs, const UIDRef& doc) = 0;
};

#endif	// __ODFRC__

#endif
// __IEndnoteSettings__