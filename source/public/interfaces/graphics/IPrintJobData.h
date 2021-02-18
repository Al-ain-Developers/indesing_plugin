//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPrintJobData.h $
//  
//  Owner: DBerggren
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
//  
//  based on IUIDListData.h - for managing list of inks
//  
//========================================================================================

#pragma once
#ifndef __IPrintJobData__
#define __IPrintJobData__

#include "IPMUnknown.h"
#include "IInkResourceData.h"
#include "PrintID.h"
#include "K2Vector.h"
#include "IPathGeometry.h"
#include "BravoForwardDecl.h"
#include "PMRect.h"

class TrapZoneInfo;
class Font_Info;

/** Print Job Data that is collected in a gathering process
	is stored here to be passed to and shared with various
	print commands. This data is gathered in the PrintGatherDataCmd.
*/
class IPrintJobData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPRINTJOBDATA };

		/** get the ink list used in the print job
			@return pointer to IInkList used in the print job
			@see IInkList
		*/
		virtual IInkList*		GetInkList(void) const = 0;
		/** set the ink list used in the print job
			@param iInkList		IN pointer to IInkList used in the print job
			@see IInkList
		*/
		virtual void			SetInkList(IInkList *iInkList) = 0;

		// Ink Resource methods - to get/set IInkResourceData for each page
		/** insert an IInkResourceData into the list for a given page (the index)
			@param index		IN the page that the inks were gathered from. Note that 
			the index has to be the same as the index into IOutputPages.
			@param iInkRsrcData	IN pointer to IInkResourceData containing the inks
			that are used on the page.
			@see IInkResourceData
		*/
		virtual void			InkRsrcInsert(int32 index, IInkResourceData *iInkRsrcData) = 0;
 		/** remove an IInkResourceData from the list for a given page (the index)
			@param index		IN the index to remove from the list
		*/
		virtual void			InkRsrcRemove(int32 index) = 0;
 		/** clear all IInkResourceData pointers from the list 
		*/
		virtual void			InkRsrcClear(void) = 0;
		/** get the number of IInkResourceData pointers stored in the list
		*/
		virtual int32			InkRsrcLength(void) = 0;
		/** get the Nth IInkResourceData pointer out of the list.
			@param index	IN the index to retrieve
			@return a pointer to the given IInkResourceData, or nil if 
			one does not exist for the given index
			@see IInkResourceData
		*/
		virtual IInkResourceData *GetNthInkRsrcData(int32 index) const = 0;

		/** get whether a gradient paint server is used in the pub - print code
			will not download the gradient paint server procset if this is false
			see below for information about flagging gradient meshes
			@return	kTrue if gradient paint server is used, kFalse otherwise
		*/
		virtual bool16			GetGradientUsed() const = 0;
		/** set whether a gradient paint server is used in the pub - print code
			will not download the gradient paint server procset if this is false
			see below for information about flagging gradient meshes
			@param bGradientUsed	IN kTrue if gradient paint server is used, kFalse otherwise
		*/
		virtual void			SetGradientUsed(const bool16 bGradientUsed) = 0;

		/** get whether an image is used in the pub - print code
			will not download the image procset if this is false
			@return kTrue if an image is used in the job, kFalse otherwise
		*/
		virtual bool16			GetImagesUsed() const = 0;
		/** set whether an image is used in the pub - print code
			will not download the image procset if this is false
			@param bImagesUsed	IN kTrue if an image is used in the job, kFalse otherwise
		*/
		virtual void			SetImagesUsed(const bool16 bImagesUsed) = 0;

		/** get whether transparency is used in the pub 
			@return kTrue if XP used in job, kFalse otherwise
		*/
		virtual bool16			GetTransparencyUsedInJob() const = 0;
		/** get whether transparency is used on a particular page 
			@param whichPage	IN which page to check
			@return kTrue if XP used on that page, kFalse otherwise
		*/
		virtual bool16			GetTransparencyUsed(const int32 whichPage) const = 0;
		/** set whether transparency is used in the pub 
			@param xpPages	IN a K2Vector which XP info for each page in the job
		*/
		virtual void			SetTransparencyInfo(const K2Vector<int32>& xpPages) = 0;
		/** get the number of pages that have transparency in the job 
			@return number of page that have XP in the job
		*/
		virtual int32           NumberOfPagesWithTransparency() const = 0;

		// font collection methods
		/** Sometimes we care about the fonts that are supplied by the graphics within the document.
			For example, when placing a page from an imported INDD document, we may want to obtain a list
			of all the fonts in the document, including those within any vector graphics within said document.
			These fonts can then be stored in the IFontNames interface for the placed object.
			
			@param fontName [IN] the name of the graphic font.
		*/
		virtual void AppendGraphicSuppliedFontName(const PMString& fontName) = 0;

		/** Sometimes we care about the fonts that are supplied by the graphics within the document.
			For example, when placing a page from an imported INDD document, we may want to obtain a list
			of all the fonts in the document, including those within any vector graphics within said document.
			These fonts can then be stored in the IFontNames interface for the placed object.
			
			@return number of fonts supplied by graphics.
		*/
		virtual int32					NumGraphicSuppliedFonts() const = 0;

		/** Sometimes we care about the fonts that are supplied by the graphics within the document.
			For example, when placing a page from an imported INDD document, we may want to obtain a list
			of all the fonts in the document, including those within any vector graphics within said document.
			These fonts can then be stored in the IFontNames interface for the placed object.
			
			@param n [IN]: zero-based index of font to get
			@param fontName [OUT]: on return, will hold the name of the Nth graphic font.
		*/
		virtual void GetNthGraphicSuppliedFontName(int32 n, PMString& fontName) const = 0;

		/** get whether SVG Fonts is used on a particular page
		@param whichPage    IN which page to check
		@return kTrue if SVG fonts used on that page, kFalse otherwise
		*/
		virtual bool16 GetSVGFontsUsed(const int32 whichPage) const = 0;

		/** set whether SVG Fonts is used in the pub
		@param xpPages    IN a K2Vector which SVG fonts info for each page in the job
		*/
		virtual void SetSVGFontsInfo(const K2Vector<int32>& svgPages) = 0;

		/** append font information into the list
			@param fontInfo		IN a reference to a Font_Info class describing a font that
			is used in the job
		*/
		virtual void			AppendFontInfo(const Font_Info* fontInfo) = 0;
		/** get the number of Font_Info stored in the list
			@return number of fonts in the list
		*/
		virtual int32			NumFontInfo() const = 0;
		/** get the Nth Font_Info class from the list
			@param n			IN the index to get
			@return Font_Info class of the given index
		*/
		virtual Font_Info*		GetNthFontInfo(int32 n) const = 0;

		/** Get the number of missing fonts. These fonts are NOT included in the NumFontInfo() count.
			@return number of missing fonts.
		*/
		virtual int32			NumMissingFonts() const = 0;

		/** Get the name of the Nth missing font.
			@param n [IN]: zero-based index of font to get
			@param fontName [OUT]: on return, will hold the name of the Nth missing font.
		*/
		virtual void GetNthMissingFontName(const int32 n, PMString& fontName) const = 0;

		/** Add the name of a missing font.
			@param fontName[IN]: Name of the missing font.
		*/
		virtual void AppendMissingFontName(const PMString& fontName) = 0;

		// trap zone information
		/** insert information about trap zones for a page into the list
			@param index		IN the page that the trap zones apply
			@param pathList		IN a K2Vector of TrapZoneInfo pointers containing the
			trap zones for the page
		*/
		virtual void			TZPathsInsert(int32 index, K2Vector<TrapZoneInfo*> pathList) = 0;
		/** remove the trap zone information for a page from the list
			@param index		IN the page which to remove
		*/
		virtual void			TZPathsRemove(int32 index) = 0;
 		/** remove all trap zone information from the list
		*/
		virtual void			TZPathsClear(void) = 0;
 		/** get the number of trap zone pages in the list
			@return number of trap zone pages in list
		*/
		virtual int32			TZPathsLength(void) = 0;
		/** get the Nth trap zone information
			@param index	IN which page to retrieve
			@return a K2Vector of TrapZoneInfo pointers containing the trap zone
			information for that page
		*/
		virtual K2Vector<TrapZoneInfo*> GetNthTZPathsList(int32 index) const = 0;
		
		/** get whether a gradient mesh is used in the pub - print code
			will not download the gradient mesh procset if this is false
			@return kTrue if gradient mesh is used in the job, kFalse otherwise
		*/
		virtual bool16			GetGradientMeshUsed() const = 0;
		/** set whether a gradient mesh is used in the pub - print code
			will not download the gradient mesh procset if this is false
			@param bGradientMeshUsed	IN kTrue if gradient mesh is used in the job, kFalse otherwise
		*/
		virtual void			SetGradientMeshUsed(const bool16 bGradientMeshUsed) = 0;

		/** for a given page (the pageIndex), provide an optional page label string to be used. The
			page label appears in the page information printer marks, as well as the DSC comments.
			@param pageIndex	IN the page that you wish to override the page label. Note that 
			the pageIndex has to be the same as the index into IOutputPages.
			@param pageLabelStr	IN PMString containing alternate page label
		*/
		virtual void			AddPageLabelString(int32 pageIndex, const PMString& pageLabelStr) = 0;
		/** remove a PMString from the optional page label list for a given page (the pageIndex)
			@param pageIndex	IN the index (page) to remove from the list
		*/
		virtual void			RemovePageLabelString(int32 pageIndex) = 0;
		/** clear all PMStrings from the list of optional page label strings 
		*/
		virtual void			ClearPageLabelStrings(void) = 0;
		/** get the PMString to use as a page label string for the pageIndex page. If the string 
			is not present for a particular page, an empty string will be returned. If an empty 
			string is returned, the page label will be generated in the default manner.
			@param pageIndex	IN the index (page) to retrieve. Note that 
			the pageIndex has to be the same as the index into IOutputPages.
			@return a PMString containing the optional page label; returned string will be empty if 
			one does not exist for the given pageIndex. If empty, the page label will be generated
			in the default manner.
		*/
		virtual PMString		GetPageLabelString(int32 pageIndex) const = 0;

		/** Append a list of page items with 1 or more data links.
		
			@param links [IN]: A list of page items with links to append to the list encountered so far.
		*/
		virtual void AppendLinks(const UIDList& links) = 0;

		/** Get the list of page items with links used in this print job. Note that you will 
			need to query for the IDataLinkReference and/or IDataLinkListReference on each 
			element in the list to obtain the actual links.
			
			@return UIDList of links.
		*/
		virtual const UIDList& GetLinks(void) const = 0;

		// page gap information
		/** insert information about page gaps for a page into the list. This is used for 
			positioning vertical gutter marks if crop marks is on, to be used with page imposition. 
			The PMRect should have coordinates for the size of the gap between the imposed pages, 
			in the same coordinate space as the IOutputPages being used.
			@param page			IN the page that the gaps refer to
			@param pathList		IN a K2Vector of PMRects containing the
			gap sizes for the page, in the same coordinate space as IOutputPages page size.
		*/
		virtual void		PageGapsListInsertPage(int32 page, K2Vector<PMRect> vecPageGapsList) = 0;
		/** remove the gaps list information for a page from the list
			@param page			IN the page which to remove
		*/
		virtual void		PageGapsListRemovePage(int32 page) = 0;
 		/** remove all page gap information from the list
		*/
		virtual void		PageGapsListClear(void) = 0;
		/** get the page gaps information for a particular page. 
			@param page			IN which page to retrieve
			@return a K2Vector of PMRects containing the page gaps
			information for that page
		*/
		virtual K2Vector<PMRect> GetPageGapsListForPage(int32 page) const = 0;

};

