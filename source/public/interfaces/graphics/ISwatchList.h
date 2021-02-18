//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/ISwatchList.h $
//  
//  Owner: SusanCL, Jack Kirstein
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
//  Purpose of Interface:
//  This is a simple interface designed to hold a list of swatches
//  or ui colors stored in the workspaces (documents or app).
//  The swatches can be any rendering objects such as solid colors and gradients.
//  
//  Add more Find__ methods as more rendering objects are implmented.
//  
//========================================================================================

#pragma once
#ifndef __ISwatchList__
#define __ISwatchList__

#include "IPMUnknown.h"
#include "ColorSystemID.h"
#include "IColorData.h"
#include "IGradientFill.h"
#include "PMString.h"

class	UIDList;

/**	An interface for managing InDesign swatch list. A swatch is a rendering object boss derived
	from kK2RenderObjectBoss and must implement IRenderingObject interface.
	All rendering object must also provide IRenderObjectService implementation through kRenderingObjectService
	service provider. This facilitates the management of the rendering objects.
	In addition, all rendering objects must also provide creation, change, and deletion commands.
	For example, the solid color objects are kPMColorBoss. It provides kNewColorCmdBoss for creating new basic color objects,
	kChangeColorCmdBoss for changing properties of the colors, and kDeleteColorCmdBoss for deleting the color opbjects.
	
	The swatches can be unnamed or named. Swatches can also be visible
	in the UI or not.
	
	Currently supported rendering objects (or swatches) are kPMColorBoss, kGradientRenderingObjectBoss, and
	kGraphicStateNoneRenderingObjectBoss.
	
	@see ColorSystemID.h
	@see GradientFillID.h
	@see GraphicStylesID.h
	@see IRenderingObject
	@see IRenderObjectService
*/
class ISwatchList : public IPMUnknown
{
	public:
		enum	{kDefaultIID = IID_ISWATCHLIST};
		
		/**	Initialize the swatch list.
		*/
		virtual	void	Init() = 0;
			
		/**	Find a swatch by name in the list and return the swatch UIDRef.
			@param name the swatch name to find.
			@return	the matching swtach UIDRef. If not found, returns UIDRef::gNull.
			UIDRef is the UIDRef of the any matching color rendering object boss.
		*/
		virtual UIDRef	FindSwatch(const PMString& name) const = 0;

		/**	Find a swatch by color space and components in the list and return the swatch UIDRef.
			@param colorSpace the color space to find.
			@param colorArray the color value to find.
			@return	the matching swtach UIDRef. If not found, returns UIDRef::gNull.
			UIDRef is the UIDRef of the matching color rendering object boss (kPMColorBoss).
		*/
		virtual UIDRef	FindSwatch(const int32& colorSpace, const ColorArray& colorArray ) const = 0;

		/**	Find a swatch by content of color data in the list and return the swatch UIDRef.
			@param colorData the color data to find.
			@return	the matching swtach UIDRef. If not found, returns UIDRef::gNull.
			UIDRef is the UIDRef of the matching color rendering object boss (kPMColorBoss).
			@see IColorData
		*/
		virtual UIDRef	FindSwatch( IColorData* colorData ) const = 0;

		/**	Find a swatch by content of gradient data in the list and return the swatch UIDRef.
			@param gradient the gradient data to find.
			@return	the matching swtach UIDRef. If not found, returns UIDRef::gNull.
			UIDRef is the UIDRef of the matching gradient rendering object boss (kGradientRenderingObjectBoss).
			@see IGradientFill
		*/
		virtual UIDRef  FindSwatch( IGradientFill* gradient ) const = 0;

		/**	Find a swatch by the Swatch UID and return its index in the swatch list.
			@param swatchUID the swatch UID to find.
			@return the index of the swatch in the list starting from index 0. If no such UID is found, returns -1.
		*/
		virtual int32	SwatchLocation (const UID& swatchUID ) const = 0;
			
		/**	Find a swatch by UID and return its index in the visible list.
			@param swatchUID the swatch UID to find.
			@return the index of the swatch in the visible list. If no such UID is found, returns -1.		
		*/
		virtual int32	VisibleSwatchLocation (const UID& swatch) const = 0;

