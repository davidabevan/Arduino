#include <M5Stack.h>

const uint8_t r2d2_surprised[] PROGMEM = {126,126,126,127,
	127,128,128,127,127,128,130,129,129,128,128,129,129,131,132,132,131,131,129,128,128,129,129,129,129,129,128,127,124,123,120,119,
	117,118,121,127,131,131,132,132,130,129,128,129,133,137,139,140,140,138,135,131,127,123,122,125,127,127,127,127,126,124,122,118,
	112,109,112,117,122,129,134,138,136,131,127,129,133,133,131,132,136,141,144,143,140,136,130,123,120,120,124,129,129,127,125,126,
	123,117,113,110,109,111,116,122,128,133,133,132,131,129,128,128,134,139,143,148,150,150,146,139,132,127,127,126,125,125,127,129,
	126,121,114,107,103,103,107,112,122,131,133,131,129,129,130,129,128,130,135,142,147,150,150,146,140,132,125,121,123,128,128,126,
	128,130,129,122,116,112,108,106,108,115,124,133,136,132,128,126,125,125,126,132,138,144,148,150,149,143,135,128,126,125,123,127,
	133,134,132,124,117,109,103,101,105,115,122,125,129,132,130,126,123,126,130,136,143,148,151,150,145,136,128,127,127,121,122,127,
	135,136,132,125,117,108,104,105,111,121,132,137,135,134,133,130,125,122,124,128,135,143,150,151,148,139,127,119,119,118,118,126,
	132,137,133,125,117,108,102,101,108,116,122,131,140,139,136,129,129,130,135,141,147,150,149,146,145,140,131,126,123,122,121,119,
	116,115,112,110,110,113,116,115,117,123,126,128,130,133,139,142,145,147,146,145,141,136,132,135,136,131,126,126,127,125,119,115,
	110,106,105,107,115,124,127,128,130,129,126,125,127,133,139,145,149,152,149,142,137,137,132,126,126,129,133,131,125,117,109,104,
	105,107,107,115,123,124,123,121,125,132,138,144,147,146,141,139,142,138,136,139,141,140,132,124,116,110,109,112,118,121,121,124,
	126,122,122,120,124,129,135,140,143,144,140,134,132,134,131,128,129,130,132,129,124,118,112,108,110,115,117,119,127,130,129,127,
	126,131,136,142,146,147,142,141,144,138,133,133,133,133,124,114,107,104,107,112,112,119,126,125,120,115,122,133,144,153,159,153,
	147,141,130,124,126,132,136,129,120,111,104,103,107,113,116,123,128,127,126,125,134,142,149,150,147,142,135,136,138,135,134,135,
	133,130,122,114,108,105,105,109,111,111,119,123,120,118,120,128,137,146,155,157,154,156,150,139,137,139,142,138,127,115,104, 97,
	 92, 91,104,113,115,113,111,118,127,141,150,156,165,158,146,145,146,151,148,137,123,109,101, 97,101,116,122,119,111,106,112,122,
	136,149,152,147,142,130,124,131,141,150,146,133,118,106,105,111,117,129,134,127,118,108,111,121,136,148,150,147,144,134,126,131,
	139,148,146,135,121,110,100, 96,106,118,122,121,116,118,122,131,143,158,160,147,141,137,140,140,134,128,117, 99, 91,100,112,123,
	126,126,125,127,132,145,160,159,148,137,129,126,123,124,122,116,103, 94,103,115,126,133,132,133,135,138,141,149,158,148,132,125,
	122,129,131,127,122,116,102, 95,107,122,132,133,127,126,127,132,140,158,161,149,140,132,135,137,135,131,115, 94, 90, 94,103,113,
	120,127,126,132,149,158,159,163,160,153,136,126,115, 99, 95, 95, 96, 99,104,118,128,139,158,167,162,159,155,152,138,125,114, 97,
	 86, 88, 95,104,112,121,133,142,149,169,181,170,160,150,138,127,112,104, 92, 72, 70, 82, 98,115,126,140,147,152,165,183,185,176,
	167,153,140,124,113, 95, 77, 72, 71, 75, 87,101,118,134,158,167,170,179,183,183,169,145,116,101, 92, 85, 83, 85, 94,108,131,140,
	144,157,166,172,163,144,119,105, 99, 93, 91, 94,107,117,132,149,152,159,168,173,174,158,141,113, 92, 81, 74, 75, 83,101,112,126,
	149,154,162,175,182,184,169,149,118, 94, 85, 79, 81, 85, 97,109,133,151,155,169,178,185,177,149,120,100, 77, 63, 60, 66, 95,129,
	144,154,171,187,204,191,167,147,127, 96, 68, 52, 66, 94,110,120,134,150,166,160,153,155,149,135,120,103,105,120,122,123,129,128,
	140,140,126,129,135,129,126,115,106,110,122,121,120,132,143,153,157,142,131,134,124,118,108,104,118,131,129,128,137,147,157,138,
	121,119,111,101, 93, 99,132,145,147,158,164,170,144,121,113,100, 84, 77,101,127,133,149,167,179,162,134,129,109, 91, 84,111,137,
	144,161,170,168,135,105, 92, 68, 63, 74,109,143,156,177,195,199,176,140,124,102, 84, 74, 79,114,131,133,145,150,152,128,111,115,
	118,124,127,137,163,158,147,141,132,124, 95, 93,100,100,104,115,147,155,155,166,166,145,113,107, 92, 79, 89,125,143,152,181,192,
	168,135,111, 73, 48, 65, 98,122,168,200,203,176,149,101, 46, 46, 77,102,145,195,216,194,169,129, 75, 43, 62, 92,122,171,207,199,
	175,148, 99, 46, 43, 75, 91,131,186,219,201,174,146, 91, 36, 44, 72, 95,141,195,221,202,181,142, 79, 38, 49, 67, 99,156,203,209,
	193,165,108, 63, 46, 58, 88,135,175,206,201,163,131, 89, 62, 80,106,127,173,178,145,128,105, 80,103,131,148,170,149,122,106, 86,
	106,146,160,182,164,108, 76, 68, 76,116,170,200,203,166,109, 67, 57, 76,122,173,193,190,158,103, 63, 59, 74,107,159,187,202,194,
	153,113, 85, 59, 71,107,124,162,180,152,138,119, 92,106,124,138,159,148,134,113, 89,112,134,161,184,144,111, 65, 42, 83,121,194,
	241,213,168, 90, 35, 34, 86,157,190,197,128, 73, 69, 98,173,199,192,131, 52, 43, 76,155,216,220,179, 88, 27, 38, 94,177,221,213,
	138, 48, 38, 71,149,218,214,172, 78, 17, 49, 94,184,241,209,155, 57, 22, 58,113,205,232,196,121, 37, 34, 74,146,216,224,171, 85,
	 38, 55,121,192,222,169, 86, 35, 63,125,199,214,154, 81, 45, 87,146,207,191,146, 87, 66, 83,124,148,156,162,155,153,123,100, 75,
	 87,121,164,180,157,111, 82, 78,128,164,189,151,107, 78, 91,129,173,178,142, 99, 77,108,133,171,144,112, 84,103,144,176,182,135,
	 91, 68,102,145,186,164,121, 83, 92,130,152,148,105,100,118,163,171,140, 94, 99,129,167,149,103, 94,127,177,153,104, 58,101,164,
	182,131, 70, 99,162,195,148, 71, 74,132,191,176,104, 69,104,163,167,123, 78,102,151,175,147, 92, 94,127,168,157,114, 80,107,147,
	179,151,100, 79,104,156,177,152, 95, 83,106,163,172,138, 84, 95,138,177,154, 88, 78,120,187,173,104, 60,102,179,184,112, 64,110,
	183,181, 95, 65,129,202,156, 64, 69,160,204,124, 61,107,191,165, 69, 69,157,209,134, 55, 92,177,185, 97, 75,138,195,146, 68, 80,
	155,196,137, 79, 91,151,155,107, 88,127,184,167,106, 77,109,174,167,109, 70,103,176,181,118, 68, 99,177,183,109, 66,111,194,172,
	 82, 60,139,202,144, 59, 81,178,186, 93, 67,146,194,120, 66,139,199,129, 50,121,210,146, 50,108,208,144, 38, 98,213,165, 49, 92,
	207,165, 58, 94,191,144, 56,112,202,153, 67,118,196,133, 51,113,200,156, 62, 96,187,173, 79, 81,168,181, 92, 57,135,206,150, 65,
	 92,181,173, 81, 72,158,189,107, 65,140,195,125, 61,130,194,125, 59,131,198,120, 61,148,196,101, 65,168,168, 63,101,207,148, 53,
	135,196, 85, 66,183,170, 63,120,200,122, 73,151,152, 88,135,166, 91, 97,181,145, 77,134,183,102, 83,172,159, 66,111,201,132, 54,
	134,193,102, 67,161,177, 84, 96,185,148, 69,126,190,109, 65,161,183, 76, 84,199,165, 48,100,207,132, 50,153,202, 85, 72,184,156,
	 63,127,180,107,103,152,114,126,170,113,104,168,112, 90,173,126, 90,181,125, 58,171,161, 60,150,172, 73,135,168, 86,137,158, 93,
	152,148, 61,146,183, 71,114,189, 92,103,186,100, 86,192,140, 66,154,161, 79,123,163,112,125,152,110,112,158,128, 97,149,159, 92,
	116,175,115, 88,164,136, 84,152,141, 90,161,138, 79,165,145, 77,163,132, 87,186,113, 82,191, 89,107,198, 65,137,175, 55,176,128,
	 74,197, 84,142,157, 61,201, 98, 96,202, 57,149,170, 54,187,106, 94,198, 69,145,176, 57,169,143, 71,180,107,110,181, 70,141,185,
	 61,149,168, 57,166,152, 64,178,135, 81,183,100,101,191, 81,113,183, 72,142,168, 64,167,140, 71,194,107, 89,195, 72,141,159, 68,
	194, 89,122,176, 57,176,117,119,138,106,182, 66,180,109,114,171, 66,191, 81,153,134,101,168, 79,181, 89,155,110,131,151, 78,193,
	 70,159,128, 96,178, 69,177, 93,142,137, 91,187, 64,173,119, 97,184, 62,181,111,102,184, 64,177,105,117,168, 71,180, 97,128,151,
	 90,186, 73,156,137, 90,186, 70,171,114,121,151, 90,170, 93,158,105,140,124,124,144,102,149,117,137,115,153, 94,158,106,141,131,
	121,121,146,105,144,124,119,141,116,142,113,139,112,150,105,139,130,116,143,120,129,135,122,135,117,141,108,153,101,155,107,150,
	101,158, 99,158,100,158,107,127,146,102,168, 82,175, 86,162,106,133,134,120,131,128,130,122,139,116,148, 97,168, 87,164,102,141,
	118,134,135,110,152,101,156, 98,147,118,135,128,118,145,109,144,118,126,143,104,150,117,126,142,107,156, 97,153,111,132,143, 98,
	159,102,150,108,141,123,127,132,119,140,112,148,110,143,121,137,116,133,127,119,149, 96,170, 90,163, 97,145,124,121,139,117,145,
	103,155,107,144,116,135,125,127,127,130,123,136,121,134,126,120,146,109,134,134,122,128,133,118,139,122,127,129,134,116,132,135,
	116,138,133,115,142,122,122,135,125,121,141,120,125,141,117,128,137,117,136,126,124,135,128,116,147,114,132,136,114,141,123,121,
	143,108,149,112,133,139,116,135,128,121,135,131,114,140,122,128,134,122,124,142,116,128,138,121,127,133,125,125,132,129,122,133,
	123,135,121,129,131,124,133,118,142,113,140,122,133,125,124,129,131,126,124,131,128,131,122,136,120,136,120,134,123,135,121,132,
	123,133,123,127,135,120,132,126,133,119,137,125,131,121,137,122,129,128,135,117,132,133,121,126,139,121,124,139,118,134,126,130,
	133,118,137,125,131,119,138,122,130,128,127,135,115,139,120,134,122,134,123,129,133,124,131,122,133,126,130,122,135,121,132,127,
	129,127,127,129,129,126,130,129,124,132,125,133,123,131,128,122,135,121,133,127,123,137,121,135,121,132,125,132,121,136,122,130,
	130,127,126,127,131,125,132,123,133,126,130,128,124,129,129,129,122,132,128,127,129,126,129,129,125,134,123,128,131,125,130,127,
	131,125,130,128,124,134,119,139,119,135,123,132,126,130,123,133,124,129,130,125,134,122,136,119,134,126,128,128,129,130,126,128,
	133,120,133,126,129,125,130,126,133,125,127,129,127,128,128,128,126,133,122,134,123,132,125,131,127,127,129,129,125,133,124,131,
	126,129,127,126,130,126,130,127,129,127,130,124,132,125,132,126,129,126,132,123,133,125,128,130,127,125,133,124,129,128,128,127,
	130,126,129,129,125,130,126,130,126,130,126,129,128,128,127,129,128,126,129,127,130,126,131,125,130,125,132,123,132,124,131,126,
	128,129,126,129,127,129,125,132,123,133,123,131,127,129,128,127,130,125,132,124,132,125,130,126,130,127,129,129,127,127,128,128,
	127,128,129,129,127,129,129,127,129,126,129,130,125,129,129,125,130,128,127,128,130,125,131,126,129,129,127,130,128,126,130,125,
	131,124,131,126,128,129,126,131,125,130,128,128,126,131,126,129,127,129,128,127,127,129,126,128,129,129,127,129,127,129,127,127,
	129,126,129,126,130,126,130,126,129,127,129,128,126,129,128,126,132,124,132,126,127,130,126,129,127,130,125,132,125,130,127,129,
	126,130,125,131,125,131,127,129,127,129,126,129,127,128,130,126,130,126,129,126,131,124,132,124,132,125,129,128,128,129,128,129,
	126,131,126,128,129,129,127,129,127,128,128,128,128,128,128,129,128,128,128,128,129,128,127,129,127,128,130,126,129,128,129,124,
	132,125,130,127,129,128,128,127,129,128,128,128,129,127,128,128,128,128,127,129,126,128,128,129,126,130,127,128,127,129,127,129,
	128,127,130,125,131,125,129,128,128,129,126,130,127,128,128,129,129,125,131,126,128,128,128,129,128,129,128,127,129,127,129,127,
	128,129,126,130,127,129,127,129,127,129,127,129,128,128,128,129,127,129,127,128,128,128,129,127,129,127,129,127,129,127,129,128,
	127,129,128,128,127,130,127,129,128,128,128,128,128,128,128,128,128,129,127,130,126,130,127,129,129,127,129,128,128,128,129,128,
	127,129,128,128,129,127,129,128,128,129,128,128,128,128,128,127,129,128,128,128,127,130,126,129,127,129,128,128,129,127,128,127,
	128,128,128,129,127,128,128,128,128,128,129,127,129,127,129,127,128,127,128,128,127,129,126,129,127,129,127,128,128,128,128,128,
	128,128,128,128,127,128,128,128,128,127,129,127,128,128,128,128,127,128,127,129,127,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,129,128,128,127,129,128,128,128,128,128,128,129,127,128,128,128,128,129,127,129,127,129,127,129,127,128,128,128,128,
	128,128,127,129,128,128,128,128,128,128,128,129,128,128,127,129,127,129,127,128,128,128,128,128,128,128,128,128,128,127,129,127,
	129,128,128,127,128,128,128,127,128,129,127,129,128,128,128,128,128,128,128,128,127,128,128,128,127,128,128,128,128,127,129,127,
	128,127,128,128,128,128,128,128,128,129,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,129,128,128,
	128,128,128,129,128,129,128,128,129,128,129,127,129,128,128,128,128,127,129,127,128,128,127,128,127,128,127,128,127,129,127,128,
	128,128,128,128,128,128,128,129,128,128,128,129,128,128,128,129,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,127,129,127,128,128,128,128,128,
	128,127,128,127,128,127,128,128,128,128,127,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,129,128,128,129,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,127,128,127,
	128,128,128,128,128,128,128,128,127,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,
	128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,
	128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,
	128,128,128,128,128,128,128,129,128,128,128,128,129,128,128,129,128,129,129,128,128,128,128,128,129,128,128,128,128,128,128,128,
	128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,127,128,128,127,127,127,128,127,127,128,127,128,
	127,128,128,128,128,127,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	129,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,
	128,127,128,128,127,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,129,128,128,128,128,128,129,128,128,128,129,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,127,128,128,128,128,128,128,128,128,128,128,128,129,128,127,128,128,128,
	129,128,128,127,128,128,128,129,128,128,127,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,127,128,129,129,128,127,
	128,128,128,128,128,128,128,128,128,128,127,128,129,129,128,127,127,129,129,128,127,128,129,129,127,127,128,129,129,128,127,128,
	129,129,129,128,128,128,128,128,128,129,128,128,128,128,128,128,129,129,128,128,128,128,128,128,128,129,128,128,128,128,128,128,
	128,128,128,127,127,127,128,128,128,128,127,127,128,128,128,127,127,128,128,128,127,128,127,128,129,126,127,129,129,126,126,130,
	129,126,126,131,129,125,128,131,127,126,129,130,127,127,130,129,127,127,129,129,127,127,128,130,128,127,128,130,129,127,127,129,
	130,128,127,128,128,129,129,128,127,128,129,129,128,128,128,128,129,129,128,128,128,129,128,128,128,128,128,129,128,128,128,128,
	129,129,126,127,132,129,123,128,134,127,123,133,132,120,129,136,122,124,137,126,121,136,129,119,133,133,121,127,134,125,123,132,
	130,122,128,132,125,124,131,129,124,128,130,126,126,129,128,126,127,128,127,127,128,126,127,130,127,125,129,130,126,127,129,128,
	128,129,126,127,130,128,126,127,129,129,128,127,126,130,130,124,126,134,128,121,132,134,120,128,138,120,125,140,121,123,141,120,
	123,141,119,125,140,117,129,138,116,132,136,116,135,134,116,135,133,117,135,133,117,133,134,118,131,135,121,127,135,125,124,134,
	129,123,129,132,127,125,130,131,125,126,132,128,124,130,131,125,127,130,128,127,127,128,131,126,125,131,131,123,127,135,125,123,
	135,128,120,134,132,117,133,135,116,133,135,115,136,131,115,141,124,119,144,115,127,142,110,137,133,112,144,122,122,142,114,133,
	134,114,141,125,119,142,121,123,141,118,126,140,116,129,139,117,129,138,118,128,137,121,126,136,124,124,133,129,122,131,132,123,
	126,134,127,123,132,131,122,130,134,122,126,136,122,124,138,121,124,140,119,126,140,115,133,136,111,142,126,116,147,112,132,137,
	111,145,117,131,134,113,148,111,136,132,115,145,112,141,120,128,138,111,147,115,132,135,113,145,115,131,137,111,145,120,124,142,
	112,137,132,113,143,123,119,144,117,127,139,115,132,137,114,135,134,115,137,130,116,139,128,118,140,125,120,140,121,124,140,115,
	132,135,113,141,125,120,143,112,139,126,120,145,107,146,119,127,137,114,144,109,149,109,142,119,131,134,112,151,102,155,103,152,
	109,141,124,124,142,105,157, 99,151,112,136,129,117,146,109,141,123,125,138,113,145,116,129,141,106,149,117,124,144,108,142,126,
	118,144,115,131,136,113,142,121,123,142,113,136,130,117,141,117,135,126,122,141,111,144,119,128,136,113,148,105,149,114,132,133,
	117,143,111,147,108,148,108,147,111,144,112,145,112,141,120,128,136,112,149,105,152,101,159, 94,162, 96,157,104,146,116,133,129,
	121,139,113,148,106,149,110,141,120,130,132,118,141,116,135,129,118,145,110,142,121,126,139,110,151,105,147,118,128,135,115,144,
	110,148,107,146,116,132,132,115,147,105,153,101,156, 99,155,103,149,111,140,119,135,123,131,128,126,130,129,125,133,123,133,123,
	133,123,134,120,139,111,150,101,157, 98,157, 99,157, 98,159, 96,160, 95,162, 95,159, 98,157, 98,159, 96,162, 92,164, 94,160,100,
	153,108,141,123,125,140,109,154, 98,159, 96,158,100,152,107,146,112,142,117,135,125,125,137,114,147,105,154,101,155,103,149,111,
	143,114,143,111,147,108,148,108,146,113,136,132,110,160, 85,177, 80,170, 95,149,121,118,154, 90,171, 87,161,107,135,133,113,150,
	101,158, 98,155,105,146,117,132,133,114,152, 96,165, 90,166, 92,160,101,149,111,141,118,136,122,134,121,136,117,141,112,146,109,
	149,107,148,109,145,113,138,123,127,135,114,150, 96,170, 78,181, 77,169,104,126,156, 77,192, 65,177,104,119,167, 72,179,100,123,
	165, 71,181,104,112,179, 59,196, 82,137,160, 68,194, 77,149,142, 84,190, 66,173,112,112,170, 73,182, 88,146,136, 98,173, 78,175,
	 90,154,115,128,139,108,154, 98,160, 95,161, 95,158,103,143,125,114,158, 83,181, 74,176, 96,135,150, 81,190, 64,177,108,112,176,
	 66,176,119, 92,192, 65,161,143, 72,195, 87,121,179, 68,154,156, 67,183,116, 89,192, 85,124,179, 62,172,130, 82,190, 90,118,176,
	 76,147,153, 73,184, 97,119,168, 79,159,129, 92,183, 72,164,123, 97,183, 66,173,117,102,182, 64,181,103,117,169, 68,191, 79,148,
	145, 79,192, 77,146,153, 71,194, 81,134,167, 67,175,123, 90,185, 93,118,177, 76,144,161, 84,134,174, 62,170,140, 73,176,130, 81,
	172,130, 82,166,140, 73,181,119, 86,179,113, 97,163,131, 84,176,113,100,163,127, 85,185, 97,108,185, 74,139,168, 63,172,136, 71,
	196, 96, 99,196, 68,141,168, 59,178,131, 75,193, 93,110,186, 68,151,159, 70,169,139, 73,191,100,105,190, 76,127,180, 76,135,171,
	 80,132,166,100,105,185, 94,109,177,100,119,142,132,127, 98,170,123, 83,170,140, 69,171,144, 75,153,154, 91,121,172, 94,114,166,
	113,104,160,122,108,136,153, 93,133,164, 87,130,169, 90,120,179, 88,111,189, 91,102,199, 75,117,193, 73,123,184, 81,114,188, 87,
	110,186, 93,105,177,114, 97,160,140,102,116,176,114, 77,194,124, 67,175,151, 75,136,159,119, 98,139,149,127, 86,146,174, 83, 98,
	184,140, 65,133,192, 97, 77,166,172, 73,103,189,135, 63,141,188, 89, 92,165,163, 71,124,184,106, 87,169,144, 84,140,157,108,111,
	157,130, 98,144,157, 89,122,185, 84,105,195, 94, 91,172,144, 78,136,175, 94,106,162,143, 88,127,167,117, 99,128,179,103, 84,159,
	181, 77, 85,203,145, 49,127,201,121, 55,130,207,115, 51,148,200,115, 51,143,204,108, 56,147,195,114, 67,124,206,121, 61,134,195,
	136, 55,134,204,104, 67,146,190,107, 69,146,196, 91, 67,180,175, 67, 87,202,145, 48,136,201, 94, 67,178,164, 71,109,184,132, 80,
	126,172,142, 62,136,194,112, 63,146,201,103, 57,159,195,106, 56,138,211,121, 45,135,208,132, 52,118,181,163, 98, 63,149,198,125,
	 51,127,184,153, 95, 74,142,198,130, 56,109,199,161, 61, 94,172,180, 95, 74,139,189,134, 69,105,186,158, 84, 83,156,193, 99, 60,
	153,201,100, 55,158,199, 89, 64,163,186,100, 68,144,199,101, 69,138,191,130, 68,112,187,160, 75, 85,170,187, 95, 74,138,177,146,
	 99, 75,151,186,133, 80, 86,165,189,121, 64, 98,184,180,106, 61,108,201,165, 89, 70,124,195,151, 89, 91,124,172,152,117, 82,106,
	178,168,100, 78,120,187,155, 85, 82,148,184,135, 77, 90,167,188,105, 59,127,206,145, 55, 91,187,187, 80, 62,153,198,129, 62,103,
	170,178,113, 64,118,189,161, 85, 87,133,176,150, 99, 94,110,176,167,103, 82,110,167,174,122, 81, 94,154,177,150, 81, 89,128,169,
	162,125, 82, 92,139,191,162, 77, 70,125,193,173, 99, 58,117,177,173,126, 70, 94,155,179,145, 87, 80,134,180,162, 98, 73,117,182,
	175,105, 60,112,195,175, 88, 68,129,184,158,111, 77,103,174,179,122, 67, 92,168,187,133, 65, 92,148,182,155, 91, 75,111,179,173,
	128, 74, 96,132,178,156,118, 89, 98,137,171,151,113,102,109,133,145,148,145,109, 93,113,147,165,144,104, 99,107,149,162,150, 96,
	 95,118,157,154,138, 95,103,125,159,153,127, 92,112,127,164,156,115, 82,109,156,170,139, 91, 97,119,165,160,132, 90, 99,119,174,
	168,116, 81, 98,147,176,151,107, 85,104,149,170,148,106,100,114,131,143,157,137,114, 97,110,136,147,160,134,114, 89,107,129,171,
	171,129, 96, 70,116,147,192,160,115, 80, 75,125,154,188,156,114, 88, 78,109,154,195,170,115, 51, 84,134,186,180,124, 82, 86,129,
	153,168,122,112,111,121,132,147,145,120,105,105,140,158,155,114,102, 94,130,155,171,140,104, 81,100,143,177,175,117, 88, 75,122,
	153,183,158,110, 99, 74,116,137,176,193,133, 83, 50, 89,163,188,195,145, 79, 54, 65,137,191,201,183,107, 57, 44, 81,170,212,206,
	157, 73, 37, 58,121,191,207,199,126, 61, 38, 68,142,199,227,176, 97, 32, 40,111,177,225,194,128, 65, 33, 82,137,214,218,153, 81,
	 29, 71,133,199,214,156, 97, 48, 63,128,176,213,162,104, 67, 55,121,166,193,195,127, 63, 51, 74,154,212,199,164,100, 41, 55, 90,
	160,226,210,158, 92, 29, 45,107,159,217,216,157,100, 51, 38, 93,150,186,212,177,121, 77, 49, 68,126,162,200,197,137,103, 61, 57,
	108,139,191,213,154,116, 65, 44, 99,133,189,214,168,130, 61, 41, 84,122,195,218,176,137, 67, 30, 73,127,189,223,185,133, 69, 32,
	 63,128,180,219,199,140, 78, 43, 50,103,170,198,201,172,126, 66, 53, 73,110,157,187,180,166,142, 92, 75, 88, 99,119,163,164,167,
	148,124,106,115,122, 98, 95,119,137,181,186,150,120, 97, 67, 78,126,143,189,194,143,104, 80, 75,109,152,157,164,158,119,102,100,
	 94,121,155,145,156,154,130,109, 95, 84, 99,138,155,174,181,152,104, 80, 77, 84,107,154,182,196,182,137, 81, 57, 72, 96,123,160,
	185,189,166,146,110, 76, 65, 85, 96,126,166,199,189,163,140, 99, 64, 63, 92,107,138,173,188,170,155,149,109, 79, 74, 75, 86,128,
	171,202,208,182,132, 76, 41, 49, 78,127,172,216,215,175,118, 77, 45, 57, 94,139,176,200,185,152,113, 85, 69, 78,104,145,172,185,
	167,141,103, 78, 86,108,119,141,163,167,148,140,128,113, 92, 97,117,109,117,143,175,174,155,154,136, 97, 57, 83,101,101,131,169,
	204,190,170,156,112, 53, 28, 65, 99,119,172,222,224,182,146,104, 41, 24, 55,107,134,172,214,217,180,145,114, 55, 25, 58, 95,118,
	167,211,218,188,164,125, 63, 27, 48, 80,108,158,209,229,196,174,133, 67, 19, 44, 74, 97,148,204,239,211,176,143, 82, 31, 17, 60,
	 98,131,179,228,235,196,150,114, 56, 17, 35, 75,130,161,193,213,200,174,133, 99, 66, 50, 62, 82,119,166,190,190,182,164,136, 90,
	 69, 76, 87, 97,121,165,172,169,179,167,136, 92, 83, 84, 79, 95,131,167,164,158,165,158,134,115,120,104, 90, 77, 95,118,132,161,
	190,200,172,133,109, 80, 63, 66, 88,128,146,157,180,190,189,147,110, 88, 70, 67, 72, 97,146,169,174,185,176,163,133, 88, 74, 80,
	 92,112,121,144,170,164,139,127,124,133,129,115,129,136,124,111, 99,116,139,137,135,140,141,146,122,124,135,130,113, 95,118,130,
	123,136,153,167,145,118,118,104, 99, 97,115,142,141,147,155,157,150,119,116,119,108,102, 93,113,130,122,136,159,176,176,148,127,
	115, 93, 88, 89, 94,120,141,139,137,144,159,174,160,138,133,119, 92, 79, 73, 92,126,142,147,153,158,167,161,137,123,123,112,101,
	 94, 93,112,133,138,142,146,152,157,129,116,122,125,124,120,119,146,139,116,113,113,128,129,118,136,146,144,135,119,132,134,116,
	108,118,139,145,126,127,138,138,122,104,105,122,127,120,130,145,159,167,151,135,128,119,100, 87, 82, 91,114,133,135,149,165,179,
	188,172,138,113,100, 80, 75, 73, 88,109,139,151,149,157,162,173,175,159,129,114,104, 89, 80, 78, 88,113,137,138,144,157,171,185,
	168,143,131,118, 90, 73, 68, 91,123,136,144,155,162,171,151,129,124,119,109,107,103,113,133,135,126,135,135,146,147,128,126,134,
	125,120,112,107,111,120,128,127,139,149,160,164,155,132,111,108,100, 95, 94,101,113,132,154,150,148,155,155,154,147,133,112,106,
	107,102,102,103,109,116,138,143,136,144,145,158,166,148,128,125,128,119,105, 87, 85,103,118,115,124,141,160,184,179,159,145,141,
	117, 95, 75, 72, 89,115,120,123,143,161,177,179,156,138,134,121,106, 93, 92, 92,113,129,118,119,131,148,164,172,166,153,154,141,
	116, 94, 71, 63, 70, 93,116,130,151,173,189,198,184,172,144,113, 94, 78, 71, 68, 78, 95,107,132,147,150,163,178,192,189,177,153,
	124,105, 81, 64, 55, 62, 79,103,132,145,162,182,194,203,190,159,130,111, 86, 68, 63, 63, 83,110,127,135,151,164,181,195,189,165,
	140,123, 99, 76, 66, 64, 82,104,124,139,147,155,168,180,178,166,158,133,109, 93, 79, 78, 80, 95,110,114,131,149,153,159,166,176,
	177,163,147,126, 99, 83, 79, 78, 84, 94,112,124,134,151,163,169,178,177,167,149,130,108, 90, 81, 79, 85, 98,107,119,132,148,160,
	164,170,170,165,150,130,108, 93, 91, 91, 93,102,111,122,127,143,152,153,160,162,163,152,138,120,102, 96, 95, 96,101,107,119,129,
	134,147,157,156,157,153,143,132,123,115,109,103,106,114,118,121,120,127,133,136,141,148,148,143,140,136,129,124,121,118,112,108,
	110,114,119,125,133,140,144,144,146,142,136,131,126,122,118,117,115,115,118,122,126,131,133,137,137,137,138,134,130,128,129,129,
	126,124,122,120,121,121,122,123,127,131,131,133,135,136,138,137,135,133,128,125,121,116,114,118,123,126,127,127,131,133,133,133,
	136,136,134,133,129,124,121,121,121,122,123,125,128,131,132,132,131,131,130,129,128,126,125,124,124,127,129,132,132,132,130,129,
	128,127,126,126,125,124,124,124,125,126,129,131,133,134,134,134,133,130,127,125,122,121,120,120,122,126,130,133,134,135,135,134,
	132,129,127,125,123,123,122,124,125,127,129,131,131,132,131,132,130,128,126,125,125,125,125,126,127,128,130,131,133,132,132,130,
	128,125,123,123,123,122,124,126,129,132,134,134,135,133,132,129,127,125,123,122,121,122,123,126,128,130,131,133,133,135,134,132,
	131,129,127,125,123,121,121,121,123,125,127,130,133,135,136,135,133,131,129,127,124,122,122,122,123,124,125,128,130,132,133,133,
	133,133,131,130,128,126,126,124,123,123,123,125,126,129,130,132,133,134,133,133,131,129,126,124,123,122,122,124,126,128,130,132,
	133,133,132,131,130,128,127,126,125,125,125,125,126,127,128,129,130,130,130,130,130,130,129,128,127,127,126,125,126,126,127,128,
	129,130,130,130,129,129,128,128,127,128,127,127,126,126,127,128,128,129,130,129,130,129,129,128,128,128,127,126,126,127,126,127,
	128,129,129,129,129,129,129,128,128,128,128,128,127,127,128,127,127,127,128,128,128,129,129,129,129,128,128,128,127,127,127,127,
	127,128,128,128,128,129,
};
