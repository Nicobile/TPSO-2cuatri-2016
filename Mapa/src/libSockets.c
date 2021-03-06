/*
 * libSockets.c
 *
 *  Created on: 7/9/2016
 *      Author: utnso
 */

#include <dirent.h>
#include "libSockets.h"
#define HEADER_PAQUETE (sizeof(int)*3)

extern t_log* logs;
extern t_list* disponibles;
extern t_list* listaContenedora;
extern char* configMapa;
metaDataPokeNest *datos; // Variable global
extern metaDataComun* datosMapa;
extern metaDataComun* datosMapa2;



/*void leerConfiguracion2() {
	t_config* archivoConfiguracion = config_create(configMapa); //Crea struct de configuracion
	if (archivoConfiguracion == NULL) {

		log_error(logs,"Error al leer metadata Mapa");
		perror("Error leer config");
	} else {
		int cantidadKeys = config_keys_amount(archivoConfiguracion);
		if (cantidadKeys < 7) {
			log_error(logs,"Error al leer metadata Mapa"); // sale, 0 es false
			perror("Error leer config");
		} else {

			datosMapa2->tiempoChequeoDeadlock = config_get_int_value(archivoConfiguracion, "TiempoChequeoDeadlock");
			//log_info(logs,"TiempoChequeo %d\n",(*datos)->tiempoChequeoDeadlock);
			log_info(logs,"Tiempo de chequeo vale: %d",datosMapa2->tiempoChequeoDeadlock);

			datosMapa2->batalla = config_get_int_value(archivoConfiguracion,"Batalla");
			//log_info(logs,"batalla %d\n",(*datos)->batalla);
			log_info(logs,"Batalla activada? %d",datosMapa2->batalla);

			char* algoritmo = string_new();
			string_append(&algoritmo,config_get_string_value(archivoConfiguracion, "algoritmo"));
			datosMapa2->algoritmo = algoritmo;
			//log_info(logs,"algoritmo  %s\n",(*datos)->algoritmo);
			log_info(logs,"Algoritmo: %s",datosMapa2->algoritmo);

			datosMapa2->quantum = config_get_int_value(archivoConfiguracion,"quantum");
			//log_info(logs,"quantum  %d\n",(*datos)->quantum);
			log_info(logs,"Quantum: %d",datosMapa2->quantum);

			datosMapa2->retardoQ = config_get_int_value(archivoConfiguracion,"retardo");
			log_info(logs,"Retardo: %d",datosMapa2->retardoQ);


			config_destroy(archivoConfiguracion);
		}
	}
}*/


void leerConfiguracion() {
	t_config* archivoConfiguracion = config_create(configMapa); //Crea struct de configuracion
	if (archivoConfiguracion == NULL) {

		log_error(logs,"Error al leer metadata Mapa");
		perror("Error leer config");
	} else {
		int cantidadKeys = config_keys_amount(archivoConfiguracion);
		if (cantidadKeys < 7) {
			log_error(logs,"Error al leer metadata Mapa"); // sale, 0 es false
			perror("Error leer config");
		} else {

			datosMapa->tiempoChequeoDeadlock = config_get_int_value(
					archivoConfiguracion, "TiempoChequeoDeadlock");
			log_info(logs,"TiempoChequeo %d\n",datosMapa->tiempoChequeoDeadlock);

			datosMapa->batalla = config_get_int_value(archivoConfiguracion,
					"Batalla");
			log_info(logs,"batalla %d\n",datosMapa->batalla);

			char* algoritmo = string_new();
			string_append(&algoritmo,
					config_get_string_value(archivoConfiguracion, "algoritmo"));
			datosMapa->algoritmo = algoritmo;
			log_info(logs,"algoritmo  %s\n",datosMapa->algoritmo);

			datosMapa->quantum = config_get_int_value(archivoConfiguracion,
					"quantum");
			log_info(logs,"quantum  %d\n",datosMapa->quantum);

			datosMapa->retardoQ = config_get_int_value(archivoConfiguracion,
					"retardo");
			log_info(logs,"retardo  %d\n",datosMapa->retardoQ);

			char* ip = string_new();
			string_append(&ip,
					config_get_string_value(archivoConfiguracion, "IP"));
			datosMapa->ip = ip;
			log_info(logs,"ip  %s\n",datosMapa->ip);

			datosMapa->puerto = config_get_int_value(archivoConfiguracion,
					"Puerto");
			log_info(logs,"puerto %d\n",datosMapa->puerto);

			config_destroy(archivoConfiguracion);
		}
	}
}