		/**	Get total number of swatches in the list, including unnamed swatches,
			hidden swatches and visible swatches (swatches shown in the swatch panel).
			@return the total number of swatches in the list.
		*/
		virtual int32	GetNumSwatches() const = 0;
			
		/**	Returns the number of visible swatches if any.
			@return the number of visible swatches.
		*/
		virtual int32	GetNumVisibleSwatches() const = 0;
			
		/**	Returns the number of named swatches if any.
			@return the number of named swatches.
		*/
		virtual int32	GetNumNamedSwatches() const = 0;
			
		/**	Returns the UIDRef of the nth swatch in the total list.
			@param index the nth swatch starting from index 0.
			@return UIDRef of the nth swatch. Returns UIDRef::gNull if index is out of range.
			UIDRef is the UIDRef of a rendering object boss.
		*/
		virtual UIDRef	GetNthSwatch(int32 index) const = 0;
			
		/**	Returns the UIDRef of the nth swatch in the visible list. Returns kInvalidUID
			if there are no visible swatches.
			The order ot these swatches is the order shown in the swatches panel.
			@param index the nth visible swatch starting from index 0.
			@return UIDRef of the nth visible swatch. Returns UIDRef::gNull if index is out of range.
			UIDRef is the UIDRef of a rendering object boss.
		*/
		virtual UIDRef	GetNthVisibleSwatch(int32 index) const = 0;

		/**	Returns the UIDRef of the nth named swatch in the named list. Returns kInvalidUID
			if there are no named swatches.
			The ordering swatches in this list may not be the same as the visible list or
			the total list.
			@param index the nth named swatch starting from index 0.
			@return UIDRef of the nth named swatch. Returns UIDRef::gNull if index is out of range.
			UIDRef is the UIDRef of a rendering object boss.
		*/
		virtual UIDRef	GetNthNamedSwatch(int32 index) const = 0;
			
		/**	Add swatch to the list. This should also update the visible list based
			on its visibility setting.
			@param swatch the new swatch UID to add. This should be an UID of a rendering object boss.
		*/
		virtual void	AddSwatch(const UID& swatch ) = 0;
			
		/**	Remove swatch from the list. This should also update the visible list based
			on its visibility setting if necessary.
			@param swatch the swatch UID to remove. This should be an UID of a rendering object boss.
		*/
		virtual void	RemoveSwatch(const UID& swatch) = 0;

		/**	Remove a list of swatches from the swatch list. This should also updates the visible  
			list based on their visibility setting if necessary.
			@param itemList the list of swatches to remove. These should be UIDs of rendering object bosses.
		*/
		virtual void	RemoveSwatch(const UIDList* itemList) = 0;

		/**	Move a swatch at fromIndex position to toIndex position in the visible list.
			@param fromIndex the original position of the swatch.
			@param toIndex the new position of the swatch.
		*/
		virtual void	Move(int32 fromIndex, int32 toIndex ) = 0;
		
		/**	Sort the visible swatch list by name in the alphabetical order.
			If all swatches are unnamed, then this method does nothing.
		*/
		virtual void	SortVisibleSwatchesByName () = 0;
			
		/**	Return the UID of the [Black] swatch. If not in the list, kInvalidUID is returned.
			@return UID of Black swatch.
		*/
		virtual UID		GetBlackSwatchUID () const = 0;
		/**	Return the UID of the [Paper] swatch. If not in the list, kInvalidUID is returned.
			@return UID of Paper swatch.
		*/
		virtual UID		GetPaperSwatchUID () const = 0;
		/**	Return the UID of the [Registration] swatch. If not in the list, kInvalidUID is returned.
			@return UID of Registration swatch.
		*/
		virtual UID		GetRegistrationSwatchUID () const = 0;
		/**	Return the UID of the [None] swatch. If not in the list, kInvalidUID is returned.
			@return UID of None swatch.
		*/
		virtual UID		GetNoneSwatchUID () const = 0;
				
	enum {kNotFound = -1};
};

#endif