//csv.h - rotina para ler arquivo CSV com nomes de imagens e rotulos
//Sera usada pelos programas treina.cpp e testa.cpp
#include <cektiny.h>
#include <cekeikon.h>
//<<<<<<<<<<<<<<<<< IMAGEM_CSV <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
class ARQCSV {
    //Le arquivo CSV com formato:
    //111a.jpg;0
    //111b.jpg;0
    //Le imagem e label no mesmo diretorio do arquivo CSV e os coloca nos vetores x e y
    public:
    int n; // numero de linhas do CSV
    // vector< Mat_<FLT> > x;  vector< Mat_<FLT> > y; // imagens e rotulos convertidos para formato tiny_dnn
    std::vector< vec_t > tiny_x;  std::vector< vec_t > tiny_y; // imagens e rotulos convertidos para formato tiny_dnn
    vector< string > nome; // nomes dos arquivos
    ARQCSV(string caminho);
};
ARQCSV::ARQCSV(string arqcsv) {
    n=0;
    string nomedir = diretorio(arqcsv);
    if (nomedir=="") 
        nomedir=".";
    FILE* arq=fopen(arqcsv.c_str(),"rt");
    while (true) {
        string st=leFileName(arq);
        if (st=="eof") break;
        string st2=leFileName(arq);
        if (st2=="eof") break;
        n++;
    }
    
    tiny_x.resize(n);
    tiny_y.resize(n);
    nome.resize(n);
    rewind(arq);
    int i=0;
    Mat_<FLT> f;
    Mat_<FLT> f2;
    while (true) {
        string st=leFileName(arq);
        if (st=="eof") break;
        st=nomedir+'/'+st;

        string st2=leFileName(arq);
        if (st2=="eof") break;
        st2 = nomedir+'/'+st2;


        le(f,st);
        le(f2,st2);
        // if (i == numero_imagem){
        //     mostra(f);
        //     mostra(f2);
        // }
        //resize(f,f,Size(nc,nl),0,0,INTER_AREA);
        normalize(f,f,1,-1,NORM_MINMAX);
        normalize(f2,f2,1,-1,NORM_MINMAX);
        //Provavelmente, e' melhor normalizar de -0.5 a +0.5 ou -1.0 a +1.0
        
        // x[i] = f.clone();
        // y[i] = f2.clone();
        converte(f,tiny_x[i]);
        converte(f2,tiny_y[i]);
        nome[i]=st;
        i++;
    }
    fclose(arq);
    // mostra(x[20]);
    // mostra(x[numero_imagem]);
}
