//testa.cpp
//compila testa -c -t
//Taxa de erro de validacao: 0%
//Taxa de erro de teste: 0%
//Tempo de execucao: 0,5 s
#include "csv.h"

int main(int argc, char** argv) {

	Mat_<FLT> f1(32,32),f2(32,32);
	vec_t out;
	vec_t x;;
	
	double media_a=0;
	double media_v=0;
	double media_q=0;
	x.resize(1);
	// x.resize(1);
	// y.resize(1);
	// nome.resize(1);
	// int rot = 1;

	if(argc=!2){
		cout<<"Argumentos incorretos\n"<< "Exemplo:  mse ../diretorio_com_imagens";
	}
	string location = argv[1];
	ARQCSV A(location + "/treino.csv");
	ARQCSV V(location + "/teste.csv" );
	ARQCSV Q(location + "/valida.csv");

	
	x=A.tiny_x[0];

	network<sequential> net;
	net.load("treina.net");
	cout << "<<<<< validacao <<<<<<\n"<<A.nome[0]; 
	printf("\noi1\n");
	out = net.predict(x);
	printf("oi2\n");

	int k=0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			f1[i][j]=out[k++];
		}
	}	
	k=0;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			f2[i][j]=A.tiny_y[0][k++];
		}
	}
	normalize(f1,f1,1,-1,NORM_MINMAX);
	normalize(f2,f2,1,-1,NORM_MINMAX);

	mostra(f1);
	mostra(f2);
	double sum = 0.0;
	
		for(int y = 0; y < 32*32; ++y){
			double difference = (out[y] - x[y]);
			sum = sum + difference*difference;
		}
	
	media_a = sum /(32*32);
	
	// media_a = net.get_loss<mse>(out, A.tiny_y);
	// media_a=media_a/A.n;
	cout<<"Media de MSE de treino.csv: "<< media_a;
	

}