int leerConfigPokenest(char *name, t_list *pokenests) {


	{
		DIR *d;
		struct dirent *dir;
		d = opendir(name);
		if (!d) {
			return 0;
		}


		while ((dir = readdir(d)) != NULL ) {
			tabla* dispo;
			dispo = malloc(sizeof(tabla)); //MATADO
			datos = malloc(sizeof(metaDataPokeNest)); //MATADO

			log_info(logs,"esto lo printea\n");

			if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {

				char* ruta = string_new();
				string_append(&ruta,string_from_format("%s/%s/metadata", name,dir->d_name));
				t_config* archivoConfigPokenest = config_create(ruta);
				free(ruta);

				//log_info(logs,"el d_name es %s\n", dir->d_name);
				//log_info(logs,"el d_type es %c\n",dir->d_type);

				if (archivoConfigPokenest == NULL) {
					return 0;
				} else {
					int cantidadKeys = config_keys_amount(
							archivoConfigPokenest);
					if (cantidadKeys < 3) {
						return 0;
					} else {
						char* tipo = string_new();
						string_append(&tipo,
								config_get_string_value(archivoConfigPokenest,
										"Tipo"));
						datos->tipoPokemon = tipo;


						char* posicion = string_new();
						string_append(&posicion,
								config_get_string_value(archivoConfigPokenest,
										"Posicion"));
						datos->posicion = posicion;
						//log_info(logs,"%s\n",datos->posicion);

						char* simbolo = string_new();
						string_append(&simbolo,
								config_get_string_value(archivoConfigPokenest,
										"Identificador"));
						datos->caracterPokeNest = simbolo;
						dispo->pokenest=simbolo[0];



						{
							int file_count = 0;
							DIR * dirp;
							struct dirent * entry;

							dirp = opendir(
									string_from_format("%s/%s", name,
											dir->d_name));
							while ((entry = readdir(dirp)) != NULL) {
								if ((strcmp(entry->d_name,"metadata")!=0) && (strcmp(entry->d_name,".")!=0) && (strcmp(entry->d_name,"..")!=0)) {

									file_count++;
								}
							}
							closedir(dirp);
							datos->cantPokemons = (file_count);
							dispo->valor = (file_count);
						}

						list_add(pokenests, (void*) datos);
						log_info(logs,"Disponible: %c%d",dispo->pokenest,dispo->valor);
						list_add(disponibles, dispo);

						config_destroy(archivoConfigPokenest);
						//free(datos);
					}
				}

			}

		}

		int ka;
					tabla *a;

					   for(ka=0; ka<list_size(pokenests); ka++){
					    	    a = (tabla*) list_get(disponibles,ka);
					    	    //log_info(logs,"%c\n",a->pokenest);
					    	    //log_info(logs,"%d\n",a->valor);
					    }

		closedir(d);

	}

	return 1;
}

