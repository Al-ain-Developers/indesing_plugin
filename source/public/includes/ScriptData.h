//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/ScriptData.h $
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
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#pragma once
#ifndef __ScriptData__
#define __ScriptData__

#include "KeyValuePair.h"
#include "K2TypeTraits.h"
#include "RequestContext.h"
#include <adobe/any_regular.hpp>
#include <adobe/vector.hpp>

class IScript;
class IUnitOfMeasure;
class IPMStream;
class IScriptCoreFunctor;
class ScriptData;

typedef adobe::vector< InterfacePtr<IScript> > ScriptList ;
typedef adobe::vector<ScriptData> ScriptListData ;
typedef KeyValuePair<ScriptID, ScriptData> ScriptIDValuePair ;
typedef adobe::vector<ScriptIDValuePair> ScriptRecordData ;

// Traits used by K2Vector
DECLARE_OBJECT_TYPE(ScriptList);
DECLARE_OBJECT_TYPE(ScriptListData);
DECLARE_OBJECT_TYPE(ScriptRecordData);

using namespace ScriptInfo ;

/**
	ScriptData is a class that can hold any of the data types supported by the 
	scripting architecture.
*/
class PUBLIC_DECL ScriptData
{
public:
	typedef object_type data_type ;

	ScriptData() : fDataType( s_empty ), fValue()
	{ }
	virtual ~ScriptData(){}
	ScriptData(const ScriptData& other) : fDataType( other.fDataType ), fValue( other.fValue )
	{ }
	explicit ScriptData(int16 integer, bool16 isBoolean = kFalse);
	explicit ScriptData(int32 integer);
	explicit ScriptData(int64 integer);
	explicit ScriptData(ScriptID enumerator);
	explicit ScriptData(PMReal real);
	explicit ScriptData(const PMString& string);
	explicit ScriptData(const WideString& string);
	explicit ScriptData(IScript* object);
	explicit ScriptData(IPMStream* stream);
	explicit ScriptData(const ScriptList& objectList);
	explicit ScriptData(const ScriptListData& list);
	explicit ScriptData(const ScriptRecordData& record);
	explicit ScriptData(uint64 date);
	explicit ScriptData(const IDFile& file);
	
	enum ScriptDataType	{
		s_empty,		// nothing
		s_boolean, 		// bool16
		s_string,		// PMString
		s_shortint,		// int16
		s_longint,		// int32
		s_longlongint,	// int64
		s_double,		// PMReal
		s_object,		// IScript
		s_objectlist,	// ScriptList (may contain 0, 1, or more Script objects)
		s_list,			// ScriptListData
		s_date,			// uint64
		s_file,			// IDFile
		s_enumeration,	// int32
		s_unit,			// PMReal in points
		s_record,		// ScriptRecordData
		s_stream,		// IPMStream
		s_function		// IScriptFunctor
	};

	virtual ScriptData::ScriptDataType GetType() const { return fDataType; }
	virtual bool16 IsEmpty() const { return fDataType == s_empty ; }

	void SetBoolean(bool16 boolean);
	ErrorCode GetBoolean(bool16* const boolean) const;

	void SetInt16(int16 integer);
	ErrorCode GetInt16(int16* const integer) const;

	void SetInt32(int32 integer);
	ErrorCode GetInt32(int32* const integer) const;

	void SetInt64(int64 integer);
	ErrorCode GetInt64(int64* const integer) const;

	void SetEnumeration(ScriptID enumeration ) ;
	ErrorCode GetEnumeration(ScriptID* const enumeration) const;

	void SetPMReal(PMReal real);
	ErrorCode GetPMReal(PMReal* const real) const;

	void SetPMString(const PMString& string);
	ErrorCode GetPMString(PMString& string) const;

	/** Stores a WideString as the value of this instance.
	    @param string IN The string value to set.
	*/
	virtual void SetWideString(const WideString& string);

	/** Gets the value as a WideString.
	    @param string OUT The current value as a WideString.
		@return kSuccess if the value can be represented as a WideString
		        an error code otherwise
	*/
	virtual ErrorCode GetWideString(WideString& string) const;