/** TrapZoneInfo is the container for trap zone information for the pages
	in the publication. Used in the IPrintJobData interface.
*/
class TrapZoneInfo
{
public:
	typedef object_type data_type;

	/** constructor
		@param trapStyleName	IN the trap style name for this trap zone
		@param trapZonePath		IN the path of the zone
		@param offsetPathAmt	IN the amount to offset the path (defaults to 0.0)
	*/
	TrapZoneInfo(PMString& trapStyleName, IPathGeometry *trapZonePath, PMReal offsetPathAmt = PMReal(0.0))
		:	fTrapStyleName(trapStyleName),
			fTrapZonePath(trapZonePath, UseDefaultIID()),
			fOffsetPathAmount(offsetPathAmt)
		{}
	/** get the trap style name for this trap zone info
		@return PMString reference containing the trap style name
	*/
	PMString &GetTrapStyleName() { return fTrapStyleName; }
	/** get the trap zone path for this trap zone info
		@return pointer to IPathGeometry containing the path for this zone
		@see IPathGeometry
	*/
	IPathGeometry *GetTrapZonePath() { return fTrapZonePath; }
	/** get the desired offset amount for the path
		@return PMReal containing the desired offset for this path
	*/
	PMReal GetOffsetPathAmount() { return fOffsetPathAmount; }

private:
	PMString fTrapStyleName;
	InterfacePtr<IPathGeometry> fTrapZonePath;
	PMReal fOffsetPathAmount;
};

