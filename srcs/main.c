/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elee <elee@student.42.us.org>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:45:08 by elee              #+#    #+#             */
/*   Updated: 2017/06/28 19:00:51 by elee             ###   ########.fr       */
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
		free(file_contents);
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

t_data	*read_test_data(char *filename)
{
	FILE		*fp;
	struct stat	filestatus;
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
	file_size = filestatus.st_size + 8;
	file_contents = (char*)malloc(sizeof(char) * file_size);
	memcpy(file_contents, "{\"X\": ", 6);
	if (file_contents == NULL)
	{
		fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
		exit(-1);
	}

	fp = fopen(filename, "rt");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s\n", filename);
		free(file_contents);
		exit(-1);
	}
	if (fread(file_contents + 6, file_size - 8, 1, fp) != 1 ) {
		fprintf(stderr, "Unable to read content of %s\n", filename);
		fclose(fp);
		free(file_contents);
		exit(-1);
	}
	fclose(fp);
	file_contents[file_size - 2] = '}';
	file_contents[file_size - 1] = '\0';

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

t_knn	btree_query_wrapper(t_btree *tree, t_data *input_data, t_data *test_data)
{
	return (btree_query(tree, test_data->data, test_data->n_samples, test_data->n_features, input_data->n_neighbors)); 
}

void	write_output(t_knn knn, char *filename)
{

}

void	free_data(t_data *input_data, t_data *test_data)
{
	free_2d_double(input_data->data, input_data->n_samples);
	free(input_data);
	free_2d_double(test_data->data, test_data->n_samples);
	free(test_data);
}

int		main(int argc, char **argv)
{
	t_data	*input_data;
	t_data	*test_data;
	t_btree	*tree;
	t_knn	knn;
	clock_t	start, end;

	if (argc != 4)
	{
		fprintf(stderr, "%s <input_json_file> <test_data_file> <path_to_output>\n", argv[0]);
		exit(-1);
	}

	start = clock();
	input_data = read_input(argv[1]);
	end = clock();
	printf("Reading input param took %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	test_data = read_test_data(argv[2]);
	end = clock();
	printf("Reading test data took %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	tree = btree_init_wrapper(input_data);
	end = clock();
	printf("Building ball tree of %d points of %d dimension with leaf size %d took %lf seconds\n",
		input_data->n_samples, input_data->n_features, input_data->leaf_size,
	(double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	knn = btree_query_wrapper(tree, input_data, test_data);
	end = clock();
	printf("Querying the %d nearest_neighbors of %d points of %d dimension took %lf seconds\n",
		input_data->n_neighbors, test_data->n_samples, test_data->n_features, (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	write_output(knn, argv[3]);
	end = clock();
	printf("Writing result data took %lf second\n", (double)(end - start) / CLOCKS_PER_SEC);

	//free stuff
	free_tree(tree);
	free_knn(knn, test_data->n_samples);
	free_data(input_data, test_data);
	return (0);
}
