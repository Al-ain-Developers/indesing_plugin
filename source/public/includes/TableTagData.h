//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TableTagData.h $
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
//  
//  Purpose:
//  Data to indicate which tags to use when tagging tables
//  
//========================================================================================

#ifndef __TableTagData__
#define __TableTagData__

#include <vector>

/** Use this class to indicate which tags should be used to tag a given table
	You can either use the default class which will tag tables with the tags
	chosen by the user or you can specify your own tags by name or UID
*/
class PUBLIC_DECL TableTagData
{
public:
	/** constructor 
		@param db - Used to specify which database tags should be retrieved from
	*/
	TableTagData(IDataBase *db = nil);

	/** Use this to initialize the data in this class 
		@param db - Used to specify which database tags should be retrieved from
	*/
	void Initialize(IDataBase *db);
	
	/** Use this to determine if this has been initialized. This can be initialized 
		by calling Initialize()
		@return whether this has been initialized
	*/
	bool16 IsInitialized(void) const;

	/** Use this to override the default table tag. You can specify the tag by name
		@param name - This is the name your table tag should have
	*/
	void SetTableTag(const WideString &name) {return SetTagName(kTable, name);}
	
	
	/** Use this to set the table header tag. You can specify the tag by name
		@param name - This is the name your table header tag should have
	*/
	void SetHeaderTag(const WideString& name) { return SetTagName(kHeader, name); }
	
	/** Use this to set the table body tag. You can specify the tag by name
		@param name - This is the name your table body tag should have
	*/
	void SetBodyTag(const WideString& name) { return SetTagName(kBody, name); }
	
	/** Use this to set the table footer tag. You can specify the tag by name
		@param name - This is the name your table footer tag should have
	*/
	void SetFooterTag(const WideString& name) { return SetTagName(kFooter, name); }
	
	/** Use this to override the default row tag. You can specify the tag by name
		@param name - This is the name your row tag should have
	*/
	void SetRowTag(const WideString &name) {return SetTagName(kRow, name);}
	
	/** Use this to override the default cell tag. You can specify the tag by name
		@param name - This is the name your cell tag should have
	*/
	void SetCellTag(const WideString &name) {return SetTagName(kCell, name);}

	/** Use this to override the default Table tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the table
	*/
	void SetTableTag(const UID &uid) {return SetTagUID(kTable, uid);}
	
	/** Use this to set the table header tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the table header
	*/
	void SetHeaderTag(UID uid) { return SetTagUID(kHeader, uid); }
	
	/** Use this to set the table body tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the table body
	*/
	void SetBodyTag(UID uid) { return SetTagUID(kBody, uid); }
	
	/** Use this to set the table footer tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the table footer
	*/
	void SetFooterTag(UID uid) { return SetTagUID(kFooter, uid); }
	
	/** Use this to override the default Row tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the row
	*/
	void SetRowTag(const UID &uid) {return SetTagUID(kRow, uid);}
	
	/** Use this to override the default Cell tag. You can specify the tag by UID
		@param uid - The UID of the tag you want to use to tag the cell
	*/
	void SetCellTag(const UID &uid) {return SetTagUID(kCell, uid);}

	/** Use this to get the UID of the tag that should be used to tag the table
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the table.
	*/
	UID GetTableTag(bool16 lwProcessing = kFalse) const {return GetTagUID(kTable, lwProcessing);}
	
	/** Returns whether a table tag was specified in this
		@return whether a table tag was specified in this
	*/
	bool16 HasTableTag(void) const { return HasTag(kTable); }

	/** Use this to get the UID of the tag that should be used to tag the table header
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the table header
	*/
	UID GetHeaderTag(bool16 lwProcessing = kFalse) const { return GetTagUID(kHeader, lwProcessing); }
	
	/** Returns whether a table header tag was specified in this
		@return whether a table header tag was specified in this
	*/
	bool16 HasHeaderTag(void) const { return HasTag(kHeader); }
	
	/** Use this to get the UID of the tag that should be used to tag the table body
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the table body
	*/
	UID GetBodyTag(bool16 lwProcessing = kFalse) const { return GetTagUID(kBody, lwProcessing); }
	
	/** Returns whether a table body tag was specified in this
		@return whether a table body tag was specified in this
	*/
	bool16 HasBodyTag(void) const { return HasTag(kBody); }
	
	/** Use this to get the UID of the tag that should be used to tag the table footer
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the table footer
	*/
	UID GetFooterTag(bool16 lwProcessing = kFalse) const { return GetTagUID(kFooter, lwProcessing); }
	
	/** Returns whether a table footer tag was specified in this
		@return whether a table footer tag was specified in this
	*/
	bool16 HasFooterTag(void) const { return HasTag(kFooter); }
	
	/** Use this to get the UID of the tag that should be used to tag the row
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the row.
	*/
	UID GetRowTag(bool16 lwProcessing = kFalse) const {return GetTagUID(kRow, lwProcessing);}
	
	/** Returns whether a table row tag was specified in this
		@return whether a table row tag was specified in this
	*/
	bool16 HasRowTag(void) const { return HasTag(kRow); }

	/** Use this to get the UID of the tag that should be used to tag the cell
		NOTE: Typically this should not be called by anything but a command because it may
		change the document.
		@param lwProcessing - kTrue Indicates that this command should be processed without notification. 
							  kFalse indicates that notification is OK.
							  Note: If you pass kTrue no command will be fired so you must make sure you
							  don't call this unless you are in a command sequence.
		@return The UID of the tag to use for tagging the cell.
	*/
	UID GetCellTag(bool16 lwProcessing = kFalse) const {return GetTagUID(kCell, lwProcessing);}
	
	/** Returns whether a table cell tag was specified in this
		@return whether a table cell tag was specified in this
	*/
	bool16 HasCellTag(void) const { return HasTag(kCell); }

private:
	// this enum is used to indicate which tag you care about. Please don't add
	// any values after kEnd because that is used to indicate the end of the list
	// programatically
	enum WhichTag {kTable = 0, kHeader, kBody, kFooter, kRow, kCell, kEnd /* Don't insert anything after kEnd */};

	// This is an internal method that is used to set the tag name for a given
	// part of the table. It sets the entire data structure up to know that the
	// tag has been set by name
	void SetTagName(WhichTag which, const WideString &name, UID colorUID = kInvalidUID);

	// This is an internal method that is used to set the tag UID for a given
	// part of the table. It sets the entire data structure up to know that the
	// tag has been set by UID
	void SetTagUID(WhichTag which, const UID &uid);

	// This is an internal method that is used to get the tag UID for a given
	// part of the table. If the tag information was set via name this method
	// will create a new tag if one doesn't already exist.
	UID GetTagUID(WhichTag which, bool16 lwProcessing) const ;
	
	// This is an internal method that is used to retrieve whether a particular tag type was 
	//	specified/stored in this
	bool16 HasTag(WhichTag which) const;

	// This is a struct for holding all of the required information about a
	// tag for a particular part of the table.
	struct TagData {
		TagData() : fColorUID(kInvalidUID),
					fReceivedName(kFalse),
					fNameProcessed(kFalse),
					fTagUID(kInvalidUID)
		{}

		WideString		fTagName;
		UID				fColorUID;
		bool16			fReceivedName;
		mutable	bool16	fNameProcessed;
		mutable UID		fTagUID;
	};

	IDataBase *fDB;
	std::vector<TagData> fTagData;
	bool16 fInitialized;
};

#endif

