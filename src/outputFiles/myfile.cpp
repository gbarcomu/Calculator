#include "entorno_shol.h"

int main(){
inicio();

marca_sensor(100,100,Temperatura,"A");
marca_sensor(100,180,Humo,"H");
desactivar_actuador(250,100,Luz,"L_1");
desactivar_actuador(250,200,Luz,"L_2");
desactivar_actuador(100,320,Alarma,"B");
valor_sensor(100,100,Temperatura,25.5);
valor_sensor(100,180,Humo,0.3);
MostrarMensaje ("SIMULACION", 50,100);
MostrarMensaje ("1", 0,0);
activar_actuador(250,100,Luz,"L_1");
activar_actuador(100,320,Alarma,"B");
pausa (2);
desactivar_actuador(100,320,Alarma,"B");
pausa (5);
activar_actuador(100,320,Alarma,"B");
pausa (2);
desactivar_actuador(100,320,Alarma,"B");
pausa (5);
activar_actuador(100,320,Alarma,"B");
pausa (2);
desactivar_actuador(100,320,Alarma,"B");
pausa (5);
activar_actuador(250,200,Luz,"L_2");
pausa (1);
desactivar_actuador(250,200,Luz,"L_2");

fin()
return 0;
}
