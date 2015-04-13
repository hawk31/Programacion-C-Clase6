#include "gestor_tareas.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");
	return 0;
}


int main(void){

	struct tarea *t1, *t2, *t3;
	struct gestor_tareas *gt;
	char buffer[4000];

	t1 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE_TAREA, "Mixturas MCMC");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DESC_TAREA, "Ahora en C!");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 0);
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, "Jose");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_PRIORIDAD, 2);

	t2 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_NOMBRE_TAREA, "Machine Learning");
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_DESC_TAREA, "En Python");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_ID, 1);
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_USUARIO, "Pepe");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_PRIORIDAD, 0);

	
	gt = curso_gestor_tareas_alloc();

	curso_gestor_tareas_set_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, t1);
	curso_gestor_tareas_set_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, t2);


	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	int rc2;
	char *sql;
	char sql2[8000];
	int i;

	rc = sqlite3_open("tareas.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	} else {
		fprintf(stdout, "Opened database successfully\n");
	}

	sql = "CREATE TABLE TAREAS(" \
		"ID INT PRIMARY KEY NOT NULL," \
		"NOMBRE_TAREA CHAR(50)," \
		"DESC_TAREA CHAR(200), " \
		"USUARIO CHAR(50),"\
		"PRIORIDAD INT );";

	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	} else {
		fprintf(stdout, "Table created successfully\n");
	}

	int max = CURSO_GESTOR_TAREAS_ATTR_MAX;
	printf("Maximo: %d\n", max);

	for(i = 0; i <= max; i++){
		snprintf(sql2, sizeof(sql2), "INSERT INTO TAREAS (ID, NOMBRE_TAREA, DESC_TAREA, USUARIO, PRIORIDAD) "\
				"VALUES ( %d, '%s', '%s', '%s', %d);",
				curso_tarea_attr_get_u32(curso_gestor_tareas_attr_get_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, i), CURSO_TAREA_ATTR_ID),
				curso_tarea_attr_get_str(curso_gestor_tareas_attr_get_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, i), CURSO_TAREA_ATTR_NOMBRE_TAREA),
				curso_tarea_attr_get_str(curso_gestor_tareas_attr_get_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, i), CURSO_TAREA_ATTR_DESC_TAREA),
				curso_tarea_attr_get_str(curso_gestor_tareas_attr_get_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, i), CURSO_TAREA_ATTR_USUARIO),
				curso_tarea_attr_get_u32(curso_gestor_tareas_attr_get_tarea(gt, CURSO_GESTOR_TAREAS_ATTR_TAREA, i), CURSO_TAREA_ATTR_PRIORIDAD));

		printf("%s \n", sql2);
		rc2 = sqlite3_exec(db, sql2, callback, 0, &zErrMsg);
		if (rc2 != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
		fprintf(stdout, "Record created successfully\n");
		}
	}



	sqlite3_close(db);
	return 0;


}