	void SetObject( IScript* object ) ;
	IScript* QueryObject() const ;

	void SetObjectList( const ScriptList& objectList ) ;
	ErrorCode GetObjectList( ScriptList& objectList ) const ;
		//Note: Will convert a single script object or a ScriptListData of objects into an object list

	void SetStream( IPMStream* stream ) ;
	IPMStream* QueryStream() const ;

	void SetFunction( IScriptCoreFunctor* func ) ;
	IScriptCoreFunctor* QueryFunction() const ;

	void SetList( const ScriptListData& list );
	ErrorCode GetList( ScriptListData& list ) const ;

	void SetRecord( const ScriptRecordData& record );
	ErrorCode GetRecord( ScriptRecordData& record ) const ;

	void SetDate(uint64 date);
	ErrorCode GetDate(uint64* const date) const;

	void SetFile( const IDFile& file ) ;
	/** Retrieve the value as an IDFile. If the value is a PMString, assume it is a file path.
		@param file - the value returned
		@param context - Before CS5, on the MacOS, if the value of the ScriptData object was 
		a PMString, the GetFile method checked first for a HFS path, then for a posix path. As 
		of CS5, the reverse is true. This change is versioned via the RequestContext parameter.
		@param validateFolder - If kTrue, will return a kDirectoryNotFoundError if the parent
		folder doesn't exist.
		@return - kSuccess or kNoDataOfTheRequestedTypeError
	*/
	ErrorCode GetFile( IDFile* const file, const RequestContext& context,  bool16 validateFolder = kTrue ) const ;
	/** Retrieve the value as an IDFile IF the value is an IDFile. Does not translate a PMString.
		@param file - the value returned
		@param validateFolder - If kTrue, will return a kDirectoryNotFoundError if the parent
		folder doesn't exist.
		@return - kSuccess or kNoDataOfTheRequestedTypeError
	*/
	ErrorCode GetFileIfFile( IDFile& file, bool16 validateFolder = kTrue ) const ;

	/**	HOW UNITS WORK
		On input: The user can pass in a numerical value or a string like "1in" and a 
		ScriptProvider can ask for this data as a unit. If user passed in a string, it 
		will get converted to points accordingly, so for "1in" you'll get 72 points, 
		for 1 we'll check what the horizontal or vertical ruler were when the event 
		came in and convert the value to points. So for example if the user passes in 5 
		and their horizontal ruler is in ciceros and the ScriptProvider asks for the the 
		horizontal value, we'll assume 5 means 5 ciceros, convert it to the proper number 
		of points and give you back that value.

		On output: The provider can call SetUnit, pass in a PMReal representing points and 
		indicate whether the data represents a horizontal or vertical value. We will then 
		convert this value to the appropriate units based on what the user's ruler settings 
		were at the time the event came in.

		In scripting DOM verersion CS5 (kCS5ScriptVersion) or later, a measurement unit is 
		added to the script engine's preference. @See IScriptPreferences.
		If the preference has a valid measurement unit:
		On input, if a numerical value is passed in, we assume the type is the one in the preference.
		On output, the passed in value representing points will be converted to the type stored in the preference.
	*/
	/**	See also IUnitOfMeasureSettings.h for information on unit of measure types */
	enum UnitType
	{
		kXCoordinate,	// Value is in XUnitOfMeasure
		kYCoordinate,	// Value is in YUnitOfMeasure
		kPoints,		// Value is in points
		kTextUnits,		// Value is in TextUnitUnitOfMeasure
		kTextSizeUnits,	// Value is in TextSizeUnitOfMeasure
		kLineUnits		// Value is in LineUnitOfMeasure
	};

