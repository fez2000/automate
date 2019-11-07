#include "lang.hpp"
#include "string.h"
#include "stdlib.h"

std::string bdlangpath = "./BD/lang/";
std::map<long long, char *> lang;

const char * get(const char * a){
    std::string g(a);
    if(lang[de_string_pour_long_long(g)]){
        return lang[de_string_pour_long_long(g)];
    }
    return "";
}
int charger(const char * fichier_lang="fr"){
    
    bool chercherBalise = true, lineEndBalise = false,chevronsOuvrant = false,ligneBalise = false;
    char c,*line = (char *)malloc(sizeof(char)*512);
    int i = 0;
    std::string balise,baliseF,continu;
    std::ifstream fichier;
        try{
            fichier.open( cat_many(5,bdlangpath.c_str(),fichier_lang,"/",fichier_lang,".txt").c_str()  );
            if(fichier)
            {
                while (!fichier.eof())
                {
                    
                    fichier.getline(line,512,'\n');
                    /* code */
                
                    i = 0;
                    
                    while (line[i]!='\0')
                    {
                        
                        c = line[i++];
                        if( c == '\\'){
                            switch(line[i])
                            {
                                case 't':
                                    continu.push_back('\t');
                                    i++;
                                    continue;
                                break;
                            }
                        }         
                        if(chercherBalise){
                            if(c=='<'){
                                if(!chevronsOuvrant)
                                    chevronsOuvrant = true; 
                                else
                                {
                                    balise.push_back(c);
                                }
                                
                            }else{
                                if(c=='>'){
                                    if(chevronsOuvrant){
                                        chevronsOuvrant = false;
                                    
                                        chercherBalise = false;
                                        ligneBalise = true;
                                    }else{
                                    return ERREUR_FIC_LANG; 
                                    }
                                }else{
                                    balise.push_back(c);
                                }
                            }

                        }
                        else{
                            if(c=='<'){
                                if(!chevronsOuvrant)
                                    chevronsOuvrant = true; 
                                else
                                {
                                    baliseF.push_back(c);
                                }
                            }else{
                                if(c == '>' ){
                                    if(chevronsOuvrant){
                                        
                                        if( 0 == balise.compare(baliseF.c_str()) ){
                                            lineEndBalise = true;
                                            
                                            lang.insert(std::pair<long long,char * >(de_string_pour_long_long(balise),strdup(continu.c_str())));
                                           // std::cout <<lang[ de_string_pour_long_long(balise)] << " "<<lang.size() << "\n";
                                            continu.clear();
                                            balise.clear();
                                            baliseF.clear();
                                            chercherBalise = true;
                                            ligneBalise = true;
                                            chevronsOuvrant = false;    

                                        }else{
                                            continu.push_back('<');
                                            continu.append(baliseF.c_str());
                                            continu.push_back('>');
                                            baliseF.clear();
                                            
                                        }
                                    }else
                                    {
                                        continu.push_back(c);
                                    }
                                    
                                }else{
                                    if(!chevronsOuvrant){
                                        continu.push_back(c);
                                    }else{
                                        baliseF.push_back(c);
                                    }
                                    
                                    
                                }
                            }
                        }
                    
                    }
                  if(!ligneBalise&&!lineEndBalise){
                      continu.push_back('\n');
                  }else{
                      ligneBalise = false;
                      lineEndBalise = false;
                  }  
                       
                     
                }
                free(line);
                fichier.close();
                return PAS_DERREUR;
                        
                
            }
        }
        catch(std::string & ex){
            return ERREUR_SYSTEME;
        }
    return PAS_DERREUR;

};