int constt = 0;

while (constt == 0) {
	srand(time(NULL));
	int row = rand() % 3 + 1;
	int col = rand() % 3 + 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == row-1 && j == col-1 && matrix && matrix[i][j] != 'X' && matrix[i][j] != 'O') {
				matrix[i][j] = 'O';
				constt = 1;
				break;
			}
			break;
		}
		break;
	}
}
cout << "Computer choose the number of the field: " << constt << endl;