//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IDataTransform.h $
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
#ifndef __IDataTransform_h__
#define __IDataTransform_h__

#include "IPMUnknown.h"
#include "DataServicesID.h"

#include <map>

class ISAXAttributes;
class IDataServicesOptions;

/** Class responsible for data transformation.
*/
class IDataTransform : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDATATRANSFORM };
	enum { kLowPriority = 0, kMediumPriority = 500, kHighPriority = 1000 };

	typedef std::map<PMString, PMString> Parameters;

	/** GetPriority returns the priority of the transform. The priority determines what
		order the transform get a chance at transforming the data.
		@return priority
	*/
	virtual int32 GetPriority() const = 0;

	virtual Parameters GetParameters(IDataServicesOptions* options, IPMStream* dataStream) const = 0;

	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream.
		@param dataStream specifies the stream containing the data.
		@param transformData specifies data that describes how the transformation.
		@return IPMStream
	 */
	virtual IPMStream* TransformStream(IDataServicesOptions* options, IPMStream* dataStream, IPMUnknown* transformData) = 0;

	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream. 
		@param dataStream specifies the stream containing the data.
		@param attrs specifies attributes that specify how to transform the stream.
		@return IPMStream
	 */
	virtual IPMStream* TransformStream(IDataServicesOptions* options, IPMStream* dataStream, ISAXAttributes* attrs, const Parameters& params) = 0;
	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream. This method assumes that the dataStream has information
		describing what transformation should be applied to the stream. For XML data this
		will typically be done with an xml-stylesheet processing instruction.
		@param dataStream specifies the stream containing the data.
		@return IPMStream
	 */
	virtual IPMStream* TransformStream(IDataServicesOptions* options, IPMStream* dataStream, const Parameters& params) = 0;

	/**	Transform a stream, typically XML from one format to another. Everything is stream
		based. Returns a new stream, which has been transformed. Caller is responsible for
		releasing the new stream. this method requires that the client pass in both the
		stream to be transformed and the stream to use for the transform.
		@param dataStream specifies the stream containing the data.
		@param xslStream specifies the stream containing the transform.
		@return IPMStream
	 */
	virtual IPMStream* TransformStream(IPMStream* dataStream, IPMStream* xslStream) = 0;
	
	
	/**	Returns true if this transform can transform the data given the transformData.
		@param dataStream specifies the stream containing the data to be transformed.
		@param transformData specified an interface that describes how the data should
		be transformed. The data usually contains a reference to a file that describes
		how to transform the data.
		@return bool16
	 */
	 virtual bool16 CanTransform(IDataServicesOptions* options, IPMStream *dataStream, IPMUnknown* transformData) const = 0;
	
	/**	Returns true if this transform can transform the data. The data either has the
		transform instructions embedded in the data or a reference to the transform
		instructions embedded in the data.
		@param dataStream specifies the stream containing the data to be transformed.
		@return bool16
	 */
	virtual bool16 CanTransform(IDataServicesOptions* options, IPMStream *dataStream) const = 0;
	
	/**	Returns true if this transform can transform the data using a transform language of
		type "type".
		@param attrs specifies attributes that specify how to transform the stream.
		@return bool16
	 */
	virtual bool16 CanTransform(IDataServicesOptions* options, IPMStream* dataStream, ISAXAttributes* attrs) const = 0;

	/**	Get the schema of the data source. The schema describes the data fields and may contain 
		additional information about the ui names of the data fields and the primary key.
		Here is an example:
			<table title="Contact Sheet">
				<schema key="key"/>
					<key type="text" uiname="Key">
					<image type="image" uiname="Image"/>
					<date type="text" uiname="Date"/>
					<filename type="text" uiname="File Name"/>
				</schema>
			</table>
		@param dataStream specifies the stream containing the data.
		@param transformData specifies data that describes how the transformation.
		@return IPMStream or nil if schema s not provided. Check for ErrorUtils::PMGetGlobalErrorCode().
	 */
	virtual IPMStream* GetSchema(IDataServicesOptions* options, IPMStream* dataStream, IPMUnknown* transformData) = 0;
	
		/**	Get the schema of the data source. The schema describes the data fields and may contain 
		additional information about the ui names of the data fields and the primary key.
		@param options ??
		@param dataStream specifies the stream containing the data.
		@param params specifies the parameters required by the transformer to transform the data
		@return IPMStream or nil if schema s not provided. Check for ErrorUtils::PMGetGlobalErrorCode().
	 */

	virtual IPMStream* GetSchema(IDataServicesOptions* options, IPMStream* dataStream, const Parameters& params) = 0;
};

#endif	// __IDataTransform_h__
