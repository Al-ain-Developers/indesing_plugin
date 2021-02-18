//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpManipulatePrintStyles.cpp $
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
#include "IGenStyleLockInfo.h"
#include "IObjectModel.h"
#include "IPersistUIDData.h"
#include "IPrintData.h"
#include "IPrintDeviceInfo.h"
#include "IPrStStyleListMgr.h"
#include "ISession.h"
#include "IStringData.h"
#include "IUIDData.h"
#include "IWorkspace.h"
#include "IXferBytes.h"

// General includes:
#include "Utils.h"
#include "UIDList.h"
#include "PrintID.h" 
#include "K2Vector.h"
#include "K2Vector.tpp"
#include "K2Pair.h"
//#include "ShuksanID.h" // IID_IPRINTCLIENTITEMSUID

// Framework includes:
#include "SnpRunnable.h"
#include "ISnipRunParameterUtils.h"
#include "SnipRunLog.h"

/** \li	A code snippet that shows how to manipulate print preset styles in a document.

	@ingroup sdk_snippet, sdk_print
	@author Ken Sadahiro
 */
class SnpManipulatePrintStyles
{
public:
	/** Strucure that stores all of the data you can "Get" from IPrintData.
	 *	@see IPrintData
	 */
	struct PrintDataStruct
	{
		IXferBytes* fPrintRecordStream; // GetPrintRecordStream(void) = 0;
		bool16 fIsDefaultValues; // GetIsDefaultValues() 
		int32 fDeviceType; //  GetDeviceType() 
		PMString fStyleName; // GetStyleName() 
		int32 fPrintTo; // GetPrintTo() 
		PMString fPrinter; // GetPrinter() 
		PMString fFileName; // GetFileName() 
		PMString fPPDName; // GetPPDName() 
		PMString fPPDFile; // GetPPDFile() 
		int32 fPSLangLevel; // GetPSLangLevel() 
		PMReal fResolution; // GetResolution() 
		PMRect fPaperSize; // GetPaperSize() 
		PMRect fImageablePaperSize; // GetImageablePaperSize() 
		int32 fPaperSizeSelection; // GetPaperSizeSelection() 
		PMString  fPaperSizeName; // GetPaperSizeName() 
		PMReal fCustomPaperWidth; // GetCustomPaperWidth() 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperWidthRange; // GetDeviceCustomPaperWidthRange(PMReal &outMinWidth, PMReal &outMaxWidth) 
		PMReal fCustomPaperHeight; // GetCustomPaperHeight() 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperHeightRange; // GetDeviceCustomPaperHeightRange(PMReal &outMinHeight, PMReal &outMaxHeight) 
		PMReal fCustomPaperOffset; // GetCustomPaperOffset() 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperWidthOffsetRange; // GetDeviceCustomPaperWidthOffsetRange(PMReal &outMin, PMReal &outMax) 
		PMReal fCustomPaperGap; // GetCustomPaperGap() 
		int32 fPaperOrientation; // GetPaperOrientation() 
		int32 fPageOrientation; // GetPageOrientation() 
		int32 fCopies; // GetCopies() 
		bool16 fCollate; // GetCollate() 
		bool16 fReverseOrder; // GetReverseOrder() 
		int32 fFlipMode; // GetFlipMode() 
		bool16 fNegative; // GetNegative() 
		bool16 fPrintBlankPages; // GetPrintBlankPages() 
		bool16 fPrintNonPrintingObjects; // GetPrintNonPrintingObjects() 
		int32 fWhichPages; // GetWhichPages() 
		PMString fPageRange; // GetPageRange()  
		int32 fPrintOption; // GetPrintOption() 
		bool16 fSpreads; // GetSpreads() 
		int32 fOutputMode; // GetOutputMode() 
		bool16 fPrintColorsInBlack; // GetPrintColorsInBlack() 
		bool16 fShowSaveDialog; // GetShowSaveDialog() 
		PMReal fCompositeAngle; // GetCompositeAngle() 
		PMReal fCompositeFrequency; // GetCompositeFrequency() 
		PMString fCompositeScreenText; // GetCompositeScreenText() 
		PMString fSeparationScreenText; // GetSeparationScreenText() 
		int32 fScaleMode; // GetScaleMode() 
		bool16 fProportional; // GetProportional() 
		PMReal fXScale; // GetXScale() 
		PMReal fYScale; // GetYScale() 
		int32 fPagePosition; // GetPagePosition() 
		int32 fTileThumbMode; // GetTileThumbMode() 
		int32 fTilingMode; // GetTilingMode() 
		PMReal fTilingOverlap; // GetTilingOverlap() 
		int32 fNumberOfThumbsPerPage; // GetNumberOfThumbsPerPage() 
		int32 fImageData; // GetImageData() 
		int32 fImageDataFormat; // GetImageDataFormat() 
		bool16 fOPIReplacement; // GetOPIReplacement() 
		bool16 fOmitEPS; // GetOmitEPS() 
		bool16 fOmitPDF; // GetOmitPDF() 
		bool16 fOmitImages; // GetOmitImages() 
		int32 fFontDownload; // GetFontDownload() 
		bool16 fDownloadPPDFonts; // GetDownloadPPDFonts() 
		PMString fPageMarkFile; // GetPageMarkFile() 
		int32 fMarkLineWeight; // GetMarkLineWeight() 
		PMReal fPageMarkOffset; // GetPageMarkOffset() 
		bool16 fCropMarks; // GetCropMarks() 
		bool16 fPageInformation; // GetPageInformation() 
		bool16 fColorBars; // GetColorBars() 
		bool16 fRegistrationMarks; // GetRegistrationMarks() 
		bool16 fBleedMarks; // GetBleedMarks() 
		bool16 fUseDocumentBleed; // GetUseDocumentBleed() 
		PMReal fBleedTop; // GetBleedTop() 
		bool16 fBleedChain; // GetBleedChain() 
		PMReal fBleedInside; // GetBleedInside() 
		PMReal fBleedBottom; // GetBleedBottom() 
		PMReal fBleedOutside; // GetBleedOutside() 
		bool16 fIncludeSlug; // GetIncludeSlug() 
		int32 fTrappingMode; // GetTrappingMode() 
		int32 fSourceSpace; // GetSourceSpace() 
		int32 fProfileType; // GetProfileType() 
		PMString fProfileName; // GetProfileName() 
		int32 fCRDType; // GetCRDType() 
		PMString fCRDName; // GetCRDName() 
		int32 fIntent; // GetIntent() 
		int32 fSpotOverPrint; // GetSpotOverPrint() 
		bool16 fPrintWYSIWYGGridsGuides; // GetPrintWYSIWYGGridsGuides() 
		bool16 fCJKFilterContent; // GetCJKFilterContent(void) 
		bool16 fCJKPrintText; // GetCJKPrintText() 
		bool16	fCJKPrintPageItems; // GetCJKPrintPageItems() 
		bool16	fCJKPrintLayoutGrids; // GetCJKPrintLayoutGrids() 
		bool16	fCJKPrintFrameGrids; // GetCJKPrintFrameGrids() 
		bool16	fCJKOnlyPrintFrameGridWhenEmpty; // GetCJKOnlyPrintFrameGridWhenEmpty() 
		int32	fCJKPrintFrameGridView; // GetCJKPrintFrameGridView() 
		PMReal fCJKFrameGridStrokeWeight; // GetCJKFrameGridStrokeWeight() 
		PMReal fCJKLayoutGridStrokeWeight; // GetCJKLayoutGridStrokeWeight()  
		bool16 fCyanPrintInk; // GetCyanPrintInk() 
		PMReal fCyanFrequency; // GetCyanFrequency() 
		PMReal fCyanAngle; // GetCyanAngle() 
		bool16 fMagentaPrintInk; // GetMagentaPrintInk() 
		PMReal fMagentaFrequency; // GetMagentaFrequency() 
		PMReal fMagentaAngle; // GetMagentaAngle() 
		bool16 fYellowPrintInk; // GetYellowPrintInk() 
		PMReal fYellowFrequency; // GetYellowFrequency() 
		PMReal fYellowAngle; // GetYellowAngle() 
		bool16 fBlackPrintInk; // GetBlackPrintInk() 
		PMReal fBlackFrequency; // GetBlackFrequency() 
		PMReal fBlackAngle; // GetBlackAngle() 
		PMReal fSpotFrequency; // GetSpotFrequency() 
		PMReal fSpotAngle; // GetSpotAngle() 
		UID fFlattenerStyleUID; // GetFlattenerStyleUID() 
		PMString fFlattenerStyleName; // GetFlattenerStyleName() 
		bool16 fIgnoreSpreadOverrides; // GetIgnoreSpreadOverrides() 
		int32 fScope; // GetScope() 
		//uchar* GetPaperSizeSelector(uint32 &outSize)  // NOTE!!! Caller is responsible for delete[]-ing the return value!!!
		//IGenericSettings* GetSettings( const  IPrintDialogData* pDlgData,
	};

