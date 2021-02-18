//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/appearancepanel/FontUtilData.cpp $
//  
//  Owner: 
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
//  Copyright 1997-2017 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#include "VCPlugInHeaders.h"

#include "IFontUtilData.h"
#include "FormFieldID.h"
#include "CPMUnknown.h"
#include "IFontMgr.h"
#include "IFontGroup.h"
#include "IPMFont.h"
#include <map>
#include "IDocument.h"
#include "IUsedFontList.h"
#include "k2sortedvector.tpp"
#include "IFontFamily.h"
#include "ShuksanCoolType.h"
#include "LocaleSetting.h"

// Utils
#include "ILayoutUIUtils.h"

class FontUtilData : public CPMUnknown<IFontUtilData>
{
	typedef CPMUnknown<IFontUtilData> inherited;
public:
	FontUtilData(IPMUnknown* boss);
	virtual ~FontUtilData();

	virtual bool16 GetFontCachedDataValid() const;

	virtual void InvalidateFontCacheData();

	virtual void UpdateFontCacheData();

	virtual PMString GetFontPostScriptName(const PMString& fontFamilyName, const PMString& fontStyle);

	virtual void GetStylesInFontFamily(const PMString& fontFamilyName, std::vector<PMString>& outStyleNames);

	virtual void GetFontFamiliesList(std::vector<PMString>& outFamiliesList);
    
    virtual bool16 IsFontStyleAvailable(const PMString& fontFamilyName, const PMString& fontStyle);

private:

	void DoValidate();
	void InitializeFontData();
	bool16 SkipThisFont(IPMFont* font);
    void InitializeMissingFonts();
    void AddBracketsAroundString(PMString &name) const;

	bool16 fIsCacheDataValid;
	std::map<PMString, PMString> fFamilyToPSNameMap;
	std::vector<PMString> fFamiliesList;
	std::map<PMString, std::vector<PMString> > fFontFamilyStyleList;
};

CREATE_PMINTERFACE(FontUtilData, kFontUtilDataImpl);

FontUtilData::FontUtilData(IPMUnknown* boss) :inherited(boss), fIsCacheDataValid(kFalse)
{}

FontUtilData::~FontUtilData() {}

bool16 FontUtilData::GetFontCachedDataValid() const
{
	return fIsCacheDataValid;
}

void FontUtilData::InvalidateFontCacheData()
{
	fIsCacheDataValid = kFalse;
}

void FontUtilData::UpdateFontCacheData()
{
	fFamiliesList.clear();
	fFamilyToPSNameMap.clear();
	fFontFamilyStyleList.clear();
	InitializeFontData();
	fIsCacheDataValid = true;
}

PMString FontUtilData::GetFontPostScriptName(const PMString& fontFamilyName, const PMString& fontStyle)
{
	DoValidate();
	PMString key(fontFamilyName + fontStyle);
	key.StripWhiteSpace(PMString::kAllWhiteSpace);
	ASSERT_MSG(key.CharCount() > 0, "Font Family and Style are empty. Are you high?");
	PMString result = "";
	std::map<PMString, PMString>::iterator it = fFamilyToPSNameMap.find(key);
	if (it != fFamilyToPSNameMap.end())
		result = it->second;
	/*result = fontFamilyName;
	result.StripWhiteSpace(PMString::kAllWhiteSpace);*/
	result.SetTranslatable(kFalse);
	return result;
}

void FontUtilData::GetFontFamiliesList(std::vector<PMString>& outFamiliesList)
{
	DoValidate();
	outFamiliesList.clear();
	for (size_t i = 0; i < fFamiliesList.size(); i++)
	{
		outFamiliesList.push_back(fFamiliesList[i]);
		outFamiliesList[i].SetTranslatable(kFalse);
	}
	ASSERT_MSG(outFamiliesList.size() > 0,"The families list not ready?");
}

void FontUtilData::GetStylesInFontFamily(const PMString& fontFamilyName, std::vector<PMString>& outStyleNames)
{
	DoValidate();
	outStyleNames.clear();
	std::map<PMString, std::vector<PMString> >::iterator it = fFontFamilyStyleList.find(fontFamilyName);
	ASSERT_MSG(it != fFontFamilyStyleList.end(), "Font family not available in font family list. something is wrong.");
	if (it == fFontFamilyStyleList.end())
        return;
    std::vector<PMString> styles = it->second;
	for (size_t i = 0; i < styles.size(); i++)
	{
		outStyleNames.push_back(styles[i]);
		outStyleNames[i].SetTranslatable(kFalse);
	}
}

