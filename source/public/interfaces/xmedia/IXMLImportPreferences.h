//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportPreferences.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLImportPreferences__
#define __IXMLImportPreferences__


#include "IPMUnknown.h"
#include "XMLID.h"

class IXMLImportOptionsPool;

/** 
Interface for getting and setting the individual XML import options.
*/
class IXMLImportPreferences : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLIMPORTPREFERENCES };

	/** 
	Enumerates the different types of storage 
	available for preferences. 
	*/
	enum kPrefType {
		/** Stored as a bool16*/
		kBool16, 
		/** Stored as an int32*/
		kInt32, 
		/** Stored as a WideString*/
		kWideString};

	/**
	Initialize the stored data. This is the only method
	that will need to be overridden if you inherit from
	CXMLImportPreferences rather than this file.

	Note: Because this class doesn't know when you are done
	with the data you need to call Uninitialize when you are
	done with it.

	Use stack based helper class XMLImportPreferencesInitializer
	below to avoid missing calling Uninitialize.

	@param pool - The pool which owns the preferences
	@see CXMLImportPreferences.h
	@see Uninitional
	*/
	virtual void Initialize(IXMLImportOptionsPool *pool) = 0;

	/**
	Uninitialize the stored data. You need to override
	this method if you store your own data locally.
	*/
	virtual void Uninitialize() = 0;

	/**
	Get the number of preference held by this object
	@return - The number of preferences you can get/set
	*/
	virtual int32 GetPrefCount() const = 0;
	
	/**
	Indicates what type of data a specific preference uses
	as its value.
	@param n - The preference you want to gather info about.
	*/
	virtual kPrefType GetNthPrefType(int32 n) const = 0;

	/**
	Get the value of the specified preference as an int32
	@param n - The preference you want to know about
	@return - The int32 this preference is currently set to
	*/
	virtual int32 GetNthPrefAsInt(int32 n) const = 0;
	
	/**
	Get the value of the specified preference as a bool16
	@param n - The preference you want to know about
	@return - The bool value this preference is currently set to
	*/
	virtual bool16 GetNthPrefAsBool(int32 n) const = 0;
	
	/**
	Get the value of the specified preference as a WideString
	@param n - The preference you want to know about
	@return - The string this preference is currently set to
	*/
	virtual WideString GetNthPrefAsString(int32 n) const = 0;

	/**
	Set the int32 value of a particular preference
	@param n - The preference you want changed
	@param newVal - The new value you want the preference set to
	*/
	virtual void SetNthPref(int32 n, const int32 &newVal) = 0;

	/**
	Set the bool16 value of a particular preference
	@param n - The preference you want changed
	@param newVal - The new value you want the preference set to
	*/
	virtual void SetNthPref(int32 n, const bool16 &newVal) = 0;

	/**
	Set the string value of a particular preference
	@param n - The preference you want changed
	@param newVal - The new value you want the preference set to
	*/
	virtual void SetNthPref(int32 n, const WideString &newVal) = 0;

	/** 
	Commit the stored changes to the preferences.  Until this method has
	been called the changes made by calling SetNthPref() don't really 
	get moved into the preferences. Call this method after each of the
	changes for this set of preferences has been set appropriately
	*/
	virtual void CommitChanges() = 0;
};

/** This is a stack-based helper class that makes sure that
	IXMLImportPreferences::Uninitialize() is called when it's 
	out of scope.
    @see IXMLImportPreferences
*/
class XMLImportPreferencesInitializer
{
public:
	XMLImportPreferencesInitializer(IXMLImportPreferences* prefs, IXMLImportOptionsPool* prefsPool)
		: fPrefs(prefs)
	{
		if (fPrefs != nil)
			fPrefs->Initialize(prefsPool);
	}

	~XMLImportPreferencesInitializer()
	{
		if (fPrefs != nil)
			fPrefs->Uninitialize();
	}

private:
    IXMLImportPreferences* fPrefs;
};

#endif	// __IXMLImportPreferences__

