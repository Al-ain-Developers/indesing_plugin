//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpInspectFontMgr.cpp $
//  
//  Owner: ???
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
#include "IDocument.h"
#include "IFontMgr.h"
#include "IFontGroup.h"
#include "IFontNames.h"
#include "IUsedFontList.h"
#include "IPMFont.h"
#include "IWorkspace.h"
#include "IPMStream.h"
#include "IDocFontMgr.h"
#include "IFontFamily.h"
#include "IHierarchy.h"
#include "ILayoutTarget.h"
#include "IDocumentFontUsage.h"
#include "IDocFontMgr.h"
#include "ILocalFontManager.h"

// General includes:
#include "CmdUtils.h"
#include "Utils.h"
#include "UIDList.h"
#include "SDKFileHelper.h"
#include "FileTypeRegistry.h"
#include "StreamUtil.h"
#include "PDFID.h" // IID_IFONTNAMES
#include "K2Vector.tpp"

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** 
	Sample code snippet that shows how to use IFontMgr and IFontGroup
	to find fonts and reports their names using IPMFont.

	@ingroup sdk_snippet
	@ingroup sdk_text

*/
class SnpInspectFontMgr 
{
public:
	/** Constructor.
	 */
	SnpInspectFontMgr() {}

	/** Destructor.
	 */
	virtual ~SnpInspectFontMgr() {}

	/** Uses IFontMgr, IFontGroup and IPMFont to report all the fonts available
		to the application.
		@return kSuccess on success, kFailure otherwise.
	 */
	ErrorCode ReportAllFonts();

	/** Uses IFontMgr, IFontGroup and IPMFont to report the 
		fonts in a given font group.
		@param groupName same as family name e.g. Times, Arial, Courier, Times New Roman
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode ReportFontGroup(const PMString& groupName);

	/** Uses IFontMgr::IsFontAvailable to check availability of the given font.
		@param fontName postscript font name e.g. "Courier-Bold"
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode IsFontAvailable(const PMString& fontName);

	/** Use the calls shown by this method to get an IPMFont when you
		have a Postscript font name.

		Uses IFontMgr::QueryFont and IPMFont to report info on the given font. 
		Using the fontStyleBits parameter you can report on a stylistic variant
		of the given font. For example:

		QueryFont("Courier-Bold", IFontMgr::kItalic)  
		
		reports on postscript font "Courier-Oblique".

		@param fontName postscript font name e.g. "Courier-Bold"
		@param fontStyleBits desired style variant see IFontMgr.h
		@return kSuccess on success, kFailure otherwise.
	*/
	ErrorCode QueryFont(const PMString& fontName, IFontMgr::FontStyleBits fontStyleBits);

	/** Use the calls shown in this method to get an IPMFont when you have the
		name of the typeface on a given platform. This is the typeface name on
		Windows or a font family name on Mac.

		Uses IFontMgr::QueryFontPlatform and IPMFont to report info on the given font.  
		Using the fontStyleBits parameter you can report on a stylistic variant.
		@param fontName name of the typeface on the platform e.g "Times New Roman" or "Courier"
		@param fontStyleBits desired variant see IFontMgr.h
	*/
	ErrorCode QueryFontPlatform(const PMString& fontName, IFontMgr::FontStyleBits fontStyleBits);
	
	void ReportGroup(IFontMgr* fontMgr, IFontGroup* fontGroup, IPMStream* stream = nil);
	void ReportFont(IPMFont* font, IPMStream* stream = nil);

	/**
		Reports all fonts supported by the application (cooltype) that have restrictions on their use.
		@return kSuccess on success
	*/
	ErrorCode ReportFontsWithRestrictions();

	/**
		Determines the list of fonts required by a placed asset
		@param runnableContext IN the context
		@return kFailure on failure
	*/
	ErrorCode TestAssetsForFonts(ISnpRunnableContext* runnableContext);

	/**
		Determines the list of fonts required by a placed assets identified through 
		the UIDList
		@param assets IN the assets to test
		@return kFailure on failure
	*/
	ErrorCode TestAssetsForFonts(UIDList assets);

