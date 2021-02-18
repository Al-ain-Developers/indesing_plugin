//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableLineType.h $
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
//  
//  Purpose: Data interface for table stroke type.
//  
//========================================================================================

#pragma once
#ifndef __ITableLineType__
#define __ITableLineType__

#include "IPMUnknown.h"
#include "TablesID.h"
#include "InstStrokeFillID.h"
#include "ScotchRulesID.h"
#include "IDataBase.h"

/** 
 * 	The type of stroke applied to a cell edge
 *  	@ingroup table_attr
 */
 class ITableLineType : public IPMUnknown
{
public:
		enum  { kDefaultIID = IID_ITABLELINETYPE };

		/**
			The data of the line type applied to a cell
		*/
		struct SType {
			typedef object_type data_type;

			/**
				ClassID of the line type	(see @IGraphicAttrClassID)
			*/
			ClassID classID;
			/**
				UID of the custom line type
			*/
			UID uID;

			/**
				Constructor
				Initializes the classID to kSolidPathStrokerBoss and the uid to kInvalidUID
			*/
			SType() {
				classID = kSolidPathStrokerBoss;
				uID = kInvalidUID;
			}

			/**
				Constructor
				@param c		the classID see @classID
				@param u		the classID see @uID
			*/
			SType(ClassID c, UID u) {
				classID = c;
				uID = u;
			}
/*
			bool16 SType::IsValid() const {
				return (IsMixed() || IsNone() ||
						((classID != kCustomStripedPathStrokerBoss || uID != kInvalidUID)));
			}
*/
			/**
				Returns true if the conditions are mixed meaning nothing is set
				@return	bool16
			*/
			bool16 IsMixed() const {
				return ((classID == kInvalidClass) && (uID == kInvalidUID));
			}

			/**
				Returns true if this is the none stroke type 
				@return	bool16
			*/
			bool16 IsNone() const {
				return (classID == kNonePathStrokerBoss);
			}

			/**
				Returns true if this is the solid stroke type 
				@return	bool16
			*/
			bool16 IsSolid() const {
				return (classID == kSolidPathStrokerBoss);
			}

			/**
				Returns true if this is a striped stroke type 
				@param	db		the database we are comparing against (for custom stripes)
				@return	bool16
			*/
			bool16 IsStriped(IDataBase* db) const {
				return (classID == kThinThinPathStrokerBoss ||
					classID == kThickThickPathStrokerBoss ||
					classID == kThinThickPathStrokerBoss ||
					classID == kThickThinPathStrokerBoss ||
					classID == kThinThickThinPathStrokerBoss ||
					classID == kThickThinThickPathStrokerBoss ||
					classID == kTriplePathStrokerBoss || 
					(classID == kCustomPathStrokerBoss && db->GetClass(uID) == kCustomStripedPathStrokerBoss)
					);
			}

			/**
				Returns true if this is a dashed stroke type 
				@param	db		the database we are comparing against (for custom stroke types)
				@return	bool16
			*/
			bool16 IsDashed(IDataBase* db) const {
				return (classID == kDashedPathStrokerBoss || 
					classID == kCannedDash4x4PathStrokerBoss || 
					classID == kCannedDash3x2PathStrokerBoss || 
					(classID == kCustomPathStrokerBoss && db->GetClass(uID) == kCustomDashedPathStrokerBoss)
					);
			}

			/**
				Returns true if this is a dotted stroke type 
				@param	db		the database we are comparing against (for custom stroke types)
				@return	bool16
			*/
			bool16 IsDotted(IDataBase* db) const {
				return (classID == kCannedDotPathStrokerBoss ||
					classID == kJapaneseDotsPathStrokerBoss ||
					(classID == kCustomPathStrokerBoss && db->GetClass(uID) == kCustomDottedPathStrokerBoss)
				);
			}

			/**
				Returns true if this is a hash stroke type 
				@param	db		the database we are comparing against (for custom stroke types)
				@return	bool16
			*/
			bool16 IsHash() const {
				return (classID == kLeftSlantHashPathStrokerBoss ||
					classID == kRightSlantHashPathStrokerBoss ||
					classID == kStraightHashPathStrokerBoss
				);
			}

			/**
				Returns true if this is a special stroke type (not dotted, striped, hash, none, or mixed)
				@param	db		the database we are comparing against (for custom stroke types)
				@return	bool16
			*/
			bool16 IsSpecial(IDataBase* db) const {
				return !(this->IsNone() || this->IsMixed() || 
					this->IsSolid() || this->IsStriped(db) || this->IsDashed(db));
			}

			/**
				Returns true if this is equal to rhs
				@param rhs 	the one to compare against
				@return bool16
			*/
			bool16 operator==(const SType& rhs) const {
				return	rhs.classID	== classID &&
						rhs.uID	== uID;
			}

			/**
				Returns true if this is not equal to rhs
				@param rhs 	the one to compare against
				@return bool16
			*/
			bool16 operator!=(const SType& rhs) const {
				return !(this->operator==(rhs));
			}
		};

		/**
			Returns the SType stored in this class
			@return SType
		*/
		virtual SType	Get() const = 0;
		/**
			Sets the SType stored in this class
			@param SType
		*/
		virtual void	Set(SType type) = 0;

		/**
			conversion methods to fix InCopyWorkflow's CInCopyXMLValue::Get/SetTLineType
			INTERNAL USE ONLY
		*/
		virtual int32	ConvertSTypeToEType(ITableLineType::SType type) const = 0;
		/**
			conversion methods to fix InCopyWorkflow's CInCopyXMLValue::Get/SetTLineType
			INTERNAL USE ONLY
		*/
		virtual ITableLineType::SType	ConvertETypeToSType(int32 eType) const = 0;
};

#endif	// __ITableLineType__
