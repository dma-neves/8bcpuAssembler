# a = 3
lod $3 RA

# b = 5
lod $5 RB

# res = 0
lod $0 RC

# i = 0
lod $0 RD

loop_start:

	# res += a
	add RC RA
	lod ACR RC


	# if i < b goto loop_start b-i < 0
	sub RB RD
	jmpn loop_start

psh RC
pop RA
hlt