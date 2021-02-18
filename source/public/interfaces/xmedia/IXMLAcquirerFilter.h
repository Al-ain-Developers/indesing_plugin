//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLAcquirerFilter.h $
//  
//  Owner: lance bushore
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
//  This interface is used for action components to update the state of their actions.
//  It is NOT a standard boss interface - it does not inherit from IPMUnknown!
//  
//========================================================================================

#pragma once
#ifndef __IXMLAcquirerFilter__
#define __IXMLAcquirerFilter__

#include "XMLID.h"

class IPMStream;
class IImportXMLData;
class ISAXEntityResolver;

typedef std::pair<InterfacePtr<IPMStream>, InterfacePtr<ISAXEntityResolver> > StreamResolverPair;

class IXMLAcquirerFilter : public IPMUnknown 
{
	public:
		enum { kDefaultIID = IID_IXMLACQUIRERFILTER };
	
	/**
		Use this method to find out how many filetypes this particular filter supports

		@return the number of filetypes supported
	*/
		virtual int32 GetFileTypeCount() const = 0;

	/**
		Get the information about the nth filter

		@param n			IN	which filetype client wants to know about
		@param family		OUT	The file type family (Pretty much always XML)
		@param extension	OUT	The Windows file extension
		@param type			OUT	The Mac filetype
	*/
		virtual void GetNthFileType(int32 n, PMString *family, PMString *extension, SysOSType *type) const = 0;

	/**
		Create a read stream based on the import data. Also create an entity resolver to 
		use when parsing the stream.
		@param	importData						IN	The data of import information.
		@param	errCode							OUT	An error code. Must not be nil.
		@return	the stream and entity resolver. Return nil for both the stream and the resolver if the
												provider can't create a stream. Return nil for the
												resolver if this provider doesn't want to create its
												own resolver.
	*/
		virtual StreamResolverPair CreateStreamAndResolver(IImportXMLData *importData, ErrorCode *errCode) const = 0;

		
	/**
		Create an entity resolver to use when parsing the stream.
		@return	the entity resolver.	Return nil if this provider doesn't support
		@param	importData				IN	The data of import information.
		@param	errCode					OUT	An error code. Must not be nil.
										this file or if it doesn't want to create 
										a special entity resolver.
	*/
		virtual ISAXEntityResolver *CreateResolver(IImportXMLData *importData, ErrorCode *errCode) const = 0;
};

#endif // __IXMLAcquirerFilter__