	/** lists the fonts used directly in the document. Fonts in notes are not reported, only
		fonts used in text page items.
		@param iDocument IN the document to list the fonts from
		@return kSuccess on success
		@see IUsedFontList
	*/
	ErrorCode ListFontsInDocument(IDocument* iDocument);

	/** lists the document-installed fonts.
	 @param iDocument IN the document local fonts installed for
	 @return kSuccess on success
	 */
	ErrorCode ListDocumentInstalledFonts(IDocument* iDocument);

	/**
		Reports the use of fonts in a document, including all text in text frames, along with
		any fonts in placed assets (PDFs or EPS). Fonts in notes are not reported.
		@param iDocument IN the document we are looking at
		@return kSuccess on success
		@see IDocumentFontUsage
	*/
	ErrorCode ReportDocumentFontUsage(IDocument* iDocument);

	/**
		Details the set of fonts that persist (persistent boss class kFontGroupBoss) in the
		(session or document) workspace. To examine the session workspace, call with no document open.
		The fonts reported here are the fonts that exist in the document, including the default set 
		of fonts available in the session workspace.
		@param iWorkspace IN the workspace of interest. Passing in the session workspace exposes
			the default fonts.
		@return kSuccess on success
		@see IDocFontMgr
	*/
	ErrorCode InspectPersistFontUsage(IWorkspace* iWorkspace);

private:
	/**
		dumps the string to SNIPLOG if no stream specified, otherwise, the string is dumped into the
		stream.
		@param str IN the string to dump
		@param stream IN the optional stream to send the string to
	*/
	void dumpString(const char* str, IPMStream* stream = nil);

};

