#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char dec['z'][9];
char enc['z'][9];

void translate_init( void ) {

	memset(dec, '\0', sizeof(dec));
	memset(enc, '\0', sizeof(enc));

	snprintf(dec['0'], 9, "efgefgef");
	snprintf(dec['1'], 9, "fghfghfg");
	snprintf(dec['2'], 9, "ghighigh");
	snprintf(dec['3'], 9, "hijhijhi");
	snprintf(dec['4'], 9, "ijaijaij");
	snprintf(dec['5'], 9, "jabjabja");
	snprintf(dec['6'], 9, "abcabcab");
	snprintf(dec['7'], 9, "bcdbcdbc");
	snprintf(dec['8'], 9, "cdecdecd");
	snprintf(dec['9'], 9, "defdefde");

	snprintf(dec['a'], 9, "34534534");
	snprintf(dec['b'], 9, "23423423");
	snprintf(dec['c'], 9, "12312312");
	snprintf(dec['d'], 9, "01201201");
	snprintf(dec['e'], 9, "90190190");
	snprintf(dec['f'], 9, "89089089");
	snprintf(dec['g'], 9, "78978978");
	snprintf(dec['h'], 9, "67867867");
	snprintf(dec['i'], 9, "56756756");
	snprintf(dec['j'], 9, "45645645");
	snprintf(dec['k'], 9, "vutsrqpo");
	snprintf(dec['l'], 9, "wvutsrqp");
	snprintf(dec['m'], 9, "xwvutsrq");
	snprintf(dec['n'], 9, "yxwvutsr");
	snprintf(dec['o'], 9, "zyxwvuts");
	snprintf(dec['p'], 9, "kzyxwvut");
	snprintf(dec['q'], 9, "lkzyxwvu");
	snprintf(dec['r'], 9, "mlkzyxwv");
	snprintf(dec['s'], 9, "nmlkzyxw");
	snprintf(dec['t'], 9, "onmlkzyx");
	snprintf(dec['u'], 9, "ponmikzy");
	snprintf(dec['v'], 9, "qponmlkz");
	snprintf(dec['w'], 9, "rqponmlk");
	snprintf(dec['x'], 9, "srqponml");
	snprintf(dec['y'], 9, "tsrqponm");
	snprintf(dec['z'], 9, "utsrqpon");

	snprintf(dec['A'], 9, "FGHIJKLM");
	snprintf(dec['B'], 9, "GHIJKLMN");
	snprintf(dec['C'], 9, "HIJKLMNO");
	snprintf(dec['D'], 9, "IJKLMNOP");
	snprintf(dec['E'], 9, "JKLMNOPQ");
	snprintf(dec['F'], 9, "KLMNOPQR");
	snprintf(dec['G'], 9, "LMNOPQRS");
	snprintf(dec['H'], 9, "MNOPQRST");
	snprintf(dec['I'], 9, "NOPQRSTU");
	snprintf(dec['J'], 9, "OPQRSTUV");
	snprintf(dec['K'], 9, "PQRSTUVW");
	snprintf(dec['L'], 9, "QRSTUVWX");
	snprintf(dec['M'], 9, "RSTUVWXY");
	snprintf(dec['N'], 9, "STUVWXYZ");
	snprintf(dec['O'], 9, "TUVWXYZA");
	snprintf(dec['P'], 9, "UVWXYZAB");
	snprintf(dec['Q'], 9, "VWXYZABC");
	snprintf(dec['R'], 9, "WXYZABCD");
	snprintf(dec['S'], 9, "XYZABCDE");
	snprintf(dec['T'], 9, "YZABCDEF");
	snprintf(dec['U'], 9, "ZABCDEFG");
	snprintf(dec['V'], 9, "ABCDEFGH");
	snprintf(dec['W'], 9, "BCDEFGHI");
	snprintf(dec['X'], 9, "CDEFGHIJ");
	snprintf(dec['Y'], 9, "DEFGHIJK");
	snprintf(dec['Z'], 9, "EFGHIJKL");


	// Generate the encoding matrix
	//
	for (int c = 0; c < 8; c++) {
		for (char z = '0'; z <= 'z'; z++) {
			char o = dec[(ssize_t)z][(ssize_t)c];
			enc[(ssize_t)o][(ssize_t)c] = z;
		}
	}

}


int decode( char *dest, char *s, ssize_t l ) {
	ssize_t i = 0;
	int r = 0; // rotation
	while ( i < l && *s ) {
		if (isalnum(*s)) {
			dest[i] = dec[(ssize_t)*s][r % 8];
			r++;
		} else {
			dest[i] = *s;
			r = 0;
		}
		i++;
		s++;
	}
	dest[l] = 0;
	return 0;
}

int encode( char *dest, char *s, ssize_t l ) {
	ssize_t i = 0;
	int r = 0;
	while ( i < l && *s ) {
		if (isalnum(*s)) {
			dest[i] = enc[(ssize_t)*s][r % 8];
			r++;
		} else {
			dest[i] = *s;
			r = 0;
		}
		i++;
		s++;
	}
	dest[l] = 0;
	return 0;
}

int main( int argc, char **argv ) {

	translate_init();

	// Dump the decoding matrix
	//
	fprintf(stdout,"// Decoding Matrix\n");
	fprintf(stdout,"//\n");
	fprintf(stdout,"char dec['z'][9] = {\n");
	for (int i = 0; i <= 'z'; i++) {
		fprintf(stdout,"\t { ");
		for (int j = 0; j < 8; j++) {
			if (isprint(dec[i][j])) {
				fprintf(stdout, "'%c'%s", dec[i][j], j==7?"":", ");
			} else {
				fprintf(stdout, "%d%s", dec[i][j], j==7?"":", ");
			}
		}
		if (isprint(i)) fprintf(stdout," }, // '%c'\n", i);
		else fprintf(stdout," }, // 0x%X\n", i);
	}
	fprintf(stdout,"}; // decoding matrix\n\n");


	fprintf(stdout,"// Encoding Matrix\n");
	fprintf(stdout,"//\n");
	fprintf(stdout,"char enc['z'][9] = {\n");
	for (int i = 0; i <= 'z'; i++) {
		fprintf(stdout,"\t{ ");
		for (int c = 0; c < 8; c++) {
			char o = enc[i][c];
			if (o) {
				fprintf(stdout, "'%c'%s", o, c==7?"":", ");
			} else {
				fprintf(stdout, "%d%s", o, c==7?"":", ");
			}
		}
		if (isprint(i)) fprintf(stdout," }, // '%c'\n", i);
		else fprintf(stdout," }, // 0x%X\n", i);
	}
	fprintf(stdout,"}; //encoding matrix\n\n");

	if (argc == 2) {
		char dbuf[100];
		char ebuf[100];
		fprintf(stdout,"%s\n", argv[1]);
		decode(dbuf, argv[1], strlen(argv[1]));
		fprintf(stdout,"%s\n", dbuf);
		encode(ebuf, dbuf, strlen(dbuf));
		fprintf(stdout,"%s\n", ebuf);
	}
	return 0;
}
