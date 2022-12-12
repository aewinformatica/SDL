void TrateColisao(Tobj *o)
{
	int other = NotPlaceFree(o, o->x, o->y);
	
	if (other)
	{
		other--;
		if (!strcmp(obj[other].nome, "WoodBox") || !strcmp(obj[other].nome, "Bomba"))
		{
			Destrua(&obj[other]);
			Destrua(o);
		}
		else
		if (!strcmp(obj[other].nome, "Wall"))
		{
			Destrua(o);
		}
		else
		if (!strcmp(obj[other].nome, "Fogo"))
		{
			Destrua(o);
		}
	}
	
	if (o->extra1<=1)
	{
		o->clock1 = TempoFogo;
	}
	else
	{
		o->clock0 = TempoCrescimento;
		o->extra1-=1;
	}
}

void CrieChama(Tobj *o)
{
	if (!strcmp(o->nome, "FireN") || !strcmp(o->nome, "FireS"))
		Crie("FireNS", o->x, o->y);
	else
		Crie("FireLO", o->x, o->y);
}

void aoCriar_Fire(Tobj *o)
{
	o->extra1 = FirePower;
	o->speed = 32;
	
	o->z = 6;
	
	if (!strcmp(o->nome, "FireN")) o->direction=1;
	if (!strcmp(o->nome, "FireS")) o->direction=3;
	if (!strcmp(o->nome, "FireL")) o->direction=0;
	if (!strcmp(o->nome, "FireO")) o->direction=2;
	
	TrateColisao(o);
}

void aoClock0_Fire(Tobj *o)
{
	CrieChama(o);
	Mova(o);
	TrateColisao(o);
}

void aoClock1_Fire(Tobj *o)
{
	Destrua(o);
}

void aoCriar_Fire2(Tobj *o)
{
	if (!strcmp(o->nome, "FireM"))
	{
		o->z = 80;
	}
	else
	{
		o->z = 7;
	}
	o->clock0 = TempoFogo;
}

void aoClock0_Fire2(Tobj *o)
{
	Destrua(o);
}