	/** Strucure that stores all of the data you can "Get" from IPrintDeviceInfo.
	 *	@see IPrintDeviceInfo
	 */
	struct PrintDeviceInfoStruct
	{
		PMString fDefaultPrinterName; // GetDefaultPrinterName;
		K2Vector<PMString> fDevices; // GetNumDevices,  GetNthDevice(const int32 index), GetDeviceIndex(const PMString& deviceName)
        K2Vector<PMString> fPPDModelNames; // GetNumPPDNames, GetNthPPDModelName(const int32 index), GetPPDIndexFromModelName(const PMString& ppdModelName)
		K2Vector<PMString> fPPDFileNames; // GetNthPPDFileName(const int32 index), GetPPDIndexFromFileName(const PMString& ppdFileName)
		K2Vector<PMString> fPaperSizes; // GetNumPaperSizes, GetNthPaperSize(const int32 index), GetPaperSizeIndex(const PMString& paperSizeName) 
		//PMString GetPaperSizeName(const PMRect& paperSizeRect, const PMRect& imageableAreaRect = PMRect()) 
		//PMRect GetPaperSize(const int32 index = 0) 	// index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		//PMRect GetImageablePaperSize(const int32 index = 0) 	// index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		//uchar *GetPaperSizeSelector(uint32 &outSize, const int32 index = 0) 	// index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		bool16 fDeviceSupportsCustomPaperSizes; // GetDeviceSupportsCustomPaperSizes()
		bool16 fDeviceSupportsCustomPaperTransverse; // GetDeviceSupportsCustomPaperTransverse() 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperWidthRange; // GetDeviceCustomPaperWidthRange(PMReal &outMinWidth, PMReal &outMaxWidth) 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperHeightRange; // GetDeviceCustomPaperHeightRange(PMReal &outMinHeight, PMReal &outMaxHeight) 
		K2Pair<PMReal, PMReal> fDeviceCustomPaperWidthOffsetRange; // GetDeviceCustomPaperWidthOffsetRange(PMReal &outMinOffset, PMReal &outMaxOffset) 
		bool16 fDeviceSupportsInRIPTrapping; // GetDeviceSupportsInRIPTrapping() 
		bool16 fDeviceSupportsInRIPSeparations; // GetDeviceSupportsInRIPSeparations() 
		bool16 fDeviceSupportsBinaryData; // GetDeviceSupportsBinaryData() 
		IPrintDeviceInfo::DefColorSpace fDeviceDefaultColorSpace; // GetDeviceDefaultColorSpace() 
		bool16 fDeviceSupportsColorSpace; // GetDeviceSupportsColorSpace(DefColorSpace colorSpace) 
		IPrintDeviceInfo::PSLevel fDevicePostScriptLevel; // GetDevicePostScriptLevel() 
		K2Vector<PMString> fCompositeFrequencies; // GetNumCompositeFrequencies() const = 0, GetNthCompositeFrequency(const int32 index) , int32 GetCompositeFrequencyIndex(const PMString& compFreqName) 
		PMReal fDeviceCompositeAngle; // GetDeviceCompositeAngle(PMString& resStr) 
		PMReal fDeviceCompositeFrequency; // GetDeviceCompositeFrequency(PMString& resStr) 
        K2Vector<PMString> fSeparationFrequencies; // int32 GetNumSeparationFrequencies()  PMString GetNthSeparationFrequency(const int32 index)  int32 GetSeparationFrequencyIndex(const PMString& sepFreqName) 
		int32 fDefaultSeparationFrequencyIndex; // GetDefaultSeparationFrequencyIndex() 
		PMReal fDeviceDefaultInkAngle[5]; // GetDeviceDefaultInkAngle(InkSelector inInkSelector) 
		PMReal fDeviceDefaultInkFrequency[5]; // GetDeviceDefaultInkFrequency(InkSelector inInkSelector) 
		PMReal fDeviceInkAngle[5]; // GetDeviceInkAngle(InkSelector inInkSelector, PMString& resStr) 
		PMReal fDeviceInkFrequency[5]; // GetDeviceInkFrequency(InkSelector inInkSelector, PMString& resStr) 
		bool16 fDeviceRequiresFlattener; // GetDeviceRequiresFlattener() 
		//ErrorCode GetPPDValues(PMString& keyIn, K2Vector<KeyValuePair<PMString, PMString> >& valueOut) 
		//ErrorCode GetPPDOptionKeys(PMString& keyIn, K2Vector<PMString>& keysOut) 
		//ErrorCode GetPPDOptionValue(PMString& keyIn, PMString& subKeyIn, PMString& subKeyTranslationOut, K2Vector<KeyValuePair<PMString, PMString> >& valueOut) 
	};
	
