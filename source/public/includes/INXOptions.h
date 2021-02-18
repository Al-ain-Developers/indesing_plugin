//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/INXOptions.h $
//  
//  Owner: Steve Pellegrin
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
#ifndef __INXOptions_h__
#define __INXOptions_h__

// Typedef for style.
typedef uint32		INXStyle;
	

// Option bits
//    Overall XML structure options
static const INXStyle bINXStructureMask				= 0x0000000F;
static const INXStyle bINXCompact					= 0x00000001;
static const INXStyle bINXExpanded					= 0x00000002;

//    Token level options
static const INXStyle bINXVerboseNames				= 0x00000010;
static const INXStyle bINXReadableNumbers			= 0x00000020;

//    DTD options
static const INXStyle bINXUseDTD					= 0x00000100; // obsolete in CS3, might still being used in some old file
static const INXStyle bINXUseNamespace				= 0x00000200;


// Standard styles
static const INXStyle kINXDragontailTraditional		= (bINXCompact);
static const INXStyle kINXTraditional				= (bINXCompact | bINXReadableNumbers);
static const INXStyle kINXExpanded					= (bINXExpanded | bINXReadableNumbers | bINXVerboseNames);


class PUBLIC_DECL INXOptions
{
public:
/**
	Constructor. Allows caller to set individual options.
	@param Determines the overall "style" of INX generated.
  */
	INXOptions(INXStyle style = kINXExpanded);
	
/**
	Destructor.
  */
	~INXOptions();

/** 
	Compare two INXOptions for equality.
	@return kTrue if equal, kFalse if not
  */
	bool16 operator==(const INXOptions &other) const
		{return fStyle == other.GetStyle();}

/**
	Get the options style.
	@return The value of the Style passed to the constructor.
  */
 	INXStyle GetStyle() const;

/**
	Returns the value of the INX structure option.
	@return An integer value from the "structure options" defined above.
  */
	uint32 GetINXStructure() const;

/**
	Returns true if these options represent a traditional INX structure.
	@return kTrue if traditional, kFalse otherwise.
  */
	bool16 IsTraditionalStructure() const;

/**
	Returns true if these options represent an expanded INX structure.
	@return kTrue if expanded, kFalse otherwise.
  */
	bool16 IsExpandedStructure() const;

/**
	Returns the value of the Verbose Names option.
	@return kTrue or kFalse.
  */
	bool16 GetVerboseNames() const;

/**
	Returns the value of the Readable Numbers option.
	@return kTrue or kFalse.
  */
	bool16 GetReadableNumbers() const;

/**
	Returns the value of the DTD option.
	@return kTrue or kFalse.
  */
	bool16 GetUseDTD() const;

/**
	Returns the value of the Namespace option.
	@return kTrue or kFalse.
  */
	bool16 GetUseNamespace() const;

private:
	INXStyle		fStyle;
};

#endif	// __INXOptions_h__
