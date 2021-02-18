//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintDeviceInfo.h $
//  
//  Owner: Michael Easter
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

#ifndef __IPrintDeviceInfo__
#define __IPrintDeviceInfo__

#if PRAGMA_ONCE
#pragma once
#endif

#ifdef MACINTOSH
#define OSX_HACK
#endif

#include "PMRect.h"
#include "PrintID.h"
#include "K2Vector.h"
#include "KeyValuePair.h"

class PMReal;
class IOutputPages;

//========================================================================================
// CLASS IPrintDeviceInfo
//========================================================================================

/** Helper class with access to information about the currently targetted printer.
	When using this interface, the first thing called should be the Begin method.
	The End method should be called when finished.
	@see IPrintData
*/
class IPrintDeviceInfo : public IPMUnknown
{
public:
	/** Default enum.
	*/
	enum { kDefaultIID = IID_IPRINTDEVICEINFO };

	/** PrintDeviceInfo must be bracketed by Begin/End - this call tells whether we are 
		in between a Begin/End construct.
		@return bool16 kTrue if there is a print session active, kFalse otherwise
	*/
	virtual bool16 IsPrintSessionActive() const = 0;
	
	/** Start a print session.
		@param initPPDList IN whether to initialize the PPD list or not
	*/
	virtual void Begin(bool16 initPPDList = kTrue) = 0;
	/** End the print session.
	*/
	virtual void End() = 0;
	
	/** Used when accessing the platform print or page setup dialogs through ProcessPlatformPrintDialog.
	*/
	enum SetupDialogType {
		/** Access printer setup dialog
		*/
		kPrinterSetup,
		/** Access the page setup dialog (Mac only)
		*/
		kPageSetup
	};

	/**	Access the platform print setup or page setup dialog - calls the system printer driver's dialogs.
		@param dialogType IN which dialog to access
		@param iOutputPages IN pointer to IOutputPages - if supplied will attempt to match bounds of pages 
		with print record page sizes. May be nil.
	*/
	virtual ErrorCode ProcessPlatformPrintDialog(SetupDialogType dialogType, IOutputPages *iOutputPages = nil) = 0;

	/**	Called when printers change to update PrintData.
		If bUsePrintData is true, the newPrinterStr and newPPDStr are ignored,
						and only the print record in the PrintData is used.
		If newPrinterStr == "kPrepress File", checks newPPDStr.
					If newPPDModelStr == "kDevice Independent", inits for Prepress
					otherwise inits to PPD file passed in newPPDFileStr.
		Else if newPrinterStr is empty, initializes using system default printer.
		Else inits to printer passed in newPrinterStr.

		@param newPrinterStr IN string containing the new printer - i.e. from IPrintData::GetPrinter()
		@param newPPDModelStr IN string containing the PPD - i.e. from IPrintData::GetPPDName()
		@param bUsePrintData IN If true, the newPrinterStr and newPPDStr are ignored, and only the print record in the PrintData is used.
		If false, newPrinterStr and newPPDStr are used as described.
		@param newPPDFileStr IN string containing the PPD file - i.e. from IPrintData::GetPPDFile()
		@return ErrorCode will return kSuccess if successful, an error return code otherwise
	 */
	virtual ErrorCode UpdatePrinterInfo(PMString& newPrinterStr, PMString& newPPDModelStr, bool16 bUsePrintData = kFalse, PMString newPPDFileStr = PMString()) = 0;

	/** Check to see if there is a default printer defined
		@return bool16 kTrue if default printer defined, kFalse otherwise
	*/
	virtual bool16 HasDefaultPrinter() const = 0;
	/** Return the name of the default printer, if one is defined.
		@return PMString containing the default printer name, if no default printer is defined, string will be empty
	*/
	virtual PMString GetDefaultPrinterName() const = 0;
	/** Check to see if the default printer is a PDFWriter. We do not allow printing to Acrobat PDFWriter.
		@return bool16 kTrue if default printer is a PDFWriter, kFalse otherwise
	*/
	virtual bool16 IsDefaultPrinterPDFWriter() const = 0;

	/** Get the number of printers on the system.
		@return int32 the number of printers on the system
	*/
	virtual int32 GetNumDevices() const = 0;
	/**	Get the name of the nth printer.
		@param index IN which printer to get
		@return PMString the name of the nth printer
	 */
	virtual PMString GetNthDevice(const int32 index) const = 0;
	/**	Given a printer name (i.e. IPrintData::GetPrinter()), get its index in the printer list.
		@param deviceName IN the printer name to find
		@return int32 the index of the given printer in the printer list, -1 if not in the list
	 */
	virtual int32 GetDeviceIndex(const PMString& deviceName) const = 0;
	
