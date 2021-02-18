//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IDynDocsPublicUtils.h $
//  
//  Owner: Yeming Liu
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

// ----- Interface files -----
#include "IGraphicsPort.h"
#include "IXPAttributeSuite.h"

// ----- Include files -----
#include "DynamicDocumentsTypes.h"
#include "Utils.h"

// ----- ID files -----
#include "DynamicDocumentsID.h"

class IDocument;
class IShape;

/**
	This utility interface is on the kUtilsBoss. 
	It is used for installing a stack based object to process hyperlink information 
	when export InDesign document to SWF. 
*/
class IDynDocsPublicUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDYNDOCSPUBLICUTILS };

	/**
		This method is called at the constructor of DynDocsHyperlinkHelper to start pushing the hyperlink information to port.

		@param port [IN]: graphics port that we push the information to.
		@param item [IN]: item that has hyperlink information.
		@param bounds [IN]: optional bounding box for the hyperlink. May be omitted if bounds can be deduced from hyperlink.
		@return bool: Return true if we did push the hyperlink information; otherwise return false. 
	*/
	virtual bool BeginHyperlink(IGraphicsPort *port, UIDRef const &item) = 0;

	/**
		This method is called at the constructor of DynDocsHyperlinkHelper to start pushing the hyperlink information to port.

		@param port [IN]: graphics port that we push the information to.
		@param item [IN]: item that has hyperlink information.
		@param bounds [IN]: bounding box for the hyperlink. May be omitted if bounds can be deduced from hyperlink.
		@param matrix [IN]: Matrix for transforming bounds to spread coordinates
		@return bool: Return true if we did push the hyperlink information; otherwise return false. 
	*/
	virtual bool BeginHyperlink(IGraphicsPort *port, UIDRef const &item, PMRect const &bounds, PMMatrix const &matrix) = 0;

	/**
		This method is called at the destructor of DynDocsHyperlinkHelper to end pushing the hyperlink information to port.
		@param port [IN]: graphics port that we push the information to.
	*/
	virtual void EndHyperlink(IGraphicsPort *port) = 0;

	/**
		This method is to check if we should push (see TableShape.cpp).

		@param port [IN]: graphics port that we push the information to.
		@param item [IN]: item could be page item or text source hyperlink.
		@return bool: Return true when we can push hyperlink info to port; otherwise false. 
	*/
	virtual bool CanAddHyperlink(IGraphicsPort const *port, UIDRef const &item) = 0;

	/**
		This method is to calculate the bounds of the given page items. 

		@param items [IN]: the selected page items
		@param width [OUT]: the width of the items
		@param height [OUT]: the height of the items
	*/
	virtual void CalculateSelectedBounds(UIDList const &items, PMReal &width, PMReal &height) const = 0;

	/**
		This method is to calculate the total bounds of the given items. 
		If readersSpreads is true, then it is the bounds of spread; otherwise it is the bounds of page.

		@param items [IN]: the given items
		@param readersSpreads [IN]: flag indicate checking spread bounds or page bounds.
		@param width [OUT]: the width of the items
		@param height [OUT]: the height of the items
	*/
	virtual void CalculateTotalBounds(UIDList const &items, bool readersSpreads, PMReal &width, PMReal &height) const = 0;

	/**
	 Calculates the effective width and height for an export to either SWF or XFL given source
	 dimensions and a structure defining the type of scaling to be applied.
	 
	 Note: The calculated width and height are implicitly converted to unsigned integers by
	 determining their mathematical ceiling.
	 
	 @param sourceWidth		[in]: The width of the source document, as determined by CalculateTotalBounds
	 @param sourceHeight	[in]: The height of the source document, as determined by CalculateTotalBounds
	 @param settings		[in]: The settings to be used to determine the scaled dimensions
	 @param destWidth		[out]: The calculated width
	 @param destHeight		[out]: The calculated height
	 */
	virtual void CalculateWidthAndHeightForExport(
		PMReal const &sourceWidth, PMReal const &sourceHeight,
		flash_export::SizeAndFitSettings const &settings,
		uint32 &destWidth, uint32 &destHeight
	) const = 0;

	/**
		Iterate the document before export to look for problems and, if showing UI, warn the
		user about issues. If the user cancels in response to a problem, IterateDocForExport will return false.

		@param pCmdExport			[in]: The dynamic documents export command to be used.
		@param items				[in]: The list of items to be exported: spreads, pages or selected page items.
		@param pDoc					[in]: The document to be exported.
		@param uiFlags				[in]: A flag indicating whether or not UI is permitted.
		@param bValidationFailure	[out]: Optional argument that denotes whether the items to be exported
										   include missing or out-of-date links, legacy media, or flattening is
										   turned on and the items have transparency.

		@return bool: Return true if the user did not cancel in response to any problems; otherwise return false. 
	 */
	virtual bool IterateDocForExport(ICommand* pCmdExport, const UIDList& items, IDocument* pDoc, UIFlags uiFlags, bool* bValidationFailure = nil) const = 0;

	/**
		Determine the expected name of a resource directory associated with an exported file.

		@param ddExportFile	[in]: The exported file for which to find the resource directory.

		@return AString: The expected name of the resource directory associated with ddExportFile.
	 */
	virtual AString GetResourceDirectoryNameFromDDExportFile(const IDFile& ddExportFile) const = 0;

	/**
   		Determine whether we should ignore the transparency effects applied on text when export to FLA.
   
   		@param iShape	[in]: The shape that has effects applied to it.
      	@param target	[in]: The applied transparency effect target(object, fill, stroke and content).

   		@return bool: return true if we should ignore; otherwise return false.
   	 */
	virtual bool ShouldIgnoreTextXPAdornment(IShape* iShape, IXPAttributeSuite::AttributeTarget target) = 0;
};
	
/**
Helper class for pushing the pageitem's hyperlink information to the SWF port.
*/
class DynDocsHyperlinkHelper : boost::noncopyable
{
	Utils<IDynDocsPublicUtils> fDynDocsUtils;
	InterfacePtr<IGraphicsPort> fGraphicsPort;
	bool fPushHyperlink;

public:
	/**
	Constructor

	@param port [IN]: graphics port that we push the information to.
	@param item [IN]: item that has hyperlink information.
	*/
	DynDocsHyperlinkHelper(IGraphicsPort *port, UIDRef const &item) : 
		fGraphicsPort(port, UseDefaultIID()), 
		fPushHyperlink(false)
	{
		if (fDynDocsUtils.Exists() && fDynDocsUtils->CanAddHyperlink(port, item))
			fPushHyperlink = fDynDocsUtils->BeginHyperlink(port, item);
	}

	/**
	Constructor

	@param port [IN]: graphics port that we push the information to.
	@param item [IN]: item that has hyperlink information.
	@param bounds [IN]: bounding box for the hyperlink.
	@param matrix [IN]: matrix used to transform bounding box to spread coordinates.
	*/
	DynDocsHyperlinkHelper(IGraphicsPort *port, UIDRef const &item, PMRect const &bounds, PMMatrix const &matrix) : 
		fGraphicsPort(port, UseDefaultIID()), 
		fPushHyperlink(false)
	{
		if (fDynDocsUtils.Exists() && fDynDocsUtils->CanAddHyperlink(port, item))
			fPushHyperlink = fDynDocsUtils->BeginHyperlink(port, item, bounds, matrix);
	}

	/**
	Destructor
	*/
	~DynDocsHyperlinkHelper()
	{
		if (fPushHyperlink)
		{
			ASSERT(fDynDocsUtils.Exists());
			fDynDocsUtils->EndHyperlink(fGraphicsPort);
		}
	}
};

