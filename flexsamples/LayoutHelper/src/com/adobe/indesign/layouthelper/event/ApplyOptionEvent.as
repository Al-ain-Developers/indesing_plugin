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
	
	public class ApplyOptionEvent extends Event
	{
		public static const ACTION:String = "apply";
		private var _panel:String;
		public function ApplyOptionEvent(type:String, panel:String, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			_panel = panel;
		}
		
		//getter function for panel object
		public function get panel():String
		{
			return _panel;
		}	
	}
}
