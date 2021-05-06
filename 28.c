// Linux call-convention: rdi, rsi, rdx, rcx, r8, r9...

f1(*elem1, *elem2){
	return (*elem1 >= *elem2)?1:-1;
}





// rdi - param1, rsi - nmemb
main(){
	// r12 - var1
	var1 = param1;
	// rbp - size
	size = nmemb*4;
	// rbx - var4
	var4 = nmemb;
	pnt1 = malloc(size);
	
	pnt1 = memcpy(pnt1, param1, size);
	
	void qsort(pnt1, nmemb, size_t size,
                  int (*f1)(const void *, const void *));
	
	if (nmemb - odd){
		return pnt1[nmemb/2];
	}
	else {
		return (pnt1[nmemb/2-1]+pnt1[nmemb/2])/2;
	}
}
