#include "tarea.h"

enum{
	CURSO_GESTOR_TAREAS_ATTR_TAREA,
	CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS,
	__CURSO_GESTOR_TAREAS_ATTR_MAX
};

#define CURSO_GESTOR_TAREAS_ATTR_MAX (__CURSO_GESTOR_TAREAS_ATTR_MAX - 1)

struct gestor_tareas;
struct gestor_tareas *curso_gestor_tareas_alloc(void);
void curso_gestor_tareas_free(struct gestor_tareas *);

void curso_gestor_tareas_attr_unset_tarea(struct gestor_tareas *gt,
	uint32_t pos);
static void curso_gestor_tareas_set_data(struct gestor_tareas *gt,
	uint16_t attr, const void *data);
void curso_gestor_tareas_set_tarea(struct gestor_tareas *gt,
	uint16_t attr, struct tarea *data);
const void *curso_gestor_tareas_attr_get_data(struct gestor_tareas *gt,
	uint16_t attr, uint32_t pos);
struct tarea *curso_gestor_tareas_attr_get_tarea(struct gestor_tareas *gt,
					         uint16_t attr, uint32_t pos);
int curso_gestor_tareas_snprintf(char *buffer, size_t size,
	struct gestor_tareas *gt);
