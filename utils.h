#pragma once

void clearScreen();                      
void pauseScreen();                     
int getRandomInt(int min, int max);      
void errorHandler(int errorCode);        
int getValidatedInput(const char* prompt, int min, int max);  
int* chargerValeursFichier(const char* nomFichier, int* totalCartes);  
int* demanderValeursUtilisateur(int* totalCartes);
int demanderNbCartes();                  
int genererNbCartesAleatoire(int min, int max);  
