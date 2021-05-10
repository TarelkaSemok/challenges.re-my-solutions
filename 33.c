f_arm(){
	val1 = *x0;
	i = 0;
	val2 = *(x0+4);
	C1 = *x1;
	C2 = *(x1+4);
	C3 = *(x1+8);
	C4 = *(x1+12);
	
	do {
		w6 = C1 + (val2<<4);
		w1 = C2 + (val2>>5);
		w5 = 0x9e3779b9;
		i = i + w5;
		val1 = val1 + (0xc6ef3720 ^ w1 ^ (val2 + i));
		//i <> 0xc6ef3720;
		val2 = val2 + ((C4 + (val1 >> 5)) ^ (C3 + (val1 << 4)) ^ (val1 + i));
	} while (ne)
	*x0 = val1;
	*(x0+4) = val2;
	return;
}

No idea what the code does.
