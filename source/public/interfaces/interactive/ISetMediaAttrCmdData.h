//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/interactive/ISetMediaAttrCmdData.h $
//  
//  Owner: Bill Tislar
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ISetMediaAttrCmdData__
#define __ISetMediaAttrCmdData__

#include "IPMUnknown.h"
#include "IMediaAttributes.h"
#include "MediaID.h"

#include <map>
#include <vector>

class ISetMediaAttrCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ISETMEDIAATTRCMDDATA };
	// ***** Begin deprecated methods DO NOT USE ******
	virtual bool16							GetCustomPosterFromMedia() const = 0;
	virtual const PMString &				GetDescription() const = 0;
	virtual bool16							GetEmbedOnPDFExport() const = 0;
	virtual bool16							GetDoNotPrintPoster() const = 0;
	virtual bool16							GetPlayOnPageTurn() const = 0;
	virtual int32							GetPosterTime() const = 0;
	virtual const PMString &				GetTitle() const = 0;
	virtual bool16							GetTitleIsFrozen() const = 0;

	virtual bool16 IsSet_CustomPosterFromMedia() const = 0;
	virtual bool16 IsSet_Description() const = 0;
	virtual bool16 IsSet_EmbedOnPDFExport() const = 0;
	virtual bool16 IsSet_PlayOnPageTurn() const = 0;
	virtual bool16 IsSet_PosterTime() const = 0;
	virtual bool16 IsSet_DoNotPrintPoster() const = 0;
	virtual bool16 IsSet_Title() const = 0;
	virtual bool16 IsSet_TitleIsFrozen() const = 0;

	virtual void SetCustomPosterFromMedia( bool16 b ) = 0;
	virtual void SetDescription( const PMString & desc ) = 0;
	virtual void SetEmbedOnPDFExport( bool16 b ) = 0;
	virtual void SetDoNotPrintPoster( bool16 b ) = 0;
	virtual void SetPlayOnPageTurn( bool16 b ) = 0;
	virtual void SetPosterTime( int32 t ) = 0;
	virtual void SetTitle( const PMString & title ) = 0;
	virtual void SetTitleIsFrozen( bool16 b ) = 0;
	// ***** End deprecated methods ******
	
	
	/** Applies all set data to an IMediaAttributes instance. This method modifies
		the model; it must be called from within the context of a command.
	*/
	virtual ErrorCode ApplyAttributes( IMediaAttributes * iMediaAttributes ) = 0;
	
	/** Removes all settings from the instance.
	*/
	virtual void Clear() = 0;
	
	/** Copies all attributes from this instance to the destData instance.
		@param destData is a valid pointer to an ISetMediaAttrCmdData instance that
			will receive the attributes.
	*/
	virtual ErrorCode CopyAttributes( ISetMediaAttrCmdData * destData ) const = 0;
	
	/** Tests if the data represented by this instance has changed; i.e., if one
		or more of the Set methods has been called.
		@return true if data has changed; otherwise returns false.
	*/
	virtual bool HasChanged() = 0;
	
	// --- Mutators for each supported value type:

	/** Sets the value of an attribute of type int16.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int16 value ) = 0;

	/** Sets the value of an attribute of type int32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, int32 value ) = 0;

	/** Sets the value of an attribute of type uint32.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, uint32 value ) = 0;
	
	/** Sets the value of an attribute of type ClassID.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, ClassID value ) = 0;

	/** Sets the value of an attribute of type PMPoint.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMPoint & value ) = 0;

	/** Sets the value of an attribute of type PMReal.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMReal & value ) = 0;

	/** Sets the value of an attribute of type PMRect.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMRect & value ) = 0;

	/** Sets the value of an attribute of type PMString.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const PMString & value ) = 0;

	/** Sets the value of an attribute of type NamedInt32AttributeList.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param value the contents of this are copied to the attribute.
	*/
	virtual void SetAttribute( uint32 attributeID, const NamedUint32AttributeList & value ) = 0;
	
	/** Sets or clears a flag attribute.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
		@param b flag value; specify kTrue to set the flag, or kFalse to clear it.
	*/
	virtual void SetFlag( uint32 attributeID, bool16 b ) = 0;

	/** Clears a flag attribute. This method has no affect if the attribute does not exist.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
	*/
	virtual void ClearFlag( uint32 attributeID ) = 0;
	
	/** Clears an attribute int16 value. This method has no affect if the attribute does not exist.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
	*/	
	virtual void ClearInt16( uint32 attributeID ) = 0;
	
	/** Clears an attribute PMPoint value. This method has no affect if the attribute does not exist.
		@param attributeID may be either a MediaAttributeID or a media-specific ID.
	*/	
	virtual void ClearPMPoint( uint32 attributeID ) = 0;
			
}; // end ISetMediaAttrCmdData interface class


#endif