	/** Inspects a print preset style, and displays some of the settings to SNIPLOG.
	 * 	@param printStyle IN The print style (kPrStStyleBoss) to examine.
	 * 	@see kPrStStyleBoss
	 * 	@see IPrintData
	 *	@see IGenStyleLockInfo
	 *	@see IStringData
	 *	@see IPersistUIDData
	 *	@see IPrintDeviceInfo
	 * 	@return kSuccess on success, other ErrorCode otherwise.
	 */
	ErrorCode InspectPrintStyle(const UIDRef& printStyle);

	/** Add a new print preset style with the given name. 
	 * 	@param printStyleListMgr IN The IPrStStyleListMgr to which you want to add.
	 * 	@param newPrintStyleName IN The name of the print preset style to add. 
	 * 	@param newPrintStyle OUT The UIDRef of the new print preset style.
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see IPrStStyleListMgr::AddStyle
	*/
	ErrorCode AddPrintStyle(IPrStStyleListMgr* printStyleListMgr, const PMString& newPrintStyleName, UIDRef& newPrintStyle);

	/** Modify the name of an existing print preset style. 
 	 * 	@param printStyleListMgr IN The IPrStStyleListMgr that contains the print preset style to modify.
	 * 	@param printStyleIndex IN The index of the print preset style to modify. 
	 * 	@param newPrintStyleName IN The new name of the print preset style. 
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see IPrStStyleListMgr::SetNthStyleName
	*/
	ErrorCode ModifyPrintStyleName(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex, const PMString& newPrintStyleName);

	/** Modify the settings of an existing print preset style.
	 * 
	 * 	NOTE: IPrStStyleListMgr inherits from IGenEdtStlListMgr, unlike 
	 * 	ITrapStyleListMgr, so the EditNthStyle method  behaves a bit differently 
	 * 	between the two interfaces.  For instance, the parameters and the 
	 * 	return type are all different between IPrStStyleListMgr::EditNthStyle and
	 * 	ITrapStyleListMgr::EditNthStyle. And while the IPrStStyleListMgr::EditNthStyle
	 *  implementation does open a dialog box, ITrapStyleListMgr::EditNthStyle does not. 
	 * 
	 * 	@param printStyleListMgr IN The IPrStStyleListMgr that contains the print preset style to modify.
	 * 	@param printStyleIndex IN The index of the print preset style to modify. 
	 * 	@param modifiedPrintStyle OUT The UIDRef of the modified print style. 
	 * 		This will be the UIDRef of the modified style if a change was made. 
	 * 		If no change was made, this will be UIDRef::gNull.
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see IPrStStyleListMgr::EditNthStyle
	*/
	ErrorCode ModifyPrintStyle(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex, UIDRef& modifiedPrintStyle);

	/** Delete an existing print preset style. 
	 * 	@param printStyleListMgr IN The IPrStStyleListMgr from which you want to delete the print style.
	 * 	@param printStyleIndex IN The index of the print preset style to delete. 
	 * 	@return Status code.  kSuccess if success.  
	 * 	@see IPrStStyleListMgr::DeleteNthStyle
	*/
	ErrorCode DeletePrintStyle(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex);

	/** Utility method: Turn IPrintData into a PrintDataStruct.
	 * 	@param printData IN The IPrintData to examine.
	 * 	@return PrintDataStruct all filled out, unless printData is nil.
	 */
	PrintDataStruct GetPrintData(IPrintData* printData);

	/** Utility method: Turn IPrintDeviceInfo into a PrintDeviceInfoStruct.
	 * 	@param printDeviceInfo IN The IPrintDeviceInfo to examine.
	 * 	@return PrintDeviceInfoStruct all filled out, unless printDeviceInfo is nil.
	 */
	PrintDeviceInfoStruct GetPrintDeviceInfo(const IPrintDeviceInfo* printDeviceInfo);

};


