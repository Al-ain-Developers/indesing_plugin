//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/AutoGSave.h $
//  
//  Owner: Sanjay Kumar
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
//  Purpose of class
//  AutoGSave is to used with IGraphicsPort to automatically call gsave and grestore
//  
//========================================================================================

#pragma once
#ifndef __AUTOGSAVE__
#define __AUTOGSAVE__

#include "IGraphicsPort.h"

/** Automatically calls IGraphicsPort::gsave in constructor and IGraphicsPort::grestore in destructor
	so you donot have to explicitly call gsave and grestore. Just create an Object of AutoGSave with
	in the scope and you are done.

	e.g.
	the following code

		InterfacePtr<IGraphicsPort> gPort(gc.GetViewPort(), IID_IGRAPHICSPORT);
		gPort->gsave();
		...
		gPort->grestore();

	would become

		InterfacePtr<IGraphicsPort> gPort(gc.GetViewPort(), IID_IGRAPHICSPORT);
		AutoGSave autoGSave(gPort);


!!! Points to remember while using AutoGSave

	* Use AutoGSave only when you have gPort->gsave() and gPort->grestore() in the same scope.
	* Do not use AutoGSave when you have some IGraphicsPort call after grestore().

	e.g.

	{
		port->setrgbcolor(0, 1, 0);
		port->gsave();
		port->setrgbcolor(1, 0, 0);
		port->rectfill(0, 0, 10, 10);
		port->grestore();
		port->rectfill(10, 0, 10, 10);
	}

	should not be converted to

	{
		port->setrgbcolor(0, 1, 0);
		AutoGSave foo(port);
		port->setrgbcolor(1, 0, 0);
		port->rectfill(0, 0, 10, 10);
		port->rectfill(10, 0, 10, 10);
	}

	As the second call to rectfill will now draw a green rectangle, not a red one as intended.

	* Do not forget to remove grestore() from all exit points.

	e.g.

	   void Foo(IGraphicsPort *port)
	   {
		   AutoGSave foo(port);
		   ...
		   if (abort) // whatever
		   {
			   // Do NOT call port->grestore() here!
			   return;
		   }
	   ...
	   }

	* Do not use AutoGSave whenever there are multiple gsave/grestore calls in the same scope.
	e.g.
	{
		gPort->gsave();
		...
		gPort->grestore();
		...
		gPort->gsave();
		...
		gPort->grestore();
	}

	* You should avoid using gsave/grestore (or the AutoGSave utility) excessively -
	  as it can have a dramatic impact on performance and on the quality of exported/printed
	  content. There are no real hard and fast rules about its use, but you shouldn't use it
	  without considering whether you truly need it.

*/
class AutoGSave
{
public:
	/** Constructor
	*/
	explicit AutoGSave(IGraphicsPort* graphicsPort):fGraphicsPort(graphicsPort)
	{
		fGraphicsPort->gsave();
	}
	/** Destructor
	*/
	~AutoGSave()
	{
		fGraphicsPort->grestore();
	}

private:
	IGraphicsPort* fGraphicsPort;
};

#endif //__AUTOGSAVE__