#include "Date.hpp"
/*
{
        int tm_sec;   // seconds of minutes from 0 to 61
        int tm_min;   // minutes of hour from 0 to 59
        int tm_hour;  // hours of day from 0 to 24
        int tm_mday;  // day of month from 1 to 31
        int tm_mon;   // month of year from 0 to 11
        int tm_year;  // year since 1900
        int tm_wday;  // days since sunday
        int tm_yday;  // days since January 1st
        int tm_isdst; // hours of daylight savings time
        }*/
namespace Date{
    std::string Date::to_str(Date d){
    std::string delimteur("/");

      return   ::to_str<int>(d.jour) + delimteur + ::to_str<int>(d.mois+1) + delimteur + ::to_str<int>(d.annee);
    };
    Date::Date (Date & a){
        
        time = a.time;
    };
    Date::Date (const Date & a){
        
        time = a.time;
    };
    Date::Date(/* args */)
    {
        time = std::time(0);
    }
    Date::Date(int jour,Mois mois,int annee)
    {
        
        this->jour = jour;
        this->mois = mois;
        this->annee = annee;
        time = std::time(NULL);
        
    }

    Date::~Date()
    {
    }
    int Date::retourner_jour(){
        return this->jour;
    };
    int Date::retourner_jour() const{
        return this->jour;
    };
    Mois Date::retourner_mois(){
        return this->mois;
    };
    Mois Date::retourner_mois() const{
        return this->mois;
    };
    int Date::retourner_annee(){
        return this->annee;
    };
    int Date::retourner_annee() const{
        return this->annee;
    };
    void Date::mettre_jour(int j){
        this->jour = j;
    };
    void Date::mettre_mois(Mois m){
        this->mois = m;
    };
    void Date::mettre_annee(int a){
        this->annee = a;
    };
    bool Date::est_valide(){
        const Date d(*this);
        return d.est_valide();
    }
    bool Date::est_valide() const{
        if(this->mois < 0 || this->mois >11) return false;
        int t[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if(this->mois == FEVRIER){
            int a = t[FEVRIER];
            if(annee_bissextile(this->annee)) a++;
            if(this->jour<1 || this->jour > a) return false;
            return true;
        }else{
            if(this->jour < 1 || this->jour > t[this->mois]){
                return false;
            }
        }
        
        return true;
    };
    Date & Date::operator= (const Date & is){
        if(this!= &is){
            this->jour = is.jour;
            this->mois = is.mois;
            this->annee = is.annee;
        }
        return *this; 
    };
    std::ostream& operator<<(std::ostream &fichier, const Date &date){
       return fichier<<date.jour << ' ' << date.mois << ' ' << date.annee;
    };
    std::istream& operator>>(std::istream &fichier, Date & date){
        if (!fichier) return fichier;
        int jour,mois,annee;
        fichier>>jour>>mois>>annee;
        date.jour = jour;
        date.mois = (Mois)mois;
        date.annee = annee;
        return fichier;
    };
    bool annee_bissextile(int annee){
        if((annee % 4)!=0 )return false;
        if((annee % 100) != 0) return true;
        if((annee % 400) == 0) return true;
        return false;
    }
    void lister_mois(const char * decalage){
        std::cout << decalage << "1- JANVIER\n";
        std::cout << decalage << "2- FEVRIER\n";
        std::cout << decalage << "3- MARS\n";
        std::cout << decalage << "4- AVRIL\n";
        std::cout << decalage << "5- MAI\n";
        std::cout << decalage << "6- JUIN\n";
        std::cout << decalage << "7- JUILLET\n";
        std::cout << decalage << "8- AOUT\n";
        std::cout << decalage << "9- SEPTEMBRE\n";
        std::cout << decalage << "10- OCTOBRE\n";
        std::cout << decalage << "11- NOVEMBRE\n";
        std::cout << decalage << "12- DECEMBRE\n";
    }
    const char * mois(int i){
        switch(i){
            case 0:
                return "JANVIER";
            break;
            case 1:
                return "FERVIER";
            break;
            case 2:
                return "MARS";
            break;
            case 3:
                return "AVRIL";
            break;
            case 4:
                return "MAI";
            break;
            case 5:
                return "JUIN";
            break;
            case 6:
                return "JUILLET";
            break;
            case 7:
                return "AOUT";
            break;
            case 9:
                return "SEPTEMBRE";
            break;
            case 10:
                return "OCTOBRE";
            break;
            case 11:
                return "DECEMBRE";
            break;
            default:
                return "JANVIER";
        }
    }
    Date recup_date(const char * decalage="\t",const char * invalideDateMsg="Date invalide",const char * jourMsg ="Jour:",const char * invalideJourMsg="Jour invalide",const char * moisMsg ="Mois:",const char * invalideMoisMsg="Mois invalide",const char * anneeMsg ="Annee:",const char * invalideAnneeMsg="Annee invalide"){
        char jour[MAX], mois[MAX],annee[MAX];
        Date date;
recommencer:        do{ 
            std::cout <<decalage << jourMsg <<TAB;
            std::cin.getline(jour,MAX);
            int j = convertion1(jour);
            if(j < JOUR_MIN || j >JOUR_MAX){
                std::cout << decalage << invalideJourMsg << std::endl;
            }else{
                date.mettre_jour(j);
                break;
            }
        }while ( true);
        do{ std::cout << decalage << moisMsg << TAB;
            std::cin.getline(mois,MAX);
            int m = convertion1(mois);
            if((m - 1 )< MOIS_MIN || (m -1) >MOIS_MAX){
                std::cout << decalage << invalideMoisMsg << std::endl;
                lister_mois(decalage);    
            }else{
                date.mettre_mois((Mois)(m-1));
                break;
            }
        }while ( true);
        do{ std::cout << decalage << anneeMsg << TAB;
            std::cin.getline(annee,MAX);
            int a = convertion1(annee);
            if(a < ERROR_CODE){
                std::cout << decalage << invalideAnneeMsg << std::endl;
            }else{
                
                date.mettre_annee(a);
                break;
            }
        }while ( true);
        if(!date.est_valide()){
            std::cout << decalage << invalideDateMsg << std::endl;
            goto recommencer;
        }
        return date;
    }
}