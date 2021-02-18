//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/text/ITextTargetAttributes.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ITextTargetAttributes__
#define __ITextTargetAttributes__

#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "AttributeBossList.h"

class ITextFocus;
class ICommand;
class IFocusCache;
class ITextAttributes;
class IApplyStyleData;
class ITextAttributeSuite;


//----------------------------------------------------------------------------------------
// Class ITextTargetAttributes
//----------------------------------------------------------------------------------------

class AttributeBossList;

#ifdef TEXTPANELLIB_BUILD
#pragma export on
#endif

class TEXTPANELLIB_DECL ITextTargetAttributes INHERITFROM
{
public:
	virtual					 	~ITextTargetAttributes();
	virtual IPMUnknown *		QueryTarget( const PMIID &rIID = IID_IUNKNOWN ) = 0;
	virtual int32 				CountAttributes( const ClassID& attr ) const = 0;
	virtual const IPMUnknown* 	QueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const = 0;
	virtual bool16				ApplyAttribute( const IPMUnknown *pAttr, const ClassID &rStrandID ) = 0;
	virtual bool16 				RemoveAttribute( const ClassID& attr ) = 0;
	virtual bool16 				ResetAttribute( const ClassID& attr, AttributeBossList *pOrig ) = 0;
	virtual bool16				ApplyAttributes( const AttributeBossList *pApplied, const ClassID &rStrandID ) = 0;
	virtual bool16 				RemoveAttributes( const AttributeBossList *pRemoved) = 0;

	virtual void				SetAcceptingUnknownValues( bool16 bIsAccepting ) = 0;
	virtual bool16				IsAcceptingUnknownValues() const = 0; // returns kTrue if the target accepts the 'unknown' state (like style editing ui).
			
	virtual void				SetReadOnly( bool16 bIsAccepting ) = 0;
	virtual bool16				IsReadOnly() const = 0;

	virtual	bool16				Reset() = 0;
	virtual IPMUnknown *		QueryPreferences( const PMIID & rIID ) = 0;
	virtual bool16				ApplyToTarget() = 0;
	virtual bool16				ApplyToList( AttributeBossList *pList ) const = 0;

	virtual const AttributeBossList	*	GetAppliedAttributes() const = 0;	// get only the list with the applied attributes.
	virtual const AttributeBossList	*	GetRemovedAttributes() const = 0;	// get only the list with the deleted attributes.

	virtual const ClassID 		GetNthStrandID( int32 ofAttribute ) const = 0;
	virtual	IDataBase *			GetTargetDataBase() const = 0;
	virtual	bool16				SetTargetDataBase( IDataBase *pDB ) = 0;
	
	// IsDummyTarget indicates that these attributes won't really be applied to anything
	// we've just created a dummy target to gather some information. Thus we don't need
	// certain warning dialogs to appear...
	virtual 	bool16				IsDummyTarget() const= 0;
	
	
	static ITextTargetAttributes *	CreateTargetAttributes( IPMUnknown *pTarget );
};
//---------------------------------------------------------------
// class BaseTextTarget
//---------------------------------------------------------------

class TEXTPANELLIB_DECL BaseTextTarget : public ITextTargetAttributes
{
public:
								BaseTextTarget();
	virtual						~BaseTextTarget();
	virtual void				SetAcceptingUnknownValues( bool16 bIsAccepting );
	virtual bool16				IsAcceptingUnknownValues() const;
	virtual void				SetReadOnly( bool16 bIsAccepting );
	virtual bool16				IsReadOnly() const;
	bool16						IsEqual( const AttributeBossList *pDefaults, const AttributeBossList *pNew ) const;
	virtual	bool16				Reset();
	

	virtual int32 				CountAttributes( const ClassID& attr ) const;
	virtual const IPMUnknown* 	QueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const;
	virtual bool16				ApplyAttribute( const IPMUnknown *pAttr, const ClassID &rStrandID );
	virtual bool16 				RemoveAttribute( const ClassID& attr );
	virtual bool16 				ResetAttribute( const ClassID& attr, AttributeBossList *pOrig );
	virtual IPMUnknown *		QueryPreferences( const PMIID & rIID );

	virtual bool16				ApplyAttributes( const AttributeBossList *pApplied, const ClassID &rStrandID  );
	virtual bool16 				RemoveAttributes( const AttributeBossList *pRemoved);

