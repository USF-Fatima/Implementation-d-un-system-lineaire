#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float * * AllocationDynamique ( int ligne , int colone )
{
//il pointe sur colone et ligne
    float * * ptr = ( float * * ) malloc ( sizeof ( float * ) * ligne + sizeof ( float ) * colone * ligne ) ;
    float *   dat = ( float *   ) ( ptr + ligne ) ;
    int i ;
    //ici si je n'ai pas de place dans la mémoire j'exit
    if ( ptr == NULL ) exit( EXIT_FAILURE ) ;
    for ( i = 0 ; i < ligne ; ++ i , dat += colone ) ptr [ i ] = dat ;
    return ptr ;
}

void RemplissageDuMatrice(float **A ,int n)
{
     int i , j ;
     printf(" Remplissez votre matrice : \n\n\n");

     for(i = 0 ; i < n ; i++)
     {
        for( j = 0 ; j < n ; j++)
        {
           printf("  A[%d][%d] : ",i+1,j+1);
           scanf("%f",&A[i][j]);
        }
     printf("\n");
      printf("\n");
       printf("\n");
     }
}

/* remplir le vecteur b*/
void Remplissage_du_vecteur_B(float *b ,int n)
{
     int i ;
     printf(" Remplissez le vexteur b : \n\n\n");

     for(i = 0 ; i < n ; i++)
     {
        printf("  b[%d] : ",i+1);
        scanf("%f",&b[i]);
        printf("\n");
     }
}
void affichage_du_matrice_iniale(float **A ,float *b ,int n)
{
	int i , j ;
	printf("Votre matrice iniale est bien celle ci : \n\n\n");

	for(i = 0 ; i < n ; i++)
	{
		printf("  (");
		for(j = 0 ; j < n ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf(" )    =");
		printf("\t%.3f",b[i]);
		printf("\n\n");
	}
}

void affiche_solution(float *x, int n)
{
    int i ;
	printf(" >Affichage de la solution : \n\n\n");

	for(i = 0 ; i < n ; i++)
	{
        printf("(x%d)   =",i+1);
		printf("\t%.6f",x[i]);
		printf("\n");
	}
}


void affichage_du_matrice(float **A ,float *b ,int n)
{
	int i , j ;
	printf(" votre matrice aprés les pivotations : \n\n\n");

	for(i = 0 ; i < n ; i++)
	{
		printf("  (");
		for(j = 0 ; j < n ; j++)
		{
			printf("  %.3f  ",A[i][j]);
		}
		printf(" )    (x%d)   =",i+1);
		printf("\t%.3f",b[i]);
		printf("\n\n");
	}
}



/* Méthode d'élimination de Gauss */
void gauss(float **A, float *b, float *x, int n)
{
     int i, j, k ;
     int imin ;
     float l ;
     float somme, valmin, tump1, tump2 ;

     for(k = 0 ; k < n-1 ; k++)
     {


        valmin = A[k][k] ; imin = k ;
        for(i = k+1 ; i < n ; i++)
        {
           if (valmin != 0)
           {
              if (abs(A[i][k]) < abs(valmin) && A[i][k] != 0)
              {
                 valmin = A[i][k] ;
                 imin = i ;
              }
           }
           else
           {
                 valmin = A[i][k] ;
                 imin = i ;
           }
        }

        /* Si l'élément minimal est nul le progrm sera intterempu psl c une matrice singulére*/

    if (valmin == 0.)
        {
           printf("\n\n\nAttention! Matrice singuliere!\n\n\n") ;
           exit( EXIT_FAILURE ) ;
        }

        /* si le programe n'a pas été intérempu alors ici on fais la pivotation partiel on inverse    */

        for(j = 0 ; j < n ; j++)
        {
           tump1 = A[imin][j] ;
           A[imin][j] = A[k][j] ;
           A[k][j] = tump1 ;
        }

        tump2 = b[imin] ;
        b[imin] = b[k] ;
        b[k] = tump2 ;


        /* On procède à la réduction de la matrice par la */
        /* implémentation d'algorithme du  Gauss. */

        for(i = k+1 ; i < n ; i++)
        {
           l = A[i][k]/A[k][k] ;

           for(j = 0 ; j < n ; j++)
           {
              A[i][j] = A[i][j] - l*A[k][j] ;
           }

           b[i] = b[i] - l*b[k] ;
        }
     }



     /* solution des x y z */

     x[n-1] = b[n-1]/A[n-1][n-1] ;

     for(i = n-2 ; i > -1 ; i--)
     {
           somme = 0 ;

           for(j = n-1 ; j > i ; j--)
           {
              somme = somme + A[i][j]*x[j] ;
           }
           x[i] = (b[i] - somme)/A[i][i] ;
     }
}

main()
{
      int n ;        
      int i, j ;
      float * * A ;  
      float * b ;    
      float * x ;   

      /* dimention */
      printf("\n Donnez la dimention de votre system: ") ;
      scanf("%d", &n) ;
      printf("\n") ;

      /* Allocation de mémoire pour A, b et x */
      A = AllocationDynamique(n,n) ;
      b = (float *) malloc (sizeof (float *) * n) ;
      x = (float *) malloc (sizeof (float *) * n) ;

      /* Saisie de la matrice A et du vecteur b */
      RemplissageDuMatrice(A,n) ;
      Remplissage_du_vecteur_B(b,n) ;

      /* affichage_du_matrice tel qu'elle est */
     affichage_du_matrice_iniale(A,b,n) ;

      /* Résolution du système par la méthode d'élimination de Gauss */
      gauss(A,b,x,n) ;

      /* affichage_du_matrice réduit */
      affichage_du_matrice(A,b,n) ;


     affiche_solution(x,n) ;

      free(A) ;
      free(b) ;

      exit( EXIT_SUCCESS ) ;
}
