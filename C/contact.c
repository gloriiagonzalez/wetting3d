#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846


double cardano(double p, double q) {
    double D = (q/2.0)*(q/2.0) + (p/3.0)*(p/3.0)*(p/3.0);
    return cbrt(-q/2.0 + sqrt(D)) + cbrt(-q/2.0 - sqrt(D));
}

int main() {
    FILE *infile = fopen("entrada.txt", "r"); //sustituir "entrada.txt" por el fichero de datos
    if (!infile) {
        printf("Error: no se puede abrir\n");
        return 1;
    }

    FILE *outfile = fopen("contact.txt", "w");
    if (!outfile) {
        printf("Error: no se puede crear\n");
        return 1;
    }

    fprintf(outfile, "MCS Area Volume r h theta_rad theta_deg\n");

    char line[256];
    int mcs;
    double A, V;
    double r, h, theta_rad, theta_deg;

    // saltar cabecera del fichero de entrada
    fgets(line, sizeof(line), infile);

    while (fgets(line, sizeof(line), infile)) {
        if (sscanf(line, "%d %lf %lf", &mcs, &V, &A) != 3) continue;

     
        r = sqrt(A / PI);

       
        h = cardano(3.0*r*r, -6.0*V/PI);


        theta_rad = 2.0 * atan(h / r);
        theta_deg = theta_rad * 180.0 / PI;

        fprintf(outfile, "%d %g %g %g %g %g %g\n",
                mcs, A, V, r, h, theta_rad, theta_deg);
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}