bool16 FontUtilData::IsFontStyleAvailable(const PMString& fontFamilyName, const PMString& fontStyleName)
{
    std::map<PMString, std::vector<PMString> >::iterator it = fFontFamilyStyleList.find(fontFamilyName);
    if (it == fFontFamilyStyleList.end())
    {
        // font may be missing, so check after adding brackets around it.
        PMString missingFamilyName(fontFamilyName), missingStyleName(fontStyleName);
        AddBracketsAroundString(missingFamilyName);
        AddBracketsAroundString(missingStyleName);
        std::map<PMString, std::vector<PMString> >::iterator missing_it = fFontFamilyStyleList.find(missingFamilyName);
        if (missing_it != fFontFamilyStyleList.end())
        {
            std::vector<PMString> styles = missing_it->second;
            if (find(styles.begin(), styles.end(), missingStyleName) != styles.end())
            {
                return kTrue;
            }
        }
    }
    else
    {
        PMString missingStyleName(fontStyleName);
        AddBracketsAroundString(missingStyleName);
        std::vector<PMString> styles = it->second;
        //Also check for missing style name
        if (find(styles.begin(), styles.end(), fontStyleName) != styles.end()
            || find(styles.begin(), styles.end(), missingStyleName) != styles.end())
        {
            return kTrue;
        }
    }
    
    return kFalse;
}

void FontUtilData::DoValidate()
{ 
	if (fIsCacheDataValid)
		return;
	fFamiliesList.clear();
	fFamilyToPSNameMap.clear();
	fFontFamilyStyleList.clear();
	InitializeFontData();
	fIsCacheDataValid = true;
}

bool ComparatorFn(PMString a, PMString b)
{
	a.ToUpper();
	b.ToUpper();
	return a < b;
}

void FontUtilData::InitializeFontData()
{
	IDocument* frontDoc = Utils <ILayoutUIUtils>()->GetFrontDocument();
	InterfacePtr<IFontMgr> fontMgr(nil);
	if (frontDoc)
	{
		fontMgr = InterfacePtr<IFontMgr>(frontDoc, UseDefaultIID());
	}
	else
	{
		fontMgr = InterfacePtr<IFontMgr>(GetExecutionContextSession(), UseDefaultIID());
	}

	std::vector<PMString> nativeNameFamiliesList;
	int32 numfontGroups = fontMgr->GetNumFontGroups();
	for (int32 i = 0; i < numfontGroups; i++)
	{
		InterfacePtr<IFontGroup> ithFontGroup(fontMgr->QueryFontGroup(i));

		if (ithFontGroup)
		{
			int32 numFonts = ithFontGroup->GetNumFonts();
			std::vector<PMString> stylesInGroup;
			const int32 localeScript = LocaleSetting::GetLocale().GetUIScript();
			bool16 useNativeName = kFalse;
			PMString fontFamilyName;
			for (int32 j = 0; j < numFonts; j++)
			{
				InterfacePtr<IPMFont> font(fontMgr->QueryFont(ithFontGroup, j));
				ASSERT(font);
				fontFamilyName = "";

				if (!SkipThisFont(font))
				{
					PMString fontStyleName, fontPSName, postScriptName("");
					// CCJK fonts should be localized and the default CCJK font should be list on top. Bug #ID-4210832
					useNativeName = localeScript != kCTRomanScript && font->GetWritingScript() == localeScript
						|| font->GetFontType() == IPMFont::kATCFontType;
					if (useNativeName)
						font->AppendFamilyNameNative(fontFamilyName);
					if (fontFamilyName.empty())
						font->AppendFamilyName(fontFamilyName);

					font->AppendFontName(fontPSName);
					font->AppendStyleName(fontStyleName);
					postScriptName.Append(font->GetPostScriptName().c_str());
					fontFamilyName.SetTranslatable(kFalse);
					fontStyleName.SetTranslatable(kFalse);
					fontPSName.SetTranslatable(kFalse);
					stylesInGroup.push_back(fontStyleName);
					PMString key(fontFamilyName + fontStyleName);
					key.StripWhiteSpace(PMString::kAllWhiteSpace);
					fFamilyToPSNameMap.insert(std::make_pair(key, fontPSName));
				}
			}
			if (!stylesInGroup.empty())
			{
				std::sort(stylesInGroup.begin(), stylesInGroup.end(), ComparatorFn);
				fFontFamilyStyleList.insert(std::make_pair(fontFamilyName, stylesInGroup));
				if (useNativeName)
					nativeNameFamiliesList.push_back(fontFamilyName);
				else
					fFamiliesList.push_back(fontFamilyName);
			}
		}
	}
	std::sort(fFamiliesList.begin(), fFamiliesList.end(), ComparatorFn);
	if (!nativeNameFamiliesList.empty())
	{
		//std::sort(nativeNameFamiliesList.begin(), nativeNameFamiliesList.end(), ComparatorFn);
		nativeNameFamiliesList.push_back("-");
		fFamiliesList.insert(fFamiliesList.begin(), nativeNameFamiliesList.begin(), nativeNameFamiliesList.end());
	}

    InitializeMissingFonts();
}