/*
*/
ErrorCode 
SnpInspectFontMgr::InspectPersistFontUsage(IWorkspace* iWorkspace){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IDocFontMgr> iDocFontMgr(iWorkspace,UseDefaultIID());
		if (iDocFontMgr == nil){
			ASSERT(iDocFontMgr);
			break;
		}

		int32 numPersistFontGroups = iDocFontMgr->GetFontGroupCount();
		SNIPLOG("Number of font groups = %d",numPersistFontGroups);

		for (int32 loop = 0; loop < numPersistFontGroups; loop++){
			UID fontFamily = iDocFontMgr->GetNthFontGroupUID(loop);
			
			InterfacePtr<IFontFamily> iFontFamily(::GetDataBase(iWorkspace),fontFamily,UseDefaultIID());
			if (iFontFamily == nil){
				ASSERT(iFontFamily);
				break;
			}
			int32 numFaces = iFontFamily->CountFontFaces();
			SNIPLOG("%d Number of font faces = %d",loop,numFaces);
			for (int32 loop2 = 0; loop2 < numFaces; loop2++){
				PMString fullName;
				iFontFamily->AppendFullName(loop2,fullName);
				SNIPLOG(fullName.GetPlatformString().c_str());
			}
		}
		status = kSuccess;
	}while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::ReportDocumentFontUsage(IDocument* iDocument){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IDocumentFontUsage> iDocumentFontUsage(iDocument,UseDefaultIID());
		if (iDocumentFontUsage == nil){
			ASSERT(iDocumentFontUsage);
			break;
		}

		iDocumentFontUsage->UpdateFontList();
		int32 numUsedFonts = iDocumentFontUsage->GetNumUsedFonts();
		if (numUsedFonts >0){
			SNIPLOG("Number of used fonts %d :",numUsedFonts);
		}
		for (int32 loop = 0; loop < numUsedFonts;loop++){
			PMString fontName = iDocumentFontUsage->GetNthUsedFontString(loop);
			PMString fontFace = iDocumentFontUsage->GetNthUsedFontFaceString(loop);
			SNIPLOG("%s %s",fontName.GetPlatformString().c_str(),fontFace.GetPlatformString().c_str());
		}

		int32 numMissingFonts = iDocumentFontUsage->GetNumMissingFonts();
		if (numMissingFonts >0){
			SNIPLOG("Number of missing fonts %d :",numMissingFonts);
		}
		for (int32 loop2 = 0; loop2<numMissingFonts;loop2++){
			PMString fontName = iDocumentFontUsage->GetNthMissingFontString(loop2);
			PMString fontFace = iDocumentFontUsage->GetNthMissingFontFaceString(loop2);
			SNIPLOG("%s %s",fontName.GetPlatformString().c_str(),fontFace.GetPlatformString().c_str());
		}

		int32 numGraphicFonts = iDocumentFontUsage->GetNumGraphicFonts();
		if (numGraphicFonts >0){
			SNIPLOG("Number of graphic fonts %d :",numGraphicFonts);
		}
		for (int32 loop3 = 0; loop3<numGraphicFonts;loop3++){
			PMString fontName = iDocumentFontUsage->GetNthGraphicFontString(loop3);
			SNIPLOG("%s",fontName.GetPlatformString().c_str());
		}
		status = kSuccess;
	}while(kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::ListFontsInDocument(IDocument* iDocument){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IUsedFontList> iUsedFontList(iDocument,UseDefaultIID());
		if (iUsedFontList == nil){
			ASSERT(iUsedFontList);
			break;
		}
		
		// make sure we are up to date
		iUsedFontList->ForceRecalculateAll();
		
		int32 numberFontFamilies = iUsedFontList->CountUsedFontFamilies();
		SNIPLOG("Number of font families: %d",numberFontFamilies);
		for (int32 loop = 0; loop<numberFontFamilies; loop++){
			UID usedFontFamily = iUsedFontList->GetUsedFontFamily(loop);
			int32 numberFontVariants = iUsedFontList->CountUsedFontVariants(usedFontFamily);
			SNIPLOG("Font family %d: number of variants used: %d",loop,numberFontVariants);
			for (int32 loop2 = 0; loop2 < numberFontVariants; loop2++){
				const PMString* variant = iUsedFontList->GetUsedFontVariant(usedFontFamily,loop2);
				InterfacePtr<IFontFamily> iFontFamily(::GetDataBase(iDocument),usedFontFamily,UseDefaultIID());
				if (iFontFamily == nil){
					ASSERT(iFontFamily);
					continue;
				}
				PMString familyName = iFontFamily->GetFamilyName();

				SNIPLOG("%s %s",familyName.GetPlatformString().c_str(),variant->GetPlatformString().c_str());
			}
		}

		int32 numberMissingFonts = iUsedFontList->CountMissingFonts();
		SNIPLOG("Number of missing fonts: %d",numberMissingFonts);
		for (int32 loop3 = 0; loop3 < numberMissingFonts; loop3++){
			UID family;
			PMString fontName;
			iUsedFontList->GetMissingFont(loop3,&family,fontName);
			InterfacePtr<IFontFamily> iFontFamily(::GetDataBase(iDocument),family,UseDefaultIID());
			if (iFontFamily == nil){
				ASSERT(iFontFamily);
				continue;
			}
			PMString familyName = iFontFamily->GetFamilyName();
			SNIPLOG("%s %s",familyName.GetPlatformString().c_str(),fontName.GetPlatformString().c_str());
		}
		status = kSuccess;
	}while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::ListDocumentInstalledFonts(IDocument* iDocument)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IFontMgr> fontMgr(iDocument, UseDefaultIID());		
		if (!fontMgr)
			break;
		
		ILocalFontManager* lFontMgr (static_cast <ILocalFontManager *> (fontMgr.get()));
		
		//document installed fonts
		int32 nDocFontGroups = lFontMgr->GetNumDocumentFontGroups();
		SNIPLOG("%d document-installed font:", nDocFontGroups);
		for(int32 i = 0; i < nDocFontGroups; i++)
		{
			InterfacePtr<IFontGroup> fontGroup(lFontMgr->QueryDocumentFontGroup(i));
			PMString groupName =  fontGroup->GetGroupName();
			SNIPLOG("  %s", groupName.GetPlatformString().c_str());
		}
		
		status = kSuccess;
	} while (kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::TestAssetsForFonts(ISnpRunnableContext* runnableContext){
	ErrorCode status = kFailure;
	do {
		UIDList itemList;
		InterfacePtr<ILayoutTarget> layoutTarget(runnableContext, UseDefaultIID());
		if (layoutTarget) {
			itemList = layoutTarget->GetUIDList(kStripStandoffs);
		}
		if (itemList.Length() > 0) {
			status = this->TestAssetsForFonts(itemList);
		}
		else {
			SNIPLOG("Snippet requires selected assets");
			break;
		}
	} while(kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::TestAssetsForFonts(UIDList assets){
	ErrorCode status = kFailure;
	do {
		int32 numItems = assets.Length();
		for (int32 loop = 0; loop < numItems; loop++){
			UIDRef asset = assets.GetRef(loop);
			InterfacePtr<IHierarchy> iHierarchy(asset,UseDefaultIID());
			if (iHierarchy == nil) {
				continue;
			}
			UIDList placedAssets(assets.GetDataBase());
			iHierarchy->GetDescendents(&placedAssets,IID_IFONTNAMES);
			if (placedAssets.Length() == 0){
				continue;
			}
			InterfacePtr<IFontNames> iFontNames(placedAssets.GetRef(0),IID_IFONTNAMES);
			if (iFontNames == nil){
				ASSERT(iFontNames);
				continue;
			}
			
			K2Vector<PMString> neededFontStrings;
			SNIPLOG("Required fonts:");
			//find all the fonts needed by the asset
			iFontNames->FontsNeeded(neededFontStrings);
			for(int32 loop2 = 0; loop2 < neededFontStrings.size(); loop2++)
			{
				SNIPLOG("%s",neededFontStrings[loop2].GetPlatformString().c_str());
			}

			K2Vector<PMString> suppliedFontStrings;
			SNIPLOG("Supplied fonts:");
			//find all the fonts supplied by the asset
			iFontNames->FontsSupplied(suppliedFontStrings);
			for(int32 loop2 = 0; loop2 < suppliedFontStrings.size(); loop2++)
			{
				SNIPLOG("%s",suppliedFontStrings[loop2].GetPlatformString().c_str());
			}
		}
		status = kSuccess;
	} while(kFalse);
	return status;
}

/*
*/
ErrorCode 
SnpInspectFontMgr::ReportFontsWithRestrictions(){
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}

		int32 numFontGroups = fontMgr->GetNumFontGroups();
		for (int32 groupIndex = 0; groupIndex < numFontGroups; groupIndex++) {
			InterfacePtr<IFontGroup>fontGroup(fontMgr->QueryFontGroup(groupIndex));
			if (fontGroup == nil) {
				break;
			}
			int32 faceCount = fontGroup->GetNumFonts();
			for (int32 faceIndex = 0; faceIndex <faceCount; faceIndex++) {
				InterfacePtr<IPMFont> font(fontMgr->QueryFont(fontGroup, faceIndex));
				if (font == nil) {
					break;
				}
				// grab all the restrictions that might apply				
				PMString protection;
				K2Vector<IPMFont::FontProtection> *fontProtection = font->GetProtection();

				K2Vector<IPMFont::FontProtection>::iterator iter;
				bool16 dumpInfo = !(fontProtection->size() == 1 && fontProtection->front() ==IPMFont::kNormal) ;
				for (iter = fontProtection->begin(); iter != fontProtection->end(); ++iter)
				{
					if ((*iter) == IPMFont::kNoOutlines)
					{
						protection += PMString("No outline ");
					}
					if ((*iter) == IPMFont::kNoPrinting)
					{
						protection += PMString("No Printing ");
					}
					if ((*iter) == IPMFont::kNoEmbedding)
					{
						protection += PMString("No Embedding ");
					}
					if ((*iter) == IPMFont::kNoPDFEmbedding)
					{
						protection += PMString("No PDF embedding ");
					}
					if ((*iter) == IPMFont::kRestrictedPrinting)
					{
						protection += PMString("Restricted printing ");
					}
					if ((*iter) == IPMFont::kInvalid)
					{
						protection += PMString("Invalid ");
					}
				}
				delete fontProtection;
				if (!dumpInfo)
					continue;
				PMString output;
				font->AppendFontName(output);
				output.Append(" - ");
				output.Append(protection);
				dumpString(output.GetPlatformString().c_str());
			}
		}
		status = kSuccess;
	} while (false);
	return status;
}

void
SnpInspectFontMgr::dumpString(const char* str, IPMStream* stream){
	if (stream) {
		const char * newline = "\r\n";
		stream->XferByte((uchar *)str, static_cast<int32>(strlen(str)));
		stream->XferByte((uchar *)newline, static_cast<int32>(strlen(newline)));
	}
	else {
		SNIPLOG(str);
	}
}

/* ReportAllFonts
*/
ErrorCode SnpInspectFontMgr::ReportAllFonts()
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}

		// create a stream to write to.
		SDKFileSaveChooser fileChooser;
		PMString title = "Fonts dump log";
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

	
		int32 numFontGroups = fontMgr->GetNumFontGroups();
		for (int32 groupIndex = 0; groupIndex < numFontGroups; groupIndex++) {
			InterfacePtr<IFontGroup>fontGroup(fontMgr->QueryFontGroup(groupIndex));
			if (fontGroup == nil) {
				break;
			}
			this->ReportGroup(fontMgr, fontGroup,stream);
		}
		status = kSuccess;
	} while (false);
	return status;
}

