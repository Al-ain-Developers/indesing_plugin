//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CXMLImportPreferences.h $
//  
//  Owner: Ryan Gano
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

#include "IXMLImportPreferences.h"

#include "WideString.h"
#include "K2Vector.tpp"

struct SinglePref
{
	typedef object_type data_type;

	SinglePref(const WideString &name, IXMLImportPreferences::kPrefType type, 
		int32 intVal = -1, bool16 boolVal = kFalse, const WideString &stringVal = WideString()) :
	fType(type), fValueName(name), fInt32Value(intVal), fBool16Value(boolVal), fWideStringValue(stringVal)
	{}

	IXMLImportPreferences::kPrefType	fType;
	WideString							fValueName;
	int32								fInt32Value;
	bool16								fBool16Value;
	WideString							fWideStringValue;
};

//----------------------------------------------------------------------------------------
// XMLImportOptionsDefaultServiceProvider
//----------------------------------------------------------------------------------------
class PUBLIC_DECL CXMLImportPreferences : public CPMUnknown<IXMLImportPreferences>
{
public:	
	CXMLImportPreferences(IPMUnknown *boss);
	
	// Use this to set each piece of data listed below
	virtual void Initialize(IXMLImportOptionsPool *pool);

	virtual void Uninitialize();
	
	virtual int32 GetPrefCount() const {return fPrefs.size();}
	virtual kPrefType GetNthPrefType(int32 n) const {return fPrefs[n].fType;}

	// Get the value of the nth pref
	virtual int32 GetNthPrefAsInt(int32 n) const {return fPrefs[n].fInt32Value;}
	virtual bool16 GetNthPrefAsBool(int32 n) const {return fPrefs[n].fBool16Value;}
	virtual WideString GetNthPrefAsString(int32 n) const {return fPrefs[n].fWideStringValue;}

	// Set the value of the nth pref
	virtual void SetNthPref(int32 n, const int32 &newVal) {fPrefs[n].fInt32Value = newVal;}
	virtual void SetNthPref(int32 n, const bool16 &newVal) {fPrefs[n].fBool16Value = newVal;}
	virtual void SetNthPref(int32 n, const WideString &newVal) {fPrefs[n].fWideStringValue = newVal;}

	// Commit stored changes. Override this to make sure the
	// stored values are valid than then call
	// CIXMLImportPreferences::CommitChanges() to actually
	// store the changes.
	virtual void CommitChanges();

protected:
	/** Use this to add a single preference easily. This method will check the 
	preference pool for the stored value based on the name and the type. If no
	preference could be found it will use the default value passed in.
	@param name - the name of the new preference
	@param type - The type of the new preference
	@param intVal - The suggested integer value of the preference
	@param boolVal - The suggested bool value of the preference
	@param stringVal - The suggested string value of the preference
	*/
	void AddPreference(const WideString &name, IXMLImportPreferences::kPrefType type, 
						int32 intVal = -1, bool16 boolVal = kFalse, const WideString &stringVal = WideString());
	
	K2Vector<SinglePref>				fPrefs;
	InterfacePtr<IXMLImportOptionsPool>	fPool;
};	