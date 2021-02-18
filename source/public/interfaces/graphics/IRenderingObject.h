//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IRenderingObject.h $
//  
//  Owner: SusanCL
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
#ifndef __IRenderingObject__
#define __IRenderingObject__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "ColorSystemID.h"
#include "PMString.h"
#include "IColorData.h"

class PMRect;
class AttributeBossList;
class GridAddress;
class IGraphicsPort;
class IGraphicStyleDescriptor;
class IWaxRenderData;
class IGraphicAttributeSuite;
class IViewPort;
class IControlView;
class IGraphicsContext;

/**	A helper class to facilitate installing the rendering object with specific attributes.
	Two types of attributes are supported, tint or gradient. They are mutually exclusive.
*/
class RenderingObjectInstallData
{
public:
	virtual ~RenderingObjectInstallData() {}
	/**	Returns a tint value.
		@return a tint value.
	*/
	virtual PMReal		GetTint() = 0;
	
	/**	Sets a tint value.
		@param tint the tint value to set.
	*/
	virtual void		SetTint(PMReal tint) = 0;

	/**	Return kTrue if gradient attribute values are used.
		@return kTrue if gradient attribute values are used.
	*/
	virtual bool16		GradientValuesSet() = 0;
	
	/**	Sets related gradient attributes values
		@param fillAngle the gradient angle to set.
		@param fillLength the gradient length to set.
		@param fillCenter the gradient start point or center to set.
		@param fillRadius the radial gradient radius to set.
		@param highlightAngle the gradient highlight angle to set.
		@param highlightLength the gradient highlight length to set.
	*/
	virtual void		SetGradientValues(PMReal fillAngle, PMReal fillLength, PMPoint fillCenter, PMReal fillRadius, 
										  PMReal highlightAngle, PMReal highlightLength) = 0;
	
	/**	Returns the gradient angle.
		@return the gradient angle.
	*/
	virtual PMReal		GetFillAngle() = 0;
	/**	Returns the gradient length.
		@return the gradient length.
	*/
	virtual PMReal		GetFillLength() = 0;
	/**	Returns the gradient center or start point.
		@return the gradient center or start point.
	*/
	virtual PMPoint		GetFillCenter() = 0;
	/**	Returns the gradient radius.
		@return the gradient radius.
	*/
	virtual PMReal		GetFillRadius() = 0;
	/**	Returns the gradient highlight angle.
		@return the gradient highlight angle.
	*/
	virtual PMReal		GetHighlightAngle() = 0;
	/**	Returns the gradient highlight length.
		@return the gradient highlight length.
	*/
	virtual PMReal		GetHighlighLength() = 0;
};

