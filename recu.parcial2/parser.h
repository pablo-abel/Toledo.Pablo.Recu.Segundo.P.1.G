#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

int parser_PostFromText(FILE* pFile, LinkedList* pArrayListPosteo);
int parser_PostFromBinary(FILE* pFile , LinkedList* pArrayListPosteo);

#endif // PARSER_H_INCLUDED
