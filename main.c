#include <stdio.h>
#include <stdlib.h>

struct combo
{
	char* one;
	char* two;

	int plen;
	int slen;
	int clen;
	int dlen;
};

struct parent
{
	char* pheno;
	int length;
};

struct square
{
	struct combo* cmb;

	char* data;
};

void print_square(struct square* s);
struct square* generate_square(struct parent p1, struct parent p2);
int int_pow(int x, int y);

int main()
{
	struct parent one = {.pheno = "AaBbCcDd", .length = 8}; /* Implement a method that does error handling & parent checking */
	struct parent two = {.pheno = "AaBb", .length = 4};
	struct parent three = {.pheno = "Aa", .length = 2};

	print_square(generate_square(one, one));
	print_square(generate_square(two, two));
	print_square(generate_square(three, three));

	return 0;
}

void print_square(struct square* s)
{
	#ifdef DEBUG
		fprintf(stdout, "DEBUG:\ns->cmb->one: %s\ns->cmb->two: %s\n", s->cmb->one, s->cmb->two);
	#endif

	/* Header Line */
	for(int i = 0; i < s->cmb->slen + 3; ++i)
		fprintf(stdout, " ");
	for(int i = 0; i < s->cmb->clen; ++i)
	{
		for(int j = 0; j < s->cmb->slen / 2; ++j)
			fprintf(stdout, " ");
		for(int j = s->cmb->slen * i; j < (s->cmb->slen * i) + s->cmb->slen; ++j)
			fprintf(stdout, "%c", s->cmb->one[j]);
		for(int j = 0; j < s->cmb->slen / 2 + 1; ++j)
			fprintf(stdout, " ");
	}
	fprintf(stdout, "\n");

	for(int i = 0; i < s->cmb->clen; ++i)
	{
		/* Margin */
		for(int j = 0; j < s->cmb->slen + 2; ++j)
			fprintf(stdout, " ");

		/* Separator */
		for(int j = 0; j < s->cmb->clen; ++j)
		{
			fprintf(stdout, "+");
			for(int k = 0; k < s->cmb->plen; ++k)
				fprintf(stdout, "-");
		}
		fprintf(stdout, "+\n");

		/* Data */
		fprintf(stdout, " ");
		for(int j = i * s->cmb->slen; j < (i * s->cmb->slen) + s->cmb->slen; ++j)
			fprintf(stdout, "%c", s->cmb->two[j]);
		fprintf(stdout, " |");
		for(int j = 0; j < s->cmb->clen; ++j)
		{
			for(int k = i * s->cmb->plen * s->cmb->clen + (j * s->cmb->plen); k < (i * s->cmb->plen * s->cmb->clen + (j * s->cmb->plen)) + s->cmb->plen; ++k)
				fprintf(stdout, "%c", s->data[k]);
			fprintf(stdout, "|");
		}
		fprintf(stdout, "\n");
	}

	/* Footer Line */
	for(int j = 0; j < s->cmb->slen + 2; ++j)
			fprintf(stdout, " ");
	for(int i = 0; i < s->cmb->clen; ++i)
	{
		fprintf(stdout, "+");
		for(int j = 0; j < s->cmb->plen; ++j)
			fprintf(stdout, "-");
	}
	fprintf(stdout, "+\n");
}

struct square* generate_square(struct parent p1, struct parent p2)
{
	#ifdef DEBUG
		fprintf(stdout, "WTF\n");
	#endif

	/* Step 0: Initialization */
	struct square* smp = (struct square*) malloc(sizeof(struct square));

	/* Step 1: Combo Generation */
	struct combo* cmp = (struct combo*) malloc(sizeof(struct combo));
	cmp->plen = p1.length;
	cmp->slen = p1.length / 2;
	cmp->clen = int_pow(2, cmp->slen);
	cmp->dlen = cmp->clen * cmp->slen;
	cmp->one = (char*) malloc(sizeof(char) * cmp->dlen);
	cmp->two = (char*) malloc(sizeof(char) * cmp->dlen);

