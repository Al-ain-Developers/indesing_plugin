//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/ITagRegistry.h $
//  
//  Owner: Robin_Briggs
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
//  Interface for keeping track of tag priorities.
//  
//========================================================================================

#pragma once
#ifndef __ITagRegistry__
#define __ITagRegistry__


#include "IPMUnknown.h"
#include "ShuksanID.h"


/** The tag registry keeps track of the priority of all the ImplementationIDs
	and ClassIDs, for purposes of managing data related to missing plug-ins.
	When a plug-in adds data to the document, the data belongs to a UID that has
	a certain ClassID, or to an ImplementationID attached to some other plug-in's
	UID. The object model needs a way to assess the priority level of the data,
	so that it can warn the user appropriately when opening up documents that
	contain data from missing plug-ins.
	
	To set the priority of your plug-in's data, you add an IgnoreTags resource or
	a CriticalTags resource to your plug-in's class.fr file. For example, to set 
	implementations to the ignore priority, you would add a resource like this:
	<pre>
resource IgnoreTags (1)
{
	kImplementationIDSpace,
	{
		kFooImpl,
		kBarImpl,
	}
};
	</pre>
	
	<pre>
	If your plug-in also has persistent classes, you may find that this is not 
	enough, and you are still getting the missing plug-ins alert when you open
	a document without your plug-in. In this case, add an ignore resource for the
	classes of the UIDs your plug-in adds:

resource IgnoreTags (2)
{
	kClassIDSpace,
	{
		kFooBoss,
		kBarBoss,
	}
};
	</pre>
	
	
	To mark data as critical, you would use the same format with the CriticalTags 
	resource:
	<pre>
resource CriticalTags (1)
{
	kImplementationIDSpace,
	{
		kFooImpl,
		kBarImpl,
	}
};
	</pre>
	
	It may be that your plug-in will want to use both, if it has preference data with some
	simple user settings, and (possibly) also objects that are tightly bound to the document.
	If the user has just set the preference data, there is no alter, but if they have
	also added new objects to the document, then they would get the critically worded
	alert.
*/
class ITagRegistry : public IPMUnknown {
public:

	/** Priority levels */
	// Order of these is significant.
	enum TagPriority{ 
		/** Ignore is the lowest priority, and should be used for data which
			that is not referred to elsewhere, and that doesn't refer to other
			objects from other plug-ins in the document. Preference data is
			a good example of data that can be marked ignore. The normal missing
			plug-in warning will not come up for data that has been marked
			ignore.
		*/	
		kIgnore, 
		/** Default is the priority level you get if you don't explicitly 
			declare a priority. Data at default priority will cause the usual
			missing plug-ins alert to come up at when the document is opened
			if the plug-in is missing.
		*/
		kDefault, 
		/** Critical is the highest priority level. Data at critical priority will 
			cause the missing plug-ins alert to be more strongly worded to warn 
			the user that editing the document without this plug-in present may
			corrupt the document.
		*/
		kCritical  
	};

	/**@name  For Internal Use Only  */
	//@{-----------------------------------------------------------------------------
	virtual void AddTag(ImplementationID newTag, TagPriority priority) = 0;
	virtual TagPriority GetTag(ImplementationID tag) = 0;

	virtual void AddClassTag(ClassID newTag, TagPriority priority) = 0;
	virtual TagPriority GetClassTag(ClassID tag) = 0;
	//@}-----------------------------------------------------------------------------
};

DECLARE_BASE_TYPE(ITagRegistry::TagPriority);


#endif // __ITagRegistry__