/** Font_Info is the container for font information for the pages
	in the publication. Used in the IPrintJobData interface.
*/
class Font_Info
{
public:
	typedef base_type data_type;

	/** constructor
		@param ctFontDict		IN pointer to a CTFontDict for the font
		@param numDesignVectors	IN the number of design vectors for the font - only applicable
		for multiple master fonts - defaults to zero
		@param designVectors	IN pointer to the array of Fixed numbers for the design vectors
		@param flags			IN the flags for this font
	*/
	Font_Info(const CTFontDict* ctFontDict, int32 numDesignVectors = 0, Fixed* designVectors = nil, uint32 flags = 0)
		:	fctFontDict(ctFontDict),
			fnumDesignVectors(numDesignVectors),
			fFlags(flags),fDesignVectors(nil)
	{
        if(numDesignVectors){
            fDesignVectors = new Fixed[numDesignVectors];
            std::memcpy(fDesignVectors, designVectors, sizeof(Fixed)*numDesignVectors);
        }
        
	}
    
    
    ~Font_Info(){
        if(fDesignVectors)
            delete[] fDesignVectors;
        fDesignVectors = nil;
    }
    
	/** get the CTFontDict for this font
		@return CTFontDict pointer
	*/
	const CTFontDict* GetCTFontDict() const { return fctFontDict; }
	/** get the number of design vectors for this font
		@return the number of design vectors
	*/
	size_t GetNumDesignVectors() const { return fnumDesignVectors; }
	/** get the design vectors
		@param dV		OUT a pointer to an array of 4 Fixed values to
		store the design vectors in
	*/
	void GetDesignVectors(Fixed* dV) const{
        std::memcpy(dV, fDesignVectors, sizeof(Fixed)*fnumDesignVectors);
    }
	/** get the flags for this font
		@return the flags
	*/
	uint32 GetFlags() const { return fFlags; }

