#ifndef IA_PLUIE_H
#define IA_PLUIE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* >>> A REGLER : altitude (en metres) de l'endroit ou la carte est installee <<<
 * Le modele a ete entraine avec la pression ramenee au niveau de la mer
 * (donnees Meteostat). Le LPS22DF mesure la pression a l'altitude de la carte :
 * on la convertit avant l'inference. 1 m d'erreur d'altitude ~ 0,12 hPa. */
#define IA_ALTITUDE_M  236.0f

typedef struct {
    float   proba;    /* probabilite de pluie, 0..1                       */
    uint8_t pluie;    /* 1 = pluie, 0 = sec (valide seulement si valide)   */
    uint8_t valide;   /* 0 si une mesure est absente ou hors plage         */
} ia_pluie_result_t;

/* Pression station (hPa) -> pression ramenee au niveau de la mer (hPa) */
float ia_pression_niveau_mer(float p_station_hpa, float altitude_m);

/* Reseau seul : entrees en unites physiques, pression DEJA au niveau de la mer */
float ia_pluie_proba(float temp_c, float hum_pct, float pres_niveau_mer_hpa);

/* Fonction a appeler depuis TaskIA : verifie les mesures, convertit la
 * pression, calcule la probabilite et applique le seuil. */
ia_pluie_result_t ia_pluie_predire(float temp_c, float hum_pct, float pres_station_hpa);

#ifdef __cplusplus
}
#endif

#endif /* IA_PLUIE_H */