/* InspectPrintStyle
*/
ErrorCode  SnpManipulatePrintStyles::InspectPrintStyle(const UIDRef& printStyle)
{
	const int BUFFER_SIZE = 128;
	ErrorCode result = kFailure;
	// NOTE: This is hardcoded - modify this to kFalse to turn off 
	// the verbose style description
	const bool16 kUseDescriptionFromStyle = kTrue;
	do
	{
		if (printStyle.ExistsInDB() == kFalse)
		{
			ASSERT_FAIL("invalid printStyle UIDRef");
			break;
		}
		IDataBase* db = printStyle.GetDataBase();

		InterfacePtr<IObjectModel> om(GetExecutionContextSession(), UseDefaultIID());
		ASSERT(om);
		ClassID styleClass = db->GetClass(printStyle.GetUID());
		const char* constPrintStyleClassName = om->GetIDName(styleClass);
		char printStyleClassName[BUFFER_SIZE] = {0};

		if (constPrintStyleClassName)
		{
			strncpy(printStyleClassName, constPrintStyleClassName, BUFFER_SIZE);
		}
		else
		{
			sprintf(printStyleClassName, "<0x%X>",styleClass.Get());
		}
		
		SNIPLOG("Examining PrintStyle: UID 0x%X, Class %s", 
				printStyle.GetUID().Get(), printStyleClassName);

		
		// the name of the style
		InterfacePtr<IStringData> nameStringData(printStyle, UseDefaultIID());
		ASSERT(nameStringData);
		PMString name = nameStringData->Get();
		 
		if (kUseDescriptionFromStyle)
		{
			InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
			if (workspace == nil) { ASSERT(workspace); break; }
			InterfacePtr<IPrStStyleListMgr> printStyleListMgr(workspace, UseDefaultIID());
			if (printStyleListMgr == nil) { ASSERT(printStyleListMgr); break; }
			int32 styleIndex = printStyleListMgr->GetStyleIndexByName(name);
			if (styleIndex < 0) { ASSERT(styleIndex >= 0); break; }
			PMString styleDescr;
			// NOTE: The resulting string styleDescr is really long!
			result = printStyleListMgr->GetNthStyleDescription(styleIndex, &styleDescr);
			if (result != kSuccess) { ASSERT(result == kSuccess); break; }
			SNIPLOG("%s", styleDescr.GetPlatformString().c_str());
		}
		else
		{
			// the name of the style
			SNIPLOG("[IStringData]");
			SNIPLOG(" Name: %s", name.GetPlatformString().c_str());

			// the print data
			InterfacePtr<IPrintData> printData(printStyle, UseDefaultIID());
			ASSERT(printData);
			PrintDataStruct sPrintData = this->GetPrintData(printData);
			SNIPLOG("[IPrintData]");
			SNIPLOG(" Printer: %s", sPrintData.fPrinter.GetPlatformString().c_str());
			SNIPLOG(" PPDName: %s", sPrintData.fPPDName.GetPlatformString().c_str());
			SNIPLOG(" PaperSizeName: %s", sPrintData.fPaperSizeName.GetPlatformString().c_str());
			SNIPLOG(" Copies: %d", sPrintData.fCopies);
			SNIPLOG(" PageRange: %s", sPrintData.fPageRange.GetPlatformString().c_str());
			
			// the printer device info (non-persistent)
			InterfacePtr<IPrintDeviceInfo> printDeviceInfo(printStyle, UseDefaultIID());
			ASSERT(printDeviceInfo);
			PrintDeviceInfoStruct sPrintDeviceInfo = this->GetPrintDeviceInfo(printDeviceInfo);
			SNIPLOG("[IPrintDeviceInfo]");
			SNIPLOG(" DefaultPrinterName: %s", sPrintDeviceInfo.fDefaultPrinterName.GetPlatformString().c_str());
		}

		SNIPLOG("---");

		// Edit/Delete locking
		InterfacePtr<IGenStyleLockInfo> styleLockInfo(printStyle, UseDefaultIID());
		ASSERT(styleLockInfo);
		bool16 isEditLocked = styleLockInfo->IsEditLocked();
		bool16 isDeleteLocked = styleLockInfo->IsDeleteLocked();
		bool16 isNameLocked = styleLockInfo->IsNameLocked();
		SNIPLOG("[IGenStyleLockInfo]");
		SNIPLOG(" isEditLocked: %s", (isEditLocked ? "true":"false"));
		SNIPLOG(" isDeleteLocked: %s", (isDeleteLocked ? "true":"false"));
		SNIPLOG(" isNameLocked: %s", (isNameLocked ? "true":"false"));
		
		// print client items stream
		// (UID of a boss with IDBStreamData, probably kDBStreamReadBoss)
		InterfacePtr<IPersistUIDData> printClientItemsData(printStyle, IID_IPRINTCLIENTITEMSUID);
		ASSERT(printClientItemsData);
		UIDRef printClientItemsUIDRef(db, printClientItemsData->GetUID());
		ClassID printClientItemsClass = db->GetClass(printClientItemsData->GetUID());
		const char* constClassName = om->GetIDName(printClientItemsClass);
		char className[BUFFER_SIZE] = {0};
		
		if (constClassName)
		{
			strncpy(className, constClassName, BUFFER_SIZE);
		}
		else
		{
			sprintf(className, "<0x%X>", printClientItemsClass.Get());
		}
        
		SNIPLOG("[IPersistUIDData(IID_IPRINTCLIENTITEMSUID)]");
		SNIPLOG(" UID: 0x%X",printClientItemsUIDRef.GetUID().Get());
		SNIPLOG(" ClassID: %s", className);

		// if we got here, then it's a success
		result = kSuccess;
	} while (false);
	return result;
}

/* AddPrintStyle
*/
ErrorCode SnpManipulatePrintStyles::AddPrintStyle(IPrStStyleListMgr* printStyleListMgr, const PMString& newPrintStyleName, UIDRef& newPrintStyle)
{
	ErrorCode status = kFailure;
	if (printStyleListMgr != nil)
	{
		PMString nonConstNewPrintStyleName(newPrintStyleName);
		status = printStyleListMgr->AddStyle(nonConstNewPrintStyleName);
		if (status == kSuccess)
		{
			int32 printStyleIndex = printStyleListMgr->GetStyleIndexByName(newPrintStyleName);
			newPrintStyle = printStyleListMgr->GetNthStyleRef(printStyleIndex);
			ASSERT(newPrintStyle.ExistsInDB());
		}
		else
		{
			newPrintStyle = UIDRef::gNull; 
			SNIPLOG("AddPrintStyle (\"%s\") failed - perhaps a style with the same name already exists?", newPrintStyleName.GetPlatformString().c_str());
		}
	}
	return status;

}