	/** assignment operator for this class
	*/
	Font_Info &operator= (const Font_Info& other)
	{
		if (this != &other)
		{
			fctFontDict = other.fctFontDict;
			fnumDesignVectors = other.fnumDesignVectors;
            Fixed *fiDV = nil;
            if(fnumDesignVectors)
                fiDV = new Fixed[fnumDesignVectors];
			other.GetDesignVectors(fiDV);
            std::memcpy(fDesignVectors, fiDV, sizeof(Fixed)*fnumDesignVectors);
			fFlags = other.fFlags;
            if(fiDV){
                delete[] fiDV;
            }
		}
		return *this;
	}

	/** equality operator for this class
		@return kTrue if classes are equal, kFalse otherwise
	*/
	bool16 operator==(const Font_Info& fi) const
	{
        bool16 result = kTrue;
		if (fctFontDict != fi.GetCTFontDict()) 
			result =  kFalse;
		if (fnumDesignVectors != fi.GetNumDesignVectors()) 
			result = kFalse;
        if(result){
            Fixed *fiDV = nil;
            if(fnumDesignVectors)
                fiDV = new Fixed[fnumDesignVectors];
            fi.GetDesignVectors(fiDV);
            if(std::memcmp(fiDV, fDesignVectors, sizeof(Fixed) * fnumDesignVectors) != 0)
                result = kFalse;
            if (fFlags != fi.GetFlags())
                result =  kFalse;
            if(fnumDesignVectors>0)
                delete [] fiDV;
        }
		return result;
	}

	/** flags for this font
	*/
	enum {
		// horizontal/vertical
		kIsVertical		= 0x00000001
	};

private:
	const CTFontDict*		fctFontDict;
	size_t					fnumDesignVectors;
	Fixed					*fDesignVectors;
	uint32					fFlags;
};


#endif // __IPrintJobData__
