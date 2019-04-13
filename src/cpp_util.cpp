

int CPrimeCount( int x, int y )
{
	int PrimeCount = 0;
	int isPrime = 0;
	int VRange = 0;
	int i = 0;
	int j = 0;

	// printf( "\n (x=%d, y=%d)", x, y);
	if (x < 2)
		x = 2;

	++y;
	for (i = x; i < y; i++)
	{
		isPrime = 1;

		VRange = i / 2; //This Validation Range is good enough
		++VRange;
		for (j = 2; j < VRange; j++)
		{
			// Check whether it is  divisible by any number other than 1
			if (!(i % j))
			{
				isPrime = 0;
				break;
			}
		}

		if (isPrime)
		{
			//printf(" [%d] ", i);
			++PrimeCount;
		}
	}

	return(PrimeCount);
}
