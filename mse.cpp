//testa.cpp
//compila testa -c -t
//Taxa de erro de validacao: 0%
//Taxa de erro de teste: 0%
//Tempo de execucao: 0,5 s
#include "csv.h"

double calcula_mse(vec_t img1 , vec_t img2){
	Mat_<FLT> f1(32,32),f2(32,32);
	int k=0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			f1[i][j]=img1[k++];
		}
	}	
	k=0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			f2[i][j]=img2[k++];
		}
	}
	normalize(f1,f1,1,0,NORM_MINMAX);
	normalize(f2,f2,1,0	,NORM_MINMAX);

	double sum = 0.0;
	
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			double difference = (f1[i][j] - f2[i][j]);
			sum = sum + difference*difference;
		}
	}
	return sum /(32*32);
}
int main(int argc, char** argv) {

	
	vec_t out;
	vec_t x,y;
	
	double media_a=0;
	double media_v=0;
	double media_q=0;
	x.resize(1);
	
	if(argc=!2){
		cout<<"Argumentos incorretos\n"<< "Exemplo:  mse ../diretorio_com_imagens";
	}
	string location = argv[1];
	ARQCSV A(location + "/treino.csv");
	ARQCSV V(location + "/teste.csv" );
	ARQCSV Q(location + "/valida.csv");

	
	

	network<sequential> net;
	net.load("treina.net");
	
	/*Treino*/
	for (int i = 0; i < A.n; i++)
	{
		x=A.tiny_x[i];
		y=A.tiny_y[i];
		out = net.predict(x);
		media_a += calcula_mse(out,y);
	}
	media_a=media_a/A.n;
	cout<<"Media de MSE de treino.csv: "<< media_a<<"\n";
	

	/*Teste*/
	for (int i = 0; i < V.n; i++)
	{
		x=V.tiny_x[i];
		y=V.tiny_y[i];
		out = net.predict(x);
		media_v += calcula_mse(out,y);
	}
	media_v=media_v/A.n;
	cout<<"Media de MSE de treino.csv: "<< media_v<<"\n";


	/*Validacao*/
	for (int i = 0; i < V.n; i++)
	{
		x=Q.tiny_x[i];
		y=Q.tiny_y[i];
		out = net.predict(x);
		media_q += calcula_mse(out,y);
	}
	media_q=media_q/A.n;
	cout<<"Media de MSE de treino.csv: "<< media_q<<"\n";
	
	

}