/* ModifyPrintStyleName
*/
ErrorCode SnpManipulatePrintStyles::ModifyPrintStyleName(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex, const PMString& newPrintStyleName)
{
	ErrorCode status = kFailure;
	do 
	{
		if (printStyleListMgr == nil)
		{
			ASSERT_FAIL("printStyleListMgr is nil");
			break;
		}
		// Set the style name using IPrStStyleListMgr.
		// NOTE: This updates the string in IStringData in the style boss. 
		PMString nonConstNewPrintStyleName(newPrintStyleName);
		status = printStyleListMgr->SetNthStyleName(printStyleIndex, 
													nonConstNewPrintStyleName);
		if (status != kSuccess)
		{
			// an error occurred - break out of loop
			break;
		}

		// In the case of print presets, we also need to modify 
		// the print style name in the print data boss
		// so that the next time the print dialog is brought displayed, 
		// the style name matches the name that you can get
		// from IPrintData::GetStyleName, not just the name from 
		// IStringData in the style boss.
		// [For internal reference: see bug report 1167857]
		UIDRef printStyle = printStyleListMgr->GetNthStyleRef(printStyleIndex);
		if (printStyle.ExistsInDB() == kFalse)
		{
			ASSERT_FAIL("something wrong with the print style!");
			status = kFailure;
			break;
		}
		InterfacePtr<IPrintData> printData(printStyle, UseDefaultIID());
		if (printData == nil)
		{
			ASSERT_FAIL("printData is nil!");
			status = kFailure;
			break;
		}
		// update the print data's style name
		printData->SetStyleName(newPrintStyleName);

	} while (false);
	return status;
}

/* ModifyPrintStyle
*/
ErrorCode SnpManipulatePrintStyles::ModifyPrintStyle(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex, UIDRef& modifiedPrintStyle)
{
	ErrorCode status = kFailure;
	if (printStyleListMgr != nil)
	{
		// don't make a new style - we can't change the style name from here...
		const bool16 makeNewStyle = kFalse;

        /* [bug 1166340] The call to printStyleListMgr->EditNthStyle 
			will give a benign assert:
			"No translation of key 'PrStEditStyleCmd' to English string"
			This bug has been noted, and will be fixed in a future release. 
			In the mean time, it is safe to skip this assert in the debug build.
		*/

		// This opens up a dialog to modify the style.
		bool32 changesApplied = printStyleListMgr->EditNthStyle(printStyleIndex, makeNewStyle);
		if (changesApplied)
		{
			modifiedPrintStyle = printStyleListMgr->GetNthStyleRef(printStyleIndex);
			ASSERT(modifiedPrintStyle.ExistsInDB());
		}
		else
		{
			// null UIDRef means no changes
			modifiedPrintStyle = UIDRef::gNull;
		}

		status = kSuccess;
	}
	return status;
}

/* DeletePrintStyle
*/
ErrorCode SnpManipulatePrintStyles::DeletePrintStyle(IPrStStyleListMgr* printStyleListMgr, const int32 printStyleIndex)
{
	ErrorCode status = kFailure;
	if (printStyleListMgr != nil)
	{
		// this opens up a dialog to modify the style.
		status = printStyleListMgr->DeleteNthStyle(printStyleIndex);
	}
	return status;

}





