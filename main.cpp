#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// ===== Classes =====

class Medecin {
private:
    int id;
    string nom;
    string prenom;
    string adresse;
    string specialite;
    double salaire;
    string dateAffectation;

public:
    Medecin() : id(0), nom(""), prenom(""), adresse(""), specialite(""), salaire(0.0), dateAffectation("") {}

    void saisir() {
        cout << "Saisir l'identifiant : "; cin >> id;
        cout << "Saisir le nom : "; cin >> nom;
        cout << "Saisir le pr�nom : "; cin >> prenom;
        cout << "Saisir l'adresse : "; cin.ignore(); getline(cin, adresse);
        cout << "Saisir la sp�cialit� : "; cin >> specialite;
        cout << "Saisir le salaire : "; cin >> salaire;
        cout << "Saisir la date d'affectation (jj/mm/aaaa) : "; cin >> dateAffectation;
    }

    void afficher() const {
        cout << "ID: " << id << ", Nom: " << nom << ", Pr�nom: " << prenom << ", Adresse: " << adresse
             << ", Sp�cialit�: " << specialite << ", Salaire: " << salaire
             << ", Date d'affectation: " << dateAffectation << endl;
    }

    int getId() const { return id; }
};

class Infirmier {
private:
    int id;
    string nom;
    string prenom;
    string adresse;
    double salaire;
    string typeContrat;
    string datePremiereAffectation;

public:
    Infirmier() : id(0), nom(""), prenom(""), adresse(""), salaire(0.0), typeContrat(""), datePremiereAffectation("") {}

    void saisir() {
        cout << "Saisir l'identifiant : "; cin >> id;
        cout << "Saisir le nom : "; cin >> nom;
        cout << "Saisir le pr�nom : "; cin >> prenom;
        cout << "Saisir l'adresse : "; cin.ignore(); getline(cin, adresse);
        cout << "Saisir le salaire : "; cin >> salaire;
        cout << "Saisir le type de contrat : "; cin >> typeContrat;
        cout << "Saisir la date de premi�re affectation (jj/mm/aaaa) : "; cin >> datePremiereAffectation;
    }

    void afficher() const {
        cout << "ID: " << id << ", Nom: " << nom << ", Pr�nom: " << prenom << ", Adresse: " << adresse
             << ", Salaire: " << salaire << ", Type de contrat: " << typeContrat
             << ", Date de premi�re affectation: " << datePremiereAffectation << endl;
    }

    int getId() const { return id; }
    string getDatePremiereAffectation() const { return datePremiereAffectation; }
};

class Service {
private:
    int code;
    string nom;
    Medecin medecinChef;
    string secretaire;
    int nombreMaxInfirmiers;
    vector<Infirmier> infirmiers;
    string dateLancement;

public:
    Service() : code(0), nom(""), secretaire(""), nombreMaxInfirmiers(0), dateLancement("") {}

    void saisir() {
        cout << "Saisir le code du service : "; cin >> code;
        cout << "Saisir le nom du service : "; cin >> nom;
        cout << "Saisir les informations du m�decin chef : \n";
        medecinChef.saisir();
        cout << "Saisir le nom du secr�taire : "; cin.ignore(); getline(cin, secretaire);
        cout << "Saisir le nombre maximum d'infirmiers : "; cin >> nombreMaxInfirmiers;
        cout << "Saisir la date de lancement (jj/mm/aaaa) : "; cin >> dateLancement;
    }

    void afficherService() const {
        cout << "Code du service : " << code << endl;
        cout << "Nom du service : " << nom << endl;
        cout << "M�decin chef : \n";
        medecinChef.afficher();
        cout << "Secr�taire : " << secretaire << endl;
        cout << "Nombre maximum d'infirmiers : " << nombreMaxInfirmiers << endl;
        cout << "Date de lancement : " << dateLancement << endl;
        cout << "Liste des infirmiers :\n";
        for (const auto& infirmier : infirmiers) {
            infirmier.afficher();
        }
    }

    int getCode() const { return code; }
    void setNom(const string& nouveauNom) { nom = nouveauNom; }
    void setMedecinChef(const Medecin& nouveauMedecin) { medecinChef = nouveauMedecin; }

