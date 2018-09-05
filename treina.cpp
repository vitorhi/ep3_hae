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
	// std::vector<vec_t> ax;
	// std::vector<vec_t> ay;
	// std::vector<vec_t> vx;
	// std::vector<vec_t> vy;
	// std::vector<vec_t> qx;
	// std::vector<vec_t> qy;

	// for(int i=0;i<=200;i++){
	// 	converte(A.x[i],ax[i]);
	// 	converte(A.y[i],ay[i]);
	// }

	// for(int i=0;i<=100;i++){
	// 	converte(V.x[i],vx[i]);
	// 	converte(V.y[i],vy[i]);
	// }


	// for(int i=0;i<=100;i++){
	// 	converte(Q.x[i],qx[i]);
	// 	converte(Q.y[i],qy[i]);
	// }



	int n_train_epochs=300;
	int n_minibatch=2;
	network<sequential> net;
	net << conv(8, 8, 2, 1, 40)
	<< max_pool(7, 7, 40, 2) << relu()
	// << conv(3, 3, 2, 40, 80)
	// << max_pool(2, 2, 80, 2) << relu()
	<< fc(3*3*40, 200) << relu()
	<< fc(200, 100) << relu()
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
		optimizer.alpha *= 0.80;
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