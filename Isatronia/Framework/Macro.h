
//--------------------------------------------------------------
// Macros about COM
//--------------------------------------------------------------
#define ReleaseCOM(x) { if(x){ x->Release(); x = nullptr; } }
#define DXInit_s(res, str) { if (FAILED(res)) {__POSTERR(str);return 0; } }

//--------------------------------------------------------------
// Macros about 16bit color
//--------------------------------------------------------------
#define __RGB16BIT555(r,g,b) ((b & 31) + ((g & 31) << 5) + ((r & 31) << 10))
#define __RGB16BIT565(r,g,b) ((b & 31) + ((g & 63) << 5) + ((r & 31) << 11))
#define __RGB32BIT(a,r,g,b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

//--------------------------------------------------------------
// other Macros
//--------------------------------------------------------------
#define __POSTERR(str) {MessageBoxA(0, str, "Error", NULL);}
//#define __ZEROMEM(obj) {memset(&obj, 0, sizeof(obj));}