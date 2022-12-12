void SortItem(Tobj *o)
{
	int a = rand()%4;
	
	if (!a)
	{
		a = rand()%4;
		switch(a)
		{
			case 0:
				Crie("ItemBomba", o->x, o->y);
				break;
			case 1:
				Crie("ItemFire", o->x, o->y);
				break;
			case 2:
				Crie("ItemPatins", o->x, o->y);
				break;
			case 3:
				a = rand()%2;
				if (!a)
					Crie("ItemLife", o->x, o->y);
				break;
			case 4:
				Crie("ItemControl", o->x, o->y);
				break;
			
		}
	}
}

void aoCriar_WoodBox(Tobj *o)
{
	o->solido=1;
	PuleAleatorio(o);
}

void aoDestruir_WoodBox(Tobj *o)
{
	SortItem(o);
	Crie("Explosion",o->x,o->y);
	Crie("Fogo",o->x,o->y);
	score+=10;
}

