#ifndef __IDHAMemoryXferBytes_h__
#define __IDHAMemoryXferBytes_h__

#include "IXferBytes.h"

class  IDHAMemoryXferBytes : public IXferBytes 
{
public:
	/** Constructor
	*/
	IDHAMemoryXferBytes(void);

	/** Destructor
	*/
	virtual ~IDHAMemoryXferBytes(void);

	//--- The IXferBytes interface we must implement  ---

	/** See IXferBytes::Read
	*/
	virtual uint32 Read(void* buffer, uint32 num);

	/** See IXferBytes::Write
	*/
	virtual uint32 Write(void* buffer, uint32 num);

	/** See IXferBytes::Seek
	*/
	virtual uint64 Seek(int64 numberOfBytes, SeekFromWhere fromHere);

	/** See IXferBytes::Flush
	*/
	virtual void Flush(void);

	/** See IXferBytes::GetStreamState
	*/
	virtual StreamState GetStreamState(void);

	/** See IXferBytes::SetEndOfStream
	*/
	virtual void SetEndOfStream(void);

protected:
	const char*  getBufferPtr(void) const;
	void resizeBuffer(uint32 newSize);

private:

	StreamState fStreamState;
	uint32 fCountBytesStored;
	uint32 fAbsolutePositionInBuffer;
	char* fMyBuffer;
	uint32 fCurrentMaxBuf;

	enum
	{
		eIDHAInitialMaxBuf = 256 * 1024
	};
};

#endif // __IDHAMemoryXferBytes_h__