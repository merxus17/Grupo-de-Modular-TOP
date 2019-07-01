@ECHO  OFF
REM  Gera script de make de todos os exemplos simples

pushd  .

gmake /cTestePartidaSemInstrumentacao  /pgmake
gmake /cTestePartidaComInstrumentacao  /pgmake

popd
