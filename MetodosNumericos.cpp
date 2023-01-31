#include <iostream>
#include <math.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <iomanip>
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define ENTER 13

using namespace std;


//////////////////GOTOXY///////////////////////////////////////
void gotoxy(int x,int y){
    HANDLE hcon= GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hcon, dwPos);
}
//MENU
void marco();
void menu();
void menu_principal();
//METODOS////////////////
void Lagrange();
////////////////
void m_trapecio();
//{
float evaluar_funcion(float);
//}
////////////////
void MetodoEuler();
//{
double FuncionEuler(double,double);
double FuncionYn1Euler(double, double, double);
double FuncionXnEuler(double, double);
double FuncionYnEuler(double, double, double, double , double );
//}
////////////////////
void simpson();
//{
float f(float);
//}
///////////////////
void m_newton();
///////////////
void MinimosCuadradosLineal(double puntos[][2],int n,double x);
//{
double Min[10][2];
int MinN;
////////
double sumaX(double puntos[][2],int n);
double sumaY(double puntos[][2],int n);
double sumaXX(double puntos[][2],int n);
double sumaXY(double puntos[][2],int n);
double xp(double puntos[][2],int n);
double yp(double puntos[][2],int n);
double a1(double puntos[][2],int n);
double a0(double puntos[][2],int n);
//}
///////////////////////
void MinimosPolinomial(double puntos[][2],int n,double x);
//{
int ManN;
double Man[10][2];
double coef[3];
///
double sumaX1(double puntos[][2],int n);
double sumaY1(double puntos[][2],int n);
double sumaXX1(double puntos[][2],int n);
double sumaXXX1(double puntos[][2],int n);
double sumaXXXX1(double puntos[][2],int n);
double sumaXY1(double puntos[][2],int n);
double sumaXXY1(double puntos[][2],int n);
double xp1(double puntos[][2],int n);
double yp1(double puntos[][2],int n);
void coeficientes(double puntos[][2],int n);

//}



/////////////////para el color
HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
////////////MAIN////////////////////////////
int main(){
	menu_principal();
	return 0;
}
////////////////////////////////////////////////////
//FUNCIONES MENU
////
void marco(const char *titulo){
    gotoxy(1,1);printf("%c",201); //201 = [╔]
    for(int xcol=2;xcol<=79;xcol++){
        gotoxy(xcol,1);printf("%c",205); //205 = [═]
    }
    gotoxy(80,1);printf("%c",187); // 187 = [╗]
    gotoxy(1,2);printf("%c",186);  // 186 = [║]
    if(titulo!="MENU DE OPERACIONES CON MATRICES"){
            gotoxy(35,2); cout<<titulo;
    }else{
            gotoxy(25,2); cout<<titulo;
    }
    gotoxy(80,2);printf("%c",186);
    //linea de abajo
    gotoxy(1,3);printf("%c",200); //200 = [╚]
    for(int xcol=2;xcol<=79;xcol++){
        gotoxy(xcol,3);printf("%c",205); //205 = [═]
    }
    gotoxy(80,3);printf("%c",188); //188 = [╝]
}


int menu(const char *titulo,const char *opciones[], int n){
    int opcion=1;
    int tecla;
    bool repite=true;
    do{
        system("cls");
        SetConsoleTextAttribute(hConsole, 14); // para el texto en azul
        marco(titulo);
        SetConsoleTextAttribute(hConsole, 11); // para el texto en azul
        gotoxy(10,5+opcion); cout<<"==>";
        ///Imprimir opciones
        for(int i=0;i<n;i++){
            gotoxy(15,6+i); cout<<i+1<<") "<<opciones[i];
        }

        do{
            gotoxy(0,0);
            tecla=getch();
        }while(tecla!=TECLA_ARRIBA&&tecla!=TECLA_ABAJO&&tecla!=ENTER);
        switch(tecla){
            case TECLA_ARRIBA:
                opcion--;
                if(opcion<1){
                    opcion=n;
                }

            break;
            case TECLA_ABAJO:
                opcion++;
                if(opcion>n){
                    opcion=1;
                }

            break;
            case ENTER:
                repite=false;
            break;
        }

    }while(repite);

    return opcion;
}


