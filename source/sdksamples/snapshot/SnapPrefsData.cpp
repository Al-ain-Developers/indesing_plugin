//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapPrefsData.cpp $
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
//  
//  SnapPrefsData is the non-persistent implementation of ISnapPrefsData. 
//  
//========================================================================================

#include "VCPlugInHeaders.h"
 
// Interface includes:
#include "IPMStream.h"
 
// General includes:
#include "CPMUnknown.h"

// project includes:
#include "SnapID.h"
#include "ISnapPrefsData.h"

/** SnapPrefsData

	The non-persistent implementation of ISnapPrefsData.
	
	@ingroup snapshot
*/
class SnapPrefsData : public CPMUnknown<ISnapPrefsData>
{
	public:
		SnapPrefsData(IPMUnknown* boss);

		virtual ~SnapPrefsData();

   		virtual void CopyPrefs(ISnapPrefsData* prefsToCopy);
   		
		virtual void SetName(const WideString& name);

		virtual const WideString& GetName();

		virtual void SetFormatClassID(const ClassID& formatClassID);

		virtual const ClassID& GetFormatClassID();
		
		virtual void SetScale(const PMReal& scale);

		virtual const PMReal& GetScale();


		virtual void SetResolution(const PMReal& resolution);

		virtual const PMReal& GetResolution();

		virtual void SetMinimumResolution(const PMReal& minimumResolution);

		virtual const PMReal& GetMinimumResolution();

		virtual void SetBleed(const PMReal& bleed);

		virtual const PMReal& GetBleed();

		virtual void SetDrawArea(bool16 drawArea);

		virtual const bool16& GetDrawArea();

		virtual void SetFullResolutionGraphics (bool16 fullResolutionGraphics);

		virtual const bool16& GetFullResolutionGraphics();

		virtual void SetDrawGray(bool16 drawGray);

		virtual const bool16& GetDrawGray();

		virtual void SetDrawingFlags (int32 drawingFlags);

		virtual const int32& GetDrawingFlags();

		virtual void SetJPEGEncoding(const int32 encoding);

		virtual const int32& GetJPEGEncoding();

		virtual void SetJPEGQuality(const int32 quality);

		virtual const int32& GetJPEGQuality();

		virtual void SetTIFFPaletteType(const int32 paletteType);

		virtual const int32& GetTIFFPaletteType();

		virtual void SetGIFPaletteType(const int32 paletteType);

		virtual const int32& GetGIFPaletteType();

		virtual void SetTIFFTransparent(const bool16 transparent);

		virtual const bool16& GetTIFFTransparent();

		virtual void SetGIFTransparent(const bool16 transparent);

		virtual const bool16& GetGIFTransparent();

		virtual void SetGIFInterlaced(const bool16 interlaced);

		virtual const bool16& GetGIFInterlaced();

	private:

