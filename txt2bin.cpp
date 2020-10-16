#include <cstdio>
#include <cstdlib>
#include "edge_type.hpp"

void Txt2Bin(FILE* output, const char *str, const int edge_attr_type = NONE) {
	unsigned int src, target;
	float f_attr;
	double d_attr;
	int i_attr;
	long l_attr;
	void* p_attr;

	int res;
	if (edge_attr_type == INT) {
		struct IntEdge edge;
		res = sscanf(str, "%u %u %d", &edge.src, &edge.target, &edge.attr);
		if (res < 3)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);

	}else if (edge_attr_type == LONG) {
		struct LongEdge edge;
		res = sscanf(str, "%u %u %ld", &edge.src, &edge.target, &edge.attr);
		if (res < 3)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);

	}else if (edge_attr_type == FLOAT) {
		struct FloatEdge edge;
		res = sscanf(str, "%u %u %f", &edge.src, &edge.target, &edge.attr);
		if (res < 3)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);

	}else if (edge_attr_type == DOUBLE) {
		struct DoubleEdge edge;
		res = sscanf(str, "%u %u %lf", &edge.src, &edge.target, &edge.attr);
		if (res < 3)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);

	}else if (edge_attr_type == PTR) {
		struct PtrEdge edge;
		res = sscanf(str, "%u %u %p", &edge.src, &edge.target, &edge.attr);
		if (res < 3)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);

	}else {
		struct DefaultEdge edge;
		res = sscanf(str, "%u %u", &edge.src, &edge.target);
		if (res < 2)
			fprintf(stderr, "parse error: %s\n", str);
		else
			fwrite(&edge, sizeof(edge), 1, output);
	}
}

void ConvertFile(char* input_file, char* output_file, int edge_attr_type = NONE){
	const int kBufSize = 4096;
	FILE *fp_input;
	FILE *fp_output;
	char buf[kBufSize];

	if (!(fp_input = fopen(input_file, "r"))) {
		fprintf(stderr, "can not open input file");
		exit(-1);
	}

	if (!(fp_output = fopen(output_file, "w+"))) {
		fprintf(stderr, "can not open graph file");
		exit(-1);
	}

	while (fgets(buf, kBufSize, fp_input) != NULL) {
		int first_char_idx = 0;
		while (buf[first_char_idx] == ' ' || buf[first_char_idx] == '\t')
			first_char_idx++;

		if (buf[0] == '#')
			continue;

		Txt2Bin(fp_output, buf, edge_attr_type);
	}
	fclose(fp_input);
}

void PrintUsage(){
	printf("./txt2bin  input_text_file  output_binary_file  [edge attribute type = None]\n");
	printf("\n");
	printf("Edge Attribute Type:\n");
	printf("\tn : None (Default)\n");
	printf("\ti : Integer\n");
	printf("\tl : Long\n");
	printf("\tf : Float\n");
	printf("\td : Double\n");
}

int main(int argc, char** argv) {
	int edge_attr_type;

	if(argc < 3) {
		PrintUsage();
		exit(-1);
	}

	if(argc < 4)
		edge_attr_type = NONE;
	else
		edge_attr_type = argv[3][0];

	switch(edge_attr_type){
		case NONE:
		case INT:
		case LONG:
		case FLOAT:
		case DOUBLE:
		case PTR:
			break;
		default:
			PrintUsage();
			exit(-1);
	}

	ConvertFile(argv[1], argv[2], edge_attr_type);
	return 0;
}