int leerPokemons(char *name, t_list *pokemons) {
	{
		DIR *d;
		struct dirent *dir;
		d = opendir(name);
		if (!d) {
			return 0;
		}
		pokimons* po;
		while ((dir = readdir(d)) != NULL ) {

			if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
				bloq* strubloq;
				strubloq = malloc(sizeof(bloq));
                po=malloc(sizeof(pokimons));
                po->listaPokemons=list_create();
                char simbol = dir->d_name[0];
                po->pokinest=simbol;
                log_info(logs,"Simbolo %c \n", po->pokinest);
                strubloq->colabloq=queue_create();
                sem_init(&(strubloq->sembloq),0,0);
                sem_init(&(strubloq->sem2),0,0);
                strubloq->pokenest=dir->d_name[0];
                log_info(logs,"Carga de info en pokenest %c",dir->d_name[0]);

				//log_info(logs,"%s\n", dir->d_name);
						{
							DIR * dirp;
							struct dirent * entry;

							dirp = opendir(string_from_format("%s/%s", name,dir->d_name));

							while ((entry = readdir(dirp)) != NULL) {
								metaDataPokemon* poke;
								if ((strcmp(entry->d_name, "metadata") != 0) && (strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)) {

									log_info(logs,"esto es %s\n",entry->d_name);
									poke = malloc(sizeof(metaDataPokemon));
								    char* ruta = string_new();
								    string_append(&ruta,string_from_format("%s/%s/%s", name,dir->d_name,entry->d_name));
									t_config* archivoConfigPokenest = config_create(ruta);
									free(ruta);

									poke->nivel = config_get_int_value(archivoConfigPokenest,"Nivel");
									log_info(logs,"nivel: %d\n",poke->nivel);

									char* speci = string_new();
								    string_append(&speci, dir->d_name);
									poke ->especie = speci;
									log_info(logs,"especie: %s\n", poke->especie);

									char* arc = string_new();
									string_append(&arc, entry->d_name);
									poke ->nombreArch = arc;
									log_info(logs,"nombreArchivo: %s\n", poke->nombreArch);

									poke->estaOcupado = 0;

									list_add(po->listaPokemons,poke);

									sem_post(&(strubloq->sembloq));
									log_info(logs,"Se postea semaforo de %c\n",strubloq->pokenest);
									int vale;
									sem_getvalue(&(strubloq->sembloq),&vale);
									log_info(logs,"Valor del mismo: %d\n",vale);

									config_destroy(archivoConfigPokenest);
								}

							}

							closedir(dirp);
						}
						list_add(listaContenedora,strubloq);
						list_add(pokemons,po);
			}
		}
		//free(po);
		closedir(d);
	}
	return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

int setup_listen(char* IP, char* Port) {
	struct addrinfo * serverInfo = cargarInfoSocket(IP, Port);
	if (serverInfo == NULL)
		return -1;
	int socketEscucha;
	socketEscucha = socket(serverInfo->ai_family, serverInfo->ai_socktype,
			serverInfo->ai_protocol);
	int resultadoBind;
	resultadoBind = bind(socketEscucha, serverInfo->ai_addr,
			serverInfo->ai_addrlen);
	const int optVal = 1;
	const socklen_t optLen = sizeof(optVal);

	int rtn = setsockopt(socketEscucha, SOL_SOCKET, SO_REUSEADDR, (void*) &optVal, optLen);
	if (resultadoBind == -1) {
		printf("Error en el Bind \n");
		exit(-1);
	}
	freeaddrinfo(serverInfo);
	return socketEscucha;
}

int setup_listen_con_log(char* IP, char* Port, t_log * logger) {
	struct addrinfo* serverInfo = cargarInfoSocket(IP, Port);
	if (serverInfo == NULL)
		return -1;
	int socketEscucha;
	socketEscucha = socket(serverInfo->ai_family, serverInfo->ai_socktype,
			serverInfo->ai_protocol);
	log_info(logger,
			string_from_format("Escuchando conexiones en el socket %d",
					socketEscucha));
	bind(socketEscucha, serverInfo->ai_addr, serverInfo->ai_addrlen);
	freeaddrinfo(serverInfo);
	return socketEscucha;
}

struct addrinfo* cargarInfoSocket(char *IP, char* Port) {
	struct addrinfo hints;
	struct addrinfo * serverInfo;
	int error;
	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (!strcmp(IP, "localhost")) {
		hints.ai_flags = AI_PASSIVE;
		error = getaddrinfo(NULL, Port, &hints, &serverInfo);
	} else
		error = getaddrinfo(IP, Port, &hints, &serverInfo);
	if (error != 0) {
		log_info(logs,"Problema con el getaddrinfo()\n");
		return NULL;
	}
	return serverInfo;
}

int conectarCliente(char *IP, char* Port) {
	struct addrinfo* serverInfo = cargarInfoSocket(IP, Port);
	if (serverInfo == NULL) {
		return -1;
	}
	int serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype,
			serverInfo->ai_protocol);
	if (serverSocket == -1) {
		log_info(logs,"Error en la creacion del socket\n");
		return -1;
	}
	if (connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen)
			== -1) {
		log_info(logs,"No se pudo conectar con el socket servidor\n");
		close(serverSocket);
		exit(-1);
	}
	freeaddrinfo(serverInfo);
	return serverSocket;
}

