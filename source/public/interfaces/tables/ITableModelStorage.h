//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/tables/ITableModelStorage.h $
//  
//  Owner: ???
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
#ifndef __ITableModelStorage__
#define __ITableModelStorage__

#include "TableTypes.h"
#include "TablesID.h"

//===================================================================================
/** Public interface exposing storage components of the table model.

	@author 	Joe Shankar
 */
//===================================================================================

class ITableStrand;
class ITableNotificationStrand;
class ICellContentMgr;

class ITableModelStorage : public IPMUnknown {

public:

	///	kDefaultIID
	enum  { kDefaultIID = IID_ITABLEMODELSTORAGE };

	//-------------------------------------------------------------------------------					
	/**@name	Strands
		   		Strands that are registered with the model are owned by it. */
	//@{-----------------------------------------------------------------------------
						/** Registers a persistent boss that has an ITableStrand implementation identified by 
						ITableStrand::kDefaultIID */
	virtual void		RegisterStrand  (UID strandUID) = 0;

						/** Unregisters a previously registered strand boss. See RegisterStrand for more info. */
	virtual void		UnregisterStrand(UID strandUID) = 0;


	enum ETableStrand { eRow, eColumn, eCell };

							/** Returns the number of strands registered with the table model */
	virtual int32		   GetStrandCount(void) const = 0;

							/**  Returns the nth strand
								@params n < self.GetStrandCount
							 */
	virtual ITableStrand*  QueryNthStrand(int32 n) const = 0;

							/** Returns the strand identified by which. Clients need to 'Release' the interface
								when done. */
	virtual ITableStrand*  QueryStrand(ETableStrand which) const = 0;

							/** Returns the strand identified by which. Clients need to 'Release' the interface
								when done. */
	virtual ITableStrand*  QueryStrand(ClassID which) const = 0;

							/** Returns the number of strands notification strands. */
	virtual int32			GetNotificationStrandCount() const = 0;

							/**  Returns the nth notification strand
								 @params n < self.GetNotificationStrandCount
							 */
	virtual ITableNotificationStrand*	QueryNthNotificationStrand(int32 n) const = 0;

	//-------------------------------------------------------------------------------					
	/**@name	Content Managers
		   		Content managers that are registered with the model are owned by it. */
	//@{-----------------------------------------------------------------------------
								/** Registers a persistent boss that has an IContentMgr implementation identified by 
									ICellContentMgr::kDefaultIID */
	virtual void				RegisterContentMgr	(CellType type, UID contentMgrUID) = 0;

								/** Unregisters a previously registered content manager boss. See RegisterContentMgr for more info. */
	virtual void				UnregisterContentMgr(CellType type, UID contentMgrUID) = 0;

								/// Returns the number of content managers registered with the table model */	
	virtual int32				GetContentMgrCount(void) const = 0;
	
								/**  Returns the nth content manager
									@params n < self.GetContentMgrCount
								 */
	virtual ICellContentMgr*	QueryNthContentMgr(int32 n) const = 0;
	
								/** Returns the ContentMgr identified by 'type'. Clients need to 'Release' the interface
								when done. */
	virtual ICellContentMgr*  	QueryContentMgr	(CellType type) const = 0;
	
	//@}-----------------------------------------------------------------------------
};

#endif // __ITableModelStorage__