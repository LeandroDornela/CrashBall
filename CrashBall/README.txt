INSTRU��ES

Para come�ar, abra o arquivo 'cg.workspace'.

===============================================================================

Windows

N�o � preciso configurar o freeglut/glui no windows pois os arquivos 
para este sistema j� est�o presentes neste projeto.

O projeto foi criado para ser executado na IDE Codeblocks que pode 
ser baixada gratuitamente no link abaixo:
http://downloads.sourceforge.net/codeblocks

===============================================================================

Linux

Para compilar os arquivos deste projeto no linux, os seguintes pacotes (ou
seus pacotes equivalentes) devem estar instalados:
* codeblocks
* g++
* freeglut3-dev
* libglew-dev 
* libXxf86vm-dev
* lib32z1-dev e/ou zlib1g-dev

Essas instru��es foram testadas no Ubuntu 14.04 LTS 64 bits. Para a vers�o
32 bits deste sistema operacional, modifique no projeto a biblioteca para 
leitura de arquivos PNG para o vers�o correspondente (libpng12_linux32.a).

===============================================================================
Corre��o de erros comuns
===============================================================================

Sistema operacional: Ubuntu 14.04 LTs

Erro: Ao compilar c�digos com o GLUI no linux aparece a seguinte mensagem
Inconsistency detected by ld.so: dl-version.c: 224: _dl_check_map_versions: 
Assertion `needed != ((void *)0)' failed!

Solu��o:
Em "Build Options" selecionar a op��o "Linux".
A seguir, v� em "Linker settings" e na op��o "Other Linker options" acrescente:
-L/usr/lib/nvidia-304
Substitua a pasta "nvidia-304" pela correspondente do seu sistema operacional.

-------------------------------------------------------------------------------
