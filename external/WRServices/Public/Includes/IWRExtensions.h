//========================================================================================
//  
//  File: IWRExtensions.h
//  
//  Owner: Pascal Rubini
//  
//  Copyright 2010 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2010.
//  
//========================================================================================
#ifndef __IWREXTENSIONS__
#define __IWREXTENSIONS__

#include "WRFontContextComponent.h"
#include "WRAttributes.h"

/// Interface to an extension
/**
When the IWRExtension returns information about a extension, both an entry point pointer and a pointer to private data are returned.
The pointer to the private data is passed back when a call to IWRClientSettings is made to release an extension.
**/

class WRSERVICES_DECL IWRExtension : public WRClass
{
public:
	virtual ~IWRExtension();
	virtual int Call(WRTag selector, void* paramBlock) = 0;	///< call the extension
	virtual IWRExtension* GetNext()const  = 0;				///< get the next extension in the extension list
	virtual WRExtensionCB	GetCallBack(void) const = 0;	///< get the entry point of the extension
	virtual void*	GetData(void) const  = 0;				///< get the private data of the extension
};

/// Interface to access extensions
/**
This interface is available on WRFontContext objects. Its purpose is to cache the list of extensions.
Extensions are stored in a single-linked list. The IWRExtensions::GetFirstExtension() returns the list
head, and then IWRExtension::GetNext() allows for iteration of the rest of the list, until NULL.
**/
class WRSERVICES_DECL IWRExtensions : public WRFontContextComponent
{
public :
	virtual ~IWRExtensions();
	virtual int	QueryExtensions() = 0;				///< query from the IWRClientSettings the list of available extension
	virtual int	ReleaseExtensions() = 0;			///< release all extensions in th extensionlist
	virtual IWRExtension* GetFirstExtension() = 0;	///< return the first extension in the extension list
} ;

#endif