		WideString fName;
		ClassID fFormatClassID;
		PMReal fScale;
		PMReal fResolution;
		PMReal fMinimumResolution;
		PMReal fBleed;
		bool16 fDrawArea;
		bool16 fFullResolutionGraphics; 
		bool16 fDrawGray;
		int32 fDrawingFlags;
		int32 fJPEGEncoding;
		int32 fJPEGQuality;
		int32 fTIFFPaletteType;
		int32 fGIFPaletteType;
		bool16 fTIFFTransparent;
		bool16 fGIFTransparent;
		bool16 fGIFInterlaced;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its 
 ImplementationID making the C++ code callable by the 
 application.
*/
CREATE_PMINTERFACE(SnapPrefsData, kSnapPrefsDataImpl)


/* Constructor
*/
SnapPrefsData::SnapPrefsData(IPMUnknown* boss) : 	
		CPMUnknown<ISnapPrefsData>(boss),
		fName(""),
		fFormatClassID(kInvalidClass),
		fScale(1.0),
		fResolution(kDefaultResolution),
		fMinimumResolution(kDefaultResolution),
		fBleed(0.0),
		fDrawArea(kFalse),
		fFullResolutionGraphics(kFalse),
		fDrawGray(kFalse),
		fDrawingFlags(0),
		fJPEGEncoding(SnapshotUtils::kSSJPEGBaseline),
		fJPEGQuality(SnapshotUtils::kSSJPEGExcellentQuality),
		fTIFFPaletteType(SnapshotUtils::kNoPalette),
		fGIFPaletteType(SnapshotUtils::kTryExactThenAdaptivePalette),
		fTIFFTransparent(kFalse),
		fGIFTransparent(kFalse),
		fGIFInterlaced(kFalse)
{
}

/* Destructor.
*/
SnapPrefsData::~SnapPrefsData()
{
}

/* CopyPrefs
*/
void SnapPrefsData::CopyPrefs(ISnapPrefsData* prefsToCopy)
{
	SetName(prefsToCopy->GetName()); 
	SetFormatClassID(prefsToCopy->GetFormatClassID()); 
	SetScale(prefsToCopy->GetScale());
	SetResolution(prefsToCopy->GetResolution());
	SetBleed(prefsToCopy->GetBleed());
	SetDrawArea(prefsToCopy->GetDrawArea());
	SetFullResolutionGraphics(prefsToCopy->GetFullResolutionGraphics());
	SetDrawGray(prefsToCopy->GetDrawGray());
	SetMinimumResolution(prefsToCopy->GetMinimumResolution());
	SetDrawingFlags(prefsToCopy->GetDrawingFlags());
	SetJPEGEncoding(prefsToCopy->GetJPEGEncoding());
	SetJPEGQuality(prefsToCopy->GetJPEGQuality());
	SetTIFFPaletteType(prefsToCopy->GetTIFFPaletteType());
	SetGIFPaletteType(prefsToCopy->GetGIFPaletteType());
	SetTIFFTransparent(prefsToCopy->GetTIFFTransparent());
	SetGIFTransparent(prefsToCopy->GetGIFTransparent());
	SetGIFInterlaced(prefsToCopy->GetGIFInterlaced());
}


/* SetName
*/
void SnapPrefsData::SetName(const WideString& name)
{
	if (fName != name)
	{
		fName = name;
	}
}

/* GetName
*/
const WideString& SnapPrefsData::GetName ()
{
	return fName;
}

/* SetFormatClassID
*/
void SnapPrefsData::SetFormatClassID(const ClassID& formatClassID)
{
	if (fFormatClassID != formatClassID)
	{
		fFormatClassID = formatClassID;
	}
}

/* GetFormatClassID
*/
const ClassID& SnapPrefsData::GetFormatClassID()
{
	return fFormatClassID;
}

/* SetXScale
*/
void SnapPrefsData::SetScale(const PMReal& scale)
{
	if (fScale != scale)
	{
		fScale = scale;
	}
}

/* GetXScale
*/
const PMReal& SnapPrefsData::GetScale()
{
	return fScale;
}

/* SetResolution
*/
void SnapPrefsData::SetResolution(const PMReal& resolution)
{
	if (fResolution != resolution)
	{
		fResolution = resolution;
	}
}

/* GetResolution
*/
const PMReal& SnapPrefsData::GetResolution()
{
	return fResolution;
}

/* SetMinimumResolution
*/
void SnapPrefsData::SetMinimumResolution(const PMReal& minimumResolution)
{
	if (fMinimumResolution != minimumResolution)
	{
		fMinimumResolution = minimumResolution;
	}
}

/* GetMinimumResolution
*/
const PMReal& SnapPrefsData::GetMinimumResolution()
{
	return fMinimumResolution;
}

/* SetBleed
*/
void SnapPrefsData::SetBleed(const PMReal& bleed)
{
	if (fBleed != bleed)
	{
		fBleed = bleed;
	}
}

/* GetBleed
*/
const PMReal& SnapPrefsData::GetBleed()
{
	return fBleed;
}

/* SetDrawArea
*/
void SnapPrefsData::SetDrawArea(bool16 drawArea)
{
	if (fDrawArea != drawArea)
	{
		fDrawArea = drawArea;
	}
}

/* GetDrawArea
*/
const bool16& SnapPrefsData::GetDrawArea()
{
	return fDrawArea;
}

/* SetFullResolutionGraphics
*/
void SnapPrefsData::SetFullResolutionGraphics(bool16 fullResolutionGraphics)
{
	if (fFullResolutionGraphics != fullResolutionGraphics)
	{
		fFullResolutionGraphics = fullResolutionGraphics;
	}
}

/* GetFullResolutionGraphics
*/
const bool16& SnapPrefsData::GetFullResolutionGraphics()
{
	return fFullResolutionGraphics;
}


/* SetDrawGray
*/
void SnapPrefsData::SetDrawGray(bool16 DrawGray)
{
	if (fDrawGray != DrawGray)
	{
		fDrawGray = DrawGray;
	}
}

/* GetDrawGray
*/
const bool16& SnapPrefsData::GetDrawGray()
{
	return fDrawGray;
}

/* SetDrawingFlags
*/
void SnapPrefsData::SetDrawingFlags(int32 drawingFlags)
{
	if (fDrawingFlags != drawingFlags)
	{
		fDrawingFlags = drawingFlags;
	}
}

/* GetDrawingFlags
*/
const int32& SnapPrefsData::GetDrawingFlags()
{
	return fDrawingFlags;
}

/* SetJPEGEncoding
*/
void SnapPrefsData::SetJPEGEncoding(const int32 encoding) 
{
	if (fJPEGEncoding != encoding)
	{
		fJPEGEncoding = encoding;
	}
}

/* GetJPEGEncoding
*/
const int32& SnapPrefsData::GetJPEGEncoding()
{
	return fJPEGEncoding;
}

/* SetJPEGQuality
*/
void SnapPrefsData::SetJPEGQuality(const int32 quality)
{
	if (fJPEGQuality != quality)
	{
		fJPEGQuality = quality;
	}
}

/* GetJPEGQuality
*/
const int32& SnapPrefsData::GetJPEGQuality() 
{
	return fJPEGQuality;
}

/* SetTIFFPaletteType
*/
void SnapPrefsData::SetTIFFPaletteType(const int32 paletteType) 
{
	if (fTIFFPaletteType != paletteType)
	{
		fTIFFPaletteType = paletteType;
	}
}

/* GetTIFFPaletteType
*/
const int32& SnapPrefsData::GetTIFFPaletteType() 
{
	return fTIFFPaletteType;
}

/* SetGIFPaletteType
*/
void SnapPrefsData::SetGIFPaletteType(const int32 paletteType) 
{
	if (fGIFPaletteType != paletteType)
	{
		fGIFPaletteType = paletteType;
	}
}

/* GetTIFFPaletteType
*/
const int32& SnapPrefsData::GetGIFPaletteType() 
{
	return fGIFPaletteType;
}

/* SetTIFFTransparent
*/
void SnapPrefsData::SetTIFFTransparent(const bool16 transparent)
{
	if (fTIFFTransparent != transparent)
	{
		fTIFFTransparent = transparent;
	}
}

/* GetTIFFTransaprent
*/
const bool16& SnapPrefsData::GetTIFFTransparent()
{
	return fTIFFTransparent;
}

/* SetGIFTransparent
*/
void SnapPrefsData::SetGIFTransparent(const bool16 transparent) 
{
	if (fGIFTransparent != transparent)
	{
		fGIFTransparent = transparent;
	}
}

/* GetGIFTransparent
*/
const bool16& SnapPrefsData::GetGIFTransparent()
{
	return fGIFTransparent;
}

/* SetGIFInterlaced
*/
void SnapPrefsData::SetGIFInterlaced(const bool16 interlaced)
{
	if (fGIFInterlaced != interlaced)
	{
		fGIFInterlaced = interlaced;
	}
}

/* GetGIFInterlaced
*/
const bool16& SnapPrefsData::GetGIFInterlaced()
{
	return fGIFInterlaced;
}

// End, SnapPrefsData.cpp.


