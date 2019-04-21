#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct entry{
	int16_t value;
	struct entry* left;
	struct entry* right;
} Entry;

Entry* grid_init(uint16_t num_columns, uint16_t num_rows)
{
	Entry* head = malloc(sizeof(Entry)); //der Kram muss da sein wenn du neuen Entry machst
	Entry* current = head;
	//Hier lasse ich die Struktur einer Matrize entstehen 
	//wie ganz unten auf dem Zettel abgebildet
	for(uint16_t j = 0; j < num_rows; j++)
	{
		for(uint16_t i = 0;i < num_columns;i++)
		{
			current->left = malloc(sizeof(Entry));
			current = current->left;		
		}
		
	}
	return head;
}
int main()
{	
	Entry* head = grid_init(4,1);
	
	return 0;
}
