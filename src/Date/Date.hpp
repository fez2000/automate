#ifndef DATE_H_INCLUDE
#define DATE_H_INCLUDE
#include "../fonctions/fonctions.hpp"
#define JOUR_MIN 1
#define JOUR_MAX 31
#define MOIS_MIN 0
#define MOIS_MAX 11
#include <ctime>
namespace Date
{
    class Date
    {
    private:
        int jour ;
        Mois mois;
        int annee;
        std::time_t time;
    public:
        Date();
        Date(int,Mois,int);
        Date (Date &);
        Date (const Date &);
        int retourner_jour() const;
        int retourner_jour();
        Mois retourner_mois() const;
        Mois retourner_mois();
        int retourner_annee() const;
        int retourner_annee();
        void mettre_jour(int);
        void mettre_mois(Mois);
        void mettre_annee(int);
        bool est_valide() const;
        bool est_valide();
        static std::string to_str(Date);
        Date & operator= (const Date &);
        friend std::ostream& operator<<(std::ostream &fichier, const Date &date);
        friend std::istream& operator>>(std::istream &is, Date & date);
        ~Date();
    };
    bool annee_bissextile(int annee);
    void lister_mois(const char * decalage);
    Date recup_date(const char * decalage,const char * invalideDateMsg,const char * jourMsg ,const char * invalidJourMsg,const char * moisMsg,const char * invalidMoisMsg,const char * anneeMsg ,const char * invalidAnneeMsg);
};    
    

#endif