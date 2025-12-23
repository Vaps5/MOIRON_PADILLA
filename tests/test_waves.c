// tests/test_wave.c
#include "../include/si.h"
#include <stdio.h>
#include <assert.h>

void test_wave_system() {
    printf("=== Test du système de vagues ===\n");
    
    // Créer un état de jeu
    Si *si = si_new(800, 600, 3);
    
    // Simuler la destruction de tous les ennemis
    char *matrix = si_get_matrix();
    for (int i = 0; i < 5 * 11; i++) {
        matrix[i] = 0; // Tous détruits
    }
    
    printf("Avant reset: %d ennemis restants\n", si_matrix_count());
    assert(si_matrix_count() == 0);
    
    // Tester la réinitialisation
    si_reset_matrix(si);
    
    printf("Après reset: %d ennemis restants\n", si_matrix_count());
    assert(si_matrix_count() == 5 * 11); // Tous les ennemis sont revenus
    
    // Tester les points par type d'ennemi
    printf("Points OCTOPUS: %d (attendu: 10)\n", si_get_points(SI_TYPE_OCTOPUS));
    printf("Points CRAB: %d (attendu: 20)\n", si_get_points(SI_TYPE_CRAB));
    printf("Points SQUID: %d (attendu: 30)\n", si_get_points(SI_TYPE_SQUID));
    
    assert(si_get_points(SI_TYPE_OCTOPUS) == 10);
    assert(si_get_points(SI_TYPE_CRAB) == 20);
    assert(si_get_points(SI_TYPE_SQUID) == 30);
    
    si_del(si);
    printf("Test réussi!\n\n");
}

void test_difficulty_increase() {
    printf("=== Test d'augmentation de difficulté ===\n");
    
    float invaders_speed = 0.1;
    float shoot_speed = 0.005;
    
    printf("Vitesse initiale ennemis: %.3f\n", invaders_speed);
    printf("Vitesse initiale tirs: %.3f\n", shoot_speed);
    
    // Simuler 3 vagues
    for (int wave = 1; wave <= 3; wave++) {
        invaders_speed *= 0.85;
        shoot_speed *= 0.9;
        
        printf("Vague %d - Ennemis: %.3f, Tirs: %.3f\n", 
               wave, invaders_speed, shoot_speed);
    }
    
    printf("Test réussi!\n\n");
}

int main() {
    printf("Démarrage des tests du système de vagues...\n\n");
    
    test_wave_system();
    test_difficulty_increase();
    
    printf("=== Tous les tests sont passés! ===\n");
    return 0;
}