void menu_principal(){
    bool repite = true;
    int opcion;
    const char *titulo = "METODOS NUMERICOS";
    const char *opciones[] = {"METODO LAGRANGE","METODO DE TRAPECIO","METODO DE EULER MEJORADO","METODO DE SIMPSON","METODO INTERPOLACION DE NEWTON","METODO APROXIMACION DE MINIMOS CUADRADOS LINEAL","METODO APROXIMACION DE MINIMOS CUADRADOS POLINOMIAL","SALIR"};
    int n = 7;
    do{
        opcion=menu(titulo,opciones,n);
        system("cls");
        switch(opcion){
            case 1: //METODO LAGRANGE
                Lagrange();
                system("PAUSE");
            break;
            case 2://METODO TRAPECIO
                m_trapecio();
                system("PAUSE");
            break;
            case 3: //METODO EULER
                MetodoEuler();
                system("PAUSE");
            break;
            case 4: // METODO SIMPSON
                simpson();
                system("PAUSE");
            break;
            case 5: // METODO INTERPOLACION DE NEWTON
                m_newton();
                system("PAUSE");
            break;
            case 6: // METODO MINIMOS CUADRADOS LINEAL
                MinimosCuadradosLineal(Min,MinN,14);
                system("PAUSE");
            break;
            case 7: // METODO MINIMOS CUADRADOS POLINOMIAL
                MinimosPolinomial(Man,ManN,5);
                system("PAUSE");
            break;
            case 8:
                repite=false;
            break;
        }
    }while(repite==true);
}

//////////////////////////////////////////////
//METODO LAGRANGE
void Lagrange(){
    cout<<"\t\tMETODO LAGRANGE\n\n";
    float x,y,xi[10],yi[10];
    int n;
    cout<<"Ingrese X : "<<endl;
    cin>>x;
    cout<<"Ingrese la cantida de puntos"<<endl;
    cin>>n;
        for(int i = 0; i < n; i++){
            cout<<"Puntos Xi"<<endl;
            cin>>xi[i];
            cout<<"Puntos Yi"<<endl;
            cin>>yi[i];
        }

    double result = 0;

    for (int i = 0; i < n; i++) {

        double term = yi[i];

        for (int j = 0; j < n; j++) {

            if (j != i){
                term = term * (x - xi[j]) / (xi[i] - xi[j]);
            }

        }
        result = result+ term;
    }
    cout<<"La interpolacion con x= n es = " <<result;
    cout<<endl;
}
/////////////////////////////////////////////////////////////////

///METODO TRAPECIO

void m_trapecio(){
	cout << "\n\nREGLA DEL TRAPECIO\n\n";
    float n, a, b;
    cout << "Escriba el numero de particiones: "; cin >> n;
    cout << "Escriba el limite inferior: "; cin >> a;
    cout << "Escriba el limite superior: "; cin >> b;

    float h = (b - a) / n;
    float sum = 0;

    cout << "h = " << (b - a) / n << endl;

    for (int i = 0; i < n+1; i++){
        float xi = a + h*i;
        cout << "X"<< i << " = " << xi << endl;
        if (i == 0 || i == n){ sum += evaluar_funcion(xi); }
        else{ sum += 2 * evaluar_funcion(xi); }
    }

    //cout << "Suma total = " << sum << endl;

    float res = (h/2) * sum;
    cout << "Resultado = " << res;
    cout<<endl;
}

float evaluar_funcion(float x){
    return 1 + x*x;
}
/////////////////////////////////////////////////////////////

////METODO EULER MEJORADO

double FuncionEuler(double x,double y){
    return 2*x*y;
}

double FuncionYn1Euler(double x, double y, double h){
    return y+h*FuncionEuler(x,y);
}

double FuncionXnEuler(double x, double h){
    return x+h;
}

