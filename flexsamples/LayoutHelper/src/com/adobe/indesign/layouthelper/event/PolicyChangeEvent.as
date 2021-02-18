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
	import flash.events.Event;
	
	public class PolicyChangeEvent extends Event
	{
		public static const CHANGE:String = "change";
		private var _item:Object;
		private var _policy:String;
		public function PolicyChangeEvent(type:String, item:Object, policy:String, bubbles:Boolean=false, cancelable:Boolean=false)
		{
			super(type, bubbles, cancelable);
			_item = item;
			_policy = policy;
		}
		
		//getter function for item object
		public function get item():Object
		{
			return _item;
		}
		//getter function for policy
		public function get policy():String
		{
			return _policy;
		}
		
	}
}