	/**	
		Assume "unit" is a value in points.
		In scripting DOM verersion CS5 (kCS5ScriptVersion) or later, if the script engine's preference has a valid measurement unit,
		we convert "unit" to the type stored in the preference. unitType is ignored.
		In earlier versions or if the preference doesn't have a valid measurment type, 
		we convert "unit" to units of "unitType". 
	*/
	void SetUnit			( const PMReal& unit, UnitType unitType, const IScript* script, const EngineContext& context ) ;
	/**	Assume "unit" is a value in points, convert it using "unitOfMeasure" and store it */
	void SetUnit			( const PMReal& unit, IUnitOfMeasure* unitOfMeasure ) ;
	/**	
		Convert a unit type in ScritData to points and return it.
		Script providers should call this method to get the value of a unit.

		In scripting DOM verersion CS5 (kCS5ScriptVersion) or later, if the script engine's preference has a valid measurement unit,
		we assume ScriptData hold a value in the preference's unit. unitType is ignored.
		In earlier versions or if the preference doesn't have a valid measurment type, 
		we assume ScriptData holds a value in units of "unitType".

		In kCS5ScriptVersion or later, if the unit value is NaN and allowNaN is kFalse, kNaNError is returned.
	*/
	ErrorCode GetUnit		( PMReal* const unit, UnitType unitType, const IScript* script, const EngineContext& context, bool16 allowNaN = kFalse ) const ;
	/**	Assume ScriptData holds a value in units and return it */
	ErrorCode RetrieveUnit	( PMReal* const unit ) const ;
	/**	Assume ScriptData holds a value in units of "unitOfMeasure", convert it to points and return it */
	ErrorCode ParseUnit		( PMReal* const unit, IUnitOfMeasure* unitOfMeasure ) const ;
	/**	Assume ScriptData holds a value in units of some type, return a value in units corresponding to the enumerated ScriptID */
	ErrorCode ConvertUnit	( PMReal* const real, const ScriptID& unitType, const RequestContext& context ) const ;
	/**	Assume ScriptData holds a value in units of some type, return a formatted string */
	ErrorCode ConvertUnit	( PMString& string ) const ;

	/** Comparison operator (will call IScript::IsEqual on objects) */
	bool16 IsEqual( const ScriptData& scriptData, const RequestContext& context ) const ;
	/** Comparison operator (will test IScript* for equality on objects) */
	bool16 operator==( const ScriptData& scriptData ) const ;
	
	/** Comparison operator (will test IScript* for equality on objects) */
	friend inline bool16 operator!=( const ScriptData& left, const ScriptData& right )
	{ return !(left == right); }

	/** Defining swap() ensures efficient swapping of ScriptData objects by swapping the remote parts.
	 */
	friend inline void swap( ScriptData& left, ScriptData& right )
	{
		using namespace std;
		swap(left.fValue, right.fValue);
		swap(left.fDataType, right.fDataType);
	}
	
	/** Movable constructor - assumes ownership of the remote part
	 */
	ScriptData(adobe::move_from<ScriptData> other) : fValue(adobe::move(other.source.fValue)), fDataType(adobe::move(other.source.fDataType))
	{ }

	/** operator assignment on a movable type takes parameter by value and consumes it
	 */
	ScriptData& operator=(ScriptData other)
    { swap(*this, other); return *this; }

	/** Clear this object */
	virtual void Reset();

	/** ReadWrite this object. Only implemented for non-object data types. */
	virtual void ReadWrite( IPMStream* s, bool16 doPlatformReadWrite = kTrue ) ;

	/**
		Convert the type into a string representation
		@param context for the conversion
		@return the string representation
	*/
	PMString	GetTypeAsString( const RequestContext& context ) const ;

	/**
		Convert the value into a string representation
		@param context for the conversion
		@return the string representation
	*/
	PMString	GetValueAsString( const RequestContext& context ) const ;

private:
    
	/** Check if a PMReal is NaN */
	bool16 IsNaN(const PMReal* real) const;

	ScriptDataType fDataType;	
	
	adobe::any_regular_t fValue;	
};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_0("scriptid:indesign:adobe",ScriptID)
ADOBE_NAME_TYPE_0("scriptdata:indesign:adobe",ScriptData)

DEFINEK2READWRITE( ScriptData ) ;

#endif