double FuncionYnEuler(double x, double y, double h, double xn, double yn1){
    return y+(h/2)*(FuncionEuler(x,y)+FuncionEuler(xn,yn1));
}

void MetodoEuler(){
    double x,y,xf,h; // valores iniciales
    double yn1,xn,yn; // resultado de formulas
    int n=0; // contador
    system("cls");
    cout<<"\n\t\t METODO EULER MEJORADO";
    cout<<"\n\nIngrese el valor inicial de X  [X0] --> : ";cin>>x;
    cout<<"\nIngrese el valor inicial de Y  [Y0] --> : ";cin>>y;
    cout<<"\nIngrese la ultima iteracion de la condicion [xf] --> :";cin>>xf;
    cout<<"\nIngrese el tamaño de paso [h] -->";cin>>h;
    //
    cout<<"\n\n\N\tXn\tYn\t\t(Yn+1)*\t\tXn+1\t\tYn+1"; //molde de tabla
    cout<<"\n_______________________________________________________________________";
    //
    while(x<=xf){// controlar el paso
        yn1=FuncionYn1Euler(x,y,h);
        xn=FuncionXnEuler(x,h);
        yn=FuncionYnEuler(x,y,h,xn,yn1);
        cout<<"\n\n"<<n<<"\t"<<x<<"\t"<<y<<"\t\t"<<yn1<<"\t\t"<<xn<<"\t\t"<<yn;
        n++;
        x=x+h;
        y=yn;
    }
    cout<<"\n_______________________________________________________________________";

    cout<<"\n\n La iteracion final es Yn = "<<yn;
    cout<<endl;
}


////////////////////////////////////////////////////////////////////////////////////
//METODO SIMPSON

void simpson()
{
	float a,b;
	int n;
	cout<<"\t\tMETODO SIMPSON\n\n";
	cout<<"\nIngrese el valor de limite inferior a --> : ";cin>>a;
	cout<<"\nIngrese el valor de limite superior b --> : ";cin>>b;
	cout<<"\nIngresa la cantidad de divisiones n --> : ";cin>>n;

	float h, x[n+1], sum = 0;
	int j;
	h = (b-a)/n;

	x[0] = a;

	for(j=1; j<=n; j++)
	{
		x[j] = a + h*j;
	}

	for(j=1; j<=n/2; j++)
	{
		sum += f(x[2*j - 2]) + 4*f(x[2*j - 1]) + f(x[2*j]);
	}

	if (n%2 == 0)
		cout<<"\n RESULTADO METODO SIMPSON : --> "<<sum*h/3;
	else
		cout<<"\nDeberia ser un numero par";

    cout<<endl;
}

float f(float x)
{
	return sqrt(5+pow(x,3));	//Define la función f(x)
}

//////////////////////////////////////////////////////////////////////////////
//METODO NEWTON

