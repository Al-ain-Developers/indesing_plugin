package com.adobe.idmltools
{
	import flash.filesystem.File;
	
	/**
	 * Used to store references to images
	 * found in the IDML file.
	 */
	[Bindable]
	public class BindableImgRef extends Object
	{
		public function BindableImgRef()
		{
			super();		
		}
		
		public var id:String = new String();		
		
		public var nativePath:String = new String();
		
		public var fileName:String = new String();
		
		public var idmlPath:String = new String();
		
		public var isEmbedded:Boolean = false;
		
		public var hasChanged:Boolean = false;
		
		/**
		 * Updates the content stored in this object
		 * with data from the image refered to in the 
		 * file provided.
		 */
		public function update(imgFile:File):void
		{
			idmlPath = imgFile.url.replace("file:///", "file:");
			fileName = imgFile.name;
			nativePath = imgFile.nativePath;
			hasChanged = true;
		}
		
		/**
		 * Returns "Yes" if the image is embedded
		 * and "No" if it is not.
		 */
		public function showEmbedded():String
		{
			return ((isEmbedded) && (!hasChanged))? 'Yes':'No';
		}
	}
}