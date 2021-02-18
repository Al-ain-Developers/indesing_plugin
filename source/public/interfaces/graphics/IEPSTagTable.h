//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IEPSTagTable.h $
//  
//  Owner: Scott Chai
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

#pragma once
#ifndef __IEPSTagTable__
#define __IEPSTagTable__

#include "EPSTagTableData.h"
#include "PMRect.h"
#include "PMString.h"

/**	This interface allows access EPSTagTable data. EPSTagTable is a collection of EPS Tag data.
	An EPS tag data is from the result of EPS comment parsing. EPS tag data contains information 
	from the EPS image, such as font, color usage, image replacement info. etc.
	The get methods query EPS resources.  They return kFailure if no more such resource is found,
	otherwise they return kSuccess. The item parameter specifies which block to get,
	0 the first one, 1, the second one, etc. 
*/
class IEPSTagTable : public IPMUnknown
{
	public:
		
		/**	Get font needed information - from %%DocumentNeededFonts comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) font needed
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetFontNeeded(uint32 item, PMString *name) = 0;
		/**	Get font supplied information - from %%DocumentSuppliedFonts comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) font supplied
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetFontSupplied(uint32 item, PMString *name) = 0;

		/**	Get proc set needed information - from %%DocumentNeededProcSets or %%DocumentNeededResource procset comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) proc set needed
			@param pProc OUT more information about the proc set - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetProcSetNeeded(uint32 item, PMString *name, ProcSetInfo *pProc) = 0;
		/**	Get proc set supplied information - from %%DocumentSuppliedProcSets or %%DocumentSuppliedResource procset comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) proc set supplied
			@param pProc OUT more information about the proc set - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetProcSetSupplied(uint32 item, PMString *name,ProcSetInfo *pProc) = 0;
		
		/**	Get NInk color information - from %ADBDocumentMultiInkColors comment. NOTE: InDesign currently
			does not support hifi colors.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) ink
			@param pHifi OUT more information about the ink - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetNInkColor(uint32 item, PMString *name,  MultiInkColor *pHifi) = 0;
		/**	Get ink information - from %ADBDocumentInks comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) ink
			@param pNeutralDensity OUT the neutral density for the ink
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetInk(uint32 item, PMString *name,  uint16 *pNeutralDensity) = 0;
		
		/**	Get the process colors used - from %%DocumentProcessColors comment.
			@param pCyan OUT kTrue if Cyan is used
			@param pMagenta OUT kTrue if Magenta is used
			@param pYellow OUT kTrue if Yello is used
			@param pBlack OUT kTrue if Black is used
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetProcessColorsUsed(bool8 *pCyan, bool8 *pMagenta, bool8 *pYellow, bool8 *pBlack) = 0;
		/**	Get the RGB spot colors - from %%RGBCustomColor comment.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) ink
			@param pRGB OUT more information about the ink - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetRGBCustomColor(uint32 item, PMString *name,  RGBApprox *pRGB) = 0;
		/**	Get the CMYK spot colors - from %%CMYKCustomColor comment. NOTE: tags are only produced 
			for CMYKCustomColors that appear in the %%DocumentCustomColors list.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) ink
			@param pCMYK OUT more information about the ink - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetCMYKCustomColor(uint32 item, PMString *name,  CMYKApprox *pCMYK) = 0;
		/** Get the CMYK process colors - from %%CMYKProcessColor (only if option turned on).
			NOTE: this option is not supported - don't use.
			@param item IN zero based iterant
			@param name OUT the name of the Nth (item) ink
			@param pCMYK OUT more information about the ink - see EPSTagTableData.h
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		*/
		virtual ErrorCode GetCMYKProcessColor(uint32 item, PMString *name,  CMYKApprox *pCMYK) = 0;

