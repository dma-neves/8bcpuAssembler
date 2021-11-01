################### main.c ###################

int avg(int* arr, int len) {
	

	int sum = 0;

	for(int i = 0; i < len; i++)
		sum += arr[i];

	int s = sum;
	int div = 0;

	do 
	{
		s -= len;
		div++;
	}
	while(s > 0);

	//return sum/len;
	return div;
}

int main() {

	int len = 3;
	
	int arr[len];
	arr[0] = 5;
	arr[1] = 2;
	arr[2] = 9;

	int res = avg(arr, len);
}

################### main.s ###################

jmp main

avg:

	// arr
	pop RB
	// len
	pop RC
	// sum = 0
	lod $0 RD
	// i = 0
	lod $0 RE

	sum_loop_start:

		// if i >= len goto loop_end
		sub RC RE
		jmpn sum_loop_end
		jmpz sum_loop_end

		// sum += arr[i]
		add RB RE
		lod ACR ADR
		lod [ADR] RF
		add RD RF
		lod ACR RD

		// i++
		inc RE
		lod ACR RE
		jmp sum_loop_start


	sum_loop_end:

	// div = 0
	psh $0
	// s = sum
	psh RD

	div_loop_start:

		// s -= len
		lsr $1 RF
		sub RF RC
		lod ACR RF
		srs RF $1

		// if s <= 0 goto div_loop_end
		lsr $1 RF
		dec RF
		jmpn div_loop_end

		// else div++ and goto div_loop_start
		lsr $2 RF
		inc RF
		lod ACR RF
		srs RF $2
		jmp div_loop_start

	div_loop_end:

	// return div
	pop
	pop RA
	pop RB
	lod RB ADR
	jmp ADR

main:

	// len = 3
	psh $3
	// arr[0] = 5
	psh $5
	// arr[1] = 2
	psh $2
	// arr[2] = 9
	psh $9


	// psh return line
	psh avg_ret
	// psh len
	lsr $5 RA
	psh RA
	// psh arr
	SSP $5
	psh ACR
	// call avg(arr,len)
	jmp avg
	avg_ret:

	hlt