//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CRenderingObject.h $
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
#ifndef __CRenderingObject__
#define __CRenderingObject__

#include "IRenderingObject.h"
#include "HelperInterface.h"

class PMRect;
class IGraphicsPort;
class IGraphicsContext;

#pragma export on
class PUBLIC_DECL CRenderingObject : public IRenderingObject
{
	public:
		CRenderingObject( IPMUnknown *boss );
		virtual ~CRenderingObject( );

		virtual void	ReadWrite			(IPMStream *s, ImplementationID prop);

		// Subclasses must override Install methods. The default method does nothing.
		virtual void Install (IGraphicsPort* gPort, IGraphicStyleDescriptor* iGSDesc, InstallAction theAction) const;
		virtual void Install (IGraphicsPort* gPort, IWaxRenderData* iWaxData, InstallAction theAction) const;
		virtual void Install (IGraphicsPort* gPort, IGraphicAttributeSuite* iGfxAttrSuite, InstallAction theAction, const PMRect& r ) const;
		virtual void Install (IGraphicsPort* gPort, const AttributeBossList& attrs, const PMRect& r, InstallAction theAction) const;
		virtual void Install ( IGraphicsPort *gPort, const PMRect& r ) const;
		virtual void Install (IGraphicsPort* gPort, RenderingObjectInstallData *data, const PMRect& r, InstallAction theAction) const;

		virtual const PMString& GetSwatchUIName		() const;		
		virtual PMString GetTipText() const;
		virtual PMString GetTipText( const int32& colorSpace, const ColorArray& colorComponents ) const;

		virtual const PMString& GetSwatchName		() const;
		virtual bool16	GetVisibility		() const;
		virtual bool16	GetCanDelete		() const;
		virtual bool16	GetCanEdit			() const;
		virtual bool16	IsGlobal			() const;
		virtual UID		GetSwatchAliasUID	() const;
		
		// Use this to get special edit info about the render object.
		// Example: for a solid color, it can indicate which data element can be edited which can't.
		// Subclass must override. The default method just returns 0.
		virtual int32	GetSpecialEditInfo	() const;

		virtual void	SetSwatchName		(const PMString& newName);
		virtual void	SetVisibility		(const bool16 visible);
		virtual void	SetCanDelete		(const bool16 canDelete);
		virtual void	SetCanEdit			(const bool16 canEdit);
		virtual void	SetSwatchAliasUID	(UID);

		virtual int32	GetCreatorID		() const;
		virtual void	SetCreatorID		(int32);

		// Use this to set special edit info for the render object. 
		// Subclass must override. The default method does nothing
		virtual void	SetSpecialEditInfo	(const int32 editInfo);
		
		// Given an UID, determined if that UID caused any changes in the rendering object.
		// returns kTrue, if updates will be required. Otherwise, return kFalse.
		virtual	bool16	NeedUpdate			( UID interestedUID ) const;

		// Duplicate this rendering object as a new local rendering object taking into account
		// any stroke or fill's overriding attributes if any. Returns the new UID that it created.
		// Use the first one with a page item and the second with text.
		// IMPORTANT NOTE:	These methods must be called within a command sequence in order for the
		//					Undo/Redo to be performed correctly.
		virtual UID		DuplicateAsLocal	( const IGraphicStyleDescriptor* overrideAttrs, InstallAction theAction) const;
		virtual UID		DuplicateAsLocal	( const AttributeBossList* overrideAttrs, InstallAction theAction) const;
		virtual UID		DuplicateAsLocal	( const PMReal& tint) const;

		//____________________________________________________________________________________
		//	Utilities
		//____________________________________________________________________________________
		
		// Rendering class
		virtual ClassID			GetRenderClass	() const {return kInvalidClass;}
		
		// Two rendering objects are equal if all their persisten data and rendering data
		// are equal.
		virtual bool16			IsEqual			(const IRenderingObject*) const;

	protected:
		UID			DuplicateAsLocal(void) const;

		PMString	fRenderName;
		
	private:
		void		SetIsGlobal			(const bool16 isGlobal);	// to be a public method once we support AI's named local swatches.
	
	
		int32		fRenderingFlag;
		enum {
				kDeleteFlag = 0x00000001,
				kVisibleFlag = 0x00000002,
				kEditFlag = 0x00000004,
				kGlobalFlag = 0x00000008	
			 };

DECLARE_HELPER_METHODS()
};
#pragma export off


#endif	// __CRenderingObject__
