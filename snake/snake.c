#include <time.h>
#include<stdio.h> 
#include<stdlib.h> 
#include "support.h"
#include<stdbool.h>
//Spielfeld, welches x Einheiten breit ist und y Einheiten hoch
typedef struct field{
	int x;
	int y;
}Field;
//Teil einer Schlange, sie besitzt eine x und y Koordinate und eine Richtung in die sie sich als nächstes bewegt
//Außerdem besitzt jedes Teil einer Schlange einen Vorgänger und einen Nachkommen
typedef struct snake{
	char direction;
	int x;
	int y;
	struct snake* tail;
	struct snake* head;
}Snake;
//Essen welches eine x und eine y Koordinate besitzt
typedef struct food{
	int x;
	int y;
}Food;
//Erzeugt ein neuen Food struct mit random x und y Werten abhängig vom Spielfeld
Food* new_food(Field test)
{
	Food* new = malloc(sizeof(Food));
	new->x = rand() % test.x;
	new->y = rand() % test.y;
	return new;	
}
//Erzeugt neue Schalnge mit x und x Koordinate und einer Richtung
//Vorgänger und Nachkomme sind bei default auf NULL
Snake* new_snake(int x, int y, char direction)
{
	Snake* new = malloc(sizeof(Snake));
	new->x = x;
	new->y = y;
	new->direction = direction;
	new->tail = NULL;
	new->head = NULL;
	return new;
}
//Verbindet zwei Schlangenteile
void  append_snake(Snake* snake_head,Snake* snake_tail)
{
	snake_head->tail = snake_tail;
	snake_tail->head = snake_head;
}
//Erzeugt ein neues Feld
Field new_field(int x,int y)
{
	Field new;
	new.x = x;
	new.y = y;
	return new;
}
//Printed das gegebene Feld mit der Schalnge und einer Frucht
void print(Field field, Snake* snake_head, Food* fruit)
{
	Snake* current;
	bool printed = false;
	//Erstellt viele neue Zeilen damit man nur immer das neueste Feld sieht
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	//printed obere Wand
	for(int i = 0; i < field.x+2; i++)
	{
		printf("=");
	}
	printf("\n");
	for(int i = 0; i < field.y;i++)
	{
		printf("|");
		for(int j = 0; j < field.x;j++)
		{
			printed = false;
			current = snake_head;
			//Teste ob ein Teil einer Schlange geprintet werden muss oder ein leeres Feld
			//auf den Koordinaten j und i
			while(current != NULL)
			{	
				//Geh mit der Schleife einmal jedes Teil der Schlange durch
				if(current->x == j & current->y == i)
				{
					printf("H");
					printed = true;
				}
				
				current = current->tail;
			}
			//Teste ob eine Frucht geprinted werden muss
			if(fruit->x == j & fruit->y == i & printed == false)
			{
					printf("+");
					printed = true;
			}
			//Falls weder Schalnge noch Frucht da ist printe ein leeres Feld
			if(!printed)
			{
				printf(" ");
			}
			
			
		}
		printf("|\n");

	}
	//printed untere Wand
	for(int i = 0; i < field.x+2; i++)
	{
		printf("=");
	}
	printf("\n");
}
//Bewegt die gegebene Schlange indem es seine x und y Koordinaten verändert anhand der directions
//Außerdem werden directions aktualisiert von den einzelnen Schlangenteilen bei Kurven
void move(Snake* snake_head)
{	
	Snake* current = snake_head;
	//Verschiebe jeden Snaketeil einmal
	while(current != NULL)
	{
		switch(current->direction)
		{
			case 'w':
				current->y -= 1;
				break;
			case 'a':
				current->x -= 1;
				break;
			case 's':
				current->y += 1;
				break;
			case 'd':
				current->x += 1;
				break;
		}
		current = current->tail;
	}
	current = snake_head;
	//Gehe zum Ende der Schlange
	while(current->tail != NULL)
	{
		current = current->tail;
	}
	//Passe die neue direction jedes Schlangenteils an 
	//anhand seines Vorgängers außer die des Kopfes der Schlange
	while(current != snake_head)
	{
		current->direction = current->head->direction;
		current = current->head;
	}
}
//Testet ob der Kopf der Schlange eine Kollision mit 
//einer Wand hat oder mit sich selbst
bool collision(Snake* snake_head,Field test)
{
	Snake* current = snake_head;
	//Testet ob der Kopf außerhalb des Bereiches ist
	if((snake_head->x < 0) || (snake_head->y < 0) || (snake_head->x > test.x) || (snake_head->y > test.y))
	{
		return true;
	}
	//Testet ob der Kopf dieselbe Koordinate hat wie ein Teil der Schlange
	while(current->tail != NULL)
	{
		current = current->tail;
		if((current->x == snake_head->x) && (current->y == snake_head->y))
		{
			return true;
		}
	}
	return false;
}
int main()
{ 	
	//Inititalisierung
	srand(time(NULL));
	support_init();
	char key;
	Field test = new_field(40,10);
	Snake* current;
	Snake* snake_head = new_snake(20,5,'w');
	Snake* snake1 = new_snake(20,6,'w');
	Snake* snake2 = new_snake(20,7,'w');
	Snake* snake3 = new_snake(21,7,'a');
	Snake* snake4 = new_snake(22,7,'a');
	append_snake(snake_head,snake1);
	append_snake(snake1,snake2);
	append_snake(snake2,snake3);
	append_snake(snake3,snake4);
	Food* fruit = new_food(test);
	//mainloop
	while(1)
	{	
		print(test,snake_head,fruit);
		move(snake_head);
		//Teste ob die Schlange auf einem Food Feld ist
		if(snake_head->x == fruit->x & snake_head->y == fruit->y)
		{
			//setzt neues food
			fruit = new_food(test);
			current = snake_head;
			//Gehe zum Schwanz der Schlange
			while(current->tail != NULL)
			{
				current = current->tail;
			}
			//Hänge ein neues Schlangenteil an
			switch(current->direction)
			{
				case 'w':
					append_snake(current,new_snake(current->x,current->y+1,current->direction));
					break;
				case 'a':
					append_snake(current,new_snake(current->x+1,current->y,current->direction));
					break;
				case 's':
					append_snake(current,new_snake(current->x,current->y-1,current->direction));
					break;
				case 'd':
					append_snake(current,new_snake(current->x-1,current->y,current->direction));
					break;
			}
		}
		//Lies Eingabe vom Benutzer
		key = support_readkey(1000);
		//Ändere Richtung entsprechend der Eingabe
		switch(key)
		{
			case 'w':
				if(snake_head->direction != 's')
				{
					snake_head->direction = key;
				}
				break;
			case 'a':
				if(snake_head->direction != 'd')
				{
					snake_head->direction = key;
				}
				break;
			case 's':
				if(snake_head->direction != 'w')
				{
					snake_head->direction = key;
				}
				break;
			case 'd':
				if(snake_head->direction != 'a')
				{
					snake_head->direction = key;
				}
				break;
		}
		//Falls Kollision auftritt beende die Endlosschleife
		if(collision(snake_head,test))
		{
			break;
		}
		
	}
	printf("You lost\n");
	return 0;
}