    // V�rifie si un infirmier existe dans le service
    bool infirmierExiste(int idInfirmier) const {
        for (const auto& infirmier : infirmiers) {
            if (infirmier.getId() == idInfirmier) {
                return true;
            }
        }
        return false;
    }



    // Nouvelle m�thode pour afficher les infirmiers ayant moins de 5 ans d'exp�rience
    void afficherInfirmiersRecents() const {
        time_t now = time(nullptr);
        tm* nowTm = localtime(&now);
        int anneeActuelle = nowTm->tm_year + 1900;

        bool trouve = false;
        cout << "Infirmiers ayant moins de 5 ans d'exp�rience :\n";

        for (const auto& infirmier : infirmiers) {
            // Convertir la date de premi�re affectation en ann�e
            int anneeAffectation = stoi(infirmier.getDatePremiereAffectation().substr(6, 4));

            // Calculer l'anciennet�
            int anciennete = anneeActuelle - anneeAffectation;

            if (anciennete < 5) {
                infirmier.afficher();
                trouve = true;
            }
        }

        if (!trouve) {
            cout << "Aucun infirmier avec moins de 5 ans d'exp�rience." << endl;
        }
    }

    // Ajoute un infirmier au service
    void ajouterInfirmier(const Infirmier& infirmier) {
        if (infirmiers.size() >= nombreMaxInfirmiers) {
            cout << "Erreur : Nombre maximum d'infirmiers atteint." << endl;
            return;
        }
        if (infirmierExiste(infirmier.getId())) {
            cout << "Erreur : L'infirmier existe d�j�." << endl;
            return;
        }
        infirmiers.push_back(infirmier);
        cout << "Infirmier ajout� avec succ�s." << endl;
    }

    // Calcule l'�ge du service
    int calculerAge() const {
        time_t now = time(nullptr);
        tm* nowTm = localtime(&now);
        int anneeActuelle = nowTm->tm_year + 1900;
        int anneeLancement = stoi(dateLancement.substr(6, 4));
        return anneeActuelle - anneeLancement;
    }

    // Supprime un infirmier par ID
    void supprimerInfirmier(int idInfirmier) {
        for (auto it = infirmiers.begin(); it != infirmiers.end(); ++it) {
            if (it->getId() == idInfirmier) {
                infirmiers.erase(it);
                cout << "Infirmier supprim� avec succ�s." << endl;
                return;
            }
        }
        cout << "Erreur : L'infirmier avec l'ID " << idInfirmier << " ne fait pas partie du service." << endl;
    }
};

// ===== Fonctions =====

void afficherMenu();
void menuServices(vector<Service>& services);
void ajouterService(vector<Service>& services);
void afficherTousLesServices(const vector<Service>& services);
void modifierNomService(vector<Service>& services);
void modifierMedecinChef(vector<Service>& services);
void supprimerService(vector<Service>& services);
void servicesPlusDe10Ans(const vector<Service>& services);

int main() {
    vector<Service> services;
    int choix;

    do {
        afficherMenu();
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                menuServices(services);
                break;
            case 2:
                cout << "Merci d'avoir utilis� le programme. � bient�t !" << endl;
                break;
            default:
                cout << "Choix invalide, veuillez r�essayer." << endl;
        }
    } while (choix != 2);

    return 0;
}

void afficherMenu() {
    cout << "\n=== Menu Principal ===" << endl;
    cout << "1. Gestion des services" << endl;
    cout << "2. Quitter" << endl;
}