/* GetPrintData
*/
SnpManipulatePrintStyles::PrintDataStruct SnpManipulatePrintStyles::GetPrintData(IPrintData* printData)
{
	PrintDataStruct s;
	memset(&s, 0, sizeof(s));
	do
	{
		if (printData == nil)
		{
			ASSERT(printData);
			break;
		}

		s.fPrintRecordStream = printData->GetPrintRecordStream();
		s.fIsDefaultValues = printData->GetIsDefaultValues(); 
		s.fDeviceType = printData->GetDeviceType(); 
		s.fStyleName = printData->GetStyleName();
		s.fPrintTo = printData->GetPrintTo();
		s.fPrinter = printData->GetPrinter();
		s.fFileName = printData->GetFileName();
		s.fPPDName = printData->GetPPDName();
		s.fPPDFile = printData->GetPPDFile();
		s.fPSLangLevel = printData->GetPSLangLevel();
		s.fResolution = printData->GetResolution();
		s.fPaperSize = printData->GetPaperSize();
		s.fImageablePaperSize = printData->GetImageablePaperSize();
		s.fPaperSizeSelection = printData->GetPaperSizeSelection();
		s.fPaperSizeName = printData->GetPaperSizeName();
		s.fCustomPaperWidth = printData->GetCustomPaperWidth();
		printData->GetDeviceCustomPaperWidthRange(s.fDeviceCustomPaperWidthRange.first, s.fDeviceCustomPaperWidthRange.second);
		s.fCustomPaperHeight = printData->GetCustomPaperHeight();
		printData->GetDeviceCustomPaperHeightRange(s.fDeviceCustomPaperHeightRange.first, s.fDeviceCustomPaperHeightRange.second);
		s.fCustomPaperOffset = printData->GetCustomPaperOffset();
		printData->GetDeviceCustomPaperWidthOffsetRange(s.fDeviceCustomPaperWidthOffsetRange.first, s.fDeviceCustomPaperWidthOffsetRange.second);
		s.fCustomPaperGap = printData->GetCustomPaperGap();
		s.fPaperOrientation = printData->GetPaperOrientation();
		s.fPageOrientation = printData->GetPageOrientation();
		s.fCopies = printData->GetCopies();
		s.fCollate = printData->GetCollate();
		s.fReverseOrder = printData->GetReverseOrder();
		s.fFlipMode = printData->GetFlipMode();
		s.fNegative = printData->GetNegative();
		s.fPrintBlankPages = printData->GetPrintBlankPages();
		s.fPrintNonPrintingObjects = printData->GetPrintNonPrintingObjects();
		s.fWhichPages = printData->GetWhichPages();
		s.fPageRange = printData->GetPageRange();
		s.fPrintOption = printData->GetPrintOption();
		s.fSpreads = printData->GetSpreads();
		s.fOutputMode = printData->GetOutputMode();
		s.fPrintColorsInBlack = printData->GetPrintColorsInBlack();
		s.fShowSaveDialog = printData->GetShowSaveDialog();
		s.fCompositeAngle = printData->GetCompositeAngle();
		s.fCompositeFrequency = printData->GetCompositeFrequency();
		s.fCompositeScreenText = printData->GetCompositeScreenText(); 
		s.fSeparationScreenText = printData->GetSeparationScreenText();
		s.fScaleMode = printData->GetScaleMode();
		s.fProportional = printData->GetProportional(); 
		s.fXScale = printData->GetXScale();
		s.fYScale = printData->GetYScale();
		s.fPagePosition = printData->GetPagePosition(); 
		s.fTileThumbMode = printData->GetTileThumbMode(); 
		s.fTilingMode = printData->GetTilingMode(); 
		s.fTilingOverlap = printData->GetTilingOverlap(); 
		s.fNumberOfThumbsPerPage = printData->GetNumberOfThumbsPerPage(); 
		s.fImageData = printData->GetImageData(); 
		s.fImageDataFormat = printData->GetImageDataFormat(); 
		s.fOPIReplacement = printData->GetOPIReplacement(); 
		s.fOmitEPS = printData->GetOmitEPS(); 
		s.fOmitPDF = printData->GetOmitPDF(); 
		s.fOmitImages = printData->GetOmitImages(); 
		s.fFontDownload = printData->GetFontDownload(); 
		s.fDownloadPPDFonts = printData->GetDownloadPPDFonts(); 
		s.fPageMarkFile = printData->GetPageMarkFile(); 
		s.fMarkLineWeight = printData->GetMarkLineWeight(); 
		s.fPageMarkOffset = printData->GetPageMarkOffset(); 
		s.fCropMarks = printData->GetCropMarks(); 
		s.fPageInformation = printData->GetPageInformation(); 
		s.fColorBars = printData->GetColorBars(); 
		s.fRegistrationMarks = printData->GetRegistrationMarks(); 
		s.fBleedMarks = printData->GetBleedMarks(); 
		s.fUseDocumentBleed = printData->GetUseDocumentBleed(); 
		s.fBleedTop = printData->GetBleedTop(); 
		s.fBleedChain = printData->GetBleedChain(); 
		s.fBleedInside = printData->GetBleedInside(); 
		s.fBleedBottom = printData->GetBleedBottom(); 
		s.fBleedOutside = printData->GetBleedOutside(); 
		s.fIncludeSlug = printData->GetIncludeSlug(); 
		s.fTrappingMode = printData->GetTrappingMode(); 
		s.fSourceSpace = printData->GetSourceSpace(); 
		s.fProfileType = printData->GetProfileType(); 
		s.fProfileName = printData->GetProfileName(); 
		s.fCRDType = printData->GetCRDType(); 
		s.fCRDName = printData->GetCRDName(); 
		s.fIntent = printData->GetIntent(); 
		s.fSpotOverPrint = printData->GetSpotOverPrint(); 
		s.fPrintWYSIWYGGridsGuides = printData->GetPrintWYSIWYGGridsGuides(); 
		s.fCJKFilterContent = printData->GetCJKFilterContent(); 
		s.fCJKPrintText = printData->GetCJKPrintText(); 
		s.fCJKPrintPageItems = printData->GetCJKPrintPageItems(); 
		s.fCJKPrintLayoutGrids = printData->GetCJKPrintLayoutGrids(); 
		s.fCJKPrintFrameGrids = printData->GetCJKPrintFrameGrids(); 
		s.fCJKOnlyPrintFrameGridWhenEmpty = printData->GetCJKOnlyPrintFrameGridWhenEmpty(); 
		s.fCJKPrintFrameGridView = printData->GetCJKPrintFrameGridView(); 
		s.fCJKFrameGridStrokeWeight = printData->GetCJKFrameGridStrokeWeight(); 
		s.fCJKLayoutGridStrokeWeight = printData->GetCJKLayoutGridStrokeWeight();  
		s.fCyanPrintInk = printData->GetCyanPrintInk(); 
		s.fCyanFrequency = printData->GetCyanFrequency(); 
		s.fCyanAngle = printData->GetCyanAngle(); 
		s.fMagentaPrintInk = printData->GetMagentaPrintInk(); 
		s.fMagentaFrequency = printData->GetMagentaFrequency(); 
		s.fMagentaAngle = printData->GetMagentaAngle(); 
		s.fYellowPrintInk = printData->GetYellowPrintInk(); 
		s.fYellowFrequency = printData->GetYellowFrequency(); 
		s.fYellowAngle = printData->GetYellowAngle(); 
		s.fBlackPrintInk = printData->GetBlackPrintInk(); 
		s.fBlackFrequency = printData->GetBlackFrequency(); 
		s.fBlackAngle = printData->GetBlackAngle(); 
		s.fSpotFrequency = printData->GetSpotFrequency(); 
		s.fSpotAngle = printData->GetSpotAngle(); 
		s.fFlattenerStyleUID = printData->GetFlattenerStyleUID();
		s.fFlattenerStyleName = printData->GetFlattenerStyleName(); 
		s.fIgnoreSpreadOverrides = printData->GetIgnoreSpreadOverrides(); 
		s.fScope = printData->GetScope(); 
	} while (false);
	return s;
}

