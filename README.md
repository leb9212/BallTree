# BallTree
BallTree implementation in C

To compile:
make

To run:
./balltree_knn \[input param jason file\] \[test data file\] \[path to output>

For example:
./balltree_knn datasets/knn_params_6_pts_2_dims.json datasets/test_data_6_pts_2_dims.json datasets/my_knn_results_6_pts_2_dims.json

Make sure that input and test files have the same format at the ones provided in datasets folder.

Also make sure that the training data and test data have the same dimensions.

Once you run, it will print out the time taken for
1. reading input file
2. reading test file
3. building ball tree
4. querying ball tree
5. writing output file

Some benchmarks:

Building 10k points of 512 dimensions with leaf size 30 took about 1.23s.
Querying the 3 nearest neighbors of 20 points of 512 dimensions took about 0.58s.

To compare the results from scikit-learn and this program, compare files prefix starting with knn_results (scikit-learn) with my_knn_results (this program)
