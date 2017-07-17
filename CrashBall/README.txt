INSTRUÇÕES

Para começar, abra o arquivo 'cg.workspace'.

===============================================================================

Windows

Não é preciso configurar o freeglut/glui no windows pois os arquivos 
para este sistema já estão presentes neste projeto.

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

Essas instruções foram testadas no Ubuntu 14.04 LTS 64 bits. Para a versão
32 bits deste sistema operacional, modifique no projeto a biblioteca para 
leitura de arquivos PNG para o versão correspondente (libpng12_linux32.a).

===============================================================================
Correção de erros comuns
===============================================================================

Sistema operacional: Ubuntu 14.04 LTs

Erro: Ao compilar códigos com o GLUI no linux aparece a seguinte mensagem
Inconsistency detected by ld.so: dl-version.c: 224: _dl_check_map_versions: 
Assertion `needed != ((void *)0)' failed!

Solução:
Em "Build Options" selecionar a opção "Linux".
A seguir, vá em "Linker settings" e na opção "Other Linker options" acrescente:
-L/usr/lib/nvidia-304
Substitua a pasta "nvidia-304" pela correspondente do seu sistema operacional.

-------------------------------------------------------------------------------