	/** Get the number of PPDs on the system.
		@return int32 the number of PPDs on the system
	*/
	virtual int32 GetNumPPDNames() const = 0;
	/**	Get the nth PPD model name. 
		@param index IN which index to get
		@return PMString contining the nth PPD model name
	 */
	virtual PMString GetNthPPDModelName(const int32 index) const = 0;
	/**	Get the nth PPD file name. 
		@param index IN which index to get
		@return PMString contining the nth PPD file name
	 */
	virtual PMString GetNthPPDFileName(const int32 index) const = 0;
	/**	Get the index of the given PPD model name.
		@param ppdModelName IN the PPD model name to find
		@return int32 the index into the list of PPDs for the given model name, -1 if not found
	 */
	virtual int32 GetPPDIndexFromModelName(const PMString& ppdModelName) const = 0;
	/**	Get the index of the given PPD file name.
		@param ppdFileName IN the PPD file name to find
		@return int32 the index into the list of PPDs for the given file name, -1 if not found
	 */
	virtual int32 GetPPDIndexFromFileName(const PMString& ppdFileName) const = 0;

	/** Get the number of paper sizes available.
		@return int32 the number of paper sizes available
	*/
	virtual int32 GetNumPaperSizes() const = 0;
	/**	Get the name of the nth paper size.
		@param index IN which paper size to get
		@return PMString containing the nth paper size name
	 */
	virtual PMString GetNthPaperSize(const int32 index) const = 0;
	/**	Get the index of the given paper size name.
		@param paperSizeName IN the paper size name to find
		@return int32 the index of the given paper size name in the paper size list
	 */
	virtual int32 GetPaperSizeIndex(const PMString& paperSizeName) const = 0;
	/**	Get the media paper size name out of the Print Record (print driver settings).
		Can be used as the parameter passed to GetPaperSizeName to determine media name.
		Will return an empty string if not printing to a printer, or if Custom or Defined
		by Driver paper setting is selected.
		@return PMString containing the media size name
	 */
	virtual PMString GetMediaSizeName() const = 0;
	/**	Given the media size name (from the PrintRecord), search for the name in the list that comes
		from the PPD. Alternative to using paper size and imageable area rects.
		@param mediaSizeName IN the name of the media to find  
		@return PMString the name of the paper size
	 */
	virtual PMString GetPaperSizeName(const PMString& mediaSizeName) const = 0;
	/**	Given the paper size rect, and the optional imageable area rect, find the paper size name.
		@param paperSizeRect IN the paper size rect to find
		@param imageableAreaRect IN the optional imageable area rect to further refine the search - i.e.
		the difference between finding Letter and Letter Small paper sizes
		@return PMString the name of the paper size
	 */
	virtual PMString GetPaperSizeName(const PMRect& paperSizeRect, const PMRect& imageableAreaRect = PMRect(), const PMString& paperSizeName = PMString()) const = 0;

	/**	Get the nth paper size rect.
		@param index IN the paper size rect to get - NOTE: index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		@return PMRect the rect of the paper size
	 */
	virtual PMRect GetPaperSize(const int32 index = 0) const = 0;
	/**	Get the nth imageable area rect.
		@param index the imageable area rect to get - NOTE: index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		@return PMRect the rect of the imageable area 
	 */
	virtual PMRect GetImageablePaperSize(const int32 index = 0) const = 0;
	/**	Get the paper size selector (a magic cookie) for the given index. Used in IPrintData Get/Set Paper Size Selector.
		Note: the caller is responsible for freeing the non-nil pointer returned, using delete[].
		@param outSize OUT size of the memory block allocated and passed back
		@param index IN which paper size selector to get - NOTE: index ignored if kPaperSizeDefinedByDriver or kPaperSizeDefinedByUser
		@return uchar pointer to memory block containing selector - NOTE: caller is responsible for freeing this memory!
	 */
	virtual uchar *GetPaperSizeSelector(uint32 &outSize, const int32 index = 0) const = 0;
	
