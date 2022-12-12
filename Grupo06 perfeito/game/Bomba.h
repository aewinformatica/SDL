void Movimentar_Bomba(Tobj *o)
{
	if (o->solido==0 && !NotPlaceFree(o,o->x,o->y))
		o->solido = 1;
}

void Colisoes_Bomba(Tobj *o)
{
	int other;
	for (other=0;other<nobj;other++)
	{
		//Colisao entre Bomba e Bomba
		if (!strcmp(obj[other].nome,"Bomba") && o != &obj[other] && ColisaoS2(o, &obj[other], 6))
		{
			Vanish(o);
			Bombs--;
		}
		
		//Colisao entre Bomba e Chama
		if ((!strcmp(obj[other].nome,"FireS") || !strcmp(obj[other].nome,"FireN") || !strcmp(obj[other].nome,"FireL") || !strcmp(obj[other].nome,"FireO") || !strcmp(obj[other].nome,"FireNS") || !strcmp(obj[other].nome,"FireLO") || !strcmp(obj[other].nome,"FireM")) && ColisaoS2(o, &obj[other], 8))
		{
			Destrua(o);
		}	
	}
}

void aoCriar_Bomba(Tobj *o)
{
	o->clock0 = 120;
	Bombs++;
}

void aoDestruir_Bomba(Tobj *o)
{
	Crie("FireM", o->x, o->y);
	
	Crie("FireN", o->x, o->y-32);
	Crie("FireS", o->x, o->y+32);
	Crie("FireL", o->x+32, o->y);
	Crie("FireO", o->x-32, o->y);
	
	Bombs--;
	
	PlaySom("sExplosion");
}

void aoTerminarAnim_Bomba(Tobj *o)
{
	PlaySom("sClock");
}

void aoClock0_Bomba(Tobj *o)
{
	Destrua(o);
}

