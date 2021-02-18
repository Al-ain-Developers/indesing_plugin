//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableAttrReport.h $
//  
//  Owner: Joe Shankar
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
#ifndef __ITableAttrReport__
#define __ITableAttrReport__

#include "IPMUnknown.h"
#include "TablesID.h"

/** This interface is on every table attribute and is the "designator" interface.
	It is used to get info about the attribute. Similar to IAttrReport for text. 
*/
class ITableAttrReport : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ITABLEATTRREPORT };

		enum EAttributeType { eRow, eColumn, eCell, eTable };

		enum ETableDamageNotification 
		{ 
			tan_geometry_first		= 0x00000001,	// space before
			tan_geometry_last		= 0x00000002,	// space after
			tan_bodyDraw			= 0x00000004,	// inval body rows
			tan_allDraw				= 0x0000000c,	// + header/footer rows
			tan_bodyTopBottomInval	= 0x00000010,	// body ink may have changed
			tan_bodyTopBottomStroke	= 0x00000030,	// + body effective weight
			tan_allTopBottomInval	= 0x00000050,	// + h/f
			tan_allTopBottomStroke	= 0x000000f0,	// + h/f
			tan_allLeftRightInval	= 0x00000100,	// all ink may have changed
			tan_bodyStructure		= 0x00000200,	// body row structure
			tan_allStructure		= 0x00000600,	// + header/footer rows
			tan_headerGeometry		= 0x00000800,	// skip/start on attr
			tan_footerGeometry		= 0x00001000,	// skip/start on attr
			tan_outerLeftDraw		= 0x00002000,	// inval left outer stroke
			tan_outerLeftInval		= 0x00004000,	// ink may have changed
			tan_outerLeftStroke		= 0x0000c000,	// + effective weight changed
			tan_outerTopDraw		= 0x00010000,	// inval top outer stroke
			tan_outerTopInval		= 0x00020000,	// ink may have changed
			tan_outerTopStroke		= 0x00060000,	// + effective weight changed
			tan_outerRightDraw		= 0x00080000,	// inval right outer stroke
			tan_outerRightInval		= 0x00100000,	// ink may have changed
			tan_outerRightStroke	= 0x00300000,	// + effective weight changed
			tan_outerBottomDraw		= 0x00400000,	// inval bottom outer stroke
			tan_outerBottomInval	= 0x00800000,	// ink may have changed
			tan_outerBottomStroke	= 0x01800000,	// + effective weight changed

			tan_all					= 0x01b6bff3	// everything but draw
		};

		enum ERowDamageNotification 
		{ 
			ran_geometry	        = 0x01,	// positioning attribute (ex: breakAt) chngd
			ran_structure			= 0x02,	// structure attribute changed
			ran_height				= 0x07,	//  + row height property changed

			ran_all					= 0x07
		};

		enum EColumnDamageNotification 
		{ 
			can_structure			= 0x01,	// structure attribute changed
			can_width				= 0x03,	// + width of the column changed

			can_all					= 0x03
		};

		enum ECellDamageNotification 
		{ 
			clan_draw				= 0x0001,	// draw attribute changed
			clan_inval				= 0x0002,	// stroke ink changed
			clan_content			= 0x0004,	// content attribute changed
			clan_structure			= 0x0008,	// structure attribute changed
			clan_leftStroke			= 0x001a,	// + inval + left effective weight changed
			clan_topStroke			= 0x002a,	// + inval + top effective weight changed
			clan_rightStroke		= 0x004a,	// + inval + right effective weight changed
			clan_bottomStroke		= 0x008a,	// + inval + bottom effective weight changed

			clan_all				= 0x00fe	// everything but draw
		};

		/** Add a descriptive name to the end of the passed in string. 
			@param into OUT parameter for description of this attribute
			@param db parameter apparently not required, can be nil
		*/
		virtual void			AppendDescription(PMString& into, IDataBase* db) const = 0;
								 
		/** Determine the type of this attribute.
			@return the type of this attribute. 
		*/
		virtual	EAttributeType	GetType(void) const = 0;

		/** Determine the type of damage this attribute causes
			@return A value from the cooresponding damage enum.  For example, if it's a cell attribute return a value from the ECellDamageNotification enum.
		*/
		virtual	int32		GetDamageNotification(void) const = 0;
								// 
								
		//virtual void ExtractAttr(/* Need to define and pass in data collector interfaces here.
		//						    e.g. ITableDrawStyle* drawStyle etc.*/) const = 0;
};

ITableAttrReport::ECellDamageNotification& operator|=(ITableAttrReport::ECellDamageNotification& obj, ITableAttrReport::ECellDamageNotification v);

ITableAttrReport::ETableDamageNotification& operator|=(ITableAttrReport::ETableDamageNotification& obj, ITableAttrReport::ETableDamageNotification v);

ITableAttrReport::EColumnDamageNotification& operator|=(ITableAttrReport::EColumnDamageNotification& obj, ITableAttrReport::EColumnDamageNotification v);

ITableAttrReport::ERowDamageNotification& operator|=(ITableAttrReport::ERowDamageNotification& obj, ITableAttrReport::ERowDamageNotification v);


#endif		// __ITableAttrReport__
