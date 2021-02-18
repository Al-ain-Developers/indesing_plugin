package com.adobe.flexsamples.IDMLContentEditor
{
	/**
	 * Used to store references to TextFrames
	 * found in the IDML file.
	 */
	[Bindable]
	public class BindableTextObject extends Object
	{
		public function BindableTextObject()
		{
			super();
		}
		
		public var scriptLabel:String = new String();
		
		public var storyContent:String = new String();
		
		public var storyId:String = new String();
		
		public var hasChanged:Boolean = false;
		
		/**
		 * Updates the content stored in this object.
		 */
		public function updateContent(content:String):void
		{
			storyContent = content;
			hasChanged = true;
		}
	}
}