	virtual const AttributeBossList	*	GetAppliedAttributes() const;	// get only the list with the applied attributes.
	virtual const AttributeBossList	*	GetRemovedAttributes() const;	// get only the list with the deleted attributes.

	virtual const ClassID 		GetNthStrandID( int32 ofAttribute ) const;
	virtual	IDataBase *			GetTargetDataBase() const;
	virtual	bool16				SetTargetDataBase( IDataBase *pDB );

	virtual 	bool16				IsDummyTarget() const {return kFalse;}
	inline	void				PreDirty() { }
	
protected:
	ClassID						fStrandID;

	virtual int32 				DoCountAttributes( const ClassID& attr ) const = 0;
	virtual const IPMUnknown* 	DoQueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const = 0;

	
private:
	bool16						fAcceptingUnknownValues;
	bool16						fReadOnly;
	
	AttributeBossList			fAppliedBossList;
	AttributeBossList			fRemovedBossList;
	
	IDataBase *					fDataBase;
};

//---------------------------------------------------------------
// class TextFocusTarget
//---------------------------------------------------------------

class TEXTPANELLIB_DECL TextFocusTarget : public BaseTextTarget
{
public:
						TextFocusTarget( ITextFocus *pFocus);
	virtual				~TextFocusTarget();

	virtual IPMUnknown *		QueryTarget( const PMIID &rIID );
	virtual bool16				ApplyToTarget();
	virtual bool16				ApplyToList( AttributeBossList *pList ) const;
	virtual IPMUnknown *		QueryPreferences( const PMIID & rIID );
	virtual	IDataBase *			GetTargetDataBase() const;
	virtual	bool16				SetTargetDataBase( IDataBase *pDB );

protected:
	virtual int32 				DoCountAttributes( const ClassID& attr ) const;
	virtual const IPMUnknown* 	DoQueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const;
	
private:
	IFocusCache *				fCache;
};

//---------------------------------------------------------------
// class TextSelectionTarget
//---------------------------------------------------------------

class TEXTPANELLIB_DECL TextSelectionTarget : public BaseTextTarget
{
public:
						TextSelectionTarget( ITextAttributeSuite* suite );
	virtual				~TextSelectionTarget();

	virtual IPMUnknown *		QueryTarget( const PMIID &rIID );
	virtual bool16				ApplyToTarget();
	virtual bool16				ApplyToList( AttributeBossList *pList ) const;
	virtual IPMUnknown *		QueryPreferences( const PMIID & rIID );
	virtual	IDataBase *			GetTargetDataBase() const;
	virtual	bool16				SetTargetDataBase( IDataBase *pDB );

protected:
	virtual int32 				DoCountAttributes( const ClassID& attr ) const;
	virtual const IPMUnknown* 	DoQueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const;
	
private:
	ITextAttributeSuite *		fTextAttributeSuite;
};

//---------------------------------------------------------------
// class TextAttributesTarget
//---------------------------------------------------------------

class TEXTPANELLIB_DECL TextAttributesTarget : public BaseTextTarget
{
public:
							TextAttributesTarget( ITextAttributes *pDefaults );
	virtual					 ~TextAttributesTarget();

	virtual IPMUnknown *		QueryTarget( const PMIID &rIID );
	virtual bool16				ApplyToTarget();
	virtual bool16				ApplyToList( AttributeBossList *pList ) const;

protected:
	virtual int32 				DoCountAttributes( const ClassID& attr ) const;
	virtual const IPMUnknown* 	DoQueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const;

	ITextAttributes *			fAttrList;
};


//---------------------------------------------------------------
// class ApplyStyleDataTarget
//---------------------------------------------------------------

class TEXTPANELLIB_DECL ApplyStyleDataTarget : public BaseTextTarget
{
public:
							ApplyStyleDataTarget( IApplyStyleData *pData );
	virtual					 ~ApplyStyleDataTarget();

	virtual IPMUnknown *		QueryTarget( const PMIID &rIID );
	virtual bool16				ApplyToTarget();
	virtual bool16				ApplyToList( AttributeBossList *pList ) const;

protected:
	virtual int32 				DoCountAttributes( const ClassID& attr ) const;
	virtual const IPMUnknown* 	DoQueryAttributeN( int32 which, const ClassID& attr, const PMIID& interfaceID  ) const;

private:
	IApplyStyleData *				fData;
};

#ifdef TEXTPANELLIB_BUILD
#pragma export off
#endif

#endif