/* GetPrintDeviceInfo
*/
SnpManipulatePrintStyles::PrintDeviceInfoStruct SnpManipulatePrintStyles::GetPrintDeviceInfo(const IPrintDeviceInfo* printDeviceInfo)
{
	PrintDeviceInfoStruct s;
	memset(&s, 0, sizeof(s));
	do
	{
		if (printDeviceInfo == nil)
		{
			ASSERT(printDeviceInfo);
			break;
		}
		int32 i = 0, n = 0;
		s.fDefaultPrinterName = printDeviceInfo->GetDefaultPrinterName();
		
		s.fDevices.clear();
		n = printDeviceInfo->GetNumDevices();
		for (i = 0; i < n; i++)
			s.fDevices.push_back(printDeviceInfo->GetNthDevice(i));
		
		s.fPPDModelNames.clear();
		n = printDeviceInfo->GetNumPPDNames();
        for (i = 0; i < n; i++)
			s.fPPDModelNames.push_back(printDeviceInfo->GetNthPPDModelName(i));
		
		s.fPPDFileNames.clear();
		for (i = 0; i < n; i++)
            s.fPPDFileNames.push_back(printDeviceInfo->GetNthPPDFileName(i));
		
		s.fPaperSizes.clear();
		n = printDeviceInfo->GetNumPaperSizes();
		for (i = 0; i < n; i++)
			s.fPaperSizes.push_back(printDeviceInfo->GetNthPaperSize(i));

		s.fDeviceSupportsCustomPaperSizes = printDeviceInfo->GetDeviceSupportsCustomPaperSizes();
		s.fDeviceSupportsCustomPaperTransverse = printDeviceInfo->GetDeviceSupportsCustomPaperTransverse();
		printDeviceInfo->GetDeviceCustomPaperWidthRange(s.fDeviceCustomPaperWidthRange.first, s.fDeviceCustomPaperWidthRange.second);
		printDeviceInfo->GetDeviceCustomPaperHeightRange(s.fDeviceCustomPaperHeightRange.first, s.fDeviceCustomPaperHeightRange.second);
		printDeviceInfo->GetDeviceCustomPaperWidthOffsetRange(s.fDeviceCustomPaperWidthOffsetRange.first, s.fDeviceCustomPaperWidthOffsetRange.second);
		s.fDeviceSupportsInRIPTrapping = printDeviceInfo->GetDeviceSupportsInRIPTrapping();
		s.fDeviceSupportsInRIPSeparations = printDeviceInfo->GetDeviceSupportsInRIPSeparations(); 
		s.fDeviceSupportsBinaryData = printDeviceInfo->GetDeviceSupportsBinaryData(); 
		s.fDeviceDefaultColorSpace = printDeviceInfo->GetDeviceDefaultColorSpace(); 
		s.fDeviceSupportsColorSpace = printDeviceInfo->GetDeviceSupportsColorSpace(s.fDeviceDefaultColorSpace); 
		s.fDevicePostScriptLevel = printDeviceInfo->GetDevicePostScriptLevel(); 
		
		n = printDeviceInfo->GetNumCompositeFrequencies();
		s.fCompositeFrequencies.clear();
		for (i = 0; i < n; i++)
			s.fCompositeFrequencies.push_back(printDeviceInfo->GetNthCompositeFrequency(i)); 
		
		PMString dummy;
		s.fDeviceCompositeAngle = printDeviceInfo->GetDeviceCompositeAngle(dummy); 
		s.fDeviceCompositeFrequency = printDeviceInfo->GetDeviceCompositeFrequency(dummy); 

		n = printDeviceInfo->GetNumSeparationFrequencies();
		s.fSeparationFrequencies.clear();
		for (i = 0; i < n; i++)
			s.fSeparationFrequencies.push_back(printDeviceInfo->GetNthSeparationFrequency(i));
		
		s.fDefaultSeparationFrequencyIndex = printDeviceInfo->GetDefaultSeparationFrequencyIndex(); 

		for (i = IPrintDeviceInfo::kCyan; i <= IPrintDeviceInfo::kSpot; i++)
			s.fDeviceDefaultInkAngle[i] = printDeviceInfo->GetDeviceDefaultInkAngle((IPrintDeviceInfo::InkSelector)i);
		
		for (i = IPrintDeviceInfo::kCyan; i <= IPrintDeviceInfo::kSpot; i++)
			s.fDeviceDefaultInkFrequency[i] = printDeviceInfo->GetDeviceDefaultInkFrequency((IPrintDeviceInfo::InkSelector)i);
		
		for (i = IPrintDeviceInfo::kCyan; i <= IPrintDeviceInfo::kSpot; i++)
			s.fDeviceInkAngle[i] = printDeviceInfo->GetDeviceInkAngle((IPrintDeviceInfo::InkSelector)i, dummy);
		
		for (i = IPrintDeviceInfo::kCyan; i <= IPrintDeviceInfo::kSpot; i++)
			s.fDeviceInkFrequency[i] = printDeviceInfo->GetDeviceInkFrequency((IPrintDeviceInfo::InkSelector)i, dummy);

		s.fDeviceRequiresFlattener = printDeviceInfo->GetDeviceRequiresFlattener(); 
		
	} while (false);
	return s;
}

// --------------------------------- SnippetRunner framework hook ---------------------------------------------------

/** Makes the snippet SnpTemplate available to the SnippetRunner framework.

  	@ingroup sdk_snippet_run

 */
class _SnpRunnerManipulatePrintStyles : public SnpRunnable
{
	public:
		/** This constructor describes your snippet to the framework.
		 */
		_SnpRunnerManipulatePrintStyles();

