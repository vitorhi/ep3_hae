//treina.cpp - treina rede para distinguir elipses e retangulos
//compila treina -c -t
#include "csv.h"
int main(int argc, char** argv) {
	string location = argv[1];
    //"C:\\Users\\marco\\Desktop\\Poli\\Materias\\SistEletronicosInteligentes2\\Hae\\Aula7\\Ex7_3\\images_reduced\\treino.csv"
    //Exemplo a partir de um diretorio: "...\\subdiretorio\\treino.csv"
	ARQCSV A(location + "/treino.csv");
	ARQCSV V(location + "/teste.csv" );
	ARQCSV Q(location + "/valida.csv");
	// Teste



	int n_train_epochs=300;
	int n_minibatch=2;
	network<sequential> net;
	net << conv(8, 8, 3, 1, 50)
	<< max_pool(6, 6, 50, 2) << relu()
	<< conv(3, 3, 2, 50, 80)
	// << max_pool(2, 2, 80, 2) << relu()
	<< fc(2*2*80, 400) << relu()
	<< fc(400, 100) << relu()
	<< fc(100, 32*32);

// aumentaTreino(ax,ay,32,32,1,false,true); //espelha, diagonais
adam optimizer;
optimizer.alpha = 5e-5;
cout << "Learning rate=" << optimizer.alpha << endl;
int sucesso_anterior=0;
cout << "start training" << endl;
progress_display disp(A.tiny_x.size());
timer t;
int epoch = 1;
double omelhor=100.0;
auto on_enumerate_epoch = [&]() {

	cout << "Epoch " << epoch << "/" << n_train_epochs << " finished. "
	<< t.elapsed() << "s elapsed. ";
	++epoch;
	auto loss = net.get_loss<mse>(V.tiny_x, V.tiny_y);
	// result res = net.test(V.tiny_x, V.tiny_y);
	cout << "Validacao: " << loss << "/" /*<< res.num_total*/ << endl;
	if (loss>=sucesso_anterior && optimizer.alpha>5e-6) {
		optimizer.alpha *= 0.70;
		cout << "Learning rate=" << optimizer.alpha << endl;
	}
	sucesso_anterior=loss;
	if (loss<=omelhor) {
		omelhor=loss;
		string nomearq = semDiret(string(argv[0]))+".net";
		net.save(nomearq);
		cout << "Gravado arquivo " << nomearq << endl;
	}
	disp.restart(A.tiny_x.size());
	t.restart();
};
auto on_enumerate_minibatch = [&]() { disp += n_minibatch; };
net.fit<mse>(optimizer, A.tiny_x, A.tiny_y, n_minibatch,n_train_epochs, on_enumerate_minibatch, on_enumerate_epoch);

cout << "end training." << endl;
}