/*
ADOBE SYSTEMS INCORPORATED
Copyright 2012 Adobe Systems Incorporated
All Rights Reserved.

NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance with the 
terms of the Adobe license agreement accompanying it.  If you have received this file from a 
source other than Adobe, then your use, modification, or distribution of it requires the prior 
written permission of Adobe.
*/
package com.adobe.indesign.layouthelper.event 
{
	import com.adobe.indesign.*;
	
	import flash.events.Event;
	
	public class ConstrainsSettingEvent extends Event
	{
		public static const CHANGE:String = "objectsetting";
		private var _page:Page;
		private var _constrain:DimensionsConstraints;
		public function ConstrainsSettingEvent(type:String, page:Page, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			_page = page;
		}
		
		//getter function for item object
		public function get page():Page
		{
			return _page;
		}
		
	}
}
