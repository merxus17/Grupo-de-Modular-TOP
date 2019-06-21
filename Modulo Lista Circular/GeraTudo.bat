@ECHO  OFF
REM  Gera script de make de todos os exemplos simples

pushd  .

gmake /cTesteListaCircular  /pgmake
gmake /cTesteListaCircularDebug  /pgmake

popd
