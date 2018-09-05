//testa.cpp
//compila testa -c -t
//Taxa de erro de validacao: 0%
//Taxa de erro de teste: 0%
//Tempo de execucao: 0,5 s
// #include "csv.h"
#include <cektiny.h>
#include <cekeikon.h>

int main(int argc, char** argv) {
  
  Mat_<FLT> f;
  Mat_<FLT> f_res(32,32);
  vector<vec_t> x; vector<vec_t> y;
  vector< string > nome;
  x.resize(1);
  y.resize(1);
  nome.resize(1);
  int rot = 1;

  if(argc=!3){
    cout<<"Argumentos incorretos\n"<< "Exemplo:  supres ../diretorio/004bx.png 004bp.png";
  }
  
  string st = argv[1];
  

  le(f,st);
  normalize(f,f,1,-1,NORM_MINMAX);
  converte(f,x[0]);

  
  nome[0] = st;
  
  network<sequential> net;
  net.load("treina.net");
  cout << "<<<<< validacao <<<<<<\n"; 
  y = net.predict(x);
  int k=0;
  for (int i = 0; i < 32; i++)
  {
    for (int j = 0; j < 32; j++)
    {
      f_res[i][j]=y[0][k++];
    }
  }
  imp(f_res,argv[2]);

}
  
