void sectoolstw(int a, int b){
	int c = 0x789;
	printf("%d\n", a+b+c);
}

int main(){
	int a = 0x123;
	int b = 0x456;
	sectoolstw(a,b);
	return 0;
}