/*
*/
ErrorCode SnpInspectFontMgr::ReportFontGroup(const PMString& groupName)	
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}

		InterfacePtr<IFontGroup> fontGroup(fontMgr->QueryFontGroup(groupName));
		if (fontGroup== nil) {
			break;
		}
		this->ReportGroup(fontMgr, fontGroup,nil);
		status = kSuccess;
	} while (false);
	return status;
}

/* IsFontAvailable
*/
ErrorCode SnpInspectFontMgr::IsFontAvailable(const PMString& fontName)
{
	ErrorCode status = kFailure;
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}
		bool16 fontIsAvailable = fontMgr->IsFontAvailable(fontName);
		if (fontIsAvailable == kFalse) {
			SNIPLOG("%s is not available", fontName.GetPlatformString().c_str());
		}
		else {
			SNIPLOG("%s is available", fontName.GetPlatformString().c_str());
		}
		status = kSuccess;
	} while(false);
	return status;
}

/* QueryFont
*/
ErrorCode SnpInspectFontMgr::QueryFont(const PMString& fontName, IFontMgr::FontStyleBits fontStyleBits)
{
	ErrorCode status = kFailure;
	SNIPLOG("fontName=%s, fontStyleBits=0x%x", fontName.GetPlatformString().c_str(), fontStyleBits);
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}
		// test to see if we have the font
		if(!fontMgr->IsFontAvailable(fontName)){
			// if you request a font (psname) that doesn't exist, you get
			// the default
			SNIPLOG(" font not available");
			break;
		}
		InterfacePtr<IPMFont> font(fontMgr->QueryFont(fontName, fontStyleBits));
		if (font == nil || font->GetFontStatus() != IPMFont::kFontInstalled) {
			SNIPLOG(" font not available");
			break;
		}
		this->ReportFont(font,nil);
		status = kSuccess;
	} while(false);
	return status;
}

