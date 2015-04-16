#include "gestor_tareas.h"
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
	json_t *root, *value, *tarea_1, *tarea_2;
	json_error_t err;
	const char *key;
	void *iter;
	struct tarea *t1, *t2;
	struct gestor_tareas *gt;
	char *string;
	int i;
	int entero;

	t1 = curso_tarea_alloc();
	t2 = curso_tarea_alloc();
	gt = curso_gestor_tareas_alloc();

	char buffer[4000];




	root = json_load_file("tareas.json", 0, &err);
	if (root == NULL) {
		perror("Error: ");
		fprintf(stderr, "Jansson error: %s %d %d\n", err.text,
			err.column, err.line);
		return EXIT_FAILURE;
	}

	tarea_1 = json_object_get(root, "tarea_1");
	if(tarea_1 == NULL){
		return EXIT_FAILURE;
	}

	tarea_2 = json_object_get(root, "tarea_2");
	if(tarea_2 == NULL){
		return EXIT_FAILURE;
	}

	i = 1;

	iter = json_object_iter(tarea_1);
	while(iter){
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		switch(i){
			case 1:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE_TAREA, string);
				break;
			case 2:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DESC_TAREA, string);
				break;
			case 3:
				entero = json_integer_value(value);
				curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, entero);
				break;
			case 4:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, string);
				break;
			default:
				entero = json_string_value(value);
				curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_PRIORIDAD, entero);
				break;

		}
		iter = json_object_iter_next(tarea_1, iter);
		i++;
	}


	curso_gestor_tareas_set_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, t1);

	i = 1;

	iter = json_object_iter(tarea_2);
	while(iter){
		key = json_object_iter_key(iter);
		value = json_object_iter_value(iter);
		switch(i){
			case 1:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_NOMBRE_TAREA, string);
				break;
			case 2:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_DESC_TAREA, string);
				break;
			case 3:
				entero =  json_integer_value(value);
				curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_ID, entero);
				break;
			case 4:
				string = json_string_value(value);
				curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_USUARIO, string);
				break;
			default:
				entero = json_string_value(value);
				curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_PRIORIDAD, entero);
				break;

		}
		iter = json_object_iter_next(tarea_1, iter);
		i++;
	}

	curso_gestor_tareas_set_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, t2);

	curso_gestor_tareas_snprintf(buffer, sizeof(buffer), gt);
	printf("%s\n", buffer);




}