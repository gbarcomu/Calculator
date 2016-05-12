entero columna;
entero fila;
columna = 30*10 + 100;
fila = columna + 100;
real valor_umbral;
posicion p_inicial, p_s_humo;
p_inicial = <0,0>;
p_s_humo = <50*2,180>;

Sensor A temperatura <100,100>;
Sensor H humo p_s_humo;
Actuador L_1 luz <250,100>;
Actuador L_2 luz <250,200>;
Actuador B alarma <100,320>;

%%
A 25.5;
H 0.3;

%%
valor_umbral = 5.0;

si A > valor_umbral [
	activar L_1;
	
	repite 3 [
		activar B 2;
		pausa 5;
	];
	activar  L_2;
];

si H >= 1 [
	desactivar L_1;
	]
sino [
	pausa 1;
	desactivar L_2;
];