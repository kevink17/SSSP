#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
//Ein Element einer verketteten Liste die 2 Nachfolger haben kann
typedef struct element
{
	int16_t value;
	struct element* left;
	struct element* right;
} Element;
/*Erzeugt neues Element wobei die Nachfolger auf NULL zeigen braucht
  man nachher wenn man die Abfrage bei grid_print macht*/
Element* new_Element()
{
	Element* new = malloc(sizeof(Element));
	new->right = NULL;
	new->left = NULL;
	return new;
}

Element* grid_init(uint16_t num_columns, uint16_t num_rows)
{
	Element* head_element = new_Element();
	Element* current_row = head_element;
	Element* current;
	//Hier lasse ich die Struktur einer Matrize entstehen
	for(uint16_t j = 0; j < num_rows; j++)
	{
		current = current_row;
		for(uint16_t i = 0;i < num_columns;i++)
		{
			/*current.value geht nicht weil current ein pointer auf ein 
			Element ist, dann muss dan so schreiben mit nem Pfeil ->*/
			current->value = i+j*num_rows+20; //irgendein Zahlenwert damit man beim printen was sieht
			current->right = new_Element();
			current = current->right;
					
		}
		current_row->left = new_Element();
		current_row = current_row->left;	
	}
	return head_element;
}
void grid_print(Element* head)
{
	Element* current_row = head;
	Element* current;
	while(current_row->left != NULL)
	{
		printf("| ");
		current = current_row;
		while(current->right != NULL)
		{
			printf("%i ",current->value);
			current = current->right;
		}
		printf("|\n");
		current_row = current_row->left;
	}
}
void grid_print_dot(Element* head)
{
    printf("digraph {\n");
    Element* current_row = head;
    Element* current;
    while(current_row->left != NULL)
    {
        current = current_row;
        while(current->right->right != NULL)
        {
            if(current->right != NULL)
            {
                printf("M%p -> M%p;\n",current,current->right);
            }
            if(current->left != NULL)
            {
                if(current->left->left != NULL)
                {
                    printf("M%p -> M%p;\n",current,current->left);
                }
            }
            current = current->right;
        }
        current_row = current_row->left;
    }
    printf("}\n");
}
int main()
{	
	Element* grid = grid_init(2,2);
	grid_print_dot(grid);
	return 0;
}
