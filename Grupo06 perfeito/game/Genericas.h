void redirect(Tobj *o)
{
	char v[4], pic[100];
	int n = 0, a;
	
	if (!Colidindo(o,o->x,o->y-32) && !ColObjPos(o,"Bomba",o->x,o->y-32))
	{
		v[n] = 1;
		n++;
	}
	if (!Colidindo(o,o->x,o->y+32) && !ColObjPos(o,"Bomba",o->x,o->y+32))
	{
		v[n] = 3;
		n++;
	}
	if (!Colidindo(o,o->x-32,o->y) && !ColObjPos(o,"Bomba",o->x-32,o->y))
	{
		v[n] = 2;
		n++;
	}
	if (!Colidindo(o,o->x+32,o->y) && !ColObjPos(o,"Bomba",o->x+32,o->y))
	{
		v[n] = 0;
		n++;
	}
	
	strcpy(pic,"i");
	strcpy(pic+1,o->nome);
	
	if (n==0)
	{
		o->clock0 = 60;
		o->direction = 4;
		a = rand()%4;
		
		switch(a)
		{
			case 0:
				strcpy(pic+strlen(pic),"Right");
				break;
			case 1:
				strcpy(pic+strlen(pic),"Up");
				break;
			case 2:
				strcpy(pic+strlen(pic),"Left");
				break;
			case 3:
				strcpy(pic+strlen(pic),"Down");
				break;
		}
	}
	else
	{
		do
		{
			a = rand()%n;
		}
		while((n>1) && ((v[a]+2)%4==o->direction));
		
		o->direction = v[a];
		o->clock0 = 1;
		
		switch((int)o->direction)
		{
			case 0:
				strcpy(pic+strlen(pic),"MoveRight");
				break;
			case 1:
				strcpy(pic+strlen(pic),"MoveUp");
				break;
			case 2:
				strcpy(pic+strlen(pic),"MoveLeft");
				break;
			case 3:
				strcpy(pic+strlen(pic),"MoveDown");
				break;
		}
	}
	
	DefPic(o, pic);
}

void Mova(Tobj *o)
{
	switch((int) o->direction)
	{
		case 0:
			o->x+=o->speed;
			break;
		case 1:
			o->y-=o->speed;
			break;
		case 2:
			o->x-=o->speed;
			break;
		case 3:
			o->y+=o->speed;
			break;
	}
}