void m_newton(){
	cout<<"\t\tMETODO NEWTON\n\n";
	cout<<" Diferencias Divididas de Newton"<<endl;
    cout<<" Calcula el polinomio interpolador de una funcion" << endl;
	setlocale(LC_ALL, "");

	double *puntos_x,*puntos_y,**efes;
	int i,j,nom_puntos;

	for(i=0;i<87;i++)
		cout<<".";

    cout << "\nIngrese el numero de puntos: ";
    cin >> nom_puntos;


    //Creamos memoria dinamica
    efes=new double *[nom_puntos];

    for(i=0;i<nom_puntos;i++)
		efes[i]= new double[nom_puntos-(i)];

    puntos_x = new double [nom_puntos];
    puntos_y = new double [nom_puntos];


    //Ingresaomos las cordenadas de los puntos
    for(i=0; i<nom_puntos;i++){
        cout<<"Ingrese x("<<i<<")=";
        cin>>puntos_x[i];
    }
    cout<<"\nf(Xi)"<<endl;
    for(i=0; i<nom_puntos;i++){
        cout<<"Ingrese f("<<i<<")=";
        cin>>puntos_y[i];
    }


    //Tabla 1
    cout<<"\nXi\t";

    cout<<fixed<<setprecision(3);
    for(i=0;i<nom_puntos;i++)
		cout<<puntos_x[i]<<"\t";

    cout<<"\nf(Xi)\t";
    for(i=0;i<nom_puntos;i++)
		cout<<puntos_y[i]<<"\t";


    //Tabla 2
    cout<<endl;
    cout<<"\ni\t\t\t\t";
    for(i=1;i<nom_puntos;i++)
		cout<<i<<"\t\t";

    cout<<"\nj\tXi\tf(Xi)\t\t";

    for(i=1;i<nom_puntos;i++)
		cout<<i<<".\t\t";

    cout<<endl;


    //Operaciones
    //Igualamos las cordenas en y de los puntos y se lo igualamos a nuestra matriz
    for(j=0;j<nom_puntos;j++)
		efes[0][j]=puntos_y[j];

    for(i=1; i<nom_puntos; i++){
        for(j=0; j<nom_puntos-i; j++){
            efes[i][j]=(efes[i-1][j+1]-efes[i-1][j])/(puntos_x[i+j]-puntos_x[j]);
        }
    }


    //Imprimir
    for(i=0; i<nom_puntos;i++){
        cout<<i<<"\tX"<<i<<"="<<setprecision(1)<<puntos_x[i]<<"\t"<<setprecision(3);
        for(j=0;j<nom_puntos-i;j++){
            cout<<"F"<<i<<j<<"="<<efes[j][i]<<"\t";
        }
        cout<<endl;
    }


    //Creamos polinomio
    cout<<"\nEl polinomio interpolar es igual a: ";

    for(i=0;i<nom_puntos;i++){
        if(efes[i][0]>0 || efes[i][0]<0){
            if(i<nom_puntos && i>0)
				cout<<" + ";
            cout<<setprecision(2)<<efes[i][0];
            for(j=0;j<i;j++){
                cout<<"(x-"<<puntos_x[j]<<")";
            }

        }
    }

    //Evaluar puntos
    int n_puntos,k;
    double x,r,total;
    cout<<"\n\nCuantos puntos deseas evaluar?: ";
    cin>>n_puntos;


    for(k=0; k<n_puntos;k++){
        cout<<"\nIngresa punto x"<<char(97+k)<<"= ";
        cin>>x;
        for(i=0;i<nom_puntos;i++){
            if(i==0)total=efes[0][0];
            else{
                for(j=0;j<i;j++){
                    if(j==0)
						r=efes[i][0];
                    r*=(x-puntos_x[j]);//Es igual a: r=r*(x-puntos_x[j]);
                }
                total+=r;//Es igual a total= total+r;
            }
        }
        cout<<"x"<<char(97+k)<<"="<<total<<endl;
    }

    cout<<"\n\n\n";
}

////////////////////////////////////////////////////////////
//METODO DE MINIMOS CUADRADOS LINEAL


double a[10][2];


double sumaX(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][0];
	}
	return suma;
}
double sumaY(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][1];
	}
	return suma;
}
double sumaXX(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=pow(puntos[i][0],2);;
	}
	return suma;
}
double sumaXY(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][0]*puntos[i][1];
	}
	return suma;
}
double xp(double puntos[][2],int n){
	return (puntos[0][0]+puntos[n-1][0])/2;
}
double yp(double puntos[][2],int n){
	return sumaY(puntos,n)/n;
}
double a1(double puntos[][2],int n){
	return (n*sumaXY(puntos,n)-sumaX(puntos,n)*sumaY(puntos,n))/(n*sumaXX(puntos,n)-sumaX(puntos,n)*sumaX(puntos,n));
}
double a0(double puntos[][2],int n){
	return yp(puntos,n)-a1(puntos,n)*xp(puntos,n);
}

