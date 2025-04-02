//
//  gnuplot_linux.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void plotResults(double* xData, double* yData, double *yData2, int dataSize);
int main() {
    int i = 0;
    int nIntervals = 100;
    double intervalSize = 1.0;
    double stepSize = intervalSize/nIntervals;
    double* xData = (double*) malloc((nIntervals+1)*sizeof(double));
    double* yData = (double*) malloc((nIntervals+1)*sizeof(double));
    double* yData2 = (double*) malloc((nIntervals+1)*sizeof(double));
    xData[0] = 0.0;
    double x0 = 0.0;
    for (i = 0; i < nIntervals; i++) {
        x0 = xData[i];
        xData[i+1] = x0 + stepSize;
    }
    for (i = 0; i <= nIntervals; i++) {
        x0 = xData[i];
        yData[i] = sin(x0)*cos(10*x0);
    }
    for (i = 0; i <= nIntervals; i++) {
        x0 = xData[i];
        yData2[i] = sin(x0)*cos(5*x0);
    }
    plotResults(xData, yData, yData2, nIntervals);
    return 0;
}
void plotResults(double* xData, double* yData, double* yData2, int dataSize) {
    FILE *gnuplotPipe,*tempDataFile;
    const char *tempDataFileName1 = "tempData1";
    const char *tempDataFileName2 = "tempData2";
    double x,y, x2, y2;
    int i;
    const char *title = "Try it";
    const char *yLabel = "Y";
    gnuplotPipe = popen("gnuplot -persist", "w");
    fprintf(gnuplotPipe, "set grid\n");
    fprintf(gnuplotPipe, "set title '%s'\n", title);
    fprintf(gnuplotPipe, "set arrow from 0,graph(0,0) to 0,graph(1,1) nohead lc rgb 'red'\n");
    fprintf(gnuplotPipe, "set xlabel 'Announcement Date'\nset ylabel '%s'\n", yLabel);
    if (gnuplotPipe) {
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines\n",tempDataFileName1, tempDataFileName2);
        fflush(gnuplotPipe);
        tempDataFile = fopen(tempDataFileName1,"w");
        for (i=0; i <= dataSize; i++) {
            x = xData[i];
            y = yData[i];
            fprintf(tempDataFile,"%lf %lf\n",x,y);
        }
        fclose(tempDataFile);
        tempDataFile = fopen(tempDataFileName2,"w");
        for (i=0; i <= dataSize; i++) {
            x2 = xData[i];
            y2 = yData2[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        printf("press enter to continue...");
        getchar();
        remove(tempDataFileName1);
        remove(tempDataFileName2);
        fprintf(gnuplotPipe,"exit \n");
    } else {        
        printf("gnuplot not found...");    
    }
} 