	/** Does the current printer support custom paper sizes.
		@return bool16 kTrue if the current printer supports custom paper sizes, kFalse otherwise
	*/
	virtual bool16 GetDeviceSupportsCustomPaperSizes() const = 0;
	/** Does the current printer support transverse paper.
		@return bool16 kTrue if the current printer supports transverse paper, kFalse otherwise
	*/
	virtual bool16 GetDeviceSupportsCustomPaperTransverse() const = 0;
	/**	Get the custom paper width range for the printer. 
		@param outMinWidth OUT the minimum custom paper width supported
		@param outMaxWidth OUT the maximum custom paper width supported
	 */
	virtual void GetDeviceCustomPaperWidthRange(PMReal &outMinWidth, PMReal &outMaxWidth) const = 0;
	/**	Get the custom paper height range for the printer.
		@param outMinHeight OUT the minimum custom paper height supported
		@param outMaxHeight OUT the maximum custom paper height supported
	 */
	virtual void GetDeviceCustomPaperHeightRange(PMReal &outMinHeight, PMReal &outMaxHeight) const = 0;
	/**	Get the custom paper width offset range for the printer.
		@param outMinOffset OUT the minimum custom paper width offset supported
		@param outMaxOffset OUT the maximum custom paper width offset supported
	 */
	virtual void GetDeviceCustomPaperWidthOffsetRange(PMReal &outMinOffset, PMReal &outMaxOffset) const = 0;

	/** Get whether the current printer supports in RIP trapping.
		@return bool16 kTrue if the printer supports in RIP trapping, kFalse otherwise
	*/
	virtual bool16 GetDeviceSupportsInRIPTrapping() const = 0;
	/** Get whether the current printer supports in RIP separations.
		@return bool16 kTrue if the printer supports in RIP separations, kFalse otherwise
	*/
	virtual bool16 GetDeviceSupportsInRIPSeparations() const = 0;
	/** Get whether the current printer supports binary data.
		@return bool16 kTrue if the printer supports binary data, kFalse otherwise
	*/
	virtual bool16 GetDeviceSupportsBinaryData() const = 0;
	
	/** Default color spaces
	*/
	enum DefColorSpace {
		/** Gray color space
		*/
		kGray,
		/** RGB color space
		*/
		kRGB,
		/** CMYK color space
		*/
		kCMYK,
		/** Unchanged color space
		*/
		kUnchanged
	};

	/**	Get the default color space for the current printer.
		@return DefColorSpace enum value for the default color space
	 */
	virtual DefColorSpace GetDeviceDefaultColorSpace() const = 0;
	/**	Determine if the printer supports a given color space.
		@param colorSpace IN the color space to check
		@return bool16 kTrue if the printer supports the given color space, kFalse otherwise
	 */
	virtual bool16 GetDeviceSupportsColorSpace(DefColorSpace colorSpace) const = 0;
	
	/** PostScript level
	*/
	enum PSLevel {
		/** PostScript level unknown
		*/
		kPSLevel_Unknown,
		/** PostScript level 1
		*/
		kPSLevel_1,
		/** PostScript level 2
		*/
		kPSLevel_2,
		/** PostScript level 3
		*/
		kPSLevel_3
	};

	/** Is the current printer a PostScript printer?
		@return bool16 kTrue if the current printer is a PostScript device, kFalse otherwise
	*/
	virtual bool16 IsPostScriptDevice() const = 0;
	/** Does a non-PS device support behaving like a PS device by distilling (or "normalizing") the PS into
		PDF, then converting the PDF to the device's native format (usually bitmaps of some sort)?
		Notes: 1) This is currently only supported on Mac OS versions >= 10.3; 2) By definition this is
		mutually exclusive with IsPostScriptDevice - when one is true the other will be false. 
		@return bool16 kTrue if the current printer supports the normalize PostScript path, kFalse otherwise
	*/
	virtual bool16 DeviceSupportsNormalizedPostScript() const = 0;
	/** Get the PostScript level supported by the current printer.
		@return PSLevel enum of the highest PostScript level supported by the printer
	*/
	virtual PSLevel GetDevicePostScriptLevel() const = 0;
	
	/** Get the number of composite frequencies - This method has been depricated - don't use.
		@return int32 will always return 0
	*/
	virtual int32 GetNumCompositeFrequencies() const = 0;
	/**	Get the nth composite frequency - This method has been depricated - don't use.
		@param index IN this parameter is current ignored
		@return PMString will always return an empty string
	 */
	virtual PMString GetNthCompositeFrequency(const int32 index) const = 0;

	/**	Get the composite angle.
		@param resStr IN this parameter is current ignored
		@return PMReal the composite angle (ScreenAngle from PPD), or 45 if not found
	 */
	virtual PMReal GetDeviceCompositeAngle(PMString& resStr) const = 0;
	/**	Get the composite frequency.
		@param resStr IN this parameter is current ignored
		@return PMReal the composite angle (ScreenFreq from PPD), or 70 if not found
	 */
	virtual PMReal GetDeviceCompositeFrequency(PMString& resStr) const = 0;