int conectarCliente_con_log(char *IP, char* Port, t_log * logger) {
	struct addrinfo* serverInfo = cargarInfoSocket(IP, Port);
	if (serverInfo == NULL) {
		return -1;
	}
	int serverSocket = socket(serverInfo->ai_family, serverInfo->ai_socktype,
			serverInfo->ai_protocol);
	if (serverSocket == -1) {
		log_error(logger,
				string_from_format("Error en la creación del socket"));
		return -1;
	}
	if (connect(serverSocket, serverInfo->ai_addr, serverInfo->ai_addrlen)
			== -1) {
		log_error(logger,
				string_from_format(
						"No se pudo conectar con el socket servidor\n"));
		close(serverSocket);
		return -1;
	}
	freeaddrinfo(serverInfo);
	return serverSocket;
}

int esperarConexionEntrante(int socketEscucha, int BACKLOG, t_log * logger) {

	listen(socketEscucha, BACKLOG);
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int socketCliente = accept(socketEscucha, (struct sockaddr *) &addr,
			&addrlen);
	log_info(logger,
			string_from_format("Se asigno el socket %d para el cliente",
					socketCliente));
	return socketCliente;

}

int conectarServidor(char* IP, char* Port, int backlog) {
	struct addrinfo* serverInfo = cargarInfoSocket(IP, Port);
	if (serverInfo == NULL)
		return -1;
	int socketEscucha;
	socketEscucha = socket(serverInfo->ai_family, serverInfo->ai_socktype,
			serverInfo->ai_protocol);
	if (bind(socketEscucha, serverInfo->ai_addr, serverInfo->ai_addrlen)
			== -1) {
		log_info(logs,"Error en el Bind \n");
	}
	freeaddrinfo(serverInfo);
	if (listen(socketEscucha, backlog) == -1) {
		log_info(logs,"error en la escucha de un cliente");
		return -5;
	}

	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);

	int socketCliente = accept(socketEscucha, (struct sockaddr *) &addr,
			&addrlen);
	if (socketCliente == -1) {
		log_info(logs,"Error en la conexion, en la funcion accept\n");
		return -2;
	}
	return socketCliente;
}

/*void enviarTresCosasSerializadas(int cosaUno, int CosaDos, char *cosaTres){
    int tamanioCosaUno = sizeof(cosaUno);
    int tamanioCosaDos = sizeof(int);
    int tamanioCosaTres = sizeof(char) * strlen(cosaTres);

    void *miBuffer = malloc((3 * sizeof(int)) + tamanioCosaUno + tamanioCosaDos + tamanioCosaTres);

    memcpy(miBuffer, &tamanioCosaUno, sizeof(int));
    memcpy(miBuffer + sizeof(int), &tamanioCosaDos, sizeof(int));
    memcpy(miBuffer + (2 * sizeof(int)), &tamanioCosaTres, sizeof(int));

    memcpy(miBuffer + (3 * sizeof(int)), &cosaUno, tamanioCosaUno);
    memcpy(miBuffer + (3 * sizeof(int)) + tamanioCosaUno, &CosaDos, tamanioCosaDos);
    memcpy(miBuffer + (3 * sizeof(int)) + tamanioCosaUno + tamanioCosaDos, &cosaTres, tamanioCosaTres);
    send(pokedexServidor, miBuffer, tamanioCosaUno + tamanioCosaDos + tamanioCosaTres, 0);

    free(miBuffer);
}

void recibirTresCosasSerializadas(){
    int tamanioCosaUno, tamanioCosaDos, tamanioCosaTres;
    int cosaUno, CosaDos;
    char *cosaTres;

    recv(pokedexServidor, &tamanioCosaUno, sizeof(int), MSG_WAITALL);
    recv(pokedexServidor, &tamanioCosaDos, sizeof(int), MSG_WAITALL);
    recv(pokedexServidor, &tamanioCosaTres, sizeof(int), MSG_WAITALL);

    void *bufferCosaUno = malloc(tamanioCosaUno);
    void *bufferCosaDos = malloc(tamanioCosaDos);
    void *bufferCosaTres = malloc(tamanioCosaTres);

    recv(pokedexServidor, bufferCosaUno, tamanioCosaUno,MSG_WAITALL);
    recv(pokedexServidor, bufferCosaDos, tamanioCosaDos,MSG_WAITALL);
    recv(pokedexServidor, bufferCosaTres, tamanioCosaTres,MSG_WAITALL);

    cosaUno = (int) bufferCosaUno;
    CosaDos = (int) bufferCosaDos;
    cosaTres = (char *) bufferCosaTres;


}*/

