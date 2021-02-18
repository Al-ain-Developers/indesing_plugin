/*
	This is a hack. The MSVC 7.2 resource compiler is over aggressive about looking
	for dependencies, to the point of assuming that a #include of the mac-only file 
	types.r (within a #ifdef MACINTOSH) is relevant. Created this file to appease that
	compiler.
*/

#ifdef MACINTOSH
#error "Why is this on the include path?"
#endif
