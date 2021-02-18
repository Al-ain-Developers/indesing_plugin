//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IDataServices.h $
//  
//  Owner: Michael Burbidge
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
#ifndef __IDataServices_h__
#define __IDataServices_h__

#include "IPMUnknown.h"
#include "IDataTransform.h"
#include "DataServicesID.h"

/**	IDataServices is the primary interface for working with the XML data service. A data
	service is primarily a transformation that can be applied to an XML document.
*/
class IDataServices : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATASERVICES };
	
	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream.
		@param stream specifies the stream containing the data.
		@param transformData specifies data that describes how the transformation.
		@return IPMStream
	 */
	virtual IPMStream* TransformContent(IPMStream* stream, IPMUnknown* transformData = nil) const = 0;
	
	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream.
		@param stream specifies the stream containing the data.
		@param params specifies parameters that should be used for the transformation. 
		@param transformData specifies data that describes how the transformation.
		@return IPMStream
	 */

	virtual IPMStream* TransformContent(IPMStream* stream, IDataTransform::Parameters& params, bool16 defaultParams = kTrue) = 0;

	/**	Get the schema of the data source. The schema describes the data fields and may contain 
		additional information about the ui names of the data fields and the primary key.
		Here is an example:
			<table title="Contact Sheet" type="csv">
				<schema>
					<key type="text" uiname="Key"/>
					<image type="image" uiname="Image"/>
					<date type="text" uiname="Date"/>
					<filename type="text" uiname="File Name"/>
				</schema>
			</table>
		@param dataStream specifies the stream containing the data.
		@param defaultParams if true use default parameters else retrieve parameteres via UI
		@return IPMStream or nil if schema s not provided. Check for ErrorUtils::PMGetGlobalErrorCode().
	 */
	virtual IPMStream* GetSchema( IPMStream* stream, IDataTransform::Parameters& params, bool16 defaultParams = kTrue ) = 0;
};

#endif	// __IDataServices_h__