		/** Destructor.
		 */
		virtual			~_SnpRunnerManipulatePrintStyles();

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
_SnpRunnerManipulatePrintStyles::_SnpRunnerManipulatePrintStyles() : SnpRunnable("ManipulatePrintStyles")
{
	this->SetDescription("Inspects, adds, modifies and deletes print styles");
	this->SetPreconditions("None");
	this->SetCategories("sdk_snippet, sdk_print");
}

/* Destructor.
*/
_SnpRunnerManipulatePrintStyles::~_SnpRunnerManipulatePrintStyles()	
{
}

/* Check if your preconditions are met.
*/
bool16  _SnpRunnerManipulatePrintStyles::CanRun(ISnpRunnableContext* runnableContext)
{
	return kTrue;
}

/* Set up the call to your operation(s).
*/
ErrorCode _SnpRunnerManipulatePrintStyles::Run(ISnpRunnableContext* runnableContext)
{
	ErrorCode status = kCancel;

	do
	{
		InterfacePtr<IWorkspace> workspace(GetExecutionContextSession()->QueryWorkspace());
		if (workspace == nil)
		{
			ASSERT_FAIL("workspace is nil");
			break; // out of do-while
		}
		InterfacePtr<IPrStStyleListMgr> printStyleListMgr(workspace, UseDefaultIID());
		if (printStyleListMgr == nil)
		{
			ASSERT_FAIL("printStyleListMgr is nil");
			break; // out of do-while
		}

		// Declare variables to use for SnpManipulatePrintStyles
		SnpManipulatePrintStyles instance;
		UIDRef printStyle = UIDRef::gNull;
		int32 printStyleIndex = -1;
		PMString newPrintStyleName = "";
		K2Vector<PMString> printStyleNames;

		// Use IParameterUtils to prompt for parameters
		Utils<ISnipRunParameterUtils> parameterUtils;
		K2Vector<PMString> choices;
		int32 defaultChoice;

		choices.clear();
		enum { kInspect, kAdd, kModifyName, kModify, kDelete };
		choices.clear();
		choices.push_back("Inspect print preset");
		choices.push_back("Add new print preset"); // no need to select one below
		choices.push_back("Modify name of print preset");
		choices.push_back("Modify print preset");
		choices.push_back("Delete print preset");
		PMString prompt("Select an operation", PMString::kEncodingASCII);
		defaultChoice = 0;
		/* --- STEP 1A: Decide which operation to perform --- */
		int32 opChoice = parameterUtils->GetChoice(prompt, choices, defaultChoice);
		if (parameterUtils->WasDialogCancelled() == kTrue)
		{
			status = kCancel;
			break;
		}
		SNIPLOG("Selected operation: %s", choices[opChoice].GetPlatformString().c_str());

        if (opChoice != kAdd)
		{
			/* --- STEP 1B: Choose a print preset style --- */
			printStyleNames.clear();
			int32 numStyles = printStyleListMgr->GetNumStyles();
			for (int32 i = 0; i < numStyles ; i++)
			{
				PMString styleName = "";
				status = printStyleListMgr->GetNthStyleName(i, &styleName);
				if (status == kSuccess)
				{
					printStyleNames.push_back(styleName);
				}
				else
				{
					SNIPLOG("Problem getting print style index %d", i);
					break;
				}
			}
			if (status != kSuccess)
			{
				status = kCancel;
				break;
			}
	
			prompt = PMString("Select a print style", PMString::kEncodingASCII);
			defaultChoice = 0;
			printStyleIndex = parameterUtils->GetChoice(prompt, printStyleNames, defaultChoice);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break;
			}
			printStyle = printStyleListMgr->GetNthStyleRef(printStyleIndex);
			SNIPLOG("Selected print style:\n%s", printStyleNames[printStyleIndex].GetPlatformString().c_str());
		}

		if (opChoice == kAdd || opChoice == kModifyName)
		{
			/* --- STEP 1B for kAdd/kModifyName : specify a new print style name --- */
			prompt = PMString("Specify a name for the print style", PMString::kEncodingASCII);
			PMString defaultName;
			if (printStyleIndex != -1)
			{
				defaultName = printStyleNames[printStyleIndex];
				// defaultName != "!"; // clang warning: unused result from inequality test
			}
			else
			{
				defaultName = PMString("NewPrintStyle", PMString::kEncodingASCII);
			}
			
			newPrintStyleName = parameterUtils->GetPMString(prompt, defaultName);
			if (parameterUtils->WasDialogCancelled() == kTrue)
			{
				status = kCancel;
				break; // out of do-while
			}
			SNIPLOG("Specified new print style name:\n%s", newPrintStyleName.GetPlatformString().c_str());
		}

		/* STEP 2: Perform the chosen operation */
		switch (opChoice)
		{
		case kInspect:
			{
				// inspect a print style
				status = instance.InspectPrintStyle(printStyle);
			}
			break;
		case kAdd:
			{
				// add a new print style
				UIDRef newPrintStyle = UIDRef::gNull;
				status = instance.AddPrintStyle(printStyleListMgr, newPrintStyleName, newPrintStyle);
				if (status == kSuccess)
					SNIPLOG("New print style added: UID 0x%X, \"%s\"", 
							newPrintStyle.GetUID().Get(), newPrintStyleName.GetPlatformString().c_str());
			}
			break;
		case kModifyName:
			{
				// modify the name of the print style
				status = instance.ModifyPrintStyleName(printStyleListMgr, printStyleIndex, newPrintStyleName);
				if (status == kSuccess)
					SNIPLOG("Print style name modified: UID 0x%X, old name = \"%s\", new name = \"%s\"", 
							printStyle.GetUID().Get(),
							printStyleNames[printStyleIndex].GetPlatformString().c_str(),
							newPrintStyleName.GetPlatformString().c_str());
			}
			break;
		case kModify:
			{
				// modify the print style
				UIDRef modifiedPrintStyle = UIDRef::gNull;
				status = instance.ModifyPrintStyle(printStyleListMgr, printStyleIndex, modifiedPrintStyle);
				if (modifiedPrintStyle.ExistsInDB())
				{
					SNIPLOG("Print style modified: UID 0x%X, \"%s\"", 
							printStyle.GetUID().Get(),
							printStyleNames[printStyleIndex].GetPlatformString().c_str());
				}
				else
				{
					SNIPLOG("Print style \"%s\" left unchanged", 
							printStyleNames[printStyleIndex].GetPlatformString().c_str());
				}
			}
			break;
		case kDelete:
			{
				// delete a print style
				status = instance.DeletePrintStyle(printStyleListMgr, printStyleIndex);
				if (status == kSuccess)
					SNIPLOG("Print style deleted: UID 0x%X, \"%s\"", 
							printStyle.GetUID().Get(),
							printStyleNames[printStyleIndex].GetPlatformString().c_str());
			}
			break;
		default:
			ASSERT_FAIL("Invalid operation choice");
			break;
		}
		
	} while (false);
	return(status);
}

/*	Declare an instance to register the snippet hook with the framework.
*/
static _SnpRunnerManipulatePrintStyles instance_SnpRunnerManipulatePrintStyles;
DEFINE_SNIPPET(_SnpRunnerManipulatePrintStyles) 	

// End, SnpManipulatePrintStyles.cpp

