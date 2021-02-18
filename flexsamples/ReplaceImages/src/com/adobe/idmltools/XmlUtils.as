package com.adobe.idmltools
{
	/**
	 * Contains the location of 
	 */ 
	public class XmlUtils
	{
		import flash.filesystem.FileStream;
		import flash.filesystem.File;
		import flash.filesystem.FileMode;
				
		/**
		 * Returns an array of Image objects
		 * found in the spread file provided.
		 */ 
		public function getSpreadImages(xmlFile:File):Array
		{
			var xml:XML = getXml(xmlFile);
			var images:Array = new Array()
			for each(var node:XML in xml..Image)
			{
				var imgPath:String = node..Link.@LinkResourceURI;
				var imgStoreState:String = node..Link.@StoredState;
				var imgID:String = node.@Self;
				
				var imgRef:BindableImgRef = new BindableImgRef();								
				imgRef.id = imgID;
				imgRef.isEmbedded = (imgStoreState == "Embedded");
				imgRef.nativePath = getNativePath(imgPath);
				imgRef.fileName = getFileName(imgPath);
				images.push(imgRef);
			}
			return images;			
		}
		
		/**
		 * Updates the spread XML file with an
		 * updated image object file.
		 */ 
		public function updateSpreadFile(xmlFile:File, imgRef:BindableImgRef):void
		{
			var xml:XML = getXml(xmlFile);
			xml..Image.(@Self == imgRef.id).Link.@LinkResourceURI = imgRef.idmlPath;
			if (imgRef.isEmbedded)
			{
				//Set StoreState to Normal instead of Embedded
				xml..Image.(@Self == imgRef.id).Link.@StoredState = "Normal";
				//Delete Embedded Image
				delete xml..Image.(@Self == imgRef.id).Properties.Contents;				
			}
			writeXml(xmlFile, xml);
		}
		
		/**
		 * Extracts the absolute path from the path found
		 * in the IDML.
		 */
		private function getNativePath(path:String):String
		{			
			return path.substring(5, path.length);
		}
		
		/**
		 * Extracts the file name from the file path.
		 */
		private function getFileName(path:String):String
		{			
			return path.substring(path.lastIndexOf("/") + 1, path.length);
		}
		
		/**
		 * Writes an XML document to file.
		 */
		private function writeXml(xmlFile:File, xml:XML):void
		{
			var stream:FileStream = new FileStream();
 			stream.open(xmlFile, FileMode.WRITE)
 			stream.writeUTFBytes(xml.toXMLString());
 			stream.close();
 		}
		
		/**
		 * Reads an XML document from file.
		 */ 
		private function getXml(xmlFile:File):XML
		{
			var fs:FileStream = new FileStream();
			fs.open(xmlFile, FileMode.READ);
			var spreadXml:XML = XML(fs.readUTFBytes(fs.bytesAvailable));
			fs.close();
			return spreadXml;			
		}
	}
}