		/**	Get OPI image name - from %ALDImageFileName (OPI 1.3).
			NOTE: OPI tags are not created unless the option is turned on when importing.
			@param item IN zero based iterant
			@param fileName OUT the name of the Nth (item) image
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetImageFileName(uint32 item, PMString *fileName) = 0;
		/**	Get OPI image name - from %ImageFileName (OPI 2.0).
			NOTE: OPI tags are not created unless the option is turned on when importing.
			@param item IN zero based iterant
			@param fileName OUT the name of the Nth (item) image
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetImage2FileName(uint32 item, PMString *fileName) = 0;
		/**	Get whether file has DCS plates. True if %%CyanPlate (DCS 1.0) or %%PlateFile (DCS 2.0) was seen.
			@param item IN zero based iterant
			@param bHasDCSPlates OUT kTrue if DCS plates found, kFalse otherwise
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetHasDCSPlates(uint32 item, bool8 *bHasDCSPlates) = 0;
		/**	Get DCS plate file information - from %%CyanPlate (DCS 1.0) or %%PlateFile (DCS 2.0 - multi file).
			@param item IN zero based iterant
			@param plateName OUT plate name found
			@param fileName OUT plate file name found
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetDCSPlateFile(uint32 item, PMString *plateName, PMString *fileName) = 0;
		/**	Get DCS plate file information - from %%PlateFile (DCS 2.0 - single file).
			@param item IN zero based iterant
			@param plateName OUT plate name found
			@param offset OUT plate offset
			@param length OUT plate length
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetDCSPlateFile(uint32 item, PMString *plateName, uint32 *offset, uint32 *length) = 0;
				
		/**	Get the bounding box for the EPS - from the %%BoundingBox comment.
			@param item IN zero based iterant
			@param imageBounds OUT the bounding box rect
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetImageBounds(uint32 item, PMRect& imageBounds) = 0;
		/**	Get the creator - from %%Creator comment.
			@param item IN zero based iterant
			@param creator OUT the creator string 
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetCreator(uint32 item, PMString *creator) = 0;
		/**	Get the language level - from %%LanguageLevel comment
			@param item IN zero based iterant
			@param langLevel OUT the language level
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetLanguageLevel(uint32 item, uint16 *langLevel) = 0;
		/**	Get the document data - from %%DocumentData comment.
			@param item IN zero based iterant
			@param docData OUT the document data string
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetDocumentData(uint32 item, PMString *docData) = 0;
		/**	Get image data information - from %%ImageData comment.
			@param item IN zero based iterant
			@param imageData OUT more information about the image data - see EPSTagTableData.h
			@param dataStart OUT the data start marker string
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetImageData(uint32 item, ImageDataData *imageData, PMString *dataStart) = 0;
		/**	Get image data information - from %ArchImageData comment.
			@param item IN zero based iterant
			@param imageData OUT more information about the image data - see EPSTagTableData.h
			@param dataStart OUT the data start marker string
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetArchImageData(uint32 item, ImageDataData *imageData, PMString *dataStart) = 0;
		/**	Get the contains XMP string - from %ADO_ContainsXMP comment.
			@param item IN zero based iterant
			@param containsXMP OUT the contains XMP string (i.e. NoMain, MainFirst or MainLast)
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetContainsXMP(uint32 item, PMString *containsXMP) = 0;

		/**	OBSOLETE. Use GetPhotoShopClipData with std::string instead
			Get the Photoshop clipping data - data between %BeginPhotoshop and %EndPhotoshop comments.
			@param item IN zero based iterant
			@param pPSClipData OUT the clipping data
			@param pPSClipDataSize OUT the clipping data size
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetPhotoShopClipData(uint32 item, PMString *pPSClipData, uint32 *pPSClipDataSize) = 0;

		/**	File matching method for file replacement.  Caller will be able to find the matching file name
			given the file name (such as DCS plate file and OPI image file) in the original EPS file.
			@param fileToFind IN the file to find
			@param fileFound OUT the matching name
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		*/
		virtual ErrorCode MatchFile(const PMString &fileToFind, PMString *fileFound ) = 0;

		/** Append data to the tag table - NOTE: This method should
			only be called by code internal to the EPSImport plugin - don't use.
		*/
		virtual void AppendTagData(int16 tag, 
					int32 DataSize = 0, 
					void * Data = nil, 
					int32 varibleData1Size = 0, 
					void * varibleData1 = nil, 
					int32 varibleData2Size = 0, 
					void * varibleData2 = nil 
					) = 0;
		/** Reset the tag table - NOTE: This method should
			only be called by code internal to the EPSImport plugin - don't use.
		*/
		virtual void Reset(void) = 0; 

		/**	Get the Photoshop clipping data - data between %BeginPhotoshop and %EndPhotoshop comments.
			@param item IN zero based iterant
			@param pPSClipData OUT the clipping data
			@param pPSClipDataSize OUT the clipping data size
			@return ErrorCode - kSuccess if successful, kFailure otherwise
		 */
		virtual ErrorCode GetPhotoShopClipData(uint32 item, std::string *pPSClipData, uint32 *pPSClipDataSize) = 0;
};


#endif