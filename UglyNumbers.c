#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define NOTHING 0
#define PLUS 1
#define MINUS 2

uint32_t makeNumbers(uint8_t operators[], const uint8_t numbers[], const uint8_t numbersSize);
uint8_t changeOperatorList(uint8_t *numberList, uint8_t index);

uint8_t identifyer = 0;

int main(int argc, char *argv[]) {
	fprintf(stderr, "No segfault Begin\n");
	FILE *fp = fopen(argv[1], "r");
	char buffer[1024];
	fprintf(stderr, "No segfault Initialized\n");
	while (fgets(buffer, 1024, fp) != NULL) {
		fprintf(stderr, "No segfault fgets\n");
		char *begin;
		char *nextBegin;
		for (begin = buffer; begin[0] != '\0'; begin = nextBegin + 1) {
			fprintf(stderr, "No segfault beginFor\n");
			nextBegin = strchr(begin, '\n');
			if (nextBegin == NULL) {
				printf("NextBegin NULL!\n");
				break;
			}
			fprintf(stderr, "No segfault nextBegin\n");
			*nextBegin = '\0';
			if (nextBegin - begin == 1) {
				uint32_t n = atoi(begin);
				printf("%d\n", n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0);
				continue;
			}
			fprintf(stderr, "No segfault bigNumber\n");
			uint8_t *numbers = malloc((nextBegin-begin) * sizeof(uint8_t));
			if (numbers == NULL) {
				fprintf(stderr, "ERROR IN MALLOC!\n");
				break;
			}
			fprintf(stderr, "No segfault numbers\n");
			char *c;
			for (c = begin; c < nextBegin; c++) {
				numbers[c - begin] = c[0] - 48;
			}
			
			fprintf(stderr, "No segfault numbers initialized\n");
			
			
			uint8_t *operators = malloc((nextBegin - begin - 1) * sizeof(uint8_t));
			if (operators == NULL) {
				fprintf(stderr, "ERROR IN MALLOC\n");
			}
			uint8_t i = 0;
			for (i = 0; i + 1 < nextBegin - begin; i++) {
				operators[i] = 0;
			}
			
			fprintf(stderr, "No segfault operatorsInitialized\n");
			
			/*printf("Numbers: [%d", numbers[0]);
			uint8_t i;
			for (i = 0; i < nextBegin - begin; i++) {
				printf(", %d", numbers[i]);
			}
			printf("]\n");
			
			printf("Operators: [%d", operators[0]);
			if (nextBegin - begin > 2) {
				for (i = 0; i < nextBegin - begin - 1; i++) {
					printf(", %d", operators[i]);
				}
			}
			printf("]\n");*/
			identifyer = 0;
			printf("%d\n", makeNumbers(operators, numbers, nextBegin - begin) - 1);
			fprintf(stderr, "No segfault madeNumbers\n");
		}
	};
	fclose(fp);
	return 0;
}

uint32_t makeNumbers(uint8_t operators[], const uint8_t numbers[], const uint8_t numbersSize) {
	int32_t n = numbers[0];
	uint8_t i;
	fprintf(stderr, "No segfault beforeMakingN\n");
	for (i = 0; i + 1 < numbersSize; i++) {
		switch (operators[i]) {
			case NOTHING:
				n *= 10; //NO BREAK HERE!
			case PLUS:
				n += numbers[i + 1];
				break;
			case MINUS:
				n -= numbers[i + 1];
				break;
		}
	}
	fprintf(stderr, "No segfault afterMakingN\n");
	
	uint8_t isUglyNumber = (uint8_t) (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0);
	
	fprintf(stderr, "No segfault beforeChangingOperatorList: %d\n", identifyer++);
	if (changeOperatorList(operators, numbersSize - 2) == 0) {
		return isUglyNumber;
	}
	fprintf(stderr, "No segfault afterChangingOperatorList\n");
	return makeNumbers(operators, numbers, numbersSize) + isUglyNumber;
}

uint8_t changeOperatorList(uint8_t *numberList, uint8_t index) {
	fprintf(stderr, "No segfault beginChangingOperatorList\n");
	if (numberList[index] == 2) {
		numberList[index] = 0;
		return index && changeOperatorList(numberList, index - 1);
	}
	return ++numberList[index];
}