bool16 FontUtilData::SkipThisFont(IPMFont * font)
{
	//do not show composite fonts in drop down. bug #ID-4210134
	if (font->GetFontTechnology() == IPMFont::kATCFont)
		return kTrue;

#if TEXTUI_FILTER_ALL_BITMAPS
	if (font->GetFontStatus() != IPMFont::kFontInstalled)
		return kTrue;
#else
#ifdef MACINTOSH
	if (font->GetWritingScript() == kCTRomanScript && font->GetFontTechnology() == IPMFont::kBitmapFont)
#endif
#ifdef WINDOWS
		if (font->GetFontTechnology() == IPMFont::kBitmapFont)
#endif
			return kTrue;
#endif
	return kFalse;
}

void FontUtilData::InitializeMissingFonts()
{
    IDocument *frontDoc = Utils<ILayoutUIUtils>()->GetFrontDocument();
    InterfacePtr<IUsedFontList> usedFonts(frontDoc, IID_IUSEDFONTLIST);
    const int32 numMissing = usedFonts ? usedFonts->CountMissingFonts() : 0;
    if( !numMissing )
        return;
    
    IDataBase    *db = ::GetDataBase(usedFonts);
    if( !db )
        return;
	bool16 addSeparator = kTrue;
    for( int32 iMissing = 0; iMissing < numMissing; ++iMissing )
    {
        PMString fontFamilyName, fontStyleName, fontPSName;
        std::vector<PMString> stylesInGroup;
        UID familyUID = kInvalidUID;
        usedFonts->GetMissingFont(iMissing, &familyUID, fontStyleName );
        InterfacePtr<IFontFamily> fontFamily(db, familyUID, UseDefaultIID());
		fontFamilyName = fontFamily->GetDisplayFamilyName();
		ASSERT_MSG(familyUID > 0, "Font UID is not valid");
        fontPSName = fontFamily->GetFacePostscriptName(fontStyleName);
		if (find(fFamiliesList.begin(), fFamiliesList.end(), fontFamilyName) == fFamiliesList.end())
		{
			AddBracketsAroundString(fontFamilyName);
			if (find(fFamiliesList.begin(), fFamiliesList.end(), fontFamilyName) == fFamiliesList.end())
			{
				if (addSeparator)
				{
					fFamiliesList.push_back("-");
					addSeparator = kFalse;
				}
				fFamiliesList.push_back(fontFamilyName);
			}
		}
        
		AddBracketsAroundString(fontStyleName);
        fontFamilyName.SetTranslatable(kFalse);
        fontStyleName.SetTranslatable(kFalse);
        fontPSName.SetTranslatable(kFalse);
        stylesInGroup.push_back(fontStyleName);
        PMString key(fontFamilyName + fontStyleName);
        key.StripWhiteSpace(PMString::kAllWhiteSpace);
        fFamilyToPSNameMap.insert(std::make_pair(key, fontPSName));
		auto ret = fFontFamilyStyleList.insert(std::make_pair(fontFamilyName, stylesInGroup));
		if (ret.second == false)
		{
			// If above insert call is not successful, it means that entry for fontFamilyName exists in fFontFamilyStyleList.
			// Now add current font style to already existing styles.
			ret.first->second.push_back(fontStyleName);
		}
		
    }
}

void FontUtilData::AddBracketsAroundString(PMString& name) const
{
    if (!name.IsEmpty())
    {
        //Do not add further brackets if name aready has bracket around it
        if (name[0] != kTextChar_LeftSquareBracket)
        {
            name.InsertW(kTextChar_LeftSquareBracket);
            name.AppendW(kTextChar_RightSquareBracket);
        }
        name.SetTranslatable(kFalse);
    }
}