	#ifdef DEBUG
		fprintf(stdout, "DEBUG:\ncmp->plen: %d\ncmp->slen: %d\ncmp->one(length):%d\nsizeof(char): %zd\n", cmp->plen, cmp->slen, cmp->dlen, sizeof(char));
	#endif

	for(int i = 0; i < cmp->clen; ++i)
	{
		int t = i;
		int c = 0;

		#ifdef DEBUG
			fprintf(stdout, "%d: ", i);
		#endif

		for(int j = cmp->slen - 1; j >= 0; --j)
		{
			#ifdef DEBUG
				fprintf(stdout, "(%d, ", t);
			#endif

			if(t - int_pow(2, j) >= 0)
			{
				#ifdef DEBUG
					fprintf(stdout, "%d - %d)", t, int_pow(2, j));
				#endif

				cmp->one[(i * cmp->slen) + c] = p1.pheno[(cmp->slen - j - 1) * 2 + 1];
				t = t - int_pow(2, j);
			}
			else
				cmp->one[(i * cmp->slen) + c] = p1.pheno[(cmp->slen - j - 1) * 2];
			++c;
		}
	}

	#ifdef DEBUG
		fprintf(stdout, "DEBUG:\ncmp->one: %s\n", cmp->one);
	#endif

	for(int i = 0; i < cmp->clen; ++i)
	{
		int t = i;
		int c = 0;

		for(int j = cmp->slen - 1; j >= 0; --j)
		{
			if(t - int_pow(2, j) >= 0)
			{
				cmp->two[(i * cmp->slen) + c] = p2.pheno[(cmp->slen - j - 1) * 2 + 1];
				t = t - int_pow(2, j);
			}
			else
				cmp->two[(i * cmp->slen) + c] = p2.pheno[(cmp->slen - j - 1) * 2];
			++c;
		}
	}

	#ifdef DEBUG
		fprintf(stdout, "DEBUG:\ncmp->two: %s\n", cmp->two);
	#endif

	smp->cmb = cmp;

	/* Step 2: Square Calculation */
	smp->data = (char*) malloc(sizeof(char) * (cmp->clen * cmp->clen * cmp->plen)); /* square area * size of phenotype */
	for(int i = 0; i < (cmp->clen * cmp->clen); ++i)
	{
		for(int j = 0; j < cmp->slen; ++j)
		{
			#ifdef DEBUG
				fprintf(stdout, "(%d, %d): %c > %c; ([%d], [%d])\n", i, j, cmp->one[(i % cmp->clen) * cmp->slen + j], cmp->two[(i / cmp->clen) * cmp->slen + j], (i % cmp->clen) * cmp->slen + j, (i / cmp->clen) * cmp->slen + j);
			#endif

			if(cmp->one[(i % cmp->clen) * cmp->slen + j] < cmp->two[(i / cmp->clen) * cmp->slen + j])
			{
				smp->data[j * 2 + (i * cmp->plen)] = cmp->one[(i % cmp->clen) * cmp->slen + j];
				smp->data[j * 2 + (i * cmp->plen) + 1] = cmp->two[(i / cmp->clen) * cmp->slen + j];
			}
			else
			{
				smp->data[j * 2 + (i * cmp->plen)] = cmp->two[(i / cmp->clen) * cmp->slen + j];
				smp->data[j * 2 + (i * cmp->plen) + 1] = cmp->one[(i % cmp->clen) * cmp->slen + j];
			}
		}
	}

	#ifdef DEBUG
		fprintf(stdout, "DEBUG:\nsmp->data: %s\n", smp->data);
	#endif

	return smp;
}

int int_pow(int x, int y)
{
	int r = 1; /* You can never get 0 from a power */

	for(int i = 0; i < y; ++i)
		r = r * x;
	
	return r;
}

/*
Square example:
HhEe x hhee
      HE   He   hE   he
    +----+----+----+----+
 he |HhEe|Hhee|hhEe|hhee|
    +----+----+----+----+
 he |HhEe|Hhee|hhEe|hhee|
    +----+----+----+----+
 he |HhEe|Hhee|hhEe|hhee|
    +----+----+----+----+
 he |HhEe|Hhee|hhEe|hhee|
    +----+----+----+----+
*/