//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLContentReference.h $
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
#ifndef __XMLContentReference__
#define __XMLContentReference__


#include "TableTypes.h"
#include "IXMLElementCommands.h"


class IPMStream;
class IXMLReferenceData;
class ITableModel;

/** Represents the content information for a XML structure element. A XML structure element
	may be associated with a specific content item. This class contains information about 
	the content item.
*/
class PUBLIC_DECL XMLContentReference {
	public:
		/** no specialized copy semantics required for K2Vector */
   		typedef base_type data_type;


		/** the type of the content */
		enum ContentType {
			kContentType_Text = 0,		/** content is text (PCDATA) */
			kContentType_PageItem,		/** page item */
			kContentType_Table,			/** table */
			kContentType_TableGrid,		/** table row */
			kContentType_TableCell,		/** table cell */
			kContentType_NoContent		/** no content is associated with this. Note that this is different than text content that's empty */
		};


		/** constructors */

		/**	Default constructor
		*/
		XMLContentReference();

		/**	Constructor
			@param baseUIDRef 
		*/
		XMLContentReference(const UIDRef& baseUIDRef, const GridID& gridID = kInvalidGridID);

		/**	Constructor
			@param baseUIDRef 
		*/
		XMLContentReference(const UIDRef& baseUIDRef, const GridID& startGrid, const GridSpan& span);

		/**	Copy constructor
			@param other object to cpy state from
		*/
		XMLContentReference(const XMLContentReference& other);


		/** accessors and mutators for member data */

		/** Get the content's type
			@return ContentType
		*/
		ContentType GetContentType() const;

		/**	Accessor for base UIDRef		
			@return const UIDRef& 
		*/
		const UIDRef& GetUIDRef() const;

		/** Mutator for base UIDRef
			@param uidRef new content UIDRef
		*/
		void SetUIDRef(const UIDRef& uidRef);

		/**	Accessor for base UID associated with the base UIDRef		
			@return base UID associated with the reference
		*/
		UID GetUID() const;

		/** Mutator for content base UIDRef's UID
			@param uid new content UID
		*/
		void SetUID(UID uid);

		/**	Accessor for database stored with the base UIDRef	
			@return IDataBase 
		*/
		IDataBase *GetDataBase() const;

		/** Mutator for database of base UIDRef
			@param db data base of content
		*/
		void SetDataBase(IDataBase *db);

		/** Accessor for the table cell by GridAddress
			return GridAddress
		*/
		GridAddress GetGridAddress(const ITableModel *tableModel) const;

		/** Accessor for the table cell grid ID
			return GridID
		*/
		const GridID& GetGridID() const;

		/** Mutator for the table cell grid ID
			@param gridID GridID of the table cell
		*/
		void SetGridID(GridID gridID);


		/** Accessor for the grid extent
			return GridSpan
		*/
		const GridSpan& GetSpan() const;

		/** Mutator for the grid extent
			@param GridSpan of the table grid element
		*/
		void SetSpan(const GridSpan& span);
		
		/** Accesor for the grid area, including GridID & GridSpan
			@param tableModel - what table owns this element
			@return GridArea
		*/
		GridArea GetGridArea(ITableModel *tableModel) const;
		
		/** Mutator for marking this as having no content */
		void SetNoContent(void);

		/** methods for accessing associated content */

		/**	Instantiate the XMLReferenceData of the content item from the database
			@return reference-incremented interface ptr to IXMLReferenceData
		*/
		IXMLReferenceData* Instantiate() const;

		/** determine whether the content is an inline page item
			@return kTrue if the content is an inline page item; kFalse otherwise
		*/
		bool16 IsInline() const;

		/** determine whether the content is a table
			@return kTrue if the content is a table; kFalse otherwise
		*/
		bool16 IsTable() const;

		/** determine whether the content is a table cell
			@return kTrue if the content is a table cell; kFalse otherwise
		*/
		bool16 IsTableCell() const;

		/** determine whether the content is a table grid
			@return kTrue if the content is a table grid; kFalse otherwise
		*/
		bool16 IsTableGrid() const;
		
		/** determine whether the content is a no content
			@return kTrue if the content is a no content type
		*/
		bool16 IsNoContent() const;

		/** determine whether the content is a pageitem placed inside table cell
			@return kTrue if the content is a pageitem placed inside table cell
		*/
		bool16 IsTableCellPlacedPageItem() const;
		
		/** misc utilities */

		/**	Method to serialise object to or deserialise object from given stream
			@param s stream to read state from or write state to
			@param db 
		*/
		void ReadWrite(IPMStream *s, IDataBase *db = nil);

		/**	Equality operator
			@param other comparand
			@return kTrue if member data match, kFalse otherwise
		*/
		bool16 operator == (const XMLContentReference& other) const;

		/**	Inequality operator
			@param compareAgainst comparand
			@return kTrue if equality operation fails, kFalse otherwise
		*/
		inline bool16 operator != (const XMLContentReference& compareAgainst) const
			{ return (!(*this == compareAgainst)); }

		/**	Less than operator
			@param compareAgainst comparand
			@return kTrue if this is less than compareAgainst, kFalse otherwise
		*/
		bool16 operator < (const XMLContentReference& compareAgainst) const;

		void SetTableTagPreference(IXMLElementCommands::TableTagPreference newSetting)
			{ fTableGridSetting = newSetting; }
		IXMLElementCommands::TableTagPreference GetTableTagPreference() const
			{ return fTableGridSetting; }
			
	private:
		UIDRef fBaseUIDRef;
		GridID fGridID;
		GridSpan fSpan;
		bool16 fIsGrid;
		IXMLElementCommands::TableTagPreference fTableGridSetting;
		bool16 fHasNoContent;
};

DECLARE_BASE_TYPE(XMLContentReference);		// no special copy


const XMLContentReference kInvalidXMLContentReference;


#endif // __XMLContentReference__

