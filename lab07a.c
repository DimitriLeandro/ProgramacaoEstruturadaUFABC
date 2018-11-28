/* Essa função recebe a unidade de peso lida na variável <tipo> e um recebe um
 * valor na variável correspondente a tal unidade.
 * Ela converte esse valor para as outras duas unidades, escrevendo nas duas variáveis
 * correspondentes. */
void converte_peso(int tipo, double *kg, double *lb, double *oz){
	/* DEFININDO QUANTO EM KILOS VALE CADA TIPO */
	double ounce = 0.028;
	double libra = 0.3732417216;

	switch(tipo){
		case 0:
			/* KILOGRAMA PARA OUTROS */
			*lb = *kg/libra;
			*oz = *kg/ounce;
			break;
		case 1:
			/* LIBRA PARA OUTROS */
			*kg = *lb * libra;
			*oz = *kg/ounce;
			break;
		case 2:
			/* OUNCE PARA OUTROS */
			*kg = *oz * ounce;
			*lb = *kg/libra;
			break;
	}
}



/* Essa função recebe a unidade de comprimento lida na variável <tipo> e um recebe um
 * valor na variável correspondente a tal unidade.
 * Ela converte esse valor para as outras quatro unidades, escrevendo nas quatro variáveis
 * correspondentes. */
void converte_comprimento(int tipo, double *km, double *mi, double *ft, double *lea){
	/* DEFININDO QUANTO EM KILOMETROS VALE CADA TIPO */
	double milha = 1.609344;
	double pes = 0.0003048;
	double legua = 4.828;

	switch(tipo){
		case 0:
			/* KM PARA OUTROS */
			*mi = *km / milha;
			*ft = *km / pes;
			*lea = *km / legua;
			break;
		case 1:
			/* MILHA PARA OUTROS */
			*km = *mi * milha;
			*ft = *km / pes;
			*lea = *km / legua;
			break;
		case 2:
			/* PES PARA OUTROS */
			*km = *ft * pes;
			*mi = *km / milha;
			*lea = *km / legua;
			break;
		case 3:
			/* LEGUAS PARA OUTROS */
			*km = *lea * legua;
			*mi = *km / milha;
			*ft = *km / pes;
			break;
	}
}



/* Essa função recebe a unidade de temperatura lida na variável <tipo> e um recebe um
 * valor na variável correspondente a tal unidade.
 * Ela converte esse valor para as outras duas unidades, escrevendo nas duas variáveis
 * correspondentes. */
void converte_temperatura(int tipo, double *c, double *f, double *k){
	switch(tipo){
		case 0:
			/* CELCIUS PARA OUTROS */
			*k = *c + 273.15;
			*f = *c * (9.0/5.0) + 32;
			break;
		case 1:
			/*  FAHREINHEIT PARA OUTROS */
			*c = (*f - 32) / (9.0/5.0);
			*k = *c + 273.15;
			break;
		case 2:
			/* KELVIN PARA OUTROS */
			*c = *k - 273.15;
			*f = ((*k * 9.0) / 5.0) - 459.67;
			break;
	}
}



/* Essa função recebe a unidade de volume lida na variável <tipo> e um recebe um
 * valor na variável correspondente a tal unidade.
 * Ela converte esse valor para as outras quatro unidades, escrevendo nas quatro variáveis
 * correspondentes. */
void converte_volume(int tipo, double *m3, double *l, double *gal, double *bl, double *floz){
	/* DEFININDO QUANTO EM M3 VALE CADA TIPO */
	double litro = 0.001;
	double galao = 0.00454609;
	double barril = 0.16365924;
	double oncas = 0.00003;

	switch(tipo){
		case 0:
			/* M3 PARA OUTROS */
			*l = *m3 / litro;
			*gal = *m3 / galao;
			*bl = *m3 / barril;
			*floz = *m3 / oncas;			
			break;
		case 1:
			/* LITRO PARA OUTROS */
			*m3 = *l * litro;
			*gal = *m3 / galao;
			*bl = *m3 / barril;
			*floz = *m3 / oncas;
			break;
		case 2:
			/* GALAO PARA OUTROS */
			*m3 = *gal * galao;
			*l = *m3 / litro;
			*bl = *m3 / barril;
			*floz = *m3 / oncas;
			break;
		case 3:
			/* BARRIL PARA OUTROS */
			*m3 = *bl * barril;	
			*l = *m3 / litro;
			*gal = *m3 / galao;
			*floz = *m3 / oncas;
			break;
		case 4:
			/* ONCAS PARA OUTROS */
			*m3 = *floz * oncas;
			*l = *m3 / litro;
			*gal = *m3 / galao;
			*bl = *m3 / barril;
			break;
	}
}



/* Essa função recebe a unidade de velocidade lida na variável <tipo> e um recebe um
 * valor na variável correspondente a tal unidade.
 * Ela converte esse valor para as outras duas unidades, escrevendo nas duas variáveis
 * correspondentes. */
void converte_velocidade(int tipo, double *kmh, double *ms, double *mph){
	/* DEFININDO QUANTO EM m/s VALE CADA TIPO */
	double milesPerHour = 0.44704;
	double kilometersHour = 0.27;

	switch(tipo){
		case 0:
			/* km/h PARA OUTROS */
			*ms = *kmh * kilometersHour;
			*mph = *ms / milesPerHour;
			break;
		case 1:
			/* m/s PARA OUTROS */
			*kmh = *ms / kilometersHour;
			*mph = *ms / milesPerHour;
			break;
		case 2:
			/* mph PARA OUTROS */
			*ms = *mph * milesPerHour;
			*kmh = *ms / kilometersHour;
			break;
	}
}
