//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/IPnlTrvDataModel.h $
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

#ifndef __IPnlTrvDataModel_H_DEFINED__
#define __IPnlTrvDataModel_H_DEFINED__

#include "IPMUnknown.h"
#include "PnlTrvID.h"

class PnlTrvDataNode;
/**  @ingroup paneltreeview
*/
class IPnlTrvDataModel : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPNLTRVDATAMODEL };

	/**	Accessor for the root path
		@return PMString giving the path associated with the root node
	 */
	virtual PMString GetRootPath() const =0 ;


	virtual PnlTrvDataNode* GetNode(const PMString& path) const = 0;

	/**	Given a path, discover the path of its parent
		@param path [IN] specifies given path
		@return Returns path as string
	 */
	virtual PMString GetParentPath(const PMString& path) const=0;

	/**	Determine the number of children given a path
		@param path [IN] specifies given path
		@return Returns number of children
	 */
	virtual int32 GetChildCount(const PMString& path)=0; 

	/**	Get the path associated with the specified child
		@param path [IN] specifies given path
		@param nth [IN] specifies which child
		@return Returns path as string
	 */
	virtual PMString GetNthChildPath(const PMString& path, int32 nth)=0; 

	/**	Determine the index in the parent's list of kids for 
		a particular child
		@param par [IN] specifies parent
		@param kid [IN] specifies kid
		@return Returns index 
	 */
	virtual int32 GetChildIndexFor(const PMString& par, const PMString& kid)=0; 

	/**	Call when you want to force a recalculation
	 */
	virtual void Rebuild(const PMString& rootPath)=0;

};


#endif // __IPnlTrvDataModel_H_DEFINED__

