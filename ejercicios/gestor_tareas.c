#include "gestor_tareas.h"
#include <string.h>

struct gestor_tareas {
	struct list_head 	tareas;
	uint32_t 	num_tareas;

	uint32_t flags;
};

struct gestor_tareas *curso_gestor_tareas_alloc(void)
{
	struct gestor_tareas *gt;

	gt = malloc(sizeof(struct gestor_tareas));
	if (gt == NULL)
		return NULL;

	INIT_LIST_HEAD(&gt->tareas);
	gt ->flags |= (1 << CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS);

	return gt;
}

void curso_gestor_tareas_free(struct gestor_tareas *gt)
{
	int i;
	struct tarea *t, *tmp;

	list_for_each_entry_safe(t, tmp, &gt->tareas, head){
		list_del(&t->head);
		curso_tarea_free(t);
	}

	xfree(gt);
}

void curso_gestor_tareas_attr_unset_tarea(struct gestor_tareas *gt,
	uint32_t pos)
	{
		int i=0;
		struct tarea *t, *tmp;

		if(pos <0 || pos > gt->num_tareas)
			return;
		list_for_each_entry_safe(t, tmp, &gt->tareas, head){
			if(i == pos){
				list_del(&t->head);
				curso_tarea_free(t);
				break;
			}
			i++;
		}
		gt->num_tareas--;
	}

static void curso_gestor_tareas_set_data(struct gestor_tareas *gt,
	uint16_t attr, const void *data)
{
	struct tarea *t;
	if(attr > CURSO_GESTOR_TAREAS_ATTR_MAX)
		return;
	switch(attr){
	case CURSO_GESTOR_TAREAS_ATTR_TAREA:
		if(gt->num_tareas > 10){
			printf("No queda espacio para tareas\n");
			break;
		}

		t = (struct tarea *)data;
		list_add(&t->head, &gt->tareas);
		gt->num_tareas++;
		break;
	}

	gt -> flags |= (1 << attr);
}

void curso_gestor_tareas_set_tarea(struct gestor_tareas *gt,
	uint16_t attr, struct tarea *data)
{
	curso_gestor_tareas_set_data(gt, attr, data);
}

/* Pueden faltar algunas cosas de strings y u32 */

const void *curso_gestor_tareas_attr_get_data(struct gestor_tareas *gt,
	uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct tarea *t;

	if(!(gt->flags & (1 << attr)))
		return NULL;

	switch(attr){
		case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
			return &gt->num_tareas;
		case CURSO_GESTOR_TAREAS_ATTR_TAREA:
			list_for_each_entry(t, &gt->tareas, head){
				if(i == pos)
					break;
				i++;
			}
			return t;
	}
	return NULL;
}

struct tarea *curso_gestor_tareas_attr_get_tarea(struct gestor_tareas *gt,
					         uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_tareas_attr_get_data(gt, attr,
								 pos);
}

/* Faltan algunos get str y get u32, pero creo que no hacen falta */

int curso_gestor_tareas_snprintf(char *buffer, size_t size,
	struct gestor_tareas *gt)
{
	int ret = 0;
	struct tarea *t;


	list_for_each_entry(t, &gt->tareas, head){
		ret += curso_tarea_snprintf(buffer + ret, size - ret, t);
		ret += snprintf(buffer + ret, size - ret, "\n");
	}
	return ret;

	
}