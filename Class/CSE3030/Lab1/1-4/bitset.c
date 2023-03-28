
/*
 * addNumber(set, x): Add 'x' to the bitset represented in array 'set'
 *   Assume that 0 <= x <= 127 and 'set' is a pointer to 16-byte array
 */


void addNumber(unsigned char* set, int x) {
  	
	int i, temp;
	int set_num;
	int pos_in_set;
	int add = 1;
	int num_of_set[8];
	set_num = x / 8;
	pos_in_set = x % 8;

	temp = *(set+set_num);
	for(i=0;i<8;i++)
	{
		num_of_set[i] = temp % 2;
		temp = temp / 2;
	}

	if ( num_of_set[7 - pos_in_set] == 0)
	{
		for(i =0; i < 7 - pos_in_set; i++)
			add *= 2; 
		*(set+set_num) += add;
	}
	return;
}