void MinimosCuadradosLineal(double puntos[][2],int n,double x){
    cout<<"\t\tMETODO DE MINIMOS CUADRADOS LINEAL\n\n";
	cout<<"Ingrese el valor de n: ";cin>>n;
	for(int i=0;i<n;i++){
		for(int j=0;j<2;j++){
			if(j==0){
				cout<<"x("<<i+1<<"): ";cin>>puntos[i][j];
			}else{
				cout<<"y("<<i+1<<"): ";cin>>puntos[i][j];
			}
		}
	}
	cout<<"f(x): "<<a0(puntos,n)<<" + "<<a1(puntos,n)<<" x "<<endl;
	cout<<"Ingrese el valor de x: ";cin>>x;
	cout<<a0(puntos,n)+a1(puntos,n)*x;
	cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//METODO DE MINIMOS CUADRADOS POLINOMIAL
double sumaX1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][0];
	}
	return suma;
}
double sumaY1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][1];
	}
	return suma;
}
double sumaXX1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=pow(puntos[i][0],2);
	}
	return suma;
}
double sumaXXX1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=pow(puntos[i][0],3);
	}
	return suma;
}
double sumaXXXX1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=pow(puntos[i][0],4);
	}
	return suma;
}
double sumaXY1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=puntos[i][0]*puntos[i][1];
	}
	return suma;
}
double sumaXXY1(double puntos[][2],int n){
	double suma=0;
	for(int i=0;i<n;i++){
		suma+=pow(puntos[i][0],2)*puntos[i][1];
	}
	return suma;
}
double xp1(double puntos[][2],int n){
	return (puntos[0][0]+puntos[n-1][0])/2;
}
double yp1(double puntos[][2],int n){
	return sumaY(puntos,n)/n;
}
void coeficientes(double puntos[][2],int n){
	double res[3];
	double ext=0;
	double matriz[3][4];
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(i+j==0){
				matriz[i][j]=n;
			}
			if(i+j==1){
				matriz[i][j]=sumaX1(puntos,n);
			}
			if(i+j==2){
				matriz[i][j]=sumaXX1(puntos,n);
			}
			if(i+j==3){
				matriz[i][j]=sumaXXX1(puntos,n);
			}
			if(i+j==4){
				matriz[i][j]=sumaXXXX1(puntos,n);
			}
		}
	}

	cout<<endl;
	matriz[0][3]=sumaY1(puntos,n);
	matriz[1][3]=sumaXY1(puntos,n);
	matriz[2][3]=sumaXXY1(puntos,n);
	for(int i=0;i<2;i++){
		for(int j=i+1;j<3;j++){
			ext=(-1*(matriz[j][i]/matriz[i][i]));
			for(int k=0;k<=3;k++){
				matriz[j][k]+=ext*matriz[i][k];
			}
		}
	}
	coef[2]=matriz[2][3]/matriz[2][2];
	coef[1]=(matriz[1][3]-matriz[1][2]*coef[2])/matriz[1][1];
	coef[0]=(matriz[0][3]-matriz[0][2]*coef[2]-matriz[0][1]*coef[1])/matriz[0][0];

}
void MinimosPolinomial(double puntos[][2],int n,double x){
    cout<<"\t\tMINIMOS CUADRADOS POLINOMIAL\n\n";
	cout<<"Ingrese el valor de n: ";cin>>n;
	//puntos[6][2]={{0,2.1},{1,7.7},{2,13.6},{3,27.2},{4,40.9},{5,61.1}};
	for(int i=0;i<n;i++){
		for(int j=0;j<2;j++){
			if(j==0){
				cout<<"x("<<i+1<<"): ";cin>>puntos[i][j];
			}else{
				cout<<"y("<<i+1<<"): ";cin>>puntos[i][j];
			}
		}
	}
	coeficientes(puntos,n);
	cout<<"f(x): "<<coef[0]<<" + "<<coef[1]<<" x "<<" + "<<coef[2]<<" x^2 "<<endl;
	cout<<"Ingrese el valor de x: ";cin>>x;
	cout<<coef[0]+coef[1]*x+coef[2]*pow(x,2);
	cout<<endl;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