/**	A reqruied interface for all InDesign rendering objects. All rendering objects are
	represented by swatches.
	@See ISwatchList
*/
class IRenderingObject : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IRENDERINGOBJECT };

		/**	Specifies how the rendering object are being installed.
		*/
		enum InstallAction
		{
			/**	Indicate installing the rendering object for stroke.
			*/
			kInstallStroke,
			/**	Indicate installing the rendering object for fill.
			*/
			kInstallFill,
			/**	Indicate installing the rendering object for stroke gap.
				Gap color is currently not valid for text.
			*/
			kInstallGap
		};
		
		/**	Install the rendering object for a pageitem with graphic attributes
			@param gPort the graphic port in which to install the rendering object.
			@param iGSDesc the graphic style descriptor.
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, IGraphicStyleDescriptor* iGSDesc, InstallAction theAction) const = 0;
		
		/**	Install the rendering object for text.
			@param gPort the graphic port in which to install the rendering object.
			@param iGSDesc the graphic style descriptor.
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, IWaxRenderData* iWaxData, InstallAction theAction) const = 0;
		
		/**	Install the rendering object for graphic state definition.
			@param gPort the graphic port in which to install the rendering object.
			@param iWaxData the text wax data containing the related rendering attributes.
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, IGraphicAttributeSuite* iGfxAttrSuite, InstallAction theAction, const PMRect& r ) const = 0;
		
		/**	Install the rendering object for tables
			@param gPort the graphic port in which to install the rendering object.
			@param attrs the table attribute list.
			@param r the rectangle
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, const AttributeBossList& attrs, const PMRect& r, InstallAction theAction) const = 0;
		
		/**	Install the rendering object for a simple rectangular area.
			@param gPort the graphic port in which to install the rendering object.
			@param r the affected rectangular area
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, const PMRect& r) const = 0;
		
		/**	Install the rendering object for using the RenderingObjectInstallData.
			@param gPort the graphic port in which to install the rendering object.
			@param data the rendering object related install data.
			@param r the affected rectangular area
			@param theAction specifies which install action to do.
		*/
		virtual void Install (IGraphicsPort* gPort, RenderingObjectInstallData *data, const PMRect& r, InstallAction theAction) const = 0;
		
		/**	Returns the string that includes the name as well as other information that appears
			in various UI elements such as tint percentage.
			@return a PMString reference that is the rendering object's UI name.  Make sure that
			you do not use the reference to the name after the pointer to the IRenderingObject 
			goes out of scope.
		*/
		virtual const PMString& GetSwatchUIName		() const = 0;		

		/**	Returns the string that contains color info which is used as tip.
			@return a PMString that is the rendering object tip text.
		*/
		virtual PMString GetTipText() const = 0;

		/**	Returns the string that contains color info which is used as tip using the specified color space and values.
			@param colorSpace the color space to format.
			@param colorComponents the color values to format.
			@return a PMString that is the rendering object tip text.
		*/
		virtual PMString GetTipText( const int32& colorSpace, const ColorArray& colorComponents ) const = 0;
		
		/**	Returns the swatch name associated with this rendering object.
			@return a PMString reference that is the rendering object' swatch name.  Make sure that
			you do not use the reference to the name after the pointer to the IRenderingObject 
			goes out of scope.
		*/
		virtual const PMString& GetSwatchName() const = 0;

		/**	Returns kTrue if swtach is visible in the swatches panel and other UI elements.
			@return kTrue if swtach is visible in UI.
		*/
		virtual bool16 GetVisibility() const = 0;

		/**	Returns kTrue if swtach can be deleted.
			@return kTrue if swtach can be deleted.
		*/
		virtual bool16 GetCanDelete() const = 0;

		/**	Returns kTrue if swtach can be edited.
			@return kTrue if swtach can be edited.
		*/
		virtual bool16 GetCanEdit() const = 0;

		/**	Returns kTrue if swtach is a global swatch.
			@return kTrue if swtach is a global swatch.
		*/
		virtual bool16 IsGlobal() const = 0;

		/**	Returns the swatch's alias swatch UID.
			@return the swatch's alias swatch UID.
		*/
		virtual UID GetSwatchAliasUID () const = 0;

		/**	Sets the new swatch name.
			@param newName the new swatch name to set.
		*/
		virtual void SetSwatchName(const PMString& newName) = 0;

		/**	Sets the visibility flag. By default, unnamed swtach must not be visible.
			@param visible kTrue if swatch is visible.
		*/
		virtual void SetVisibility(const bool16 visible) = 0;

		/**	Sets the new delete flag. By default, all custom swatches are deletable.
			@param canDelete kTrue if swatch can be deleted.
		*/
		virtual void SetCanDelete(const bool16 canDelete) = 0;

		/**	Sets the new edit flag. By default, all custom swatches are editable.
			@param canEdit kTrue if swatch can be edited.
		*/
		virtual void SetCanEdit(const bool16 canEdit) = 0;
		
		/**	Sets the swatch's new alias swatch UID.	kInvalidUID means swatch is not aliased.
			@param newAliasUID the new alias swatch UID to set.
		*/
		virtual void SetSwatchAliasUID (UID newAliasUID) = 0;

		/**	Returns the swatch's creator ID. By default, swatch creator ID is set to kInDesignNativeSwatchCreatorID.
			@return the creator ID.
		*/
		virtual int32 GetCreatorID () const = 0;
		
		/**	Sets the new creator ID.
			@param newCreatorID the new creator ID to set.
		*/
		virtual void SetCreatorID (int32 newCreatorID) = 0;
		
		/**	Used to get/set special edit info about the render object. Using 0 to mean normal edit condition.
			Example: for a solid color, it can indicate which data elements can be edited which can't.
			@return the four byte containing special edit info.
		*/
		virtual int32	GetSpecialEditInfo() const = 0;
		
		/**	Sets the new special edit info.
			@param newEditInfo the new edit info to set.
		*/
		virtual void SetSpecialEditInfo(const int32 newEditInfo) = 0;
		
		/**	Given an UID, determined if that UID caused any changes in the rendering object.
			@return kTrue, if updates will be required. Otherwise, return kFalse.
		*/
		virtual	bool16	NeedUpdate( UID	interestedUID ) const = 0;

		/**	Duplicate this rendering object as a new unnamed rendering object taking into account
			any stroke or fill's overriding attributes if any. Returns the new UID that it created.
			"overrideAttrs" is either a graphic attribute boss list or a text attribute boss list.
			DuplicateAsLocal must be called within a command sequence in order for the Undo/Redo to be performed correctly.
		*/
		virtual UID		DuplicateAsLocal	( const IGraphicStyleDescriptor* overrideAttrs, InstallAction theAction) const = 0;
		/**	@see DuplicateAsLocal */
		virtual UID		DuplicateAsLocal	( const AttributeBossList* overrideAttrs, InstallAction theAction) const = 0;
		/**	@see DuplicateAsLocal */
		virtual UID		DuplicateAsLocal	( const PMReal& tint) const = 0;

		//____________________________________________________________________________________
		//	Utilities
		//____________________________________________________________________________________
		
		/**	Returns the rendering class.
			@return the rendering class.
		*/
		virtual ClassID			GetRenderClass	() const = 0;
		
		/**	Two rendering objects are equal if all their persisten data (except swatch name)
			and rendering data are equal. Swatch names ARE NOT compared.
			@param iRenderObject2 the rendering object to compare with.
			@return kTrue if two rendering objects are equal.
		*/
		virtual bool16			IsEqual			(const IRenderingObject* iRenderObject2) const = 0;
		
};


#endif
