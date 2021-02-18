//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TextAttrScriptUtility.h $
//  
//  Owner: Jonathan W. Brown
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
//  
//========================================================================================

#pragma once
#ifndef __TextAttrScriptUtility__
#define __TextAttrScriptUtility__

#include "AttributeBossList.h"
#include "K2SmartPtr.h"
#include "ScriptData.h"
#include "ScriptIDEnumMap.h"

#include "IAttrReport.h"
#include "IComposeScanner.h"
#include "IScript.h"
#include "IScriptRequestData.h"
#include "IScriptUtils.h"

class IAttrReport;
class IScript;
class IScriptRequestData;
class IDataBase;

typedef boost::shared_ptr<AttributeBossList>	ScopedAttributeList ;
typedef ScopedAttributeList					AddAttributeList ;
typedef K2Vector<ClassID>					RemoveAttributeList ;

/** Text attribute utility class
This utility class helps handle the common details of how Text Attributes are
processed for scripting objects. Due to the wide variety of scripting objects
that have Text Attributes of some sort this ensures that we have a consistent
handling of them across all the scripting objects. However, there is no way
at the present time to extensibly add new types scripting objects to this
implementation.

The constructor takes a IScript object with any of following properties (in
order of priority):

	It implements the IID_ITEXTMODEL interface (typically the kTextStoryBoss)
		(and IID_ICOMPOSESCANNER)
	It implements the IID_ITEXTTARGET interface (typically something inheriting
		from the kTextScriptingSuiteBoss)
	It implements the IID_ITEXTITERSCRIPTDATA interface (used by IDML)
	It implements the IID_ISTYLEINFO interface (character/paragraph styles)
	It is a c_FindPref or c_FindTextPref Script object type
	It is a c_ChangePref or c_ChangeText Script object type
	It is a c_FindGrepPref Script object type
	It is a c_ChangeGrepPref Script object type
	It is a c_FindTransliteratePref Script object type
	It is a c_ChangeTransliteratePref Script object type
	It is a c_TextDefault Script object type
	IT is a c_FindGlyphPref Script object type
	IT is a c_ChangeGlyphPref Script object type

The simplest usage pattern looks like this:

	ErrorCode MyProvider::AccessMyBoolAttr(ScriptID propID, IScriptRequestData* data, IScript* script)
	{
		TextAttrScriptUtility tasu(script, script, data->GetRequestContext());
		const ClassID attrID = kMyBoolAttributeBoss;
		ErrorCode err = tasu.AccessBoolAttribute(data, propID, attrID);
		if ( err == kSuccess && data->IsPropertyPut())
        	err = tasu.ApplyScriptCmd();
    	return err ;
	}

For those implementations that have more than one TextAttribute it is much more
efficient for INX and IDML purposes if this is wired up via PreAccessProperty()
and PostAccessProperty() like so:

	class MyProvider : ...
	{
		private:
			scoped_ptr<TextAttrScriptUtility>  tasu;

	}

	ErrorCode MyProvider::PreAccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
	{
		tasu.reset(new TextAttrScriptUtility(script));
		return kSuccess;
	}

	ErrorCode MyProvider::PostAccessProperty(ScriptID propID, IScriptRequestData* data, IScript* script)
	{
		ASSERT(tasu != nil);
		ErrorCode err = kSuccess;
		if (data->IsPropertyPut())
			err = tasu->ApplyScriptCmd(data);
		tasu.reset() ;
		return err;
	}

	To remove an attribute pass in en_Nothing for scriptData.

*/
class PUBLIC_DECL TextAttrScriptUtility
{
public:
	/**
		Construct a new TextAttrScriptUtility
		@param script Pointer to script boss, see comments at top of file. is the target object that has text attributes you plan to get or set
	*/
	TextAttrScriptUtility( IScript* script, const RequestContext& context, IScript *target = nil ) ;
	TextAttrScriptUtility( const AttributeBossList* attributeBossList, const RequestContext& context ) ;