void menuServices(vector<Service>& services) {
    int choix;
    do {
        cout << "\n=== Menu Gestion des Services ===" << endl;
        cout << "1. Ajouter un service" << endl;
        cout << "2. Afficher tous les services" << endl;
        cout << "3. Modifier le nom d'un service" << endl;
        cout << "4. Modifier le m�decin chef d'un service" << endl;
        cout << "5. Supprimer un service" << endl;
        cout << "6. Afficher les services lanc�s il y a plus de 10 ans" << endl;
        cout << "7. Supprimer un infirmier dans un service" << endl;
        cout << "8. Ajouter un infirmier � un service" << endl;
        cout << "9. Afficher les infirmiers ayant moins de 5 ans d'exp�rience" << endl;
        cout << "10. Retour au menu principal" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                ajouterService(services);
                break;
            case 2:
                afficherTousLesServices(services);
                break;
            case 3:
                modifierNomService(services);
                break;
            case 4:
                modifierMedecinChef(services);
                break;
            case 5:
                supprimerService(services);
                break;
            case 6:
                servicesPlusDe10Ans(services);
                break;
            case 7: {
                int codeService, idInfirmier;
                cout << "Entrez le code du service : ";
                cin >> codeService;
                cout << "Entrez l'ID de l'infirmier � supprimer : ";
                cin >> idInfirmier;
                for (auto& service : services) {
                    if (service.getCode() == codeService) {
                        service.supprimerInfirmier(idInfirmier);
                        break;
                    }
                }
                break;
            }
            case 8: {
                int codeService;
                cout << "Entrez le code du service : ";
                cin >> codeService;
                for (auto& service : services) {
                    if (service.getCode() == codeService) {
                        Infirmier nouvelInfirmier;
                        nouvelInfirmier.saisir();
                        service.ajouterInfirmier(nouvelInfirmier);
                        break;
                    }
                }
                break;
            }
            case 9: {
                int codeService;
                cout << "Entrez le code du service : ";
                cin >> codeService;
                for (const auto& service : services) {
                    if (service.getCode() == codeService) {
                        service.afficherInfirmiersRecents();
                        break;
                    }
                }
                break;
            }
            case 10:
                cout << "Retour au menu principal." << endl;
                break;
            default:
                cout << "Choix invalide, veuillez r�essayer." << endl;
        }
    } while (choix != 10);
}

void ajouterService(vector<Service>& services) {
    Service nouveauService;
    cout << "Ajout d'un nouveau service : \n";
    nouveauService.saisir();
    for (const auto& service : services) {
        if (service.getCode() == nouveauService.getCode()) {
            cout << "Erreur : Le service avec le code " << nouveauService.getCode() << " existe d�j�." << endl;
            return;
        }
    }
    services.push_back(nouveauService);
    cout << "Service ajout� avec succ�s." << endl;
}

void afficherTousLesServices(const vector<Service>& services) {
    if (services.empty()) {
        cout << "Aucun service n'est enregistr�." << endl;
        return;
    }
    for (const auto& service : services) {
        service.afficherService();
        cout << "------------------------" << endl;
    }
}

void modifierNomService(vector<Service>& services) {
    int codeService;
    string nouveauNom;
    cout << "Entrez le code du service � modifier : ";
    cin >> codeService;

    for (auto& service : services) {
        if (service.getCode() == codeService) {
            cout << "Entrez le nouveau nom du service : ";
            cin.ignore();
            getline(cin, nouveauNom);
            service.setNom(nouveauNom);
            cout << "Nom du service modifi� avec succ�s." << endl;
            return;
        }
    }
    cout << "Erreur : Service introuvable." << endl;
}

void modifierMedecinChef(vector<Service>& services) {
    int codeService;
    cout << "Entrez le code du service : ";
    cin >> codeService;

    for (auto& service : services) {
        if (service.getCode() == codeService) {
            Medecin nouveauMedecin;
            cout << "Saisissez les nouvelles informations du m�decin chef : \n";
            nouveauMedecin.saisir();
            service.setMedecinChef(nouveauMedecin);
            cout << "M�decin chef modifi� avec succ�s." << endl;
            return;
        }
    }
    cout << "Erreur : Service introuvable." << endl;
}

void supprimerService(vector<Service>& services) {
    int codeService;
    cout << "Entrez le code du service � supprimer : ";
    cin >> codeService;

    for (auto it = services.begin(); it != services.end(); ++it) {
        if (it->getCode() == codeService) {
            services.erase(it);
            cout << "Service supprim� avec succ�s." << endl;
            return;
        }
    }
    cout << "Erreur : Service introuvable." << endl;
}

void servicesPlusDe10Ans(const vector<Service>& services) {
    time_t now = time(nullptr);
    tm* nowTm = localtime(&now);
    int anneeActuelle = nowTm->tm_year + 1900;

    bool trouve = false;
    for (const auto& service : services) {
        if (service.calculerAge() > 10) {
            service.afficherService();
            cout << "------------------------" << endl;
            trouve = true;
        }
    }
    if (!trouve) {
        cout << "Aucun service lanc� il y a plus de 10 ans." << endl;
    }
}
