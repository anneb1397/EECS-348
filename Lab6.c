void part_one_classifier(float **data_train,float **data_test)
{
	// PUT YOUR CODE HERE
	// Access the training data using "data_train[i][j]"
	// Training data contains 3 cols per row: X in 
	// index 0, Y in index 1 and Class in index 2
	// Access the test data using "data_test[i][j]"
	// Test data contains 2 cols per row: X in 
	// index 0 and Y in index 1, and a blank space in index 2 
	// to be filled with class
	// The class value could be a 0 or a 1

	float weight[2] = { 0,0};
	float rate = 0.01;
	int iterations = 0;
	float bias;

	while (iterations < 1000)
	{
		int error = 0;
		for (int i = 0; i < TRAINING_SIZE; i++) {
			int y = (weight[0] * data_train[i][0] + weight[1] * data_train[i][1] + bias) >= 0 ? 1 : 0;
			int dy = data_train[i][2] - y;
			for (int j = 0; j < 2; j++) {
				weight[j] += rate * dy * data_train[i][j];
			}
			bias += rate * dy;
			error += dy;
		}

		iterations++;
	}

	for (int i = 0; i < TEST_SIZE; i++) {
		data_test[i][2] = (weight[0] * data_test[i][0] + weight[1] * data_test[i][1] + bias >= 0) ? 1 : 0;
	}
}

void part_two_classifier(float **data_train,float **data_test)
{
	// PUT YOUR CODE HERE
	// Access the training data using "data_train[i][j]"
	// Training data contains 3 cols per row: X in 
	// index 0, Y in index 1 and Class in index 2
	// Access the test data using "data_test[i][j]"
	// Test data contains 2 cols per row: X in 
	// index 0 and Y in index 1, and a blank space in index 2 
	// to be filled with class
	// The class value could be a 0 or a 8

	int iterations = 0;
	float y[9];
	float weight[9][3];
	float rate = 0.01;

	float argMax = -999999;
	int argIndex;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 3; j++)
			weight[i][j] = 0;

	while (iterations < 1000) {
		argMax = -999999;
		argIndex = 0;
		for (int i = 0; i < TRAINING_SIZE; i++) {
			for (int j = 0; j < 9; j++)
			{
				y[j] = weight[j][0] * data_train[i][0] + weight[j][1] * data_train[i][1] + weight[j][2];
				if (y[j] > argMax)
				{
					argMax = y[j];
					argIndex = j;
				}
			}
			int expected = int(data_train[i][2]);

			if (argIndex != expected)
			{
				for (int k = 0; k < 2; k++) {
					weight[argIndex][k] -= rate*data_train[i][k];
					weight[expected][k] += rate*data_train[i][k];
				}
				weight[argIndex][2] -= rate*weight[argIndex][2];
				weight[expected][2] += rate*weight[expected][2];
			}
		}
		iterations++;
	}

	for (int i = 0; i < TEST_SIZE; i++) {
		argMax = -999999;
		argIndex = 0;
		for (int j = 0; j < 9; j++)
		{
			y[j] = weight[j][0] * data_test[i][0] + weight[j][1] * data_test[i][1] + weight[j][2];
			if (y[j] > argMax)
			{
				argMax = y[j];
				argIndex = j;
			}
		}
		data_test[i][2] = argIndex;
	}
}