	/** AccessBoolAttribute. Get/Set a boolean attribute.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRBOOLEAN
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessBoolAttribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessInt16Attribute. Get/Set a int16 attribute.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRINT16
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessInt16Attribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessInt32Attribute. Get/Set a int32 attribute.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRINT32
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessInt32Attribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessUnitAttribute. Get/Set a Unit attribute based on a PMReal.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRREALNUMBER
		@param unitType Caller specifies script unit type
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessUnitAttribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass, ScriptData::UnitType unitType);

	/** AccessRealAttribute. Get/Set a real number attribute. The implementation calls AccessMultiplierAttribute with a multiplier of 1.0.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRREALNUMBER
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessRealAttribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessPercentageAttribute. Get/Set a percentage attribute. The implementation calls AccessMultiplierAttribute with a multiplier of 100.0.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRREALNUMBER
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessPercentageAttribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessColor. Get/Set a color attribute.
		@param data Pointer to IScriptRequestData. Accepts "Text Color", swatch object or en_Nothing on set, returns "Text Color" string or swatch object on get.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRUID
		@param useTextColor - typically text attributes for color allow "Text Color" string as valid value, clients can configure to not allow "Text Color" for a particular attribute.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessColor(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass, const bool16 useTextColor = kTrue);

	/** AccessLineTypeAttribute. Get/Set a line type attribute.
		@param data Pointer to IScriptRequestData. Calls IPathStrokerUtils::GetStrokeStyleForSetProperty() on set, IPathStrokeUtils::GetStrokeStyleForGetProperty() on get.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRSTROKETYPE.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessLineTypeAttribute(IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass);

	/** AccessFont. Get/Set a font attribute.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param fontClass Boss must implement IID_ITEXTATTRUID
		@param styleClass Boss must implement IID_ITEXATTRUID
		@param strand One of kCharAttrStrandBoss or kParaAttrStrandBoss
		@param returnFontName If kTrue, display family name is returned, otherwise Script object for the font.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessFont(IScriptRequestData* data, const ScriptID& propID, const ClassID& fontClass,
							const ClassID& styleClass, const ClassID& strand = kCharAttrStrandBoss, bool16 returnFontName = kFalse);

	/** AccessFontStyle. Get/Set a font style attribute.
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param fontClass Boss must implement IID_ITEXTATTRUID
		@param styleClass Boss must implement IID_ITEXATTRUID
		@param strand One of kCharAttrStrandBoss or kParaAttrStrandBoss
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessFontStyle(IScriptRequestData* data, const ScriptID& propID, const ClassID& fontClass,
								const ClassID& styleClass, const ClassID& strand = kCharAttrStrandBoss);

	/** GetAttributeReport
		@param attrClass Boss must implement IID_IATTRREPORT
		@param attrReport Reference to InterfacePtr which will be reset with the boss of the requested class
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	GetAttributeReport(const ClassID& attrClass, InterfacePtr<const IAttrReport>& attrReport);

	/** Add Attribute.
		@param addAttr Pointer to attribute boss.
		@param targetDB Pointer to IDataBase. Only used by FindChange objects.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AddAttribute(const IPMUnknown* addAttr, IDataBase* targetDB = nil);

	/** AddAttributes.
		@param addAttrList Reference to AttributeBossList
		@param targetDB Pointer to IDataBase. Only used by FindChange objects.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AddAttributes( const AddAttributeList& addAttrList, IDataBase* targetDB = nil ) ;

	/** RemoveAttribute.
		@param removeAttr The ClassID of the attribute to be removed.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	RemoveAttribute( const ClassID& removeAttr ) ;

	/** RemoveAttributes
		@param removeAttrList Reference to AttributeBossList containing attributes to be removed.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	RemoveAttributes( const RemoveAttributeList& removeAttrList ) ;

	/** ApplyScriptCmd. Apply the attributes added and/or removed.
		@return kSuccess if successful or returns an error code. Returns kInvalidParameterError if attempting to remove attributes from a text object
	*/
	ErrorCode	ApplyScriptCmd() ;
    
    /** AccessDesignAxes
     @param data data Pointer to IScriptRequestData expected to contain design axes of variable font.
     @param propID ScriptID of the property to be accessed, should be p_DesignAxes.
     @param fontClass Boss must implement IID_ITEXTATTRUID
     @param styleClass Boss must implement IID_ITEXATTRUID
     @param strand One of kCharAttrStrandBoss or kParaAttrStrandBoss
     @return kSuccess if successful or returns an error code.
     */
    ErrorCode   AccessDesignAxes( IScriptRequestData* data, const ScriptID& propID, const ClassID& fontClass, const ClassID& styleClass, const ClassID& strand = kCharAttrStrandBoss );
    
    /** AccessDesignAxes
     @param data data Pointer to IScriptRequestData expected to contain index and value of design axis of variable font.
     @param script Pointer to script boss, see comments at top of file.
     @param fontClass Boss must implement IID_ITEXTATTRUID
     @param styleClass Boss must implement IID_ITEXATTRUID
     @param strand One of kCharAttrStrandBoss or kParaAttrStrandBoss
     @return kSuccess if successful or returns an error code.
     */
    ErrorCode SetNthDesignAxis(IScriptRequestData* data, IScript* script, const ClassID& fontClass, const ClassID& styleClass, const ClassID& strand = kCharAttrStrandBoss );
    
protected:
	/** GetScript
		@return IScript*
	*/
	IScript*	GetScript() const { return fScript ; }

	/** GetTargetScript
		@return IScript*
	*/
	IScript*	GetTargetScript() const { return fTargetScript ; }

	/** GetObjectType
		@return ScriptID&
	*/
	const ScriptID&	GetObjectType() const { return fObjectType ; }

	/** CacheCurrentAttrs. The GetAttributeReport() method calls this method
	once to cache the attributes for the given script object. It then returns
	references to the cached attribute bosses.
	*/
	void		CacheCurrentAttrs() ;

