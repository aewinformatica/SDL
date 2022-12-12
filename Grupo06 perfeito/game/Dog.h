void aoDestruir_Dog(Tobj *o)
{
	Crie("Explosion2", o->x, o->y);
}

void Colisoes_Dog(Tobj *o)
{
	int other;
	for (other=0;other<nobj;other++)
	{
		//Colisao entre Dog e Chama
		if ((!strcmp(obj[other].nome,"FireS") || !strcmp(obj[other].nome,"FireN") || !strcmp(obj[other].nome,"FireL") || !strcmp(obj[other].nome,"FireO") || !strcmp(obj[other].nome,"FireNS") || !strcmp(obj[other].nome,"FireLO") || !strcmp(obj[other].nome,"FireM")) && ColisaoS2(o, &obj[other], 8))
		{
			Destrua(o);
			score+=200;
		}
	}

}

void aoCriar_Dog(Tobj *o)
{
	PuleAleatorio(o);
	redirect(o);
	o->speed = 4;
	o->z=1000;
}

void aoClock0_Dog(Tobj *o)
{
	Mova(o);
	if (NaGrade(o,32))
		redirect(o);
	else
		o->clock0 = 1;
}

