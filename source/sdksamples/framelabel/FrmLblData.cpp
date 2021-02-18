//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblData.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:

// General includes:
#include "IPMStream.h"
#include "CPMUnknown.h"

// Project includes:
#include "IFrmLblData.h"
#include "FrmLblID.h"
#include "FrmLblType.h"

// forward declarations
class IPMStream;


/** Stores persistent data to control the display of
	the frame label adornment; implements IFrmLblData.
  
	@ingroup framelabel
	
*/
class FrmLblData : public CPMUnknown<IFrmLblData>
{
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		FrmLblData(IPMUnknown*  boss);
		/** 
			Destructor.
		*/
		virtual ~FrmLblData();

		/**
			Stores new persistent values for the label adornment. 
			@param the label properties to be displayed as the label.
		*/
		virtual void Set(const FrmLblInfo& frmLblInfo);

		/** 
			Retrieves the current frame label property to be displayed as the adornment.
			@return The frame label properties.
		*/
		virtual const FrmLblInfo& Get() const { return fFrmLblInfo; }

		/** Saves persistently, reads persistent data.
			Reads if the stream is a 'read-stream'
			and writes if the stream is a write stream:
		*/
		void ReadWrite(IPMStream*  stream, ImplementationID implementation);

	private:
		FrmLblInfo fFrmLblInfo;
};


/* CREATE_PERSIST_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PERSIST_PMINTERFACE(FrmLblData, kFrmLblDataImpl)

/* FrmLblData Constructor
	The initial values in the member values indicate the default persistent values.
	Also see the SchemaList resource in FrmLbl.fr.
*/
FrmLblData::FrmLblData(IPMUnknown* boss) : 
		CPMUnknown<IFrmLblData>(boss),
		fFrmLblInfo(WideString(kFrmLblDefaultLabel), 
					kFrmLblDefaultPointSize, 
					kFrmLblDefaultVisibility,
					kFrmLblDefaultColor,
					kFrmLblBottom
					)
{
}

/* FrmLblData Destructor
*/
FrmLblData::~FrmLblData()
{
	// Add code to delete extra private data, if any.
}

void FrmLblData::Set(const FrmLblInfo& frmLblInfo)
{
	PreDirty ();
	this->fFrmLblInfo = frmLblInfo;
}

/* ReadWrite

	DATA FORMAT HISTORY: 
		See SchemaList in FrmLbl.fr
*/
void FrmLblData::ReadWrite(IPMStream* stream, ImplementationID implementation)
{
	fFrmLblInfo.label.ReadWrite(stream);
//	stream->XferInt32(fFrmLblInfo.width);
	stream->XferInt32(fFrmLblInfo.pointSize);
	stream->XferBool(fFrmLblInfo.visibility);
	stream->XferReference(fFrmLblInfo.fontColor);
	stream->XferEnum(fFrmLblInfo.position);
}






