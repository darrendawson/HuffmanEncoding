# include <stdio.h>
# include <stdlib.h>

//---openFile------------------------------------------------------------

void openFile()
{
  FILE *file;
  long fileSize;
  char *buffer;

  file = fopen("README", "r");

  // get file size
  fseek(file, 0, SEEK_END);
  fileSize = ftell(file);
  rewind(file);

  buffer = (char*)calloc(1, sizeof(char)*fileSize);

  fread(buffer, 1, fileSize, file);

  printf("%c\n", buffer[1]);

  fclose(file);
  free(buffer);
  return;
}

//---MAIN----------------------------------------------------------------

int main()
{
  
  openFile();
  return 0;
}