/* QueryFontPlatform
*/
ErrorCode SnpInspectFontMgr::QueryFontPlatform(const PMString& fontName, IFontMgr::FontStyleBits fontStyleBits)
{
	ErrorCode status = kFailure;
	SNIPLOG("fontName=%s, fontStyleBits=0x%x", fontName.GetPlatformString().c_str(), fontStyleBits);
	do {
		InterfacePtr<IFontMgr> fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil) {
			break;
		}
		InterfacePtr<IPMFont> font(fontMgr->QueryFontPlatform(fontName, fontStyleBits));
		if (font == nil || font->GetFontStatus() != IPMFont::kFontInstalled) {
			SNIPLOG(" font not available");
			break;
		}
		this->ReportFont(font,nil);
		status = kSuccess;
	} while(false);
	return status;
}

/* ReportGroup
*/
void SnpInspectFontMgr::ReportGroup(IFontMgr* fontMgr, IFontGroup* fontGroup, IPMStream* stream)
{
	do {
		const PMString& groupName = fontGroup->GetGroupName();
		int32 faceCount = fontGroup->GetNumFonts();
		char buffer[250];
		sprintf(buffer,"groupName=%s", groupName.GetPlatformString().c_str());
		dumpString(buffer,stream);

		for (int32 faceIndex = 0; faceIndex <faceCount; faceIndex++) {
			InterfacePtr<IPMFont> font(fontMgr->QueryFont(fontGroup, faceIndex));
			if (font == nil) {
				break;
			}
			this->ReportFont(font, stream);
		}
	} while (false);
}

