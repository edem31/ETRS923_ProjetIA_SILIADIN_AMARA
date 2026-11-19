#include "ia_pluie.h"
#include "ia_pluie_poids.h"   /* genere par export_poids_c.py */

#include <math.h>

/* Plages utilisees a l'entrainement (memes que le nettoyage du script Python) */
#define IA_TEMP_MIN   (-80.0f)
#define IA_TEMP_MAX     60.0f
#define IA_HUM_MIN       0.0f
#define IA_HUM_MAX     100.0f
#define IA_PRES_MIN    800.0f
#define IA_PRES_MAX   1100.0f

float ia_pression_niveau_mer(float p_station_hpa, float altitude_m)
{
    /* Formule barometrique (atmosphere standard) */
    return p_station_hpa * powf(1.0f - altitude_m / 44330.0f, -5.255f);
}

float ia_pluie_proba(float temp_c, float hum_pct, float pres_niveau_mer_hpa)
{
    float x[IA_N_IN];
    float h1[IA_N_H1];
    float h2[IA_N_H2];
    float z;
    int i, j;

    /* Normalisation : (x - moyenne) / ecart_type */
    x[0] = (temp_c             - IA_MOY[0]) / IA_ECT[0];
    x[1] = (hum_pct            - IA_MOY[1]) / IA_ECT[1];
    x[2] = (pres_niveau_mer_hpa - IA_MOY[2]) / IA_ECT[2];

    /* Couche 1 : 3 -> 12, ReLU */
    for (j = 0; j < IA_N_H1; j++) {
        float s = IA_B1[j];
        for (i = 0; i < IA_N_IN; i++) {
            s += x[i] * IA_W1[i][j];
        }
        h1[j] = (s > 0.0f) ? s : 0.0f;
    }

    /* Couche 2 : 12 -> 6, ReLU */
    for (j = 0; j < IA_N_H2; j++) {
        float s = IA_B2[j];
        for (i = 0; i < IA_N_H1; i++) {
            s += h1[i] * IA_W2[i][j];
        }
        h2[j] = (s > 0.0f) ? s : 0.0f;
    }

    /* Sortie : 6 -> 1, sigmoide */
    z = IA_B3;
    for (i = 0; i < IA_N_H2; i++) {
        z += h2[i] * IA_W3[i];
    }
    return 1.0f / (1.0f + expf(-z));
}

ia_pluie_result_t ia_pluie_predire(float temp_c, float hum_pct, float pres_station_hpa)
{
    ia_pluie_result_t r = { 0.0f, 0U, 0U };

    /* NAN : toutes les comparaisons sont fausses, donc rejete ici */
    if (!(temp_c >= IA_TEMP_MIN && temp_c <= IA_TEMP_MAX) ||
        !(hum_pct >= IA_HUM_MIN && hum_pct <= IA_HUM_MAX) ||
        !(pres_station_hpa > 0.0f)) {
        return r;
    }

    float p0 = ia_pression_niveau_mer(pres_station_hpa, IA_ALTITUDE_M);
    if (!(p0 >= IA_PRES_MIN && p0 <= IA_PRES_MAX)) {
        return r;
    }

    r.proba  = ia_pluie_proba(temp_c, hum_pct, p0);
    r.pluie  = (r.proba >= IA_SEUIL) ? 1U : 0U;
    r.valide = 1U;
    return r;
}
