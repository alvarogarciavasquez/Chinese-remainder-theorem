/*
22/11/2021
Álvaro García Vásquez
*/

//C standard library fuctions
#include <stdio.h>
#include <stdlib.h>

//Prototypes
int gcd(int, int);

int main(void){
    //Define variables
    int N=1, k, value_in_a, value_in_n, X;

    //Messages
    printf("Chinese remainder theorem\n");
    printf("This program do the Chinese remainder theorem with a linear congruence system.\n");
    printf("Consider 'a' should be an integer number and 'n' should be a natural number.\n");
    printf("Otherwise something is going to be wrong.\n");

    //Insert value of k
    printf("\nInsert the dimension (k) of the linear congruence system: ");
    scanf("%d", &k);
    printf("\n");

    //Define x, a, n, c and d as an array with k as the size 
    int x[k], a[k], n[k], c[k], d[k];

    //Insert values for a[i] and n[i] with i in a range of 0 <= i < k
    printf("Insert all the values to create the linear congruence system | x = a (mod n) |: \n");
    for(int i=0; i<k; i++){
        //Insert values in a[i]
        printf("a[%d]:     ", i+1);
        scanf("%d", &value_in_a);
        a[i] = value_in_a;

        //Insert values in n[i]
        printf("Module %d: ", i+1);
        scanf("%d", &value_in_n);
        n[i] = value_in_n;
        printf("\n");
    }

    //Verify gmd with all the modules using the fuction gcd()
    printf("Verify the greatest common divisor of each module with another one which is different is equal to 1.\n");
    for(int i=0; i<k-1; i++){
        for(int z=i+1; z<k; z++){
            if( gcd(n[i], n[z]) == 1){
                printf("Greatest common divisor (%d,%d) = 1\n", n[i], n[z]);
                continue;
            }
            else{
                printf("Error, the greatest common divisor (%d,%d) != 1\n", n[i],n[z]);
                printf("\nThe Chinese remainder theorem is no valid for this case.");
                printf("\nFinished");
                exit(-1);
            }
        }
    }

    //Print the Linear congruence system | x ≡ ak (mod nk)
    printf("\nLinear congruence system: \n");
    for(int i=0; i<k; i++){
        printf("x = %d (mod %d) \n", a[i], n[i]);
    }
    
    //Get N using N = n1 * n2 * ... * nk
    for(int i=0; i<k; i++){
        N *= n[i];
    }
    //Print solve to N
    for(int i=0; i<k; i++){
        if(i==0){
            printf("\n\nSolution to 'N'\nN = ");
        }
        printf("n[%d]", i+1);
        if(i<k-1){
            printf(" x ");
        }
    }
    for(int i=0; i<k; i++){
        if(i==0){
            printf("\nN = ");
        }
        printf("%d", n[i]);
        if(i<k-1){
            printf(" x ");
        }
    }
    printf("\nN = %d\n\n\n", N);

    //Get c[i] using c[i] = N / n[i]
    for(int i=0; i<k; i++){
        c[i] = N / n[i];
    }

    //Get d[i] using c[i] * d[i] ≡ 1 (mod n[i])
    int result;
    for(int i=0; i<k; i++){
        for(int z=0; z<n[i]; z++){
            // n | a - 1  correct 
            if( (((c[i] * z) - 1) % (n[i])) == 0 ){
                result = z;
                break;
            }
            else{
                //In case there´s no solution, d[i] = 0.
                result = 0;
            }
        }
        if(result == 0){
            printf("Error, there's no solution for d[%d], so the Chinese remainder theorem is no valid for this case.\n", i+1);
            printf("\nFinished");
            exit(-1);
        }
        d[i] = result;
    }

    //Print all the values of n[i], a[i], c[i], d[i].
    for(int i=0; i<k; i++){
        if(i==0){
            printf("Values of 'n', 'a', 'c' and 'd'\n");
        }
        printf("n[%d] = %d\t", i+1, n[i]);
        printf("a[%d] = %d\t", i+1, a[i]);
        printf("c[%d] = %d\t", i+1, c[i]);
        printf("d[%d] = %d\t\n", i+1, d[i]);
    }

    //Get x
    int x_sum = 0;
    printf("\n\nSolution to 'x'\nx = (");
    for(int i=0; i<k; i++){
        x_sum += a[i] * c[i] * d[i];
        printf("(%d x %d x %d)", a[i], c[i], d[i]);
        if(i == k-1){
            // x = a1*c1*d1 + a2*c2*d2 + ... + ak*ck*dk (mod N)
            X = x_sum % N;
            printf(") (mod %d)", N);
            printf("\nx = %d (mod %d)\n", x_sum, X);
            printf("x = %d\n\n\n", X);
        }
        else{
            printf(" + ");
        }
    }

    //Verify and print the results with X 
    for(int i=0; i<k; i++){
        if(d[i] == 0){
            printf("\nError, the Chinese remainder theorem is not valid because of one of the next reasons.\n");
            printf("1.- A number is not a integer.\n");
            printf("2.- A module is not a natural number.\n");
            printf("3.- The greatest common divisor (n[r], n[j]) != 1.\n");
            printf("4.- Or something just went wrong.\n");
            break;
        }
        else{
            if(i==0){
                printf("Final results\n");
            }
            printf("%d = %d (mod %d) \n", X, a[i], n[i]);
        } 
    } 

    //Print results verification
    for(int i=0; i<k; i++){
        if(i == 0){
            printf("\n\nResults verification\n");
        }
        printf("%d | %d - %d\n", n[i], X, a[i]);
    }

    printf("\nFinished");

    return 0;
}

// Greatest common divisor
int gcd(int x, int y){
	//Define variables
	int a,b,q,r,result;
	
	//Order values (Greatest(a) y leastest(b))
	if(x<=y){
		a = y;
		b = x;
	}
	else{
		a = x;
		b = y;
	}
	
	//Operation with Euclid's algorithm
	q = a/b;  
	r = a%b;
	
	if(r==0){
		//Result gcd
		result = b;
	}
	else{
		while(r!=0){
		a = b;
		b = r;
		q = a/b;
		r = a%b;	
		}
		//Result gcd
		result = b;
	}
	
	//gcd
	return b;
}