/* ReportFont
*/
void SnpInspectFontMgr::ReportFont(IPMFont* font, IPMStream* stream)
{
	do {
		char buffer[250];

		PMString familyName("IPMFont::AppendFamilyName= ");
		font->AppendFamilyName(familyName);
		sprintf(buffer,"%s",familyName.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString styleName("IPMFont::AppendStyleName= ");
		font->AppendStyleName(styleName);
		sprintf(buffer,"%s",styleName.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString fontName("IPMFont::AppendFontName= ");
		font->AppendFontName(fontName);
		sprintf(buffer,"%s",fontName.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString fullName("IPMFont::AppendFullName= ");
		font->AppendFullName(fullName);
		sprintf(buffer,"%s",fullName.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString familyNameNative("IPMFont::AppendFamilyNameNative= ");
		font->AppendFamilyNameNative(familyNameNative);
		sprintf(buffer,"%s",familyNameNative.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString styleNameNative("IPMFont::AppendStyleNameNative= ");
		font->AppendStyleNameNative(styleNameNative);
		sprintf(buffer,"%s",styleNameNative.GetPlatformString().c_str());
		dumpString(buffer,stream);

		PMString fullNameNative;
		font->AppendFullNameNative(fullNameNative);
 		// commented out - if PMString is set to an encoding that cannot be displayed, this asserts
		// SNIPLOG("IPMFont::AppendFullNameNative=%s", fullNameNative.GetPlatformString().c_str());


		sprintf(buffer,"IPMFont::GetFontTechnology=0x%x",font->GetFontTechnology());
		dumpString(buffer,stream);

		sprintf(buffer,"IPMFont::GetFontStatus=0x%x",font->GetFontStatus());
		dumpString(buffer,stream);

		dumpString("-----------------------------",stream);
	} while (false);
}

// --------------------------------- SnippetRunner framework hooks ---------------------------------------------------
/** Makes the snippet SnpInspectFontMgr available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run
	
 */
class _SnpRunnerInspectFontMgr : public SnpRunnable
{
public:
	// SnippetRunner framework hooks.

	/** Constructor.
	 */
	_SnpRunnerInspectFontMgr(void);

	/** Destructor.
	 */
	virtual ~_SnpRunnerInspectFontMgr(void);

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

/* Constructor.
*/
_SnpRunnerInspectFontMgr::_SnpRunnerInspectFontMgr(void) : SnpRunnable("InspectFontMgr")
{
	this->SetDescription("Inspect IFontMgr and IFontGroup");
    this->SetPreconditions("none");
	this->SetCategories("sdk_snippet, sdk_text");
}

/* Destructor.
*/
_SnpRunnerInspectFontMgr::~_SnpRunnerInspectFontMgr(void)
{
	// do nothing
}

/* Check if your preconditions are met.
*/
bool16	_SnpRunnerInspectFontMgr::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerInspectFontMgr::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do {
		SnpInspectFontMgr instance;
		// Get parameters.
		Utils<ISnipRunParameterUtils> parameterUtils;

		// Get which choice the user wants to run.
		K2Vector<PMString> choices;
		choices.push_back(PMString("ReportAllFonts"));
		choices.push_back(PMString("ReportFontsWithRestrictions"));
		choices.push_back(PMString("ReportFontGroup"));
		choices.push_back(PMString("IsFontAvailable"));
		choices.push_back(PMString("QueryFont"));
		choices.push_back(PMString("QueryFontPlatform"));
		choices.push_back(PMString("TestAssetForFonts"));
		choices.push_back(PMString("ListDocumentFonts"));
		choices.push_back(PMString("ListDocumentInstalledFonts"));
		choices.push_back(PMString("ReportDocumentFontUsage"));
		choices.push_back(PMString("InspectPersistFontUsage"));
		
		enum {kReportAllFonts, kReportFontsWithRestrictions, kReportFontGroup, 
			kIsFontAvailable, kQueryFont, kQueryFontPlatform, kTestAssetForFonts,
			kListDocumentFonts, kListDocumentInstalledFonts,
			kReportDocumentFontUsage,kInspectPersistFontUsage};
		int32 choice  = parameterUtils->GetChoice("What do you want to do.", choices);
		if (parameterUtils->WasDialogCancelled() == kFalse) {
			switch (choice) 
			{
				case kReportAllFonts:
					{
						status = instance.ReportAllFonts();
						break;
					}
				case kReportFontsWithRestrictions:
					{
						status = instance.ReportFontsWithRestrictions();
						break;
					}
				case kReportFontGroup:
					{
						Utils<ISnipRunParameterUtils> parameterUtils;
						PMString fontGroup = parameterUtils->GetPMString("please give the name of the font group you want", "Times New Roman");
						status = instance.ReportFontGroup(fontGroup);
						break;
					}
				case kIsFontAvailable:
					{
						Utils<ISnipRunParameterUtils> parameterUtils;
						PMString fontName = parameterUtils->GetPMString("please specify the name of the font you want to check", "AGaramond-Regular");
						status = instance.IsFontAvailable(fontName);
						break;
					}
				case kQueryFont:
					{
						Utils<ISnipRunParameterUtils> parameterUtils;
						PMString fontName = parameterUtils->GetPMString("please specify name of font to call IFontMgr::QueryFont with", "AGaramond-Regular");
						instance.QueryFont(fontName, IFontMgr::kBold);
						instance.QueryFont(fontName, IFontMgr::kItalic);
						status = instance.QueryFont(fontName, IFontMgr::kNormal);
						break;
					}
				case kQueryFontPlatform:
					{
						Utils<ISnipRunParameterUtils> parameterUtils;
						PMString fontName = parameterUtils->GetPMString("please specify name of font to call IFontMgr::QueryFontPlatform with", "Times New Roman");
						instance.QueryFontPlatform(fontName, IFontMgr::kBold);
						instance.QueryFontPlatform(fontName, IFontMgr::kItalic);
						status = instance.QueryFontPlatform(fontName, IFontMgr::kNormal);
						break;
					}
				case kTestAssetForFonts:
					{
						status = instance.TestAssetsForFonts(runnableContext);
						break;
					}

				case kListDocumentFonts:
				case kListDocumentInstalledFonts:
				case kReportDocumentFontUsage:
					{
						IDocument* iDocument = runnableContext->GetActiveContext()->GetContextDocument();
						if (iDocument == nil){
							SNIPLOG("This option requires a document");
							break;
						}
						if (choice == kListDocumentFonts){
							status = instance.ListFontsInDocument(iDocument);
						} 
						else if (choice == kListDocumentInstalledFonts){
							status = instance.ListDocumentInstalledFonts(iDocument);
						} 
						else{
							status = instance.ReportDocumentFontUsage(iDocument);
						}
						break;
					}
				case kInspectPersistFontUsage:
					{
						IWorkspace* iWorkspace = runnableContext->GetActiveContext()->GetContextWorkspace();
						status = instance.InspectPersistFontUsage(iWorkspace);
						break;
					}

				default:
					{
						SNIPLOG("No such choice");
					}
			}
		}		
	} while(false);
	return status;
}

/*	Declare an instance to register the snippet with the framework.
*/
static _SnpRunnerInspectFontMgr instance_SnpRunnerInspectFontMgr;
DEFINE_SNIPPET(_SnpRunnerInspectFontMgr) 	
