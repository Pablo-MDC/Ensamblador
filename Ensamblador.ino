char data[26];
int number_of_bytes_received;

// Declaraciones de las funciones
void encender(int a, int b, int c, int d, int e, int f, int g);
void mostrarCaracter(char caracter);

void encender(int a, int b, int c, int d, int e, int f, int g) {
  digitalWrite(2, a);  // Segmento 'a'
  digitalWrite(3, b);  // Segmento 'b'
  digitalWrite(4, c);  // Segmento 'c'
  digitalWrite(5, d);  // Segmento 'd'
  digitalWrite(6, e);  // Segmento 'e'
  digitalWrite(7, f);  // Segmento 'f'
  digitalWrite(8, g);  // Segmento 'g'
}

void mostrarCaracter(char caracter) {
  switch (caracter) {
    case '0': encender(1, 1, 1, 0, 1, 1, 1); break; // '0'
    case '1': encender(0, 0, 1, 0, 0, 0, 1); break; // '1'
    case 'a': encender(1, 0, 1, 1, 1, 1, 1); break; // 'a' (acarreo)
    case 'b': encender(1, 1, 1, 1, 1, 0, 0); break; // 'b' (negativo)
    case 'c': encender(1, 1, 0, 0, 1, 1, 0); break; // 'c' (indefinido)
    case 'd': encender(1, 1, 1, 1, 0, 0, 1); break; // 'd' (infinito)
    case 'P': encender(1, 0, 0, 1, 1, 1, 1); break; // Error (P)
    default: encender(1, 0, 0, 1, 1, 1, 1); break;  // Error (P)
  }
}

void setup() { 
  Serial.begin(9600);
  Serial.println("En línea, esperando instrucciones...");
  
  for (int i = 2; i <= 8; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  while (Serial.available()) {
    number_of_bytes_received = Serial.readBytesUntil(13, data, 25);
    data[number_of_bytes_received] = 0;

    // Extraer el comando y los valores de entrada
    char comando[10];
    int valor1, valor2;
    sscanf(data, "%s %d %d", comando, &valor1, &valor2);

    if (strcmp(comando, "sum") == 0) {
      Serial.println("Operación de suma seleccionada");

      int resultado = valor1 + valor2;
      int acarreo = (valor1 & valor2);
      if (resultado == 0) {
        mostrarCaracter('0');
      } else if (acarreo > 0) {
        mostrarCaracter('a');
      } else {
        mostrarCaracter('1');
      }
    } 

    else if (strcmp(comando, "res") == 0) {
      Serial.println("Operación de resta seleccionada");

      int resultado = valor1 - valor2;
      if (resultado < 0) {
        mostrarCaracter('b');
      } else if (resultado == 0) {
        mostrarCaracter('0');
      } else {
        mostrarCaracter('1');
      }
    } 

    else if (strcmp(comando, "mul") == 0) {
      Serial.println("Operación de multiplicación seleccionada");

      int resultado = valor1 * valor2;
      if (resultado == 0) {
        mostrarCaracter('0');
      } else {
        mostrarCaracter('1');
      }
    }

    else if (strcmp(comando, "div") == 0) {
      Serial.println("Operación de división seleccionada");
      if (valor2 == 0 && valor1 == 0) {
        mostrarCaracter('c');  // Indefinido (0 / 0)
      } else if (valor2 == 0 && valor1 == 1) {
        mostrarCaracter('d');  // Infinito (1 / 0)
      } else if (valor2 == 1 && valor1 == 0) {
        mostrarCaracter('c');  // Indefinido (0 / 1)
      } else {
        int resultado = valor1 / valor2;
        mostrarCaracter(resultado == 0 ? '0' : '1');
      }
    }


    // Operaciones Lógicas
    else if (strcmp(comando, "and") == 0) {
      Serial.println("Operación AND seleccionada");
      int resultado = valor1 & valor2;
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "or") == 0) {
      Serial.println("Operación OR seleccionada");
      int resultado = valor1 | valor2;
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "xor") == 0) {
      Serial.println("Operación XOR seleccionada");
      int resultado = valor1 ^ valor2;
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "not") == 0) {
      Serial.println("Operación NOT seleccionada");
      int resultado = !valor1;  // Aplica NOT solo a valor1
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "xnor") == 0) {
      Serial.println("Operación XNOR seleccionada");
      int resultado = !(valor1 ^ valor2);
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "nand") == 0) {
      Serial.println("Operación NAND seleccionada");
      int resultado = !(valor1 & valor2);
      mostrarCaracter(resultado ? '1' : '0');
    } 
    else if (strcmp(comando, "nor") == 0) {
      Serial.println("Operación NOR seleccionada");
      int resultado = !(valor1 | valor2);
      mostrarCaracter(resultado ? '1' : '0');
    }

    // Comando desconocido
    else {
      Serial.println("Comando desconocido");
      mostrarCaracter('P');  // Muestra "P" para comando inválido
    }
  }
}