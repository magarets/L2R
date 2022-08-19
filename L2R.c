#include <stdio.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM * a)
{
        char * number_str = BN_bn2dec(a);
        printf("%s %s\n", msg, number_str);
        OPENSSL_free(number_str);
}

int ExpMod(BIGNUM *r, const BIGNUM *a, const BIGNUM *e, BIGNUM *m)
{
	/*
	 * r: a^e mod m
	 * a: argv[1]
	 * e: argv[2]
	 * m: argv[3]
	 */	
	
	
	// setting
	// x = 1
	// bin = e
	// pow = a
	

	// roop
	// if(bin == 1)
	// pow = x^2 mod m
	// x = x * pow mod m

	BN_CTX *ctx = BN_CTX_new();

	BIGNUM *x = BN_new();
	BIGNUM *bin = BN_new();
	BIGNUM *pow = BN_new();
	BIGNUM *rem = BN_new();
	BIGNUM *bin_ = BN_new();
	BIGNUM *two = BN_new();

	/*copy*/
	BN_copy(bin, e);
	BN_copy(pow, a);

	/*setting*/
	BN_dec2bn(&x, "1");	
	BN_dec2bn(&two, "2");

	printf("b pow x\n");

	while(1){
		BN_div(bin_, rem, bin, two, ctx);
		BN_copy(bin, bin_);

		if(BN_is_one(rem)){
			BN_mod_mul(x, x, pow, m, ctx); // x = x * pow mod m			
		}
		
		printf("%s %s %s\n", BN_bn2dec(rem), BN_bn2dec(pow), BN_bn2dec(x));

		BN_mod_exp(pow, pow, two, m, ctx);

		if(BN_is_zero(bin)){
			// free
			
			BN_copy(r, x);
			return 0;
		}
	}

	
}

int main (int argc, char *argv[])
{
        BIGNUM *a = BN_new();
        BIGNUM *e = BN_new();
        BIGNUM *m = BN_new();
        BIGNUM *res = BN_new();

        if(argc != 4){
                printf("usage: exp base exponent modulus\n");
                return -1;
        }

        BN_dec2bn(&a, argv[1]);
        BN_dec2bn(&e, argv[2]);
        BN_dec2bn(&m, argv[3]);
        printBN("a = ", a);
        printBN("e = ", e);
        printBN("m = ", m);

        ExpMod(res,a,e,m);

        printBN("a**e mod m = ", res);

        if(a != NULL) BN_free(a);
        if(e != NULL) BN_free(e);
        if(m != NULL) BN_free(m);
        if(res != NULL) BN_free(res);

        return 0;
}
