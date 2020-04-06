#include <M5Stack.h>

const uint8_t r2d2_snappy[] PROGMEM = {129,129,128,128,127,126,126,126,127,127,128,130,131,130,126,124,123,126,131,132,130,124,123,128,132,130,123,
	121,128,133,131,124,122,129,133,131,125,123,127,132,131,126,121,120,123,130,134,135,133,129,125,123,123,125,126,127,131,133,133,
	131,128,127,127,126,123,122,121,121,121,120,123,127,130,130,130,130,132,134,133,133,135,137,133,129,127,129,131,129,126,122,119,
	119,117,118,121,127,135,136,136,133,125,119,117,121,135,144,143,131,121,120,134,140,130,114,115,132,137,125,120,131,136,124,117,
	129,139,128,114,119,136,139,126,113,115,131,138,137,126,118,118,121,132,138,139,138,131,118,111,110,113,117,123,131,141,147,145,
	141,136,132,129,125,119,116,111,109,110,112,117,123,128,131,134,138,142,148,155,154,149,142,136,129,120,109, 97, 92, 98,107,123,
	150,166,163,144,110, 87, 90,126,167,165,121, 88,111,165,160,102, 91,149,160, 98, 92,160,155, 90,113,169,125, 84,143,169,106, 88,
	148,166,114, 86,123,171,160,113, 85, 98,139,169,162,139,103, 87, 90,104,130,160,167,159,146,130,114,102,100,104,110,117,123,126,
	132,143,156,159,153,146,139,132,128,122,116,107,100, 97, 98,103,112,123,135,152,167,166,159,149,129,102, 90, 93,111,152,169,157,
	117, 87, 99,150,165,123, 84,121,172,133, 83,131,165, 98,100,169,123, 90,163,135, 87,158,153, 89,139,167, 96, 99,164,142, 87,108,
	163,154,103, 85,114,161,165,139,100, 88, 97,122,155,164,156,141,118, 99, 97,105,118,130,144,158,161,154,145,136,128,123,116,105,
	 99,100,106,115,124,131,137,148,158,156,150,144,137,126,107, 92, 90, 98,115,147,171,169,148,108, 83, 91,135,169,150, 99, 92,146,
	167,113, 95,159,157, 89,126,164, 93,119,165, 92,130,159, 87,143,147, 86,156,143, 84,151,147, 80,125,168,111, 87,142,168,125, 86,
	103,152,167,144,104, 88, 98,126,161,165,154,135,109, 97, 98,108,121,134,151,160,155,148,139,129,119,108, 99, 97,101,110,120,129,
	137,151,160,158,152,143,130,113, 95, 91, 99,111,136,167,171,157,123, 90, 88,118,163,161,115, 85,120,170,139, 89,129,173,110,101,
	167,113, 98,167,102,119,160, 88,152,132,100,171,100,128,161, 83,140,151, 78,133,165, 96,100,167,153, 96,100,154,169,136, 94, 89,
	115,157,163,150,122, 95, 94,104,119,146,164,161,153,139,124,108, 97, 98,102,110,121,133,147,161,164,160,149,138,125,110, 94, 88,
	 91,102,117,141,165,166,159,140,107, 90, 95,122,163,164,130, 86, 90,144,170,122, 88,141,173,107,102,172,121, 92,167,109,106,166,
	 89,145,140, 96,173, 99,138,149, 85,166,109,102,173, 98,107,175,113, 84,156,166,103, 89,140,172,145, 97, 89,111,154,166,154,126,
	 99, 96,105,122,151,165,160,150,134,116, 97, 90, 95,105,116,128,140,157,164,159,152,140,126,111, 96, 88, 92,101,115,135,163,172,
	164,148,118, 90, 88,103,143,169,157,113, 86,112,164,159,102, 96,162,152, 87,128,170, 94,118,167, 87,136,144, 86,165,104,123,155,
	 89,166,111,113,161, 84,146,148, 85,153,153, 89,127,172,129, 95,126,159,142,105, 98,116,144,149,140,121,111,111,120,132,140,140,
	135,128,121,115,115,118,123,128,131,135,138,135,132,129,128,127,125,124,125,126,125,125,128,130,132,132,129,127,125,124,126,127,
	130,130,129,126,123,125,127,129,129,128,130,131,129,128,129,127,125,128,128,128,129,127,128,129,129,128,125,124,124,126,127,128,
	129,128,127,126,127,126,124,124,123,123,124,125,128,129,130,130,130,128,127,126,125,126,126,126,127,129,130,131,131,131,130,128,
	126,127,127,127,129,129,129,128,128,128,128,128,126,127,127,127,128,129,129,130,129,128,126,125,125,127,127,128,129,129,130,130,
	129,130,131,129,128,126,126,126,127,128,128,127,126,125,125,125,126,129,126,128,130,124,133,125,128,131,119,131,125,118,133,128,
	121,135,134,119,123,138,134,119,117,130,138,135,123,116,117,126,137,138,135,128,120,117,119,122,126,133,139,140,136,131,126,122,
	117,115,117,121,126,131,136,140,144,142,138,133,127,120,113,110,113,119,131,145,147,142,127,113,111,124,140,140,123,109,120,141,
	132,112,125,145,127,121,144,127,119,141,120,125,135,113,135,123,124,138,117,139,127,120,139,114,124,140,113,127,148,118,111,142,
	145,115,108,132,149,137,109,101,116,145,159,152,133,109, 97,100,109,127,153,160,153,144,132,117,103, 99,104,110,118,127,138,155,
	164,161,151,138,127,114, 99, 91, 96,106,120,145,169,171,156,127, 91, 79, 93,136,173,164,116, 84,114,169,154, 90, 98,166,138, 80,
	141,153, 83,144,148, 91,168,116,115,162, 89,158,116,114,163, 86,156,131, 93,171,113,102,173,117, 79,150,166,105, 94,149,171,134,
	 92, 97,131,162,157,136,102, 89, 95,113,142,163,163,155,141,118,100, 97,103,109,115,126,139,155,159,155,150,140,127,113,104, 99,
	 99,103,113,130,154,166,161,148,125, 97, 90, 99,125,163,166,141, 96, 87,124,164,140, 89,110,170,140, 85,141,161, 88,141,153, 82,
	159,119,105,166, 86,153,127,112,163, 91,159,122,102,174, 99,117,172, 90,107,169,123, 84,133,168,131, 90,103,152,170,147,108, 90,
	104,134,162,162,150,127, 96, 87, 97,108,122,147,164,165,158,144,132,118,104, 99, 97,101,109,122,139,154,162,161,155,142,126,106,
	 90, 87, 98,130,165,166,155,122, 86, 82,124,172,159,102, 83,140,174,112, 88,160,148, 83,149,152, 86,159,117,105,167, 89,154,108,
	130,152,100,171, 93,152,112,108,165, 81,145,146, 84,156,148, 85,129,173,123, 89,127,170,147, 98, 87,106,147,163,153,120, 97,101,
	110,136,164,164,154,140,116, 96, 91, 94,105,119,137,157,164,160,150,137,122,105, 90, 91,105,117,136,162,169,162,141,105, 83, 91,
	114,155,173,148, 94, 87,140,174,127, 82,133,174,104,101,170,108,110,166, 88,146,129,107,163,103,161, 92,154, 98,145,109,135,115,
	126,144,106,167, 93,162,120,101,176,102,108,169,111, 82,152,172,111, 86,125,166,158,121, 91, 94,127,161,158,141,116, 94, 92,105,
	125,151,163,159,145,135,116, 95, 92,101,113,127,152,167,162,152,139,113, 88, 89, 98,114,158,176,159,124, 95, 97,130,172,153, 96,
	 86,144,165,107, 95,161,128, 95,169,114,116,167,100,161, 99,145,101,141,107,149,110,151,106,147,114,140,116,126,115,126,129,138,
	122,154, 93,158,108,127,156, 92,125,158,109,106,153,152,112,108,131,146,141,122,104,110,129,146,148,140,121,115,116,120,128,137,
	137,137,134,131,126,120,115,118,125,131,134,132,130,125,121,125,128,129,132,131,126,126,127,129,130,124,121,126,128,124,129,131,
	121,130,134,126,132,125,124,130,123,116,123,129,129,132,134,128,125,127,131,130,125,120,124,129,125,131,136,128,125,125,124,133,
	133,127,130,130,128,128,125,129,128,124,129,129,127,125,130,132,129,131,129,129,128,124,132,132,124,127,129,127,129,133,133,132,
	134,128,125,131,129,123,126,123,120,129,123,124,136,127,122,129,129,123,121,123,120,125,127,123,128,133,129,121,125,130,126,123,
	121,125,130,129,131,132,130,131,133,128,124,126,124,123,127,127,134,132,129,135,133,130,127,123,123,123,125,130,129,133,133,124,
	129,131,122,123,121,122,127,128,129,130,133,135,135,131,123,126,124,122,128,131,126,123,130,134,125,123,128,124,121,124,126,125,
	127,130,134,135,128,123,128,128,123,123,126,126,120,127,132,129,133,133,131,129,132,131,120,126,126,119,126,127,127,132,134,129,
	128,129,126,124,124,125,124,128,131,126,125,128,131,133,134,132,126,128,128,118,123,123,126,130,130,131,134,123,141,126,117,136,
	128,116,132,138,119,116,140,147,128,115,117,131,142,136,119,112,116,125,143,146,129,113,112,115,129,139,141,134,117,114,126,144,
	147,125,105,118,143,144,113,116,145,128,115,140,126,118,136,115,133,118,132,124,138,131,132,126,126,128,125,121,123,127,126,124,
	128,135,136,131,129,128,125,127,127,124,122,122,125,131,128,135,132,130,132,120,129,118,125,140,105,139,132,109,143,139,111,119,
	150,144,110,109,133,149,141,117,103,113,139,154,149,133,103, 93,110,142,158,151,120, 95, 98,134,173,160,112, 80,105,165,161,101,
	 90,149,159, 94,118,178,106,126,157, 85,153,101,145,107,147,114,144,122,122,135,125,124,127,128,129,123,125,130,128,128,131,127,
	127,127,126,123,125,126,124,134,134,116,131,134,118,152,101,153, 93,153,117,110,169, 90,123,177,110, 95,159,161,107, 90,129,167,
	149,105, 90,107,153,167,148,110, 90,102,137,163,157,131, 93, 86,114,160,165,141, 97, 93,133,167,146, 92, 97,164,153, 84,119,170,
	 99,121,164, 87,157,110,137,118,135,116,142,113,131,132,124,126,129,127,126,130,131,129,119,115,124,129,128,128,132,130,130,134,
	133,132,133,119,114,136,116,133,128,124,135,132,117,168, 88,158,138, 76,153,154, 83,109,167,154,100, 90,138,175,154,107, 89,111,
	149,159,148,110, 86, 94,134,169,158,126, 99, 99,122,167,160,120, 87, 97,151,157,108, 90,148,171, 96,107,173, 99,114,162, 80,159,
	108,146,116,145,118,142,114,129,134,120,121,125,130,130,129,133,127,127,126,124,136,126,121,133,125,127,130,126,123,127,136,128,
	124,141,108,151,110,147, 95,166, 89,156,135, 83,164,146, 85,133,179,121, 80,124,166,154,112, 83,104,155,166,145,107, 90,101,147,
	168,158,122, 91, 97,119,153,160,124, 91,100,143,169,134, 87,112,165,140, 81,127,168, 88,132,165, 89,164,108,146,119,133,113,136,
	108,134,136,119,124,140,132,123,125,123,122,123,124,130,133,129,128,132,129,132,132,126,124,127,132,128,121,142,113,130,134,119,
	132,138,105,168, 84,143,152, 75,135,171,101, 91,154,180,122, 84,111,153,153,130, 90, 91,122,162,164,140,100, 85,106,156,169,152,
	117, 89, 99,146,162,143, 97, 89,138,169,120, 78,138,171,100,118,172, 99,132,146, 93,153, 90,156,107,147,125,135,138,124,136,131,
	123,116,117,130,132,135,132,129,128,126,130,123,123,125,125,129,127,125,125,132,138,124,127,138,107,150, 99,153, 85,159, 89,142,
	158, 88,159,161, 93,111,170,135, 75, 97,160,165,119, 91,109,146,177,155, 99, 88, 97,138,158,154,119, 89,103,138,169,161,112, 84,
	111,161,153,100, 94,149,171, 96,105,175,108, 99,175, 91,143,128,126,142,132,122,136,114,132,117,125,134,127,128,131,131,131,122,
	121,132,125,123,132,129,127,125,129,127,132,133,128,126,127,120,120,135,126,133,129,123,137,131,116,143,111,127,130,110,128,136,
	125,128,144,139,127,121,118,130,132,126,120,121,127,127,131,132,131,133,128,127,127,130,123,120,126,133,131,125,126,127,125,128,
	120,124,127,131,133,132,125,123,124,126,121,128,125,127,126,134,133,127,120,132,131,124,132,124,120,132,131,135,126,125,123,125,
	123,130,131,129,124,124,127,138,136,128,123,127,124,123,126,125,130,130,125,130,131,131,131,137,124,127,133,125,117,132,132,134,
	121,119,134,140,131,130,123,122,127,131,133,129,121,114,122,141,142,136,114,116,128,135,138,123,114,127,138,129,114,134,141,116,
	123,141,115,131,131,121,133,122,138,122,134,136,121,129,128,122,126,132,129,129,131,124,121,130,135,133,126,126,126,128,129,128,
	124,124,121,128,134,128,132,126,127,129,120,136,126,129,139,104,150,124,100,148,131, 93,131,160,134, 96,108,155,162,134, 86, 79,
	124,169,174,134, 78, 74,103,174,202,162, 94, 50, 63,160,214,169, 79, 46,126,208,158, 57, 84,205,149, 49,161,167, 48,178,116,114,
	158, 91,169, 94,143,127,111,143,118,127,134,136,135,130,122,120,127,131,126,131,122,123,133,131,133,127,121,120,130,142,127,108,
	131,131,105,167,103,166, 74,173, 75,167,156, 63,164,124, 72,166,190, 91, 62,157,201,123, 74, 96,140,172,168,104, 78,103,131,188,
	162,132, 69, 87,121,172,173,129, 85, 80,137,188,156, 85, 75,148,177, 98, 83,177,148, 76,163,130, 90,185, 77,158, 90,157,101,163,
	111,127,141,109,133,131,133,126,113,141,123,115,137,133,114,124,144,133,117,118,129,139,131,114,122,129,134,151,135,104,146, 87,
	175, 90,175, 93,115,160, 72,166,175, 69,107,184,138, 72, 94,170,183,113, 62,107,167,166,168, 95, 72,105,149,187,154,105, 76, 91,
	141,180,167,111, 71, 94,162,172,119, 68,123,193,123, 65,155,167, 66,153,158, 78,172, 79,162,105,153, 98,149,110,139,141,126,122,
	132,110,134,120,132,137,116,133,143,125,118,124,137,121,114,124,138,140,123,125,130,116,138,149,100,147, 83,168, 91,197, 95,130,
	145, 66,173,170, 70,103,180,151, 83, 95,157,171,125, 63, 95,162,169,160,109, 67, 95,125,188,167,134, 80, 82,113,168,177,139, 82,
	 75,139,186,139, 69,104,188,138, 73,144,160, 75,154,146, 81,181, 86,160,100,155,104,155,114,129,129,125,119,144,116,133,122,122,
	137,120,117,141,128,113,125,151,136,110,125,130,134,127,132,122,107,149,133,123,153, 96,143,110,120,171, 74,164,141, 64,161,184,
	 83, 76,165,185,113, 66,104,189,178,119, 84, 74,127,193,161,132, 72, 85,115,177,174,142, 78, 81,127,178,161, 93, 82,130,178,124,
	 71,135,179, 95,102,188, 92,121,160, 84,169, 82,162,102,154,131,109,137,125,121,141,135,125,126,114,143,125,118,141,124,114,130,
	142,125,113,115,143,147,125,115,121,140,135,120,129,116,112,154,113,171, 79,161, 83,147,161, 84,171,116, 61,167,192, 87, 71,164,
	186,106, 71,122,163,169,133, 61,101,141,182,156,107, 71,109,163,176,135, 79, 82,147,182,130, 70,108,186,141, 73,142,171, 72,134,
	171, 81,167, 82,153,117,156,102,146,116,125,140,130,126,126,121,130,135,132,132,127,111,139,128,121,136,131,113,125,147,128,115,
	125,136,139,123,120,126,132,128,122,142,108,132,132,126,131,124,103,187, 72,149,152, 57,152,195, 87, 68,177,177, 83, 83,148,165,
	152, 84, 74,144,175,167, 88, 76,119,181,170, 97, 70,124,186,151, 73,100,185,140, 69,145,174, 73,145,151, 83,181, 82,167,101,156,
	100,137,126,123,135,131,118,114,133,143,132,127,120,129,116,139,127,124,137,110,128,143,123,123,130,130,120,132,138,131,117,117,
	127,145,140,124,103,133,125,146,140, 98,131,121,123,175, 66,160,154, 70,151,174, 85, 91,183,159, 67,100,175,167,116, 63,119,180,
	162, 99, 73,127,181,152, 87, 84,160,178,102, 82,154,164, 73,117,186, 82,126,165, 73,174, 96,161, 98,147,100,143,129,119,131,127,
	126,127,130,132,126,127,131,132,128,135,120,123,127,122,143,125,117,137,115,126,131,135,118,118,135,133,125,121,128,135,122,129,
	127,130,155, 91,145, 90,192, 93,154,106, 99,198, 91, 92,197,127, 60,151,184,108, 80,122,191,135, 82, 86,164,172,121, 70,106,180,
	161, 88, 79,158,176, 92, 81,174,152, 69,151,157, 73,168,115,118,157, 93,150,117,138,132,111,138,126,125,133,129,127,120,129,132,
	131,130,126,128,129,138,121,136,125,117,139,125,131,129,116,127,142,132,115,126,142,129,120,118,128,143,127,104,138,125,141,119,
	115,116,170, 82,169, 91,125,173, 76,110,181,121, 83,111,178,143, 69,109,161,173,101, 82,128,180,152, 86, 84,155,180,113, 75,141,
	180,102, 87,180,132, 70,179,124,103,175, 75,163,100,167,103,146,121,122,137,127,127,130,128,126,130,127,124,130,131,132,123,133,
	123,134,120,140,124,124,133,112,130,140,119,118,136,135,121,125,136,133,123,114,125,147,133,106,139, 99,173, 97,162, 70,174,129,
	 85,175,112, 92,167,136, 81,129,184,106, 78,125,170,143, 77, 93,162,171,118, 79,115,176,154, 92, 97,162,154, 79,111,179,113, 96,
	181,105,113,171, 85,166, 99,150,102,151,113,127,137,125,125,128,124,130,133,130,127,126,124,128,126,129,132,121,123,121,136,120,
	136,131,116,137,136,118,130,136,122,119,135,137,127,120,133,129,129,138,108,144,124,132,108,149,104,175, 83,115,179, 90,111,179,
	121, 75,149,169,110, 88,121,180,134, 99, 96,156,169,121, 85,113,167,151, 96,100,160,162, 97,103,167,123, 84,160,120,102,166, 90,
	149,111,144,111,141,115,136,127,126,125,128,131,125,131,124,123,127,130,122,138,126,125,130,126,124,137,119,128,123,121,134,133,
	122,129,139,127,115,129,136,127,121,119,131,145,105,136,112,154,117,150, 87,165,123,110,160,116,111,153,133,100,120,170,137, 88,
	112,150,159,125, 90,106,157,152,120, 95,111,149,152,114, 96,135,157,123,101,143,155,100,118,163,101,131,140,102,150,104,149,108,
	137,114,130,136,124,126,125,126,126,133,130,122,125,130,124,134,124,132,123,130,126,133,131,118,129,135,128,124,127,127,126,124,
	132,139,127,114,135,138,134,139,105,138,123,132,145, 91,145,137, 99,136,147,114,109,137,152,122, 96,121,149,140,131,107,111,130,
	151,143,119,100,121,149,149,129,104,107,139,149,125,100,123,151,129,100,142,139,106,147,128,114,148,109,147,113,140,114,137,125,
	124,133,127,125,127,132,132,126,130,126,129,127,132,125,126,125,124,133,129,124,127,132,129,123,125,134,135,119,124,130,122,140,
	117,132,111,143,114,148,126,109,143,123,113,144,136,109,113,138,144,122,112,116,130,146,141,118,115,116,129,142,142,131,115,114,
	120,138,143,136,115,112,121,144,140,119,114,137,143,118,115,144,133,114,140,123,123,141,116,140,118,138,121,134,126,126,131,122,
	125,130,126,126,126,126,128,124,132,128,123,131,131,125,125,129,131,128,123,127,132,127,132,120,132,124,137,119,136,118,127,134,
	118,133,138,116,119,136,136,122,118,125,136,136,127,118,118,131,139,134,129,123,116,122,126,134,138,131,126,118,121,125,133,136,
	132,124,119,122,132,135,129,120,125,135,130,121,130,135,121,126,133,121,134,124,127,126,126,127,129,127,128,126,127,130,127,128,
	128,126,128,128,127,128,128,126,127,129,128,128,126,126,128,128,129,126,127,126,128,128,129,
};
