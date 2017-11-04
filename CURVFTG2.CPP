//fits least square polynomial
//further scope : to decide the best fit polynomial by trying all degree polynomial fits and calculating standard error of estimates for each

#include<stdio.h>
#include<math.h>
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include"stats.cpp"
#include"det2busd.cpp"
#include"graphics.cpp"

void main()
{
 int i,j,t,n,N,c,degree;
 float x[80],y[80];
 float temp[80],temp2[80],cof[80][80],con[80],cal[80][80],sol[80],r,D,d;
 char ch;
			//N=no of entries
			//n=degree+1=no of linear equations to be solved
 clrscr();
 cout<<"CURVE FITTING  ( Least square polynomial )\n";

  hline();

  for( i=0;i<80;i++)
   {
     x[i]    = 0;
     y[i]    = 0;
     temp[i] = 0;
     temp2[i]= 0;
     con[i]  = 0;
     sol[i]  = 0;
   }

  for( i=0;i<80;i++)
   {
    for( j=0;j<80;j++)
     {
      cof[i][j]=0;
      cal[i][j]=0;
     }
   }

//input
    cout<<"\nEnter no. of entries (max 80) : ";
    cin>>N;
    cout<<"\nEnter degree of polynomial to be fit (max 1 less than no. of entries) : ";
    cin>>degree;

    cout<<"\n\nThe program may terminate abruptly if the data is beyond the \nrange : 3.4 * 10^-38 to 3.4 * 10^+38 \nat any time during computation.\n\nSame is the case while fitting higher degree polynomials if for example there \nare repeated points eg. two values of y for same value of x\n\nSo keep noting down each fit on paper\n\n";

    cout<<"PRESS  ANY KEY TO CONTINUE..."; getch();
    clrscr();

    inp_agn:
    cout<<"Enter how to input data : \n\nPress 1 : From keyboard\nPress 2 : From text files (one having x values in a column, and other having y \n\t\tvalues in a column).";

    switch(getche())
    {
     case '1':
      cout<<"\nEnter data:\n\n";
      for( i=0;i<N;i++)
       {
	cout<<"x"<<i+1<<":";
	cin>>x[i];
	cout<<"y"<<i+1<<":";
	cin>>y[i];
	printf("\n");
       }
      break;

      case '2':
       FILE *fx,*fy;
       char xfile[20],yfile[20];

       cout<<"\n\nEnter filename of x data : ";
       cin>>xfile;
       cout<<"Enter filename of y data : ";
       cin>>yfile;

       fx=fopen(xfile,"r");
       fy=fopen(yfile,"r");

       for( i=0;i<N;i++)
       {
	fscanf(fx,"%f",&x[i]);
	fscanf(fy,"%f",&y[i]);
       }

       fclose(fx);
       fclose(fy);
       break;

      default:
       clrscr();
       goto inp_agn;
     }

//input finishes, setting up of equations

newfit:

 for(i=0;i<=2*degree;i++)
  {
   temp[i]=sumxn(x,N,i);
  }

 for( i=0;i<=degree;i++)
   {
    int i2=i;

    for( t=0;t<=degree;t++)
     {
      temp2[t]=temp[i2++];
     }

    for( j=0;j<=degree;j++)
     {
      cof[i][j]=temp2[j];
     }

    con[i]=sumxnym(x,y,N,i,1);
  }

  /*
       // output for checking
 cout<<"\n\nThe entered system is...\n"
    <<"Eqn  ";

 for(i=0;i<=degree;i++)
 cout<<"Var"<<i+1<<"       ";

 cout<<"constant\n";

 for(i=0;i<=degree;i++)
  {
   printf("\n%d:",i+1);
   for(j=0;j<=degree;j++)
    {
     printf("%10.3g",cof[i][j]);
    }
   printf("%10.3g",con[i]);
  }

  */


 // now onwards adapted from lineqn.cpp

 n=degree+1;

 D=det(cof,n);

 //check for homogenity and case non homogenity with D=0 have been ommited
 // assuming that there is always a unique solution


//CASE OF D!=0(non homogenity)
for(c=0;c<n;c++)
 {
  for(i=0;i<n;i++)
   {
    for(j=0;j<n;j++)
     {
      if(j==c)
       {
	cal[i][j]=con[i];
       }
      else
       {
       cal[i][j]=cof[i][j];
       }
   }
 }
d=det(cal,n);
sol[c]=d/D;
}

//OUTPUT

printf("\n\nThe Least Square polynomial is:\n");
for(i=0;i<n;i++)
 {
  printf("\ncoefficient of x^ %d = %12g",i,sol[i]);
  if( (i+1)%20==0) getch();
 }


inp_again:


cout<<"\n\nFit new polynomial ? y/n : ";
ch=getch();

switch(ch)
{
 case 'y':
 case 'Y':
  cout<<"\nEnter degree of polynomial to be fit (max 1 less than no. of entries) : ";
    cin>>degree;
  goto newfit;
 case 'n':
 case 'N':
  goto end;
 default:

  cout<<"Error!!!";
  goto inp_again;
 }

end:

cbab();
}//main ends