	/** AccessMultiplierAttribute
		@param data Pointer to IScriptRequestData.
		@param propID ScriptID of the property to be accessed.
		@param attrClass Boss must implement IID_ITEXTATTRREALNUMBER
		@param multiplier Returned values are multiplied by this value, set values are divided by this value.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode	AccessMultiplierAttribute( IScriptRequestData* data, const ScriptID& propID, const ClassID& attrClass, const PMReal& multiplier);

	/** IsFindChangeObject
		@param objectType to check.
		@return bool16 kTrue if the the specified ObjectType is one of the following: c_FindPref, c_ChangePref, c_FindTextPref, c_ChangeTextPref, c_FindGrepPref, c_ChangeGrepPref, c_FindTransliteratePref, c_ChangeTransliteratePref, c_FindGlyphPref or c_ChangeGlyphPref. kFalse otherwise.
	*/
	bool16		IsFindChangeObject(const ScriptID& objectType);

	/** QueryFontFamilyFromScript
		@param data Pointer to IScriptRequestData expected to contain string type of the display family name.
		@param propID ScriptID of the property to be accessed, should be p_TextFont.
		@param fontStyle Desired style name of the font
		@return IFontFamily*
	*/
	IFontFamily *QueryFontFamilyFromScript(IScriptRequestData* data, const ScriptID& propID, PMString fontStyle);

	/** QueryFontFamilyFromModel
		@param data Pointer to IScriptRequestData.
		@param fontClass Boss must implement IID_ITEXTATTRUID
		@param fontStyle Ignored argument
		@return IFontFamily* Pointer to queried IFontFamily
	*/
	IFontFamily *QueryFontFamilyFromModel(IScriptRequestData* data, const ClassID& fontClass, PMString fontStyle);

    

private:
	InterfacePtr<IScript>			fScript;
	InterfacePtr<IScript>			fTargetScript;
	const RequestContext			fRequestContext;
	const ScriptID					fObjectType;
	InterfacePtr<IComposeScanner>	fComposeScanner;	//"get" cache
	ScopedAttributeList				fStyleAttrs;		//"get" cache
	InterfacePtr<IPMUnknown>		fAttrInterface;		//"get" cache
	const AttributeBossList*		fCurrentAttrs;		//"get" cache
	AddAttributeList				fAddAttrList;		//"set" cache
	RemoveAttributeList				fRemoveAttrList;	//"set" cache
	IDataBase*						fTargetDB;			//"set" cache
	ClassID							fTargetStrand;		//"set" cache
};

/** Accessor class
*/
template<class T, class S> class Accessor
{
public:
	/**	Construct a new Accessor
		@param parent
		@param map
		@param mapSize
		@param boss
	*/
	Accessor( TextAttrScriptUtility* parent, const ScriptIDEnumMapEntry* map, size_t mapSize, const ClassID& boss ) :
		fScriptUtils(parent),
		fMap(map, mapSize),
		fAttrClass(boss)
		{}

	/** Access
		@param data Pointer to IScriptRequestData.
		@param script Pointer to script boss, see comments at top of file.
		@param propID ScriptID of the property to be accessed.
		@return kSuccess if successful or returns an error code.
	*/
	ErrorCode Access( IScriptRequestData* data, IScript* script, const ScriptID& propID ) ;

private:
	TextAttrScriptUtility	*fScriptUtils;
	const ClassID&		fAttrClass;
	ScriptIDEnumMap		fMap;
};

template<class T, class S> ErrorCode Accessor<T,S>::Access( IScriptRequestData* data, IScript* script, const ScriptID& propID )
{
	ErrorCode err;
	ScriptData scriptData;
	if (data->IsPropertyGet())
	{
		InterfacePtr<const IAttrReport> attrReport;
		err = fScriptUtils->GetAttributeReport(fAttrClass, attrReport);
		if (err == kUnSetError)
		{
			scriptData.SetEnumeration(en_Nothing);
			data->AppendReturnData( script, propID, scriptData ) ;
			return kSuccess;
		}

		if (err != kSuccess) return err;

		InterfacePtr<const T> attr(attrReport, UseDefaultIID());
		if (!attr) return kFailure;

		return fMap.GetForGetProperty( script, data, propID, attr->Get() ) ;
	}
	else if (data->IsPropertyPut())
	{
		err = data->ExtractRequestData(propID, scriptData);
		if (err != kSuccess) return err;

		if (Utils<IScriptUtils>()->IsNothing( scriptData ))	// removing an attribute
		{
			err = fScriptUtils->RemoveAttribute( fAttrClass ) ;
		}
		else						// adding/modifying an attribute
		{
			int32 val(0);
			err = fMap.GetForSetProperty( script, data, propID, val ) ;
			if (err != kSuccess) return err;

			InterfacePtr<T> attrR(::CreateObject2<T>(fAttrClass));
			if (!attrR) return kFailure;

			attrR->Set(static_cast<S>(val));
			err = fScriptUtils->AddAttribute( attrR ) ;
		}

		return err ;
	}

	return kFailure ;
}

#endif	//__TextAttrScriptUtility__
