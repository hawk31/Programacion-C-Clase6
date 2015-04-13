#include "tarea.h"
#include <string.h>


/* Para devolver un puntero en lugar de la estructura */

struct tarea *curso_tarea_alloc(void){
	return (struct tarea *)malloc(sizeof(struct tarea));
}

/* Liberando campos y luego estructura*/

void curso_tarea_free(struct tarea *t){

	if(t->flags & (1 << CURSO_TAREA_ATTR_NOMBRE_TAREA))
		xfree(t->nombre_tarea);

	if(t->flags & (1 << CURSO_TAREA_ATTR_DESC_TAREA))
		xfree(t->desc_tarea);

	/*if(t->flags & (1 << CURSO_TAREA_ATTR_ID))
		xfree(t->id);*/

	if(t->flags & (1 << CURSO_TAREA_ATTR_USUARIO))
		xfree(t->usuario);

	xfree(t);

}

/* Comprobar si un campo esta activo */

bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr)
{
	return t->flags & (1 << attr);
}

/* Desasignar un campo */

void curso_tarea_attr_unset(struct tarea *t, uint16_t attr)
{
	/* Comprobar si campo activo */
	if(!(t->flags & (1 << attr)))
		return;

	switch(attr) {

	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if(t->nombre_tarea){
			xfree(t->nombre_tarea);
			t->nombre_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if(t->desc_tarea){
			xfree(t->desc_tarea);
			t->desc_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_USUARIO:
		if(t->usuario){
			xfree(t->usuario);
			t->usuario = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_ID:
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		break;
	}

	t->flags &= ~(1 << attr);
}

/* Asignamos un campo */

void curso_tarea_set_data(struct tarea *t, uint16_t attr, const void *data,
				uint32_t data_len)
{
	/*Comprueba numero maximo de atributos*/
	if(attr > CURSO_TAREA_ATTR_MAX)
		return;

	switch(attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if(t->nombre_tarea)
			xfree(t->nombre_tarea);
		t->nombre_tarea = strdup(data);
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if(t->desc_tarea)
			xfree(t->desc_tarea);
		t->desc_tarea = strdup(data);
		break;
	case CURSO_TAREA_ATTR_ID:
		t->id = *((uint32_t *)data);
		break;
	case CURSO_TAREA_ATTR_USUARIO:
		if(t->usuario)
			xfree(t->usuario);
		t->usuario = strdup(data);
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		t->prioridad = *((uint32_t *)data);
		break;	
	}

	t->flags |= (1 << attr);
}

/* Hacemos mas facil la insercion de integers */

void curso_tarea_attr_set_u32(struct tarea *t, uint16_t attr, uint32_t data)
{
	curso_tarea_set_data(t, attr, &data, sizeof(uint32_t));
}

/* Igual con strings */

void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr, const char *data)
{
	curso_tarea_set_data(t, attr, data, 0);
}	

/* Retorno de datos */

const void *curso_tarea_attr_get_data(struct tarea *t, uint16_t attr)
{
	if(!(t->flags & (1 << attr)))
		return NULL;

	switch(attr){
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		return t->nombre_tarea;
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		return t->desc_tarea;
		break;
	case CURSO_TAREA_ATTR_ID:
		return &t->id;
		break;
	case CURSO_TAREA_ATTR_USUARIO:
		return t->usuario;
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		return &t->prioridad;
		break;
	}
	return NULL;
}

/* Retorno de integers */

uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr)
{
	const void *ret = curso_tarea_attr_get_data(t, attr);
	return ret == NULL ? 0: *((uint32_t *)ret);
}

/* Retorno de strings */

const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr)
{
	return curso_tarea_attr_get_data(t,attr);
}

/* Plantilla */

int curso_tarea_snprintf(char *buffer, size_t size, struct tarea *t)
{
	return snprintf(buffer, size, "La tarea numero %d esta enviada por %s. Se llama %s y la descripcion es %s", t->id, t->usuario,t->nombre_tarea,t->desc_tarea);
}