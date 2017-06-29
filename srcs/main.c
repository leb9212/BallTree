/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:45:08 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 18:02:10 by elee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ball.h"
#include "json.h"

static void process_value(t_data *data, json_value* value);

static void process_object(t_data *data, json_value* value)
{
	int length;
	int x;
	int y;
	int z;
	char *name;
	json_value *temp;

	(void)temp;
	(void)z;
	(void)y;
	if (value == NULL)
		return;
	length = value->u.object.length;
	for (x = 0; x < length; x++)
	{
		name = strdup(value->u.object.values[x].name);
		if (!strcmp(name, "n_neighbors"))
			data->n_neighbors = value->u.object.values[x].value->u.integer;
		else if (!strcmp(name, "leaf_size"))
			data->leaf_size = value->u.object.values[x].value->u.integer;
		else if (!strcmp(name, "_tree"))
		{
			/*
			temp = value->u.object.values[x].value->u.object.values[1].value;
			int y_len = temp->u.array.length;
			data->data = (double**)malloc(sizeof(double*) * y_len);
			for (y = 0; y < y_len; y++)
			{
				int z_len = temp->u.array.values[y].value->u.array.length;
				data->data[y] = (double*)malloc(sizeof(double) * z_len);
				for (z = 0; z < z_len; z++)
					data->data[y][z] = temp->u.array.values[y].value->u.array.values[z].value->u.dbl;
			}
			*/
		}
		// process_value(data, value->u.object.values[x].value);
		free(name);
	}
}

static void process_array(t_data *data, json_value* value)
{
	int length;
	int x;

	if (value == NULL)
		return;
	length = value->u.array.length;
	// printf("array length is %d\n", length);
	for (x = 0; x < length; x++)
		process_value(data, value->u.array.values[x]);
}

static void process_value(t_data *data, json_value* value)
{
	int j;
	(void)j;
	if (value == NULL)
		return;
	switch (value->type)
	{
		case json_none:
			break;
		case json_object:
			process_object(data, value);
			break;
		case json_array:
			process_array(data, value);
			break;
		case json_integer:
			// printf("int: %10" PRId64 "\n", value->u.integer);
			break;
		case json_double:
			// printf("double: %f\n", value->u.dbl);
			break;
		case json_string:
			// printf("string: %s\n", value->u.string.ptr);
			break;
		case json_boolean:
			break;
		case json_null:
			break;
	}
}

t_data	*read_input(char *filename)
{
	FILE 		*fp;
	struct stat filestatus;
	int			file_size;
	char		*file_contents;
	json_char	*json;
	json_value	*value;
	t_data		*data;

	if (stat(filename, &filestatus) != 0)
	{
		fprintf(stderr, "File %s not found\n", filename);
		exit(-1);
	}
	file_size = filestatus.st_size;
	file_contents = (char*)malloc(sizeof(char) * filestatus.st_size);
	if (file_contents == NULL)
	{
		fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
		exit(-1);
	}

	fp = fopen(filename, "rt");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s\n", filename);
		free(file_contents)k;
		exit(-1);
	}
	if (fread(file_contents, file_size, 1, fp) != 1 ) {
		fprintf(stderr, "Unable to read content of %s\n", filename);
		fclose(fp);
		free(file_contents);
		exit(-1);
	}
	fclose(fp);

	json = (json_char*)file_contents;
	value = json_parse(json, file_size);
	if (value == NULL)
	{
		fprintf(stderr, "Unable to parse data\n");
		free(file_contents);
		exit(-11);
	}
	data = (t_data*)malloc(sizeof(t_data));
	process_value(data, value);
	json_value_free(value);
	free(file_contents);
	return (data);
}

t_btree	*btree_init_wrapper(t_data *input_data)
{
	return (btree_init(input_data->data, input_data->n_samples, input_data->n_features, input_data->leaf_size));
}

double	**read_test_data(t_data *data, char *filename)
{
}

void	write_output(t_knn knn)
{
}

int		main(int argc, char **argv)
{
	t_data	*input_data;
	t_btree	*tree;
	double	**test_data;

	if (argc != 4)
	{
		fprintf(stderr, "%s <input_json_file> <test_data_file> <path_to_output>\n", argv[0]);
		exit(-1);
	}
	input_data = read_input(argv[1]);
	test_data = read_test_data(input_data, argv[2]);
	tree = btree_init_wrapper(input_data);
}
