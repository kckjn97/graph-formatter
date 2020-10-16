#include <cstdio>
#include <cstdlib>
#include "edge_type.hpp"

void Bin2Txt(FILE* output, FILE *input, const int edge_attr_type = NONE) {
	unsigned int src, target;
	float f_attr;
	double d_attr;
	int i_attr;
	long l_attr;
	void* p_attr;

	int res;
	if (edge_attr_type == INT) {
		struct IntEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u %d\n", edge.src, edge.target, edge.attr);

	}else if (edge_attr_type == LONG) {
		struct LongEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u %ld\n", edge.src, edge.target, edge.attr);

	}else if (edge_attr_type == FLOAT) {
		struct FloatEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u %f\n", edge.src, edge.target, edge.attr);

	}else if (edge_attr_type == DOUBLE) {
		struct DoubleEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u %lf\n", edge.src, edge.target, edge.attr);

	}else if (edge_attr_type == PTR) {
		struct PtrEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u %p\n", edge.src, edge.target, edge.attr);

	}else {
		struct DefaultEdge edge;
		fread(&edge, sizeof(edge), 1, input);
		fprintf(output, "%u %u\n", edge.src, edge.target);
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

	if(output_file) {
		if (!(fp_output = fopen(output_file, "w+"))) {
			fprintf(stderr, "can not open graph file");
			exit(-1);
		}
	}else{
		fp_output = stdout;
	}

	while (!feof(fp_input))
		Bin2Txt(fp_output, fp_input, edge_attr_type);

	fclose(fp_input);
}

void PrintUsage(){
	printf("./txt2bin  input_binary_file  edge_attribute_type  [output_text_file = STDOUT] \n");
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

	char* output = NULL;
	if(argc > 3)
		output = argv[3];

	edge_attr_type = argv[2][0];
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

	ConvertFile(argv[1], output, edge_attr_type);
	return 0;
}