	/**	Get the composite frequency index - This method has been depricated - don't use.
		@param compFreqName IN this parameter is currently ignored
		@return int32 will always return -1
	 */
	virtual int32 GetCompositeFrequencyIndex(const PMString& compFreqName) const = 0;
	
	/** Get the number of separation frequencies.
		@return int32 the number of separation frequencies
	*/
	virtual int32 GetNumSeparationFrequencies() const = 0;
	/**	Get the nth separation frequency.
		@param index IN which separation frequency to get
		@return PMString containing the nth separation frequency
	 */
	virtual PMString GetNthSeparationFrequency(const int32 index) const = 0;
	/**	Get the index of the given separation frequency.
		@param sepFreqName IN the separation frequency to find
		@return int32 the index of the given separation frequency, -1 if not found
	 */
	virtual int32 GetSeparationFrequencyIndex(const PMString& sepFreqName) const = 0;
	/**	Get the default separation frequency index.
		@return int32 the default separation frequency index
	 */
	virtual int32 GetDefaultSeparationFrequencyIndex() const = 0;
	
	/** Ink selector for retrieving frequency and angle information.
	*/
	enum InkSelector {
		/** Cyan
		*/
		kCyan,
		/** Magenta
		*/
		kMagenta,
		/** Yellow
		*/
		kYellow,
		/** Black
		*/
		kBlack,
		/** Spot
		*/
		kSpot
	};
	
	/**	Get the default ink angle for the given ink.
		@param inInkSelector IN which ink to get
		@return PMReal the default angle
	 */
	virtual PMReal GetDeviceDefaultInkAngle(InkSelector inInkSelector) const = 0;
	/**	Get the default ink frequency for the given ink.
		@param inInkSelector IN which ink to get
		@return PMReal the default frequency
	 */
	virtual PMReal GetDeviceDefaultInkFrequency(InkSelector inInkSelector) const = 0;
	
	/**	Get the ink angle for the given ink and separation screen string.
		@param inInkSelector IN which ink to get
		@param resStr IN the separation screen text string (i.e. IPrintData::GetSeparationScreenText())
		@return PMReal the ink angle
	 */
	virtual PMReal GetDeviceInkAngle(InkSelector inInkSelector, PMString& resStr) const = 0;
	/**	Get the ink frequency for the given ink and separation screen string.
		@param inInkSelector IN which ink to get
		@param resStr IN the separation screen text string (i.e. IPrintData::GetSeparationScreenText())
		@return PMReal the ink frequency
	 */
	virtual PMReal GetDeviceInkFrequency(InkSelector inInkSelector, PMString& resStr) const = 0;

	/**	Get whether the current printer requires the flattener.
		@return bool16 if the printer requires the flattener, kFalse otherwise
	 */
	virtual bool16 GetDeviceRequiresFlattener() const = 0;

	/**	PPD parsing - get PPD values.
		@param keyIn IN the key to look up
		@param valueOut OUT a K2Vector of key/value pairs for the given PPD key, where the first string is the text, second string is translation
		@return ErrorCode kSuccess if successful, kFailure otherwise
	 */
	virtual ErrorCode GetPPDValues(PMString& keyIn, K2Vector<KeyValuePair<PMString, PMString> >& valueOut) const = 0;
	/**	PPD parsing - get PPD option keys.
		@param keyIn IN the key to look up
		@param keysOut OUT a K2Vector of key strings to use as subKeyIn to GetPPDOptionValue()
		@return ErrorCode kSuccess if successful, kFailure otherwise
	 */
	virtual ErrorCode GetPPDOptionKeys(PMString& keyIn, K2Vector<PMString>& keysOut) const = 0;
	/**	PPD parsing - get PPD option value.
		@param keyIn IN the key to look up
		@param subKeyIn IN sub key to lookup - from GetPPDOptionKeys()
		@param subKeyTranslationOut OUT translation of the subKeyIn
		@param valueOut - K2Lookup of two strings, first string is the text, second string is translation
		@return ErrorCode kSuccess if successful, kFailure otherwise
	 */
	virtual ErrorCode GetPPDOptionValue(PMString& keyIn, PMString& subKeyIn, PMString& subKeyTranslationOut, K2Vector<KeyValuePair<PMString, PMString> >& valueOut) const = 0;
};

#endif // __IPrintDeviceInfo__

// End, IPrintDeviceInfo.h.
