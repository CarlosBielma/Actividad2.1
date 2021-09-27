#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *image, *outputImage, *lecturas;
    image = fopen("pai0.bmp","rb");          //Imagen original a transformar
    outputImage = fopen("pai0gray.bmp","wb");    //Imagen transformada

    long ancho;
    long alto;
    unsigned char r, g, b;               //Pixel
    unsigned char xx[54];
    int red[256]={0};
    int blue[256]={0};
    int green[256]={0};
    int gray[256]={0};
    int gray2[256]={0};

    for(int i=0; i<54; i++){
       xx[i] = fgetc(image);
      fputc(xx[i], outputImage);   //Copia cabecera a nueva imagen
    } 
    ancho = (long)xx[20]*65536+(long)xx[19]*256+(long)xx[18];
    alto = (long)xx[24]*65536+(long)xx[23]*256+(long)xx[22];
    printf("largo img %li\n",alto);
    printf("ancho img %li\n",ancho);

    while(!feof(image)){                                      //Grises
      b = fgetc(image);
      g = fgetc(image);
      r = fgetc(image);
      unsigned char pixel = 0.3*r+0.59*g+0.1*b;
      //unsigned char pixel = 0.21*r+0.72*g+0.07*b;
      blue[b]+=1;
      green[g]+=1;
      red[r]+=1;
      gray[pixel]+=1;
      fputc(pixel, outputImage);
      fputc(pixel, outputImage);
      fputc(pixel, outputImage);
    }
    lecturas=fopen("Histograma.txt","w");
    fprintf(lecturas, "Color\t Tono\t numero de repeticiones\n");
    printf("RED \n");
    for (int i = 0; i<=255; i++){
      printf("%d \n", red[i]);
      fprintf(lecturas, "%d\t %d \t Red\n", i, red[i]);
    }
    printf("BLUE \n");
    for (int i = 0; i<=255; i++){
      printf("%d \n", blue[i]);
      fprintf(lecturas, "%d\t %d \t Blue\n", i, blue[i]);
    }
    printf("GREEN \n");
    for (int i = 0; i<=255; i++){
      printf("%d \n", green[i]);
      fprintf(lecturas, "%d\t %d \t Green\n", i, green[i]);
    }
    printf("GRAY \n");
    for (int i = 0; i<=255; i++){
      printf("%d \n", gray[i]);
      fprintf(lecturas, "%d\t %d \t Gray\n", i, gray[i]);
    }

    fclose(image);
    fclose(outputImage);
    return 0;
}

