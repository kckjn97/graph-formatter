#ifndef GRAPH_TXT2BIN_EDGE_TYPE_HPP
#define GRAPH_TXT2BIN_EDGE_TYPE_HPP

enum{
	NONE = 'n',
	FLOAT = 'f',
	DOUBLE = 'd',
	LONG = 'l',
	INT = 'i',
	PTR = 'p',
} ATTR_TYPE;

struct DefaultEdge{
	unsigned int src;
	unsigned int target;
};

struct IntEdge{
	unsigned int src;
	unsigned int target;
	int attr;
};

struct LongEdge{
	unsigned int src;
	unsigned int target;
	long attr;
};

struct FloatEdge{
	unsigned int src;
	unsigned int target;
	float attr;
};

struct DoubleEdge{
	unsigned int src;
	unsigned int target;
	double attr;
};

struct PtrEdge{
	unsigned int src;
	unsigned int target;
	double attr;
};

#endif //GRAPH_TXT2BIN_EDGE_TYPE_HPP
